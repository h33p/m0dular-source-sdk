#ifndef ENUMS_SHARED_H
#define ENUMS_SHARED_H

enum EntityFlags
{
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_WATERJUMP = (1 << 2),
	FL_ONTRAIN = (1 << 3),
	FL_INRAIN = (1 << 4),
	FL_FROZEN = (1 << 5),
	FL_ATCONTROLS = (1 << 6),
	FL_CLIENT = (1 << 7),
	FL_FAKECLIENT = (1 << 8),
	MAX_ENTITYFLAGS
};

enum CSWeaponType
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_PLACEHOLDER,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN
};

enum Effects
{
	EF_BONEMERGE = 0x001, // Performs bone merge on client side
	EF_BRIGHTLIGHT = 0x002, // DLIGHT centered at entity origin
	EF_DIMLIGHT = 0x004, // player flashlight
	EF_NOINTERP = 0x008, // don't interpolate the next frame
	EF_NOSHADOW = 0x010, // Don't cast no shadow
	EF_NODRAW = 0x020, // don't draw entity
	EF_NORECEIVESHADOW = 0x040, // Don't receive no shadow
	EF_BONEMERGE_FASTCULL = 0x080, // For use with EF_BONEMERGE. If this is set, then it places this ent's origin at its
	// parent and uses the parent's bbox + the max extents of the aiment.
	// Otherwise, it sets up the parent's bones every frame to figure out where to place
	// the aiment, which is inefficient because it'll setup the parent's bones even if
	// the parent is not in the PVS.
	EF_ITEM_BLINK = 0x100, // blink an item so that the user notices it.
	EF_PARENT_ANIMATES = 0x200, // always assume that the parent entity is animating
	EF_MAX_BITS = 10
};

enum LifeState : unsigned char
{
	LIFE_ALIVE = 0,// alive
	LIFE_DYING = 1, // playing death animation or still falling off of a ledge waiting to hit ground
	LIFE_DEAD = 2, // dead. lying still.
	MAX_LIFESTATE
};

enum MoveType_t
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4,
	MAX_MOVETYPE
};

enum WeaponSound_t
{
	EMPTY,
	SINGLE,
	SINGLE_NPC,
	WPN_DOUBLE, // Can't be "DOUBLE" because windows.h uses it.
	DOUBLE_NPC,
	BURST,
	RELOAD,
	RELOAD_NPC,
	MELEE_MISS,
	MELEE_HIT,
	MELEE_HIT_WORLD,
	SPECIAL1,
	SPECIAL2,
	SPECIAL3,
	TAUNT,
	FAST_RELOAD,
	// Add new shoot sound types here
	REVERSE_THE_NEW_SOUND,
	NUM_SHOOT_SOUND_TYPES,
	MAX_WEAPONSOUND
};

enum class TeamNumbers : int
{
	TEAM_NONE = 0,
	TEAM_SPECTATOR,
	TEAM_CT, //TEAM_COMBINE,
	TEAM_T //TEAM_REBELS
};

enum class HitGroups : int
{
	HITGROUP_GENERIC = 0,
	HITGROUP_HEAD,
	HITGROUP_CHEST,
	HITGROUP_STOMACH,
	HITGROUP_LEFTARM,
	HITGROUP_RIGHTARM,
	HITGROUP_LEFTLEG,
	HITGROUP_RIGHTLEG,
	HITGROUP_GEAR
};

struct DefItem_t
{
	DefItem_t(const char* displayName,
			  const char* entityName,
			  const char* entityModel,
			  const char* killIcon = nullptr,
			  CSWeaponType weaponType = CSWeaponType::WEAPONTYPE_UNKNOWN)
	{
		this->displayName = displayName;
		this->entityName = entityName;
		this->entityModel = entityModel;
		this->killIcon = killIcon;
		this->weaponType = weaponType;
	}

	const char* displayName = nullptr;
	const char* entityName = nullptr;
	const char* entityModel = nullptr;
	const char* killIcon = nullptr;
    CSWeaponType weaponType = CSWeaponType::WEAPONTYPE_UNKNOWN;
};

//Flags that are supposed to be implemented by other SDKs
#ifndef ENUMS_H
#define ENUMS_H
enum ClassId {
	UNDEFINED = 0
};
#endif

#endif
