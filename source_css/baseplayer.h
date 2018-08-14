#ifndef BASEPLAYER_H
#define BASEPLAYER_H

class C_BaseEntity;
struct AnimationLayer;
struct CCSPlayerAnimState;

class C_BasePlayer : public C_BaseEntity
{
  public:
	OFFSET(VarMapping_t, varMapping, 0x14);
	OFFSET(CUtlVector<matrix3x4_t>, boneMatrix, PosixWin(0x800, 0x80c));
	ONETVAR(AnimationLayer*, animationLayers, "DT_BaseAnimating", "m_nMuzzleFlashParity", 0x20);
	ONETVAR(CCSPlayerAnimState*, animState, "DT_CSPlayer", "m_iAddonBits", -0x1c);
	ONETVAR(vec3, localAngles, "DT_BasePlayer", "deadflag", 0x4);
	NETVAR(vec3, viewOffset, "DT_BasePlayer", "m_vecViewOffset[0]");

	VFuncPosixWin(void, UpdateClientSideAnimation, 251, 189);
};

struct AnimationLayer
{
	int sequence;
	float prevCycle;
	float weight;
	int order;
	float playbackRate;
	float cycle;
	float layerAnimTime;
	float layerFadeOutTime;
	void* unk[3];
};

enum PlayerAnimEvent_t
{
	PLAYERANIMEVENT_FIRE_GUN_PRIMARY=0,
	PLAYERANIMEVENT_FIRE_GUN_SECONDARY,
	PLAYERANIMEVENT_THROW_GRENADE,
	PLAYERANIMEVENT_JUMP,
	PLAYERANIMEVENT_RELOAD,
	PLAYERANIMEVENT_RELOAD_START,
	PLAYERANIMEVENT_RELOAD_LOOP,
	PLAYERANIMEVENT_RELOAD_END,
	PLAYERANIMEVENT_COUNT
};

struct CCSPlayerAnimState
{
	virtual void Release() = 0;
	void* animConfig;
	void* outer;
	float eyePitch;
	float eyeYaw;
	float goalFeetYaw;
	float currentFeetYaw;
	bool currentFeetYawInitialized;
	float currentTorsoYaw;
	float lastYaw;
	float lastTurnTime;
	int turningInPlace;
	vec3 angRender;
	float gaitYaw;
	float storedCycle;
	vec2 lastMovePose;
	CUtlVector<AnimationLayer> idleSequenceTransitioner;
	CUtlVector<AnimationLayer> sequenceTransitioner;
	bool jumping;
	float jumpStartTime;
	bool firstJumpFrame;
	bool reloading;
	float reloadCycle;
	int reloadSequence;
	float reloadHoldEndTime;
	bool firing;
	int fireSequence;
	float fireCycle;
	PlayerAnimEvent_t delayedFire;
	bool throwingGrenade;
	bool primingGrenade;
	float grenadeCycle;
	int grenadeSequence;
	int lastThrowGrenadeCounter;
	C_BasePlayer* player;
	void* helpers;
};

#endif
