#ifndef IBASEENTITY_H
#define IBASEENTITY_H

#include "iclientunknown.h"

class ITraceFilter;
class FireBulletsInfo_t;

class IBaseEntity : public IClientUnknown
{
  public:
	virtual vec3 GetAbsOrigin() {};
	virtual vec3 GetAbsAngles() {};
    virtual void GetMouth_() {};
    virtual void GetSoundSpatialization_() {};
    virtual void GetDataDescMap_() {};
    virtual void YouForgotToImplementOrDeclareClientClass_() {};
    virtual void GetClientClass_() {};
    virtual void GetPredDescMap_() {};
	virtual void FireBullets(const FireBulletsInfo_t &info) {};
	virtual void ModifyFireBulletsDamage_() {};
	virtual bool ShouldDrawUnderwaterBulletBubbles() {};
	virtual bool ShouldDrawWaterImpacts() {};
	virtual bool HandleShotImpactingWater(const FireBulletsInfo_t &info, const vec3 &vecEnd, ITraceFilter *pTraceFilter, vec3 *pVecTracerDest) {};
	virtual void GetBeamTraceFilter_() {};
	virtual void DispatchTraceAttack(const void* info, const vec3 &vecDir, trace_t *ptr) {};
	virtual void TraceAttack(const void* info, const vec3 &vecDir, trace_t *ptr) {};
	virtual void DoImpactEffect(trace_t &tr, int nDamageType) {};
	virtual void MakeTracer(const vec3 &vecTracerSrc, const trace_t &tr, int iTracerType) {};
	virtual void GetTracerAttachment_() {};
	virtual int BloodColor() {};
	virtual const char* GetTracerType() {};
	virtual void Spawn() {};
	virtual void SpawnClientEntity() {};
	virtual void Precache() {};
	virtual void Activate() {};
	virtual void ParseMapData(void* mapData) {};
	virtual bool KeyValue(const char *szKeyName, const char *szValue) {};
	virtual bool KeyValue(const char *szKeyName, float flValue) {};
	virtual bool KeyValue(const char *szKeyName, vec3 vec) {};
	virtual void* GetKeyValue_() {};
};


#endif
