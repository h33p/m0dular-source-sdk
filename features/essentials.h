#ifndef ESSENTIALS_H
#define ESSENTIALS_H

#include "../framework/players.h"

struct CUserCmd;

namespace SourceEssentials
{
#ifdef SOURCE_DEFINITIONS
	vec3_t oldAngles(0);
	vec3_t prevAngles(0);
	int prevFramecount = 0;
#else
	extern vec3_t oldAngles;
	extern vec3_t prevAngles;
	extern int prevFramecount;
#endif

	inline void CorrectMovement(vec3_t& oldAngles, CUserCmd* cmd, int movetype)
	{
		fflush(stdout);
		vec3_t frL, riL, upL, frC, riC, upC;
		oldAngles.GetVectors(frL, riL, upL, true);
		vec3_t viewangles = cmd->viewangles;
		viewangles.GetVectors(frC, riC, upC, true);

		frL.z = riL.z = frC.z = riC.z = 0.f;
		frL.Normalize();
		riL.Normalize();
		frC.Normalize();
		riC.Normalize();

		vec3_t worldCoords = frL * cmd->forwardmove + riL * cmd->sidemove;

		cmd->sidemove = (frC.x * worldCoords.y - frC.y * worldCoords.x) / (riC.y * frC.x - riC.x * frC.y);
		cmd->forwardmove = (riC.y * worldCoords.x - riC.x * worldCoords.y) / (riC.y * frC.x - riC.x * frC.y);

		oldAngles = cmd->viewangles;
	}

	/*
	  These functions only deal with data provided by the CMD.
	  Other data needs to be filled in manually.
	*/
	inline void UpdateData(CUserCmd* cmd, LocalPlayer* lpData)
	{

		lpData->angles = cmd->viewangles;
		oldAngles = lpData->angles;

		int keys = 0;
		if (cmd->buttons & IN_ATTACK)
			keys |= Keys::ATTACK1;
		if (cmd->buttons & IN_ATTACK2)
			keys |= Keys::ATTACK2;
		if (cmd->buttons & IN_JUMP)
			keys|= Keys::JUMP;
		lpData->keys = keys;

	}

	inline void UpdateCMD(CUserCmd* cmd, LocalPlayer* lpData, vec2 sensitivity, float sampleRate)
	{
		cmd->buttons &= (lpData->keys & Keys::ATTACK1) ? ~0 : ~IN_ATTACK;
		cmd->buttons &= (lpData->keys & Keys::ATTACK2) ? ~0 : ~IN_ATTACK2;
		cmd->buttons &= (lpData->keys & Keys::JUMP) ? ~0 : ~IN_JUMP;

		cmd->buttons |= (lpData->keys & Keys::ATTACK1) ? IN_ATTACK : 0;
		cmd->buttons |= (lpData->keys & Keys::ATTACK2) ? IN_ATTACK2 : 0;
		cmd->buttons |= (lpData->keys & Keys::JUMP) ? IN_JUMP : 0;

		lpData->angles.NormalizeAngles<3>(-180.f, 180.f);
		cmd->viewangles = lpData->angles;
		CorrectMovement(oldAngles, cmd, 0);

		vec2 move(cmd->sidemove, cmd->forwardmove);

		//Normalize cmd move values if necessary
		if (move.Length() > 450) {
			move.Normalize();
			move *= 450;
		}

		cmd->sidemove = move[0];
		cmd->forwardmove = move[1];

		//The mousedx/y values only seem to be of the last mouse sample -- not the exact delta. Thus, we use framecount difference to make it seem more like a reality
	    int frameCountDelta = (globalVars->framecount - prevFramecount);

		if (prevAngles != vec3_t(0) && frameCountDelta > 0) {

			vec3_t angleDelta = (cmd->viewangles - prevAngles).NormalizeAngles<2>(-180.f, 180.f) / Max(1, frameCountDelta);

			cmd->mousedx = -angleDelta[1] / sensitivity[0];
			cmd->mousedy = angleDelta[0] / sensitivity[1];
		}

		prevAngles = cmd->viewangles;
		prevFramecount = globalVars->framecount;
	}
}

#endif
