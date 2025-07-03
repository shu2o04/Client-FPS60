#pragma once
#include "zzzmathlib.h"

#pragma pack(push, 1)
typedef struct  //-> Complete (size: 27)
{
	WORD	ObjectID;
	char	Name[25];
} NpcNameList, * lpNpcNameList;
#pragma pack(pop)

typedef class
{
public:
	/*+16*/
	int		Color1;
	/*+40*/		int		Color2;
	/*+64*/		int		Color3;
	/*+88*/		int		Color6;
	/*+112*/	int		Color7;
	/*+136*/	int		Color8;
	/*+160*/	int		Color4;
	/*+184*/	int		Color5;
	/*+208*/	int		Color9;
	/*+232*/	int		Color10;

	/*+268*/	char *	Unknwon268;	//
	/*+316*/	DWORD	Unknown316;
	/*+320*/	DWORD	Unknown320;
	/*+328*/	DWORD	Unknown328;
	/*+336*/	float	Unknown336;
};


#pragma pack(push, 1)
struct PartyList //-> Complete (size: 32)
{
	/*+0*/	char	Name[10];
	/*+10*/	BYTE	Unknown10;
	/*+11*/	BYTE	Unknown11;
	/*+12*/	BYTE	MapNumber;
	/*+13*/	BYTE	PosX;
	/*+14*/	BYTE	PosY;
	BYTE gap01;
	/*+16*/	int		Life;
	/*+20*/	int		MaxLife;
	/*+24*/	BYTE	LifePercent;
	BYTE gap02[3];
	/*+28*/	int		ViewportID;
};
typedef PartyList * lpPartyList;
#pragma pack(pop)


#pragma pack(push, 1)
struct ItemAttribute
{
	/*+0*/		char Name[10];	//??
	/*+60*/		short ReqLevel;
};
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct	//-> Complete (size: 107)
{
	/*+0*/		short	ItemID;
	/*+2*/		int		Level;
	/*+6*/		char	Unknown6;
	/*+7*/		char	Unknown7;
	/*+8*/		char	Unknown8;
	/*+9*/		WORD	DamageMin;
	/*+11*/		WORD	DamageMax;
	/*+13*/		char	Unknown13;
	/*+14*/		WORD	Defense;
	/*+16*/		WORD	MagicDefense;
	/*+18*/		char	MagicPower;
	/*+19*/		char	Unknown19;
	/*+20*/		short	Unknown20;
	/*+22*/		char	Durability;
	/*+23*/		char	ExcellentOption;
	/*+24*/		char	AncientOption;
	/*+25*/		short	ReqStrenght;
	/*+27*/		short	ReqDextirity;
	/*+29*/		short	ReqEnergy;
	/*+31*/		short	ReqVitality;
	/*+33*/		short	ReqCommand;
	/*+35*/		short	ReqLevel;
	/*+37*/		char	SpecialCount;
	/*+38*/		WORD	SpecialType[8];
	/*+54*/		BYTE	SpecialValue[8];
	/*+62*/		int		UniqueID;
	/*+66*/		char	Unknown66;
	/*+67*/		char	PosX;
	/*+68*/		char	PosY;
	/*+69*/		WORD	HarmonyType;
	/*+71*/		short	HarmonyValue;
	/*+73*/		char	Is380Item;
	/*+74*/		char	SocketOption[5];
	/*+79*/		char	Unknown79;
	/*+80*/		char	SocketSeedIndex[5];
	/*+85*/		char	SocketSphereLevel[5];
	/*+90*/		char	SocketSet;
	BYTE gap01[5];
	/*+96*/		char	DurabilityState;
	/*+97*/		char	PeriodItem;
	/*+98*/		char	ExpiredItem;
	/*+99*/		int		ExpireDateConvert;
	/*+103*/	int		Unknown103;
} ObjectItem, * lpItemObj;
#pragma pack(pop)


#pragma pack(push, 1)
struct UnknownStruct0
{
	/*+0*/	WORD	Unknown0;//?
	/*+2*/	WORD	Unknown2;//?
	/*+4*/	WORD	Unknown4;//?
	/*+6*/	WORD	Unknown6;
	/*+8*/	WORD	Unknown8;
	/*+10*/	WORD	Unknown10;
	/*+12*/	WORD	Unknown12;//?
	/*+14*/	WORD	Unknown14;
	/*+16*/	WORD	Unknown16;
};
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct	//-> InDev (size: 6012)
{
	/*+0*/		char	Name[11];
	/*+11*/		char	Class;
	/*+12*/		BYTE	Unknown12;
	/*+13*/		BYTE	Unknown13;
	/*+14*/		short	Level;
	/*+16*/		DWORD	Experience;
	/*+20*/		DWORD	NextExperience;
	/*+24*/		WORD	Strength;
	/*+26*/		WORD	Dexterity;
	/*+28*/		WORD	Vitality;
	/*+30*/		WORD	Energy;
	/*+32*/		WORD	Leadership;
	/*+34*/		WORD	Life;
	/*+36*/		WORD	Mana;
	/*+38*/		WORD	MaxLife;
	/*+40*/		WORD	MaxMana;
	/*+42*/		WORD	Shield;
	/*+44*/		WORD	MaxShield;
	/*+46*/		WORD	AttackRate;
	/*+48*/		WORD	DefenseRate;
	/*+50*/		short	AddStrength;
	/*+52*/		short	AddDexterity;
	/*+54*/		short	AddVitality;
	/*+56*/		short	AddEnergy;
				BYTE	gap01[4];
	/*+62*/		WORD	AddLeadership;	//GS use unsigned value...
	/*+64*/		WORD	Stamina;
	/*+66*/		WORD	MaxStamina;
	/*+68*/		BYTE	ItemSpecialUseFlag;		//Bit decomposit (1, 2, 8)
				BYTE	UnknownGap;
	/*+70*/		WORD	ItemSpecialUseTime[3];	//[ ]
	/*+76*/		WORD	AddPoint;	//FruitStat start
	/*+78*/		WORD	MaxAddPoint;
	/*+80*/		WORD	MinusPoint;
	/*+82*/		WORD	MaxMinusPoint;	//FruitStat end
	/*+84*/		WORD	AttackSpeed;
	/*+86*/		WORD	DamageRate;
	/*+88*/		WORD	DamageMin;
	/*+90*/		WORD	DamageMax;
	/*+92*/		WORD	Unknown92;
	/*+94*/		WORD	Unknown94;
	/*+96*/		WORD	MagicSpeed;
				BYTE	gap02[10];
	/*+108*/	WORD	Unknown108;
	/*+110*/	WORD	Unknown110;
				BYTE	gap03[4];
	/*+116*/	WORD	LevelPoint;
	/*+118*/	BYTE	MagicCount;
	/*+119*/	BYTE	Unknown119;
	/*+120*/	WORD	pMagicList[650];	//maybe 150?
	/*1420*/
				BYTE	gap04[3252];	//maybe preview struct some here
	/*+4672*/	ObjectItem pEquipment[12];
	/*+5956*/	DWORD	MoneyInventory;	//(C4)
	/*+5960*/	DWORD	MoneyWarehouse;	//(C4)
				BYTE	gap05[8];
	/*+5972*/	UnknownStruct0 Unknown5972;
				BYTE	gap06[2];
	/*+5992*/	WORD	Unknown5992;
	/*+5994*/	WORD	Unknown5994;
				BYTE	gap07[2];
	/*+5998*/	WORD	Unknown5998;
	/*+6000*/	WORD	Unknown6000;
	/*+6002*/	WORD	Unknown6002;
	/*+6004*/	WORD	Unknown6004;
	/*+6006*/	WORD	Unknown6006;
	/*+6008*/	BYTE	Unknown6008;
	/*+6009*/	BYTE	Unknown6009;
	/*+6010*/	BYTE	Unknown6010;
	/*+6011*/	BYTE	Unknown6011;
} ObjectCharacter, * lpCharObj;
#pragma pack(pop)


#pragma pack(push, 1)

struct VAngle
{
	float X;
	float Y;
	float Z;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct ObjectModel_424
{
	float Unknown0;
	float Unknown4;
	float Unknown8;
	float Unknown12;
	float Unknown16;
	float Unknown20;
	float Unknown24;
	float Unknown28;
	float Unknown32;
	float Unknown36;
	float Unknown40;
	float Unknown44;
};
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct	//648? 848!!
{
			BYTE	gap00[4];
/*+4*/		BYTE	Unknown4; //-- 780
			BYTE	gap01[4];
/*+9*/		BYTE	Unknown9;
			BYTE	gap02[2];
/*+12*/		BYTE	Unknown12;
			BYTE	gap022[2];
/*+15*/		BYTE	Unknown15;
			BYTE	gap03[2];
/*+18*/		WORD	AnimationID;
/*+20*/		WORD	Unknown20;
/*+22*/		BYTE	Unknown22;
/*+23*/		BYTE	Unknown23;
/*+24*/		BYTE	ObjectType; //-- +800
BYTE gap04[13];
/*+38*/		WORD	Unknown38;
BYTE gap05[8];
/*+48*/		DWORD	Unknown48;
/*+52*/		DWORD	Unknown52;
BYTE gap06[40];
/*+96*/		float	Scale;
BYTE gap07[16];
/*+116*/	float	Unknown116;
BYTE gap08[20];
/*+140*/	float	Unknown140;
/*+144*/	float	Unknown144;
//BYTE gap13[8];
/*+148*/	float	Unknown148;
/*+152*/	float	Unknown152;//ColorR
/*+156*/	float	Unknown156;//ColorG
/*+160*/	float	Unknown160;//ColorB
/*+164*/	float	Unknown164;
BYTE gap09[36];
/*+204*/	VAngle	Unknown204;
/*+216*/	VAngle	Unknown216;
BYTE gap10[24];
///*+252*/	float	VecPosX;
///*+256*/	float	VecPosY;
///*+260*/	float	VecPosZ;
/*+252*/	VAngle	VecPos;
/*+264*/	VAngle	Angle;
///*+264*/	float	Unknown264;
///*+268*/	float	Unknown268;
///*+272*/	float	Unknown272;
BYTE gap11[148];
/*+424*/	ObjectModel_424 Unknown424;
BYTE gap12[176];
/*+484*/
}ObjectModel, * lpModelObj;
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct	//-> InDev (size: 1432)
{
	BYTE gap01[14];
	/*+14*/		bool	InSafeZone;
	/*+15*/		BYTE	Unknown15;
	/*+16*/		BYTE	Unknown16;
	/*+17*/		BYTE	IsLiveObject;
	/*+18*/		BYTE	Unknown18;
	/*+19*/		BYTE	Class;
	/*+20*/		BYTE	Unknown20;
	/*+21*/		BYTE	CtlCode;	//Bit decomposit (0x10)
	/*+22*/		BYTE	Unknown22;
	/*+23*/		BYTE	Unknown23;
	/*+24*/		BYTE	Unknown24;
	/*+25*/		BYTE	Unknown25;
	/*+26*/		BYTE	Unknown26;
	/*+27*/		BYTE	Unknown27;
	/*+28*/		BYTE	Unknown28;
	/*+29*/		BYTE	Unknown29;
	/*+30*/		BYTE	Unknown30;
	/*+31*/		BYTE	GensInfluence;	//0 - None, 1 - D, 2 - V
	/*+32*/		BYTE	Unknown32;
	/*+33*/		BYTE	Unknown33;
	/*+34*/		BYTE	Unknown34;
	/*+35*/		BYTE	Unknown35;
	/*+36*/		BYTE	Unknown36;	//Personal Shop
	/*+37*/		BYTE	Unknown37;
	/*+38*/		WORD	Unknown38;
	/*+40*/		BYTE	Unknown40;
	/*+41*/		BYTE	Unknown41;
	/*+42*/		BYTE	Unknown42;
	BYTE gap03[2];
	/*+45*/		BYTE	RespawnPosX;
	/*+46*/		BYTE	RespawnPosY;
	BYTE gap04[3];
	/*+50*/		BYTE	ActiveMagic;
	BYTE gap05[5];
	/*+56*/		char	Name[25];	//need check size
	BYTE gap06[39];
	/*+120*/	BYTE	Unknown120;
	/*+121*/	BYTE	Unknown121;
	BYTE gap07[2];
	/*+124*/	WORD	Unknown124;
	/*+126*/	WORD	aIndex;
	/*+128*/	WORD	Unknown128;
	/*+130*/	WORD	Decolorate;
	/*+132*/	WORD	ID;
	/*+134*/	WORD	Unknown134;
	/*+136*/	//maybe word
	BYTE gap09[36];
	/*+172*/	DWORD	MapPosX;
	/*+176*/	DWORD	MapPosY;
	BYTE gap10[8];
	/*+188*/	float	Unknown188;
	BYTE gap11[76];
	/*+268*/	short	HelmSlot;
	/*+270*/	BYTE	HelmLevel;
	/*+271*/	BYTE	HelmExcellent;
	/*+272*/	BYTE	HelmAncient;
	BYTE gap12[31];
	/*+304*/	short	ArmorSlot;
	/*+306*/	BYTE	ArmorLevel;
	/*+307*/	BYTE	ArmorExcellent;
	/*+308*/	BYTE	ArmorAncient;
	BYTE gap13[31];
	/*+340*/	short	PantsSlot;
	/*+342*/	BYTE	PantsLevel;
	/*+343*/	BYTE	PantsExcellent;
	/*+344*/	BYTE	PantsAncient;
	BYTE gap14[31];
	/*+376*/	short	GlovesSlot;
	/*+378*/	BYTE	GlovesLevel;
	/*+379*/	BYTE	GlovesExcellent;
	/*+380*/	BYTE	GlovesAncient;
	BYTE gap15[31];
	/*+412*/	short	BootsSlot;
	/*+414*/	BYTE	BootsLevel;
	/*+415*/	BYTE	BootsExcellent;
	/*+416*/	BYTE	BootsAncient;
	BYTE gap16[31];
	/*+448*/	short	WeaponFirstSlot;
	/*+450*/	BYTE	WeaponFirstLevel;
	/*+451*/	BYTE	WeaponFirstExcellent;
	/*+452*/	BYTE	WeaponFirstAncient;
	BYTE gap17[31];
	/*+484*/	short	WeaponSecondSlot;
	/*+486*/	BYTE	WeaponSecondLevel;
	/*+487*/	BYTE	WeaponSecondExcellent;
	/*+488*/	BYTE	WeaponSecondAncient;
	BYTE gap18[31];
	/*+520*/	short	WingsSlot;
	/*+522*/	BYTE	WingsLevel;
	/*+523*/	BYTE	WingsExcellent;
	/*+524*/	BYTE	WingsAncient;
	BYTE gap19[31];
	/*+556*/	short	PetSlot;
	/*+558*/	BYTE	PetLevel;
	/*+559*/	BYTE	PetExcellent;
	/*+560*/	BYTE	PetAncient;
	BYTE gap20[111];
	/*+672*/	DWORD	Unknown672;
	/*+676*/	DWORD	Unknown676;
	BYTE gap21[84];
	/*+764*/	DWORD	Unknown764;
	BYTE gap22[8];
	/*+776*/	ObjectModel	m_Model;
	/*+1424*/	BYTE	Unknown1424;	//maybe gens rank
	BYTE gap23[3];
	/*+1428*/	DWORD	Unknown1428;	//-> end
} ObjectPreview, * lpViewObj;
#pragma pack(pop)

#pragma pack(push, 1)
struct ItemBmdStruct
{
	char Name[30];
/*+30*/	BYTE TwoHand;
/*+31*/	BYTE gap01;
/*+32*/	BYTE ItemLvl;
/*+33*/	BYTE gap02;
/*+34*/	BYTE Slot;
/*+35*/	BYTE gap03;
/*+36*/	BYTE Skill;
/*+37*/	BYTE gap04;
/*+38*/	BYTE ItemWidth;
/*+39*/	BYTE ItemHeight;
/*+40*/	BYTE MinDmg;
/*+41*/	BYTE MaxDmg;
/*+42*/	BYTE gap05;
/*+43*/	BYTE Defence;
/*+44*/	BYTE gap06;
/*+45*/	BYTE Speed;
/*+46*/	BYTE gap07;
/*+47*/	BYTE Dur;
/*+48*/	BYTE MagicDur;
/*+49*/	BYTE MagicPwr;
/*+50*/	BYTE ReqStr;
/*+51*/	BYTE ReqStrValue;
/*+52*/	BYTE ReqAgi;
/*+53*/	BYTE ReqAgiValue;
/*+54*/	BYTE ReqEne;
/*+55*/	BYTE ReqEneValue;
/*+56*/	BYTE ReqVit;
/*+57*/	BYTE ReqVitValue;
/*+58*/	BYTE ReqCmd; //ReqCmd = ReqCmd+(ReqCmdValue*256)
/*+59*/	BYTE ReqCmdValue;
/*+60*/	BYTE ReqLvl;
/*+60*/	BYTE gap08[3];
/*+63*/	unsigned int Money;
/*+67*/	BYTE Type;
/*+68*/	BYTE DW;
/*+69*/	BYTE DK;
/*+70*/	BYTE ELF;
/*+71*/	BYTE MG;
/*+72*/	BYTE DL;
/*+73*/	BYTE Sum;
/*+74*/	BYTE RF;
	BYTE Resists[8];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct teste //-> Complete (size: 32)
{
	int index;
	/*+0*/	float	Unknown0;
	/*+4*/	float	Unknown1;
	/*+8*/	float	Unknown2;
	/*+12*/	float	Unknown3;
	/*+12*/	float	Unknown4;
	/*+12*/	float	Unknown5;
};
typedef teste * lpteste;
#pragma pack(pop)

// ----------------------------------------------------------------------------------------------
#pragma pack(push, 1)
typedef struct	//648? 848!!
{
	/*+0*/		int		Prev;
	/*+4*/		BYTE	IsSetted;
	/*+5*/		BYTE	Unknown5;
	BYTE gap01[3];
	/*+9*/		BYTE	Unknown9;
	/*+10*/		BYTE	Unknown10;
	/*+11*/		BYTE	Unknown11;
	/*+12*/		BYTE	Unknown12;
	/*+13*/		BYTE	Unknown13;
	/*+14*/		BYTE	Unknown14;
	/*+15*/		BYTE	Unknown15;
	/*+16*/		BYTE	Unknown16;
	/*+17*/		BYTE	Unknown17;
	/*+18*/		WORD	AnimationID;
	/*+20*/		WORD	Unknown20;
	/*+22*/		BYTE	Unknown22;
	/*+23*/		BYTE	Unknown23;
	/*+24*/		BYTE	ObjectType;
	/*+25*/		BYTE	Unknown25;
	/*+26*/		BYTE	Unknown26;
	/*+27*/		BYTE	Unknown27;
	/*+28*/		BYTE	Unknown28;
	/*+29*/		BYTE	Unknown29;
	/*+30*/		BYTE	OnAttacking;
	/*+31*/		BYTE	Unknown31;
	/*+32*/		BYTE	Unknown32;
	/*+33*/		BYTE	Unknown33;
	/*+34*/		BYTE	Unknown34;
	/*+35*/		BYTE	Unknown35;
	/*+36*/		WORD	Unknown36;
	/*+38*/		WORD	Unknown38;
	BYTE gap05[8];
	/*+48*/		DWORD	SkinID;
	/*+52*/		DWORD	ActionType; //Fireworks
	/*+56*/		DWORD	Unknown56;
	/*+60*/		DWORD	Unknown60;
	/*+64*/		DWORD	Unknown64; //Count ?
	/*+68*/		DWORD	Transparency;
	/*+72*/		float	Unknown72;
	/*+76*/		float	Unknown76;
	/*+80*/		float	Unknown80;
	BYTE gap06[8];
	/*+92*/		DWORD	Time; //Tempo de dura��o ?
	/*+96*/		float	Scale;
	/*+100*/	float	Unknown100;
	/*+104*/	float	Unknown104;
	/*+108*/	float	Unknown108;
	/*+112*/	float	Unknown112;
	/*+116*/	float	Unknown116;
	/*+120*/	float	Unknown120;
	/*+124*/	float	Unknown124;
	/*+128*/	float	Unknown128;
	/*+132*/	float	Unknown132;
	/*+136*/	float	Unknown136;
	/*+140*/	float	CoordX;
	/*+144*/	float	CoordY;
	/*+148*/	float	Unknown148;
	/*+152*/	float	Unknown152;
	/*+156*/	float	ColorR;
	/*+160*/	float	ColorG;
	/*+164*/	float	ColorB;
	/*+168*/	float	Unknown168;
	/*+172*/	float	Unknown172;
	/*+176*/	float	Unknown176;
	/*+180*/	float	Unknown180;
	/*+184*/	float	Unknown184;
	/*+188*/	float	Unknown188;
	/*+192*/	float	Unknown192;
	/*+196*/	float	Unknown196;
	/*+200*/	float	Unknown200;
	/*+204*/	VAngle	Unknown204;
	/*+216*/	VAngle	Unknown216;
	/*+228*/    VAngle  Unknown228;
	/*+240*/    VAngle  SelectZone; //ou o de cima
	/*+252*/	float	VecPosX;
	/*+256*/	float	VecPosY;
	/*+260*/	float	VecPosZ;
	/*+264*/	VAngle	WorldPos;
	/*+272*/	float	Unknown272; //body direct 0-360
	BYTE gap11[148];
	/*+424*/	ObjectModel_424 Unknown424;
	/*+472*/	VAngle	Unknown472;
	BYTE gap12[164];
	/*+484*/
} ObjectModel1, * lpModelObj1;
#pragma pack(pop)
namespace MUChatTypeName
{
	enum T
	{
		Default		= 0,
		TalkNormal	= 1,
		Info		= 2,
		SystemInfo	= 3,
		Warning		= 4,
		Party		= 5,
		Guild		= 6,
		Alliance	= 7,
		TalkGM		= 8,
		Gens		= 9,
	};
};

struct MUChatType	//-> 24
{
	DWORD a1;
	DWORD a2;
	DWORD a3;
/*+12*/	DWORD	Unknown12;
/*+16*/	DWORD	Unknown16;
/*+20*/	DWORD	Unknown20;
};

struct MUChat
{
			BYTE	Gap0[4];
	//DWORD Unknown0;
/*+4*/		DWORD	Unknown4;
/*+8*/		DWORD	Unknown8;
/*+12*/		DWORD	Unknown12;
/*+16*/		MUChatType ChatType[MAX_CHAT_TYPE1];
/*+256*/	bool	IsActiveChatType[MAX_CHAT_TYPE1];
BYTE gap266[26];
/*+268*/	//SomeType LPVOID;
/*+292*/	DWORD	WindowPosX;
/*+296*/	DWORD	WindowPosY;
/*+300*/	DWORD	ScrollX;
/*+304*/	DWORD	ScrollY;
/*+308*/	DWORD	WindowWidth_;
/*+312*/	DWORD	WindowHeight_;
/*+316*/	DWORD	WindowLineCount;
/*+320*/	DWORD	MessageType;
/*+324*/	DWORD	Unknown324;
/*+328*/	DWORD	WindowScrollPos;
/*+332*/	DWORD	Unknown332;
/*+336*/	float	AlphaColor;
/*+340*/	DWORD	Unknown340;
/*+344*/	BYTE	WindowsActivo;
/*+345*/	BYTE	Unknown345;
/*+345*/	BYTE	gap346[2];
/*+348*/	DWORD	Unknown348;
};



#pragma pack(push, 1)
struct SkillData
{
	/*+216*/	DWORD	SkillSecondID;
	/*+220*/	BOOL	SkillSecondDelayOn;
	/*+224*/	DWORD	SkillSecondDelayTime;
	/*+228*/	BOOL	SkillSecondCounterOn;
	/*+232*/	int		SkillSecondCounterPre;
	/*+236*/	int		SkillSecondCounterSub;
};
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
	BYTE gap01[4];
	/*+4*/		lpViewObj lpPlayer;
	/*+8*/		BYTE	HelperOn;
	BYTE gap02[3];
	/*+12*/		lpViewObj lpTarget;
	/*+16*/		lpViewObj lpIDontKnow;
	/*+20*/		DWORD	Unknown20;
	BYTE gap04[8];
	/*+32*/		DWORD	Time01;
	BYTE gap05[4];
	/*+40*/		DWORD	Unknown40;
	/*+44*/		DWORD	Unknown44;
	/*+48*/		DWORD	Unknown48;
	/*+52*/		DWORD	Unknown52;
	/*+56*/		DWORD	Unknown56;
	/*+60*/		DWORD	Unknown60;
	//BYTE gap06[12];
	/*+64*/		DWORD	Time02;
	/*+68*/		DWORD	MapPosX;
	/*+72*/		DWORD	MapPosY;
	/*+76*/		DWORD	Time03;
	/*+80*/		DWORD	Unknown80;
	BYTE gap07[76];
	/*+160*/	BYTE	Unknown160;
	BYTE gap08[7];
	/*+168*/	BYTE Unknown168;
	BYTE gap09[3];
	/*+172*/	DWORD	HuntingRange;
	/*+176*/	bool	RecoveryPotionOn;
	/*+177*/	BYTE	RecoveryPotionPercent;
	/*+178*/	bool	RecoveryHealOn;			//-> CLASS_ELF
	/*+179*/	BYTE	RecoveryHealPercent;	//-> CLASS_ELF
	/*+180*/	bool	RecoveryDrainOn;		//-> CLASS_SUMMONER
	/*+181*/	BYTE	RecoveryDrainPercent;	//-> CLASS_SUMMONER
	/*+182*/	bool	DistanceLongOn;
	/*+183*/	bool	DistanceReturnOn;
	/*+184*/	DWORD	DistanceMin;
	/*+188*/	DWORD	SkillBasicID;
	/*+192*/	SkillData SkillSecond1;
	/*+216*/	SkillData SkillSecond2;
	///*+192*/	DWORD	SkillSecond1ID;
	///*+196*/	BOOL	SkillSecond1DelayOn;
	///*+200*/	DWORD	SkillSecond1DelayTime;
	///*+204*/	BOOL	SkillSecond1CounterOn;
	///*+208*/	int		SkillSecond1CounterPre;
	///*+212*/	int		SkillSecond1CounterSub;
	///*+216*/	DWORD	SkillSecond2ID;
	///*+220*/	BOOL	SkillSecond2DelayOn;
	///*+224*/	DWORD	SkillSecond2DelayTime;
	///*+228*/	BOOL	SkillSecond2CounterOn;
	///*+232*/	int		SkillSecond2CounterPre;
	///*+236*/	int		SkillSecond2CounterSub;
	/*+240*/	bool	ComboOn;				//-> CLASS_KNIGHT
	/*+241*/	bool	PartyModeOn;
	/*+242*/	bool	PartyModeHealOn;		//-> CLASS_ELF
	/*+243*/	BYTE	PartyModeHealPercent;	//-> CLASS_ELF
	/*+244*/	BOOL	PartyModeBuffOn;
	/*+248*/	DWORD	PartyModeBuffInterval;
	/*+252*/	BOOL	DarkSpiritOn;			//-> CLASS_DARKLORD
	/*+256*/	DWORD	DarkSpiritMode;			//-> CLASS_DARKLORD
	/*+260*/	BOOL	BuffOn;
	/*+264*/	DWORD	BuffSkill[3];
	/*+276*/	DWORD	BuffExtra[3];
//--
	/*+288*/	DWORD	ObtainRange;
	/*+292*/	bool	ObtainRepairOn;
	/*+293*/	bool	ObtainPickNear;
	/*+294*/	bool	ObtainPickSelected;
	/*+295*/	bool	ObtainPickJewels;
	/*+296*/	bool	ObtainPickAncient;
	/*+297*/	bool	ObtainPickMoney;
	/*+298*/	bool	ObtainPickExcellent;
	/*+299*/	bool	ObtainPickExtra;
	/*+300*/	BYTE	ObtainPickItemList[28][12];
	/*+636*/	BYTE	Unknown636;
	/*+637*/	BYTE	Unknown637;
	/*+638*/	BYTE	Unknown638;
} MUHelper, * lpMUHelper;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
	BYTE gap00[44];
	/*+44*/		WORD Unknown44;
	BYTE gap01[110];
	/*+156*/	vec3_t Light;
	BYTE gap02[84];
	/*+252*/	vec3_t Position;
	/*+264*/	vec3_t Angle;
} Object, * lpObject;
#pragma pack(pop)

#pragma pack(push, 1)
enum eTextureIndex
{
	TEXTURE_START_INDEX = 100000,
	TEXTURE_EMOJI_LIST1,
	TEXTURE_EMOJI_LIST2,
	TEXTURE_EMOJI_LIST3,
	TEXTURE_EMOJI_LIST_BTN,
	TEXTURE_EMOJI_LIST_ON,
	TEXTURE_EMOJI_LIST_ARROW,
};
#pragma pack(pop)