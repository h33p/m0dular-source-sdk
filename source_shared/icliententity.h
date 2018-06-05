#ifndef ICLIENTENTITY_H
#define ICLIENTENTITY_H

#include "iclientthinkable.h"
#include "iclientunknown.h"
#include "iclientrenderable.h"
#include "iclientnetworkable.h"
#include "netvars.h"
#include "../framework/utils/crc32.h"

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
  public:
	virtual void Release(void) = 0;
};

#endif
