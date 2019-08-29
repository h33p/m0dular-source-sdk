#ifndef GLOW_OBJECT_H
#define GLOW_OBJECT_H

struct GlowObjectDefinition_t
{
	class IHandleEntity* ent;
	vec4_t color;
	PAD(4);
	float movementAlpha;
	float bloomAmount;
	PAD(4);
	bool renderWhenOccluded;
	bool renderWhenUnoccluded;
	bool fullBloom;
	PAD(1);
	int fullBloomStencilTestValue;
	int glowStyle;
	int splitScreenSlot;
	int nextFreeSlot;
};

#endif