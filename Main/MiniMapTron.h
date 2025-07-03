#pragma once
#define pDrawMapFull ((void(__cdecl*)(int ModelID, float x, float y, float Width, float Heigth, float Rotacion))0x00638130)
#define sub_82B7A0 ((char(__thiscall*)(signed int a4, signed int a5))0x0082B7A0)
#define sub_8875E0 ((char(__cdecl*)(DWORD a1))0x008875E0)
#define sub_635CF0 ((void (__stdcall*)(signed int a4))0X00635CF0)
#define rFileOpen ((int(__cdecl*)(char* FileName, char* Mode)) 0x9D0040) //1.04E
#define rFileClose ((signed int(__cdecl*)(int a1))0x9CFC26) //1.04E 

#define MAX_MINI_MAP_TRON 100

struct LoadTypeMapTron
{
	DWORD ModelID;
	DWORD XSW_Minimap_Frame;
	DWORD YSW_Minimap_Frame;
	DWORD XSW_Minimap;
	DWORD YSW_Minimap;
	DWORD XSW_Time_Frame;
	DWORD YSW_Time_Frame;
	DWORD This_92;
	DWORD This_96;
	DWORD DropMoveUserX;
	DWORD DropMoveUserY;
	DWORD This_108;
	DWORD This_112;
	float CurrentMoveX;
	float CurrentMoveY;
	DWORD Scale;
	DWORD TimerEventVK;
	float Alpha;
};

class CMinimapTron
{
	public:
	CMinimapTron();
	void MiniMapTronload();
	char MapTronRender(int a1);
	LoadTypeMapTron DataMapTron;
}; 
extern CMinimapTron gRenderMapTron;