#ifndef ICLIENTRENDERABLE_H
#define ICLIENTRENDERABLE_H

typedef unsigned short ClientShadowHandle_t;
typedef unsigned short ClientRenderHandle_t;
typedef unsigned short ModelInstanceHandle_t;
typedef unsigned char uint8_t;

class IClientUnknown;
class IBaseEntity;
struct model_t;

#include "ibaseentity.h"

class IClientRenderable
{
  public:

	virtual IClientUnknown* GetIClientUnknown() {};
	virtual vec3 const& GetRenderOrigin(void) {};
	virtual vec3 const& GetRenderAngles(void) {};
	virtual bool ShouldDraw(void) {};
	virtual void* IsTransparent_() {};
	virtual void* UsesPowerOfTwoFrameBufferTexture_() {};
	virtual void* UsesFullFrameBufferTexture_() {};
	virtual ClientShadowHandle_t GetShadowHandle() const {};
	virtual ClientRenderHandle_t& RenderHandle() {};
	virtual const model_t* GetModel() const {};
	virtual int DrawModel(int flags, const int /*RenderableInstance_t*/ &instance) {};
	virtual int GetBody() {};
	virtual void ComputeFxBlend_() {};
	virtual void* GetFxBlend_() {};
	virtual void GetColorModulation(float* color) {};
	virtual bool LODTest() {};
	virtual bool SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) {};
	virtual void SetupWeights(const matrix3x4_t *pBoneToWorld, int nFlexWeightCount, float *pFlexWeights, float *pFlexDelayedWeights) {};
	virtual void DoAnimationEvents(void) {};
	virtual void* /*IPVSNotify*/ GetPVSNotifyInterface() {};
	virtual void GetRenderBounds(vec3& mins, vec3& maxs) {};
	virtual void GetRenderBoundsWorldspace(vec3& mins, vec3& maxs) {};
	virtual void GetShadowRenderBounds(vec3 &mins, vec3 &maxs, int /*ShadowType_t*/ shadowType) {};
	virtual bool ShouldReceiveProjectedTextures(int flags) {};
	virtual bool GetShadowCastDistance(float* pDist, int /*ShadowType_t*/ shadowType) const {};
	virtual bool GetShadowCastDirection(vec3* pDirection, int /*ShadowType_t*/ shadowType) const {};
	virtual bool IsShadowDirty() {};
	virtual void MarkShadowDirty(bool bDirty) {};
	virtual IClientRenderable* GetShadowParent() {};
	virtual IClientRenderable* FirstShadowChild() {};
	virtual IClientRenderable* NextShadowPeer() {};
	virtual int /*ShadowType_t*/ ShadowCastType() {};
	virtual void CreateModelInstance() {};
	virtual ModelInstanceHandle_t GetModelInstance() {};
	virtual const matrix3x4_t& RenderableToWorldTransform() {};
	virtual int LookupAttachment(const char *pAttachmentName) {};
	virtual bool GetAttachment(int number, vec3 &origin, vec3 &angles) {};
	virtual bool GetAttachment(int number, matrix3x4_t &matrix) {};
	virtual float* GetRenderClipPlane(void) {};
	virtual int GetSkin() {};
	virtual bool IsTwoPass() {};
	virtual void OnThreadedDrawSetup() {};
	virtual bool UsesFlexDelayedWeights() {};
	virtual void RecordToolMessage() {};
	virtual bool IgnoresZBuffer() {};
};

#endif
