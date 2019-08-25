#ifndef SERVERCLASS_H
#define SERVERCLASS_H

#include "sdk.h"

class ServerClass
{
  public:
	char* networkName;
	SendTable* sendTable;
	ServerClass* next;
	ClassId classID;
};

#endif
