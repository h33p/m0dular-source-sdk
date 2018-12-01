#ifndef SPATIALPARTITION_H
#define SPATIALPARTITION_H

typedef void* IPartitionQueryCallback;

#include "ienginetrace.h"

class CSpatialPartition
{
  public:
	virtual void CreateHandle(IHandleEntity *) = 0;
	virtual void CreateHandle(IHandleEntity *, int, vec3 const&, vec3 const&) = 0;
	virtual void DestroyHandle(unsigned short) = 0;
	virtual void Insert(int, unsigned short) = 0;
	virtual void Remove(int, unsigned short) = 0;
	virtual void RemoveAndInsert(int, int, unsigned short) = 0;
	virtual void Remove(unsigned short) = 0;
	virtual void ElementMoved(unsigned short, vec3 const&, vec3 const&) = 0;
	virtual void HideElement(unsigned short) = 0;
	virtual void UnhideElement(unsigned short, int) = 0;
	virtual void InstallQueryCallback(IPartitionQueryCallback*) = 0;
	virtual void RemoveQueryCallback(IPartitionQueryCallback*) = 0;
	virtual void EnumerateElementsInBox(int,vec3 const&, vec3 const&, bool, IEntityEnumerator*) = 0;
	virtual void EnumerateElementsInSphere(int, vec3 const&, float, bool, IEntityEnumerator*) = 0;
	virtual void EnumerateElementsAlongRay(int, Ray_t const&, bool, IEntityEnumerator*) = 0;
	virtual void EnumerateElementsAtPoint(int, vec3 const&, bool, IEntityEnumerator*) = 0;
};

#endif
