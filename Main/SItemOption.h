
#pragma once

#include "Defines.h"
#include "Object.h"
#include "Item.h"

#define MAX_ITEM_SETOPTION 254
#define MAX_SET_ITEM_OPTION_TABLE 12
#define MAX_SET_ITEM_FULL_OPTION_TABLE 5
#define MAX_ITEM 8192
#define INVENTORY_WEAR_SIZE 12

#define pMultiLineTooltip ((void(__cdecl*)(int x, int y, int nCount, int witd, int height,int type, int Align)) 0x005BF700)

typedef char tooltiparray[100];
// ---------------------------------------------------------------------------------------------

#define MAX_SETOPT_LINE			110	//108
#define MAX_SETOPT_COUNT		256	//256
#define MAX_BSETOPT_SIZE		(MAX_SETOPT_COUNT * MAX_SETOPT_LINE)

//#define pGameWindow				*(HWND*)0x5878000
#define oItemSetOptionBMDLoad	0x004E8916	//1.04E
#define oItemSetOptionAsm1		0x004E956E	//1.04E
#define oItemSetOptionAsm2		0x004E926B	//1.04E
#define oItemSetOptionAsm3		0x004EC4C4	//1.04E
#define oItemSetOptionAsm4		0x004EC2A5	//1.04E
#define oItemSetOptionAsm5		0x004EC3A9	//1.04E
#define oItemSetOptionAsm6		0x004EBD7F	//1.04E
#define oItemSetOptionAsm7		0x004EBEE9	//1.04E
#define oItemSetOptionAsm8		0x004ECAAA	//1.04E
#define pFileOpen				((int(__cdecl*)(char* FileName, char* Mode)) 0x9D0040) //1.04E
#define pFileRead				((int(__cdecl*)(int a1, int a2, int a3, int a4)) 0x9CFF5F) //1.04E
#define pFileClose				((signed int(__cdecl*)(int a1))0x9CFC26) //1.04E 
#define pFileCRC				((int(__cdecl*)(int a1, int a2, unsigned __int16 a3)) 0x4B1A20) //1.04E
#define pFileDec				((int(__cdecl*)(int a1, signed int a2)) 0x4071A0) //1.04E
//==================================================================================================
enum eSetItemOption
{
	SET_ITEM_OPTION_ADD_STRENGTH = 0,
	SET_ITEM_OPTION_ADD_DEXTERITY = 1,
	SET_ITEM_OPTION_ADD_ENERGY = 2,
	SET_ITEM_OPTION_ADD_VITALITY = 3,
	SET_ITEM_OPTION_ADD_LEADERSHIP = 4,
	SET_ITEM_OPTION_ADD_MIN_PHYSI_DAMAGE = 5,
	SET_ITEM_OPTION_ADD_MAX_PHYSI_DAMAGE = 6,
	SET_ITEM_OPTION_MUL_MAGIC_DAMAGE = 7,
	SET_ITEM_OPTION_ADD_PHYSI_DAMAGE = 8,
	SET_ITEM_OPTION_MUL_ATTACK_SUCCESS_RATE = 9,
	SET_ITEM_OPTION_ADD_DEFENSE = 10,
	SET_ITEM_OPTION_ADD_MAX_LIFE = 11,
	SET_ITEM_OPTION_ADD_MAX_MANA = 12,
	SET_ITEM_OPTION_ADD_MAX_BP = 13,
	SET_ITEM_OPTION_ADD_BP_RECOVERY = 14,
	SET_ITEM_OPTION_ADD_CRITICAL_DAMAGE_RATE = 15,
	SET_ITEM_OPTION_ADD_CRITICAL_DAMAGE = 16,
	SET_ITEM_OPTION_ADD_EXCELLENT_DAMAGE_RATE = 17,
	SET_ITEM_OPTION_ADD_EXCELLENT_DAMAGE = 18,
	SET_ITEM_OPTION_ADD_SKILL_DAMAGE = 19,
	SET_ITEM_OPTION_ADD_DOUBLE_DAMAGE_RATE = 20,
	SET_ITEM_OPTION_ADD_IGNORE_DEFENSE_RATE = 21,
	SET_ITEM_OPTION_MUL_SHIELD_DEFENSE = 22,
	SET_ITEM_OPTION_MUL_TWO_HAND_PHYSI_DAMAGE = 23,
	SET_ITEM_OPTION_ADD_PHYSI_DAMAGE_BY_STRENGTH = 24,
	SET_ITEM_OPTION_ADD_PHYSI_DAMAGE_BY_DEXTERITY = 25,
	SET_ITEM_OPTION_ADD_DEFENSE_BY_DEXTERITY = 26,
	SET_ITEM_OPTION_ADD_DEFENSE_BY_VITALITY = 27,
	SET_ITEM_OPTION_ADD_MAGIC_DAMAGE_BY_ENERGY = 28,
	SET_ITEM_OPTION_ADD_ICE_DAMAGE = 29,
	SET_ITEM_OPTION_ADD_POISON_DAMAGE = 30,
	SET_ITEM_OPTION_ADD_LIGHTNING_DAMAGE = 31,
	SET_ITEM_OPTION_ADD_FIRE_DAMAGE = 32,
	SET_ITEM_OPTION_ADD_EARTH_DAMAGE = 33,
	SET_ITEM_OPTION_ADD_WIND_DAMAGE = 34,
	SET_ITEM_OPTION_ADD_WATER_DAMAGE = 35,
};

enum eSetItemColor
{
	TEXT_BLUE			=	1,
	TEXT_RED			=	2,
	TEXT_GOLD			=	3,
	TEXT_GREN			=	4,
	TEXT_WHITE_RED		=	5,
	TEXT_PINK			=	6,
	TEXT_WHITE_BLUE		=	7,
	TEXT_WHITE_YELLOW	=	8,
	TEXT_GREN_BLUE		=	9,
	TEXT_GRAY			=	10,
	TEXT_PINK2			=	11,
	TEXT_PURPLE			=	12,
	TEXT_ORANGE			=	13,
	TEXT_WHITE			=	14,
};

#pragma pack(push, 1)
struct ITEM_SETTYPE_INFO //4
{
	BYTE set[2];
	BYTE mix[2];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ITEM_SETOPTION_INFO //(size: 110 x 64)
{
	/*+0*/		char name[64];
	/*+64*/		char option[12];
	/*+76*/		char value[12];
	/*+88*/		char unknown88;
	/*+89*/		char unknown89;
	/*+90*/		char unknown90;
	/*+91*/		char unknown91;
	/*+92*/		char unknown92;
	/*+93*/		char fulloption[5];
	/*+98*/		char fullvalue[5];
	/*+103*/	char Class[7];
};
#pragma pack(pop)

#pragma pack(push,1)
class CSItemOption
{
public:
	CSItemOption();
	virtual ~CSItemOption();

private:
	ITEM_SETTYPE_INFO m_ItemSetType[MAX_ITEM];  //?
	//BYTE gap[4];  //?
	ITEM_SETOPTION_INFO m_ItemSetOption[64];//32772 Not Enough Memory
	BYTE unknow39812;
	BYTE unknow39813;
	BYTE ViewSet;
	BYTE unknow39815;
	BYTE unknow39816[220];
public:
	void RenderColorItem( int ColorTexto );
	void ItemTooltipS15(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6);
	bool isEquiped(lpCharObj lpObj, int id, BYTE Ancien);
	bool InitSetOptionName(char * Buffer, int ItemID, int AncientOption);
	int InitSetOptionsTooltip(ObjectItem * lpItem, int CurrentLine, char a4);
	void InitInfoTooltip(int PosX, int PosY);
	BYTE GetSetIndexbyItem(int itemindex, int type);
	int GetCountSetPath(int itemindex, int type);
	ITEM_SETOPTION_INFO* GetSetOptionInfo(int index);
	int GetAncientTextIndex(BYTE OptionIndex);
	bool LoadSetType(char * path);
	bool LoadSetOption(char * path);
	void RemoveDuplicatesUnsorted(int arr[][3], int Length);
	void Load();
	#if LUC_CHIEN
	static int __thiscall RenderDefaultOptionText(int This, ObjectItem* a2, int a3);
	#endif
//---------------------------
	static bool BMDLoad(char * path);

	static void AsmAncent1();
	static void AsmAncent2();
	static void AsmAncent3();
	static void AsmAncent4();
	static void AsmAncent5();
	static void AsmAncent6();
	static void AsmAncent7();
	static void AsmAncent8();
	
	DWORD m_dwSetOptionAddress;
	DWORD m_dwJmpReturn1;
	DWORD m_dwJmpReturn2;
	DWORD m_dwJmpReturn3;
	DWORD m_dwJmpReturn4;
	DWORD m_dwJmpReturn5;
	DWORD m_dwJmpReturn6;
	DWORD m_dwJmpReturn7;
	DWORD m_dwJmpReturn8;

	BYTE m_SetOptionData[MAX_BSETOPT_SIZE];
//---------------------------

public:
	ITEM_SETOPTION_INFO AccPlus[MAX_ITEM_SETOPTION];
};
#pragma pack(pop)

extern CSItemOption gCItemSetOption;

