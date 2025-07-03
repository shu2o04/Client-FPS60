#include "stdafx.h"
#include <Windows.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "Common.h"
#include "CustomCommandInfo.h"
#include "CustomEventTime.h"
#include "Interface.h"
#include "Import.h"
#include "TAS_DameRender.h"
#include "CSCharacterS13.h"
#include "TMemory.h"
#include "Defines.h"
#include "TAS_PKSystem.h"
#include "OffTrade.h"
#include "Protect.h"
#include "Protocol.h"
#include "PrintPlayer.h"
#include "User.h"
#include "Util.h"
#include "Offset.h"
#include "CustomCloak.h"
#include "ChatExpanded.h"
#include "Camera.h"
#include "TrayModeNew.h"
#include "Controller.h"
#include "postInterface.h"
#include "InterEx.h"
#include "Central.h"
#include "CustomFont.h"
#include "CustomEventTime.h"
#include "WindowsStruct.h"
#include "CMacroUIEx.h"
#include "PartySearchSettings.h"
#include "PartySearch.h"
#include "Config.h"
#include "time.h"
#include "CustomLuckySpin.h"
#include "CustomJewelBank.h"
#include "Ranking.h"
#include "TAS_ResetChange.h"
#include "Bytes.h"
#include "MuHelper.h"
#include "MessHacking.h"
#include "GuildUpgrade.h"
#include "CustomRankUser.h"
#include "Item.h"
#include "CB_ArenaPvP.h"
#if CHAOS_RATE_FIX
#include "ChaosMachine.h"
#endif
#if(SO_LUONG_BOSS)
#include "TAS_Invasions.h"
#endif
#include "TAS_CharacterList.h"
#include "TAS_DrawBoxAtm.h"
#include "TAS_Invasions.h"
#include "ThueFlag.h"
#include "TAS_ToolKit.h"
#include "TAS_MobileAvt.h"
#include "TAS_CongHuongV2.h"
#include "TAS_ThanMa.h"
#include "TAS_CtcMini.h"
#include "TAS_CongPoint.h"
#include "TAS_ItemTrader.h"
#include "TAS_Relife.h"
#include "TAS_MocNapNew.H"
#include "TAS_DrawFPS.h"
#include "TAS_HonHoan.h"
#include "TAS_DanhHieu.h"
#include "TAS_QuanHam.h"
#include "TAS_TuChan.h"
#include "TAS_NewVip.h"
#include "TAS_ChangePass.h"
#include "TAS_DameBoss.h"
#if NEWXSHOP
#include "TAS_xShop.h"
#include "InterfaceElemental.h"
#endif
#include "TAS_Intros.h"
#include "TAS_SoiItemNew.h"
#include "TAS_DungLuyen.h"
#include "TAS_InterSS2.h"
#include "MiniMapTron.h"
#include "MiniMap.h"
#include "TAS_Harmony.h"
#include "TAS_ItemLocker.h"
#include "TAS_FixSolution.h"
#include "CameraMove.h"
#include "Widescreen.h"
#include "Extras.h"
#include "SmoothCamera.h"
using namespace std;
Interface gInterface;

void Interface::DrawAnimatedGUI(short ObjectID, float PosX, float PosY)
{
	this->Data[ObjectID].X = PosX;
	this->Data[ObjectID].Y = PosY;
	this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	// ----
	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}
void Interface::DrawColoredAnimatedGUI(short ObjectID, float X, float Y, DWORD Color)
{
	this->Data[ObjectID].X = X;
	this->Data[ObjectID].Y = Y;
	this->Data[ObjectID].MaxX = X + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY = Y + this->Data[ObjectID].Height;
	// ----
	pDrawColorButton(this->Data[ObjectID].ModelID, X, Y,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, Color);
}
void Interface::DrawAnimatedButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	//if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	//{
	this->Data[ObjectID].X = PosX;
	this->Data[ObjectID].Y = PosY;
	this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	//}
	// ----
	pDrawButton(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY);
}
void Interface::RenderObjectSystem()
{	

	gRanking.BingImg();
	gFpsView.RenderObjectFps();
	#if RELIFE
	G_TASRelife.BingRelife();
	#endif
	#if(HT_THUE_FLAG)
	ThueFlag.Bind();
#	endif	
	#if(NOTICE_PKSYSTEM)
	gPKSys.m_DataNoticePK.clear();
	#endif
	#if BXHDAME
	gDmgBoss.DAMECLEAR();
	#endif
	gTaiKhoan.BinObeject();
	gPartySearch.loadBind();
	InitEncDec();

	#if ADD_POINT
	gAddPoint.BingObjectRenderAddPoint();
	#endif

	this->BindObject(TAS_Ranking_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_Comment_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_TuChan_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_DanhHieu_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_QuanHam_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_HonHoan_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_ThueFlag_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_Relife_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_LSpin_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_MocNap_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_CuaHang_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_RsChange_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_NewVip_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_Harmony_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_ItemTrade_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_BoxAtm_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_EventTime_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_DungLuyen_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_BxhArena_BtnClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(TAS_Option_BtnClose, 0x7EC5, 36, 29, -1, -1);

	this->BindObject(CTCMINI_MAIN,		0x7A5A, 222, 260, 205, -1);
	this->BindObject(CTCMINI_TITLE,		0x7A63, 230, 67, -1, -1);
	this->BindObject(CTCMINI_FRAME,		0x7A58, 230, 15, -1, -1);
	this->BindObject(CTCMINI_FOOTER,	0x7A59, 230, 50, -1, -1);
	this->BindObject(CTCMINI_DIV,		0x7A62, 223, 21, -1, -1);
	this->BindObject(TAS_CtcMini_BtnClose, 0x7EC5, 36, 29, -1, -1);

	this->BindObject(TMC_MAIN,			0x7A5A, 222, 230, 205, -1);
	this->BindObject(TMC_TITLE,			0x7A63, 230, 67, -1, -1);
	this->BindObject(TMC_FRAME,			0x7A58, 230, 15, -1, -1);
	this->BindObject(TMC_FOOTER,		0x7A59, 230, 50, -1, -1);

	this->BindObject(Arena_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(FormZen, 0x7909, 170, 26, -1, -1);

	#if (RESETCHANGE)
	this->BindObject(TAS_RsChange_Main, 0x7A5A, 222, 303, -1, -1);
	this->BindObject(TAS_RsChange_Btn01, 0x7E54, 52, 25, -1, -1);
	this->BindObject(TAS_RsChange_Btn02, 0x7E54, 52, 25, -1, -1);
	this->BindObject(TAS_RsChange_Btn03, 0x7E54, 52, 25, -1, -1);
	this->BindObject(TAS_RsChange_Btn04, 0x7E54, 52, 25, -1, -1);
	this->BindObject(TAS_RsChange_Btn05, 0x7E54, 52, 25, -1, -1);
	#endif
	//Jewel Bank
	this->BindObject(eJewelBank_MAIN	, 0x7A5A, 222, 300, -1, -1);
	this->BindObject(eJewelBank_TITLE	, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eJewelBank_FRAME	, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eJewelBank_FOOTER	, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eJewelBank_CLOSE	, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eJewelBank_NEXT	, BTN_PREV_NEW, 20, 22, -1, -1);
	this->BindObject(eJewelBank_PREV	, BTN_NEX_NEW, 20, 22, -1, -1);
	
	this->BindObject(RankingBtnNext, BTN_PREV_NEW, 20, 22, -1, -1);
	this->BindObject(RankingBtnPrev, BTN_NEX_NEW, 20, 22, -1, -1);

	this->BindObject(eWindowMocNapClose, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eWindowIntrosClose, 0x7EC5, 36, 29, -1, -1);

	for (int i = 0; i < 150; i++)
	{
		this->BindObject(eJewelBank_WITHDRAW + i, 31743, 16, 16, -1, -1);
	}
		
	this->BindObject(eJewelBank_Count, 0x17919, 32, 16, -1, -1);

	#if(VONGQUAY_NEW)
	this->BindObject(eLuckySpin, 31461, 640, 419, -1, -1);  // 31461
	this->BindObject(eLuckySpinRoll, 0x7E54, 52, 25, -1, -1);
	this->BindObject(eLuckySpinClose, 0x7EC5, 36, 29, -1, -1);
	#endif

	this->BindObject(eMenu_MAIN,    0x7A5A, 222, 377, 205, -1);
	this->BindObject(eMenu_TITLE,	0x7A63, 230, 67, -1, -1);
	this->BindObject(eMenu_FRAME,	0x7A58, 230, 15, -1, -1);
	this->BindObject(eMenu_FOOTER,	0x7A59, 230, 50, -1, -1);
	this->BindObject(eMenu_DIV,		0x7A62, 223, 21, -1, -1);
	this->BindObject(eMenu_CLOSE,   0x7EC5, 36,  29, -1, -1);

	this->BindObject(eCustomShop_CLOSE,   0x7EC5, 36,  29, -1, -1);

	for (int i = 0; i < ButtonMenuTAS; ++i) 
	{
		this->BindObject(eMenu_OPT1 + i, 0x7A5E, 108, 29.5f, -1, -1);
	}

	this->BindObject(TAS_MAIN_ATM	,	0xC942, 13, 13, -1, -1);
	this->BindObject(TAS_MAIN_ARESET,	0xC942, 13, 13, -1, -1);
	this->BindObject(TAS_MAIN_RSCAM,	0xC942, 13, 13, -1, -1);
	this->BindObject(TAS_MAIN_ZMCAM,	0xC942, 13, 13, -1, -1);
	this->BindObject(TAS_MAIN_BOXSK,	0xC942, 13, 13, -1, -1);
	this->BindObject(TAS_ITEM_BLOCK,	0xC942, 13, 13, -1, -1);
	this->BindObject(TAS_PK_LOCK,		0xC942, 13, 13, -1, -1);
	this->BindObject(TAS_AUTO_HP,		0xC942, 13, 13, -1, -1);
	this->BindObject(TAS_AUTO_BF,		0xC942, 13, 13, -1, -1);

	for (int i = 0; i < MAX_EVENTTIME; ++i)
	{
		this->BindObject(TAS_MOVE_EVENT + i, 31461, 291, 9, -1, -1);
	}

	this->BindObject(eTIME, 30847, 106, 22, -10, 359);
	//--
	this->BindObject(TAS_Ranking_Main, 0x7A5A, 445, 364, 205, -1);

	this->BindObject(TAS_JBank_Prev, 0x7903, 25, 40, -1, -1);
	this->BindObject(TAS_JBank_Next, 0x7904, 25, 40, -1, -1);

	this->BindObject(eCommand_MAIN, 0x7A5A, 222, 300, 205, -1);
	this->BindObject(eCONFIRM_MAIN, 0x7A5A, 222, 120, 205, -1);
	this->BindObject(eCONFIRM_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eCONFIRM_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eCONFIRM_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eCONFIRM_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eCONFIRM_BTN_OK, 0x7A5B, 54, 30, -1, -1);
	this->BindObject(eCONFIRM_BTN_CANCEL, 0x7A5C, 54, 30, -1, -1);
	//Custom Store
	this->BindObject(eOFFTRADE_JoB, 0x7908, 40, 19, -1, -1);
	this->BindObject(eOFFTRADE_JoS, 0x7908, 40, 19, -1, -1);
	this->BindObject(eOFFTRADE_JoC, 0x7908, 40, 19, -1, -1);
	this->BindObject(eOFFTRADE_WCC, 0x7908, 40, 19, -1, -1);
	this->BindObject(eOFFTRADE_WCP, 0x7908, 40, 19, -1, -1);
	this->BindObject(eOFFTRADE_WCG, 0x7908, 40, 19, -1, -1);
	this->BindObject(eOFFTRADE_OPEN, 0x7BFD, 108, 30, -1, -1);
	this->BindObject(eSTORE_CLOSE, 0x7BFD, 108, 30, -1, -1);
	this->BindObject(ePLAYER_POINT, 31460, 3, 3, -1, -1);
	this->BindObject(eNULL_MAP, 31461, 128, 128, -1, -1);
	
	this->BindObject(eCamera3DInit, 31659, 17, 18, -1, -1);
	this->BindObject(eCamera3DSwitch, 31659, 17, 18, -1, -1);
	this->Data[eTIME].OnShow = true;
	if(gProtect.m_MainInfo.CustomInterfaceType == 4)
	{
		this->BindObject(ButtonSettings, 51522, 13, 13, -1, -1);
		this->BindObject(ButtonStart, 51522, 13, 13, -1, -1);
		this->BindObject(ButtonStop, 51522, 13, 13, -1, -1);
	}
	else
	{
		this->BindObject(ButtonSettings, 31761, 18, 13.3, -1, -1);
		this->BindObject(ButtonStart, 31762, 18, 13.3, -1, -1);
		this->BindObject(ButtonStop, 31763, 18, 13.3, -1, -1);
	}
	this->BindObject(ButtonStartAttack, 31593, 15, 15, -15, -15);
	switch(gProtect.m_MainInfo.CustomInterfaceType)
	{
		case 2:
		this->BindObject(eMenu, 0x7906, 14, 13, -1, -1);
		this->BindObject(MINIMAP_FRAME, 31608, 154, 162, -10, 359);
		this->BindObject(MINIMAP_TIME_FRAME, 31609, 134.0, 37.0, -10, 359);
		this->BindObject(MINIMAP_BUTTOM, 31617, 38.0f, 24.0f, -10, 569);
		this->BindObject(eDragonLeft, 2337, 108.0, 45.0, 0.0, 385);
		this->BindObject(eDragonRight, 2336, 108.0, 45.0, 532.0, 385);
		this->BindObject(eParty, iNewParty, 25, 25, 348, 449);
		this->BindObject(eCharacter, iNewCharacter, 25, 25, 379, 449);
		this->BindObject(eInventory, iNewInventory, 25, 25, 409, 449);
		this->BindObject(eFriend, iNewWinpush, 52, 18, 581, 432);
		this->BindObject(eFastMenu, iNewFastMenu, 53, 19, 5, 432);
		this->BindObject(eGuild, iNewGuild, 52, 18, 581, 454);
		this->BindObject(eZen, 0x17915, 113, 19, -1, -1);
		this->BindObject(eMainMenuSet, 0x17916, 160, 19, -1, -1);
		break;
		case 4:
		if (gProtect.m_MainInfo.CustomMenuType == 1)
		{
			this->BindObject(eMenu, 0x7906, 102, 29, -1, -1);
		}
		else
		{
			this->BindObject(eMenu, 51522, 19, 19, -1, -1);
		}
		//Ex700
		this->BindObject(chatbackground, 51545, 300.0f, 128.0f, -10, 569);
		this->BindObject(eShop, 51522, 19.5f, 19.5f, -1, -1);
		this->BindObject(eCharacter, 51522, 19.5f, 19.5f, -1, -1);
		this->BindObject(eInventory, 51522, 19.5f, 19.5f, -1, -1);
		break;
		default:
		this->BindObject(eMenu, BTN_MENU_OFFSET, 16, 13, -1, -1);
		break;
	}
	this->ClickTime = 0;

	SetRange((LPVOID)0x00842086, 5, ASM::NOP);
	SetRange((LPVOID)0x0084234F, 5, ASM::NOP);
	SetRange((LPVOID)0x008423C3, 5, ASM::NOP);
	SetOp((LPVOID)oLoadSomeForm_Call, this->LoadImages, ASM::CALL);
	SetOp((LPVOID)oDrawInterface_Call, this->Work, ASM::CALL);
	#if CMUI_RENDER_ZEN
	SetRange((LPVOID)0x00835116, 5, ASM::NOP);
	SetOp((LPVOID)0x00835116, this->DrawZenAndRud, ASM::CALL);
	#endif

}
void Interface::LoadModels()
{
	pLoadModel(406, "Data\\Custom\\Bmd\\VIP1\\", "musign", -1);
	pLoadTexture(406, "Custom\\Bmd\\VIP1\\", 0x2901, 0x2600, 1);
	pLoadModel(407, "Data\\Custom\\Bmd\\VIP2\\", "musign", -1);
	pLoadTexture(407, "Custom\\Bmd\\VIP2\\", 0x2901, 0x2600, 1);
	pLoadModel(408, "Data\\Custom\\Bmd\\VIP3\\", "musign", -1);
	pLoadTexture(408, "Custom\\Bmd\\VIP3\\", 0x2901, 0x2600, 1);
	pInitModelData2();
}

int Interface::LoadImg(char * Folder, DWORD ID)
{
	return pLoadImage(Folder, ID, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
}


void LoadMapRender()
{
	
	LoadBitmapA("TAS\\MainBoard.tga", 0x1791E, GL_LINEAR_MIPMAP_LINEAR, 0x2901, 1, 0);
	LoadBitmapA("TAS\\MinRanking.tga", 0x1791F, GL_LINEAR_MIPMAP_LINEAR, 0x2901, 1, 0);
	LoadBitmapA("TAS\\Text_RankingBoard.tga", 0x17920, GL_LINEAR_MIPMAP_LINEAR, 0x2901, 1, 0);
	LoadBitmapA("TAS\\Text_EventBoard.tga", 0x17921, GL_LINEAR_MIPMAP_LINEAR, 0x2901, 1, 0);
	LoadBitmapA("TAS\\Status.tga", 0x17922, GL_LINEAR_MIPMAP_LINEAR, 0x2901, 1, 0);
	LoadBitmapA("TAS\\Other\\BG_BAR_BOSS.tga", 0x17924, GL_LINEAR_MIPMAP_LINEAR, 0x2901, 1, 0);
	LoadBitmapA("TAS\\Other\\HP_BAR_BOSS.tga", 0x17925, GL_LINEAR_MIPMAP_LINEAR, 0x2901, 1, 0);
	LoadBitmapA("TAS\\Other\\BG_BLK_BOSS.tga", 0x17926, GL_LINEAR_MIPMAP_LINEAR, 0x2901, 1, 0);
	LoadBitmapA("TAS\\TAS_Porcento.tga", 531126, 0x2601, 0x2901, 1, 0);
	LoadBitmapA("TAS\\Page_Porcento.tga", 0x1791A, 0x2601, 0x2901, 1, 0);
	LoadBitmapA("TAS\\TAS_NumberWhite.tga", 31337, 9729, 10496, 1, 0);
	LoadBitmapA("TAS\\TAS_NumberYello.tga",	BG_IMG_NUM2, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
}

void Interface::LoadImages()
{
	gRanking.LoadImg();

	LoadMapRender();

	//g_DamageRender.Load();
	#if(TAS_HONHOAN)
	gHonHoan.LoadImageHonHoan();
	#endif
	#if TAS_DANHHIEU
	gDanhHieu.LoadImageDanhHieu();
	#endif
	#if TAS_QUANHAM
	gQuanHam.LoadImageQuanHam();
	#endif
	#if TAS_TUCHAN
	gTuLuyen.LoadImageTuLuyen();
	#endif
	#if TAS_NEWVIP 
	gNewVip.LoadImageNewVip();
	#endif
	#if(TAS_STYLE == 1)
	mTAS.LoadImg();
	#endif
	LoadBitmapA("TAS\\CheckBox.tga", 0x17919, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("TAS\\character_ex.tga", 0x1791C, 0x2601, 0x2901, 1, 0);

	if(gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		LoadBitmapA("TAS\\InterfaceS2\\Inventory\\Item_Money.jpg", 0x17915, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);			//Zen
	}
	else
	{
		#if TYPEZEN != 0
		pLoadImage("TAS\\iMoney.tga", 0x17915, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, 1, 0);
		#else
		pLoadImage("TAS\\newui_item_money.tga", 0x7909, 0x2601, 0x2901, 1, 0);
		#endif
	}
    pLoadImage("TAS\\Other\\TAS-logo.tga", 0x17905, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, 1, 0);
	pLoadImage("TAS\\Other\\ButtonA.tga", 0x17908, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, 1, 0);
	pLoadImage("TAS\\Other\\ButtonB.tga", 0x17909, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, 1, 0);
	pLoadImage("TAS\\Other\\CTC.tga", 0x17912, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, 1, 0);
	pLoadImage("TAS\\Other\\ATM.tga", 0x17918, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, 1, 0);
	pLoadImage("TAS\\Other\\MessTAS.tga", 0x1791B, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, 1, 0);

	pLoadImage("TAS\\CTCMini\\CharPoint.tga"						, 32506  , GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("TAS\\CTCMini\\OtherCharPoint.tga"				, 32507  , GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("TAS\\CTCMini\\CTCMiniMap.tga"					, 32583  , GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("TAS\\CTCMini\\UiCtc.tga"							, 32584  , GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);	
	pLoadImage("TAS\\CTCMini\\StartCTC.tga"						, 32585  , GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("TAS\\CTCMini\\WinCTC.tga"						, 32586  , GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("TAS\\CTCMini\\LoseCTC.tga"						, 32589  , GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0); 
	pLoadImage("TAS\\CTCMini\\DialogCTC.tga"						, 32588  , GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
	
	pLoadImage("TAS\\Next.tga"	, 0x7903, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\Previous.tga", 0x7904, 0x2601, 0x2901, 1, 0);
	
	#if(PARTYSEARCH==1)
	gInterface.LoadImg("TAS\\PartySearch_Title.tga", 0x7E98);
	gInterface.LoadImg("TAS\\Info_Block.tga", 0x7E99);
	#endif
	pLoadImage("TAS\\mini_map_ui_party.tga", 61520, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	pLoadImage("TAS\\Nop\\none.tga", 31461, 0x2601, 0x2900, 1, 0);
	pLoadImage("TAS\\BtnMoveM.tga", 0x7906, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\Button.tga", 0x7908, 0x2601, 0x2900,1,0);
	pLoadImage("TAS\\Maps\\PlayerPoint.jpg", 31460, 0x2600, 0x2900, 1, 0);
	pLoadImage("TAS\\Maps\\edBtUcx.tga", 31463, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("TAS\\Maps\\edBtUcx_1.tga", 31464, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("TAS\\Maps\\BackGrMaps.tga", 31465, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("TAS\\Maps\\mini_map_ui_blacksmith.tga", 31466, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("TAS\\Maps\\mini_map_ui_Potion.tga", 31467, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("TAS\\Maps\\mini_map_ui_baul.tga", 31468, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("TAS\\Maps\\mini_map_ui_Que.tga", 31469, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("TAS\\Maps\\mini_map_ui_monsterred.tga", 31471, 0x2601, 0x2900, 1, 0); //-- Dungeon Red
	pLoadImage("TAS\\Maps\\mini_map_ui_monsterblue.tga", 31472, 0x2601, 0x2900, 1, 0); //-- Dungeon Blue
	pLoadImage("TAS\\Maps\\Frame.tga" , 50000, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\Maps\\map_radar.tga", 61519, 0x2601, 0x2901, 1, 0);

	pLoadImage("TAS\\ToolTips\\tooltip_bg01.tga", 61511, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\ToolTips\\tooltip_bg02.tga", 61512, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\ToolTips\\tooltip_bg03.tga", 61513, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\ToolTips\\tooltip_bg04.tga", 61514, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\ToolTips\\tooltip_bg06.tga", 61515, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\ToolTips\\tooltip_bg07.tga", 61516, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\ToolTips\\tooltip_bg08.tga", 61517, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\ToolTips\\tooltip_bg09.tga", 61518, 0x2601, 0x2901, 1, 0);

	pLoadImage("TAS\\PopUp\\popupbg01.tga", 71511, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\PopUp\\popupbg02.tga", 71512, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\PopUp\\popupbg03.tga", 71513, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\PopUp\\popupbg04.tga", 71514, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\PopUp\\popupbg06.tga", 71515, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\PopUp\\popupbg07.tga", 71516, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\PopUp\\popupbg08.tga", 71517, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\PopUp\\popupbg09.tga", 71518, 0x2601, 0x2901, 1, 0);

	pLoadImage("TAS\\popup_line_m.tga", 71519, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\popup_line_s.tga", 71520, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\Render_buttom_1.tga", 71521, 0x2601, 0x2901, 1, 0); 
	pLoadImage("TAS\\Render_buttom_2.tga", 71522, 0x2601, 0x2901, 1, 0); 
	pLoadImage("TAS\\Render_buttom_3.tga", 71524, 0x2601, 0x2901, 1, 0); 
	pLoadImage("TAS\\RenderBits_Sound.tga", 71523, 0x2601, 0x2901, 1, 0); 
	pLoadImage("TAS\\newui_option_volume01.tga", 31596, 0x2601, 0x2901, 1, 0); 
	pLoadImage("TAS\\newui_option_volume02.tga", 31597, 0x2601, 0x2901, 1, 0); 

	pLoadImage("TAS\\Party\\newui_Party_Back.tga", 81520, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\Party\\newui_Party_flag.tga", 81521, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\Party\\newui_Party_HpBar.jpg", 81522, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\Party\\newui_Party_ManaBar.jpg", 81523, 0x2601, 0x2901, 1, 0);
	pLoadImage("TAS\\Party\\newui_Party_X.tga", 81524, 0x2601, 0x2901, 1, 0);

	LoadBitmapA("TAS\\newui_SW_Minimap_Frame.tga", 31608, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("TAS\\newui_SW_Time_Frame.tga", 31609, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("TAS\\newui_SW_MiniMap_Bt_clearness.jpg", 31617, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
	//
	pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\Decor.tga", 87968, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\InterfaceBar.tga", 87969, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\Main_Skillbox.tga", 51500, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\newui_skillbox2.jpg", 31313, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\item_pbtnbg.tga", 61547, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\skill_render.tga", 61546, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
	switch(gProtect.m_MainInfo.CustomInterfaceType) 
	{
		case 0:
			LoadBitmapA("TAS\\MacroUI\\MacroUI_Main.tga", 51550, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("TAS\\MacroUI\\MacroUI_BSetup.tga", 51546, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("TAS\\MacroUI\\MacroUI_BStart.tga", 51547, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("TAS\\MacroUI\\MacroUI_Stop.tga", 51548, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("TAS\\MacroUI\\MacroUI_Bar.jpg", 51549, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("TAS\\MacroUI\\MacroUI_Menu.tga", 51553, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("TAS\\MacroUI\\MacroUI_BResetAuto.tga", 151554, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("TAS\\MacroUI\\MacroUI_BDanhHieu.tga", 151555, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("TAS\\MacroUI\\MacroUI_BReset.tga", 151556, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("TAS\\MacroUI\\MacroUI_BCamera.tga", 151557, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("TAS\\MacroUI\\MacroUI_BAtm.tga", 151558, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("TAS\\MacroUI\\MacroUI_BInfo.tga", 151559, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("TAS\\MacroUI\\MacroUI_BBlock.tga", 151560, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("TAS\\MacroUI\\Btn_A_AutoHP.tga", 151561, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
			LoadBitmapA("TAS\\MacroUI\\Btn_A_Buff.tga", 151562, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("TAS\\MacroUI\\MacroUI_MenuNew.tga", BTN_MENU_OFFSET, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		break;
		case 2:
		LoadBitmapA("TAS\\InterfaceS2\\Inventory\\newui_item_weapon(L).tga", 0x7A82, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);	//VuKhi 1
		LoadBitmapA("TAS\\InterfaceS2\\Inventory\\newui_item_weapon(R).tga", 0x7A83, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);	//VuKhi 2
		LoadBitmapA("TAS\\InterfaceS2\\Inventory\\newui_item_cap.tga", 0x7A7F, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);			//Mu
		LoadBitmapA("TAS\\InterfaceS2\\Inventory\\newui_item_upper.tga", 0x7A84, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);		//Au
		LoadBitmapA("TAS\\InterfaceS2\\Inventory\\newui_item_lower.tga", 0x7A86, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);		//Quan
		LoadBitmapA("TAS\\InterfaceS2\\Inventory\\newui_item_gloves.tga", 0x7A85, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);		//Gang
		LoadBitmapA("TAS\\InterfaceS2\\Inventory\\newui_item_boots.tga", 0x7A7E, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);		//Giay
		LoadBitmapA("TAS\\InterfaceS2\\Inventory\\newui_item_wing.tga", 0x7A81, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);			//Wing Slot 7
		LoadBitmapA("TAS\\InterfaceS2\\Inventory\\newui_item_fairy.tga", 0x7A80, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);		//SlotPet
		LoadBitmapA("TAS\\InterfaceS2\\Inventory\\newui_item_necklace.tga", 0x7A88, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);		//Pen
		LoadBitmapA("TAS\\InterfaceS2\\Inventory\\newui_item_ring.tga", 0x7A87, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);			//Ring
		LoadBitmapA("TAS\\InterfaceS2\\Inventory\\setitem.jpg", 0x17916, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);			//TopLine

		LoadBitmapA("TAS\\MacroUI\\MacroUI_MenuNew.tga", BTN_MENU_OFFSET, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\Item_Back01.tga", 61522, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\DragonRight.tga", 2336, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\DragonLeft.tga", 2337, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\Menu_left.jpg", 31292, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0); //replace
		LoadBitmapA("TAS\\InterfaceS2\\Menu_SD.jpg", 31300, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\Menu_right.jpg", 31294, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0); //replace
		LoadBitmapA("TAS\\InterfaceS2\\Menu_middle.jpg", 31293, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0); //replace
		LoadBitmapA("TAS\\InterfaceS2\\Menu_Red.jpg", 0x7A42, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);//replace
		LoadBitmapA("TAS\\InterfaceS2\\Menu_Green.jpg", 0x7A41, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);//replace
		LoadBitmapA("TAS\\InterfaceS2\\Menu_Blue.jpg", 0x7A40, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);//replace
		LoadBitmapA("TAS\\InterfaceS2\\Menu_AG.jpg", 31299, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\Boton\\Menu_fastmenu.jpg", iNewFastMenu, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\Boton\\Menu_Inventory.jpg", iNewInventory, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\Boton\\Menu_Character.jpg", iNewCharacter, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\Boton\\Menu_Party.jpg", iNewParty, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\Boton\\Menu_friend.jpg", iNewWinpush, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\Boton\\Menu_guild.jpg", iNewGuild, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\skillboxR.jpg", 0x700003, 0x2601, 0x2901, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\newui_skill.jpg", 31308, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\newui_skill2.jpg", 31309, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\newui_skill3.jpg", 31311, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\newui_command.jpg", 31310, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\newui_non_skill.jpg", 31314, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\newui_non_skill2.jpg", 31315, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\newui_non_skill3.jpg", 31317, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\newui_skillbox.jpg", 31312, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\newui_skillbox2.jpg", 31313, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\Menu\\Stats.jpg", 31352, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\Menu\\StatsDL.jpg", 51291, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\Menu\\Stats2.jpg", 51292, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\Menu\\Level_box.jpg", 35353, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\Menu\\Level_button.jpg", 51290, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\chat\\nis_vframe.jpg", 51551, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\chat\\nis_rsframe.tga", 51552, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\chat\\nis_rsframe_up.jpg", 51553, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\chat\\nis_rsframe_m.jpg", 51554, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\chat\\nis_rsframe_down.jpg", 51555, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\chat\\nis_hframe.jpg", 31275, 9729, 10496, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\Chat\\dialogue1.tga", 51530, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\Chat\\dialogue2.tga", 51531, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterfaceS2\\Chat\\dialogue2_1.jpg", 51532, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		break;
		case 4:
		LoadBitmapA("TAS\\InterTAS\\BACKGROUND.tga", BG_IMG_OFFSET, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\BLUE_MP_128.tga", MP_IMG_OFFSET, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\BLACK_MP_128.tga", MP_IMG_ENDSET, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\GREEN_HP_128.tga", HP_IMG_GRESET, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\RED_HP_128.tga", HP_IMG_REDSET, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\BLACK_HP_128.tga", HP_IMG_ENDSET, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\HEADER_DRA_L.tga", BG_IMG_HDLSET, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\HEADER_DRA_R.tga", BG_IMG_HDRSET, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("TAS\\InterTAS\\BarFaceHP.tga", HP_FACER, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\BarFaceBG.tga", HP_FACEB, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\BarFaceMN.tga", HP_MANA, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\BarFaceSD.tga", HP_SDFACE, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("TAS\\InterTAS\\Main_I5.jpg", 31299, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\Main_I4.jpg", 31300, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\newui_skillbox2.tga", 31313, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\newui_skillbox1.tga", 31312, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\Main_Skillbox.tga", 51500, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("TAS\\InterTAS\\Buttom_empty_small.tga", 61525, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\chat_bg01.tga", 61550, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\chat_bg02.tga", 61551, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\chat_bg03.tga", 61534, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\Chat_I5.tga", 61548, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("TAS\\InterTAS\\newui_chat_back.tga", 61549, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\Main_IE_Buttons.tga", 0x901, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\skill_render.tga", 61546, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\winPet_I1.tga", 61545, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\InterTAS\\item_pbtnbg.tga", 61547, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("TAS\\MacroUI\\MacroUI_Main.tga",		51550, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\MacroUI\\MacroUI_BSetup.tga",		51546, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\MacroUI\\MacroUI_BStart.tga",		51547, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\MacroUI\\MacroUI_Stop.tga",		51548, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\MacroUI\\MacroUI_Bar.jpg",		51549, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\MacroUI\\MacroUI_Menu.tga",		51553, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\MacroUI\\MacroUI_BResetAuto.tga",	151554, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\MacroUI\\MacroUI_BDanhHieu.tga",	151555, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\MacroUI\\MacroUI_BReset.tga",		151556, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\MacroUI\\MacroUI_BCamera.tga",	151557, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\MacroUI\\MacroUI_BAtm.tga",		151558, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\MacroUI\\MacroUI_BInfo.tga",		151559, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\MacroUI\\MacroUI_BBlock.tga",		151560, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\MacroUI\\Btn_A_AutoHP.tga",		151561, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\MacroUI\\Btn_A_Buff.tga",			151562, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);

		LoadBitmapA("TAS\\Nop\\none.tga", 31303, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\Nop\\none.tga", 31304, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\Nop\\none.tga", 31305, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\Nop\\none.tga", 31306, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\Nop\\none.tga", 31307, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\Nop\\none.tga", 51522, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\Nop\\none.tga", 31294, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\Nop\\none.tga", 31295, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		LoadBitmapA("TAS\\Nop\\none.tga", 31292, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP, 1, 0);
		break;
	}
	if( gProtect.m_MainInfo.DisableEffectRemake == 0 )
	{
		pLoadImage("Effect\\flare01.jpg", 52002, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\flareRed.jpg", 52230, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\JointLaser01.jpg", 52224, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\hikorora.jpg", 52379, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\flareBlue.jpg", 52229, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\bostar3_R.jpg", 32614, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\line_of_big_R.jpg", 32772, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, 1, 0);
		pLoadImage("Effect\\flare01.jpg", 42134, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, 1, 0);
	}
	//--
	if(gProtect.m_MainInfo.DisableCustomCloack == 0)
	{
		gCloak.LoadTexture();
	}
	
	//--
	#if(NOTICE_MES==1)
	pDrawMessage ( Notice_1, 0 );
	pDrawMessage ( Notice_2, 1 );
	#endif
	pLoadSomeForm();
}

void Interface::WindowsKG()
{	
	gFpsView.MainFps();
	char interaltas[500];
	char ClassName[11] = { 0 };
	memcpy(ClassName, gObjUser.lpPlayer->Name, sizeof(gObjUser.lpPlayer->Name));
	int gZoomCurrent = (*(float*)(0x00D27BFC));
	if (gInterface.validar == 0)
	{
		//if (strcmp(ClassName, "ADMIN") == 0)
		//{
		//	sprintf_s(interaltas, sizeof(interaltas), "%s | %s | Zoom: %d | MX: %d | MY: %d | MapID: %d (%d/%d)", 
		//	gProtect.m_MainInfo.WindowName,
		//	gFpsView.FPS_REAL,
		//	gZoomCurrent,
		//	pCursorX,
		//	pCursorY,
		//	*(WORD*)0x00E61E18, gObjUser.CoordenadaX, gObjUser.CoordenadaY);
		//	SetWindowText(pGameWindow, interaltas);
		//}
		//else
		//{
		//	sprintf_s(interaltas, sizeof(interaltas), "%s | %s | Zoom: %d | MapID: %d (%d/%d)",
		//		gProtect.m_MainInfo.WindowName,
		//		gFpsView.FPS_REAL,
		//		gZoomCurrent,
		//		*(WORD*)0x00E61E18, gObjUser.CoordenadaX, gObjUser.CoordenadaY);
		//	SetWindowText(pGameWindow, interaltas);
		//}
	}
}

void Interface::BindObject(short MonsterID, DWORD ModelID, float Width, float Height, float X, float Y)
{
	this->Data[MonsterID].EventTick	= 0;
	this->Data[MonsterID].OnClick	= false;
	this->Data[MonsterID].OnShow	= false;
	this->Data[MonsterID].ModelID	= ModelID;
	this->Data[MonsterID].Width		= Width;
	this->Data[MonsterID].Height	= Height;
	this->Data[MonsterID].X			= X;
	this->Data[MonsterID].Y			= Y;
	this->Data[MonsterID].MaxX		= X + Width;
	this->Data[MonsterID].MaxY		= Y + Height;
	this->Data[MonsterID].Attribute	= 0;
}

void Interface::DrawGUI(short ObjectID, float PosX, float PosY)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X		= PosX;
		this->Data[ObjectID].Y		= PosY;
		this->Data[ObjectID].MaxX	= PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY	= PosY + this->Data[ObjectID].Height;
	}

	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY,this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}

void Interface::DrawGUI2(short ObjectID, float PosX, float PosY)
{
	this->Data[ObjectID].X		= PosX;
	this->Data[ObjectID].Y		= PosY;
	this->Data[ObjectID].MaxX	= PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY	= PosY + this->Data[ObjectID].Height;

	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY,this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}

void Interface::DrawGUI3(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	this->Data[ObjectID].X		= PosX;
	this->Data[ObjectID].Y		= PosY;
	this->Data[ObjectID].MaxX	= PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY	= PosY + this->Data[ObjectID].Height;

	RenderBitmap(this->Data[ObjectID].ModelID, PosX, PosY,this->Data[ObjectID].Width, this->Data[ObjectID].Height,0,0,ScaleX,ScaleY,1,1,0);
}

void Interface::DrawIMG(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X		= PosX;
		this->Data[ObjectID].Y		= PosY;
		this->Data[ObjectID].MaxX	= PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY	= PosY + this->Data[ObjectID].Height;
	}

	RenderBitmap(this->Data[ObjectID].ModelID, PosX, PosY,this->Data[ObjectID].Width, this->Data[ObjectID].Height,0,0,ScaleX,ScaleY,1,1,0);
}
void Interface::ResetDrawIMG(short ObjectID)
{
	if( this->Data[ObjectID].X != -1 || this->Data[ObjectID].Y != -1 )
	{
		this->Data[ObjectID].X		= -1;
		this->Data[ObjectID].Y		= -1;
		this->Data[ObjectID].MaxX	= -1;
		this->Data[ObjectID].MaxY	= -1;
	}
}
#if(BAUCUA)
int Custom_dem;
bool Custom_dem_b;
float VitriX1 = 150.0;
float VitriY1 = 380.0;
bool QuayLai1 = false;
int res1 = 0;
int begin_time1 = 0;
DWORD IsClickTimer;
void RunGameMini()
{
	//điều kiện
	if (gInterface.CheckWindow(Character)
		|| gInterface.CheckWindow(ObjWindow::CashShop)
		|| gInterface.CheckWindow(ObjWindow::SkillTree)
		|| gInterface.CheckWindow(ObjWindow::FullMap)
		|| gInterface.CheckWindow(FriendList)
		|| gInterface.CheckWindow(MoveList)
		|| gInterface.CheckWindow(Party)
		|| gInterface.CheckWindow(Quest)
		|| gInterface.CheckWindow(NPC_Devin)
		|| gInterface.CheckWindow(Guild)
		|| gInterface.CheckWindow(Trade)
		|| gInterface.CheckWindow(Warehouse)
		|| gInterface.CheckWindow(ChaosBox)
		|| gInterface.CheckWindow(CommandWindow)
		|| gInterface.CheckWindow(Shop)
		|| gInterface.CheckWindow(Inventory)
		|| gInterface.CheckWindow(Store)
		|| gInterface.CheckWindow(OtherStore)
		|| gInterface.CheckWindow(Character)
		|| gInterface.CheckWindow(DevilSquare)
		|| gInterface.CheckWindow(BloodCastle)
		|| gInterface.CheckWindow(CreateGuild)
		|| gInterface.CheckWindow(GuardNPC)
		|| gInterface.CheckWindow(SeniorNPC)
		|| gInterface.CheckWindow(GuardNPC2)
		|| gInterface.CheckWindow(CastleGateSwitch)
		|| gInterface.CheckWindow(CatapultNPC)
		|| gInterface.CheckWindow(CrywolfGate)
		|| gInterface.CheckWindow(IllusionTemple)
		|| gInterface.CheckWindow(HeroList)
		|| gInterface.CheckWindow(ChatWindow)
		|| gInterface.CheckWindow(FastMenu)
		|| gInterface.CheckWindow(Options)
		|| gInterface.CheckWindow(FastDial)
		|| gInterface.CheckWindow(SkillTree)
		|| gInterface.CheckWindow(GoldenArcher1)
		|| gInterface.CheckWindow(GoldenArcher2)
		|| gInterface.CheckWindow(LuckyCoin1)
		|| gInterface.CheckWindow(LuckyCoin2)
		|| gInterface.CheckWindow(CashShop)
		|| gInterface.CheckWindow(Lugard)
		|| gInterface.CheckWindow(QuestList1)
		|| gInterface.CheckWindow(QuestList2)
		|| gInterface.CheckWindow(GensInfo)
		|| gInterface.CheckWindow(NPC_ChaosMix)
		|| gInterface.CheckWindow(ExpandInventory)
		|| gInterface.CheckWindow(MuHelper)
		|| gInterface.CheckWindow(PetInfo)
		|| gInterface.Data[eMenu_MAIN].OnShow
		|| gInterface.Data[eEventTimePANEL_MAIN].OnShow
		|| gInterface.Data[eCommand_MAIN].OnShow
		|| gInterface.Data[eChangePass_Main].OnShow
		|| gInterface.Data[TAS_Ranking_Main].OnShow
		|| gInterface.Data[eCONFIRM_MAIN].OnShow
		|| gInterface.Data[eJewelBank_MAIN].OnShow
		|| gInterface.Data[ePARTYSETTINGS_MAIN].OnShow
		|| gInterface.Data[ePARTYSEARCH_MAIN].OnShow
		|| gInterface.Data[BAUCUA_MAIN].OnShow
		|| pMapNumber == 40)

	{
		return;
	}

}
#endif
#if(SO_LUONG_BOSS)
void Interface::DrawBtnTTBOSS()
{
	if (CheckWindow(ChatWindow) || CheckWindow(FullMap) || CheckWindow(SkillTree) || CheckWindow(CashShop) || CheckWindow(Inventory) || CheckWindow(Character)
		|| CheckWindow(Quest) || CheckWindow(Party) || CheckWindow(MuHelper) || CheckWindow(Guild) || CheckWindow(FriendList))
	{
		return;
	}
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	//if (gCentral.gDrawButton((StartX + 150) + ((CuaSoW - 160) / 2) - (110 / 2), StartY + (CuaSoH - 40), 110, 14, "Nâng Cấp",0) && (GetTickCount() - gInterface.Data[eWindow_NangCapHonHoan].EventTick) > 300)
	if (gElemental.gDrawButton(JCResto +MAX_WIN_WIDTH / 2 - 30, 0, 60, 13, "Thông Tin Boss", 0) && (GetTickCount() - gInterface.Data[eInvasionInfo].EventTick) > 300)
	{
		PMSG_RESET_SEND pMsg;
		pMsg.header.set(0xF7, 0x02, sizeof(pMsg));
		DataSend((LPBYTE)&pMsg, pMsg.header.size);
	}
}
#endif
void Interface::Work()
{
	gFixSolution.StartLoadPos();
	if (pMapNumber == 30 || pMapNumber == 31 || pMapNumber == 62)
		return;

	SmoothCamera.Camera();

	#if TAS_ITEMLOCK
	nInterface.RenderWindow();
	#endif
	#if (CUSTOM_HARMONY)
	gCustomHarmony.DrawHarmony();
	#endif
	
	#if	CUSTOM_DUNGLUYENITEM
	gMixDL.DrawWindows();
	#endif
	gInfoChar.DrawWindowInfo();
	gNewIntros.DrawWindowMocNap();
	#if(B_MOCNAP)
	gNewMocNap.DrawWindowMocNap();
	#endif	
	#if NEWXSHOP
	gNewCashShop.DrawShop();
	gElemental.DrawMessageBox();
	#endif
	#if RELIFE
	G_TASRelife.CallWindows();
	#endif
	#if(TAS_ITEMTRADE)
	gItemTrade.DrawDoiItem();
	#endif
	#if ADD_POINT
	gAddPoint.DrawStatsAddWindow();
	#endif
	#if(HT_THUE_FLAG)
	ThueFlag.Draw();
	#endif
	#if CHAOS_RATE_FIX
	InitChaosBox();
	#endif
	#if(NOTICE_PKSYSTEM)
	gPKSys.DrawNoticePKSystem();
	#endif
	#if BXHDAME
	gDmgBoss.DAMEDRAW();
	#endif
	#if(CB_EventArenaPvP)
	gCBArenaPvP.Draw();
	#endif	
	gTaiKhoan.DrawVoidDoiPass();
	#if (CongHuongV2)
	gCongHuong2.DrawWindowCongHuong();	
	#endif
	gObjUser.Refresh();
	#if (RESETCHANGE==1)
	gResetChange.DrawResetChange();
	#endif
	gBoxAtm.DrawAtmWork();
	#if(THANMA)
	gThanMa.DrawTMAllWindows();
	#endif
	//gToolKit.RunAntiHack();

	if(gObjUser.lpViewPlayer->WeaponFirstSlot >= ITEM2(4,0) && gObjUser.lpViewPlayer->WeaponFirstSlot <= ITEM2(4,255)||gObjUser.lpViewPlayer->WeaponSecondSlot >= ITEM2(4,0) && gObjUser.lpViewPlayer->WeaponSecondSlot <= ITEM2(4,255))
	{
		gInterface.PetY = 38.0f;		
	}
	else
	{
		gInterface.PetY = 26.0f;
	}

	if(gObjUser.lpViewPlayer->PetSlot!= -1)
	{
		gInterface.PetX = 61.0f;
	}
	else
	{
		gInterface.PetX = 0;
	}
	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		gInterface.DrawInterfaceDragonLS3();
		gInterface.DrawInterfaceDragonRS3();
	}
	#if(VONGQUAY_NEW)
	gLuckySpin.Draw();
	#endif
	#if(TAS_STYLE == 1)
	mTAS.HienThiKhuonNhanVat();
	#endif

#if(CTCMINI)
	gCtcMini.DrawCTCMiNiMap();	
	gCtcMini.DrawCTCMiniWindow();	
#endif
	gRenderMap.DrawMiniMap();
	gRanking.Draw();
	gCETime.DrawEventTimePanelWindow();
	gInterface.DrawMenu();
	gInterface.DrawMenuOpen();
	gCustomCommandInfo.DrawCommandWindow();
	gInterface.DrawConfirmOpen();
	gCustomJewelBank.DrawJewelBankWindow();

	#if(CUSTOM_GUILD_UPGRADE)
	GuildUpgrade.Draw();
	#endif

	#if(TAS_STYLE == 0)
	gInterface.WindowsKG();
	#endif

#if SO_LUONG_BOSS
	gInterface.DrawBtnTTBOSS();
	gActiveInvasions.render();  // Đúng nếu gActiveInvasions là đối tượng
#endif
	 


	#if(PARTYSEARCH==1)
	gPartySearch.DrawPartySearchWindow();
	gPartySearch.DrawPartySettingsWindow();
	#endif

	#if(TAS_HONHOAN)
	gHonHoan.DrawWindowNangCapHonHoan();
	#endif
	#if TAS_DANHHIEU
	gDanhHieu.DrawWindowNangCapDanhHieu();
	#endif
	#if TAS_QUANHAM
	gQuanHam.DrawWindowNangCapQuanHam();
	#endif
	#if TAS_TUCHAN
	gTuLuyen.DrawWindowNangCapTuLuyen();
	#endif
	#if TAS_NEWVIP
	gNewVip.DrawWindowNangCapNewVip();
	#endif

	if(gProtect.m_MainInfo.CustomInterfaceType == 4)
	{
		gInterface.DrawInterfaceCustom();
	}
	else
	{
		pDrawInterface();
	}

	if  (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		gInterface.DrawInterfaceS2Menu();
	}
	if( GetForegroundWindow() == pGameWindow )
	{	
		if (GetKeyState('H') & 0x4000) 
		{
			if (gInterface.Data[eChangePass_Main].OnShow)
			{
				return;
			}
			else
			{
				gCETime.OpenWindow();
			}
		}
		if (GetKeyState('O') & 0x4000) 
		{
			if (gInterface.Data[eChangePass_Main].OnShow)
			{
				return;
			}
			else
			{
				gInterface.OpenConfig(0);
			}
		}

		if (GetKeyState('J') & 0x4000)
		{
			if (gInterface.Data[eChangePass_Main].OnShow)
			{
				return;
			}
			else
			{		
				gCustomJewelBank.OpenWindow();
			}
		}

		if (GetKeyState(VK_UP) & 0x4000) 
		{
			gInterface.OpenConfig(1);
		}
		else if (GetKeyState(VK_DOWN) & 0x4000) 
		{
			gInterface.OpenConfig(1);
		}
		
		if (GetKeyState(VK_F6) & 0x4000) 
		{
			gInterface.SwitchChatExpand();
		}

		if (GetKeyState(VK_F5) & 0x4000)
		{
			gInterface.SwitchHideDanhHieu();
		}
		if (GetKeyState(VK_F7) & 0x4000) 
		{
			//gInterface.SwitchAntiLag2();
			gInterface.SwitchAntiLag1();
		}
		
		if (GetKeyState(VK_F8) & 0x4000) 
		{
			if((GetTickCount()-gInterface.Data[eMenu_MAIN].EventTick) > 300)
			{
				if (gInterface.CheckMenuWindow())
				{
					gInterface.Data[eMenu_MAIN].EventTick = GetTickCount();
					gInterface.CloseMenuWindow();
				}
				else
				{
					gInterface.Data[eMenu_MAIN].EventTick = GetTickCount();
					gInterface.CloseMenuWindow();
					gInterface.CloseEventTimeWindow(); //event time
					gInterface.Data[ePARTYSEARCH_MAIN].OnShow == false;//setting searchparty
					gInterface.Data[ePARTYSETTINGS_MAIN].OnShow == false;//searchpeary
					gInterface.Data[eJewelBank_MAIN].OnShow == false;//searchpeary
					gInterface.Data[eWindowInfo].OnShow == false;
					gInterface.Data[TAS_Ranking_Main].OnShow == false;//searchpeary
					gInterface.OpenMenuWindow();
				
				}
			}
		}
		
		if (GetKeyState(VK_END) <0 ) 
		{
			{		
				gObjUser.ToggleAuto();
			}

		}

		if (GetKeyState(VK_INSERT) <0 ) 
		{
			{		
				gObjUser.ToggleAutoTron();
			}

		}
		//if (GetKeyState(VK_F10) & 0x4000) 
		//{
		//	gInterface.SwitchCamera();
		//}
		//if (GetKeyState(VK_F11) & 0x4000) 
		//{
		//	gInterface.CameraInit();
		//}
		//
		if (GetKeyState(VK_ESCAPE) < 0) 
		{
			#if (CUSTOM_HARMONY)
			if (gInterface.Data[eWindowHarmony].OnShow == true)
			{
				gInterface.Data[eWindowHarmony].OnShow = false;

				pCloseWindow(pWindowThis(), Inventory);
			}
			#endif
			#if CUSTOM_DUNGLUYENITEM
			if (gInterface.Data[eWindowDungLuyenItem].OnShow == true)
			{
				gInterface.Data[eWindowDungLuyenItem].Close();
				pCloseWindow(pWindowThis(), Inventory);
			}
			#endif
			if (gInterface.Data[ePARTYSEARCH_MAIN].OnShow == true)
			{
				gInterface.Data[ePARTYSEARCH_MAIN].OnShow = false;
				
				if(gProtect.m_MainInfo.CustomInterfaceType != 4)
				{
					pSetCursorFocus = false;
				}
			}
			#if CongHuongV2
			if(gInterface.Data[eWindow_CongHuong].OnShow == true)
			{
				gInterface.Data[eWindow_CongHuong].Close();
				pCloseWindow(pWindowThis(), Inventory);
				
			}
			#endif
			if (gInterface.Data[ePARTYSETTINGS_MAIN].OnShow == true)
			{
					gInterface.Data[ePARTYSETTINGS_MAIN].OnShow == false;
				
				if(gProtect.m_MainInfo.CustomInterfaceType != 4)
				{
					pSetCursorFocus = false;
				}
			}

			if (gInterface.Data[eCommand_MAIN].OnShow == true)
			{
				gInterface.Data[eCommand_MAIN].OnShow = false;
				
				if(gProtect.m_MainInfo.CustomInterfaceType != 4)
				{
					pSetCursorFocus = false;
				}
			}

			if (gInterface.CheckMenuWindow())
			{
				gInterface.CloseMenuWindow();
			}
			if (gInterface.Data[eEventTimePANEL_MAIN].OnShow == true)
			{
				gInterface.Data[eEventTimePANEL_MAIN].OnShow = false;
				
				if(gProtect.m_MainInfo.CustomInterfaceType != 4)
				{
					pSetCursorFocus = false;
				}
			}
		}
	}
}

void Interface::SwitchMiniMap()
{
	if((GetTickCount() - gInterface.Data[eNULL_MAP].EventTick) < 1000 ||this->CheckWindow(ChatWindow))
	{
		return;
	}

	gInterface.Data[eNULL_MAP].EventTick = GetTickCount();

	if (MiniMap != 0)
	{
		gInterface.DrawMessage(1, gConfig.TTAS_TEXT_ENGINE[0]);
		MiniMap = 0;
		WritePrivateProfileStringA("Graphics","MiniMap","0","./Settings.ini");
	}
	else 
	{
		gInterface.DrawMessage(1, gConfig.TTAS_TEXT_ENGINE[1]);
		MiniMap = 1;
		WritePrivateProfileStringA("Graphics","MiniMap","1","./Settings.ini");
	}
}

DWORD	SetInvisibleEffect_PointerYYYYY;
DWORD	SetInvisibleEffect_BuffYYYYY;
DWORD	SetInvisibleEffect_PointerYYYY;
DWORD	SetInvisibleEffect_BuffYYYY;

__declspec(naked) void ItemInvisible11(){
	static DWORD m_aaaaab = 0x0060B37A;
	_asm{
		mov SetInvisibleEffect_BuffYYYYY, esi
			mov ecx, dword ptr ss : [ebp + 8]
			mov esi, dword ptr ds : [ecx + 0x30]
			mov SetInvisibleEffect_PointerYYYYY, esi
			mov esi, SetInvisibleEffect_BuffYYYYY
	}
	if (SetInvisibleEffect_PointerYYYYY != 0x1EA5
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(12, 15)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(12, 30)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(12, 31)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(12, 136)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(12, 137)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(12, 138)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(12, 139)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(12, 140)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(12, 141)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(12, 142)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(12, 143)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(14, 13)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(14, 14)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(14, 16)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(14, 31)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(14, 42)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(14, 13)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(14, 41)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(14, 43)
		|| SetInvisibleEffect_PointerYYYYY != ITEM2(14, 44))
	{
		_asm{
			jmp[m_aaaaab]
		}
	}
}
__declspec(naked) void ItemInvisible22(){
	static DWORD m_aaaaaa = 0x0060B41D;
	_asm{
		mov SetInvisibleEffect_BuffYYYY, esi
			mov ecx, dword ptr ss : [ebp + 8]
			mov esi, dword ptr ds : [ecx + 0x30]
			jmp[m_aaaaaa]
	}
}
DWORD	SetInvisibleEffect_PointerXXX;
DWORD	SetInvisibleEffect_BuffXXX;

Naked(InvisibleEffectXX){
	_asm{
		mov SetInvisibleEffect_BuffXXX, esi
			mov ecx, dword ptr ss : [ebp + 8]
			mov esi, dword ptr ds : [ecx + 0x30]
			mov SetInvisibleEffect_PointerXXX, esi
			mov esi, SetInvisibleEffect_BuffXXX
	}
	if (SetInvisibleEffect_PointerXXX == 0x1EA5 || SetInvisibleEffect_PointerXXX == ITEM2(13, 18)){
		_asm{
			mov SetInvisibleEffect_BuffXXX, 0x0060B37A
				jmp SetInvisibleEffect_BuffXXX
		}
	}
	else{
		_asm{
			mov SetInvisibleEffect_BuffXXX, 0x0060B41D
				jmp SetInvisibleEffect_BuffXXX
		}
	}
}

void InvisibleItem11(){
	SetCompleteHook(0xE9, 0x0060B36A, &ItemInvisible11);
}
void InvisibleItem22(){
	SetCompleteHook(0xE9, 0x0060B36A, &ItemInvisible22);
}
void InvisibleItemXX(){
	SetRange((LPVOID)0x0060B36A, 10, ASM::NOP); //12
	SetCompleteHook(0xE9, 0x0060B36A, &InvisibleEffectXX);
}


void Interface::SwitchAntiLag1()
{
	if ((GetTickCount() - gInterface.Data[ePLAYER_POINT].EventTick) < 1000 || this->CheckWindow(ChatWindow))
	{
		return;
	}

	gInterface.Data[ePLAYER_POINT].EventTick = GetTickCount();

	if (GetForegroundWindow() == pGameWindow && !gInterface.CheckWindow(ObjWindow::ChatWindow))
	{
		if (AntiLag1 != 0)
		{
			gInterface.DrawMessage(1, gConfig.TTAS_TEXT_ENGINE[2]);
			AntiLag1 = 0;
			SetByte(0x0074CD30, 0x55); //Enable Dynamic Effects
			SetByte(0x00771310, 0x55); //Enable Static Effects
			SetByte(0x00608200, 0x55); //Enable Glow Effects
			SetByte(0x00608FB0, 0x55); //Enable Skills Effects
			SetByte(0x005EDFE0, 0x55); //Enable Objects
			SetByte(0x0054A270, 0x55); //Shadows

		}
		else
		{
			gInterface.DrawMessage(1, gConfig.TTAS_TEXT_ENGINE[3]);
			AntiLag1 = 1;
			SetByte(0x0074CD30, 0xC3); //Disable Dynamic Effects
			SetByte(0x00771310, 0xC3); //Disable Static Effects
			SetByte(0x00608200, 0xC3); //Disable Glow Effects
			SetByte(0x00608FB0, 0xC3); //Disable Skills Effects
			SetByte(0x0054A270, 0xC3); //Disable Shadows
			
		}
	}
}




void Interface::SwitchAntiLag2()
{
	if (pPlayerState < GameProcess)
	{
		return;
	}
	if (gInterface.CheckWindow(ObjWindow::CashShop)
		|| gInterface.CheckWindow(ObjWindow::FriendList)
		|| gInterface.CheckWindow(ObjWindow::MoveList)
		|| gInterface.CheckWindow(ObjWindow::Party)
		|| gInterface.CheckWindow(ObjWindow::Quest)
		|| gInterface.CheckWindow(ObjWindow::NPC_Devin)
		|| gInterface.CheckWindow(ObjWindow::Guild)
		|| gInterface.CheckWindow(ObjWindow::Trade)
		|| gInterface.CheckWindow(ObjWindow::Warehouse)
		|| gInterface.CheckWindow(ObjWindow::ChaosBox)
		|| gInterface.CheckWindow(ObjWindow::CommandWindow)
		|| gInterface.CheckWindow(ObjWindow::PetInfo)
		|| gInterface.CheckWindow(ObjWindow::Shop)
		|| gInterface.CheckWindow(ObjWindow::Inventory)
		|| gInterface.CheckWindow(ObjWindow::Store)
		|| gInterface.CheckWindow(ObjWindow::OtherStore)
		|| gInterface.CheckWindow(ObjWindow::Character)
		|| gInterface.CheckWindow(ObjWindow::DevilSquare)
		|| gInterface.CheckWindow(ObjWindow::BloodCastle)
		|| gInterface.CheckWindow(ObjWindow::CreateGuild)
		|| gInterface.CheckWindow(ObjWindow::GuardNPC)
		|| gInterface.CheckWindow(ObjWindow::SeniorNPC)
		|| gInterface.CheckWindow(ObjWindow::GuardNPC2)
		|| gInterface.CheckWindow(ObjWindow::CastleGateSwitch)
		|| gInterface.CheckWindow(ObjWindow::CatapultNPC)
		|| gInterface.CheckWindow(ObjWindow::CrywolfGate)
		|| gInterface.CheckWindow(ObjWindow::IllusionTemple)
		|| gInterface.CheckWindow(ObjWindow::HeroList)
		|| gInterface.CheckWindow(ObjWindow::ChatWindow)
		|| gInterface.CheckWindow(ObjWindow::FastMenu)
		|| gInterface.CheckWindow(ObjWindow::Options)
		|| gInterface.CheckWindow(ObjWindow::Help)
		|| gInterface.CheckWindow(ObjWindow::FastDial)
		|| gInterface.CheckWindow(ObjWindow::SkillTree)
		|| gInterface.CheckWindow(ObjWindow::GoldenArcher1)
		|| gInterface.CheckWindow(ObjWindow::GoldenArcher2)
		|| gInterface.CheckWindow(ObjWindow::LuckyCoin1)
		|| gInterface.CheckWindow(ObjWindow::LuckyCoin2)
		|| gInterface.CheckWindow(ObjWindow::NPC_Duel)
		|| gInterface.CheckWindow(ObjWindow::NPC_Titus)
		|| gInterface.CheckWindow(ObjWindow::CashShop)
		|| gInterface.CheckWindow(ObjWindow::Lugard)
		|| gInterface.CheckWindow(ObjWindow::QuestList1)
		|| gInterface.CheckWindow(ObjWindow::QuestList2)
		|| gInterface.CheckWindow(ObjWindow::Jerint)
		|| gInterface.CheckWindow(ObjWindow::FullMap)
		|| gInterface.CheckWindow(ObjWindow::NPC_Dialog)
		|| gInterface.CheckWindow(ObjWindow::GensInfo)
		|| gInterface.CheckWindow(ObjWindow::NPC_Julia)
		|| gInterface.CheckWindow(ObjWindow::NPC_ChaosMix)
		|| gInterface.CheckWindow(ObjWindow::ExpandInventory)
		|| gInterface.CheckWindow(ObjWindow::ExpandWarehouse)
		|| gInterface.CheckWindow(ObjWindow::MuHelper))
	{
		return;
	}
	if ((GetTickCount() - gInterface.Data[ePLAYER_POINT].EventTick) < 1000 || this->CheckWindow(ChatWindow))
	{
		return;
	}

	gInterface.Data[ePLAYER_POINT].EventTick = GetTickCount();

	if (GetForegroundWindow() == pGameWindow && !gInterface.CheckWindow(ObjWindow::ChatWindow))
	{
		if (AntiLag2 != 0)
		{
			gInterface.DrawMessage(1, gConfig.TTAS_TEXT_ENGINE[4]);

			AntiLag2 = 0;
			InvisibleItem22();
			InvisibleItemXX();

			SetByte((0x0074CD80 + 2), (this->AntiLag2 == 0) ? 1 : 0); // DisableDynamicEffect
			SetByte((0x00771359 + 3), (this->AntiLag2 == 0) ? 1 : 0); // DisableStaticEffect
			DisableGlowEffect == this->AntiLag2 == 1;
			DisableShadow = this->AntiLag2 == 1;
			SetCompleteHook(0xE8, 0x00588661, 0x005655C0); // Dis Wings
			SetCompleteHook(0xE8, 0x00576DDB, 0x005655C0); //Enable Weapons
			SetCompleteHook(0xE8, 0x005883F4, 0x005655C0); //Enable Weapons
			SetByte(0x0051EE20, 0x55); //Enable Cloaks
		}
		else
		{
			gInterface.DrawMessage(1, gConfig.TTAS_TEXT_ENGINE[5]);
			InvisibleItem11();

			SetByte((0x0074CD80 + 2), (this->AntiLag2 == 1) ? 1 : 0); // DisableDynamicEffect
			SetByte((0x00771359 + 3), (this->AntiLag2 == 1) ? 1 : 0); // DisableStaticEffect

			DisableGlowEffect == this->AntiLag2 == 0;
			DisableShadow = this->AntiLag2 == 0;

			MemorySet(0x00588661, 0x90, 0x05); // On Wing
			MemorySet(0x00576DDB, 0x90, 0x05); //Disable Weapons
			MemorySet(0x005883F4, 0x90, 0x05); //Disable Weapons
			SetByte(0x0051EE20, 0xC3); //Disable Cloaks

			AntiLag2 = 1;
		}
	}
}
void Interface::SwitchHideDanhHieu()
{
	if ((GetTickCount() - gInterface.Data[ePLAYER_POINT].EventTick) < 1000 || this->CheckWindow(ChatWindow))
	{
		return;
	}

	gInterface.Data[ePLAYER_POINT].EventTick = GetTickCount();

	if (MinimizarOfRank == 0)
	{
		MinimizarOfRank = 1;
	}
	else
	{
		MinimizarOfRank = 0;
	}
}

int Interface::DrawFormat(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);
	
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	
	int LineCount = 0;
	
	char * Line = strtok(Buff, "\n");
	
	while( Line != NULL )
	{
		pDrawColorText(Line, PosX, PosY, Width, 0, Color, 0, Align);
		PosY += 10;
		Line = strtok(NULL, "\n");
	}
	
	return PosY;
}
int Interface::TASText(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...)
{
    char Buff[2048];
    int BuffLen = sizeof(Buff) - 1;
    ZeroMemory(Buff, BuffLen);

    va_list args;
    va_start(args, Text);
    int Len = vsprintf_s(Buff, BuffLen, Text, args);
    va_end(args);

    int LineCount = 0;

    char* Line = strtok(Buff, "\n");

    while (Line != NULL)
    {
        std::string str = Line;
        std::stringstream ss(str);
        std::string token;
        std::vector<std::string> tokens;
        while (getline(ss, token, ' ')) {
            tokens.push_back(token);
        }
        std::string num_str = tokens.back();
        int num = atoi(num_str.c_str());
        tokens.pop_back();
        std::string new_str = "";
        if (num < 1000) {
            new_str = num_str;
        }
        else {
            int num_digit = num_str.size();
            int num_commas = (num_digit - 1) / 3;
            int start = 0;
            for (int i = 0; i < num_commas; i++) {
                int end = num_digit - 3 * (i + 1);
                new_str = "," + num_str.substr(end, 3) + new_str;
                start = end;
            }
            new_str = num_str.substr(0, start) + new_str;
        }
        tokens.push_back(new_str);
        std::string new_line = "";
        for (int i = 0; i < tokens.size(); i++) {
            if (i != 0) new_line += " ";
            new_line += tokens[i];
        }
        pDrawColorText(new_line.c_str(), PosX, PosY, Width, 0, Color, 0, Align);
		PosY += 10;
        Line = strtok(NULL, "\n");
    }

    return PosY;
}
bool Interface::CheckWindow(int WindowID)
{
	return pCheckWindow(pWindowThis(), WindowID);
}
int Interface::CloseWindow(int WindowID)
{
	return pCloseWindow(pWindowThis(), WindowID);
}
int Interface::OpenWindow(int WindowID)
{
	return pOpenWindow(pWindowThis(), WindowID);
}

bool Interface::IsWorkZone2(float X, float Y, float MaxX, float MaxY)
{
	if ((gObjUser.m_CursorX < X || gObjUser.m_CursorX > MaxX)
		|| (gObjUser.m_CursorY < Y || gObjUser.m_CursorY > MaxY))
	{
		return false;
	}
	// ----
	return true;
}

bool Interface::IsWorkZone(short ObjectID)
{
	if( (pCursorX < this->Data[ObjectID].X || pCursorX > this->Data[ObjectID].MaxX) 
		|| (pCursorY < this->Data[ObjectID].Y || pCursorY > this->Data[ObjectID].MaxY) )
		return false;

	return true;
}

bool Interface::IsWorkZone(float X, float Y, float MaxX, float MaxY)
{
	if ((gObjUser.m_CursorX < X || gObjUser.m_CursorX > MaxX)
		|| (gObjUser.m_CursorY < Y || gObjUser.m_CursorY > MaxY))
	{
		return false;
	}
	// ----
	return true;
}
int Interface::DrawToolTip(int X, int Y, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	
	return pDrawToolTip(X, Y, Buff);
}

int Interface::DrawMessage(int Mode, LPCSTR Text, ...)
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	char Buff[2048];
	int BuffLen	= sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----
	return pDrawMessage(Buff, Mode);
}
float Interface::DrawRepeatGUI(short MonsterID, float X, float Y, int Count)
{
	float StartY = Y;
	// ----
	for (int i = 0; i < Count; i++)
	{
		pDrawGUI(this->Data[MonsterID].ModelID, X, StartY,
			this->Data[MonsterID].Width, this->Data[MonsterID].Height);
		// ----
		StartY += this->Data[MonsterID].Height;
	}
	// ----
	return StartY;
}

float Interface::DrawRepeatGUIScale(short MonsterID, float X, float Y, float ScaleX, float ScaleY, int Count)
{
	float StartY = Y;
	// ----
	for (int i = 0; i < Count; i++)
	{
		this->DrawIMG(this->Data[MonsterID].ModelID, X, StartY, ScaleX, ScaleY);
		// ----
		StartY += this->Data[MonsterID].Height;
	}
	// ----
	return StartY;
}

void Interface::DrawButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}
	// ----
	pDrawButton(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY);
}

void Interface::DrawButtonRender(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	this->Data[ObjectID].X = PosX;
	this->Data[ObjectID].Y = PosY;
	this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	// ----
	pDrawButton(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY);
}

void Interface::DrawColoredGUI(short ObjectID, float X, float Y, DWORD Color)
{
	if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X		= X;
		this->Data[ObjectID].Y		= Y;
		this->Data[ObjectID].MaxX	= X + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY	= Y + this->Data[ObjectID].Height;
	}
	// ----
	pDrawColorButton(this->Data[ObjectID].ModelID, X, Y, 
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, Color);
}

void Interface::DrawMenu()
{
	if (gProtect.m_MainInfo.CustomMenuSwitch != 1)
	{
		return;
	}

	if (this->Data[eMenu].OnShow)
	{
		this->Data[eMenu].OnShow = false;
	}

	if (this->CheckWindow(ObjWindow::MoveList) || this->CheckWindow(ObjWindow::CashShop) || this->CheckWindow(ObjWindow::SkillTree) || this->CheckWindow(ObjWindow::FullMap)
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(ExpandInventory) 
		&& this->CheckWindow(Store))
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(ExpandInventory) 
		&& this->CheckWindow(Character))
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(Warehouse) 
		&& this->CheckWindow(ExpandWarehouse)) )
	{
		CloseMenuWindow();
		return;
	}
	
	this->Data[eMenu].OnShow = true;
}

bool Interface::EventDrawMenu_Open(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenu].EventTick);
	if (!this->Data[eMenu].OnShow || !IsWorkZone(eMenu))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		
	if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
		this->Data[eMenu].OnClick = true;
		return true;
	}
	this->Data[eMenu].OnClick = false;
	if (Delay < 500)
	{
		return false;
	}
	this->Data[eMenu].EventTick = GetTickCount();
	if (CheckMenuWindow())
	{
		CloseMenuWindow();
	}
	else
	{
		CloseCustomWindow();
		OpenMenuWindow();
	}
	return false;
}

void Interface::DrawMenuOpen()
{
	if (gInterface.CheckWindow(Character)
	|| gInterface.CheckWindow(Warehouse)
	|| gInterface.CheckWindow(ChaosBox)
	|| gInterface.CheckWindow(Store)
	|| gInterface.CheckWindow(OtherStore)
	|| gInterface.CheckWindow(ExpandInventory)
	|| gInterface.CheckWindow(Shop)
	|| gInterface.CheckWindow(Trade)
	|| gInterface.CheckWindow(LuckyCoin1)
	|| gInterface.CheckWindow(NPC_ChaosMix))
	{
		return;
	}
	//--
	if (gProtect.m_MainInfo.CustomMenuSwitch != 1 || !this->Data[eMenu_MAIN].OnShow || pCheckWindow(pWindowThis(), 35))
	{
		return;
	}
	pSetCursorFocus = true;
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;
	float MainWidth = 230.0;
	float StartY = 25;
	float StartX = JCResto+(MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (29.0 / 2);

	this->DrawAnimatedGUI(eMenu_MAIN, StartX, StartY + 2);
	this->DrawAnimatedGUI(eMenu_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(eMenu_FRAME, StartX, StartY + 67.0, 18);
	this->DrawAnimatedGUI(eMenu_FOOTER, StartX, StartY);
	this->DrawAnimatedGUI(eMenu_CLOSE, StartX + MainWidth - this->Data[eMenu_CLOSE].Width, this->Data[eMenu_MAIN].Y - 2);

	if (this->IsWorkZone(eMenu_CLOSE))
	{
		DWORD Color = eGray100;
		if (this->Data[eMenu_CLOSE].OnClick)
		{
			Color = eGray150;
		}
		this->DrawColoredGUI(eMenu_CLOSE, this->Data[eMenu_CLOSE].X, this->Data[eMenu_CLOSE].Y, Color);
		this->DrawToolTip(this->Data[eMenu_CLOSE].X + 5, this->Data[eMenu_CLOSE].Y + 25, gConfig.TTAS_TEXT_ENGINE[26]);
	}

	this->DrawFormat(eGold, StartX + 10, this->Data[eMenu_MAIN].Y + 8, 210, 3, gConfig.TTAS_TEXT_ENGINE[39]);
	this->DrawFormat(eBlue, StartX + 10, this->Data[eMenu_MAIN].Y + 30, 210, 3, gConfig.TTAS_TEXT_ENGINE[106], gObjUser.lpPlayer->Name);
	this->DrawAnimatedGUI(eMenu_DIV, StartX, this->Data[eMenu_MAIN].Y + 33);
	float CurrentMove;
	int BtCount = -1;
	int BtStart = StartY + 48;

	int ObjectIDs[ButtonMenuTAS];
	for (int i = 0; i < ButtonMenuTAS; ++i) 
	{
		ObjectIDs[i] = eMenu_OPT1 + i;
	}
	for(int n = 0; n < ButtonMenuTAS; n++)
	{
		if(gProtect.m_MainInfo.MenuButtons[n] == 1)
		{
			BtCount++;
		}
		else
		{
			continue;
		}

		CurrentMove = 0.0;
		if (IsWorkZone(ObjectIDs[n]))
		{
			if (this->Data[ObjectIDs[n]].OnClick)
			{
				if( gProtect.m_MainInfo.CustomInterfaceType == 3 || gProtect.m_MainInfo.CustomInterfaceType == 4 )
				{	
					PlayBuffer(25, 0, 0);
					CurrentMove = 29;
				}
			}
		}
		
		int SoButton = ButtonMenuTAS;
		float CurY = 310.0f;
		COLORREF gColorString = RGB(255, 255, 255);
		HFONT MenuSample;
		if (BtCount %2 == 0)
		{
			this->DrawButton(ObjectIDs[n], StartX	+ 6,	BtStart + (27 * (BtCount/2))		- CurY, 0, CurrentMove);
			gToolKit.CreateFontNew(StartX + 6, BtStart + (27 * (BtCount / 2)) + 9 - CurY, 108, 3,13,700, gConfig.MenuGame_TextVN[((n == SoButton) ? 40 : 1 + n)], gColorString,MenuSample);
		}
		else
		{
			this->DrawButton(ObjectIDs[n], StartX + (MainWidth) - (108 )	- 9,	BtStart + (27 * (BtCount/2))		- CurY, 0, CurrentMove);
			gToolKit.CreateFontNew(StartX + (MainWidth)-(108) - 9, BtStart + (27 * (BtCount / 2)) + 9 - CurY, 108, 3, 13, 700, gConfig.MenuGame_TextVN[((n == SoButton) ? 40 : 1 + n)], gColorString, MenuSample);
		}
	}
}

bool Interface::TASEventClick(DWORD Event)
{
	if (gInterface.Data[eMenu_MAIN].OnShow == false)
	{
		return false;
	}
	else
	{
		DWORD CurrentTick = GetTickCount();
		for (int i = 0; i < ButtonMenuTAS; i++)
		{
			DWORD Delay = (CurrentTick - this->Data[eMenu_OPT1 + i].EventTick);	
			if(gInterface.IsWorkZone(eMenu_OPT1 + i))
			{
				if(Event == WM_LBUTTONDOWN)
				{
					this->Data[eMenu_OPT1 + i].OnClick = true; return true;
				}
				this->Data[eMenu_OPT1 + i].OnClick = false;
				if(Delay < 500)
				{
					return false;
				}
				switch(eMenu_OPT1 + i)
				{
					case eMenu_OPT1: gCETime.OpenWindow();					break;
					case eMenu_OPT2: gNewVip.SendMenuButton();					break;
					case eMenu_OPT3: gRanking.SendMenuButton();						break;
					case eMenu_OPT4: gCustomCommandInfo.OpenCommandWindow()	;		break;
					case eMenu_OPT5: gCustomJewelBank.OpenWindow();					break;
					case eMenu_OPT6: gTuLuyen.SendMenuButton();						break;
					case eMenu_OPT7: gPartySearch.SwitchPartySettingsWindowState();	break;
					case eMenu_OPT8: gPartySearch.SendMenuButton();					break;
					case eMenu_OPT9: gQuanHam.SendMenuButton();						break;
					case eMenu_OPT10: gDanhHieu.SendMenuButton();					break;
					case eMenu_OPT11: ThueFlag.OpenFlag();							break;
					case eMenu_OPT12: G_TASRelife.SendMenuButton();					break;
					case eMenu_OPT13: gLuckySpin.SwitchLuckySpinWindowState();		break;
					case eMenu_OPT14: gNewMocNap.OpenWindowMocNap();				break;
					case eMenu_OPT15: gNewCashShop.OpenCustomShop();				break;
					case eMenu_OPT16: gNewIntros.OpenWindowMocNap();				break;
					case eMenu_OPT17: gTaiKhoan.OpenWindowsChangePass();			break;
					case eMenu_OPT18: break;
					case eMenu_OPT19: gResetChange.OpenResetChange();				break; 	
					case eMenu_OPT20: gHonHoan.SendMenuButton();					break; 					
					default:
					break;
				}
				this->CloseMenuWindow();			
				gInterface.Data[eMenu_OPT1 + i].EventTick = GetTickCount();
			}
		}
		return false;
	}	
}

bool Interface::MiniMapCheck()
{
	bool visual = false;

	if ( gInterface.CheckWindow(13) && gInterface.CheckWindow(Character)
    || gInterface.CheckWindow(8)
    || gInterface.CheckWindow(12)
    || gInterface.CheckWindow(9)
    || gInterface.CheckWindow(7)
    || gInterface.CheckWindow(14)
    || gInterface.CheckWindow(15)
    || gInterface.CheckWindow(60)
    || gInterface.CheckWindow(76) )
	{
		visual = true;
	}
	else
	{
		if ( gInterface.CheckWindow(16) && (gInterface.CheckWindow(4)||gInterface.CheckWindow(69)) )
		{
			visual = true;
		}
		else
		{
			if ( gInterface.CheckWindow(16) && gInterface.CheckWindow(11) )
			{
				visual = true;
			}
			else
			{
				if ( gInterface.CheckWindow(27) )
				{
					visual = true;
				}
				else
				{
					if ( gInterface.CheckWindow(13)
					|| gInterface.CheckWindow(16)
					|| gInterface.CheckWindow(3)
					|| gInterface.CheckWindow(21)
					|| gInterface.CheckWindow(6)
					|| gInterface.CheckWindow(22)
					|| gInterface.CheckWindow(23)
					|| gInterface.CheckWindow(24)
					|| gInterface.CheckWindow(4)
					|| gInterface.CheckWindow(18)
					|| gInterface.CheckWindow(10)
					|| gInterface.CheckWindow(5)
					|| gInterface.CheckWindow(25)
					|| gInterface.CheckWindow(26)
					|| gInterface.CheckWindow(19)
					|| gInterface.CheckWindow(20)
					|| gInterface.CheckWindow(58)
					|| gInterface.CheckWindow(59)
					|| gInterface.CheckWindow(62)
					|| gInterface.CheckWindow(73)
					|| gInterface.CheckWindow(68)
					|| gInterface.CheckWindow(69)
					|| gInterface.CheckWindow(70)
					|| gInterface.CheckWindow(66)
					|| gInterface.CheckWindow(75)
					|| gInterface.CheckWindow(74) )
					{
						visual = true;
					}
					else
					{
						if ( gInterface.CheckWindow(79) )
						{
							if ( gInterface.CheckWindow(80) )
							{
								visual = true;
							}
							else
							{
								visual = true;
							}	
						}
					}
				}
			}
		}
	}
  
	if ( gInterface.CheckWindow(77) )
	{
		if ( gInterface.CheckWindow(Warehouse) ||
			gInterface.CheckWindow(ChaosBox) ||
			gInterface.CheckWindow(Store) ||
			gInterface.CheckWindow(OtherStore) ||
			gInterface.CheckWindow(Character))
		{
			visual = true;
		}
		else
		{
			visual = true;
		}
	}
	else if ( gInterface.CheckWindow(78) )
	{
			visual = true;
	}
	return visual;
}

bool Interface::CheckMap()
{
	switch(gObjUser.m_MapNumber)
	{
		case eMapNumber::Lorencia:	return false;	break;
		case eMapNumber::Dungeon:	return false;	break;
		case eMapNumber::Devias:	return false;	break;
		case eMapNumber::Noria:		return false;	break;
		case eMapNumber::LostTower:	return false;	break;
		case eMapNumber::Stadium:	return false;	break;
		case eMapNumber::Atlans:	return false;	break;
		case eMapNumber::Tarkan:	return false;	break;
		case eMapNumber::Elbeland:	return false;	break;
		case eMapNumber::Icarus:	return false;	break;
		case eMapNumber::Trials:	return false;	break;
		case eMapNumber::Aida:		return false;	break;
		case eMapNumber::Crywolf:	return false;	break;
		case eMapNumber::Kanturu1:	return false;	break;
		case eMapNumber::Kanturu3:	return false;	break;
		case eMapNumber::Barracks:	return false;	break;
		case eMapNumber::Calmness:	return false;	break;
		case eMapNumber::Raklion:	return false;	break;
		case eMapNumber::Vulcanus:	return false;	break;
		case eMapNumber::Karutan1:	return false;	break;
		case eMapNumber::Karutan2:	return false;	break;
		default:
		return true;
		break;
	}
}

void Interface::CloseCustomWindow()
{
	this->CloseMenuWindow();
	this->Data[TAS_Ranking_Main].OnShow		= false;
	this->Data[eEventTimePANEL_MAIN].OnShow = false;
	this->Data[eCommand_MAIN].OnShow		= false;

	this->Data[eWindow_NangCapHonHoan].OnShow	= false;
	this->Data[eWindow_NangCapDanhHieu].OnShow	= false;
	this->Data[eWindow_NangCapQuanHam].OnShow	= false;
	this->Data[eWindow_NangCapTuChan].OnShow	= false;
	this->Data[eChangePass_Main].OnShow			= false;

	if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}	
}

void Interface::DrawItem(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse)
{

	if (this->CheckWindow(ObjWindow::MoveList) || this->CheckWindow(ObjWindow::CashShop) || this->CheckWindow(ObjWindow::SkillTree) || this->CheckWindow(ObjWindow::FullMap)
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(ExpandInventory) 
		&& this->CheckWindow(Store)) 
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(Warehouse) 
		&& this->CheckWindow(ExpandWarehouse)) )
	{
		return;
	}

	pSetBlend(true);
	glMatrixMode(0x1701);
	glPushMatrix();
	glLoadIdentity();

	sub_6363D0_Addr(0, 0, *(GLsizei*)MAIN_RESOLUTION_X, *(GLsizei*)MAIN_RESOLUTION_Y);

	float v2 = *(float*)MAIN_RESOLUTION_X / *(float*)MAIN_RESOLUTION_Y;

	if (ItemID == 406)
	{
		sub_6358A0_Addr(0.4, v2, *(float*)0xE61E38, *(float*)0xE61E3C); //tamanho do bmd
	}
	else if (ItemID == 407)
	{
		sub_6358A0_Addr(0.5, v2, *(float*)0xE61E38, *(float*)0xE61E3C); //tamanho do bmd
	}
	else
	{
		sub_6358A0_Addr(0.7, v2, *(float*)0xE61E38, *(float*)0xE61E3C); //tamanho do bmd
	}

	glMatrixMode(0x1700);
	glPushMatrix();
	glLoadIdentity();

	sub_635830_Addr((LPVOID)0x87933A0); 
	sub_635DE0_Addr();
	sub_635E40_Addr();

	glClear(0x100);

	VAngle v45;

	unsigned __int8 v44 = 1; //0 = parado / 1 = girando

	sub_6359B0_Addr(PosX, PosY, (int)&v45, 0); //vi tri bmd
	sub_5CA0D0_Addr(ItemID, Level, Excl, Anc, (int)&v45, v44, 0); //chức năng hiển thị BMD
	
	sub_636720_Addr();

	glMatrixMode(0x1700);
	glPopMatrix();
	glMatrixMode(0x1701);
	glPopMatrix();

	sub_637770_Addr();

	glColor3f(1,1,1);
	pSetBlend(false);
}

void Interface::DrawConfirmOpen()
{
	if(!this->CheckWindow(Shop) && this->Data[eCONFIRM_MAIN].OnShow == true)
	{
		this->Data[eCONFIRM_MAIN].OnShow = false;
	}

	if ((GetTickCount() - this->Data[eCONFIRM_BTN_OK].EventTick) < 100)
	{
		this->Data[eCONFIRM_MAIN].OnShow = false;
	}

	if ((GetTickCount() - this->Data[eCONFIRM_BTN_CANCEL].EventTick) < 100)
	{
		this->Data[eCONFIRM_MAIN].OnShow = false;
	}

	if( !this->Data[eCONFIRM_MAIN].OnShow )
	{
		return;
	}

	float StartX;
	if( gProtect.m_MainInfo.CustomInterfaceType == 3 )
	{
		StartX = 205.0f;
	}
	else
	{
		StartX = 25.0f;
	}

	float MainWidth			= 230.0;
	float MainHeight		= 130.0;
	float StartBody			= 90.0;
	float StartY			= 90.0;
	
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (float)(29.0 / 2);

	gCentral.PrintDropBox(StartX, StartY, MainWidth, MainHeight, 0, 0);

	this->DrawFormat(eGold, (int)StartX + 10, (int)StartBody + 10, 210, 3, gCustomMessage.GetMessage(66));

	this->DrawFormat(eGold, (int)StartX + 10, (int)StartBody + 40, 210, 3, gCustomMessage.GetMessage(67));

	this->DrawButton(eCONFIRM_BTN_OK, (int)StartX+40, (int)StartBody + 70, 0, 0);

	if( this->IsWorkZone(eCONFIRM_BTN_OK) )
	{
		int ScaleY = 30;
		if( this->Data[eCONFIRM_BTN_OK].OnClick )
		{
			ScaleY = 60;
		}
		this->DrawButton(eCONFIRM_BTN_OK, (int)StartX+40, (int)StartBody + 70, 0, ScaleY);
	}

	this->DrawButton(eCONFIRM_BTN_CANCEL, (int)StartX+140, (int)StartBody + 70, 0, 0);

	if( this->IsWorkZone(eCONFIRM_BTN_CANCEL) )
	{
		int ScaleY = 30;
		if( this->Data[eCONFIRM_BTN_CANCEL].OnClick )
		{
			ScaleY = 60;
		}
		this->DrawButton(eCONFIRM_BTN_CANCEL, (int)StartX+140, (int)StartBody + 70, 0, ScaleY);
	}
}

bool Interface::EventConfirm_OK(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eCONFIRM_BTN_OK].EventTick);
	if (!this->Data[eCONFIRM_MAIN].OnShow || !IsWorkZone(eCONFIRM_BTN_OK))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eCONFIRM_BTN_OK].OnClick = true;
		return true;
	}
	this->Data[eCONFIRM_BTN_OK].OnClick = false;;
	if (Delay < 500)
	{
		return false;
	}
	this->Data[eCONFIRM_BTN_OK].EventTick = GetTickCount();
	PMSG_ITEM_BUY_RECV pMsg;
	pMsg.header.set(0xF3, 0xED,sizeof(pMsg));
	pMsg.slot = this->ConfirmSlot;
	DataSend((BYTE*)&pMsg,pMsg.header.size);
	this->Data[eCONFIRM_MAIN].OnShow = false;
	if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
	return false;
}

bool Interface::EventConfirm_CANCEL(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eCONFIRM_BTN_CANCEL].EventTick);
	if (!this->Data[eCONFIRM_MAIN].OnShow || !IsWorkZone(eCONFIRM_BTN_CANCEL))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eCONFIRM_BTN_CANCEL].OnClick = true;
		return true;
	}
	this->Data[eCONFIRM_BTN_CANCEL].OnClick = false;;
	if (Delay < 500)
	{
		return false;
	}
	this->Data[eCONFIRM_BTN_CANCEL].EventTick = GetTickCount();
	this->Data[eCONFIRM_MAIN].OnShow = false;
	if(gProtect.m_MainInfo.CustomInterfaceType != 3 || gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
	return false;
}

void Interface::DrawBarForm(float PosX, float PosY, float Width, float Height, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	pSetBlend(true);
	glColor4f((GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, (float)0.8);
	pDrawBarForm(PosX, PosY, Width, Height, 0.0f, 0);
	pGLSwitchBlend();
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);
}
// ----------------------------------------------------------------------------------------------
bool Interface::CheckWindowEx(int WindowID)
{
	if (WindowID < 0 || WindowID > MAX_WINDOW_EX)
	{
		return 0;
	}
	return this->WindowEx[WindowID];
}


void Interface::SwitchChatExpand()
{

	if((GetTickCount() - gInterface.Data[chatbackground].EventTick) < 1000 ||this->CheckWindow(ChatWindow))
	{
		return;
	}

	gInterface.Data[chatbackground].EventTick = GetTickCount();

	if (SeparateChat != 0)
	{
		gInterface.DrawMessage(1, gConfig.TTAS_TEXT_ENGINE[6]);
		SeparateChat = 0;
		WritePrivateProfileStringA("Setting","SeparateChat","0","./Settings.ini");
	}
	else 
	{
		gInterface.DrawMessage(1, gConfig.TTAS_TEXT_ENGINE[7]);
		SeparateChat = 1;
		WritePrivateProfileStringA("Setting","SeparateChat","1","./Settings.ini");
	}
		gChatExpanded.Switch();
}

void Interface::OpenConfig(int type)
{
	if(type == 0)
	{
		if( (GetTickCount() - gInterface.Data[ePLAYER_POINT].EventTick) < 400 
			|| this->CheckWindow(ChatWindow) 
			|| this->CheckWindow(MuHelper) 
			|| this->CheckWindow(Inventory) 
			|| this->CheckWindow(Store) 
			|| this->CheckWindow(Character) 
			|| this->CheckWindow(CreateGuild) )
		{
			return;
		}

		gInterface.Data[ePLAYER_POINT].EventTick = GetTickCount();

		if (pCheckWindow(pWindowThis(), 35))
		{
			pCloseWindow(pWindowThis(), 35);
		}
		else 
		{
			pOpenWindow(pWindowThis(), 35);
		}
	}
	else if(type == 1 )
	{
		if( (GetTickCount() - gInterface.Data[ePLAYER_POINT].EventTick) < 400 || OpenSwicthSkill == 0)
		{
			return;
		}

		gInterface.Data[ePLAYER_POINT].EventTick = GetTickCount();

		if (SkillPage == 1)
		{
			SkillPage = 2;
		}
		else
		{
			SkillPage = 1;
		}
	}

	PlayBuffer(25, 0, 0);
}
void Interface::SwitchCamera()
{

	if(gProtect.m_MainInfo.DisableHelper == 0)
	{
		if( (GetTickCount() - gInterface.Data[eCamera3DSwitch].EventTick) < 1000 )
		{
			return;
		}

		if( pMapNumber == 62 )
		{
			gInterface.DrawMessage(1, CameraNotAc);
			gCamera.Restore();
		}

		gInterface.Data[eCamera3DSwitch].EventTick = GetTickCount();

		gCamera.Toggle();

		if (gCamera.getEnabled())
		{
			gInterface.DrawMessage(1, "Camera ON");
		}
		else
		{
			gInterface.DrawMessage(1, "Camera OFF");
		}
	}
}

void Interface::CameraInit(){

	if((GetTickCount() - gInterface.Data[eCamera3DInit].EventTick) < 1000 )
	{
		return;
	}

	gInterface.Data[eCamera3DInit].EventTick = GetTickCount();

	if (gCamera.getEnabled())
	{
		gInterface.DrawMessage(1, "Set về mặc định của Camera!");
		gCamera.Restore();
	}
}

bool Interface::Button(DWORD Event, int WinID, int ButtonID, bool Type)
{
	if (!this->IsWorkZone(ButtonID))
	{
		return false;
	}

	if (Type == true)
	{
		if (!this->Data[ButtonID].Attribute)
		{
			return false;
		}
	}
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[ButtonID].EventTick);

	if (Event == WM_LBUTTONDOWN  && this->Data[ButtonID].OnClick == false)
	{
		this->Data[ButtonID].OnClick = true;
	}

	if (Event == WM_LBUTTONUP && this->Data[ButtonID].OnClick == true)
	{
		this->Data[ButtonID].OnClick = false;
		return true;
	}
	if (Delay < 500)
	{
		return false;
	}
	this->Data[ButtonID].OnClick = false;
	this->Data[ButtonID].EventTick = GetTickCount();
	return false;
}

void Interface::EventNewInterface_All(DWORD Event){
	DWORD CurrentTick = GetTickCount();
	if (this->CheckWindow(ChaosBox))
	{
		return;
	}
	
	if (IsWorkZone(eFastMenu))
	{
		DWORD Delay = (CurrentTick - this->Data[eFastMenu].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eFastMenu].OnClick = true;
			return;
		}
		this->Data[eFastMenu].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eFastMenu].EventTick = GetTickCount();
		if (this->CheckWindow(FastMenu)) {
				this->CloseWindow(FastMenu);
		}
		else {
			this->OpenWindow(FastMenu);
		}
	}
	else if (IsWorkZone(eParty))
	{
		DWORD Delay = (CurrentTick - this->Data[eParty].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eParty].OnClick = true;
			return;
		}
		this->Data[eParty].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eParty].EventTick = GetTickCount();
		if (this->CheckWindow(Party)) {
			this->CloseWindow(Party);
		}
		else {
			this->OpenWindow(Party);
		}
	}
	
	else if (IsWorkZone(eCharacter))
	{
		DWORD Delay = (CurrentTick - this->Data[eCharacter].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eCharacter].OnClick = true;
			return;
		}
		this->Data[eCharacter].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eCharacter].EventTick = GetTickCount();
		if (this->CheckWindow(Character)) {
			this->CloseWindow(Character);
		}
		else {
			this->OpenWindow(Character);
		}
	}
	else if (IsWorkZone(eInventory))
	{
		DWORD Delay = (CurrentTick - this->Data[eInventory].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eInventory].OnClick = true;
			return;
		}
		this->Data[eInventory].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eInventory].EventTick = GetTickCount();
		if (this->CheckWindow(Inventory)) {
			this->CloseWindow(Inventory);
		}
		else {
			this->OpenWindow(Inventory);
		}
	}
	else if (IsWorkZone(eFriend))
	{
		DWORD Delay = (CurrentTick - this->Data[eFriend].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eFriend].OnClick = true;
			return;
		}
		this->Data[eFriend].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eFriend].EventTick = GetTickCount();
		if (this->CheckWindow(FriendList)) {
			this->CloseWindow(FriendList);
		}
		else {
			this->OpenWindow(FriendList);
		}
	}
	else if (IsWorkZone(eGuild))
	{
		DWORD Delay = (CurrentTick - this->Data[eGuild].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eGuild].OnClick = true;
			return;
		}
		this->Data[eGuild].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eGuild].EventTick = GetTickCount();
		if (this->CheckWindow(Guild)) {
			this->CloseWindow(Guild);
		}
		else {
			this->OpenWindow(Guild);
		}
	}
}
void Interface::DrawCoord()
{
	gObjUser.Refresh();

	if (*(DWORD*)MAIN_SCREEN_STATE == 5)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		pDrawInterfaceNumBer(22, 461, gObjUser.lpViewPlayer->MapPosX, 1);
		pDrawInterfaceNumBer(46, 461, gObjUser.lpViewPlayer->MapPosY, 1);

	}
}

bool Interface::ButtonEx(DWORD Event, int ButtonID, bool Type)
{
	if (!this->IsWorkZone(ButtonID))
	{
		return false;
	}
	if (Type == true)
	{
		if (!this->Data[ButtonID].Attribute)
		{
			return false;
		}
	}
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[ButtonID].EventTick);
	if (Event == WM_LBUTTONDOWN && this->Data[ButtonID].OnClick == false)
	{
		this->Data[ButtonID].OnClick = true;
	}
	if (Event == WM_LBUTTONUP && this->Data[ButtonID].OnClick == true)
	{
		this->Data[ButtonID].OnClick = false;
		return true;
	}
	if (Delay < 500)
	{
		return false;
	}
	this->Data[ButtonID].OnClick = false;
	this->Data[ButtonID].EventTick = GetTickCount();
	return false;
}

void testfunc()
{
	glMatrixMode(0x1700u);
	glPopMatrix();
	glMatrixMode(0x1701u);
	glPopMatrix();
}

void Interface::DrawItem2(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse)
{

	glMatrixMode(0x1701);
	glPushMatrix();
	glLoadIdentity();
	sub_6363D0_Addr(0, 0, *(GLsizei*)MAIN_RESOLUTION_X, *(GLsizei*)MAIN_RESOLUTION_Y);
	float v2 = *(float*)MAIN_RESOLUTION_X / *(float*)MAIN_RESOLUTION_Y;
	sub_6358A0_Addr(1.0, v2, *(float*)0xE61E38, *(float*)0xE61E3C);
	glMatrixMode(0x1700);
	glPushMatrix();
	glLoadIdentity();
	sub_635830_Addr((LPVOID)0x87933A0);
	sub_635DE0_Addr();
	sub_635E40_Addr();
	pDrawItemModel(PosX, PosY, Width, Height, ItemID, Level, Excl, Anc, OnMouse);
	testfunc();
	glColor3f(1, 1, 1);
	pSetBlend(false);
}

void Interface::LoadImages2(char * Folder, int Code, int Arg3, int Arg4, int Arg5)
{
	pLoadImage(Folder, Code, Arg3, Arg4, Arg5,0);
}
void Interface::DrawWindow(int ObjMain, int ObjTitle, int ObjFrame, int ObjFooter, int Repeat, float X, float Y, char* Text)
{
int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	float StartY = Y;
	float StartX = JCResto+ X;
	gInterface.DrawGUI(ObjMain, StartX, StartY + 2);
	gInterface.DrawGUI(ObjTitle, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(ObjFrame, StartX, StartY + 67.0, Repeat);
	gInterface.DrawGUI(ObjFooter, StartX, StartY);

	gInterface.DrawFormat(eGold, StartX + 10, Y + 10, 210, 3, Text);
}

bool Interface::IsWorkZone1(float x, float y, float x2, float y2)
{
	return pCursorX >= x && pCursorX <= x + x2 && pCursorY >= y && pCursorY <= y + y2;
}
void Interface::DrawInterfaceDragonLS3()
{
	if (this->CheckWindow(ObjWindow::CashShop)
		|| this->CheckWindow(ObjWindow::FullMap)
		|| this->CheckWindow(ObjWindow::SkillTree)
		|| this->CheckWindow(ObjWindow::MoveList)
		)
	{
		return;
	}
	this->DrawGUI(eDragonLeft, this->Data[eDragonLeft].X, this->Data[eDragonLeft].Y);
}

void Interface::DrawInterfaceDragonRS3()
{
	if (this->MiniMapCheck() || (this->CheckWindow(SkillTree) || this->CheckWindow(CashShop) || this->CheckWindow(FullMap)
		|| this->CheckWindow(FastMenu) || this->CheckWindow(FriendList))
		|| pMapNumber == 39 //Kanturu
		|| pMapNumber == 58 //Selupam
		|| pMapNumber == 64 //Duel Arena
		|| pMapNumber == 65 //Doppelganger
		|| pMapNumber == 66 //Doppelganger
		|| pMapNumber == 67 //Doppelganger
		|| pMapNumber == 68 //Doppelganger
		|| pMapNumber == 69 //Imperial Guardian
		|| pMapNumber == 70 //Imperial Guardian
		|| pMapNumber == 71 //Imperial Guardian
		|| pMapNumber == 72 //Imperial Guardian
		|| pMapNumber == 11	//Blood Castle
		|| pMapNumber == 12	//Blood Castle
		|| pMapNumber == 13	//Blood Castle
		|| pMapNumber == 14	//Blood Castle
		|| pMapNumber == 15	//Blood Castle
		|| pMapNumber == 16	//Blood Castle
		|| pMapNumber == 17	//Blood Castle
		|| pMapNumber == 52	//Blood Castle
		|| pMapNumber == 9	//Devil Square
		|| pMapNumber == 32	//Devil Square
		|| pMapNumber == 18	//Chaos Castle
		|| pMapNumber == 19	//Chaos Castle
		|| pMapNumber == 20	//Chaos Castle
		|| pMapNumber == 21	//Chaos Castle
		|| pMapNumber == 22	//Chaos Castle
		|| pMapNumber == 23	//Chaos Castle
		|| pMapNumber == 53	//Chaos Castle
		|| pMapNumber == 45	//Illusion Temple
		|| pMapNumber == 46	//Illusion Temple
		|| pMapNumber == 47	//Illusion Temple
		|| pMapNumber == 48	//Illusion Temple
		|| pMapNumber == 49	//Illusion Temple
		|| pMapNumber == 50	//Illusion Temple
		|| pMapNumber == 18	//Chaos Castle
		|| pMapNumber == 19	//Chaos Castle
		|| pMapNumber == 20	//Chaos Castle
		|| pMapNumber == 21	//Chaos Castle
		|| pMapNumber == 22	//Chaos Castle
		|| pMapNumber == 23	//Chaos Castle
		|| pMapNumber == 53	//Chaos Castle
		|| pMapNumber == 34 //Crywolf
		|| pMapNumber == 30 //Valley/CastleSiege
		|| pMapNumber == 65 /*DuelArena*/)
	{
		return;
	}
	this->DrawGUI(eDragonRight, this->Data[eDragonRight].X, this->Data[eDragonRight].Y);
}

void Interface::DrawInterfaceS2Menu()
{
	if (IsWorkZone(eParty))
	{
		this->DrawToolTip(345, 420, "Party");
	}
	if (this->CheckWindow(Party))
	{
		gInterface.DrawButton(eParty, 348, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eCharacter))
	{
		this->DrawToolTip(375, 420, "Character");
	}
	if (this->CheckWindow(Character))
	{
		gInterface.DrawButton(eCharacter, 378.5f, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eInventory))
	{
		this->DrawToolTip(405, 420, "Inventory");
	}
	if (this->CheckWindow(Inventory))
	{
		gInterface.DrawButton(eInventory, 409, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eShop))
	{
		this->DrawToolTip(430, 420, "CashShop");
	}
	if (this->CheckWindow(CashShop))
	{
		gInterface.DrawButton(eShop, 439.5f, 451, 0.0, 0.0);
	}
	if (IsWorkZone(eFriend))
	{
		this->DrawToolTip(580, 420, "Friends");
	}
	if (this->CheckWindow(FriendList))
	{
		gInterface.DrawButton(eFriend, 581, 433, 0.0, 0.0);
	}
	if (IsWorkZone(eGuild))
	{
		this->DrawToolTip(580, 444, "Guild");
	}
	if (this->CheckWindow(Guild))
	{
		gInterface.DrawButton(eGuild, 581, 457, 0.0, 0.0);
	}
	if (IsWorkZone(eFastMenu))
	{
		this->DrawToolTip(13, 420, "System");
	}
	if (this->CheckWindow(FastMenu))
	{
		gInterface.DrawButton(eFastMenu, 6, 433, 0.0, 0.0);
	}
}
