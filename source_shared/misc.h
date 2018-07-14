#ifndef MISC_H
#define MISC_H

#define MY(a, b) a##b
#define MX(a, b) MY(a, b)

#define OFFSET(t, n, o) t& n() {return *(t*)((uintptr_t)this + o);}
#define OFFSET6432(t, n, o1, o2) OFFSET(t, n, x64x32(o1, o2))
#define PAD(o1) char MX(pad, __COUNTER__) [o1]
#define PAD6432(o1, o2) PAD(x64x32(o1, o2))

#define VFuncPosixWin(type, name, index_posix, index_win)				\
	type name () {														\
		typedef type(__thiscall* name##fn)(void*);						\
		return GetVFunc<name##fn, PosixWin(index_posix, index_win)>(this)(this); \
	}

#endif
