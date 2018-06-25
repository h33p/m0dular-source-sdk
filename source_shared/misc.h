#ifndef MISC_H
#define MISC_H

#define OFFSET(t, n, o) t& n() {return *(t*)((uintptr_t)this + o);}
#define OFFSET6432(t, n, o1, o2) OFFSET(t, n, x64x32(o1, o2))

#define VFuncPosixWin(type, name, index_posix, index_win)				\
	type name () {														\
		typedef type(__thiscall* name##fn)(void*);						\
		return GetVFunc<name##fn, PosixWin(index_posix, index_win)>(this)(this); \
	}

#endif
