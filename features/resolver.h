#ifndef RANDOMRESOLVER_H
#define RANDOMRESOLVER_H

#include "../framework/utils/scheduler.h"

/*
 * This is a random caching fake angle resolver.
 * It does not incorporate any game specific logic,
 * picks angles by random or bruteforcing with a predefined angle step.
 * Hits are cached and the most successful angles are used first.
 * RESOLVEBASECOUNT has to be defined by the compiler.
*/

#ifndef RESOLVE_ANGLE_STEP
constexpr int RESOLVE_ANGLE_STEP = 10;
#endif
#ifndef RESOLVE_SCHED_COUNT
constexpr int RESOLVE_SCHED_COUNT = 5;
#endif
constexpr int RESOLVE_ANGLE_COUNT = 360 / RESOLVE_ANGLE_STEP;

#ifndef RESOLVE_BRUTEFORCE_SHOTS
constexpr int RESOLVE_BRUTEFORCE_SHOTS = 10;
#endif
#ifndef RESOLVE_BRUTEFORCE_STEP
constexpr int RESOLVE_BRUTEFORCE_STEP = RESOLVE_ANGLE_STEP * 3;
#endif

class RandomResolver
{
  public:
	void PreRun();
	float ResolvePlayer(int id);
	void ProcessHit(int id, float angle);
	void ShotFired(int id);
	void UpdateBases(int id, float bases[RESOLVEBASECOUNT]);
	void UpdateOffsets(float offsets[RESOLVEBASECOUNT][2]);
	RandomResolver();

  private:
	void Initialize(int id);
	void Requeue(int id, int insertID = -1);

	float baseOffsets[MAX_PLAYERS][RESOLVEBASECOUNT];
	float offsetRanges[RESOLVEBASECOUNT][2];
	int score[MAX_PLAYERS][RESOLVEBASECOUNT][RESOLVE_ANGLE_COUNT];
	int maxScore[MAX_PLAYERS];
	Scheduler<int, RESOLVE_SCHED_COUNT> queue[MAX_PLAYERS];
	int lastID[MAX_PLAYERS];
	int prevID[MAX_PLAYERS];
	int shotCount[MAX_PLAYERS];
	int totalShots[MAX_PLAYERS];
	bool init[MAX_PLAYERS];
};

#endif
