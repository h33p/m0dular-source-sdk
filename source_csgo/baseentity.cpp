#include "sdk.h"

bool C_BaseEntity::IsPlayer()
{
	return GetVFunc<bool(__thiscall*)(C_BaseEntity*), 152>(this);
}

bool C_BaseEntity::IsWeapon()
{
	return GetVFunc<bool(__thiscall*)(C_BaseEntity*), 160>(this);
}

bool C_BaseEntity::IsPlantedC4()
{
	return false;
}

bool C_BaseEntity::IsDefuseKit()
{
	return false;
}
