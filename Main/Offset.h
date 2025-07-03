#pragma once

#define MAIN_LANGUAGE 0x00E8C5C4
#define MAIN_CONNECTION_STATUS 0x08793704
#define MAIN_SCREEN_STATE 0x00E609E8
#define MAIN_CHARACTER_STRUCT 0x08128AC8
#define MAIN_VIEWPORT_STRUCT 0x07BC4F04
#define MAIN_PACKET_SERIAL 0x08793700
#define MAIN_HELPER_STRUCT 0x00E8CB7C
#define MAIN_CURRENT_MAP		0x00E61E18

#define MAIN_FONT_SIZE 0x081C0380
#define MAIN_RESOLUTION 0x00E8C240
#define MAIN_RESOLUTION_X 0x00E61E58
#define MAIN_RESOLUTION_Y 0x00E61E5C
#define MAIN_PARTY_MEMBER_COUNT 0x081F6B6C
#define PickedItem					(*(DWORD*)0x09816F7C)
#define InventoryThis				((LPVOID(__thiscall*)(LPVOID))0x00861260)
#define GetItemEquiped(x)			(*(DWORD*)(0x08128AC4)+(4672+(107*x)))
#define GetItemEquipedIndex(x)		(*(WORD*)(GetItemEquiped(x)))
#define GetMyInventoryCtrl			((LPVOID(__thiscall*)(LPVOID,int))0x00835720)
#define InventoryFindEmptySlot		((int(__thiscall*)(LPVOID,int,int))0x00835940)
#define InventoryFindItem			((DWORD*(__thiscall*)(LPVOID,int,int))0x007DAC10)
#define InventoryFindItemAtPt		((DWORD*(__thiscall*)(LPVOID,int,int,DWORD*))0x0083CAB0)
#define InventoryFindItemSlot		((int(__thiscall*)(LPVOID,int,int))0x007DAC40)
#define InventoryMixDeleteItem		((DWORD*(__thiscall*)(LPVOID,int))0x0084EFD0)
#define InventoryMixFindEmptySlot	((int(__thiscall*)(LPVOID,int,int))0x007DACA0)
#define InventoryThis				((LPVOID(__thiscall*)(LPVOID))0x00861260)
#define InventoryUnequipItem		((DWORD*(__thiscall*)(LPVOID,int))0x00833B20)
#define PSInventoryThis				((LPVOID(__thiscall*)(LPVOID))0x00861400)
#define MixGetMyInventoryCtrl		((LPVOID(__thiscall*)(LPVOID))0x0082C780)
#define MixInventoryThis			((LPVOID(__thiscall*)(LPVOID))0x008612C0)
#define CreatePickedItem			((bool(__cdecl*)(DWORD,DWORD))0x007DD100)
#define ResetMouseRButton			((void(*)())0x007D51E0)
#define SendRequestEquipmentItem	((bool(_cdecl*)(int,int,DWORD,int,int))0x005BD850)
#define InventoryDeleteItem			((DWORD*(__thiscall*)(LPVOID,int))0x00834320)
#define pWindowThis				((LPVOID(*)())0x00861110)
#define pCursorX				*(int*)0x879340C
#define pCursorY				*(int*)0x8793410
#define pCheckWindow			((bool(__thiscall*)(LPVOID,int))0x0085EC20)
#define IsPress								((int(__cdecl*)(int VKBUTTON)) 0x00791070)
#define pChaosMixIndex			((DWORD(__thiscall*)(DWORD*))0x0079DEA0)(&*(DWORD*)(0x00EBB848))

#define ProtocolCore ((BOOL(*)(DWORD,BYTE*,DWORD,DWORD))0x00663B20)
#define DrawInterfaceText ((void(*)(char*,int,int,int,int,int,int,int))0x007D04D0)

#define pSetFont				((int(__thiscall*)(LPVOID This, int a2)) 0x420120)
#define pSetBkColor				((int(__thiscall*)(LPVOID This, BYTE red, BYTE green, BYTE blue, BYTE alpha)) 0x4200B0)
#define pSetTexture				((void(__cdecl*)(int a1)) 0x00635CF0)//sub_635CF0(a1)
#define	pFontNormal				*(HGDIOBJ*)0x00E8C588
#define pFontBold				*(HGDIOBJ*)0x00E8C58C
#define pFontBigBold			*(HGDIOBJ*)0x00E8C590
#define pFontNormal2			*(HGDIOBJ*)0x00E8C594
