#ifndef MISC_H
#define MISC_H

#define OFFSET(t, n, o) t& n() {return *(t*)((uintptr_t)this + o);}

#endif
