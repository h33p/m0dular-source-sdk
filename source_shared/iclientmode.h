#ifndef ICLIENTMODE_H
#define ICLIENTMODE_H

class IPanel;
class C_BaseEntity;
class CViewSetup;

class IClientMode
{
  public:
	virtual ~IClientMode() {}
	virtual int ClientModeCSNormal(void*) = 0;
	virtual void Init() = 0;
	virtual void InitViewport() = 0;
	virtual void Shutdown() = 0;
	virtual void Enable() = 0;
	virtual void Disable() = 0;
	virtual void Layout() = 0;
	virtual IPanel* GetViewport() = 0;
	virtual void* GetViewportAnimationController() = 0;
	virtual void ProcessInput(bool bActive) = 0;
	virtual bool ShouldDrawDetailObjects() = 0;
	virtual bool ShouldDrawEntity(C_BaseEntity* pEnt) = 0;
	virtual bool ShouldDrawLocalPlayer(C_BaseEntity* pPlayer) = 0;
	virtual bool ShouldDrawParticles() = 0;
	virtual bool ShouldDrawFog(void) = 0;
	virtual void OverrideView(CViewSetup* pSetup) = 0;
	virtual int KeyInput(int down, int keynum, const char* pszCurrentBinding) = 0;
	virtual void StartMessageMode(int iMessageModeType) = 0;
	virtual IPanel* GetMessagePanel() = 0;
	virtual void OverrideMouseInput(float* x, float* y) = 0;
	virtual bool CreateMove(float flInputSampleTime, void* usercmd) = 0;
	virtual void LevelInit(const char* newmap) = 0;
	virtual void LevelShutdown(void) = 0;
};

#endif
