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
constexpr int MAX_TICKS = 12;

namespace SourceFakelag
{
	static bool changeAllowed = false;
	static vec3_t prevOrigin;
	static int chokedTicks = 0;
	static int realChokedTicks = 0;

#ifdef SOURCE_DEFINITIONS
	int falseChange = false;
	FakelagState state = FakelagState::REAL;
#else
	extern int falseChange;
	extern FakelagState state;
#endif

	inline FakelagState Run(CUserCmd* cmd, LocalPlayer* lpData, bool* bSendPacket, bool allowChange)
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

		if (!realChokedTicks)
			state = FakelagState::REAL;

		if (canChange && (chokedTicks >= 1 || realChokedTicks >= MAX_TICKS)) {
			*bSendPacket = true;
			prevOrigin = lpData->origin;
			if (realChokedTicks)
				state = FakelagState::FAKE;
			chokedTicks = 0;
			realChokedTicks = 0;
			changeAllowed = false;
		} else {
			*bSendPacket = false;
			if (realChokedTicks)
				state = FakelagState::INTERMEDIATE;
			chokedTicks++;
			realChokedTicks++;
		}

		if (falseChange)
			falseChange--;

		return state;
	}
}

#endif
