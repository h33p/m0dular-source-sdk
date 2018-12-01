#ifndef VOXELTREE_H
#define VOXELTREE_H

class CSpatialPartition;
struct Ray_t;
class IEntityEnumerator;

class CVoxelTree
{
public:
	virtual ~CVoxelTree() {};
	virtual void Init(CSpatialPartition* owner, int tree, const vec3& worldmin, const vec3& worldmax) = 0;
	virtual void ElementMoved(unsigned short handle, const vec3& mins, const vec3& maxs) = 0;
	virtual void EnumerateElementsInBox(unsigned int listMask, const vec3& mins, const vec3& maxs, bool coarseTest, IEntityEnumerator* iterator) = 0;
	virtual void EnumerateElementsInSphere(unsigned int listMask, const vec3& origin, float radius, bool coarseTest, IEntityEnumerator* iterator) = 0;
	virtual void EnumerateElementsAlongRay(unsigned int listMask, const Ray_t& ray, bool coarseTest, IEntityEnumerator* iterator) = 0;
	virtual void EnumerateElementsAtPoint(unsigned int listMask, const vec3& pt, bool coarseTest, IEntityEnumerator* iterator) = 0;
	virtual void RenderAllObjectsInTree(float time) = 0;
	virtual void RenderObjectsInPlayerLeafs(const vec3& playerMin, const vec3& playerMax, float time) = 0;
	virtual void ReportStats(const char* fileName) = 0;
	virtual void DrawDebugOverlays() = 0;
};

#endif
