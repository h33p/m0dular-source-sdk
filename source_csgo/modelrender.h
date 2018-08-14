#ifndef MODELRENDER_H
#define MODELRENDER_H

struct ModelRenderInfo_t
{
	vec3 origin;
	vec3 angles;
	void* unk;
	IClientRenderable* pRenderable;
	const model_t* pModel;
	const matrix3x4_t* pModelToWorld;
	const matrix3x4_t* pLightingOffset;
	const vec3* pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	ModelInstanceHandle_t instance;

	ModelRenderInfo_t()
	{
		pModelToWorld = NULL;
		pLightingOffset = NULL;
		pLightingOrigin = NULL;
	}
};

struct LightingQuery_t
{
	vec3 lightingOrigin;
	ModelInstanceHandle_t instanceHandle;
	bool ambientBoost;
};

struct StaticLightingQuery_t : public LightingQuery_t
{
	IClientRenderable* renderable;
};

class IMaterial
{
  public:
	virtual const char* GetName() const = 0;
	virtual const char* GetTextureGroupName() const = 0;
	virtual PreviewImageRetVal_t GetPreviewImageProperties(int *width, int *height, ImageFormat *imageFormat, bool* isTranslucent) const = 0;
	virtual PreviewImageRetVal_t GetPreviewImage(unsigned char *data, int width, int height, ImageFormat imageFormat) const = 0;
	virtual int GetMappingWidth() = 0;
	virtual int GetMappingHeight() = 0;
	virtual int GetNumAnimationFrames() = 0;
	virtual bool InMaterialPage(void) = 0;
	virtual void GetMaterialOffset(float *pOffset) = 0;
	virtual void GetMaterialScale(float *pScale) = 0;
	virtual IMaterial* GetMaterialPage(void) = 0;
	virtual IMaterialVar* FindVar(const char *varName, bool *found, bool complain = true) = 0;
	virtual void IncrementReferenceCount(void) = 0;
	virtual void DecrementReferenceCount(void) = 0;
	inline void AddRef() { IncrementReferenceCount(); }
	inline void Release() { DecrementReferenceCount(); }
	virtual int GetEnumerationID(void) const = 0;
	virtual void GetLowResColorSample(float s, float t, float *color) const = 0;
	virtual void RecomputeStateSnapshots() = 0;
	virtual bool IsTranslucent() = 0;
	virtual bool IsAlphaTested() = 0;
	virtual bool IsVertexLit() = 0;
	virtual VertexFormat_t GetVertexFormat() const = 0;
	virtual bool HasProxy(void) const = 0;
	virtual bool UsesEnvCubemap(void) = 0;
	virtual bool NeedsTangentSpace(void) = 0;
	virtual bool NeedsPowerOfTwoFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool NeedsFullFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool NeedsSoftwareSkinning(void) = 0;
	virtual void AlphaModulate(float alpha) = 0;
	virtual void ColorModulate(float r, float g, float b) = 0;
	virtual void SetMaterialVarFlag(MaterialVarFlags_t flag, bool on) = 0;
	virtual bool GetMaterialVarFlag(MaterialVarFlags_t flag) const = 0;
	virtual void GetReflectivity(vec3& reflect) = 0;
	virtual bool GetPropertyFlag(MaterialPropertyTypes_t type) = 0;
	virtual bool IsTwoSided() = 0;
	virtual void SetShader(const char *pShaderName) = 0;
	virtual int GetNumPasses(void) = 0;
	virtual int GetTextureMemoryBytes(void) = 0;
	virtual void Refresh() = 0;
	virtual bool NeedsLightmapBlendAlpha(void) = 0;
	virtual bool NeedsSoftwareLighting(void) = 0;
	virtual int ShaderParamCount() const = 0;
	virtual IMaterialVar** GetShaderParams(void) = 0;
	virtual bool IsErrorMaterial() const = 0;
	virtual void Unused() = 0;
	virtual float GetAlphaModulation() = 0;
	virtual void GetColorModulation(float *r, float *g, float *b) = 0;
	virtual bool IsTranslucentUnderModulation(float fAlphaModulation = 1.0f) const = 0;
	virtual IMaterialVar* FindVarFast(char const *pVarName, unsigned int *pToken) = 0;
	virtual void SetShaderAndParams(KeyValues *pKeyValues) = 0;
	virtual const char* GetShaderName() const = 0;
	virtual void DeleteIfUnreferenced() = 0;
	virtual bool IsSpriteCard() = 0;
	virtual void CallBindProxy(void *proxyData) = 0;
	virtual void RefreshPreservingMaterialVars() = 0;
	virtual bool WasReloadedFromWhitelist() = 0;
	virtual bool SetTempExcluded(bool bSet, int nExcludedDimensionLimit) = 0;
	virtual int GetReferenceCount() const = 0;
};

class IVModelRender
{
  public:
	virtual int DrawModel(int flags, IClientRenderable *pRenderable, ModelInstanceHandle_t instance, int entity_index, const model_t *model, vec3 const& origin, vec3 const& angles, int skin, int body, int hitboxset, const matrix3x4_t *modelToWorld = NULL, const matrix3x4_t *pLightingOffset = NULL) = 0;
	virtual void ForcedMaterialOverride(IMaterial *newMaterial, OverrideType_t nOverrideType = 0, int nOverrides = 0) = 0;
	virtual bool IsForcedMaterialOverride(void) = 0;
	virtual void SetViewTarget(const CStudioHdr *pStudioHdr, int nBodyIndex, const vec3& target) = 0;
	virtual ModelInstanceHandle_t CreateInstance(IClientRenderable *pRenderable, LightCacheHandle_t *pCache = NULL) = 0;
	virtual void DestroyInstance(ModelInstanceHandle_t handle) = 0;
	virtual void SetStaticLighting(ModelInstanceHandle_t handle, LightCacheHandle_t* pHandle) = 0;
	virtual LightCacheHandle_t GetStaticLighting(ModelInstanceHandle_t handle) = 0;
	virtual bool ChangeInstance(ModelInstanceHandle_t handle, IClientRenderable *pRenderable) = 0;
	virtual void AddDecal(ModelInstanceHandle_t handle, Ray_t const& ray, vec3 const& decalUp, int decalIndex, int body, bool noPokeThru, int maxLODToDecal) = 0;
	virtual void RemoveAllDecals(ModelInstanceHandle_t handle) = 0;
	virtual bool ModelHasDecals(ModelInstanceHandle_t handle) = 0;
	virtual void RemoveAllDecalsFromAllModels() = 0;
	virtual matrix3x4_t* DrawModelShadowSetup(IClientRenderable *pRenderable, int body, int skin, DrawModelInfo_t *pInfo, matrix3x4_t *pCustomBoneToWorld = NULL) = 0;
	virtual void DrawModelShadow(IClientRenderable *pRenderable, const DrawModelInfo_t &info, matrix3x4_t *pCustomBoneToWorld = NULL) = 0;
	virtual bool RecomputeStaticLighting(ModelInstanceHandle_t handle) = 0;
	virtual void ReleaseAllStaticPropColorData(void) = 0;
	virtual void RestoreAllStaticPropColorData(void) = 0;
	virtual int DrawModelEx(ModelRenderInfo_t &pInfo) = 0;
	virtual int DrawModelExStaticProp(ModelRenderInfo_t &pInfo) = 0;
	virtual bool DrawModelSetup(ModelRenderInfo_t &pInfo, DrawModelState_t *pState, matrix3x4_t **ppBoneToWorldOut) = 0;
	virtual void DrawModelExecute(IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld = NULL) = 0;
	virtual void SetupLighting(const vec3 &vecCenter) = 0;
	virtual int DrawStaticPropArrayFast(StaticPropRenderInfo_t *pProps, int count, bool bShadowDepth) = 0;
	virtual void SuppressEngineLighting(bool bSuppress) = 0;
	virtual void SetupColorMeshes(int nTotalVerts) = 0;
	virtual void SetupLightingEx(const vec3 &vecCenter, ModelInstanceHandle_t handle) = 0;
	virtual bool GetBrightestShadowingLightSource(const vec3 &vecCenter, vec3& lightPos, vec3& lightBrightness, bool bAllowNonTaggedLights) = 0;
	virtual void ComputeLightingState(int nCount, const LightingQuery_t *pQuery, MaterialLightingState_t *pState, ITexture **ppEnvCubemapTexture) = 0;
	virtual void GetModelDecalHandles(StudioDecalHandle_t *pDecals, int nDecalStride, int nCount, const ModelInstanceHandle_t *pHandles) = 0;
	virtual void ComputeStaticLightingState(int nCount, const StaticLightingQuery_t *pQuery, MaterialLightingState_t *pState, MaterialLightingState_t *pDecalState, ColorMeshInfo_t **ppStaticLighting, ITexture **ppEnvCubemapTexture, DataCacheHandle_t *pColorMeshHandles) = 0;
	virtual void CleanupStaticLightingState(int nCount, DataCacheHandle_t *pColorMeshHandles) = 0;
};

#endif
