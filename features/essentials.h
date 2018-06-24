#ifndef ESSENTIALS_H
#define ESSENTIALS_H

#include "../framework/players.h"

struct CUserCmd;

#define _SOLVEY(a, b, c, d, e, f) ((c * b - d * a) / (c * f - d * e))
#define SOLVEY(world, forward, right) _SOLVEY(world.x, world.y, forward.x, forward.y, right.x, right.y)
#define SOLVEX(y, world, forward, right) ((world.x - right.x * y) / forward.x)

namespace SourceEssentials
{

	vec3_t oldAngles;

	inline void CorrectMovement(vec3_t& oldAngles, CUserCmd* cmd, int movetype)
	{
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

		cmd->sidemove = SOLVEY(worldCoords, frC, riC);
		cmd->forwardmove = SOLVEX(cmd->sidemove, worldCoords, frC, riC);

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
