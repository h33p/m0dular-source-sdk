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

	OFFSET(VarMapping_t, varMapping, x64x32(0x48, 0x24));
	NETVAR(float, simulationTime, "DT_BaseEntity", "m_flSimulationTime");
	ONETVAR(float, prevSimulationTime, "DT_BaseEntity", "m_flSimulationTime", 4);
	NETVAR(int, flags, "DT_BasePlayer", "m_fFlags");
	NETVAR(bool, hasDefuser, "DT_CSPlayer", "m_bHasDefuser");
	NETVAR(bool, gunGameImmunity, "DT_CSPlayer", "m_bGunGameImmunity");
	NETVAR(int, shotsFired, "DT_CSPlayer", "m_iShotsFired");
	NETVAR(vec3, eyeAngles, "DT_CSPlayer", "m_angEyeAngles[0]");
	NETVAR(vec3, angles, "DT_BaseEntity", "m_angRotation");
	NETVAR(int, armorValue, "DT_CSPlayer", "m_ArmorValue");
	NETVAR(bool, hasHelmet, "DT_CSPlayer", "m_bHasHelmet");
	NETVAR(bool, hasHeavyArmor, "DT_CSPlayer", "m_bHasHeavyArmor");
	NETVAR(bool, isScoped, "DT_CSPlayer", "m_bIsScoped");
	NETVAR(float, lowerBodyYawTarget, "DT_CSPlayer", "m_flLowerBodyYawTarget");
	NETVAR(int, health, "DT_BasePlayer", "m_iHealth");
	NETVAR(int, lifeState, "DT_BasePlayer", "m_lifeState");
	NETVAR(int, tickBase, "DT_BasePlayer", "m_nTickBase");
	NETVAR(vec3, aimPunchAngle, "DT_BasePlayer", "m_aimPunchAngle");
	NETVAR(vec3, aimPunchAngleVel, "DT_BasePlayer", "m_aimPunchAngleVel");
	NETVAR(vec3, velocity, "DT_BasePlayer", "m_vecVelocity[0]");
	NETVAR(vec3, origin, "DT_BaseEntity", "m_vecOrigin");
	NETVAR(int, teamNum, "DT_BaseEntity", "m_iTeamNum");
	NETVAR(float, maxspeed, "DT_BasePlayer", "m_flMaxspeed");
	NETVAR(float, flashMaxAlpha, "DT_CSPlayer", "m_flFlashMaxAlpha");
	NETVAR(int, collisionGroup, "DT_BaseEntity", "m_CollisionGroup");
	NETVAR(vec3, mins, "DT_BaseEntity", "m_vecMins");
	NETVAR(vec3, maxs, "DT_BaseEntity", "m_vecMaxs");
	NETVAR(float, duckAmount, "DT_BasePlayer", "m_flDuckAmount");

	NETVAR(bool, clientSideAnimation, "DT_BaseAnimating", "m_bClientSideAnimation");
	ONETVAR(float, poseParameter, "DT_BaseAnimating", "m_ScaleType", x64x32(0x34, 0x28));

	NETVAR(CHandle<C_BaseEntity>, observerTarget, "DT_BasePlayer", "m_hObserverTarget");
	NETVAR(CHandle<C_BaseCombatWeapon>, activeWeapon, "DT_BaseCombatCharacter", "m_hActiveWeapon");
};

#endif
