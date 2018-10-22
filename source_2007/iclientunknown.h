#ifndef ICLIENTUNKNOWN_H
#define ICLIENTUNKNOWN_H

#include "ihandleentity.h"
#include "icollideable.h"

class IClientNetworkable;
class IClientRenderable;
class IClientEntity;
class C_BaseEntity;
class IClientThinkable;
class IClientAlphaProperty;

class IClientUnknown : public IHandleEntity
{
  public:
	virtual ICollideable* GetCollideable() = 0;
	virtual IClientNetworkable* GetClientNetworkable() = 0;
	virtual IClientRenderable* GetClientRenderable() = 0;
	virtual IClientEntity* GetIClientEntity() = 0;
	virtual C_BaseEntity* GetBaseEntity() = 0;
	virtual IClientThinkable* GetClientThinkable() = 0;
	virtual void Release(void) = 0;
};

#endif
