#ifndef IHANDLEENTITY_H
#define IHANDLEENTITY_H

class CBaseHandle;

class IHandleEntity
{
  public:
	virtual ~IHandleEntity() {}
	virtual void SetRefEHandle(const CBaseHandle &handle) {};
	virtual const CBaseHandle& GetRefEHandle() const {};
};

#endif
