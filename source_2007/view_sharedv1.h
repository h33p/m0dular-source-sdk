#ifndef VIEW_SHARED
#define VIEW_SHARED

class CViewSetup
{
public:
	int context;
	int x;
	int y;
	int width;
	int height;
	bool clearColor;
	bool clearDepth;
	bool forceClearWholeRenderTarget;
	bool ortho;
	float orthoLeft;
	float orthoTop;
	float orthoRight;
	float orthoBottom;
	float fov;
	float fovViewmodel;
	vec3 origin;
	vec3 unreflectedOrigin;
	vec3 angles;
	float zNear;
	float zFar;
	float zNearViewmodel;
	float zFarViewmodel;
	bool forceAspectRatio1To1;
	bool renderToSubrectOfLargerScreen;
	bool useRenderTargetAspectRatio;
};

#endif
