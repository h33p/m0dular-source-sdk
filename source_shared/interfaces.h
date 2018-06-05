#ifndef SOURCEINTERFACES_H
#define SOURCEINTERFACES_H

#include "../sdk/framework/utils/rstring.h"
#include "../sdk/framework/utils/handles.h"
#include "../sdk/framework/utils/memutils.h"
#include "string.h"

#if defined(__linux__) || defined(__APPLE__)
#include <dlfcn.h>
#endif

typedef void* (*InstantiateInterfaceFn)();

struct InterfaceReg
{
	InstantiateInterfaceFn createFn;
	const char* name;
	InterfaceReg* next;
};

struct InterfaceDefinition
{
	void*& reference;
	const char* module;
	const char* name;
	bool exact;
};

template<typename T>
T GetInterface(InterfaceReg** interfaceRegs, const char* name, bool exact = false)
{
	int len = strlen(name);
	for (InterfaceReg* interface = *interfaceRegs; interface; interface = interface->next)
		if (exact ? (!rstrcmp(interface->name, name)) : (strstr(interface->name, name) && strlen(interface->name) - len == 3))
			return (T)interface->createFn();
	return nullptr;
}

template<typename T>
T GetInterface(const char* module, const char* name, bool exact = false)
{
	MHandle library = Handles::GetModuleHandle(module);

	if (!library)
		return nullptr;

	InterfaceReg** interfaceRegs = nullptr;

#if defined(__linux__) || defined(__APPLE__)
	interfaceRegs = (InterfaceReg**)dlsym(library, "s_pInterfaceRegs");
#elif defined(_WIN32)
	uintptr_t jmp = (uintptr_t)GetProcAddress(library, "CreateInterface") + 4;
	interfaceRegs = *(InterfaceReg***)(GetAbsoluteAddress(jmp, 1, 5) + 6);
#endif

	return GetInterface<T>(interfaceRegs, name, exact);
}

inline void FindAllInterfaces(const InterfaceDefinition* interfaces, int count)
{
	for (int i = 0; i < count; i++)
		interfaces[i].reference = GetInterface<void*>(interfaces[i].module, interfaces[i].name, interfaces[i].exact);
}

#endif