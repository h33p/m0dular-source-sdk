#ifndef DEBUGOVERLAY_H
#define DEBUGOVERLAY_H

class IVDebugOverlay
{
  public:
	void AddCapsuleOverlay(const vec3& mins, const vec3& max, float& diameter, int r, int g, int b, int a, float duration)
	{
		typedef void(__thiscall* OriginalFn)(void*, const vec3&, const vec3&, float&, int, int, int, int, float);
		return GetVFunc<OriginalFn, LWM(23, 24, 23)>(this)(this, mins, max, diameter, r, g, b, a, duration);
	}

	void AddCapsuleOverlay(const vec3& mins, const vec3& max, float& diameter, Color col, float duration)
	{
	    AddCapsuleOverlay(mins, max, diameter, col.r(), col.g(), col.b(), col.a(), duration);
	}

	void AddBoxOverlay(const vec3& origin, const vec3& mins, const vec3& max, const vec3& angles, int r, int g, int b, int a, float duration)
	{
		typedef void(__thiscall* OriginalFn)(void*, const vec3&, const vec3&, const vec3&, const vec3&, int, int, int, int, float);
		return GetVFunc<OriginalFn, LWM(1, 2, 1)>(this)(this, origin, mins, max, angles, r, g, b, a, duration);
	}

	void AddBoxOverlay(const vec3& origin, const vec3& mins, const vec3& max, const vec3& angles, Color col, float duration)
	{
	    AddBoxOverlay(origin, mins, max, angles, col.r(), col.g(), col.b(), col.a(), duration);
	}

	void AddBoxOverlay2(const vec3& origin, const vec3& mins, const vec3& max, const vec3& angles, Color faceCol, Color edgeCol, float duration)
	{
		typedef void(__thiscall* OriginalFn)(void*, const vec3&, const vec3&, const vec3&, const vec3&, const Color&, const Color&, float);
		return GetVFunc<OriginalFn, LWM(20, 21, 20)>(this)(this, origin, mins, max, angles, faceCol, edgeCol, duration);
	}

};


#endif
