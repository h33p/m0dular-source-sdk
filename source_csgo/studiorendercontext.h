#ifndef STUDIORENDERCONTEXT_H
#define STUDIORENDERCONTEXT_H

struct LightDesc_t;
struct DrawModelResults_t;
struct StudioModelArrayInfo2_t;
struct StudioRenderConfig_t;
struct StudioArrayData_t;
struct GetTriangles_Output_t;
struct StudioModelArrayInfo_t;
struct StudioArrayInstanceData_t;
struct FlashlightState_t;
struct DrawModelInfo_t;
struct MeshInstanceData_t;
struct ColorMeshInfo_t;
class ITexture;
class IMaterial;

class IStudioRenderContext
{
public:
	virtual void Connect(void* (*)(char const*, int*)) = 0;
	virtual void Disconnect(void) = 0;
	virtual void QueryInterface(char const*) = 0;
	virtual void Init(void) = 0;
	virtual void Shutdown(void) = 0;
	virtual void GetDependencies(void) = 0;
	virtual void GetTier(void) = 0;
	virtual void Reconnect(void* (*)(char const*, int*), char const*) = 0;
	virtual bool IsSingleton(void) = 0;
	virtual void BeginFrame(void) = 0;
	virtual void EndFrame(void) = 0;
	virtual void Mat_Stub(IMaterialSystem*) = 0;
	virtual void UpdateConfig(StudioRenderConfig_t const&) = 0;
	virtual void GetCurrentConfig(StudioRenderConfig_t&) = 0;
	virtual void LoadModel(studiohdr_t*, void*, studiohwdata_t*) = 0;
	virtual void UnloadModel(studiohwdata_t*) = 0;
	virtual void RefreshStudioHdr(studiohdr_t*, studiohwdata_t*) = 0;
	virtual void SetEyeViewTarget(studiohdr_t const*, int, vec3 const&) = 0;
	virtual void GetNumAmbientLightSamples(void) = 0;
	virtual void GetAmbientLightDirections(void) = 0;
	virtual void SetAmbientLightColors(vec4_t const*) = 0;
	virtual void SetAmbientLightColors(vec3 const*) = 0;
	virtual void SetLocalLights(int, LightDesc_t const*) = 0;
	virtual void SetViewState(vec3 const&, vec3 const&, vec3 const&, vec3 const&) = 0;
	virtual void GetNumLODs(studiohwdata_t const&)const = 0;
	virtual void GetLODSwitchValue(studiohwdata_t const&, int)const = 0;
	virtual void SetLODSwitchValue(studiohwdata_t&, int, float) = 0;
	virtual void SetColorModulation(float const*) = 0;
	virtual void SetAlphaModulation(float) = 0;
	virtual void DrawModel(DrawModelResults_t*, DrawModelInfo_t const&, matrix3x4_t*, float*, float*, vec3 const&, int) = 0;
	virtual void DrawModelStaticProp(DrawModelInfo_t const&, matrix3x4_t const&, int) = 0;
	virtual void DrawStaticPropDecals(DrawModelInfo_t const&, matrix3x4_t const&) = 0;
	virtual void DrawStaticPropShadows(DrawModelInfo_t const&, matrix3x4_t const&, int) = 0;
	virtual void ForcedMaterialOverride(IMaterial*, OverrideType_t, int) = 0;
	virtual void IsForcedMaterialOverride(void) = 0;
	virtual void CreateDecalList(studiohwdata_t*) = 0;
	virtual void DestroyDecalList(StudioDecalHandle_t*) = 0;
	virtual void AddDecal(StudioDecalHandle_t*, studiohdr_t*, matrix3x4_t*, Ray_t const&, vec3 const&, IMaterial*, float, int, bool, int, void*, int) = 0;
	virtual void ComputeLighting(vec3 const*, int, LightDesc_t*, vec3 const&, vec3 const&, vec3&) = 0;
	virtual void ComputeLightingConstDirectional(vec3 const*, int, LightDesc_t*, vec3 const&, vec3 const&, vec3&, float) = 0;
	virtual void AddShadow(IMaterial*, void*, FlashlightState_t*, matrix3x4_t*, ITexture*) = 0;
	virtual void ClearAllShadows(void) = 0;
	virtual void ComputeModelLod(studiohwdata_t*, float, float*) = 0;
	virtual void GetPerfStats(DrawModelResults_t*, DrawModelInfo_t const&, CUtlBuffer*)const = 0;
	virtual void GetTriangles(DrawModelInfo_t const&, matrix3x4_t*, GetTriangles_Output_t&) = 0;
	virtual void GetMaterialList(studiohdr_t*, int, IMaterial**) = 0;
	virtual void GetMaterialListFromBodyAndSkin(unsigned short, int, int, int, IMaterial**) = 0;
	virtual void DrawModelArrayStaticProp(DrawModelInfo_t const&, int, MeshInstanceData_t const*, ColorMeshInfo_t**) = 0;
	virtual void DrawModelArray(StudioModelArrayInfo_t const&, int, StudioArrayInstanceData_t*, int, int) = 0;
	virtual void DrawModelShadowArray(int, StudioArrayData_t*, int, int) = 0;
	virtual void DrawModelArray(StudioModelArrayInfo2_t const&, int, StudioArrayData_t*, int, int) = 0;

	ONETVAR(IMaterial*, forcedMaterial, "", "", x64x32(0x258, 0x250));
	ONETVAR(IMaterial*, forcedMaterialType, "", "", x64x32(0x278, 0x260));
};


#endif