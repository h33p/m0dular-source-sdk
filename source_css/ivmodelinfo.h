#ifndef IVMODELINFO_H
#define IVMODELINFO_H

class IVModelInfo
{
  public:
	studiohdr_t* GetStudiomodel(const void* model)
	{
		typedef studiohdr_t*(__thiscall* GetStudiomodel_t)(void*, const void*);
		return GetVFunc<GetStudiomodel_t, PosixWin(29, 28)>(this)(this, model);
	}
};

#endif
