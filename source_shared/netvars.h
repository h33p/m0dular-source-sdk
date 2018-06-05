#ifndef NETVARS_H
#define NETVARS_H

#include <stdint.h>
#include "../framework/utils/crc32.h"

class CBaseClient;

namespace SourceNetvars
{
	void Initialize(CBaseClient* cl);
	int GetOffset(uintptr_t k1, uintptr_t k2);

	template<typename T, int off>
	T& NetvarOffset(uintptr_t tptr, unsigned int k1, unsigned int k2)
	{
		static int offset = SourceNetvars::GetOffset(k1, k2);
		return *(T*)(tptr + offset + off);
	}

}

#define NETVAR(t,n,k1,k2) t& n(){return SourceNetvars::NetvarOffset<t, 0>((uintptr_t)this, CCRC32(k1), CCRC32(k2));}
#define ONETVAR(t,n,k1,k2,o) t& n(){return SourceNetvars::NetvarOffset<t, o>((uintptr_t)this, CCRC32(k1), CCRC32(k2));}

#endif
