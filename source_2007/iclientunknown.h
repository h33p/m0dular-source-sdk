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
	virtual ICollideable* GetCollideable() {};
	virtual IClientNetworkable* GetClientNetworkable() {};
	virtual IClientRenderable* GetClientRenderable() {};
	virtual IClientEntity* GetIClientEntity() {};
	virtual C_BaseEntity* GetBaseEntity() {};
	virtual IClientThinkable* GetClientThinkable() {};
	virtual void Release(void) {};
};

#endif
