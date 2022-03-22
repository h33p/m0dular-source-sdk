#ifndef SOURCE_NO_ENGINEPREDICTION
#ifndef SOURCE_ENGINEPREDICTION_H
#define SOURCE_ENGINEPREDICTION_H

#include "../framework/utils/md5.h"

struct CUserCmd;
class C_BaseEntity;
class CPrediciton;

/*
  Correct RUNFRAME_TICK constant has to be set before including,
  CL_RunPrediction has to exist alongside clientState, globalVars and prediction
*/

extern CClientState* clientState;
extern CGlobalVarsBase* globalVars;
void RunSimulation(CPrediction* prediction, float curtime, int command_number, CUserCmd* tCmd, C_BaseEntity* localPlayer);

namespace SourceEnginePred
{
#ifdef SOURCE_DEFINITIONS
	int prevFlags = 0;
	int nextFlags = 0;
	float curtimeBackup = 0;
	float frametimeBackup = 0;
	float duckAmount = 0;
#else
	extern int prevFlags;
	extern int nextFlags;
	extern float curtimeBackup;
	extern float frametimeBackup;
	extern float duckAmount;
#endif

	static bool simulated = false;

	inline void Prepare(CUserCmd* cmd, C_BaseEntity* localPlayer, void* hostRunFrameFp)
	{
		if (localPlayer->lifeState() == LIFE_ALIVE) {
			if (*(long*)((uintptr_t*)hostRunFrameFp - RUNFRAME_TICK) > 0) {
				clientState->deltaTick--;
				CL_RunPrediction();
				clientState->deltaTick++;
			}

			cmd->random_seed = MD5::PseudoRandom(cmd->command_number) & 0x7FFFFFFF;

			prevFlags = localPlayer->flags();

			curtimeBackup = globalVars->curtime;
			frametimeBackup = globalVars->frametime;
		}
	}

	/*
	  Temporary engine prediction.
	  TODO: Rebuild the functions or find a better way of executing it.
	  Shoot height bugs out on CSGO Linux when crouched. NOTE: This is probably not due to this prediction code.
	*/
	inline void Run(CUserCmd* cmd, C_BaseEntity* localPlayer)
	{
		if (localPlayer->lifeState() == LIFE_ALIVE) {
			int tickbaseBackup = localPlayer->tickBase();

			CUserCmd tCmd = *cmd;

			//This is a hack
			C_BaseCombatWeapon* activeWeapon = localPlayer->activeWeapon();
			if (simulated)
				localPlayer->activeWeapon() = nullptr;

			RunSimulation(prediction, globalVars->curtime, cmd->command_number - 1, &tCmd, localPlayer);
			localPlayer->activeWeapon() = activeWeapon;

			simulated = true;

			globalVars->curtime = localPlayer->tickBase() * globalVars->interval_per_tick;
			globalVars->frametime = globalVars->interval_per_tick;

			nextFlags = localPlayer->flags();

			localPlayer->flags() = prevFlags;
			localPlayer->tickBase() = tickbaseBackup;

			duckAmount = localPlayer->duckAmount();
		}
	}

	inline void Finish(CUserCmd* cmd, C_BaseEntity* localPlayer)
	{
		CL_RunPrediction();
		if (localPlayer->lifeState() == LIFE_ALIVE) {
			globalVars->curtime = curtimeBackup;
			globalVars->frametime = frametimeBackup;
		}
	}
}

#endif
#endif
