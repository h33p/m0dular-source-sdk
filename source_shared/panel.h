#ifndef PANEL_H
#define PANEL_H

class IPanel
{
  public:
	const char *GetName(vgui::VPANEL vguiPanel)
	{
		typedef const char *(__thiscall* tGetName)(void*, vgui::VPANEL);
		return GetVFunc<tGetName, PosixWin(37, 36)>(this)(this, vguiPanel);
	}
#ifdef GetClassName
#undef GetClassName
#endif
	const char *GetClassName(vgui::VPANEL vguiPanel)
	{
		typedef const char *(__thiscall* tGetClassName)(void*, vgui::VPANEL);
		return GetVFunc<tGetClassName, PosixWin(38, 37)>(this)(this, vguiPanel);
	}
};

#endif
