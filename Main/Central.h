#pragma once
#include "Protocol.h"
#include "JCOptionBox.h"
#define sub_4DB0E0					((BOOL(__cdecl*)(int a1))0x004DB0E0)
#define sub_59A8B0					((bool(__stdcall*)())0x0059A8B0)
#define sub_637E80					((void(__cdecl*)(int x, float y, float w, float h, float giro, float a9, float a10, float a11, float a12, float a13))0x00637E80)
#define sub_4F6170					((void(__cdecl*)(float a1))0x004F6170)
#define sub_83C310					((char(__thiscall*)(DWORD * This))0x0083C310)
#define sub_861260					((int(__thiscall*)(int This))0x00861260)

#define sub_78ECE0					((int(__thiscall*)(int This))0x0078ECE0)
#define sub_8615E0					((int(__thiscall*)(int This))0x008615E0)
#define GetWindowShop				((int(__thiscall*)(int This))0x00861280)
#define CheckRepairInv				((int(__thiscall*)(int This))0x00834550)
#define CheckRepairShop				((int(__thiscall*)(int This))0x00847EF0)

#define CursorX					*(DWORD*)0x879340C 
#define CursorY					*(DWORD*)0x8793410 
#define ItemTarget				*(DWORD*)0xE61728
#define NpcTarget				*(DWORD*)0xE6172C
#define PlayerTarget			*(DWORD*)0xE61730
//--
#define sub_861A60					((int(__thiscall*)(int This))0x00861A60)
#define sub_7D6270					((int(__thiscall*)(int This, int a5))0x007D6270)
#define getWindowConfig_35 ((int(__thiscall*)(int This))0x00861620)
#define sub_9CEFB0        ((int(__thiscall*)(int a1)) 0x009CF130) //1

class Centralizado
{
	public:
	Centralizado();
	void InitCentral();
	void RenderCursor();
	static void RenderGame();
	void Centralizado::LoadFormBG();
	void PrintDropBox(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6);
	static signed int MoveRenderCameraDefault();
	bool EventPushCursor(int x, int y, int w, int h);
	void gDrawWindowCustom(float StartX, float StartY, float CuaSoW, float CuaSoH, int eNumWindow, char* WindowName);
	void gDrawWindowCustomXClose(float StartX, float StartY, float CuaSoW, float CuaSoH, int eNumWindow, char* WindowName);
	#if BXH_LUCHIEN	
	DWORD LockMouse;
	void gInfoBox(float PosX, float PosY, float Width, float Height, DWORD bkcolor, float Arg5, int Arg6);
	#else
	void gInfoBox(float PosX, float PosY, float Width, float Height, DWORD bkcolor, float Arg5, int Arg6);
	#endif
	bool gDrawButton(float PosX, float PosY , float SizeButton, int FontSize, char* ButtonText);
	void DrawFrame(DWORD ModelID, float X, float Y, float W, float H, float SourceX = 0, float SourceY = 0, float SourceW = 225, float SourceH = 225, float ScaleW = 1.5f, float ScaleH = 1.5f, bool ScaleUp = 0);
	DWORD LockMouseMoveClick;
	int TimerPush;
	JCOptionBox JCOption[6];
	#if(CongHuongV2)
	void Centralizado::gItemBoxInv(int X, int Y, int Doc, int Ngang, int Use);
	#endif
	void gInfoBoxColor(float PosX, float PosY, float Width, float Height, DWORD bkcolor, float Arg5, int Arg6);
};
extern Centralizado gCentral;
