#ifndef ICLIENTENTITYLIST_H
#define ICLIENTENTITYLIST_H

class IClientNetworkable;
class IClientEntity;

class IClientEntityList
{
  public:
	virtual IClientNetworkable* GetClientNetworkable(int entnum) = 0;
	virtual IClientNetworkable* GetClientNetworkableFromHandle(CBaseHandle handle) = 0;
	virtual void* GetClientUnknownFromHandle(CBaseHandle handle) = 0;
	virtual IClientEntity* GetClientEntity(int entNum) = 0;
	virtual IClientEntity* GetClientEntityFromHandle(CBaseHandle hEnt) = 0;
	virtual int NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int GetHighestEntityIndex(void) = 0;
	virtual void SetMaxEntities(int maxEnts) = 0;
	virtual int GetMaxEntities() = 0;
};

#endif
