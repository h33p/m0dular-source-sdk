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

constexpr int ANGLE_STEP = 10;
constexpr int SCHED_COUNT = 5;
constexpr int ANGLE_COUNT = 360 / ANGLE_STEP;

constexpr int BRUTEFORCE_SHOTS = 10;
constexpr int BRUTEFORCE_STEP = ANGLE_STEP * 3;

class RandomResolver
{
  public:
	void PreRun();
	float ResolvePlayer(int id);
	void ProcessHit(int id, float angle);
	void ShotFired(int id);
	void UpdateBases(int id, float bases[RESOLVEBASECOUNT]);
	RandomResolver();

  private:
	void Initialize(int id);
	void Requeue(int id, int insertID = -1);

	float baseOffsets[MAX_PLAYERS][RESOLVEBASECOUNT];
	int score[MAX_PLAYERS][RESOLVEBASECOUNT][ANGLE_COUNT];
	int maxScore[MAX_PLAYERS];
	Scheduler<int, SCHED_COUNT> queue[MAX_PLAYERS];
	int lastID[MAX_PLAYERS];
	int prevID[MAX_PLAYERS];
	int shotCount[MAX_PLAYERS];
	int totalShots[MAX_PLAYERS];
	bool init[MAX_PLAYERS];
};

#endif
