#ifndef VIEW_SHARED
#define VIEW_SHARED
class CViewSetup
{
  public:
	int x;
	int x_old;
	int y;
	int y_old;
	int width;
	int width_old;
	int height;
	int height_old;
	char pad_0x0020[x64x32(0x98, 0x90)];
	float fov;
	float viewmodel_fov;
	vec3 origin;
	vec3 angles;
	float zNear;
	float zFar;
	float zNearViewmodel;
	float zFarViewmodel;
	float aspectRatio;
	float nearBlurDepth;
	float nearFocusDepth;
	float farFocusDepth;
	float farBlurDepth;
	float nearBlurRadius;
	float farBlurRadius;
	float doFQuality;
	int motionBlurMode;
};
#endif
