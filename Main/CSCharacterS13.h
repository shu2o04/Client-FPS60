#pragma once
#include "Protocol.h"

// ---------------------------------------------------------------------------------------------
#define sub_482B70			((int(*)()) 0x00482B70)
#define sub_587620			((int(__cdecl*)(char a1)) 0x00587620)
#define sub_483B20			((int(__thiscall*)(int a1,int a2)) 0x00483B20)
#define SelectedHero		*(int*)0xE60B4C
#define SelectedCharacter	*(int*)0xE61730
#define PlayBuffer			((signed int(__cdecl*)(int a1, int a2, int a3)) 0x006D6C20)
#define sub_63CB40			((int(*)(void)) 0x0063CB40)
#define sub_4D5130			((DWORD(__cdecl*)(char a1)) 0x004D5130)
#define sub_587380			((DWORD(__cdecl*)(char)) 0x587380)
#define sub_586DA0			((int(__cdecl*)(int, int, char, float, float, float)) 0x586DA0)
#define sub_9CF1C0			((DWORD(__cdecl*)(DWORD, DWORD, DWORD)) 0x009CF1C0)
#define sub_57FD90			((void(__cdecl*)(signed int a1, int a2, int a3, int a4)) 0x0057FD90)
#define dword_87935A4		*(int*)0x87935A4
#define dword_E8CB30		*(int*)0xE8CB30
#define SceneFlag			*(int*)0x0E609E8
#define World				*(int*)0x0E61E18

#define JCSetModelCoord					((int(__cdecl*)(int a1, int a2, char a3, float UbicacionX, float UbicacionY, float Rotacion)) 0x00586DA0)
// ---------------------------------------------------------------------------------------------


class CSCharacterS13
{
public:

	// ----
	std::map<int, PMSG_CHARACTER_LIST> lpInfoPlayer;
	int CSCharacterS13::JPlayerList(PMSG_CHARACTER_LIST_RECV* lpMsg);
	int JPlayerAddList(PMSG_CHARACTER_CREATE_RECV* lpMsg);
	void initCharacter();
	void StatusInfo();
	void CSCharacterS13::GetBarSelectCharacter(int a, int b, int c, int d, BYTE Slot);
};
extern CSCharacterS13 gCSCharacterS13;
int JCGetClassname(unsigned __int8 a4);
void GetColorCTCode(BYTE CTLCODE);
int GetStatus(BYTE GuildStatus);
// ---------------------------------------------------------------------------------------------