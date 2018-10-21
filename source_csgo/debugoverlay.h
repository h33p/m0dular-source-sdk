#ifndef DEBUGOVERLAY_H
#define DEBUGOVERLAY_H

class IVDebugOverlay
{
  public:
	void DrawPill(const vec3& mins, const vec3& max, float& diameter, int r, int g, int b, int a, float duration)
	{
		typedef void(__thiscall* OriginalFn)(void*, const vec3&, const vec3&, float&, int, int, int, int, float);
		return GetVFunc<OriginalFn, LWM(23, 24, 23)>(this)(this, mins, max, diameter, r, g, b, a, duration);
	}

	void DrawPill(const vec3& mins, const vec3& max, float& diameter, Color col, float duration)
	{
	    DrawPill(mins, max, diameter, col.r(), col.g(), col.b(), col.a(), duration);
	}
};


#endif
