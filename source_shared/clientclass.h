#ifndef CLIENTCLASS_H
#define CLIENTCLASS_H

#include "sdk.h"

class ClientClass;
class IClientNetworkable;

typedef IClientNetworkable* (*CreateClientClassFn)(int entnum, int serialNum);
typedef IClientNetworkable* (*CreateEventFn)();

class ClientClass
{
  public:
	CreateClientClassFn createFn;
	CreateEventFn createEventFn;
	char* networkName;
	RecvTable* recvTable;
	ClientClass* next;
	ClassId classID;
};

#endif
