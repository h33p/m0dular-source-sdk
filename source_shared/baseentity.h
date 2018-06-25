#ifndef BASEENTITY_H
#define BASEENTITY_H

struct CCollisionProp;
class C_BaseCombatWeapon;

class C_BaseEntity : public IClientEntity
{
  public:
	bool IsPlayer();
	bool IsWeapon();
	bool IsPlantedC4();
	bool IsDefuseKit();

	OFFSET(VarMapping_t, m_varMapping, x64x32(0x48, 0x24));
	NETVAR(float, m_flSimulationTime, "DT_BaseEntity", "m_flSimulationTime");
	ONETVAR(float, m_flPrevSimulationTime, "DT_BaseEntity", "m_flSimulationTime", 4);
	NETVAR(int, m_fFlags, "DT_BasePlayer", "m_fFlags");
	NETVAR(bool, m_bHasDefuser, "DT_CSPlayer", "m_bHasDefuser");
	NETVAR(bool, m_bGunGameImmunity, "DT_CSPlayer", "m_bGunGameImmunity");
	NETVAR(int, m_iShotsFired, "DT_CSPlayer", "m_iShotsFired");
	NETVAR(vec3, m_angEyeAngles, "DT_CSPlayer", "m_angEyeAngles[0]");
	NETVAR(vec3, m_vecAngles, "DT_BaseEntity", "m_angRotation");
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
	NETVAR(int, m_iTeamNum, "DT_BaseEntity", "m_iTeamNum");
	NETVAR(float, m_flMaxspeed, "DT_BasePlayer", "m_flMaxspeed");
	NETVAR(float, m_flFlashMaxAlpha, "DT_CSPlayer", "m_flFlashMaxAlpha");
	NETVAR(int, m_collisionGroup, "DT_BaseEntity", "m_CollisionGroup");
	NETVAR(CCollisionProp*, m_Collision, "DT_BaseEntity", "m_Collision");

	NETVAR(bool, m_bClientSideAnimation, "DT_BaseAnimating", "m_bClientSideAnimation");
	NETVAR(float*, m_flPoseParameter, "DT_BaseAnimating", "m_flPoseParameter");

	NETVAR(CHandle<C_BaseEntity>, m_hObserverTarget, "DT_BasePlayer", "m_hObserverTarget");
	NETVAR(CHandle<C_BaseCombatWeapon>, m_hActiveWeapon, "DT_BaseCombatCharacter", "m_hActiveWeapon");
};

struct CCollisionProp
{
	NETVAR(vec3, m_vecMins, "DT_CollisionProperty", "m_vecMins");
	NETVAR(vec3, m_vecMaxs, "DT_CollisionProperty", "m_vecMaxs");
};

#endif
