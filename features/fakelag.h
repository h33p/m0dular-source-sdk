#ifndef SOURCE_FAKELAG_H
#define SOURCE_FAKELAG_H

#include "engineprediction.h"
#include "types.h"

struct CUserCmd;
struct LocalPlayer;

#ifndef LC_DIMENSIONS
constexpr int LC_DIMENSIONS = 2;
#endif

constexpr float LC_DISTANCE = 4096;
constexpr bool BREAK_LC = true;
constexpr int MAX_TICKS = 10;

namespace SourceFakelag
{
	static bool changeAllowed = false;
	static vec3_t prevOrigin;
	static int chokedTicks = 0;
	static int realChokedTicks = 0;

#ifdef SOURCE_DEFINITIONS
	int falseChange = false;
	FakelagState_t state = FakelagState::FIRST | FakelagState::LAST;
	int prevChokeCount = 0;
	int ticksToChoke = 5;
#else
	extern int falseChange;
	extern FakelagState_t state;
	extern int prevChokeCount;
	extern int ticksToChoke;
#endif

	inline FakelagState_t Run(CUserCmd* cmd, LocalPlayer* lpData, bool* bSendPacket, bool allowChange)
	{
		if (allowChange)
			changeAllowed = true;

		bool canChange = changeAllowed;

		//Break lag compensation
		if (~lpData->flags & Flags::ONGROUND && BREAK_LC && (lpData->origin - prevOrigin).LengthSqr<LC_DIMENSIONS>() < LC_DISTANCE)
			chokedTicks = -1;

		//Prevent hitting ground with the real angle
		if (falseChange || (SourceEnginePred::nextFlags & FL_ONGROUND && ~SourceEnginePred::prevFlags & FL_ONGROUND)) {
			if (!falseChange)
				falseChange = (SourceEnginePred::duckAmount != 0.f) ? 3 : 2;
			if (falseChange)
				canChange = false;
		}

		state = FakelagState::NONE;

		if (!realChokedTicks)
			state |= FakelagState::FIRST;

		if (canChange && (chokedTicks >= ticksToChoke || realChokedTicks >= MAX_TICKS)) {
			*bSendPacket = true;
			prevOrigin = lpData->origin;
			state |= FakelagState::LAST;
			prevChokeCount = realChokedTicks;
			chokedTicks = 0;
			realChokedTicks = 0;
			changeAllowed = false;
		} else {
			*bSendPacket = false;
			chokedTicks++;
			realChokedTicks++;
		}

		if (falseChange)
			falseChange--;

		return state;
	}
}

#endif
