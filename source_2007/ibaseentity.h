#ifndef IBASEENTITY_H
#define IBASEENTITY_H

#include "iclientunknown.h"

class ITraceFilter;
class FireBulletsInfo_t;

class IBaseEntity : public IClientUnknown
{
  public:
	virtual vec3 GetAbsOrigin() = 0;
	virtual vec3 GetAbsAngles() = 0;
    virtual void GetMouth_() = 0;
    virtual void GetSoundSpatialization_() = 0;
    virtual void GetDataDescMap_() = 0;
    virtual void YouForgotToImplementOrDeclareClientClass_() = 0;
    virtual void GetClientClass_() = 0;
    virtual void GetPredDescMap_() = 0;
	virtual void FireBullets(const FireBulletsInfo_t &info) = 0;
	virtual void ModifyFireBulletsDamage_() = 0;
	virtual bool ShouldDrawUnderwaterBulletBubbles() = 0;
	virtual bool ShouldDrawWaterImpacts() = 0;
	virtual bool HandleShotImpactingWater(const FireBulletsInfo_t &info, const vec3 &vecEnd, ITraceFilter *pTraceFilter, vec3 *pVecTracerDest) = 0;
	virtual void GetBeamTraceFilter_() = 0;
	virtual void DispatchTraceAttack(const void* info, const vec3 &vecDir, trace_t *ptr) = 0;
	virtual void TraceAttack(const void* info, const vec3 &vecDir, trace_t *ptr) = 0;
	virtual void DoImpactEffect(trace_t &tr, int nDamageType) = 0;
	virtual void MakeTracer(const vec3 &vecTracerSrc, const trace_t &tr, int iTracerType) = 0;
	virtual void GetTracerAttachment_() = 0;
	virtual int BloodColor() = 0;
	virtual const char* GetTracerType() = 0;
	virtual void Spawn() = 0;
	virtual void SpawnClientEntity() = 0;
	virtual void Precache() = 0;
	virtual void Activate() = 0;
	virtual void ParseMapData(void* mapData) = 0;
	virtual bool KeyValue(const char *szKeyName, const char *szValue) = 0;
	virtual bool KeyValue(const char *szKeyName, float flValue) = 0;
	virtual bool KeyValue(const char *szKeyName, vec3 vec) = 0;
	virtual void* GetKeyValue_() = 0;
};


#endif
