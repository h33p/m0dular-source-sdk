#ifndef SOURCE_SHARED_HOOKS_H
#define SOURCE_SHARED_HOOKS_H

#include "../framework/g_defines.h"
#include "sdk.h"

namespace SourceHooks
{
	bool __fastcall CreateMove(FASTARGS, float, CUserCmd*);
}

#endif
