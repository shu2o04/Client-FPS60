#pragma once

#include "stdafx.h"
#include "import.h"
#include "Protect.h"
#include "Camera.h"
#define KiemTraCacEvent_1 gInterface.CheckWindow(Character)	|| gInterface.CheckWindow(Warehouse)	|| gInterface.CheckWindow(ChaosBox)	|| gInterface.CheckWindow(Store)	|| gInterface.CheckWindow(OtherStore)	|| gInterface.CheckWindow(Inventory) || gInterface.CheckWindow(ExpandInventory)	|| gInterface.CheckWindow(Shop)	|| gInterface.CheckWindow(Trade)	|| gInterface.CheckWindow(LuckyCoin1)	|| gInterface.CheckWindow(NPC_ChaosMix) || gInterface.CheckWindow(MoveList)
#define KiemTraCacEvent_2 gInterface.CheckWindow(ObjWindow::CashShop) ||gInterface.CheckWindow(ObjWindow::FriendList)||gInterface.CheckWindow(ObjWindow::MoveList)|| gInterface.CheckWindow(ObjWindow::Party)|| gInterface.CheckWindow(ObjWindow::Quest)|| gInterface.CheckWindow(ObjWindow::NPC_Devin)|| gInterface.CheckWindow(ObjWindow::Guild)	|| gInterface.CheckWindow(ObjWindow::Trade)|| gInterface.CheckWindow(ObjWindow::Warehouse)|| gInterface.CheckWindow(ObjWindow::ChaosBox)|| gInterface.CheckWindow(ObjWindow::CommandWindow)|| gInterface.CheckWindow(ObjWindow::PetInfo)|| gInterface.CheckWindow(ObjWindow::Shop)|| gInterface.CheckWindow(ObjWindow::Inventory)|| gInterface.CheckWindow(ObjWindow::Store)|| gInterface.CheckWindow(ObjWindow::OtherStore)|| gInterface.CheckWindow(ObjWindow::Character)	|| gInterface.CheckWindow(ObjWindow::DevilSquare)|| gInterface.CheckWindow(ObjWindow::BloodCastle)|| gInterface.CheckWindow(ObjWindow::CreateGuild)|| gInterface.CheckWindow(ObjWindow::GuardNPC)|| gInterface.CheckWindow(ObjWindow::SeniorNPC)|| gInterface.CheckWindow(ObjWindow::GuardNPC2)|| gInterface.CheckWindow(ObjWindow::CastleGateSwitch)|| gInterface.CheckWindow(ObjWindow::CatapultNPC)|| gInterface.CheckWindow(ObjWindow::CrywolfGate)|| gInterface.CheckWindow(ObjWindow::IllusionTemple)|| gInterface.CheckWindow(ObjWindow::HeroList)   || gInterface.CheckWindow(ObjWindow::ChatWindow)|| gInterface.CheckWindow(ObjWindow::FastMenu)|| gInterface.CheckWindow(ObjWindow::Options)|| gInterface.CheckWindow(ObjWindow::Help)|| gInterface.CheckWindow(ObjWindow::FastDial)|| gInterface.CheckWindow(ObjWindow::SkillTree)|| gInterface.CheckWindow(ObjWindow::GoldenArcher1)|| gInterface.CheckWindow(ObjWindow::GoldenArcher2)|| gInterface.CheckWindow(ObjWindow::LuckyCoin1)|| gInterface.CheckWindow(ObjWindow::LuckyCoin2)|| gInterface.CheckWindow(ObjWindow::NPC_Duel)|| gInterface.CheckWindow(ObjWindow::NPC_Titus)|| gInterface.CheckWindow(ObjWindow::CashShop)|| gInterface.CheckWindow(ObjWindow::Lugard)|| gInterface.CheckWindow(ObjWindow::QuestList1)|| gInterface.CheckWindow(ObjWindow::QuestList2)|| gInterface.CheckWindow(ObjWindow::Jerint)|| gInterface.CheckWindow(ObjWindow::FullMap)|| gInterface.CheckWindow(ObjWindow::NPC_Dialog)|| gInterface.CheckWindow(ObjWindow::GensInfo)|| gInterface.CheckWindow(ObjWindow::NPC_Julia)|| gInterface.CheckWindow(ObjWindow::NPC_ChaosMix)|| gInterface.CheckWindow(ObjWindow::ExpandInventory)|| gInterface.CheckWindow(ObjWindow::ExpandWarehouse)|| gInterface.CheckWindow(ObjWindow::MuHelper)
#define MAX_OBJECT 	500

#define MAX_WINDOW_EX 100
#define MUHELPER_STRUC		0x00E8CB7C
#define pDrawInterfaceNumBer   ((double(__stdcall*)(float X, float Y, int num, float size)) 0x854FE0)
#define pSetItemOption			    ((void(__cdecl*)(ObjectItem * lpItem, BYTE Option, BYTE Special, BYTE Value)) 0x58B910)
void testfunc();
#define GMT (24 + (gProtect.m_MainInfo.TIME_GMT))
#define ButtonMenuTAS 21

enum ObjectID
{
	eTIME = 1,
	TAS_Ranking_Main,
	TAS_JBank_Prev,
	TAS_JBank_Next,
	// CAMERA 3D
	eCAMERA_MAIN,
	eCAMERA_BUTTON1,
	eCAMERA_BUTTON2,
	//======
	#if (RESETCHANGE ==1)
	TAS_RsChange_Main,
	TAS_RsChange_Btn01,
	TAS_RsChange_Btn02,
	TAS_RsChange_Btn03,
	TAS_RsChange_Btn04,
	TAS_RsChange_Btn05,
	#endif

	TAS_ThueFlag_Main,
	eEventTimePANEL_MAIN,
	eMenu,
	eMenu_MAIN,
	eMenu_TITLE,
	eMenu_FRAME,
	eMenu_FOOTER,
	eMenu_DIV,
	eMenu_CLOSE,

	eMenu_OPT1,
	eMenu_OPT2,
	eMenu_OPT3,
	eMenu_OPT4,
	eMenu_OPT5,
	eMenu_OPT6,
	eMenu_OPT7,
	eMenu_OPT8,
	eMenu_OPT9,
	eMenu_OPT10,
	eMenu_OPT11,
	eMenu_OPT12,
	eMenu_OPT13,
	eMenu_OPT14,
	eMenu_OPT15,
	eMenu_OPT16,
	eMenu_OPT17,
	eMenu_OPT18,
	eMenu_OPT19,
	eMenu_OPT20,

	TAS_MAIN_ATM = 53,
	TAS_MAIN_ARESET,
	TAS_MAIN_RSCAM,
	TAS_MAIN_ZMCAM,
	TAS_MAIN_BOXSK,
	TAS_CONFIG_BOX,
	TAS_ITEM_BLOCK,
	TAS_PK_LOCK,
	TAS_AUTO_HP,
	TAS_AUTO_BF,

	TAS_MOVE_EVENT = 80, // +42
	//123
	eCommand_MAIN = 124,
	eOFFTRADE_JoB,
	eOFFTRADE_JoS,
	eOFFTRADE_JoC,
	eOFFTRADE_WCC,
	eOFFTRADE_WCP,
	eOFFTRADE_WCG,
	eOFFTRADE_OPEN,
   #if(CongHuongV2)
	eWindowDoiItem,
	eWindow_CongHuong,
	#endif
	ePLAYER_POINT,
	eNULL_MAP,
	
	eCONFIRM_MAIN,
	eCONFIRM_BTN_OK,
	eCONFIRM_BTN_CANCEL,
	eCONFIRM_TITLE,
	eCONFIRM_FRAME,
	eCONFIRM_FOOTER,
	eCONFIRM_DIV,

	eSTORE_CLOSE,
	MINIMAP_FRAME,
	MINIMAP_TIME_FRAME,
	MINIMAP_BUTTOM,
	eDragonLeft,
	eDragonRight,
	eCharacter,
	eInventory,
	eParty,
	eFriend,
	eFastMenu,
	eShop,
	eGuild,
	eZen,
	eMainMenuSet,
	chatbackground,
	ButtonSettings,
	ButtonStart,
	ButtonStop,
	ButtonStartAttack,
	eCamera3DInit,
	eCamera3DSwitch,
	#if(VONGQUAY_NEW)
	eLuckySpin,
	eLuckySpinRoll,
	eLuckySpinClose,
	#endif
	RankingBtnNext,
	RankingBtnPrev,

	#if(PARTYSEARCH==1)
	ePARTYSETTINGS_MAIN,
	ePARTYSETTINGS_TITLE,
	ePARTYSETTINGS_FRAME,
	ePARTYSETTINGS_FOOTER,
	ePARTYSETTINGS_DIV,
	ePARTYSETTINGS_CLOSE,
	ePARTYSETTINGS_SYSTEM_ACTIVE,
	ePARTYSETTINGS_ONLY_GUILD,
	ePARTYSETTINGS_ONE_CLASS,
	ePARTYSETTINGS_DARK_WIZARD,
	ePARTYSETTINGS_DARK_KNIGHT,
	ePARTYSETTINGS_ELF,
	ePARTYSETTINGS_MAGIC_GLADIATOR,
	ePARTYSETTINGS_DARK_LORD,
	ePARTYSETTINGS_SUMMONER,
	ePARTYSETTINGS_RAGE_FIGHTER,
	ePARTYSETTINGS_LEVEL_MINUS,
	ePARTYSETTINGS_LEVEL_PLUS,
	ePARTYSETTINGS_OK,
	ePARTYSEARCH_LEFT,
	ePARTYSEARCH_RIGHT,
	ePARTYSEARCH_MAIN,
	ePARTYSEARCH_TITLE,
	ePARTYSEARCH_FRAME,
	ePARTYSEARCH_FOOTER,
	ePARTYSEARCH_DIV,
	ePARTYSEARCH_CLOSE,
	#endif	

	#if(CTCMINI)
	eCTCMiniWindow,
	eTimeCTC,
	CTCMINI_MAIN,  
	CTCMINI_TITLE,	
	CTCMINI_FRAME,	
	CTCMINI_FOOTER,
	CTCMINI_DIV,	
	TAS_CtcMini_BtnClose,
	#endif

	TMC_MAIN,	
	TMC_TITLE,	
	TMC_FRAME,	
	TMC_FOOTER,

	ChonTopAll,
	ChonTopWC,
	ChonTopEvent,
	ChonTopPK,
	ChonTopGuild,
	ChonTopMT,

	#if(THANMA)
     eWindowNPC_ThanMaChien,
     eWindowBXH_ThanMaChien,
	#endif
	eJewelBank_MAIN,
	eJewelBank_TITLE,
	eJewelBank_FRAME,
	eJewelBank_FOOTER,
	eJewelBank_CLOSE,
	eJewelBank_NEXT,
	eJewelBank_PREV,
	//223
	//224
	eWindow_NangCapHonHoan = 225,
	eWindow_NangCapDanhHieu,
	eWindow_NangCapQuanHam,
	eWindow_NangCapTuChan,
	eWindow_NangCapNewVip,

	eChangePass_Main ,
    eChangePass_OLD,
    eChangePass_OLD_HIDE,
    eChangePass_NEW_HIDE,
    eChangePass_NEW_HIDE1,
    eChangePass_NEW,
    eChangePass_NEW1,
    eChangePass_BTOK,
    eChangePass_BTCLOSE,

	 #if(CB_EventArenaPvP)
	eWindowBXHGuildPvP,
	eWindowNPCArenaPvP,
	eWindowBXHArenaPvP,
	#endif
	eTopDame,
	ATM_BOX_MAIN,
	eJewelBank_Count,
	eJewelBank_WITHDRAW ,	//+150
	FormZen = 395,
	FormPassLock,
	//397
	//398
	//399
	#if ADD_POINT
	eSTATSADD_MAIN = 400,
	eSTATSADD_TITLE,
	eSTATSADD_FRAME,
	eSTATSADD_FOOTER,
	eSTATSADD_CLOSE,
	eSTATSADD_TEXTBOX01,
	eSTATSADD_STATBOX01,
	eSTATSADD_STATBOX02,
	eSTATSADD_STATBOX03,
	eSTATSADD_STATBOX04,
	eSTATSADD_STATBOX05,
	eSTATSADD_BTN_OK,
	eRESETSTATS_MAIN,
	eRESETSTATS_TITLE,
	eRESETSTATS_FRAME,
	eRESETSTATS_FOOTER,
	eRESETSTATS_CLOSE,
	eRESETSTATS_POINT,
	eRESETSTATS_BTN_OK,
	eCHARINFO_BTN_STAT,
	eCHARINFO_BTN_AUTOHP,
	eCHARINFO_BTN_RESSTAT,
	eCHARINFO_BTN_FAKE,
	#endif
	
	#if RELIFE
	TASRelife_MainBox,
	TASRelife_CloseBox,
	TASRelifeButton, // 425 -> 434
	#endif

	#if NEWXSHOP
	eCustomShop = 435,
	eWindowMessageBox,
	eCustomShop_CLOSE,
	#endif

	eWindowMocNap,
	eWindowMocNapList,
	eWindowMocNapClose,

	eWindowIntros,
	eWindowIntrosList,
	eWindowIntrosClose,
	eWindowInfo,
	eWindowInfoClose,
	eWindowHarmony,
	eWindowDungLuyenItem,
	Arena_CLOSE,
	Option_Main,

#if(BAUCUA)
	BAUCUA_MAIN,
	BAUCUA_TITLE,
	BAUCUA_FRAME,
	BAUCUA_FOOTER,
	BAUCUA_CLOSE,
	BAUCUA_TEXTBOX01,
	BAUCUA_STATBOX01,
	BAUCUA_STATBOX02,
	BAUCUA_STATBOX03,
	BAUCUA_STATBOX04,
	BAUCUA_STATBOX05,
	BAUCUA_STATBOX06,
	BAUCUA_LOAITIENTE01,
	BAUCUA_LOAITIENTE02,
	BAUCUA_LOAITIENTE03,
	BAUCUA_LOAITIENTE04,
	BAUCUA_LOAITIENTE05,
	BAUCUA_LOAITIENTE06,
	BAUCUA_BTN_OK,
	BAUCUA_WC,
	BAUCUA_WP,
	BAUCUA_B,
	BAUCUA_S,
	BAUCUA_L,
	BAUCUA_C,
	BAUCUA_Bau,
	BAUCUA_Cua,
	BAUCUA_Tom,
	BAUCUA_Ca,
	BAUCUA_Ga,
	BAUCUA_Nai,
#endif
#if(SO_LUONG_BOSS)
	eInvasionInfo,
#endif
	TAS_Ranking_BtnClose,
	TAS_Comment_BtnClose,
	TAS_TuChan_BtnClose,
	TAS_DanhHieu_BtnClose,
	TAS_QuanHam_BtnClose,
	TAS_HonHoan_BtnClose,
	TAS_ThueFlag_BtnClose,
	TAS_Relife_BtnClose,
	TAS_LSpin_BtnClose,
	TAS_MocNap_BtnClose,
	TAS_CuaHang_BtnClose,
	TAS_RsChange_BtnClose,
	TAS_NewVip_BtnClose,
	TAS_Harmony_BtnClose,
	TAS_ItemTrade_BtnClose,
	TAS_BoxAtm_BtnClose,
	TAS_EventTime_BtnClose,
	TAS_DungLuyen_BtnClose,
	TAS_BxhArena_BtnClose,
	TAS_Option_BtnClose,
};

struct InterfaceElement
{
	DWORD	ModelID;
	float	Width;
	float	Height;
	float	X;
	float	Y;
	float	MaxX;
	float	MaxY;
	DWORD	EventTick;
	bool	OnClick;
	bool	OnShow;
	BYTE	Attribute;
	long	OpenedValue;
	BYTE	Speed;
	char	StatValue[20];
	bool	ByClose;
	bool	FirstLoad;
	//int		Type;
	float  curX;
	float	curY;
	bool	Hover;
	void Open()
	{
		this->OnShow = true; pSetCursorFocus = true;
		this->ByClose = false;
	};

	void Open(int Value, int Speed)
	{
		this->OnShow = true; pSetCursorFocus = true;
		this->OpenedValue = Value;
		this->Speed = Speed;
		this->ByClose = false;
		this->FirstLoad = true;
	};

	void Close()
	{
		this->OnShow = false;
		pSetCursorFocus = false;
		this->ByClose = false;
	};

	void Close(int Value, int Speed)
	{
		this->OnShow = false; pSetCursorFocus = false;
		this->OpenedValue = Value;
		this->Speed = Speed;
		this->ByClose = false;
	}

	void CloseAnimated(int Speed)
	{
		pSetCursorFocus = false;
		this->Speed = Speed;
		this->ByClose = true;
	}

	bool Check()
	{
		return this->OnShow;
	}
};
struct InterfaceObject
{
	DWORD	ModelID;
	float	Width;
	float	Height;
	float	X;
	float	Y;
	float	MaxX;
	float	MaxY;
	DWORD	EventTick;
	bool	OnClick;
	bool	OnShow;
	DWORD	Attribute;
	long	OpenedValue;
	BYTE	Speed;
	char	StatValue[20];
	bool	ByClose;
	bool	FirstLoad;
	//int		Type;

	void Open()
	{
		this->OnShow = true; pSetCursorFocus = true;
		this->ByClose = false;
	};

	void Open(int Value, int Speed)
	{
		this->OnShow = true; pSetCursorFocus = true;
		this->OpenedValue = Value;
		this->Speed = Speed;
		this->ByClose = false;
		this->FirstLoad = true;
	};

	void Close()
	{
		this->OnShow = false;
		pSetCursorFocus = false;
		this->ByClose = false;
	};

	void Close(int Value, int Speed)
	{
		this->OnShow = false; pSetCursorFocus = false;
		this->OpenedValue = Value;
		this->Speed = Speed;
		this->ByClose = false;
	}

	void CloseAnimated(int Speed)
	{
		pSetCursorFocus = false;
		this->Speed = Speed;
		this->ByClose = true;
	}

	bool Check()
	{
		return this->OnShow;
	}
};


class Interface
{
	public:
	static void LoadImages();
	static int		LoadImg(char * Folder, DWORD ID);
	static void DrawItem2(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse);
	void		LoadImages2(char * Folder, int Code, int Arg3, int Arg4, int Arg5);
	static void LoadModels();
	static void Work();
#if(SO_LUONG_BOSS)
	void Interface::DrawBtnTTBOSS();
#endif

	int ConfirmSlot;
	float PetY;
	float PetX;
	int validar;
	DWORD  ClickTime;
	InterfaceElement Data[MAX_OBJECT];
	void RenderObjectSystem();
	void DrawMenu();
	bool EventDrawMenu_Open(DWORD Event);
	void OpenMenuWindow() { this->Data[eMenu_MAIN].OnShow = true; };
	void CloseMenuWindow() {this->Data[eMenu_MAIN].OnShow = false; };
	bool CheckMenuWindow() { return this->Data[eMenu_MAIN].OnShow; };


	bool HandleCloseEvent(DWORD Event, int btnCloseID, int windowID);

	bool TAS_DrawMenu_Close(DWORD Event);
	bool TAS_CtcMini_Close(DWORD Event);
	bool TAS_Ranking_Close(DWORD Event);
	bool TAS_Comment_Close(DWORD Event);
	bool TAS_TuChan_Close(DWORD Event);
	bool TAS_DanhHieu_Close(DWORD Event);
	bool TAS_QuanHam_Close(DWORD Event);
	bool TAS_HonHoan_Close(DWORD Event);
	bool TAS_ThueFlag_Close(DWORD Event);
	bool TAS_Relife_Close(DWORD Event);
	bool TAS_LSpin_Close(DWORD Event);
	bool TAS_MocNap_Close(DWORD Event);
	bool TAS_CuaHang_Close(DWORD Event);
	bool TAS_RsChange_Close(DWORD Event);
	bool TAS_NewVip_Close(DWORD Event);
	bool TAS_Harmony_Close(DWORD Event);
	bool TAS_ItemTrade_Close(DWORD Event);
	bool TAS_Arena_Close(DWORD Event);
	bool TAS_BoxAtm_Close(DWORD Event);
	bool TAS_EventTime_Close(DWORD Event);
	bool TAS_DungLuyen_Close(DWORD Event);
	bool TAS_Option_Close(DWORD Event);
	bool TAS_BxhArena_Close(DWORD Event);

	void DrawMenuOpen();

	bool TASEventClick(DWORD Event);

	void CloseEventTimeWindow() { this->Data[eEventTimePANEL_MAIN].OnShow = false; }
	float		GetResizeX(short ObjectID);

	void DrawConfirmOpen();
	bool EventConfirm_OK(DWORD Event);
	bool EventConfirm_CANCEL(DWORD Event);
	bool TAS_ResetAuto(DWORD Event);
	bool TAS_BomMauAuto(DWORD Event);
	bool TAS_BuffAuto(DWORD Event);
	bool TAS_Camera3D(DWORD Event);
	bool TAS_RsCamera3D(DWORD Event);
	bool TAS_OpenBoxAtm(DWORD Event);
	bool TAS_OpenBoxBSK(DWORD Event);
	bool TAS_OpenBoxCfg(DWORD Event);
	bool TAS_ItemBlock(DWORD Event);
	bool TAS_Pklock(DWORD Event);
//-- Funtions
	void WindowsKG();
	void BindObject(short ObjectID, DWORD ModelID, float Width, float Height, float X, float Y);
	void DrawGUI(short ObjectID, float PosX, float PosY);
	void DrawGUI2(short ObjectID, float PosX, float PosY);

	void DrawGUI3(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);
	int DrawFormat(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...);
	int TASText(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...);
	void DrawIMG(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);
	void ResetDrawIMG(short ObjectID);
	int DrawMessage(int Mode, LPCSTR Text, ...);
	void DrawItem(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse);

	void DrawWindow(int ObjMain, int ObjTitle, int ObjFrame, int ObjFooter, int Repeat, float X, float Y, char* Text);
	bool CheckWindow(int WindowID);
	int CloseWindow(int WindowID);
	int OpenWindow(int WindowID);
	bool IsWorkZone2(float X, float Y, float MaxX, float MaxY);
	bool IsWorkZone(short ObjectID);
	bool IsWorkZone(float X, float Y, float MaxX, float MaxY);

	bool IsWorkZone1(float, float, float, float);
	int DrawToolTip(int X, int Y, LPCSTR Text, ...);
	float DrawRepeatGUI(short MonsterID, float X, float Y, int Count);
	float DrawRepeatGUIScale(short MonsterID, float X, float Y,float ScaleX, float ScaleY, int Count);
	void DrawColoredGUI(short ObjectID, float X, float Y, DWORD Color);
	void DrawButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);
	void DrawButtonRender(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);

	void CloseCustomWindow();
	//Mini Map
	//void DrawMiniMap();
	void DrawMiniMapTron();
	bool MiniMapCheck();
	bool CheckMap();
	void SwitchMiniMap();
	void SwitchHideDanhHieu();
	void SwitchAntiLag1();
	void SwitchAntiLag2();
	int  AntiLag1;
	int  AntiLag2;
	void DrawInterfaceCustom();
	void DrawInterfaceS2Menu();
	void DrawInterfaceDragonLS3();
	void DrawInterfaceDragonRS3();
	void EventNewInterface_All(DWORD Event);

	void DrawCoord();
	bool WindowEx[MAX_WINDOW_EX];
	bool CheckWindowEx(int WindowID);
	void DrawBarForm(float PosX,float PosY,float Width,float Height,GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	//--
	void OpenConfig(int type);
	void SwitchCamera();
	void SwitchChatExpand();
	void CameraInit();
	bool Button(DWORD Event, int WinID, int ButtonID, bool Type);
	bool		ButtonEx(DWORD Event, int ButtonID, bool Type);
	void		DrawCameraUI();

	static void DrawZenAndRud(int a1, int a2, int a3, int a4);
	BOOL        is_auto;
	BOOL        is_autotron;
	void Interface::DrawAnimatedGUI(short ObjectID, float PosX, float PosY);
	void DrawAnimatedButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);
	void		DrawColoredAnimatedGUI(short ObjectID, float X, float Y, DWORD Color);
};
extern Interface gInterface;

