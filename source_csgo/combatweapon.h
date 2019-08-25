#ifndef SOURCE_COMBATWEAPON_H
#define SOURCE_COMBATWEAPON_H

class CCSWeaponInfo
{
  public:
	OFFSET6432(char*, consoleName, 0x8, 0x4);
	OFFSET6432(char*, bulletType, 0x110, 0x84);
	OFFSET6432(CSWeaponType, iWeaponType, 0x140, 0xCC);
	OFFSET6432(int, iWeaponPrice, 0x144, 0xD0);
	OFFSET6432(int, iKillAward, 0x148, 0xD4);
	OFFSET6432(char*, szAnimationPrefix, 0x15C, 0xD8);
	OFFSET6432(float, flCycleTime, 0x158, 0xDC);
	OFFSET6432(int, iDamage, 0x16C, 0xF0);
	OFFSET6432(float, flArmorRatio, 0x170, 0xF4);
	OFFSET6432(float, flPenetration, 0x178, 0xFC);
	OFFSET6432(float, flRange, 0x184, 0x108);
	OFFSET6432(float, flRangeModifier, 0x188, 0x10C);
	OFFSET6432(float, flMaxPlayerSpeed, 0x1B0, 0x130);
	OFFSET6432(int, iZoomLevels, 0x240, 0x1C0);
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
	NETVAR(ItemDefinitionIndex, itemDefinitionIndex, "DT_BaseAttributableItem", "m_iItemDefinitionIndex");

	VFuncPosixWin(CCSWeaponInfo*, GetCSWeaponData, 522, 454);
	VFuncPosixWin(float, GetInaccuracy, 544, 476);
	VFuncPosixWin(float, GetSpread, 514, 450);
	VFuncPosixWin(void, UpdateAccuracyPenalty, 545, 477);
};

#endif
