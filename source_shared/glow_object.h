#ifndef GLOW_OBJECT_H
#define GLOW_OBJECT_H

struct GlowObjectDefinition_t
{
	class CBaseHandle ent;
	vec4_t color;
	bool renderWhenOccluded;
	bool renderWhenUnoccluded;
	int splitScreenSlot;
	int nextFreeSlot;
};

#endif