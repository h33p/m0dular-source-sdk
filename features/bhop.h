#ifndef SOURCE_BHOP_H
#define SOURCE_BHOP_H

#include "../framework/players.h"

struct CUserCmd;

namespace SourceBhop
{
	static bool jumpedLastTick = false;
	inline void Run(CUserCmd* cmd, LocalPlayer* lpData)
	{
#ifdef SOURCE_ENGINEPREDICTION_H
		bool onGround = SourceEnginePred::prevFlags & FL_ONGROUND;
#else
		bool onGround = lpData->flags & Flags::ONGROUND;
#endif
		if (lpData->keys & Keys::JUMP) {
			if (!onGround || jumpedLastTick) {
				lpData->keys &= ~Keys::JUMP;
				jumpedLastTick = false;
			} else
				jumpedLastTick = true;
		} else
			jumpedLastTick = false;
	}
}

#endif
