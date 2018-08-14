#ifndef SOURCE_COMBATWEAPON_H
#define SOURCE_COMBATWEAPON_H

class CCSWeaponInfo
{
  public:
	OFFSET(float, flMaxPlayerSpeed, 0x6F8);
	OFFSET(CSWeaponType, iWeaponType, 0x6FC);
	OFFSET(float, flArmorRatio, 0x70C);
	OFFSET(int, flPenetration, 0x884);
	OFFSET(int, iDamage, 0x888);
	OFFSET(float, flRange, 0x88C);
	OFFSET(float, flRangeModifier, 0x890);
	OFFSET(float, flCycleTime, 0x898);
	OFFSET(int, iWeaponPrice, 0x908);
};

class C_BaseCombatWeapon : public C_BaseEntity
{
  public:
	NETVAR(float_t, nextPrimaryAttack, "DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
	NETVAR(float_t, nextSecondaryAttack, "DT_BaseCombatWeapon", "m_flNextSecondaryAttack");
	NETVAR(float_t, lastShotTime, "DT_BaseCombatWeapon", "m_fLastShotTime");
	NETVAR(int, clip1, "DT_BaseCombatWeapon", "m_iClip1");
	NETVAR(int, clip2, "DT_BaseCombatWeapon", "m_iClip2");
	NETVAR(int, primaryReserveAmmoCount, "DT_BaseCombatWeapon", "m_iPrimaryReserveAmmoCount");
	NETVAR(float_t, recoilIndex, "DT_WeaponCSBase", "m_flRecoilIndex");
	NETVAR(float_t, postponeFireReadyTime, "DT_WeaponCSBase", "m_flPostponeFireReadyTime");

	VFuncPosixWin(ItemDefinitionIndex, GetWeaponID, 428, 426);
	VFuncPosixWin(float, GetInaccuracy, 439, 437);
	VFuncPosixWin(float, GetSpread, 440, 438);
	VFuncPosixWin(void, UpdateAccuracyPenalty, 441, 439);
};

#endif
