#ifndef PHYSICSSURFACEPROPS_H
#define PHYSICSSURFACEPROPS_H

struct surfacephysicsparams_t;
struct surfacedata_t;

class IPhysicsSurfaceProps
{
public:
	virtual ~IPhysicsSurfaceProps(void) {}
	virtual int ParseSurfaceData(const char* filename, const char* textfile) = 0;
	virtual int SurfacePropCount(void) const = 0;
	virtual int GetSurfaceIndex(const char* surfacePropName) const = 0;
	virtual void GetPhysicsProperties(int surfaceDataIndex, float* density, float* thickness, float* friction, float* elasticity) const = 0;
	virtual surfacedata_t* GetSurfaceData(int surfaceDataIndex) = 0;
	virtual const char* GetString(unsigned short stringTableIndex) const = 0;
	virtual const char* GetPropName(int surfaceDataIndex) const = 0;
	virtual void SetWorldMaterialIndexTable(int *mapArray, int mapSize) = 0;
	virtual void GetPhysicsParameters(int surfaceDataIndex, surfacephysicsparams_t* paramsOut) const = 0;
};

#endif
