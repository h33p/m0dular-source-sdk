#ifndef ESSENTIALS_H
#define ESSENTIALS_H

#include "../framework/players.h"

struct CUserCmd;

namespace SourceEssentials
{

	/*
	  These functions only deal with data provided by the CMD.
	  Other data needs to be filled in manually.
	*/
	inline void UpdateData(CUserCmd* cmd, LocalPlayer* lpData)
	{

		lpData->angles = cmd->viewangles;

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

		cmd->viewangles = lpData->angles;
	}
}

#endif
