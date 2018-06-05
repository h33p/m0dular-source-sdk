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
	bool bForceClearWholeRenderTarget;
	bool m_bOrtho;			
	float m_OrthoLeft;		
	float m_OrthoTop;
	float m_OrthoRight;
	float m_OrthoBottom;
	float fov;				
	float fovViewmodel;		
	vec3 origin;					
	vec3 m_vUnreflectedOrigin;																			
	vec3 angles;				
	float zNear;			
	float zFar;			
	float zNearViewmodel;		
	float zFarViewmodel;		
	bool m_bForceAspectRatio1To1;
	bool m_bRenderToSubrectOfLargerScreen;
	bool m_bUseRenderTargetAspectRatio;
};

#endif
