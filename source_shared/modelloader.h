#ifndef MODELLOADER_H
#define MODELLOADER_H

struct model_t;
class IMaterial;
class IFileList;

enum REFERENCETYPE
{
	// The name is allocated, but nothing else is in memory or being referenced
	FMODELLOADER_NOTLOADEDORREFERENCED = 0,
	// The model has been loaded into memory
	FMODELLOADER_LOADED     = (1<<0),
	// The model is being referenced by the server code
	FMODELLOADER_SERVER = (1<<1),
	// The model is being referenced by the client code
	FMODELLOADER_CLIENT = (1<<2),
	// The model is being referenced in the client .dll
	FMODELLOADER_CLIENTDLL = (1<<3),
	// The model is being referenced by static props
	FMODELLOADER_STATICPROP = (1<<4),
	// The model is a detail prop
	FMODELLOADER_DETAILPROP = (1<<5),
	FMODELLOADER_REFERENCEMASK = (FMODELLOADER_SERVER | FMODELLOADER_CLIENT | FMODELLOADER_CLIENTDLL | FMODELLOADER_STATICPROP | FMODELLOADER_DETAILPROP),
	// The model was touched by the preload method
	FMODELLOADER_TOUCHED_BY_PRELOAD = (1<<15),
	// The model was loaded by the preload method, a postload fixup is required
	FMODELLOADER_LOADED_BY_PRELOAD = (1<<16),
	// The model touched its materials as part of its load
	FMODELLOADER_TOUCHED_MATERIALS = (1<<17),
};

enum ReloadType_t
{
	RELOAD_LOD_CHANGED = 0,
	RELOAD_EVERYTHING,
	RELOAD_REFRESH_MODELS,
};

class IModelLoader
{
  public:
	virtual void Init(void) = 0;
	virtual void Shutdown(void) = 0;
	virtual int GetCount( void ) = 0;
	virtual model_t* GetModelForIndex(int i) = 0;
	virtual const char* GetName(const model_t* model) = 0;
	virtual void* GetExtraData(model_t* model) = 0;
	virtual int GetModelFileSize(const char* name) = 0;
	virtual model_t* GetModelForName(const char* name, REFERENCETYPE referencetype) = 0;
	virtual model_t* ReferenceModel(const char* name, REFERENCETYPE referencetype) = 0;
	virtual void UnreferenceModel(model_t* model, REFERENCETYPE referencetype) = 0;
	virtual void UnreferenceAllModels(REFERENCETYPE referencetype) = 0;
	virtual void UnloadUnreferencedModels(void) = 0;
	virtual void PurgeUnusedModels(void) = 0;
	virtual bool Map_GetRenderInfoAllocated(void) = 0;
	virtual void Map_SetRenderInfoAllocated(bool allocated) = 0;
	virtual void Map_LoadDisplacements(model_t* model, bool bRestoring) = 0;
	virtual void Print(void) = 0;
	virtual bool Map_IsValid(char const* mapname) = 0;
	virtual void RecomputeSurfaceFlags(model_t* mod) = 0;
	virtual void Studio_ReloadModels(ReloadType_t reloadType) = 0;
	virtual bool IsLoaded(const model_t* mod) = 0;
	virtual bool LastLoadedMapHasHDRLighting(void) = 0;
	virtual void ReloadFilesInList(IFileList* pFilesToReload) = 0;
	virtual const char *GetActiveMapName(void) = 0;
};

#endif
