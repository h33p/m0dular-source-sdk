#include "sdk.h"

bool C_BaseEntity::IsPlayer()
{
	return GetVFunc<bool(__thiscall*)(C_BaseEntity*), PosixWin(210, 158)>(this)(this);
}

bool C_BaseEntity::IsWeapon()
{
	return GetVFunc<bool(__thiscall*)(C_BaseEntity*), PosixWin(218, 166)>(this)(this);
}

bool C_BaseEntity::IsPlantedC4()
{
	return false;
}

bool C_BaseEntity::IsDefuseKit()
{
	return false;
}
