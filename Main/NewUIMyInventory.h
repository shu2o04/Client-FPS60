#pragma once
#include "CharacterMachine.h"
#include "Protocol.h"

#if(SLOTPET2)
typedef float vec_t;

typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];
typedef vec_t vec34_t[3][4];
typedef unsigned long dword;

#define EQUIPMENT_WEAPON_RIGHT		0
#define EQUIPMENT_WEAPON_LEFT		1
#define EQUIPMENT_HELM				2
#define EQUIPMENT_ARMOR				3
#define EQUIPMENT_PANTS				4
#define EQUIPMENT_GLOVES			5
#define EQUIPMENT_BOOTS				6
#define EQUIPMENT_WING				7
#define EQUIPMENT_HELPER			8
#define EQUIPMENT_AMULET			9
#define EQUIPMENT_RING_RIGHT		10
#define EQUIPMENT_RING_LEFT			11
//--
#define EQUIPMENT_PENTAGRAM			12
#define EQUIPMENT_ERRING_RIGHT		13
#define EQUIPMENT_ERRING_LEFT		14
#define MAX_EQUIPMENT_INDEX			12

typedef struct tagEQUIPMENT_ITEM
{
	int x, y;
	int width, height;
	DWORD dwBgImage;
} EQUIPMENT_ITEM;


#define HookBackupItem			((void(__cdecl*)()) 0x7DD230)


#define RenderRepairInfo					((void(__cdecl*)(int sz, int sy, int ip, bool Sell)) 0x005C3D70)
#define RenderItemInfo_						((void(__thiscall*)(int thisa, int sx,int sy,int ip,bool Sell, int Inventype, bool bItemTextListBoxUse)) 0x007E3E30)
#define sub_83CBE0							((int   (__thiscall*)(void *thisa)) 0x0083CBE0)
#define MyInventory_Update					((bool(__thiscall*)(void *thisa)) 0x007DB160)
#define calcMaxDurability					((WORD(__cdecl*)(int ip, ITEM_ATTRIBUTE *p, int Level)) 0x005C2170)
#define GetSlotIndexAtPt					((int(__stdcall*)(unsigned __int8 col, unsigned __int8 fil, int temporal)) 0x0083C770)
#define CreateBugSub_						((bool(__cdecl*)(int Type, int Position, int Owner, int o, int SubType, int LinkBone)) 0x005013B0)
#define PetProcess							((int(*)()) 0x004DB230)
#define IsPetProcess						((bool(__thiscall*)(int thisa, int type)) 0x00925700)
#define Process_DeletePet					((void(__thiscall*)(int thisa, int Owner, int itemType)) 0x009253D0)
#define Process_CreatePet					((bool(__thiscall*)(int thisa, int itemType, int modelType, float* Position, int Owner, int SubType, int LinkBone)) 0x009250E0)
#define g_pNPCShop							((int(__thiscall*)(int Instance)) 0x00861280)
#define SetSellingItem						((void(__thiscall*)(int thls, bool bFlag)) 0x00847FF0)
#define ChangeChaosCastleUnit						((void(__cdecl*)(int Character)) 0x004E6670)
#define pPlayerState				*(int*)0x0E609E8
#define pCheckEffectPlayer			((bool(__thiscall*)(void * This,char a2)) 0x004C8640)
#define pPlayStaticEffect			((int(__cdecl*)(DWORD ModelID, DWORD * Arg1, float Scale, float * Color, int Model, float a6, int a7)) 0x00771310)

#define CreateBug                 ((void  (__cdecl*)(int Type, vec3_t Position, OBJECT *Owner, int SubType, int LinkBone)) 0x00501700)

#define MODEL_FENRIR_BLACK					384
#define MODEL_FENRIR_RED					385
#define MODEL_FENRIR_BLUE					386
#define MODEL_FENRIR_GOLD					387
#define MODEL_DARK_HORSE					226
#define MODEL_PEGASUS						323
#define MODEL_UNICON						233
#define MODEL_BUTTERFLY01					176


typedef struct
{
	vec3_t StartPos;
	vec3_t XAxis;
	vec3_t YAxis;
	vec3_t ZAxis;
} OBB_t_ok;


struct OBJECT
{
	BYTE arg[4];
	/*+4*/	bool          Live;
	/*+5*/	bool          bBillBoard;
	/*+6*/	bool          m_bCollisionCheck;		//  Ăæµ¹ Ă¼Å© Ç̉±î?
	/*+7*/	bool          m_bRenderShadow;			//  ±×¸²ÀÚ¸¦ ÂïÀ»±î? ¸»±î?
	/*+8*/	bool          EnableShadow;
	/*+9*/	bool		  LightEnable;
	/*+10*/	bool		  m_bActionStart;
	/*+11*/	bool		  m_bRenderAfterCharacter;
	/*+12*/	bool	      Visible;
	/*+13*/	bool	      AlphaEnable;
	/*+14*/	bool          EnableBoneMatrix;
	/*+15*/	bool		  ContrastEnable;
	/*+16*/	bool          ChromeEnable;
	/*+17*/	unsigned char AI;
	/*+18*/	unsigned short CurrentAction;
	/*+19*/	unsigned short PriorAction;
	/*+20*/		BYTE          ExtState;
	/*+21*/		BYTE          Teleport;
	/*+22*/		BYTE          Kind;
	/*+23*/		WORD		Skill;
	/*+24*/		BYTE		  m_byNumCloth;				// Ăµ °³¼ö
	/*+25*/		BYTE		  m_byHurtByOneToOne;
	/*+26*/		BYTE          WeaponLevel;
	/*+27*/		BYTE          DamageTime;				//  °ø°ƯÀ» ¹̃Àº Ăæ°Ư ½Ă°£.
	/*+28*/		BYTE          m_byBuildTime;
	/*+29*/		BYTE		  m_bySkillCount;
	/*+30*/		BYTE		  m_bySkillSerialNum;
	/*+31*/		BYTE		  Block;
	/*+32*/	void* m_pCloth;	// Ăµ ºÙÀ̀±â
	/*+40*/	short         ScreenX;
	/*+42*/	short         ScreenY;
	/*+44*/	short         PKKey;
	/*+46*/	short         Weapon;
	/*+48*/	int			  Type;
	/*+52*/	int           SubType;
	/*+56*/	int			  m_iAnimation;				// Ææ¸± ¹ß¹Ù´Ú °ü·Ă ¿¡´Ï¸̃À̀¼Ç Å°°ª
	/*+60*/	int           HiddenMesh;
	/*+64*/	int           LifeTime;
	/*+68*/	int           BlendMesh;
	int           AttackPoint[2];
	int           RenderType;
	int			  InitialSceneFrame;
	int           LinkBone;
	/*92*/		DWORD		  m_dwTime;
	/*+96*/		float         Scale;
	/*+100*/	float         BlendMeshLight;
	/*+104*/	float         BlendMeshTexCoordU;
	/*+108*/	float         BlendMeshTexCoordV;
	/*+112*/	float         Timer;
	/*+116*/	float         m_fEdgeScale;				//  ¿Ü°û¼± ½ºÄÉÀÏ.	
	/*+120*/	float         Velocity;
	/*+124*/	float		  CollisionRange;
	/*+128*/	float         ShadowScale;
	/*+132*/	float         Gravity;
	/*+136*/	float         Distance;
	/*+140*/	float         AnimationFrame;
	/*+144*/	float         PriorAnimationFrame;
	/*+148*/	float	      AlphaTarget;
	/*+152*/	float         Alpha;
	vec3_t        Light;
	vec3_t        Direction;
	vec3_t		  m_vPosSword;				// Ä®³¡ À§Ä¡
	vec3_t		  StartPosition;			// bullet
	vec3_t        BoundingBoxMin;
	vec3_t        BoundingBoxMax;
	vec3_t		  m_vDownAngle;
	vec3_t		  m_vDeadPosition;
	/*+252*/	vec3_t        Position;
	/*+264*/	vec3_t	 	  Angle;
	/*+276*/	vec3_t	 	  HeadAngle;
	/*+288*/	vec3_t	   	  HeadTargetAngle;
	/*+300*/	vec3_t  	  EyeLeft;
	/*+312*/	vec3_t  	  EyeRight;
	/*+324*/	vec3_t		  EyeLeft2;
	/*+336*/	vec3_t		  EyeRight2;
	/*+348*/	vec3_t		  EyeLeft3;
	/*+360*/	vec3_t		  EyeRight3;
	/*+372*/	vec34_t	 	  Matrix;
	vec34_t* BoneTrans;
	OBB_t_ok		  OBB;
	OBJECT* Owner;
	OBJECT* Prior;
	OBJECT* Next;
	BYTE		  m_BuffMap[134];
	short int	  m_sTargetIndex;
	BOOL		  m_bpcroom;
	vec3_t		  m_v3PrePos1;
	vec3_t		  m_v3PrePos2;
};

typedef struct //-> InDev (size: 1432)
{
	BYTE		byClass[5];
	bool        Blood;
	bool        Ride;
	bool        SkillSuccess;
	BOOL        m_bFixForm;
	bool        Foot[2];
	/*+14*/		bool	SafeZone;
	/*+15*/		bool	Change;
	/*+16*/		bool	HideShadow;
	/*+17*/		bool	m_bIsSelected;
	/*+18*/		bool	Decoy;
	/*+19*/		BYTE	Class;
	/*+20*/		BYTE	Skin;
	/*+21*/		BYTE	CtlCode;	//Bit decomposit (0x10)
	/*+22*/		BYTE	ExtendState;
	/*+23*/		BYTE	EtcPart;
	/*+24*/		BYTE	GuildStatus;
	/*+25*/		BYTE	GuildType;
	/*+26*/		BYTE	GuildRelationShip;
	/*+27*/		BYTE	GuildSkill;
	/*+28*/		BYTE	GuildMasterKillCount;
	/*+29*/		BYTE	BackupCurrentSkill;
	/*+30*/		BYTE	GuildTeam;
	/*+31*/		BYTE	m_byGensInfluence;	//0 - None, 1 - D, 2 - V
	/*+32*/		BYTE	PK;
	/*+33*/		char	PKPartyLevel;
	/*+34*/		BYTE	AttackFlag;
	/*+35*/		BYTE	AttackTime;
	/*+36*/		BYTE	TargetAngle;	//Personal Shop
	/*+37*/		BYTE	Dead;
	/*+40*/		WORD	Skill;
	/*+41*/		BYTE	SwordCount;
	/*+42*/		BYTE	byExtensionSkill;
	BYTE	m_byDieType;			//	Á×´Â Çü½Ä.
	BYTE	StormTime;
	BYTE	JumpTime;
	/*+45*/		BYTE	RespawnPosX;
	/*+46*/		BYTE	RespawnPosY;
	BYTE    Appear;
	/*+50*/		BYTE	CurrentSkill;
	BYTE    CastRenderTime;
	BYTE    m_byFriend;
	WORD    MonsterSkill;
	/*+56*/		char    Name[32];	//need check size
	char 		Movement;
	BYTE gap06[30];
	/*+120*/	BYTE	Unknown120;
	/*+121*/	BYTE	Unknown121;
	BYTE gap07[2];
	/*+124*/	WORD	Unknown124;
	/*+126*/	WORD	aIndex;
	/*+128*/	WORD	TargetCharacter;
	/*+130*/	WORD	Decolorate;
	/*+132*/	WORD	ID;
	/*+134*/	WORD	Unknown134;
	/*+136*/	//maybe word
	BYTE gap09[36];
	/*+172*/	int		PositionX;
	/*+176*/	int		PositionY;
	BYTE gap10[8];
	/*+188*/	float	Unknown188;
	BYTE gap11[32];
	float	ProtectGuildMarkWorldTime;
	float	AttackRange;
	float	Freeze;
	float   Duplication;
	float	Rot;
	vec3_t  TargetPosition;
	vec3_t  Light;
	//--
	/*+268*/	short	Helm_Type;
	/*+270*/	BYTE	HelmLevel;
	/*+271*/	BYTE	HelmExcellent;
	/*+272*/	BYTE	HelmAncient;
	BYTE gap12[31];
	/*+304*/	short	Armor_Type;
	/*+306*/	BYTE	ArmorLevel;
	/*+307*/	BYTE	ArmorExcellent;
	/*+308*/	BYTE	ArmorAncient;
	BYTE gap13[31];
	/*+340*/	short	Pants_Type;
	/*+342*/	BYTE	PantsLevel;
	/*+343*/	BYTE	PantsExcellent;
	/*+344*/	BYTE	PantsAncient;
	BYTE gap14[31];
	/*+376*/	short	Gloves_Type;
	/*+378*/	BYTE	GlovesLevel;
	/*+379*/	BYTE	GlovesExcellent;
	/*+380*/	BYTE	GlovesAncient;
	BYTE gap15[31];
	/*+412*/	short	Boots_Type;
	/*+414*/	BYTE	BootsLevel;
	/*+415*/	BYTE	BootsExcellent;
	/*+416*/	BYTE	BootsAncient;
	BYTE gap16[31];
	/*+448*/	short	WeaponFirst_Type;
	/*+450*/	BYTE	WeaponFirstLevel;
	/*+451*/	BYTE	WeaponFirstExcellent;
	/*+452*/	BYTE	WeaponFirstAncient;
	BYTE gap17[31];
	/*+484*/	short	WeaponSecond_Type;
	/*+486*/	BYTE	WeaponSecondLevel;
	/*+487*/	BYTE	WeaponSecondExcellent;
	/*+488*/	BYTE	WeaponSecondAncient;
	BYTE gap18[31];
	/*+520*/	short	Wing_Type;
	/*+522*/	BYTE	Wing_Level;
	/*+523*/	BYTE	Wing_Option1;
	/*+524*/	BYTE	Wing_ExtOption;
	BYTE gap19[31];
	/*+556*/	short	Helper_Type;
	/*+558*/	BYTE	Helper_Level;
	/*+559*/	BYTE	Helper_Option1;
	/*+560*/	BYTE	Helper_ExtOption;
	BYTE	Helper_LinkBone;
	BYTE	Helper_CurrentAction;
	BYTE gap20[109];
	/*+672*/	DWORD	Unknown672;
	/*+676*/	DWORD	Unknown676;
	/*+680*/	DWORD	RavenSlot;
	BYTE gap21[80];
	/*+764*/	DWORD	Unknown764;
	BYTE gap22[8];
	/*+776*/	OBJECT	Object;
	/*+1424*/	BYTE	m_byRankIndex;	//maybe gens rank
	BYTE gap23[3];
	/*+1428*/	DWORD	Unknown1428;	//-> end
} CHARACTER_PRE, * CHARACTER;


#pragma pack(push, 1)
typedef struct tagITEM	//-> Complete (size: 107)
{
	/*+0*/		WORD	Type;
	/*+2*/		int		Level;
	/*+6*/		BYTE	Part;
	/*+7*/		BYTE	Class;
	/*+8*/		bool	TwoHand;
	/*+9*/		WORD	DamageMin;
	/*+11*/		WORD	DamageMax;
	/*+13*/		BYTE	SuccessfulBlocking;
	/*+14*/		WORD	Defense;
	/*+16*/		WORD	MagicDefense;
	/*+18*/		BYTE	MagicPower;
	/*+19*/		BYTE	WeaponSpeed;
	/*+20*/		WORD	WalkSpeed;
	/*+22*/		BYTE	Durability;
	/*+23*/		BYTE	Option1;
	/*+24*/		BYTE	ExtOption;
	/*+25*/		WORD	RequireStrength;
	/*+27*/		WORD	RequireDexterity;
	/*+29*/		WORD	RequireEnergy;
	/*+31*/		WORD	RequireVitality;
	/*+33*/		WORD	RequireCharisma;
	/*+35*/		WORD	RequireLevel;
	/*+37*/		BYTE	SpecialNum;
	/*+38*/		WORD	Special[8];
	/*+54*/		BYTE	SpecialValue[8];
	/*+62*/		DWORD	Key;
	/*+66*/		BYTE	bySelectedSlotIndex;
	/*+67*/		BYTE	x;
	/*+68*/		BYTE	y;
	/*+69*/		WORD	Jewel_Of_Harmony_Option;
	/*+71*/		WORD	Jewel_Of_Harmony_OptionLevel;
	/*+73*/		bool	option_380;
	/*+74*/		BYTE	bySocketOption[5];
	/*+79*/		BYTE	SocketCount;
	/*+80*/		BYTE	SocketSeedID[5];
	/*+85*/		BYTE	SocketSphereLv[5];
	/*+90*/		BYTE	SocketSeedSetOption;
	int		Number;
	BYTE	Color;
	/*+96*/		BYTE	byColorState;
	/*+97*/		bool	PeriodItem;
	/*+98*/		bool	ExpiredItem;
	/*+99*/		int		lExpireTime;
	/*+103*/	int		RefCount;
} ITEM;
#pragma pack(pop)

void g_DeleteMuunBug(OBJECT* Owner, int Index);
bool g_CheckBugLive(OBJECT* Owner, int Index);
void Delect_FlyBug(int Owner);
void Create_FlyBug(int Type, int Position, int Owner, int SubType, int LinkBone);
bool CreatePet_Process(int itemType, int modelType, float* Position, int Owner, int SubType, int LinkBone);

class CNewUIMyInventory
{
public:
	void Init();
	void ReceiveInventory(BYTE* ReceiveBuffer);
	void ReceiveDurability(BYTE* ReceiveBuffer);
	void ReceiveItemChange(PMSG_NEWINV_ITEM_CHANGE_RECV* lpMsg);
	void ReceiveDeleteInventory(BYTE* ReceiveBuffer);
	//--
	static void LoadImages();
	static void Backup_PickedItem();
	static bool __thiscall Update(DWORD* a1);
	static void __thiscall RenderFrame(DWORD thisa);
	static void __thiscall SetButtonInfo(DWORD thisa);
	static void __thiscall Render3D(signed int* thisa);
	static bool __thiscall InventoryProcess(int thisa);
	static void __thiscall RenderEquippedItem(DWORD thisa);
	static bool __thiscall EquipmentWindowProcess(DWORD thisa);
	static void __thiscall SetEquipmentSlotInfo(DWORD thisa);
	static void __thiscall RenderItemToolTip(int thisa, int iSlotIndex);
	static void RenderEquipped(GLuint uiImageType, float x, float y, float width, float height);
	static void __thiscall RenderDetailsText(int thisa, int iPos_x, int iPos_y, LPCSTR pszText, int iBoxWidth, int iBoxHeight, int iSort, OUT SIZE* lpTextSize);
	//--
	static bool __thiscall NewUIManager_Render(int thls);

	static void __thiscall RenderLeft(int thls);
};

extern int TypeInventory;
extern BYTE t;
extern CNewUIMyInventory g_pMyInventory;
extern CCharacterMachine* Character_Machin;
#endif