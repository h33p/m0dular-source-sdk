#ifndef MDLCACHE_H
#define MDLCACHE_H

//TODO: possibly check how the interface is laid out on different source games and determine whether or not the definition should be shared
//TODO: prepare the interface for CSGO (SetCacheNotify is repeated, some functions are out of place, as Only BeginLock and EndLock were of the interest)

class studiohdr_t;
struct virtualmodel_t;

typedef void* IMDLCacheNotify;
typedef void* MDLCacheDataType_t;
typedef void* MDLCacheFlush_t;
typedef void* vertexFileHeader_t;

#include "appsystem.h"
#include "studio.h"
#include "ienginetrace.h"

class IMDLCache
{
  public:
	virtual bool Connect(CreateInterfaceFn factory) = 0;
	virtual void Disconnect() = 0;
	virtual void* QueryInterface(const char* interfaceName) = 0;
	virtual InitReturnVal_t Init() = 0;
	virtual void Shutdown() = 0;
#ifdef SOURCE_CSGO_SDK
	virtual void GetDependencies(void) = 0;
	virtual void GetTier(void) = 0;
	virtual void Reconnect(CreateInterfaceFn factory, char const* version) = 0;
	virtual bool IsSingleton(void) = 0;
	virtual void SetCacheNotify_(IMDLCacheNotify* notify) = 0;
#endif
	virtual MDLHandle_t FindMDL(const char* MDLRelativePath) = 0;
	virtual int AddRef(MDLHandle_t handle) = 0;
	virtual int Release(MDLHandle_t handle) = 0;
	virtual int GetRef(MDLHandle_t handle) = 0;
#ifndef SOURCE_CSGO_SDK
	virtual void MarkAsLoaded(MDLHandle_t handle) = 0;
#endif
	virtual studiohdr_t* GetStudioHdr(MDLHandle_t handle) = 0;
	virtual studiohwdata_t* GetHardwareData(MDLHandle_t handle) = 0;
	virtual vcollide_t* GetVCollide(MDLHandle_t handle) = 0;
	virtual vcollide_t* GetVCollideEx(MDLHandle_t handle, bool synchronousLoad) = 0;
	virtual unsigned char* GetAnimBlock(MDLHandle_t handle, int block) = 0;
#ifdef SOURCE_CSGO_SDK
	virtual bool HasAnimBlockBeenPreloaded(unsigned short,int) = 0;
#endif
	virtual virtualmodel_t* GetVirtualModel(MDLHandle_t handle) = 0;
	virtual virtualmodel_t* GetVirtualModelFast(const studiohdr_t* studiohdr, MDLHandle_t handle) = 0;
	virtual int GetAutoplayList(MDLHandle_t handle, unsigned short **out) = 0;
	virtual void TouchAllData(MDLHandle_t handle) = 0;
	virtual void SetUserData(MDLHandle_t handle, void* data) = 0;
	virtual void* GetUserData(MDLHandle_t handle) = 0;
	virtual bool IsErrorModel(MDLHandle_t handle) = 0;
#ifdef SOURCE_CSGO_SDK
	virtual bool IsOverBudget(unsigned short) = 0;
#endif
	virtual void SetCacheNotify(IMDLCacheNotify* notify) = 0;
	virtual vertexFileHeader_t* GetVertexData(MDLHandle_t handle) = 0;
	virtual void Flush(MDLCacheFlush_t flushFlags) = 0;
	virtual void Flush(MDLHandle_t handle, int flushFlags) = 0;
	virtual const char* GetModelName(MDLHandle_t handle) = 0;
	virtual void BeginLock() = 0;
	virtual void EndLock() = 0;
	virtual int* GetFrameUnlockCounterPtrOLD() = 0;
	virtual int* GetFrameUnlockCounterPtr(MDLCacheDataType_t type) = 0;
	virtual void FinishPendingLoads() = 0;
};

#endif
