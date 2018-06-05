#ifndef STUDIO_H
#define STUDIO_H

#include <stdint.h>

typedef float Quaternion[4];
typedef float RadianEuler[3];

#define MAX_QPATH 260

#define BONE_CALCULATE_MASK 0x1F
#define BONE_PHYSICALLY_SIMULATED 0x01 // bone is physically simulated when physics are active
#define BONE_PHYSICS_PROCEDURAL 0x02 // procedural when physics is active
#define BONE_ALWAYS_PROCEDURAL 0x04 // bone is always procedurally animated
#define BONE_SCREEN_ALIGN_SPHERE 0x08 // bone aligns to the screen, not constrained in motion.
#define BONE_SCREEN_ALIGN_CYLINDER 0x10 // bone aligns to the screen, constrained by it's own axis.

#define BONE_USED_MASK 0x0007FF00
#define BONE_USED_BY_ANYTHING 0x0007FF00
#define BONE_USED_BY_HITBOX 0x00000100 // bone (or child) is used by a hit box
#define BONE_USED_BY_ATTACHMENT 0x00000200 // bone (or child) is used by an attachment point
#define BONE_USED_BY_VERTEX_MASK 0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0 0x00000400 // bone (or child) is used by the toplevel model via skinned vertex
#define BONE_USED_BY_VERTEX_LOD1 0x00000800
#define BONE_USED_BY_VERTEX_LOD2 0x00001000
#define BONE_USED_BY_VERTEX_LOD3 0x00002000
#define BONE_USED_BY_VERTEX_LOD4 0x00004000
#define BONE_USED_BY_VERTEX_LOD5 0x00008000
#define BONE_USED_BY_VERTEX_LOD6 0x00010000
#define BONE_USED_BY_VERTEX_LOD7 0x00020000
#define BONE_USED_BY_BONE_MERGE 0x00040000 // bone is available for bone merge to occur against it

#define BONE_USED_BY_VERTEX_AT_LOD(lod) ( BONE_USED_BY_VERTEX_LOD0 << (lod) )
#define BONE_USED_BY_ANYTHING_AT_LOD(lod) ( ( BONE_USED_BY_ANYTHING & ~BONE_USED_BY_VERTEX_MASK ) | BONE_USED_BY_VERTEX_AT_LOD(lod) )

#define MAX_NUM_LODS 8
#define MAXSTUDIOBONES 128 // total bones actually used

#define BONE_TYPE_MASK 0x00F00000
#define BONE_FIXED_ALIGNMENT 0x00100000 // bone can't spin 360 degrees, all interpolation is normalized around a fixed orientation

#define BONE_HAS_SAVEFRAME_POS 0x00200000 // vec348
#define BONE_HAS_SAVEFRAME_ROT64 0x00400000 // Quaternion64
#define BONE_HAS_SAVEFRAME_ROT32 0x00800000 // Quaternion32


enum modtype_t
{
	mod_bad = 0,
	mod_brush,
	mod_sprite,
	mod_studio
};

enum Hitboxes
{
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_LOWER_NECK,
	HITBOX_PELVIS,
	HITBOX_STOMACH,
	HITBOX_LOWER_CHEST,
	HITBOX_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_MAX
};

typedef unsigned short MDLHandle_t;

struct mstudiobone_t
{
	int sznameindex;
	int parent; // parent bone
	int bonecontroller[6]; // bone controller index, -1 == none
	vec3 pos;
	Quaternion quat;
	RadianEuler rot;
	vec3 posscale;
	vec3 rotscale;

	matrix3x4_t poseToBone;
	Quaternion qAlignment;
	int flags;
	int proctype;
	int procindex; // procedural rule
	mutable int physicsbone; // index into physically simulated bone
	inline void* pProcedure() const
	{
		if (procindex == 0)
			return NULL;
		else
			return (void *)(((char*)this) + procindex);
	};
	int surfacepropidx; // index into string tablefor property name
	inline char* pszSurfaceProp(void) const
	{
		return ((char *)this) + surfacepropidx;
	}

	inline int GetSurfaceProp(void) const
	{
		return surfacepropLookup;
	}

	int contents; // See BSPFlags.h for the contents flags
	int surfacepropLookup; // this index must be cached by the loader, not saved in the file
	int unused[7]; // remove as appropriate
};


struct mstudiobbox_t
{
	int bone;
	int group;
	vec3 bbmin;
	vec3 bbmax;
	int szhitboxnameindex;
	int32_t m_iPad01[3];
	float m_flRadius;
	int32_t m_iPad02[4];

	const char* GetName()
	{
		if(!szhitboxnameindex) return nullptr;
		return (const char*)((uint8_t*)this + szhitboxnameindex);
	}
};

struct mstudiohitboxset_t
{
	int sznameindex;
	int numhitboxes;
	int hitboxindex;

	const char* GetName()
	{
		if(!sznameindex) return nullptr;
		return (const char*)((uint8_t*)this + sznameindex);
	}

	mstudiobbox_t* GetHitbox(int i)
	{
		if(i > numhitboxes) return nullptr;
		return (mstudiobbox_t*)((uint8_t*)this + hitboxindex) + i;
	}
};

struct model_t
{
	void* fnHandle; //0x0000
	char szName[260]; //0x0004
	int nLoadFlags; //0x0108
	int nServerCount; //0x010C
	int type; //0x0110
	int flags; //0x0114
	vec3 vecMins; //0x0118
	vec3 vecMaxs; //0x0124
	float radius; //0x0130
	char pad[0x1C]; //0x0134
};//Size=0x0150

class studiohdr_t
{
  public:
	int id; //0x0000
	int version; //0x0004
	int checksum; //0x0008
	char szName[64]; //0x000C
	int length; //0x004C
	vec3 vecEyePos; //0x0050
	vec3 vecIllumPos; //0x005C
	vec3 vecHullMin; //0x0068
	vec3 vecHullMax; //0x0074
	vec3 vecBBMin; //0x0080
	vec3 vecBBMax; //0x008C
	int flags; //0x0098
	int numbones; //0x009C
	int boneindex; //0x00A0
	int numbonecontrollers; //0x00A4
	int bonecontrollerindex; //0x00A8
	int numhitboxsets; //0x00AC
	int hitboxsetindex; //0x00B0
	int numlocalanim; //0x00B4
	int localanimindex; //0x00B8
	int numlocalseq; //0x00BC
	int localseqindex; //0x00C0
	int activitylistversion; //0x00C4
	int eventsindexed; //0x00C8
	int numtextures; //0x00CC
	int textureindex; //0x00D0

	mstudiohitboxset_t* GetHitboxSet(int i)
	{
		if(i > numhitboxsets) return nullptr;
		return (mstudiohitboxset_t*)((uint8_t*)this + hitboxsetindex) + i;
	}
	mstudiobone_t* GetBone(int i)
	{
		if(i > numbones) return nullptr;
		return (mstudiobone_t*)((uint8_t*)this + boneindex) + i;
	}

};//Size=0x00D4

#endif
