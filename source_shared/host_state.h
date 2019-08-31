#ifndef HOST_STATE_H
#define HOST_STATE_H

class CCommonHostState
{
public:
	struct model_t* worldmodel;
	struct worldbrushdata_t* worldbrush;
	float intervalPerTick;
};

struct worldbrushdata_t
{
	PAD6432(0x144, 0xa8);
	int numworldlights;
	struct dworldlight_t* worldlights;
};

enum emittype_t
{
	emit_surface, // 90 degree spotlight
	emit_point, // simple point light source
	emit_spotlight, // spotlight with penumbra
	emit_skylight, // directional light with no falloff (surface must trace to SKY texture)
	emit_quakelight, // linear falloff, non-lambertian
	emit_skyambient, // spherical light source with no falloff (surface must trace to SKY texture)
};

struct dworldlight_t
{
	vec3 origin;
	vec3 intensity;
	vec3 normal;
	int cluster;
	emittype_t type;
	int style;
	float stopdot;
	float stopdot2;
	float exponent;
	float radius;
	float constantAttn;
	float linearAttn;
	float quadraticAttn;
	int flags;
	int texinfo;
	int owner;
	PAD(12);
};

static_assert(sizeof(dworldlight_t) == 100);

#endif