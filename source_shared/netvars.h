#ifndef NETVARS_H
#define NETVARS_H

#include <stdint.h>
#include "../framework/utils/crc32.h"

class CBaseClient;

namespace SourceNetvars
{
	void Initialize(CBaseClient* cl);
	int GetOffset(uintptr_t k1, uintptr_t k2);

	template<typename T, int off, unsigned int k1, unsigned int k2>
	T& NetvarOffset(uintptr_t tptr)
	{
		static int offset = SourceNetvars::GetOffset(k1, k2);
		return *(T*)(tptr + offset + off);
	}

}

#define ONETVAR(t,n,k1,k2,o) t& n(){return SourceNetvars::NetvarOffset<t, o, CCRC32(k1), CCRC32(k2)>((uintptr_t)this);}
#define NETVAR(t,n,k1,k2) ONETVAR(t,n,k1,k2,0)

#endif
