#ifndef SOURCE_BHOP_H
#define SOURCE_BHOP_H

#include "../framework/players.h"

struct CUserCmd;

namespace SourceBhop
{
	static bool jumpedLastTick = false;
	inline void Run(CUserCmd* cmd, LocalPlayer* lpData)
	{
		if (lpData->keys & Keys::JUMP) {
			if (~lpData->flags & Flags::ONGROUND || jumpedLastTick) {
				lpData->keys &= ~Keys::JUMP;
				jumpedLastTick = false;
			} else
				jumpedLastTick = true;
		}
	}
}

#endif
