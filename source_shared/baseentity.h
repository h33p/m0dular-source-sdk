#ifndef BASEPLAYER_H
#define BASEPLAYER_H

struct CCollisionProp;

class C_BaseEntity : public IClientEntity
{
  public:
	bool IsPlayer();
	bool IsWeapon();
	bool IsPlantedC4();
	bool IsDefuseKit();

	NETVAR(float, m_flSimulationTime, "DT_BaseEntity", "m_flSimulationTime");
	NETVAR(int, m_fFlags, "DT_BaseEntity", "m_fFlags");
	NETVAR(bool, m_bHasDefuser, "DT_CSPlayer", "m_bHasDefuser");
	NETVAR(bool, m_bGunGameImmunity, "DT_CSPlayer", "m_bGunGameImmunity");
	NETVAR(int, m_iShotsFired, "DT_CSPlayer", "m_iShotsFired");
	NETVAR(vec3, m_angEyeAngles, "DT_CSPlayer", "m_angEyeAngles[0]");
	NETVAR(int, m_ArmorValue, "DT_CSPlayer", "m_ArmorValue");
	NETVAR(bool, m_bHasHelmet, "DT_CSPlayer", "m_bHasHelmet");
	NETVAR(bool, m_bHasHeavyArmor, "DT_CSPlayer", "m_bHasHeavyArmor");
	NETVAR(bool, m_bIsScoped, "DT_CSPlayer", "m_bIsScoped");
	NETVAR(float, m_flLowerBodyYawTarget, "DT_CSPlayer", "m_flLowerBodyYawTarget");
	NETVAR(int, m_iHealth, "DT_BasePlayer", "m_iHealth");
	NETVAR(int, m_lifeState, "DT_BasePlayer", "m_lifeState");
	NETVAR(int, m_nTickBase, "DT_BasePlayer", "m_nTickBase");
	NETVAR(vec3, m_aimPunchAngle, "DT_BasePlayer", "m_aimPunchAngle");
	NETVAR(vec3, m_aimPunchAngleVel, "DT_BasePlayer", "m_aimPunchAngleVel");
	NETVAR(vec3, m_vecVelocity, "DT_BasePlayer", "m_vecVelocity[0]");
	NETVAR(vec3, m_vecOrigin, "DT_BaseEntity", "m_vecOrigin");
	NETVAR(float, m_flMaxspeed, "DT_BasePlayer", "m_flMaxspeed");
	NETVAR(float, m_flFlashMaxAlpha, "DT_CSPlayer", "m_flFlashMaxAlpha");
	NETVAR(int, m_collisionGroup, "DT_BaseEntity", "m_CollisionGroup");
	NETVAR(CCollisionProp*, m_Collision, "DT_BaseEntity", "m_Collision");
};

struct CCollisionProp
{
	NETVAR(vec3, m_vecMins, "DT_CollisionProperty", "m_vecMins");
	NETVAR(vec3, m_vecMaxs, "DT_CollisionProperty", "m_vecMaxs");
};

#endif
