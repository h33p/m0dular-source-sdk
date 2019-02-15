#ifndef IENGINETRACE_H
#define IENGINETRACE_H

#include "enums.h"
#include <float.h>

#define DISPSURF_FLAG_SURFACE (1<<0)
#define DISPSURF_FLAG_WALKABLE (1<<1)
#define DISPSURF_FLAG_BUILDABLE (1<<2)
#define DISPSURF_FLAG_SURFPROP1 (1<<3)
#define DISPSURF_FLAG_SURFPROP2 (1<<4)

#define CONTENTS_EMPTY 0

#define CONTENTS_SOLID 0x1
#define CONTENTS_WINDOW 0x2
#define CONTENTS_AUX 0x4
#define CONTENTS_GRATE 0x8
#define CONTENTS_SLIME 0x10
#define CONTENTS_WATER 0x20
#define CONTENTS_BLOCKLOS 0x40
#define CONTENTS_OPAQUE 0x80
#define LAST_VISIBLE_CONTENTS CONTENTS_OPAQUE

#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME 0x100
#define CONTENTS_UNUSED 0x200
#define CONTENTS_BLOCKLIGHT 0x400
#define CONTENTS_TEAM1 0x800
#define CONTENTS_TEAM2 0x1000
#define CONTENTS_IGNORE_NODRAW_OPAQUE 0x2000
#define CONTENTS_MOVEABLE 0x4000
#define CONTENTS_AREAPORTAL 0x8000
#define CONTENTS_PLAYERCLIP 0x10000
#define CONTENTS_MONSTERCLIP 0x20000
#define CONTENTS_CURRENT_0 0x40000
#define CONTENTS_CURRENT_90 0x80000
#define CONTENTS_CURRENT_180 0x100000
#define CONTENTS_CURRENT_270 0x200000
#define CONTENTS_CURRENT_UP 0x400000
#define CONTENTS_CURRENT_DOWN 0x800000

#define CONTENTS_ORIGIN 0x1000000

#define CONTENTS_MONSTER 0x2000000
#define CONTENTS_DEBRIS 0x4000000
#define CONTENTS_DETAIL 0x8000000
#define CONTENTS_TRANSLUCENT 0x10000000
#define CONTENTS_LADDER 0x20000000
#define CONTENTS_HITBOX 0x40000000

#define SURF_LIGHT 0x0001
#define SURF_SKY2D 0x0002
#define SURF_SKY 0x0004
#define SURF_WARP 0x0008
#define SURF_TRANS 0x0010
#define SURF_NOPORTAL 0x0020
#define SURF_TRIGGER 0x0040
#define SURF_NODRAW 0x0080

#define SURF_HINT 0x0100

#define SURF_SKIP 0x0200
#define SURF_NOLIGHT 0x0400
#define SURF_BUMPLIGHT 0x0800
#define SURF_NOSHADOWS 0x1000
#define SURF_NODECALS 0x2000
#define SURF_NOPAINT SURF_NODECALS
#define SURF_NOCHOP 0x4000
#define SURF_HITBOX 0x8000

enum SolidType_t
{
	SOLID_NONE = 0, //no solid model
	SOLID_BSP = 1, //a BSP tree
	SOLID_BBOX = 2, //an AABB
	SOLID_OBB = 3, //an OBB (not implemented yet)
	SOLID_OBB_YAW  = 4, //an OBB, constrained so that it can only yaw
	SOLID_CUSTOM = 5, //Always call into the entity for tests
	SOLID_VPHYSICS = 6, //solid vphysics object, get vcollide from the model and collide with that
	SOLID_LAST,
};

enum SolidFlags_t
{
	FSOLID_CUSTOMRAYTEST = (1 << 0), //Ignore solid type + always call into the entity for ray tests
	FSOLID_CUSTOMBOXTEST = (1 << 1), //Ignore solid type + always call into the entity for swept box tests
	FSOLID_NOT_SOLID = (1 << 2), //Are we currently not solid?
	FSOLID_TRIGGER  = (1 << 3), //This is something may be collideable but fires touch functions, even when it's not collideable (when the FSOLID_NOT_SOLID flag is set)
	FSOLID_NOT_STANDABLE = (1 << 4), //You can't stand on this
	FSOLID_VOLUME_CONTENTS = (1 << 5), //Contains volumetric contents (like water)
	FSOLID_FORCE_WORLD_ALIGNED = (1 << 6), //Forces the collision rep to be world-aligned even if it's SOLID_BSP or SOLID_VPHYSICS
	FSOLID_USE_TRIGGER_BOUNDS = (1 << 7), //Uses a special trigger bounds separate from the normal OBB
	FSOLID_ROOT_PARENT_ALIGNED = (1 << 8), //Collisions are defined in root parent's local coordinate space
	FSOLID_TRIGGER_TOUCH_DEBRIS = (1 << 9), //This trigger will touch debris objects
	FSOLID_MAX_BITS = 10
};


// -----------------------------------------------------
// spatial content masks - used for spatial queries (traceline,etc.)
// -----------------------------------------------------
#define MASK_ALL (0xFFFFFFFF)
#define MASK_SOLID (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define MASK_PLAYERSOLID (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define MASK_NPCSOLID (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define MASK_NPCFLUID (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define MASK_WATER (CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
#define MASK_OPAQUE (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
#define MASK_OPAQUE_AND_NPCS (MASK_OPAQUE|CONTENTS_MONSTER)
#define MASK_BLOCKLOS (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
#define MASK_BLOCKLOS_AND_NPCS (MASK_BLOCKLOS|CONTENTS_MONSTER)
#define MASK_VISIBLE (MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define MASK_VISIBLE_AND_NPCS (MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define MASK_SHOT (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define MASK_SHOT_BRUSHONLY (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
#define MASK_SHOT_HULL (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
#define MASK_SHOT_PORTAL (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define MASK_SOLID_BRUSHONLY (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
#define MASK_PLAYERSOLID_BRUSHONLY (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
#define MASK_NPCSOLID_BRUSHONLY (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define MASK_NPCWORLDSTATIC (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define MASK_NPCWORLDSTATIC_FLUID (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
#define MASK_SPLITAREAPORTAL (CONTENTS_WATER|CONTENTS_SLIME)
#define MASK_CURRENT (CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)
#define MASK_DEADSOLID (CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)

class IHandleEntity;
struct Ray_t;
class CGameTrace;
typedef CGameTrace trace_t;
class ICollideable;
class ITraceListData;
class CPhysCollide;
struct cplane_t;
struct virtualmeshlist_t;

//TODO: Move this out of here!!!
extern IClientEntityList* entityList;

// Settings for takeDamage
#define DAMAGE_NO 0					// Don't call damage functions
#define DAMAGE_EVENTS_ONLY 1		// Call damage functions, but don't modify health
#define DAMAGE_YES 2
#define DAMAGE_AIM 3

enum class TraceType
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

class ITraceFilter
{
  public:
	virtual bool ShouldHitEntity(IHandleEntity *pEntity, int) = 0;
	virtual TraceType GetTraceType() = 0;
};

//-----------------------------------------------------------------------------
// Classes are expected to inherit these + implement the ShouldHitEntity method
//-----------------------------------------------------------------------------

// This is the one most normal traces will inherit from
class CTraceFilter : public ITraceFilter
{
  public:
	virtual bool ShouldHitEntity(IHandleEntity* pEntityHandle, int /*contentsMask*/) override
	{
		return !(pEntityHandle == pSkip);
	}
	virtual TraceType GetTraceType() override
	{
		return TraceType::TRACE_EVERYTHING;
	}
	void* pSkip;
};

class CTraceFilterSkipEntity : public ITraceFilter
{
  public:
	CTraceFilterSkipEntity(IHandleEntity* pEntityHandle)
	{
		pSkip = pEntityHandle;
	}

	virtual bool ShouldHitEntity(IHandleEntity* pEntityHandle, int /*contentsMask*/) override
	{
		return !(pEntityHandle == pSkip);
	}
	virtual TraceType GetTraceType() override
	{
		return TraceType::TRACE_EVERYTHING;
	}
	void* pSkip;
};

class CTraceFilterEntitiesOnly : public ITraceFilter
{
  public:
	virtual bool ShouldHitEntity(IHandleEntity* pEntityHandle, int /*contentsMask*/) override
	{
		return true;
	}
	virtual TraceType GetTraceType() override
	{
		return TraceType::TRACE_ENTITIES_ONLY;
	}
};


//-----------------------------------------------------------------------------
// Classes need not inherit from these
//-----------------------------------------------------------------------------
class CTraceFilterWorldOnly : public ITraceFilter
{
  public:
	virtual bool ShouldHitEntity(IHandleEntity* /*pServerEntity*/, int /*contentsMask*/) override
	{
		return false;
	}
	virtual TraceType GetTraceType() override
	{
		return TraceType::TRACE_WORLD_ONLY;
	}
};

class CTraceFilterWorldAndPropsOnly : public ITraceFilter
{
  public:
	virtual bool ShouldHitEntity(IHandleEntity* /*pServerEntity*/, int /*contentsMask*/) override
	{
		return false;
	}
	virtual TraceType GetTraceType() override
	{
		return TraceType::TRACE_EVERYTHING;
	}
};

class CTraceFilterSkipTwoEntities : public ITraceFilter
{
  public:
	CTraceFilterSkipTwoEntities(IClientEntity* ent1, IClientEntity* ent2)
	{
		pEnt1 = ent1;
		pEnt2 = ent2;
	}
	virtual bool ShouldHitEntity(IHandleEntity* pEntityHandle, int /*contentsMask*/) override
	{
		return !(pEntityHandle == pEnt1 || pEntityHandle == pEnt2);
	}
	virtual TraceType GetTraceType() override
	{
		return TraceType::TRACE_EVERYTHING;
	}

  private:
	IClientEntity* pEnt1;
	IClientEntity* pEnt2;
};

class CTraceFilterHitAll : public CTraceFilter
{
  public:
	virtual TraceType GetTraceType() override
	{
		return TraceType::TRACE_EVERYTHING;
	}

	virtual bool ShouldHitEntity(IHandleEntity* /*pServerEntity*/, int /*contentsMask*/l) override
	{
		return true;
	}
};

class CTraceFilterSkipPlayers : public ITraceFilter
{
  public:
	virtual bool ShouldHitEntity(IHandleEntity* pEntityHandle, int /*contentsMask*/) override
	{
		return pEntityHandle && !((C_BaseEntity*)pEntityHandle)->IsPlayer();
	}
	virtual TraceType GetTraceType() override
	{
		return TraceType::TRACE_EVERYTHING;
	}
};


enum class DebugTraceCounterBehavior_t
{
	kTRACE_COUNTER_SET = 0,
	kTRACE_COUNTER_INC,
};

//-----------------------------------------------------------------------------
// Enumeration interface for EnumerateLinkEntities
//-----------------------------------------------------------------------------
class IEntityEnumerator
{
  public:
	// This gets called with each handle
	virtual bool EnumElement(IHandleEntity *handleEntity) = 0;
};

class CEntityListAlongRay : public IEntityEnumerator
{
  public:

	enum { MAX_ENTITIES_ALONGRAY = 1024 };

	CEntityListAlongRay()
	{
		count = 0;
	}

	void Reset()
	{
		count = 0;
	}

	int Count()
	{
		return count;
	}

	virtual bool EnumElement(IHandleEntity* handleEntity) override
	{
		if (count < MAX_ENTITIES_ALONGRAY)
			entityHandles[count++] = handleEntity;
		else
			return true;

		return false;
	}

	int count;
	IHandleEntity* entityHandles[MAX_ENTITIES_ALONGRAY];
};


struct BrushSideInfo_t
{
	vec4_t plane; // The plane of the brush side
	unsigned short bevel; // Bevel plane?
	unsigned short thin; // Thin?
};

class CPhysCollide;

struct vcollide_t
{
	unsigned short solidCount : 15;
	unsigned short isPacked : 1;
	unsigned short descSize;
	// VPhysicsSolids
	CPhysCollide **solids;
	char *pKeyValues;
	void *pUserData;
};

struct cmodel_t
{
	vec3 mins, maxs;
	vec3 origin; // for sounds or lights
	int headnode;
	vcollide_t vcollisionData;
};

struct csurface_t
{
	const char *name;
	short surfaceProps;
	unsigned short flags; // BUGBUG: These are declared per surface, not per material, but this database is per-material now
};


//-----------------------------------------------------------------------------
// A ray...
//-----------------------------------------------------------------------------

#ifdef SOURCE_CSGO_SDK
#define RAY_ALIGN alignas(16)
#else
#define RAY_ALIGN
#endif

struct Ray_t
{
    RAY_ALIGN vec3_t start; // starting point, centered within the extents
	RAY_ALIGN vec3_t delta; // direction + length of the ray
	RAY_ALIGN vec3_t startOffset; // Add this to start to Get the actual ray start
	RAY_ALIGN vec3_t extents; // Describes an axis aligned box extruded along a ray
#ifdef SOURCE_CSGO_SDK
	const matrix3x4_t *worldAxisTransform;
#endif
	bool isRay; // are the extents zero?
	bool isSwept; // is delta != 0?

	Ray_t()
#ifdef SOURCE_CSGO_SDK
		: worldAxisTransform(NULL)
#endif
	{

	}

	void Init(vec3_t const& vstart, vec3_t const& vend)
	{
		delta = vend - vstart;

		isSwept = (delta.LengthSqr() != 0);

		extents = 0.f;

#ifdef SOURCE_CSGO_SDK
		worldAxisTransform = NULL;
#endif
		isRay = true;

		// Offset start to be in the center of the box...
		startOffset = 0.f;
		start = vstart;
	}

	void Init(vec3_t const& vstart, vec3_t const& vend, vec3_t const& mins, vec3_t const& maxs)
	{
		delta = vend - vstart;

#ifdef SOURCE_CSGO_SDK
		worldAxisTransform = NULL;
#endif
		isSwept = (delta.LengthSqr() != 0);

		extents = maxs - mins;
		extents *= 0.5f;
		isRay = (extents.LengthSqr() < 1e-6);

		// Offset start to be in the center of the box...
		startOffset = maxs + mins;
		startOffset *= 0.5f;
		start = vstart + startOffset;
		startOffset *= -1.0f;
	}
	vec3_t InvDelta() const
	{
		vec3_t vecInvDelta;
		for(int iAxis = 0; iAxis < 3; ++iAxis) {
			if(delta[iAxis] != 0.0f) {
				vecInvDelta[iAxis] = 1.0f / delta[iAxis];
			} else {
				vecInvDelta[iAxis] = FLT_MAX;
			}
		}
		return vecInvDelta;
	}

  private:
};

class
#ifdef _WIN32
#ifdef SOURCE_CSGO_SDK
//alignas(1024)
#endif
#endif
CBaseTrace
{
  public:
	bool IsDispSurface(void) { return ((dispFlags & DISPSURF_FLAG_SURFACE) != 0); }
	bool IsDispSurfaceWalkable(void) { return ((dispFlags & DISPSURF_FLAG_WALKABLE) != 0); }
	bool IsDispSurfaceBuildable(void) { return ((dispFlags & DISPSURF_FLAG_BUILDABLE) != 0); }
	bool IsDispSurfaceProp1(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP1) != 0); }
	bool IsDispSurfaceProp2(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP2) != 0); }

  public:

	// these members are aligned!!
	vec3 startpos; // start position
	vec3 endpos; // final position
	cplane_t plane; // surface normal at impact

	float fraction; // time completed, 1.0 = didn't hit anything

	int contents; // contents on other side of surface hit
	unsigned short dispFlags; // displacement flags for marking surfaces with data

	bool allsolid; // if true, plane is not valid
	bool startsolid; // if true, the initial point was in a solid area

	CBaseTrace() {}

};

class CGameTrace : public CBaseTrace
{
  public:
	bool DidHitWorld() const;
	bool DidHitNonWorldEntity() const;
	int GetEntityIndex() const;
	bool DidHit() const;
	bool IsVisible() const;

  public:
	float fractionleftsolid; // time we left a solid, only valid if we started in solid
	csurface_t surface; // surface hit (impact surface)
	HitGroups hitgroup; // 0 == generic, non-zero is specific body part
	short physicsbone; // physics bone hit by trace in studio
#ifdef SOURCE_CSGO_SDK
	unsigned short worldSurfaceIndex; // Index of the msurface2_t, if applicable
#endif
	IClientEntity* ent; // Entity to hit
	int hitbox; // box hit by trace in studio

	CGameTrace() {}

	// No copy constructors allowed
	CGameTrace(const CGameTrace& other) :
		fractionleftsolid(other.fractionleftsolid),
		surface(other.surface),
		hitgroup(other.hitgroup),
		physicsbone(other.physicsbone),
#ifdef SOURCE_CSGO_SDK
		worldSurfaceIndex(other.worldSurfaceIndex),
#endif
		ent(other.ent),
		hitbox(other.hitbox)
	{
		startpos = other.startpos;
		endpos = other.endpos;
		plane = other.plane;
		fraction = other.fraction;
		contents = other.contents;
		dispFlags = other.dispFlags;
		allsolid = other.allsolid;
		startsolid = other.startsolid;
	}

	CGameTrace& operator=(const CGameTrace& other)
	{
		startpos = other.startpos;
		endpos = other.endpos;
		plane = other.plane;
		fraction = other.fraction;
		contents = other.contents;
		dispFlags = other.dispFlags;
		allsolid = other.allsolid;
		startsolid = other.startsolid;
		fractionleftsolid = other.fractionleftsolid;
		surface = other.surface;
		hitgroup = other.hitgroup;
		physicsbone = other.physicsbone;
#ifdef SOURCE_CSGO_SDK
		worldSurfaceIndex = other.worldSurfaceIndex;
#endif
		ent = other.ent;
		hitbox = other.hitbox;
		return *this;
	}
};

inline bool CGameTrace::DidHitWorld() const
{
	return ent == entityList->GetClientEntity(0);
}

inline bool CGameTrace::DidHitNonWorldEntity() const
{
	return ent != nullptr && !DidHitWorld();
}

inline int CGameTrace::GetEntityIndex() const
{
	if (ent)
		return ent->EntIndex();
	else
		return -1;
}

inline bool CGameTrace::DidHit() const
{
	return fraction < 1.f || allsolid || startsolid;
}

inline bool CGameTrace::IsVisible() const
{
	return fraction > 0.97f;
}

class ITraceListData
{
  public:
	virtual void EnumElement(IHandleEntity*) = 0;
	virtual void Destr1() = 0;
	virtual void Destr2() = 0;
	virtual void Reset() = 0;
	virtual bool IsEmpty() = 0;
	virtual bool CanTraceRay(const Ray_t&) = 0;
};

class IEngineTrace
{
public:
	// Returns the contents mask + entity at a particular world-space position
	virtual int GetPointContents(const vec3 &vecAbsPosition, int contentsMask = MASK_ALL, IHandleEntity** ppEntity = NULL) = 0;
#ifdef SOURCE_CSGO_SDK
	// Returns the contents mask of the world only @ the world-space position (static props are ignored)
	virtual int GetPointContents_WorldOnly(const vec3 &vecAbsPosition, int contentsMask = MASK_ALL) = 0;
#endif
	// Get the point contents, but only test the specific entity. This works
	// on static props and brush models.
	//
	// If the entity isn't a static prop or a brush model, it returns CONTENTS_EMPTY and sets
	// bFailed to true if bFailed is non-null.
	virtual int GetPointContents_Collideable(ICollideable *pCollide, const vec3 &vecAbsPosition) = 0;
	// Traces a ray against a particular entity
	virtual void ClipRayToEntity(const Ray_t &ray, unsigned int fMask, IHandleEntity *pEnt, trace_t *pTrace) = 0;
	// Traces a ray against a particular entity
	virtual void ClipRayToCollideable(const Ray_t &ray, unsigned int fMask, ICollideable *pCollide, trace_t *pTrace) = 0;
	// A version that simply accepts a ray (can work as a traceline or tracehull)
	virtual void TraceRay(const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace) = 0;
	// A version that sets up the leaf and entity lists and allows you to pass those in for collision.
	virtual void SetupLeafAndEntityListRay(const Ray_t &ray, ITraceListData *pTraceData) = 0;
	virtual void SetupLeafAndEntityListBox(const vec3 &vecBoxMin, const vec3 &vecBoxMax, ITraceListData *pTraceData) = 0;
	virtual void TraceRayAgainstLeafAndEntityList(const Ray_t &ray, ITraceListData *pTraceData, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace) = 0;
	// A version that sweeps a collideable through the world
	// abs start + abs end represents the collision origins you want to sweep the collideable through
	// vecAngles represents the collision angles of the collideable during the sweep
	virtual void SweepCollideable(ICollideable *pCollide, const vec3 &vecAbsStart, const vec3 &vecAbsEnd, const vec3 &vecAngles, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace) = 0;
	// Enumerates over all entities along a ray
	// If triggers == true, it enumerates all triggers along a ray
	virtual void EnumerateEntities(const Ray_t &ray, bool triggers, IEntityEnumerator *pEnumerator) = 0;
	// Same thing, but enumerate entitys within a box
	virtual void EnumerateEntities(const vec3 &vecAbsMins, const vec3 &vecAbsMaxs, IEntityEnumerator *pEnumerator) = 0;
	// Convert a handle entity to a collideable.  Useful inside enumer
	virtual ICollideable *GetCollideable(IHandleEntity *pEntity) = 0;
	// HACKHACK: Temp for performance measurments
	virtual int GetStatByIndex(int index, bool bClear) = 0;
#ifdef SOURCE_CSGO_SDK
	//finds brushes in an AABB, prone to some false positives //TODO CUtilvec3<int> *pOutput
	virtual void GetBrushesInAABB(const vec3 &vMins, const vec3 &vMaxs, void* *pOutput, int iContentsMask = 0xFFFFFFFF) = 0;
	//Creates a CPhysCollide out of all displacements wholly or partially contained in the specified AABB
	virtual CPhysCollide* GetCollidableFromDisplacementsInAABB(const vec3& vMins, const vec3& vMaxs) = 0;
	// gets the number of displacements in the world
	virtual int GetNumDisplacements() = 0;
	// gets a specific diplacement mesh
	virtual void GetDisplacementMesh(int nIndex, virtualmeshlist_t *pMeshTriList) = 0;
	//retrieve brush planes and contents, returns true if data is being returned in the output pointers, false if the brush doesn't exist //TODO: CUtilvec3<BrushSideInfo_t> *pBrushSideInfoOut
	virtual bool GetBrushInfo(int iBrush, void *pBrushSideInfoOut, int *pContentsOut) = 0;
	virtual bool PointOutsideWorld(const vec3 &ptTest) = 0; //Tests a point to see if it's outside any playable area
	// Walks bsp to find the leaf containing the specified point
	virtual int GetLeafContainingPoint(const vec3 &ptTest) = 0;
	virtual ITraceListData* AllocTraceListData() = 0;
	virtual void FreeTraceListData(ITraceListData*) = 0;
	/// Used only in debugging: get/set/clear/increment the trace debug counter. See comment below for details.
	virtual int GetSetDebugTraceCounter(int value, DebugTraceCounterBehavior_t behavior) = 0;

	virtual void GetMeshesFromDisplacementsInAABB(const vec3&, const vec3&, void*, int) = 0;
	virtual void GetBrushesInCollideable(ICollideable*, void*) = 0;
	virtual bool IsFullyOccluded(int, void*, void*, const vec3&) = 0;
	virtual void SuspendOcclusionTests(void) = 0;
	virtual void ResumeOcclusionTests(void) = 0;
	virtual void FlushOcclusionQueries(void) = 0;
	virtual void HandleEntityToCollideable(IHandleEntity*, ICollideable**) = 0;
	virtual ICollideable* GetWorldCollideable(void) = 0;
	virtual void GetDebugName(IHandleEntity*) = 0;
	virtual void SetTraceEntity(ICollideable*, CGameTrace*) = 0;
#endif
};

#endif
