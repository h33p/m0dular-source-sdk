#ifndef SERVERGAME_H
#define SERVERGAME_H

#include "sdk.h"

class CServerGame
{
  public:
	virtual int DLLInit(const char*, CGlobalVarsBase *pGlobals) = 0;
	virtual int GameInit(void) = 0;
	virtual void LevelInit(const char*, const char*, const char*, const char*, bool, bool) = 0;
	virtual void ServerActivate(void*, int, int) = 0;
	virtual void GameFrame(bool) = 0;
	virtual void PreClientUpdate(bool) = 0;
	virtual void LevelShutdown(void) = 0;
	virtual void GameShutdown(void) = 0;
	virtual void DLLShutdown(void) = 0;
	virtual float GetTickInterbal(void) = 0;
	virtual ServerClass* GetAllServerClasses(void) = 0;
};

#endif
