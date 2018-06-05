#ifndef SOURCE_SHARED_TYPES_H
#define SOURCE_SHARED_TYPES_H

#include "../framework/math/mmath.h"

typedef matrix4x4 VMatrix;
typedef matrix<3,4> matrix3x4_t;

struct cplane_t
{
	vec3 normal;
	float dist;
	uint8_t type;
	uint8_t signbits;
	uint8_t pad[2];
};

#endif
