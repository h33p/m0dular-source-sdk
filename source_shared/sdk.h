#ifndef SOURCE_SHARED_SDK_H
#define SOURCE_SHARED_SDK_H

/*
 * This is the base SDK for all Source Engine games.
 * All the contents inside this directory should be backwards compatible to Source 2007.
 * Other games may need some changes and thus everything has to be defined in their respective directory.
 * For example, CSGO has some changes to the interfaces and structures, thus you would include source_csgo/sdk.h
 * instead of this one.
*/

#include "../framework/utils/memutils.h"
#include "../framework/g_defines.h"

#include "misc.h"
#include "types.h"
#include "enums.h"
#include "utlvector.h"
#include "utlmemory.h"
#include "recv.h"
#include "usercmd.h"
#include "prediction.h"
#include "inetchannelinfo.h"
#include "globalvars.h"
#include "clientclass.h"
#include "appsystem.h"
#include "iclientmode.h"
#include "baseclient.h"
#include "ihandleentity.h"
#include "basehandle.h"
#include "icliententitylist.h"
#include "iclientunknown.h"
#include "iclientthinkable.h"
#include "icliententity.h"
#include "iclientrenderable.h"
#include "iclientnetworkable.h"
#include "icollideable.h"
#include "varmapping.h"
#include "baseentity.h"
#include "interfaces.h"
#include "netvars.h"
#include "iconvar.h"
#include "convar.h"
#include "cvar.h"
#include "color.h"

#endif
