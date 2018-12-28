#ifndef SOURCE_GAMEMOVEMENT_H
#define SOURCE_GAMEMOVEMENT_H

namespace SourceGameMovement
{
	bool PlayerMove(C_BaseEntity* player, vec3_t* position, vec3_t* velocity, bool* isGrounded, bool jumpPressed, float interval, bool incPlayers = false);
}

#ifdef SOURCE_DEFINITIONS
const int PLAYER_MAX_SAFE_FALL_SPEED = 580;
const float GAMEMOVEMENT_JUMP_HEIGHT = 21.0f;
const int MAX_CLIP_PLANES = 5;
const int COORD_INTEGER_BITS = 14;
const int COORD_FRACTIONAL_BITS = 5;
const int COORD_DENOMINATOR = 1 << COORD_FRACTIONAL_BITS;
const float COORD_RESOLUTION = 1.0 / (double)COORD_DENOMINATOR;
const int COORD_INTEGER_BITS_MP = 11;
const int COORD_FRACTIONAL_BITS_MP_LOWPRECISION = 3;
const int COORD_DENOMINATOR_LOWPRECISION = 1 << COORD_FRACTIONAL_BITS_MP_LOWPRECISION;
const int COORD_RESOLUTION_LOWPRECISION = 1.0 / COORD_DENOMINATOR_LOWPRECISION;
const int NORMAL_FRACTIONAL_BITS = 11;
const int NORMAL_DENOMINATOR = (1 << NORMAL_FRACTIONAL_BITS) - 1;
const int NORMAL_RESOLUTION = 1.0 / NORMAL_DENOMINATOR;
const float STEP_SIZE = 15.f;


static ConVar* sv_gravity = nullptr;
static ConVar* sv_jump_impulse = nullptr;
static bool includePlayers = false;


static void TracePlayerBBox(C_BaseEntity* player, int mask, vec3_t start, vec3_t end, CGameTrace* tr)
{
	if (!includePlayers) {
		CTraceFilterWorldAndPropsOnly filter;
		Ray_t ray;
		ray.Init(start, end, (vec3)player->GetCollideable()->OBBMins(), (vec3)player->GetCollideable()->OBBMaxs());
		engineTrace->TraceRay(ray, mask, &filter, tr);
	} else {
		CTraceFilter filter;
		filter.pSkip = player;
		Ray_t ray;
		ray.Init(start, end, (vec3)player->GetCollideable()->OBBMins(), (vec3)player->GetCollideable()->OBBMaxs());
		engineTrace->TraceRay(ray, mask, &filter, tr);
	}
}

static int ClipVelocity(vec3_t& in, vec3_t& normal, vec3_t& out, float overbounce)
{
	float backoff;
	float change;
	float angle;
	int i, blocked;

	angle = normal[2];

	blocked = 0x00;
	if (angle > 0)
		blocked |= 0x01;
	if (!angle)
		blocked |= 0x02;

	backoff = in.Dot(normal) * overbounce;

	for (i = 0; i < 3; i++) {
		change = normal[i] * backoff;
		out[i] = in[i] - change;
	}

	// iterate once to make sure we aren't still moving through the plane
	float adjust = out.Dot(normal);
	if (adjust < 0.0f)
		out -= (normal * adjust);

	// Return blocking flags.
	return blocked;
}

static void TryPlayerMove(C_BaseEntity* player, vec3_t& vecPos, vec3_t& vecVel, vec3_t end, vec3_t originalVelocity, CGameTrace& pm, float interval)
{
	vec3_t dir;

	float d;
	float allFraction = 0;

	int blocked = 0;
	int numplanes = 0;

	CGameTrace tr;

	vec3_t planes[MAX_CLIP_PLANES];

	float timeLeft = interval;

	for (int i = 0; i < 4; i++) {
		if (vecVel.Length() == 0)
			break;

		end = vecPos + vecVel * timeLeft;

		TracePlayerBBox(player, MASK_PLAYERSOLID, vecPos, end, &tr);

		allFraction += tr.fraction;

		if (tr.allsolid) {
			vecVel = 0.f;
			return;
		}

		if (tr.fraction > 0) {
			if (i > 0 && tr.fraction == 1) {
				// There's a precision issue with terrain tracing that can cause a swept box to successfully trace
				// when the end position is stuck in the triangle.  Re-run the test with an uswept box to catch that
				// case until the bug is fixed.
				// If we detect getting stuck, don't allow the movement
				CGameTrace stuck;
				TracePlayerBBox(player, MASK_PLAYERSOLID, vecPos, end, &stuck);
				if (stuck.startsolid || stuck.fraction != 1.0f) {
					vecVel = 0.f;
					break;
				}
			}

			vecPos = tr.endpos;
			vecVel = originalVelocity;
			numplanes = 0;
		}

		// If we covered the entire distance, we are done
		//  and can return.
		if (tr.fraction == 1)
			break;

		// If the plane we hit has a high z component in the normal, then
		//  it's probably a floor
		if (tr.plane.normal[2] > 0.7)
			blocked |= 1;
		// If the plane has a zero z component in the normal, then it's a
		//  step or wall
		if (!tr.plane.normal[2])
			blocked |= 2;

		// Reduce amount of m_flFrameTime left by total time left * fraction
		//  that we covered.
		timeLeft -= timeLeft * tr.fraction;

		// Did we run out of planes to clip against?
		if (numplanes >= MAX_CLIP_PLANES) {
			// this shouldn't really happen
			//  Stop our movement if so.
			vecVel = 0.f;
			break;
		}

		// Set up next clipping plane
	    planes[numplanes] = tr.plane.normal;
		numplanes++;

		int o = 0;
		int j = 0;

		if (numplanes == 0) {
			for (i = 0; i < numplanes; i++) {
				if (planes[i][2] > 0.7) {
					// floor or slope
					ClipVelocity(originalVelocity, planes[i], vecVel, 1);
				    originalVelocity = vecVel;
				}
			}

			originalVelocity = vecVel;
		} else {
			for (o = 0; o < numplanes; o++) {
				ClipVelocity(originalVelocity, planes[o], vecVel, 1);

				for (j = 0; j < numplanes; j++)
					if (j != o)
						// Are we now moving against this plane?
						if (vecVel.Dot(planes[j]) < 0)
							break;	// not ok
				if (j == numplanes)  // Didn't have to clip, so we're ok
					break;
			}
		}

		// Did we go all the way through plane set
		if (o == numplanes) {
			if (numplanes != 2) {
				vecVel = 0.f;
				break;
			}
		    dir = planes[0].Cross(planes[1]);
			dir.Normalize();
			vecVel = dir * dir.Dot(vecVel);
		}

		//
		// if original velocity is against the original velocity, stop dead
		// to avoid tiny occilations in sloping corners
		//
		d = vecVel.Dot(originalVelocity);
		if (d <= 0) {
		    vecVel = 0.f;
			break;
		}
	}

	if (allFraction == 0)
		vecVel = 0.f;

	// Check if they slammed into a wall
	[[maybe_unused]] float slamVol = 0.0f;

	float lateralStoppingAmount = originalVelocity.Length<2>() - vecVel.Length<2>();
	if (lateralStoppingAmount > PLAYER_MAX_SAFE_FALL_SPEED * 2.0f)
		slamVol = 1.0f;
	else if (lateralStoppingAmount > PLAYER_MAX_SAFE_FALL_SPEED)
		slamVol = 0.85f;
}

static bool StayOnGround(C_BaseEntity* player, vec3_t& position)
{

	CGameTrace tr;

    vec3_t start = position;
	vec3_t end = position;
	start.z += 2;
	end.z -= STEP_SIZE;

	//This really kills framerate
	//TracePlayerBBox(player, MASK_PLAYERSOLID, position, start, &tr);
	//start = tr.endpos;

	TracePlayerBBox(player, MASK_PLAYERSOLID, start, end, &tr);

	if (tr.fraction > 0.0f && tr.fraction < 1.0f && !tr.startsolid && tr.plane.normal[2] >= 0.7) {
		float delta = fabs(position.z - tr.endpos[2]);

		//This is incredibly hacky. The real problem is that trace returning that strange value we can't network over.
		if (delta > 0.5f * COORD_RESOLUTION)
			position = tr.endpos;

		return true;
	}

	return false;
}

static void StepMove(C_BaseEntity* player, CGameTrace& trace, vec3_t& position, vec3_t velocity, vec3_t& vecDestination, float interval)
{
	vec3_t vecEndPos = vecDestination;

	// Try sliding forward both on ground and up 16 pixels
	//  take the move that goes farthest
	vec3_t vecPos, vecVel;
	vecPos = position;
	vecVel = velocity;

	// Slide move down.
	TryPlayerMove(player, position, velocity, vecEndPos, velocity, trace, interval);

	// Down results.
	vec3_t vecDownPos, vecDownVel;
	vecDownPos = position;
	vecDownVel = velocity;

	// Reset original values.
	position = vecPos;
	velocity = vecVel;

	// Move up a stair height.
	vecEndPos = position;
	vecEndPos.z += STEP_SIZE + 0.0001f;

	TracePlayerBBox(player, MASK_PLAYERSOLID, position, vecEndPos, &trace);
	if (!trace.startsolid && !trace.allsolid)
		position = trace.endpos;

	// Slide move up.
	TryPlayerMove(player, position, velocity, vecEndPos, velocity, trace, interval);

	// Move down a stair (attempt to).
	vecEndPos = position;
	vecEndPos.z -= STEP_SIZE + 0.0001f; // *(float*)((uintptr_t)(*((void**)player->m_Local())) + 0x64) + 0.0001f; //Step Size

	TracePlayerBBox(player, MASK_PLAYERSOLID, position, vecEndPos, &trace);

	// If we are not on the ground any more then use the original movement attempt.
	if (trace.plane.normal[2] < 0.7) {
		position = vecDownPos;
		velocity = vecDownVel;
		return;
	}

	// If the trace ended up in empty space, copy the end over to the origin.
	if (!trace.startsolid && !trace.allsolid)
		position = trace.endpos;

	// Copy this origin to up.
	vec3_t vecUpPos = position;

	// decide which one went farther
	float downDist = (vecDownPos.x - vecPos.x) * (vecDownPos.x - vecPos.x) + (vecDownPos.y - vecPos.y) * (vecDownPos.y - vecPos.y);
	float upDist = (vecUpPos.x - vecPos.x) * (vecUpPos.x - vecPos.x) + (vecUpPos.y - vecPos.y) * (vecUpPos.y - vecPos.y);
	if (downDist > upDist) {
		position = vecDownPos;
		velocity = vecDownVel;
	} else
		// copy z value from slide move
		velocity.z = vecDownVel.z;
}

bool SourceGameMovement::PlayerMove(C_BaseEntity* player, vec3_t* position, vec3_t* velocity, bool* isGrounded, bool jumpPressed, float interval, bool incPlayers)
{
	includePlayers = incPlayers;

	if (!sv_gravity)
		sv_gravity = cvar->FindVar(ST("sv_gravity"));

	float gravity = sv_gravity ? sv_gravity->GetFloat() : 800;

	if (!*isGrounded)
		velocity->z -= gravity * interval;
	else
		velocity->z = 0.f;

	//Clamp velocity to 3500
	if (velocity->Length() > 3500.f)
		*velocity *= 3500.f / velocity->Length();

	vec3_t startPosition = *position;
	vec3_t wantPosition = *position + *velocity * interval;
	vec3_t originalVelocity = *velocity;

	CGameTrace pm;

	TracePlayerBBox(player, MASK_PLAYERSOLID, startPosition, wantPosition, &pm);

	if (pm.fraction == 1) {
		*position = wantPosition;

		if (*isGrounded)
			*isGrounded = StayOnGround(player, *position);

		return true;
	}

	if (*isGrounded) {
		StepMove(player, pm, startPosition, *velocity, wantPosition, interval);
		StayOnGround(player, startPosition);
		*position = startPosition;
		return true;
	} else {
		*isGrounded = StayOnGround(player, startPosition);

		TryPlayerMove(player, *position, *velocity, wantPosition, originalVelocity, pm, interval);

		if (*isGrounded && jumpPressed) {
			*isGrounded = false;

			if (!sv_jump_impulse)
				sv_jump_impulse = cvar->FindVar(ST("sv_jump_impulse"));

			velocity->z = sv_jump_impulse->GetFloat();
		}
	}

	return pm.plane.normal[2] >= 0.7f;
}
#endif

#endif
