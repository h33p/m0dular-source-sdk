#ifndef ICLIENTENTITY_H
#define ICLIENTENTITY_H

#include "iclientthinkable.h"
#include "iclientunknown.h"
#include "iclientrenderable.h"
#include "iclientnetworkable.h"
#include "ibaseentity.h"

class IClientEntity : public IBaseEntity, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
};

#endif
