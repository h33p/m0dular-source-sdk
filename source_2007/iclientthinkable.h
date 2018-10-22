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
	virtual IClientUnknown* GetIClientUnknown() = 0;
	virtual void ClientThink() = 0;
	virtual ClientThinkHandle_t GetThinkHandle() = 0;
	virtual void SetThinkHandle(ClientThinkHandle_t hThink) = 0;
	virtual void Release() = 0;
};

#endif
