#pragma once

typedef unsigned __int64 QWORD;

#define WIN32_LEAN_AND_MEAN

#define _WIN32_WINNT _WIN32_WINNT_WINXP

// System Include
#include <windows.h>
#include "../../Addon/KeySerial.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <winsock2.h>
#include <Mmsystem.h>
#include <time.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <Shellapi.h>
#include <vector>
#include <map>
#include <Windows.h>
#include <algorithm>
#include <winioctl.h>
#include <algorithm>
#include <tlhelp32.h>

#define va_start _crt_va_start
#define va_arg _crt_va_arg
#define va_end _crt_va_end
#define FPS_60					1
#define PJH_NEW_SERVER_SELECT_MAP
#define WIDE_SCREEN					2
#define MAX_SMOKE_ITEMS				500
#define MAX_MODEL_EFFECT			500
#define MAX_FOG						100

#include "WideScreen.h"


#define MAX_WIN_WIDTH						QTFrame.DisplayWin
#define MAX_WIN_HEIGHT						QTFrame.DisplayHeight
#define WS_WIN_HEIGHTADD					QTFrame.DisplayHeightExt
#define WS_WIN_WIDTHADD						QTFrame.DisplayWinExt
#define WS_WIN_WIDTHREAL					QTFrame.DisplayWinReal
#define CBImgDecor							87968
#define	Fix_DisplayWinCDepthBox				QTFrame.DisplayWinCDepthBox
#define	Fix_DisplayWin						QTFrame.DisplayWin
#define	Fix_DisplayWinMid					QTFrame.DisplayWinMid
#define	Fix_DisplayWinExt					QTFrame.DisplayWinExt	
#define Fix_DisplayHeight                   QTFrame.DisplayHeight
#define Fix_DisplayHeightExt                QTFrame.DisplayHeightExt
#define THEMY			0
#define THEMX			0


#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"Opengl32.lib")
#define MENU_GAME_FILE "./Data/TAS/Message/Messenger.ini"
#define MENU_NOTE_FILE  ".\\data\\Custom\\Notice.ini"
#define MENU_OPTN_FILE  "./Settings.ini"

#define MAXSIZEMOCNAP			15
#define MAXSIZERL				11
#define MAXSUBSIZE				6
#define MAX_EARTH_QUAKE				100

#define MAX_WIN_WIDTH			640
#define MAX_WIN_HEIGHT			480

#define TAS_DANHHIEU_IMG		1677300
#define MAX_LEVEL_DANH_HIEU		25

#define TAS_QUANHAM_IMG			1677400
#define MAX_LEVEL_QUAN_HAM		20

#define TAS_TULUYEN_IMG			1677500
#define MAX_LEVEL_TU_LUYEN		40

#define TAS_NEWVIP_IMG			1677600
#define MAX_LEVEL_NEW_VIP		5

#define LevelHH					50
#define MAX_EFFECT_LIST			32
#define MAX_EFFECT_LINE			16 // tạo 2 dòng BUFF mỗi dòng 16
#define MAX_NUM_RSCHANGE		5

//UPDATE 02/09/2024 14:25
#define FPS_OPTION				0
#define MOVE_ITEMBANK_DIR		0 //Trừ trực tiếp vào bank ( DH )
#define TAS_ITEMLOCK			1
#define TAS_OFF_BAR				0
#define CUSTOM_HARMONY			1
#define BAUCUA					1
#define ACTIVE_FIX_DISMOVE		1
#define ACTIVE_VKR				1
#define CUSTOM_DUNGLUYENITEM	1
#define TYPEZEN					0
#define TAS_VKR_HOOK			1
#define B_MOCNAP				1
#define OFF_SOCKET_HAMONY		1
#define NEWXSHOP				1
#define RELIFE					1
#define ZOOM_MAX_CAM			1
#define TAS_ITEMTRADE			1
#define ADD_POINT		        1
#define SLOTPET2				0
#define SOIITEM					1
#define CMUI_RENDER_ZEN			1 // WC - Zen Phim V
#define HT_THUE_FLAG			1
#define SO_LUONG_BOSS			1
#define RINGPEN_NEW				0

#define CHAOS_RATE_FIX			1
#define	DAMAGE_RENDER_ENABLE	0
#define NOTICE_PKSYSTEM			1
#define BXHDAME					1
#define CB_EventArenaPvP		1
#define	TAS_HONHOAN				1
#define TAS_DANHHIEU			1
#define TAS_QUANHAM				1
#define TAS_TUCHAN				1
#define TAS_NEWVIP				1
#define SELECT_CHAR_INFO		1
#define CongHuongV2				1
#define LUC_CHIEN				1
#define BXH_LUCHIEN				1 
#define VONGQUAY_NEW			1

#define REGISTER_INGAME			1
#define CTCMINI					1
#define BUFF_PART_ICON			0
#define OFFNAMEGUILD			0
#define BUNDLE_ITEM				1
#define THANMA					1
#define	RESETCHANGE				1
#define TINHNANG_NEW			1

#define	TAS_STYLE				0
#define SAU_ANTIHACK			1
#define CUSTOM_GUILD_UPGRADE	1
#define MAIN_VERSION_S8			1
#define PREMIUN					1
#define MAX_CHAT_TYPE1			10
#define MOVE_HP_NUM				1
#define MAX_CUSTOM_GLOVES	50
#define MAX_CUSTOM_BOW		50
#define MAX_PET_ITEM		300
#define MAX_CUSTOMCLOAK		20

#define MAX_CUSTOM_WING			100
#define MAX_REMAKE_EFFECT		100
#define MAX_CUSTOM_ITEM_INFO	1000
#define MAX_POSITION_ITEM		1000
//--
#define MAX_CUSTOPETEFFECT			2000
#define MAX_DYNAMIC_WING_EFFECT		5000
#define MAX_CUSTOM_WING_EFFECT		5000

#define UPDATE 15



#define LODWORD(h)					((DWORD)(__int64(h) & __int64(0xffffffff)))

//===Custom

#define NOTICE_MES					1
#define TEXT_IN_GAME				1
#define PARTYSEARCH					1

#define THONG_BAO_PLUGIN_ERROR		1
#ifndef TEXTVN_NEW
#define TEXTVN_NEW					1
#endif

#define HUY_HIEU_CUONG_HOA			0

#define ANTI_CRACK_MAIN				1
#define TAT_QUEST_T					1
#define FIX_MONTER_TRABE			1
#define FIX_LAG_QOAI				1
#define FIX_GIAM_LAG_MAIN			1

#define CheckTAS_WINDOWS gInterface.CheckWindow(ObjWindow::CashShop)				|| gInterface.CheckWindow(ObjWindow::FriendList)	|| gInterface.CheckWindow(ObjWindow::MoveList)		|| gInterface.CheckWindow(ObjWindow::Party)				|| gInterface.CheckWindow(ObjWindow::Quest)			|| gInterface.CheckWindow(ObjWindow::NPC_Devin)		|| gInterface.CheckWindow(ObjWindow::Guild)				|| gInterface.CheckWindow(ObjWindow::Trade)			|| gInterface.CheckWindow(ObjWindow::Warehouse)		|| gInterface.CheckWindow(ObjWindow::ChaosBox)			|| gInterface.CheckWindow(ObjWindow::CommandWindow) || gInterface.CheckWindow(ObjWindow::PetInfo)		|| gInterface.CheckWindow(ObjWindow::Shop)				|| gInterface.CheckWindow(ObjWindow::Inventory)		|| gInterface.CheckWindow(ObjWindow::Store)		|| gInterface.CheckWindow(ObjWindow::OtherStore)		|| gInterface.CheckWindow(ObjWindow::Character)		|| gInterface.CheckWindow(ObjWindow::DevilSquare)		|| gInterface.CheckWindow(ObjWindow::BloodCastle)		|| gInterface.CheckWindow(ObjWindow::CreateGuild)	|| gInterface.CheckWindow(ObjWindow::GuardNPC)		|| gInterface.CheckWindow(ObjWindow::SeniorNPC)			|| gInterface.CheckWindow(ObjWindow::GuardNPC2)		|| gInterface.CheckWindow(ObjWindow::CastleGateSwitch)		|| gInterface.CheckWindow(ObjWindow::CatapultNPC)		|| gInterface.CheckWindow(ObjWindow::CrywolfGate)	|| gInterface.CheckWindow(ObjWindow::IllusionTemple)		|| gInterface.CheckWindow(ObjWindow::HeroList)			|| gInterface.CheckWindow(ObjWindow::ChatWindow)	|| gInterface.CheckWindow(ObjWindow::FastMenu)		|| gInterface.CheckWindow(ObjWindow::Options)			|| gInterface.CheckWindow(ObjWindow::Help)			|| gInterface.CheckWindow(ObjWindow::FastDial)		|| gInterface.CheckWindow(ObjWindow::SkillTree)			|| gInterface.CheckWindow(ObjWindow::GoldenArcher1) || gInterface.CheckWindow(ObjWindow::GoldenArcher2)		|| gInterface.CheckWindow(ObjWindow::LuckyCoin1)		|| gInterface.CheckWindow(ObjWindow::LuckyCoin2)	|| gInterface.CheckWindow(ObjWindow::NPC_Duel)		|| gInterface.CheckWindow(ObjWindow::NPC_Titus)			|| gInterface.CheckWindow(ObjWindow::CashShop)		|| gInterface.CheckWindow(ObjWindow::Lugard)		|| gInterface.CheckWindow(ObjWindow::QuestList1)		|| gInterface.CheckWindow(ObjWindow::QuestList2)	|| gInterface.CheckWindow(ObjWindow::Jerint)		|| gInterface.CheckWindow(ObjWindow::FullMap)			|| gInterface.CheckWindow(ObjWindow::NPC_Dialog)	|| gInterface.CheckWindow(ObjWindow::GensInfo)		|| gInterface.CheckWindow(ObjWindow::NPC_Julia)			|| gInterface.CheckWindow(ObjWindow::NPC_ChaosMix)	|| gInterface.CheckWindow(ObjWindow::ExpandInventory)		|| gInterface.CheckWindow(ObjWindow::ExpandWarehouse)	|| gInterface.CheckWindow(ObjWindow::MuHelper)
#define CheckTAS_WINDOWSX gInterface.CheckWindow(ObjWindow::CashShop)				|| gInterface.CheckWindow(ObjWindow::FriendList)	|| gInterface.CheckWindow(ObjWindow::MoveList)		|| gInterface.CheckWindow(ObjWindow::Party)				|| gInterface.CheckWindow(ObjWindow::Quest)			|| gInterface.CheckWindow(ObjWindow::NPC_Devin)		|| gInterface.CheckWindow(ObjWindow::Guild)				|| gInterface.CheckWindow(ObjWindow::Trade)			|| gInterface.CheckWindow(ObjWindow::Warehouse)		|| gInterface.CheckWindow(ObjWindow::ChaosBox)			|| gInterface.CheckWindow(ObjWindow::CommandWindow) || gInterface.CheckWindow(ObjWindow::PetInfo)		|| gInterface.CheckWindow(ObjWindow::Shop)				|| gInterface.CheckWindow(ObjWindow::Store)		|| gInterface.CheckWindow(ObjWindow::OtherStore)		|| gInterface.CheckWindow(ObjWindow::Character)		|| gInterface.CheckWindow(ObjWindow::DevilSquare)		|| gInterface.CheckWindow(ObjWindow::BloodCastle)		|| gInterface.CheckWindow(ObjWindow::CreateGuild)	|| gInterface.CheckWindow(ObjWindow::GuardNPC)		|| gInterface.CheckWindow(ObjWindow::SeniorNPC)			|| gInterface.CheckWindow(ObjWindow::GuardNPC2)		|| gInterface.CheckWindow(ObjWindow::CastleGateSwitch)		|| gInterface.CheckWindow(ObjWindow::CatapultNPC)		|| gInterface.CheckWindow(ObjWindow::CrywolfGate)	|| gInterface.CheckWindow(ObjWindow::IllusionTemple)		|| gInterface.CheckWindow(ObjWindow::HeroList)			|| gInterface.CheckWindow(ObjWindow::ChatWindow)	|| gInterface.CheckWindow(ObjWindow::FastMenu)		|| gInterface.CheckWindow(ObjWindow::Options)			|| gInterface.CheckWindow(ObjWindow::Help)			|| gInterface.CheckWindow(ObjWindow::FastDial)		|| gInterface.CheckWindow(ObjWindow::SkillTree)			|| gInterface.CheckWindow(ObjWindow::GoldenArcher1) || gInterface.CheckWindow(ObjWindow::GoldenArcher2)		|| gInterface.CheckWindow(ObjWindow::LuckyCoin1)		|| gInterface.CheckWindow(ObjWindow::LuckyCoin2)	|| gInterface.CheckWindow(ObjWindow::NPC_Duel)		|| gInterface.CheckWindow(ObjWindow::NPC_Titus)			|| gInterface.CheckWindow(ObjWindow::CashShop)		|| gInterface.CheckWindow(ObjWindow::Lugard)		|| gInterface.CheckWindow(ObjWindow::QuestList1)		|| gInterface.CheckWindow(ObjWindow::QuestList2)	|| gInterface.CheckWindow(ObjWindow::Jerint)		|| gInterface.CheckWindow(ObjWindow::FullMap)			|| gInterface.CheckWindow(ObjWindow::NPC_Dialog)	|| gInterface.CheckWindow(ObjWindow::GensInfo)		|| gInterface.CheckWindow(ObjWindow::NPC_Julia)			|| gInterface.CheckWindow(ObjWindow::NPC_ChaosMix)	|| gInterface.CheckWindow(ObjWindow::ExpandInventory)		|| gInterface.CheckWindow(ObjWindow::ExpandWarehouse)	|| gInterface.CheckWindow(ObjWindow::MuHelper)
#define CheckTAS_WINDOWS2 gInterface.CheckWindow(CashShop)|| gInterface.CheckWindow(SkillTree)|| gInterface.CheckWindow(FullMap)|| gInterface.CheckWindow(MoveList)|| gInterface.CheckWindow(Inventory)|| gInterface.CheckWindow(ExpandInventory)|| gInterface.CheckWindow(Store)|| gInterface.CheckWindow(Inventory)|| gInterface.CheckWindow(Party)	|| gInterface.CheckWindow(Trade)	|| gInterface.CheckWindow(Warehouse)|| gInterface.CheckWindow(ExpandWarehouse)
#define CheckTAS_WINDOWS3 gInterface.CheckWindow(ObjWindow::CashShop)|| gInterface.CheckWindow(ObjWindow::FriendList)|| gInterface.CheckWindow(ObjWindow::MoveList)|| gInterface.CheckWindow(ObjWindow::Party)|| gInterface.CheckWindow(ObjWindow::Quest)|| gInterface.CheckWindow(ObjWindow::NPC_Devin)|| gInterface.CheckWindow(ObjWindow::Guild)|| gInterface.CheckWindow(ObjWindow::Trade)|| gInterface.CheckWindow(ObjWindow::Warehouse)|| gInterface.CheckWindow(ObjWindow::ChaosBox)|| gInterface.CheckWindow(ObjWindow::CommandWindow)|| gInterface.CheckWindow(ObjWindow::PetInfo)|| gInterface.CheckWindow(ObjWindow::Shop)|| gInterface.CheckWindow(ObjWindow::Store)|| gInterface.CheckWindow(ObjWindow::OtherStore)|| gInterface.CheckWindow(ObjWindow::Character)|| gInterface.CheckWindow(ObjWindow::DevilSquare)|| gInterface.CheckWindow(ObjWindow::BloodCastle)|| gInterface.CheckWindow(ObjWindow::CreateGuild)|| gInterface.CheckWindow(ObjWindow::GuardNPC)|| gInterface.CheckWindow(ObjWindow::SeniorNPC)|| gInterface.CheckWindow(ObjWindow::GuardNPC2)|| gInterface.CheckWindow(ObjWindow::CastleGateSwitch)|| gInterface.CheckWindow(ObjWindow::CatapultNPC)|| gInterface.CheckWindow(ObjWindow::CrywolfGate)|| gInterface.CheckWindow(ObjWindow::IllusionTemple)|| gInterface.CheckWindow(ObjWindow::HeroList)|| gInterface.CheckWindow(ObjWindow::ChatWindow)|| gInterface.CheckWindow(ObjWindow::FastMenu)|| gInterface.CheckWindow(ObjWindow::Options)|| gInterface.CheckWindow(ObjWindow::Help)|| gInterface.CheckWindow(ObjWindow::FastDial)|| gInterface.CheckWindow(ObjWindow::SkillTree)|| gInterface.CheckWindow(ObjWindow::GoldenArcher1)|| gInterface.CheckWindow(ObjWindow::GoldenArcher2)|| gInterface.CheckWindow(ObjWindow::LuckyCoin1)|| gInterface.CheckWindow(ObjWindow::LuckyCoin2)|| gInterface.CheckWindow(ObjWindow::NPC_Duel)|| gInterface.CheckWindow(ObjWindow::NPC_Titus)|| gInterface.CheckWindow(ObjWindow::CashShop)|| gInterface.CheckWindow(ObjWindow::Lugard)|| gInterface.CheckWindow(ObjWindow::QuestList1)|| gInterface.CheckWindow(ObjWindow::QuestList2)|| gInterface.CheckWindow(ObjWindow::Jerint)|| gInterface.CheckWindow(ObjWindow::FullMap)|| gInterface.CheckWindow(ObjWindow::NPC_Dialog)|| gInterface.CheckWindow(ObjWindow::GensInfo)|| gInterface.CheckWindow(ObjWindow::NPC_Julia)|| gInterface.CheckWindow(ObjWindow::NPC_ChaosMix)|| gInterface.CheckWindow(ObjWindow::ExpandInventory)|| gInterface.CheckWindow(ObjWindow::ExpandWarehouse)|| gInterface.CheckWindow(ObjWindow::MuHelper)
#define CheckTAS_WINDOWS4 gInterface.CheckWindow(Inventory)|| gInterface.CheckWindow(Character)|| gInterface.CheckWindow(Warehouse)|| gInterface.CheckWindow(Shop) || gInterface.CheckWindow(ChaosBox)|| gInterface.CheckWindow(Trade)|| gInterface.CheckWindow(Store)|| gInterface.CheckWindow(OtherStore)|| gInterface.CheckWindow(LuckyCoin1) || gInterface.CheckWindow(NPC_ChaosMix)|| gInterface.CheckWindow(MoveList)
#define CheckTAS_WINDOWS5 gInterface.CheckWindow(ObjWindow::MoveList) || gInterface.CheckWindow(ObjWindow::CashShop) || gInterface.CheckWindow(ObjWindow::SkillTree) || gInterface.CheckWindow(ObjWindow::FullMap)|| (gInterface.CheckWindow(Inventory)&& gInterface.CheckWindow(ExpandInventory)&& gInterface.CheckWindow(Store))|| (gInterface.CheckWindow(Inventory)&& gInterface.CheckWindow(Warehouse)&& gInterface.CheckWindow(ExpandWarehouse))
#define CheckTAS_WINDOWS6 gInterface.CheckWindow(Inventory)|| gInterface.CheckWindow(Character)|| gInterface.CheckWindow(Warehouse)|| gInterface.CheckWindow(Shop)|| gInterface.CheckWindow(ChaosBox)|| gInterface.CheckWindow(Trade)|| gInterface.CheckWindow(Store)|| gInterface.CheckWindow(OtherStore)|| gInterface.CheckWindow(LuckyCoin1)|| gInterface.CheckWindow(NPC_ChaosMix)|| gInterface.CheckWindow(MoveList)
enum TAS_RenderFile
{
	BTN_NEX_NEW = 0x7E59,
	BTN_PREV_NEW = 0x7E5A,

	BTN_MENU_OFFSET = 0x17A3C,
	BG_IMG_OFFSET = 0x17A3D,
	MP_IMG_OFFSET = 0x17A40,
	MP_IMG_ENDSET = 0x1C92D,
	HP_IMG_ENDSET = 0x1C92E,
	HP_IMG_GRESET = 0x17A41,
	HP_IMG_REDSET = 0x17A42,
	BG_IMG_HDLSET = 0x17A43,
	BG_IMG_HDRSET = 0x17A44,	
	BG_IMG_CHARIC = 0x17A45,	

	BG_IMG_PERS = 0x17AEE,
	BG_IMG_NUM2 = 0x17AEF,

	HP_FACER	= 0x17AF0,
	HP_FACEB	= 0x17AF1,
	HP_MANA		= 0x17AF2,
	HP_SDFACE	= 0x17AF3,
};