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
	int prevFlags = 0;
	int nextFlags = 0;

	float curtimeBackup = 0;
	float frametimeBackup = 0;

	inline void Prepare(CUserCmd* cmd, C_BaseEntity* localPlayer, void* hostRunFrameFp)
	{
		if (localPlayer->m_lifeState() == LIFE_ALIVE) {
			if (*(long*)((uintptr_t*)hostRunFrameFp - RUNFRAME_TICK) > 0) {
				clientState->m_nDeltaTick--;
				CL_RunPrediction();
				clientState->m_nDeltaTick++;
			}

			cmd->random_seed = MD5::PseudoRandom(cmd->command_number) & 0x7FFFFFFF;

			prevFlags = localPlayer->m_fFlags();

			curtimeBackup = globalVars->curtime;
			frametimeBackup = globalVars->frametime;
		}
	}

	/*
	  Temporary engine prediction.
	  TODO: Rebuild the functions or find a better way of executing it.
	  Shoot height bugs out on CSGO Linux when crouched.
	*/
	inline void Run(CUserCmd* cmd, C_BaseEntity* localPlayer)
	{
		if (localPlayer->m_lifeState() == LIFE_ALIVE) {
			int tickbaseBackup = localPlayer->m_nTickBase();

			CUserCmd* tCmd = new CUserCmd(*cmd);

			//This is a hack
			C_BaseCombatWeapon* activeWeapon = localPlayer->m_hActiveWeapon();
			localPlayer->m_hActiveWeapon() = nullptr;

			RunSimulation(prediction, globalVars->curtime, cmd->command_number - 1, tCmd, localPlayer);
			localPlayer->m_hActiveWeapon() = activeWeapon;

			globalVars->curtime = localPlayer->m_nTickBase() * globalVars->interval_per_tick;
			globalVars->frametime = globalVars->interval_per_tick;

			nextFlags = localPlayer->m_fFlags();

			localPlayer->m_fFlags() = prevFlags;
			localPlayer->m_nTickBase() = tickbaseBackup;

			delete tCmd;
		}
	}

	inline void Finish(CUserCmd* cmd, C_BaseEntity* localPlayer)
	{
		RunSimulation(prediction, globalVars->curtime, cmd->command_number - 1, cmd, localPlayer);
		if (localPlayer->m_lifeState() == LIFE_ALIVE) {
			globalVars->curtime = curtimeBackup;
			globalVars->frametime = frametimeBackup;
		}
	}
}

#endif
