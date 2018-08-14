#ifndef STUDIO_CSGO_H
#define STUDIO_CSGO_H

#include <stdint.h>

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

#endif
