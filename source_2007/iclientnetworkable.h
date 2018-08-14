#ifndef ICLIENTNETWORKABLE_H
#define ICLIENTNETWORKABLE_H

class IClientUnknown;
class IClientRenderable;
class ClientClass;
class bf_read;

#include "iclientrenderable.h"

class IClientNetworkable
{
  public:
	virtual IClientUnknown* GetIClientUnknown() {};
	virtual void Release() {};
	virtual ClientClass* GetClientClass() {};
	virtual void NotifyShouldTransmit(int state) {};
	virtual void OnPreDataChanged(int updateType) {};
	virtual void OnDataChanged(int updateType) {};
	virtual void PreDataUpdate(int updateType) {};
	virtual void PostDataUpdate(int updateType) {};
	virtual bool IsDormant(void) {};
	virtual int EntIndex(void) const {};
	virtual void ReceiveMessage(int classID, bf_read& msg) {};
	virtual void* GetDataTableBasePtr() {};
	virtual void SetDestroyedOnRecreateEntities(void) {};
};

#endif
