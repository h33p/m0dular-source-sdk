#ifndef SOURCEINTERFACES_H
#define SOURCEINTERFACES_H

#include "../framework/utils/rstring.h"
#include "../framework/utils/handles.h"
#include "../framework/utils/memutils.h"
#include "../framework/utils/stackstring.h"
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

extern InterfaceReg** GetInterfaceRegs(MHandle library);

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

	InterfaceReg** interfaceRegs = GetInterfaceRegs(library);

	return GetInterface<T>(interfaceRegs, name, exact);
}

inline void FindAllInterfaces(const InterfaceDefinition* interfaces, int count)
{
	for (int i = 0; i < count; i++)
		interfaces[i].reference = GetInterface<void*>(interfaces[i].module, interfaces[i].name, interfaces[i].exact);
}

#endif
