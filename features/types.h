#ifndef SOURCE_TYPES_H
#define SOURCE_TYPES_H

typedef unsigned char FakelagState_t;

enum FakelagState
{
	NONE = 0,
	FIRST = (1 << 0),
	LAST = (1 << 1)
};

#endif
