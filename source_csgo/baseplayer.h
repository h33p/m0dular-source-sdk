#ifndef BASEPLAYER_H
#define BASEPLAYER_H

class C_BaseEntity;
struct AnimationLayer;
struct CCSGOPlayerAnimState;

class C_BasePlayer : public C_BaseEntity
{
  public:
	OFFSET(CUtlVector<matrix3x4_t>, boneMatrix, BONE_MATRIX);
	ONETVAR(AnimationLayer*, animationLayers, "DT_CSRagdoll", "m_vecRagdollVelocity", -x64x32(0x8c, 0x80));
	ONETVAR(CCSGOPlayerAnimState*, animState, "DT_CSPlayer", "m_bIsWalking", -x64x32(0xf, 0xb));

	VFuncPosixWin(void, UpdateClientSideAnimation, 280, 218);

	inline void InvalidateBoneCache()
	{
		*(uintptr_t*)((uintptr_t)this + x64x32(0x2C48, 0x2680)) = 0;
	}
};

struct AnimationLayer
{
	char pad_0000[x64x32(24, 20)];
	int order;
	int sequence;
	float_t prevCycle;
	float_t weight;
	float_t weightDeltaRate;
	float_t playbackRate;
	float_t cycle;
	void* owner;
	void* unk1;
	void* unk2;
};

struct CCSGOPlayerAnimState
{
	PAD6432(0x68, 0x60);
	C_BasePlayer* player;
	C_BaseCombatWeapon* activeWeapon;
	C_BaseCombatWeapon* lastActiveWeapon;
	float updateTime;
	int frameCount;
	float eyePitch;
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
	PAD6432(0x2AC, 0x244);
};

constexpr uintptr_t ANIMSTATE_SIZE = x64x32(0x3B8, 0x33C);

#endif
