#ifndef PHYSICS_H
#define PHYSICS_H

struct surfacephysicsparams_t
{
	float friction;
	float elasticity;
	float density;
	float thickness;
	float dampening;
};

struct surfaceaudioparams_t
{
	float audioReflectivity;
	float audioHardnessFactor;
	float audioRoughnessFactor;
	float scrapeRoughThreshold;
	float impactHardThreshold;
	float audioHardMinVelocity;
	float highPitchOcclusion;
	float midPitchOcclusion;
	float lowPitchOcclusion;
};

struct surfacesoundnames_t
{
	short walkLeft;
	short walkRight;
	short runLeft;
	short runRight;
	short impactsoft;
	short impacthard;
	short scrapesmooth;
	short scraperough;
	short bulletimpact;
	short rolling;
	short breakSound;
	short strain;
};

struct surfacegameprops_t
{
	float flMaxSpeedFactor;
	float flJumpFactor;
	float flPenetrationModifier;
	float flDamageModifier;
	uint16_t material;
	uint8_t climbable;
};

struct surfacedata_t
{
	surfacephysicsparams_t physics;
	surfaceaudioparams_t audio;
	surfacesoundnames_t sounds;
	surfacegameprops_t game;
	char pad[48];
};

#endif
