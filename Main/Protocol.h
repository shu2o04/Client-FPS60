#pragma once

#define SET_NUMBERHB(x) ((BYTE)((DWORD)(x)>>(DWORD)8))
#define SET_NUMBERLB(x) ((BYTE)((DWORD)(x)&0xFF))
#define SET_NUMBERHW(x) ((WORD)((DWORD)(x)>>(DWORD)16))
#define SET_NUMBERLW(x) ((WORD)((DWORD)(x)&0xFFFF))
#define SET_NUMBERHDW(x) ((DWORD)((QWORD)(x)>>(QWORD)32))
#define SET_NUMBERLDW(x) ((DWORD)((QWORD)(x)&0xFFFFFFFF))

#define MAKE_NUMBERW(x,y) ((WORD)(((BYTE)((y)&0xFF))|((BYTE)((x)&0xFF)<<8)))
#define MAKE_NUMBERDW(x,y) ((DWORD)(((WORD)((y)&0xFFFF))|((WORD)((x)&0xFFFF)<<16)))
#define MAKE_NUMBERQW(x,y) ((QWORD)(((DWORD)((y)&0xFFFFFFFF))|((DWORD)((x)&0xFFFFFFFF)<<32)))

struct PBMSG_HEAD3
{
	public:
	void set( LPBYTE lpBuf, BYTE head, BYTE sub, BYTE size)
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
		lpBuf[3] = sub;
	};
	BYTE c;
	BYTE size;
	BYTE headcode;
	BYTE subcode;
};
struct PBMSG_HEAD2
{
	public:
	void set( LPBYTE lpBuf, BYTE head, BYTE sub, BYTE size)
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
		lpBuf[3] = sub;
	};
	BYTE c;
	BYTE size;
	BYTE headcode;
	BYTE subcode;
};


struct PBMSG_HEAD
{
	void set(BYTE head,BYTE size) // OK
	{
		this->type = 0xC1;
		this->size = size;
		this->head = head;
	}

	void setE(BYTE head,BYTE size) // OK
	{
		this->type = 0xC3;
		this->size = size;
		this->head = head;
	}

	BYTE type;
	BYTE size;
	BYTE head;
};

struct PSBMSG_HEAD
{
	void set(BYTE head,BYTE subh,BYTE size) // OK
	{
		this->type = 0xC1;
		this->size = size;
		this->head = head;
		this->subh = subh;
	}

	void setE(BYTE head,BYTE subh,BYTE size) // OK
	{
		this->type = 0xC3;
		this->size = size;
		this->head = head;
		this->subh = subh;
	}

	BYTE type;
	BYTE size;
	BYTE head;
	BYTE subh;
};

struct SEND_SERVER_REQ
{
	PSBMSG_HEAD h;
};

struct PWMSG_HEAD
{
	void set(BYTE head,WORD size) // OK
	{
		this->type = 0xC2;
		this->size[0] = HIBYTE(size);
		this->size[1] = LOBYTE(size);
		this->head = head;
	}

	void setE(BYTE head,WORD size) // OK
	{
		this->type = 0xC4;
		this->size[0] = HIBYTE(size);
		this->size[1] = LOBYTE(size);
		this->head = head;
	}

	BYTE type;
	BYTE size[2];
	BYTE head;
};

struct PSWMSG_HEAD
{
	void set(BYTE head,BYTE subh,WORD size) // OK
	{
		this->type = 0xC2;
		this->size[0] = HIBYTE(size);
		this->size[1] = LOBYTE(size);
		this->head = head;
		this->subh = subh;
	}

	void setE(BYTE head,BYTE subh,WORD size) // OK
	{
		this->type = 0xC4;
		this->size[0] = HIBYTE(size);
		this->size[1] = LOBYTE(size);
		this->head = head;
		this->subh = subh;
	}

	BYTE type;
	BYTE size[2];
	BYTE head;
	BYTE subh;
};

struct PMSG_SHOPRUUD_SEND
{
	PBMSG_HEAD h;
};
struct PBMSG_CHATPOSTITEM {
	PBMSG_HEAD h;
	char character_[10];  //  3
	char message_[89];  //  D
};

struct PMSG_POSTITEM {
	PBMSG_HEAD h;
	char chatid[10];    //  3
	char chatmsg[60];   //  D
	char item_data[107];
};
//---
struct PMSG_DAMAGE_RECV
{
	PBMSG_HEAD header; // C1:11
	BYTE index[2];
	BYTE damage[2];
	BYTE type;
	BYTE ShieldDamage[2];
	DWORD ViewCurHP;
	DWORD ViewCurSD;
	DWORD ViewDamageHP;
	DWORD ViewDamageSD;
};

struct PMSG_VIEWPORT_DESTROY_RECV
{
	PBMSG_HEAD header; // C1:14
	BYTE count;
};

struct PMSG_VIEWPORT_DESTROY
{
	BYTE index[2];
};

struct PMSG_MONSTER_DIE_RECV
{
	PBMSG_HEAD header; // C1:16
	BYTE index[2];
	BYTE experience[2];
	BYTE damage[2];
	DWORD ViewDamageHP;
};

struct PMSG_USER_DIE_RECV
{
	PBMSG_HEAD header; // C1:17
	BYTE index[2];
	BYTE skill[2];
	BYTE killer[2];
};

struct PMSG_LIFE_RECV
{
	PBMSG_HEAD header; // C1:26
	BYTE type;
	BYTE life[2];
	BYTE flag;
	BYTE shield[2];
	DWORD ViewHP;
	DWORD ViewSD;
};

struct PMSG_MANA_RECV
{
	PBMSG_HEAD header; // C1:27
	BYTE type;
	BYTE mana[2];
	BYTE bp[2];
	DWORD ViewMP;
	DWORD ViewBP;
};

struct PMSG_FRUIT_RESULT_RECV
{
	PBMSG_HEAD header; // C1:2C
	BYTE result;
	WORD value;
	BYTE type;
	DWORD ViewValue;
	DWORD ViewPoint;
	DWORD ViewStrength;
	DWORD ViewDexterity;
	DWORD ViewVitality;
	DWORD ViewEnergy;
	DWORD ViewLeadership;
};

struct PMSG_REWARD_EXPERIENCE_RECV
{
	PBMSG_HEAD header; // C1:9C
	BYTE index[2];
	WORD experience[2];
	BYTE damage[2];
	DWORD ViewDamageHP;
};

struct PMSG_QUEST_REWARD_RECV
{
	PBMSG_HEAD header; // C1:A3
	BYTE index[2];
	BYTE QuestReward;
	BYTE QuestAmount;
	DWORD ViewPoint;
};

struct PMSG_MAP_SERVER_MOVE_RECV
{
	PSBMSG_HEAD header; // C1:B1:00
	char IpAddress[16];
	WORD ServerPort;
	WORD ServerCode;
	DWORD AuthCode1;
	DWORD AuthCode2;
	DWORD AuthCode3;
	DWORD AuthCode4;
};

struct PMSG_MAP_SERVER_MOVE_AUTH_RECV
{
	PSBMSG_HEAD header; // C1:B1:01
	BYTE result;
};

struct PMSG_CONNECT_CLIENT_RECV
{
	PSBMSG_HEAD header; // C1:F1:00
	BYTE result;
	BYTE index[2];
	BYTE ClientVersion[5];
};

struct PMSG_CONNECT_ACCOUNT_RECV
{
	PSBMSG_HEAD header; // C1:F1:01
	BYTE result;
};

struct PMSG_CLOSE_CLIENT_RECV
{
	PSBMSG_HEAD header; // C1:F1:02
	BYTE result;
};

struct PMSG_CHARACTER_LIST_RECV
{
	PSWMSG_HEAD header; // C1:F3:00
	BYTE ClassCode;
	BYTE MoveCnt;
	BYTE count;
	BYTE ExtWarehouse;
};

struct PMSG_CHARACTER_CREATE_RECV //-- 0xF3,0x01
{
	PSBMSG_HEAD header; // C1:F3:01
	BYTE result;
	char name[10];
	BYTE slot;
	WORD level;
	BYTE Class;
	BYTE equipment[24];
};

struct PMSG_CHARACTER_DELETE_RECV
{
	PSBMSG_HEAD header; // C1:F3:02
	char name[10];
	char PersonalCode[10];
};

struct PMSG_CHARACTER_LIST
{
	BYTE slot;
	char Name[10];
	WORD Level;
	BYTE CtlCode;
	BYTE CharSet[18];
	BYTE GuildStatus;
	DWORD Reset;
	DWORD MasterReset;
	DWORD pDanhHieu;
	DWORD pQuanHam;
	DWORD pTuLuyen;
	DWORD pHonHoan;
};

struct PMSG_CHARACTER_INFO_RECV
{
	PSBMSG_HEAD header; // C3:F3:03
	BYTE X;
	BYTE Y;
	BYTE Map;
	BYTE Dir;
	BYTE Experience[8];
	BYTE NextExperience[8];
	WORD LevelUpPoint;
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	WORD Life;
	WORD MaxLife;
	WORD Mana;
	WORD MaxMana;
	WORD Shield;
	WORD MaxShield;
	WORD BP;
	WORD MaxBP;
	DWORD Money;
	BYTE PKLevel;
	BYTE CtlCode;
	WORD FruitAddPoint;
	WORD MaxFruitAddPoint;
	WORD Leadership;
	WORD FruitSubPoint;
	WORD MaxFruitSubPoint;
	BYTE ExtInventory;
	//EXTRA
	DWORD ViewReset;
	DWORD ViewPoint;
	DWORD ViewCurHP;
	DWORD ViewMaxHP;
	DWORD ViewCurMP;
	DWORD ViewMaxMP;
	DWORD ViewCurBP;
	DWORD ViewMaxBP;
	DWORD ViewCurSD;
	DWORD ViewMaxSD;
	DWORD ViewStrength;
	DWORD ViewDexterity;
	DWORD ViewVitality;
	DWORD ViewEnergy;
	DWORD ViewLeadership;
};

struct PMSG_CHARACTER_REGEN_RECV
{
	PSBMSG_HEAD header; // C3:F3:04
	BYTE X;
	BYTE Y;
	BYTE Map;
	BYTE Dir;
	WORD Life;
	WORD Mana;
	WORD Shield;
	WORD BP;
	BYTE Experience[8];
	DWORD Money;
	//EXTRA
	DWORD ViewCurHP;
	DWORD ViewCurMP;
	DWORD ViewCurBP;
	DWORD ViewCurSD;
};

struct PMSG_LEVEL_UP_RECV
{
	PSBMSG_HEAD header; // C1:F3:05
	WORD Level;
	WORD LevelUpPoint;
	WORD MaxLife;
	WORD MaxMana;
	WORD MaxShield;
	WORD MaxBP;
	WORD FruitAddPoint;
	WORD MaxFruitAddPoint;
	WORD FruitSubPoint;
	WORD MaxFruitSubPoint;
	//-- Extra
	DWORD ViewPoint;
	DWORD ViewMaxHP;
	DWORD ViewMaxMP;
	DWORD ViewMaxBP;
	DWORD ViewMaxSD;
	DWORD ViewExperience;
	DWORD ViewNextExperience;
};

struct PMSG_LEVEL_UP_POINT_RECV
{
	PSBMSG_HEAD header; // C1:F3:06
	BYTE result;
	WORD MaxLifeAndMana;
	WORD MaxShield;
	WORD MaxBP;
	//EXTRA
	DWORD ViewPoint;
	DWORD ViewMaxHP;
	DWORD ViewMaxMP;
	DWORD ViewMaxBP;
	DWORD ViewMaxSD;
	DWORD ViewStrength;
	DWORD ViewDexterity;
	DWORD ViewVitality;
	DWORD ViewEnergy;
	DWORD ViewLeadership;
};

struct PMSG_MONSTER_DAMAGE_RECV
{
	PSBMSG_HEAD header; // C1:F3:07
	BYTE damage[2];
	BYTE ShieldDamage[2];
	//EXTRA
	DWORD ViewCurHP;
	DWORD ViewCurSD;
	DWORD ViewDamageHP;
	DWORD ViewDamageSD;
};

struct PMSG_MASTER_INFO_RECV
{
	PSBMSG_HEAD header; // C1:F3:50
	WORD MasterLevel;
	BYTE Experience[8];
	BYTE NextExperience[8];
	WORD MasterPoint;
	WORD MaxLife;
	WORD MaxMana;
	WORD MaxShield;
	WORD MaxBP;
	//EXTRA
	DWORD ViewMaxHP;
	DWORD ViewMaxMP;
	DWORD ViewMaxBP;
	DWORD ViewMaxSD;
};

struct PMSG_MASTER_LEVEL_UP_RECV
{
	PSBMSG_HEAD header; // C1:F3:51
	WORD MasterLevel;
	WORD MinMasterLevel;
	WORD MasterPoint;
	WORD MaxMasterLevel;
	WORD MaxLife;
	WORD MaxMana;
	WORD MaxShield;
	WORD MaxBP;
	//EXTRA
	DWORD ViewMaxHP;
	DWORD ViewMaxMP;
	DWORD ViewMaxBP;
	DWORD ViewMaxSD;
	QWORD ViewMasterExperience;
	QWORD ViewMasterNextExperience;
};

struct PMSG_NEW_CHARACTER_INFO_RECV
{
	PSBMSG_HEAD header; // C1:F3:E0
	WORD Level;
	WORD LevelUpPoint;
	DWORD Experience;
	DWORD NextExperience;
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	WORD Leadership;
	WORD Life;
	WORD MaxLife;
	WORD Mana;
	WORD MaxMana;
	WORD BP;
	WORD MaxBP;
	WORD Shield;
	WORD MaxShield;
	WORD FruitAddPoint;
	WORD MaxFruitAddPoint;
	WORD FruitSubPoint;
	WORD MaxFruitSubPoint;
	//EXTRA
	DWORD ViewReset;
	DWORD ViewPoint;
	DWORD ViewCurHP;
	DWORD ViewMaxHP;
	DWORD ViewCurMP;
	DWORD ViewMaxMP;
	DWORD ViewCurBP;
	DWORD ViewMaxBP;
	DWORD ViewCurSD;
	DWORD ViewMaxSD;
	DWORD ViewStrength;
	DWORD ViewDexterity;
	DWORD ViewVitality;
	DWORD ViewEnergy;
	DWORD ViewLeadership;
};

struct PMSG_NEW_CHARACTER_CALC_RECV
{
	PSBMSG_HEAD header; // C1:F3:E1
	DWORD ViewCurHP;
	DWORD ViewMaxHP;
	DWORD ViewCurMP;
	DWORD ViewMaxMP;
	DWORD ViewCurBP;
	DWORD ViewMaxBP;
	DWORD ViewCurSD;
	DWORD ViewMaxSD;
	DWORD ViewAddStrength;
	DWORD ViewAddDexterity;
	DWORD ViewAddVitality;
	DWORD ViewAddEnergy;
	DWORD ViewAddLeadership;
	DWORD ViewPhysiDamageMin;
	DWORD ViewPhysiDamageMax;
	DWORD ViewMagicDamageMin;
	DWORD ViewMagicDamageMax;
	DWORD ViewCurseDamageMin;
	DWORD ViewCurseDamageMax;
	DWORD ViewMulPhysiDamage;
	DWORD ViewDivPhysiDamage;
	DWORD ViewMulMagicDamage;
	DWORD ViewDivMagicDamage;
	DWORD ViewMulCurseDamage;
	DWORD ViewDivCurseDamage;
	DWORD ViewMagicDamageRate;
	DWORD ViewCurseDamageRate;
	DWORD ViewPhysiSpeed;
	DWORD ViewMagicSpeed;
	DWORD ViewAttackSuccessRate;
	DWORD ViewAttackSuccessRatePvP;
	DWORD ViewDefense;
	DWORD ViewDefenseSuccessRate;
	DWORD ViewDefenseSuccessRatePvP;
	DWORD ViewDamageMultiplier;
	DWORD ViewRFDamageMultiplierA;
	DWORD ViewRFDamageMultiplierB;
	DWORD ViewRFDamageMultiplierC;
	DWORD ViewDarkSpiritAttackDamageMin;
	DWORD ViewDarkSpiritAttackDamageMax;
	DWORD ViewDarkSpiritAttackSpeed;
	DWORD ViewDarkSpiritAttackSuccessRate;
};

struct PMSG_NEW_HEALTH_BAR_RECV
{
	PSWMSG_HEAD header; // C2:F3:E2
	BYTE count;
};

struct PMSG_NEW_HEALTH_RECV
{
	WORD index;
	BYTE type;
	BYTE rate;
	BYTE rate2;
	short Level;
	float Life;
	WORD MonsID;
};

struct PMSG_NEW_GENS_BATTLE_INFO_RECV
{
	PSBMSG_HEAD header; // C1:F3:E3
	BYTE GensBattleMapCount;
	BYTE GensMoveIndexCount;
	BYTE GensBattleMap[120];
	BYTE GensMoveIndex[120];
};

struct PMSG_NEW_MESSAGE_RECV
{
	PSBMSG_HEAD header; // C1:F3:E4
	char message[128];
};

struct PMSG_COIN_RECV
{
	PSBMSG_HEAD header; // 
	int  Coin1;
	int  Coin2;
	int  Coin3;
	int  Ruud;
	int  CoinAtm;
};

struct PMSG_ITEM_BUY_RECV
{
	PSBMSG_HEAD header; // C1:32
	BYTE slot;
};

struct UP_PARTYSEARCH_REQ
{
	PSBMSG_HEAD h;
};


struct PMSG_NPC_TALK_RECV
{
	PBMSG_HEAD header; // C3:30
	BYTE result;
	BYTE level[7];
};
struct PMSG_NPC_TALK_SEND
{
	PBMSG_HEAD header; // C1:30
};

struct PMSG_HELPER_START_SEND
{
	PSBMSG_HEAD header; // C1:BF:51
	BYTE type;
};

struct PMSG_CONNECT_ACCOUNT_SEND
{
	#pragma pack(1)
	PSBMSG_HEAD header; // C3:F1:01
	char account[10];
	char password[20];
	DWORD TickCount;
	BYTE ClientVersion[5];
	BYTE ClientSerial[16];
	#pragma pack()
};

struct PMSG_CHARACTER_LIST_SEND
{
	PSBMSG_HEAD header; // C1:F3:00
};

struct PMSG_CHARACTER_INFO_SEND
{
	PSBMSG_HEAD header; // C1:F3:03
	char name[10];
};

struct PMSG_PARTYSEARCH_PARTYLIST
{
	char Name[11];
	int Map;
	int X;
	int Y;
	int Level;
	bool DarkWizard;
	bool DarkKnight;
	bool Elf;
	bool MagicGladiator;
	bool DarkLord;
	bool Summoner;
	bool RageFighter;
	bool OnlyGuild;
	bool IsSameGuild;
	int Count;
};
//struct PMSG_ITEM_MOVE_RECV
//{
//	PBMSG_HEAD header; // C3:24
//	BYTE result;
//	BYTE slot;
//	BYTE ItemInfo[12];
//};
struct PMSG_RECV_PARTYLIST
{
	PSWMSG_HEAD header;
	int Count;
};

struct PMSG_SERVER_LIST_RECV
{
	PSBMSG_HEAD header; // C1:F4:06
};

struct PMSG_CASH_SHOP_OPEN_RECV
{
	#pragma pack(1)
	PSBMSG_HEAD header; // C1:D2:02
	BYTE OpenType;
	#pragma pack()
};



struct PMSG_SERVER_INFO_SEND
{
	PSBMSG_HEAD header; // C1:F4:03
	char ServerAddress[16];
	WORD ServerPort;
};
struct PMSG_SERVER_LIST_SEND
{
	PSWMSG_HEAD header; // C1:F4:06
	BYTE count[2];
};
struct PMSG_SERVER_INFO_RECV
{
	PSBMSG_HEAD header; // C1:F4:03
	BYTE ServerCode;
};

struct UP_SEND_REQ
{
	PSBMSG_HEAD h;
};

struct UP_TUCHAN_REQ
{
	PSBMSG_HEAD h;
};

struct PMSG_ITEM_MOVE_RECV
{
	PSBMSG_HEAD h;
	BYTE sFlag;
	BYTE tFlag;
	BYTE Source;
	BYTE Target;
};

struct PMSG_SET_CHAOSBOX_STATE
{
	PSBMSG_HEAD header; // C1:32
	BYTE state;
};
struct PMSG_TICKET_SEND
{
	PSBMSG_HEAD header; // C1:F3:00
};

struct INFOCTC_SENDCLIENT
{
	PSBMSG_HEAD header; // C3:F3:03
	DWORD TimeConLai;
	DWORD PointKillQuai;
	DWORD PartyKillPoint;
	DWORD MonterYeuCau;
	DWORD TYPE;

};
struct CTCKILL_SENDCLIENT
{
	PSBMSG_HEAD header; // C3:F3:03
	DWORD QuaiKill;

};
struct XULY_CGPACKET
{
	PSBMSG_HEAD header; // C3:F3:03
	DWORD ThaoTac;
};

#if LUC_CHIEN
struct DATA_LUCCHIEN
{
	PSBMSG_HEAD header; // C3:F3:03
	DWORD LucChien;
};
#endif
typedef struct
{
#pragma pack(1)
	PSBMSG_HEAD Header;
	char lpszID[10];
	char lpszPass[20];
	char lpszPCode[20];
	char lpszEmail[50];
	DWORD TickCount;
	BYTE Version[5];
	BYTE Serial[16];
	#pragma pack()
} 
PBMSG_REGISTER_ACCOUNT, *LPPBMSG_REGISTER_ACCOUNT;

struct PMSG_NOTICE_SEND
{
	PBMSG_HEAD header; // C1:0D
	BYTE type;
	BYTE count;
	BYTE opacity;
	WORD delay;
	DWORD color;
	BYTE speed;
	char message[256];
};
#if(SOIITEM)
typedef struct
{
	PSBMSG_HEAD header;
	BYTE index[2];
}
PMSG_VIEW_REQUEST_SEND;
#endif

#if(SLOTPET2)
typedef struct {
	PSBMSG_HEAD   Header;
	BYTE          KeyH;
	BYTE          KeyL;
	BYTE          Item[12];
} PSCHANGE_CHARACTER, * LPPSCHANGE_CHARACTER;

typedef struct {
	PBMSG_HEAD  Header;
	BYTE          SubCode;
	BYTE          Index;
	BYTE          Item[12];
} PHEAD_DEFAULT_SUBCODE_ITEM, * LPPHEAD_DEFAULT_SUBCODE_ITEM;

typedef struct {
	PBMSG_HEAD Header;
	BYTE         Value;
	BYTE         KeyH;
	BYTE         KeyL;
} PHEAD_DEFAULT_VALUE_KEY, * LPPHEAD_DEFAULT_VALUE_KEY;

typedef struct //-- itemlist
{
	PSWMSG_HEAD  Header;
	BYTE         Value;
} PHEADER_DEFAULT_SUBCODE_WORD, * LPPHEADER_DEFAULT_SUBCODE_WORD;

typedef struct //-- GetList Item
{
	BYTE          Index;
	BYTE          Item[12];
} PRECEIVE_INVENTORY, * LPPRECEIVE_INVENTORY;

typedef struct //-- Get Item Modify
{
	PBMSG_HEAD    Header;
	BYTE          SubCode;
	BYTE          Index;
	BYTE          Item[12];
} PHEADER_SUBCODE_ITEM, * LPPHEADER_SUBCODE_ITEM;

typedef struct //-- GetItem
{
	PSBMSG_HEAD   Header;
	BYTE          Result;
	BYTE          Item[12];
} PRECEIVE_GET_ITEM, * LPPRECEIVE_GET_ITEM;

typedef struct //-- Durabilidad
{
	PSBMSG_HEAD  Header;
	BYTE         Key;
	BYTE         Value;
} PHEADER_DEFAULT_VALUE_DUR, * LPPHEADER_DEFAULT_VALUE_DUR;

typedef struct //-- Item Drop
{
	PSBMSG_HEAD  Header;
	BYTE         KeyH;
	BYTE         KeyL;
} PHEADER_DEFAULT_KEY, * LPPHEADER_DEFAULT_KEY;

typedef struct
{
	PSBMSG_HEAD  Header;
	BYTE         SubCode;
	BYTE         Value;
} PHEADER_DEFAULT_SUBCODE, * LPPHEADER_DEFAULT_SUBCODE;

/* By Denis - Inventory Visual*/


struct PMSG_NEWINV_ITEM_CHANGE_RECV
{
	PSBMSG_HEAD header; // C1:4E:06
	BYTE index[2];
	BYTE ItemInfo[12];
};


typedef struct //-- Get Item Modify
{
	PSBMSG_HEAD   Header;
	BYTE          SubCode;
	BYTE          Index;
	BYTE          Item[12];
} PHEADER_DEFAULT_SUBCODE_ITEM, * LPPHEADER_DEFAULT_SUBCODE_ITEM;
#endif


void SetChaosBoxState(PMSG_SET_CHAOSBOX_STATE* Data);
bool RecvPostItem(PMSG_POSTITEM * lpMsg); //--post item
BOOL ProtocolCoreEx(BYTE head,BYTE* lpMsg,int size,int key);
void GCDamageRecv(PMSG_DAMAGE_RECV* lpMsg);
void GCMonsterDieRecv(PMSG_MONSTER_DIE_RECV* lpMsg);
void GCUserDieRecv(PMSG_USER_DIE_RECV* lpMsg);
void GCLifeRecv(PMSG_LIFE_RECV* lpMsg);
void GCManaRecv(PMSG_MANA_RECV* lpMsg);
void GCFruitResultRecv(PMSG_FRUIT_RESULT_RECV* lpMsg);
void GCRewardExperienceRecv(PMSG_REWARD_EXPERIENCE_RECV* lpMsg);
void GCQuestRewardRecv(PMSG_QUEST_REWARD_RECV* lpMsg);
void GCMapServerMoveRecv(PMSG_MAP_SERVER_MOVE_RECV* lpMsg);
void GCMapServerMoveAuthRecv(PMSG_MAP_SERVER_MOVE_AUTH_RECV* lpMsg);
void GCConnectClientRecv(PMSG_CONNECT_CLIENT_RECV* lpMsg);
void GCConnectAccountRecv(PMSG_CONNECT_ACCOUNT_RECV* lpMsg);
void GCCloseClientRecv(PMSG_CLOSE_CLIENT_RECV* lpMsg);
void GCCharacterListRecv(PMSG_CHARACTER_LIST_RECV* lpMsg);
void GCCharacterInfoRecv(PMSG_CHARACTER_INFO_RECV* lpMsg);
void GCCharacterRegenRecv(PMSG_CHARACTER_REGEN_RECV* lpMsg);
void GCLevelUpRecv(PMSG_LEVEL_UP_RECV* lpMsg);
void GCLevelUpPointRecv(PMSG_LEVEL_UP_POINT_RECV* lpMsg);
void GCMonsterDamageRecv(PMSG_MONSTER_DAMAGE_RECV* lpMsg);
void GCMasterInfoRecv(PMSG_MASTER_INFO_RECV* lpMsg);
void GCMasterLevelUpRecv(PMSG_MASTER_LEVEL_UP_RECV* lpMsg);
void GCNewCharacterInfoRecv(PMSG_NEW_CHARACTER_INFO_RECV* lpMsg);
void GCNewCharacterCalcRecv(PMSG_NEW_CHARACTER_CALC_RECV* lpMsg);
void GCNewHealthBarRecv(PMSG_NEW_HEALTH_BAR_RECV* lpMsg);
void GCNewGensBattleInfoRecv(PMSG_NEW_GENS_BATTLE_INFO_RECV* lpMsg);
void GCNewMessageRecv(PMSG_NEW_MESSAGE_RECV* lpMsg);
void DataSend(BYTE* lpMsg,DWORD size);
void GCRecvCoin(PMSG_COIN_RECV* lpMsg);
void GCBuyConfirmRecv(PMSG_ITEM_BUY_RECV* lpMsg);
void OpenCashShopSend(BYTE type);
bool CashShopSwitchState();
#if(VONGQUAY_NEW)
void LuckySpinRoll();
#endif
#if(PARTYSEARCH==1)
void GCPartyListRecv(PMSG_RECV_PARTYLIST* lpMsg);
#endif

#if SO_LUONG_BOSS
struct PMSG_RESET_SEND
{
	PSBMSG_HEAD header; // C1:F3:00
};
#endif
#if(B_MOCNAP)
struct PMSG_CBMONAP_SEND
{
	PSWMSG_HEAD header; // C2:F3:E2
	BYTE count;
	int NhanMocNap;
	int TongNap;
};

struct ListMocNapSend
{
	int IndexMocNap;
	int GiaTriNap;
};
struct PMSG_CBLISTTHUONG_SEND
{
	PSWMSG_HEAD header; // C2:F3:E2
	BYTE count;
	int WC;
	int WP;
	int GP;
	int Ruud;
	int CoinAtm;
};
struct LISTITEMMOCNAP_SENDINFO
{
	float SizeBMD;
	int Count;
	short Index;
	BYTE GetTypeItem;
	BYTE Dur;
	BYTE Item[12];
	int  PeriodTime;
};
#include "Object.h"
//==Struct Client
struct INFO_LOCAL_ITEM
{
	float SizeBMD;
	int Count;
	short Index;
	BYTE GetTypeItem;
	ObjectItem Item;
};
struct CBLISTPHANTHUONGMOCNAP_CLIENT
{
	int WC;
	int WP;
	int GP;
	int Ruud;
	int CoinAtm;
	std::vector<INFO_LOCAL_ITEM> ListItemMocNap;

	void Clear()
	{
		WC = 0;
		WP = 0;
		GP = 0;
		Ruud = 0;
		CoinAtm = 0;
		ListItemMocNap.clear();
	}
};
struct CBINFOMOCNAP_CLIENT
{
	int NhanMocNap;
	int TongNap;
	std::vector<ListMocNapSend> DanhSachMocNap;
	void Clear()
	{
		NhanMocNap = 0;
		TongNap = 0;
		DanhSachMocNap.clear();
	}
};

extern CBINFOMOCNAP_CLIENT mDataMocNapClient;
extern CBLISTPHANTHUONGMOCNAP_CLIENT mDataListItemMocNapClient;

#endif

#if(CUSTOM_DUNGLUYENITEM)
struct INFOITEM_DUNGLUYENT_CLIENT
{
	PSWMSG_HEAD header;
	BYTE ActiveMix;
	BYTE ItemChinh[16];
	BYTE ItemPhu[3][16];
	BYTE ItemKetQua[16];
	int Rate;
	int TypeMix;
	char Text[100];
};
#endif