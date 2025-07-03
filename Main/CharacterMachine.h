#pragma once

#if(SLOTPET2)
#define MAX_SOCKETS_				5
#define MAX_ITEM_SPECIAL_			8
#define SOCKET_EMPTY_				0xFF
#define REQUEST_INVENTORY			0
#define REQUEST_EQUIPMENT			40
#define REQUEST_TRADE				1
#define REQUEST_STORAGE				2
#define REQUEST_CHAOS_MIX			3
#define REQUEST_MYSHOP				4
#define REQUEST_TRAINER_MIX			5
#define REQUEST_ELPIS_MIX			6
#define REQUEST_OSBOURNE_MIX		7
#define REQUEST_JERRIDON_MIX		8
#define REQUEST_CHAOS_CARD_MIX		9
#define REQUEST_CHERRYBLOSSOM_MIX	10
#define REQUEST_EXTRACT_SEED_MIX	11
#define REQUEST_SEED_SPHERE_MIX		12
#define REQUEST_ATTACH_SOCKET_MIX	13
#define REQUEST_DETACH_SOCKET_MIX	14


enum ITEM_EX_SRC_TYPE
{
	ITEM_EX_SRC_EQUIPMENT1 = 1,
	ITEM_EX_SRC_EQUIPMENT2 = 2,
	ITEM_EX_SRC_PETINVENTORY = 3,
};

enum REPAIR_MODE
{
	REPAIR_MODE_OFF = 0,
	REPAIR_MODE_ON,
};

enum MESSAGE_TYPE
{
	TYPE_ALL_MESSAGE = 0,
	TYPE_CHAT_MESSAGE,
	TYPE_WHISPER_MESSAGE,
	TYPE_SYSTEM_MESSAGE,
	TYPE_ERROR_MESSAGE,
	TYPE_PARTY_MESSAGE,
	TYPE_GUILD_MESSAGE,
	TYPE_UNION_MESSAGE,
	TYPE_GM_MESSAGE,
	NUMBER_OF_TYPES,
	TYPE_UNKNOWN = 0xFFFFFFFF
};

#pragma pack(push, 1)
typedef struct tagITEM_2	//-> Complete (size: 107)
{
	WORD	Type;
	int		Level;
	BYTE	Part;
	BYTE	Class;
	bool	TwoHand;
	WORD	DamageMin;
	WORD	DamageMax;
	BYTE	SuccessfulBlocking;
	WORD	Defense;
	WORD	MagicDefense;
	BYTE	MagicPower;
	BYTE	WeaponSpeed;
	WORD	WalkSpeed;
	BYTE	Durability;
	BYTE	Option1;
	BYTE	ExtOption;
	WORD	RequireStrength;
	WORD	RequireDexterity;
	WORD	RequireEnergy;
	WORD	RequireVitality;
	WORD	RequireCharisma;
	WORD	RequireLevel;
	BYTE	SpecialNum;
	WORD	Special[MAX_ITEM_SPECIAL_];
	BYTE	SpecialValue[MAX_ITEM_SPECIAL_];
	DWORD	Key;
	BYTE	bySelectedSlotIndex;
	union
	{
		BYTE  x;
		BYTE  lineal_pos;
	};
	union
	{
		BYTE  y;
		BYTE  ex_src_type;
	};

	WORD	Jewel_Of_Harmony_Option;
	WORD	Jewel_Of_Harmony_OptionLevel;
	bool	option_380;
	BYTE	bySocketOption[MAX_SOCKETS_];
	BYTE	SocketCount;
	BYTE	SocketSeedID[MAX_SOCKETS_];
	BYTE	SocketSphereLv[MAX_SOCKETS_];
	BYTE	SocketSeedSetOption;
	int		Number;
	BYTE	Color;
	BYTE	byColorState;
	bool	bPeriodItem;
	bool	bExpiredPeriod;
	int		lExpireTime;
	int		RefCount;
} 
zITEM;
#pragma pack(pop)

typedef std::map<int, zITEM*> type_vect_item;


#define CreateItemConvert				((zITEM* (__thiscall*)(int a1, void *lp)) 0x007E1B10)
#define RageEquipmentWeapon				((bool (__thiscall*)(int thisa, int _Index, short _ItemType)) 0x0050EB10)
#define pPicked_GetItem					((int (__thiscall*)(int thisa)) 0x007D9430)
#define SendRequestEquipment			((bool (__cdecl*)(BYTE SourceFlag, BYTE SourceSlot, int Item, BYTE TargetFlag, BYTE TargetSlot)) 0x005BD850)
#define IsRepairBan						((bool (__cdecl*)(int itemR))0x005C9A00)

#define ChatLog_AddText					((void(__thiscall*)(int thisa, void *strID, void *strText, int MsgType, int ErrMsgType))0x007894E0)
#define CharToString					((void*(__thiscall*)(void *thisa, char *a4))0x00409A50)
#define StrCopy							((void*(__thiscall*)(void *thisa, void *a4))0x00409AF0)

#define EmptyBufferString				((int (__thiscall*)(void* strMsg))0x00409AD0)
#define Is_EquipItem					((bool(__stdcall*)(int Slot, int iTemp)) 0x00833CB0)

#define FindItemAtPt_ctrl				((int(__thiscall*)(void* thisa, int x, int y)) 0x007DAC10)
#define FindEmptySlot_ctrl				((int(__thiscall*)(void* thisa, IN int cx, IN int cy)) 0x007DACA0)
#define RemoveItem_ctrl					((void(__thiscall*)(int thisa, int pItem)) 0x007DA480)
#define FindItem_ctrl					((int(__thiscall*)(int thisa, int LinealPos)) 0x007DA760)
#define FindItemAtPt					((int(__thiscall*)(void* thisa, int mousex, int mousey, int *temporal)) 0x0083CAB0)
#define MyFindEmptySlot					((int(__thiscall*)(int This, int iTemp, BYTE Type)) 0x008359C0)
#define UnequipItem						((void(__thiscall*)(void *thisa, int iIndex)) 0x00833B20)
#define GetMouseItem					((zITEM* (__thiscall*)(int thisa)) 0x007D9430)

int GetRepairMode();
int GetUINewMyInventory();
void SendRequest_Repair(char p_Index, char p_AddGold);
zITEM* CreateItem(void* lp);
void CreateEffectEquipping(WORD Type, int pCha, int o);

class CCharacterMachine
{
	public:
	void EquipItem(int iIndex, BYTE* pbyItemPacket);
	void Unequip_Item(int iIndex);
	void UnequipAllItems();
	bool IsEquipable(int iIndex, zITEM* pItem);
	bool EquipmentWindowProcess();
	bool UnEquipmentWindowProcess(int m_iPointedSlot, int TypeInventory);
	zITEM Equipment[16];
};
#endif
