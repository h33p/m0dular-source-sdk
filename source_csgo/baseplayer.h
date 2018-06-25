#ifndef BASEPLAYER_H
#define BASEPLAYER_H

class C_BaseEntity;
struct AnimationLayer;
struct CCSGOPlayerAnimState;

class C_BasePlayer : public C_BaseEntity
{
  public:
	OFFSET(CUtlVector<matrix3x4_t>, m_nBoneMatrix, BONE_MATRIX);
	ONETVAR(AnimationLayer*, m_pAnimationLayers, "DT_CSRagdoll", "m_vecRagdollVelocity", -x64x32(0x8c, 0x80));
	ONETVAR(CCSGOPlayerAnimState*, m_pAnimState, "DT_CSPlayer", "m_bIsWalking", -x64x32(0xf, 0xb));

	VFuncPosixWin(void, UpdateClientSideAnimation, 280, 218);
};

struct AnimationLayer
{
	char pad_0000[x64x32(24, 20)];
	int m_nOrder;
	int m_nSequence;
	float_t m_flPrevCycle;
	float_t m_flWeight;
	float_t m_flWeightDeltaRate;
	float_t m_flPlaybackRate;
	float_t m_flCycle;
	void *m_pOwner;
	char pad_0038[x64x32(8, 4)];
};

struct CCSGOPlayerAnimState
{
	OFFSET6432(int, modelIndex, 0x54, 0x1);
	OFFSET6432(C_BaseEntity*, player, 0x68, 0x60);
	OFFSET6432(void*, activeWeapon, 0x70, 0x64);
	OFFSET6432(void*, lastActiveWeapon, 0x78, 0x68);
	OFFSET6432(float, updateTime, 0x80, 0x6C);
	OFFSET6432(int, frameCount, 0x84, 0x70);
	OFFSET6432(vec3, origin, 0xC4, 0xB0);
	OFFSET6432(vec3, prevOrigin, 0xD0, 0xBC);
	OFFSET6432(vec3, vecVelocity, 0xDC, 0xC8);
	OFFSET6432(vec3, unkVel2, 0xE8, 0xD4);
	OFFSET6432(vec3, unkVel1, 0xF4, 0xE0);
	OFFSET6432(vec3, scaledVelocity, 0x100, 0xEC);
	OFFSET6432(int, animsetVersion, 0x3B0, 0x1);
};

#endif
