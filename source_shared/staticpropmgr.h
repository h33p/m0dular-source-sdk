#ifndef STATICPROPMGR_H
#define STATICPROPMGR_H

#include "basehandle.h"

class IStaticPropMgr
{
  public:
	virtual void Unk0() = 0;
	virtual void Unk1() = 0;
	virtual bool IsStaticProp(IHandleEntity*) = 0;
	virtual bool IsStaticProp(CBaseHandle) = 0;
	virtual void Unk5() = 0;
	virtual void Unk6() = 0;
	virtual void Unk7() = 0;
	virtual void Unk8() = 0;
	virtual C_BaseEntity* GetStaticProp(IHandleEntity*) = 0;
};

class CStaticPropMgr
{
  public:
	virtual void Unk0() = 0;
	virtual void Unk1() = 0;
	virtual void Unk2() = 0;
	virtual void Unk3() = 0;
	virtual void Unk4() = 0;
	virtual void Unk5() = 0;
	virtual void Unk6() = 0;
	virtual void Unk7() = 0;
	virtual void Unk8() = 0;
	virtual C_BaseEntity* GetStaticProp(IHandleEntity*) = 0;
};

#endif
