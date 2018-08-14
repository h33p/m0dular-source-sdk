#ifndef ICLIENTTHINKABLE_H
#define ICLIENTTHINKABLE_H

class IClientUnknown;
class CClientThinkHandlePtr;
class IClientNetworkable;
typedef CClientThinkHandlePtr* ClientThinkHandle_t;

#include "iclientnetworkable.h"

class IClientThinkable
{
  public:
	virtual IClientUnknown* GetIClientUnknown() {};
	virtual void ClientThink() {};
	virtual ClientThinkHandle_t GetThinkHandle() {};
	virtual void SetThinkHandle(ClientThinkHandle_t hThink) {};
	virtual void Release() {};
};

#endif
