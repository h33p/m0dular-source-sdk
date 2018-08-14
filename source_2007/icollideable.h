#ifndef ICOLLIDEABLE_H
#define ICOLLIDEABLE_H

class IHandleEntity;
struct Ray_t;
struct model_t;
class CGameTrace;
typedef CGameTrace trace_t;
class IClientUnknown;

class ICollideable
{
  public:
	virtual IHandleEntity* GetEntityHandle() = 0;
	virtual const vec3& OBBMins() const = 0;
	virtual const vec3& OBBMaxs() const = 0;
	virtual void WorldSpaceTriggerBounds(vec3 *pVecWorldMins, vec3 *pVecWorldMaxs) const = 0;
	virtual bool TestCollision(const Ray_t &ray, unsigned int fContentsMask, trace_t& tr) = 0;
	virtual bool TestHitboxes(const Ray_t &ray, unsigned int fContentsMask, trace_t& tr) = 0;
	virtual int GetCollisionModelIndex() = 0;
	virtual const model_t* GetCollisionModel() = 0;
	virtual const vec3& GetCollisionOrigin() const = 0;
	virtual const vec3& GetCollisionAngles() const = 0;
	virtual const matrix3x4_t& CollisionToWorldTransform() const = 0;
	virtual int GetSolid() const = 0;
	virtual int GetSolidFlags() const = 0;
	virtual IClientUnknown* GetIClientUnknown() = 0;
	virtual int GetCollisionGroup() const = 0;
	virtual void WorldSpaceSurroundingBounds(vec3 *pVecMins, vec3 *pVecMaxs) = 0;
	virtual bool ShouldTouchTrigger(int triggerSolidFlags) const = 0;
	virtual const matrix3x4_t* GetRootParentToWorldTransform() const = 0;
};

#endif
