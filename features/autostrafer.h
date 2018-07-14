#ifndef SOURCE_AUTOSTRAFER_H
#define SOURCE_AUTOSTRAFER_H

#include "../framework/players.h"

struct CUserCmd;

namespace SourceAutostrafer
{
	constexpr float AIR_SPEED_CAP = 30.f;
	constexpr float MAX_MOVE = 450.f;
	constexpr float SPEED_TOWARDS = 1.3f;

	float lastAng = 0.f;
	char sign = 0;

	inline void Run(CUserCmd* cmd, LocalPlayer* lpData)
	{
#ifdef SOURCE_ENGINEPREDICTION_H
		bool onGround = SourceEnginePred::prevFlags & FL_ONGROUND;
#else
		bool onGround = lpData->flags & Flags::ONGROUND;
#endif

		lastAng = SourceEssentials::oldAngles.y;

		if (onGround || cmd->buttons & (IN_FORWARD | IN_BACK | IN_MOVERIGHT | IN_MOVELEFT))
			return;

		float speed = lpData->velocity.Length<2>();

		if (speed < AIR_SPEED_CAP * 0.5f)
			cmd->forwardmove = MAX_MOVE;
		else {
			vec3_t velAngles = lpData->velocity.GetAngles(true);
			float idealAngle = std::clamp(atan2f(AIR_SPEED_CAP, speed) * RAD2DEG, -90.f, 90.f);
			float velDeg = idealAngle * SPEED_TOWARDS;
			vec3_t backup = lpData->angles;
			vec3_t ang = SourceEssentials::oldAngles;
			float velAngDelta = NormalizeFloat(velAngles.y - lastAng, -180.f, 180.f);

			cmd->viewangles = SourceEssentials::oldAngles;
			cmd->forwardmove = 0.f;

			if (fabsf(velAngDelta) < velDeg)
				ang.y += idealAngle * 0.5f * (sign * 2 - 1);
			else {
				sign = velAngDelta > 0;
			    ang.y = velAngles.y - velDeg * (sign * 2 - 1);
			}

			cmd->sidemove = MAX_MOVE * (sign * 2 - 1);
			sign = (char)!sign;

			SourceEssentials::CorrectMovement(ang, cmd, 0);

			lpData->angles = backup;
		}
	}
}

#endif
