#ifndef MISCENTS_H
#define MISCENTS_H

class C_FogController : public C_BaseEntity
{
  public:
	NETVAR(bool, fogEnable, "DT_FogController", "m_fog.enable");
};

#endif
