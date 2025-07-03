#pragma once
#if RELIFE
#include "Import.h"
#include "Interface.h"
#include "Protocol.h"
#define IsWindowsCheck gInterface.CheckWindow(ObjWindow::CashShop)|| gInterface.CheckWindow(ObjWindow::FriendList)|| gInterface.CheckWindow(ObjWindow::MoveList)|| gInterface.CheckWindow(ObjWindow::Party)|| gInterface.CheckWindow(ObjWindow::Quest)|| gInterface.CheckWindow(ObjWindow::NPC_Devin)|| gInterface.CheckWindow(ObjWindow::Guild)|| gInterface.CheckWindow(ObjWindow::Trade)|| gInterface.CheckWindow(ObjWindow::Warehouse)|| gInterface.CheckWindow(ObjWindow::ChaosBox)|| gInterface.CheckWindow(ObjWindow::CommandWindow)|| gInterface.CheckWindow(ObjWindow::PetInfo)|| gInterface.CheckWindow(ObjWindow::Shop)|| gInterface.CheckWindow(ObjWindow::Inventory)|| gInterface.CheckWindow(ObjWindow::Store)|| gInterface.CheckWindow(ObjWindow::OtherStore)|| gInterface.CheckWindow(ObjWindow::Character)|| gInterface.CheckWindow(ObjWindow::DevilSquare)|| gInterface.CheckWindow(ObjWindow::BloodCastle)|| gInterface.CheckWindow(ObjWindow::CreateGuild)|| gInterface.CheckWindow(ObjWindow::GuardNPC)|| gInterface.CheckWindow(ObjWindow::SeniorNPC)|| gInterface.CheckWindow(ObjWindow::GuardNPC2)|| gInterface.CheckWindow(ObjWindow::CastleGateSwitch)|| gInterface.CheckWindow(ObjWindow::CatapultNPC)|| gInterface.CheckWindow(ObjWindow::CrywolfGate)|| gInterface.CheckWindow(ObjWindow::IllusionTemple)|| gInterface.CheckWindow(ObjWindow::HeroList)|| gInterface.CheckWindow(ObjWindow::ChatWindow)|| gInterface.CheckWindow(ObjWindow::FastMenu)|| gInterface.CheckWindow(ObjWindow::Options)|| gInterface.CheckWindow(ObjWindow::Help)|| gInterface.CheckWindow(ObjWindow::FastDial)|| gInterface.CheckWindow(ObjWindow::SkillTree)|| gInterface.CheckWindow(ObjWindow::GoldenArcher1)|| gInterface.CheckWindow(ObjWindow::GoldenArcher2)|| gInterface.CheckWindow(ObjWindow::LuckyCoin1)|| gInterface.CheckWindow(ObjWindow::LuckyCoin2)|| gInterface.CheckWindow(ObjWindow::NPC_Duel)|| gInterface.CheckWindow(ObjWindow::NPC_Titus)|| gInterface.CheckWindow(ObjWindow::CashShop)|| gInterface.CheckWindow(ObjWindow::Lugard)|| gInterface.CheckWindow(ObjWindow::QuestList1)|| gInterface.CheckWindow(ObjWindow::QuestList2)|| gInterface.CheckWindow(ObjWindow::Jerint)|| gInterface.CheckWindow(ObjWindow::FullMap)|| gInterface.CheckWindow(ObjWindow::NPC_Dialog)|| gInterface.CheckWindow(ObjWindow::GensInfo)|| gInterface.CheckWindow(ObjWindow::NPC_Julia)|| gInterface.CheckWindow(ObjWindow::NPC_ChaosMix)|| gInterface.CheckWindow(ObjWindow::ExpandInventory)|| gInterface.CheckWindow(ObjWindow::ExpandWarehouse)|| gInterface.CheckWindow(ObjWindow::MuHelper)|| gInterface.Data[eMenu_MAIN].OnShow|| gInterface.Data[eVip_MAIN].OnShow|| gInterface.Data[eEventTimePANEL_MAIN].OnShow|| gInterface.Data[eCommand_MAIN].OnShow|| gInterface.Data[eChangePass_Main].OnShow|| gInterface.Data[TAS_Ranking_Main].OnShow|| gInterface.Data[eCONFIRM_MAIN].OnShow|| gInterface.Data[eJewelBank_MAIN].OnShow|| gInterface.Data[eWindowInfo].OnShow|| gInterface.Data[ePARTYSETTINGS_MAIN].OnShow|| gInterface.Data[ePARTYSEARCH_MAIN].OnShow|| gInterface.Data[eLuckySpin].OnShow

#define MAXSIZERL	10
#define MAXSUBSIZE	5

struct RelifeCheckReQuest
{
	PSBMSG_HEAD h;
	int			Number;
};

struct PSBMSG_JewelBankRevX
{
	PSBMSG_HEAD h;
	int JewelIndex[MAXSIZERL];
};

struct RelifeCheckUpdate
{
	PBMSG_HEAD2 h;
	int m_TaiSinh;
	int m_DieuKienLevel;
	int CheckDieuKien[MAXSIZERL];
	int ResetLife;
};

struct RelifePointUpdate
{
	PBMSG_HEAD2 h;
	int CheckDiemTaiSinh[MAXSIZERL];
};

struct RelifeCheckReqInfoPart1
{
	PBMSG_HEAD2 h;
	int CheckDieuKienNgocVal[MAXSIZERL][MAXSUBSIZE];
};
class TASRelife
{
	public:
	TASRelife();
	void CallWindows();
	void BingRelife();
	bool DrawMainRelife;
	float MainWidth;
	float StartY;
	float StartX;
	DWORD ClickTick;

	int m_TaiSinh;
	int m_DieuKienLevel;
	int mCheckDieuKien[MAXSIZERL];
	int ResetLife;
	int mCheckDiemTaiSinh[MAXSIZERL];
	int CheckDieuKienJw[MAXSIZERL][MAXSUBSIZE];

	void DrawLineTaiSinh(int ItemType, int ItemIndex, int ItemLevel, float DrawX, float DrawY, char* ItemName);
	void RelifePacket(int Number);
	void SendMenuButton();
	void OpenWindowsRelife() { gInterface.Data[TASRelife_MainBox].OnShow = true; pSetCursorFocus = true; };
	void CloseWindowsRelife() { gInterface.Data[TASRelife_MainBox].OnShow = false; pSetCursorFocus = false; };
	bool CheckWindowsRelife() { return gInterface.Data[TASRelife_MainBox].OnShow; };
	void CallWindowsRelife();
	bool MainWindowsRelife(DWORD Event);
	bool RejectWindowsRelife(DWORD Event);
	void TaiSinhCheckRecv(RelifeCheckUpdate* TAS);
	void TaiSinhDiemRecv(RelifePointUpdate* TAS);
	void SaveFormGs(RelifeCheckReqInfoPart1* TAS);
	void GetRelifeDataDraw(float x, float y, float Center, int SlotJw1, int SlotJw2, int SlotJw3, int SlotJw4, int SlotJw5, int gmCheckDieuKien, int gmCheckRelife);
}; 
extern TASRelife G_TASRelife;
#endif