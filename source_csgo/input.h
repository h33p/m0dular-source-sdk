#ifndef SOURCE_INPUT_H
#define SOURCE_INPUT_H

typedef void UNKRET;
struct CUserCmd;
class bf_write;
class bf_read;

static constexpr size_t MULTIPLAYER_BACKUP = 150;

class CInput
{
  public:
	virtual void Init_All(void) = 0;
	virtual void Shutdown_All(void) = 0;
	virtual int GetButtonBits(int) = 0;
	virtual void CreateMove(int sequenceNumber, float inputSampleFrametime, bool active) = 0;
	virtual void ExtraMouseSample(float frametime, bool active) = 0;
	virtual bool WriteUsercmdDeltaToBuffer(bf_write* buf, int from, int to, bool isNewCommand) = 0;
	virtual void EncodeUserCmdToBuffer(bf_write& buf, int slot) = 0;
	virtual void DecodeUserCmdFromBuffer(bf_read& buf, int slot) = 0;
	virtual UNKRET GetUserCmd(int, int) = 0;
	virtual UNKRET MakeWeaponSelection(void*) = 0;
	virtual UNKRET KeyState(void*) = 0;
	virtual UNKRET KeyEvent(int, int, const char*) = 0;
	virtual UNKRET FindKey(const char*) = 0;
	virtual UNKRET Contr9ollerCommands(void) = 0;
	virtual UNKRET ControllerModeActive(void) = 0;
	virtual UNKRET Joystick_Advanced(bool) = 0;
	virtual UNKRET Joystick_SetSampleTime(float) = 0;
	virtual UNKRET Joystick_GetPitch(void) = 0;
	virtual UNKRET Joystick_GetYaw(void) = 0;
	virtual UNKRET Joystick_Querry(float&, float&, float&, float&) = 0;
	virtual UNKRET Joystick_ForceRecentering(int, bool) = 0;
	virtual UNKRET IN_SetSampleTime(float) = 0;
	virtual UNKRET AccumulateMouse(int) = 0;
	virtual UNKRET ActivateMouse(void) = 0;
	virtual UNKRET DeactivateMouse(void) = 0;
	virtual UNKRET ClearStates(void) = 0;
	virtual UNKRET GetLookSpring(void) = 0;
	virtual UNKRET GetFullscreenMousePos(int*, int*, int*, int*) = 0;
	virtual UNKRET SetFullscreenMousePos(int, int) = 0;
	virtual UNKRET ResetMouse(void) = 0;
	virtual UNKRET GetLastForwardMove(void) = 0;
	virtual UNKRET CAM_Think(void) = 0;
	virtual bool CAM_IsThirdPerson(int) = 0;
	virtual UNKRET CAM_IsThirdPersonOverview(int) = 0;
	virtual UNKRET CAM_GetCameraOffset(vec3&) = 0;
	virtual UNKRET CAM_ToThirdPerson(void) = 0;
	virtual UNKRET CAM_ToFirstPerson(void) = 0;
	virtual UNKRET CAM_ToThirdPersonShoulder(void) = 0;
	virtual UNKRET CAM_ToThirdPersonOverview(void) = 0;
	virtual UNKRET CAM_StartMouseMove(void) = 0;

	inline CUserCmd* GetUserCmd(int sequenceNumber)
	{
		return commands + (sequenceNumber % MULTIPLAYER_BACKUP);
	}

	char pad1[0xac];
	bool cameraInterceptingMouse;
	bool cameraInThirdPerson;
	bool cameraMovingWithMouse;
	vec3 cameraOffset;
	bool cameraDistanceMove;
	int cameraOldX;
	int cameraOldY;
	int cameraX;
	int cameraY;
	bool cameraIsOrthographic;
	char pad2[0x14];
    void* pad3;
	CUserCmd* commands;
};

#endif
