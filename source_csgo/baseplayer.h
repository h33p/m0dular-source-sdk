#ifndef BASEPLAYER_H
#define BASEPLAYER_H

class C_BaseEntity;
struct AnimationLayer;
struct CCSGOPlayerAnimState;

class C_BasePlayer : public C_CSPlayer
{
  public:
	OFFSET(VarMapping_t, varMapping, x64x32(0x48, 0x24));
	ONETVAR(AnimationLayer*, animationLayers, "DT_CSRagdoll", "m_vecRagdollVelocity", -x64x32(0x8c, 0x80));
	ONETVAR(CCSGOPlayerAnimState*, animState, "DT_CSPlayer", "m_bIsScoped", -x64x32(0x14, 0x10));
	ONETVAR(vec3, localAngles, "DT_BasePlayer", "deadflag", 0x4);
	ONETVAR(int, lastBoneFrameCount, "DT_BaseAnimating", "m_nMuzzleFlashParity", 0x4);
	ONETVAR(int, prevBoneMask, "DT_BaseAnimating", "m_nForceBone", x64x32(0x14, 0xc));
	ONETVAR(int, accumulatedBoneMask, "DT_BaseAnimating", "m_nForceBone", x64x32(0x10, 0x10));
	ONETVAR(CUtlVector<matrix3x4_t>, boneMatrix, "DT_BaseAnimating", "m_bClientSideFrameReset", -x64x32(0x1c, 0x18));
	ONETVAR(int, lastBoneTime, "DT_BaseAnimating", "m_hLightingOrigin", -x64x32(0x38, 0x24));
	NETVAR(int, survivalTeamNum, "DT_CSPlayer", "m_nSurvivalTeam");
	ONETVAR(long, mostRecentBoneCounter, "DT_BaseAnimating", "m_nForceBone", 4);
	ONETVAR(int, occlusionFlags2, "DT_BaseAnimating", "m_nBody", 4);
	ONETVAR(int, occlusionFlags, "DT_BaseAnimating", "m_nBody", 8);
	ONETVAR(int, lastOcclusionCheck, "DT_BaseAnimating", "m_nBody", 16);
	ONETVAR(uint8_t, takeDamage, "DT_BaseEntity", "m_nModelIndex", 0x28);

	VFuncPosixWin(void, UpdateClientSideAnimation, 285, 223);

	inline void InvalidateBoneCache()
	{
		*(uintptr_t*)((uintptr_t)this + x64x32(0x2C48, 0x2680)) = 0;
	}
};

struct AnimationLayer
{
	PAD6432(24, 20);
	int order;
	int sequence;
	float_t prevCycle;
	float_t weight;
	float_t weightDeltaRate;
	float_t playbackRate;
	float_t cycle;
	void* owner;
	void* unk1;
};

struct CCSGOPlayerAnimState
{
	PAD6432(0x68, 0x60);
	C_BasePlayer* player;
	C_BaseCombatWeapon* activeWeapon;
	C_BaseCombatWeapon* lastActiveWeapon;
	float updateTime;
	int frameCount;
	float interval;
	float eyeYaw;
	float pitch;
	float goalFeetYaw;
	float currentFeetYaw;
	float currentTorsoYaw;
	PAD(0x24);
	vec3 origin;
	vec3 prevOrigin;
	vec3 vecVelocity;
	PAD(0x18);
	vec3 scaledVelocity;
	PAD(0x2C);
	float groundedFraction;
	PAD6432(0x27C, 0x21c);
};

constexpr uintptr_t ANIMSTATE_SIZE = x64x32(0x3B8, 0x344);
static_assert(sizeof(CCSGOPlayerAnimState) == ANIMSTATE_SIZE);

#endif
