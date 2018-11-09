#ifndef ESSENTIALS_H
#define ESSENTIALS_H

#include "../framework/players.h"

struct CUserCmd;

namespace SourceEssentials
{
#ifdef SOURCE_DEFINITIONS
	vec3_t oldAngles;
#else
	extern vec3_t oldAngles;
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

	inline void UpdateCMD(CUserCmd* cmd, LocalPlayer* lpData)
	{
		cmd->buttons &= (lpData->keys & Keys::ATTACK1) ? ~0 : ~IN_ATTACK;
		cmd->buttons &= (lpData->keys & Keys::ATTACK2) ? ~0 : ~IN_ATTACK2;
		cmd->buttons &= (lpData->keys & Keys::JUMP) ? ~0 : ~IN_JUMP;

		lpData->angles.NormalizeAngles<3>(-180.f, 180.f);
		cmd->viewangles = lpData->angles;
		CorrectMovement(oldAngles, cmd, 0);
	}
}

#endif
