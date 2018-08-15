#include "sdk.h"

bool C_BaseEntity::IsPlayer()
{
	return GetVFunc<bool(__thiscall*)(C_BaseEntity*), PosixWin(204, 152)>(this)(this);
}

bool C_BaseEntity::IsWeapon()
{
	return GetVFunc<bool(__thiscall*)(C_BaseEntity*), PosixWin(205, 160)>(this)(this);
}

bool C_BaseEntity::IsPlantedC4()
{
	return false;
}

bool C_BaseEntity::IsDefuseKit()
{
	return false;
}
