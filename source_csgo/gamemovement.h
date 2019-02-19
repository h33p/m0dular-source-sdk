#ifndef SOURCE_SDK_GAMEMOVEMENT_H
#define SOURCE_SDK_GAMEMOVEMENT_H

class C_BasePlayer;
class C_BaseEntity;
class CMoveData;
class CGameTrace;

class CSGameMovement
{
public:
	virtual ~CSGameMovement() {}
	virtual void Destr2() = 0;
	virtual void ProcessMovement(C_BasePlayer*, CMoveData*) = 0;
	virtual void Reset(void) = 0;
	virtual void StartTrackPredictionErrors(C_BasePlayer*) = 0;
	virtual void FinishTrackPredictionErrors(C_BasePlayer*) = 0;
	virtual void DiffPrint(char const*, ...) = 0;
	virtual void GetPlayerMins(bool) const = 0;
	virtual void GetPlayerMaxs(bool) const = 0;
	virtual void GetPlayerViewOffset(bool) const = 0;
	virtual void IsMovingPlayerStuck(void) const = 0;
	virtual void GetMovingPlayer(void) const = 0;
	virtual void UnblockPusher(C_BasePlayer*, C_BaseEntity*) = 0;
	virtual void SetupMovementBounds(CMoveData*) = 0;
	virtual void TracePlayerBBox(vec3 const&, vec3 const&, unsigned int, int, CGameTrace&) = 0;
	virtual void PlayerSolidMask(bool, C_BasePlayer*) const = 0;
	virtual void PlayerMove(void) = 0;
	virtual void CalcRoll(vec3 const&, vec3 const&, float, float) = 0;
	virtual void DecayViewPunchAngle(void) = 0;
	virtual void CheckWaterJump(void) = 0;
	virtual void WaterMove(void) = 0;
	virtual void WaterJump(void) = 0;
	virtual void Friction(void) = 0;
	virtual void AirAccelerate(vec3&, float, float) = 0;
	virtual void AirMove(void) = 0;
	virtual void CanAccelerate(void) = 0;
	virtual void Accelerate(vec3&, float, float) = 0;
	virtual void WalkMove(void) = 0;
	virtual void StayOnGround(void) = 0;
	virtual void FullWalkMove(void) = 0;
	virtual void OnJump(float) = 0;
	virtual void OnLand(float) = 0;
	virtual void OnTryPlayerMoveCollision(CGameTrace&) = 0;
	virtual void GetPlayerMins(void) const = 0;
	virtual void GetPlayerMaxs(void) const = 0;
	virtual void GetCheckInterval(int) = 0;
	virtual void StartGravity(void) = 0;
	virtual void FinishGravity(void) = 0;
	virtual void AddGravity(void) = 0;
	virtual void CheckJumpButton(void) = 0;
	virtual void FullTossMove(void) = 0;
	virtual void FullLadderMove(void) = 0;
	virtual void TryPlayerMove(vec3*, CGameTrace*) = 0;
	virtual void LadderMove(void) = 0;
	virtual void OnLadder(CGameTrace&) = 0;
	virtual void LadderDistance(void) const = 0;
	virtual void LadderMask(void) const = 0;
	virtual void ClimbSpeed(void) const = 0;
	virtual void LadderLateralMultiplier(void) const = 0;
	virtual void ClipVelocity(vec3&, vec3&, vec3&, float) = 0;
	virtual void CheckWater(void) = 0;
	virtual void GetWaterCheckPosition(int, vec3*) = 0;
	virtual void CategorizePosition(void) = 0;
	virtual void CheckParameters(void) = 0;
	virtual void ReduceTimers(void) = 0;
	virtual void CheckFalling(void) = 0;
	virtual void PlayerRoughLandingEffects(float) = 0;
	virtual void Duck(void) = 0;
	virtual void HandleDuckingSpeedCrop(void) = 0;
	virtual void FinishUnDuck(void) = 0;
	virtual void FinishDuck(void) = 0;
	virtual void CanUnduck(void) = 0;
	virtual void UpdateDuckJumpEyeOffset(void) = 0;
	virtual void CanUnDuckJump(CGameTrace&) = 0;
	virtual void StartUnDuckJump(void) = 0;
	virtual void FinishUnDuckJump(CGameTrace&) = 0;
	virtual void SetDuckedEyeOffset(float) = 0;
	virtual void FixPlayerCrouchStuck(bool) = 0;
	virtual void CategorizeGroundSurface(CGameTrace&) = 0;
	virtual void InWater(void) = 0;
	virtual void TestPlayerPosition(vec3 const&, int, CGameTrace&) = 0;
	virtual void SetGroundEntity(CGameTrace*) = 0;
	virtual void StepMove(vec3&, CGameTrace&) = 0;
	virtual void LockTraceFilter(int) = 0;
	virtual void UnlockTraceFilter(ITraceFilter*&) = 0;
	virtual void GameHasLadders(void) const = 0;
	virtual void PreventBunnyJumping(void) = 0;
	virtual void DecayAimPunchAngle(void) = 0;

};

#endif
