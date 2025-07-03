#pragma once
#if(CUSTOM_DUNGLUYENITEM)
#include "Protocol.h"
#define CheckNoVault_Inv gInterface.CheckWindow(ObjWindow::CashShop)|| gInterface.CheckWindow(ObjWindow::FriendList)|| gInterface.CheckWindow(ObjWindow::MoveList)|| gInterface.CheckWindow(ObjWindow::Party)|| gInterface.CheckWindow(ObjWindow::Quest)|| gInterface.CheckWindow(ObjWindow::NPC_Devin)|| gInterface.CheckWindow(ObjWindow::Guild)|| gInterface.CheckWindow(ObjWindow::Trade)|| gInterface.CheckWindow(ObjWindow::Warehouse)|| gInterface.CheckWindow(ObjWindow::ChaosBox)|| gInterface.CheckWindow(ObjWindow::CommandWindow)|| gInterface.CheckWindow(ObjWindow::PetInfo)|| gInterface.CheckWindow(ObjWindow::Shop)|| gInterface.CheckWindow(ObjWindow::Store)|| gInterface.CheckWindow(ObjWindow::OtherStore)|| gInterface.CheckWindow(ObjWindow::Character)|| gInterface.CheckWindow(ObjWindow::DevilSquare)|| gInterface.CheckWindow(ObjWindow::BloodCastle)|| gInterface.CheckWindow(ObjWindow::CreateGuild)|| gInterface.CheckWindow(ObjWindow::GuardNPC)|| gInterface.CheckWindow(ObjWindow::SeniorNPC)|| gInterface.CheckWindow(ObjWindow::GuardNPC2)|| gInterface.CheckWindow(ObjWindow::CastleGateSwitch)|| gInterface.CheckWindow(ObjWindow::CatapultNPC)|| gInterface.CheckWindow(ObjWindow::CrywolfGate)|| gInterface.CheckWindow(ObjWindow::IllusionTemple)|| gInterface.CheckWindow(ObjWindow::HeroList)|| gInterface.CheckWindow(ObjWindow::ChatWindow)|| gInterface.CheckWindow(ObjWindow::FastMenu)|| gInterface.CheckWindow(ObjWindow::Options)|| gInterface.CheckWindow(ObjWindow::Help)|| gInterface.CheckWindow(ObjWindow::FastDial)|| gInterface.CheckWindow(ObjWindow::SkillTree)|| gInterface.CheckWindow(ObjWindow::GoldenArcher1)|| gInterface.CheckWindow(ObjWindow::GoldenArcher2)|| gInterface.CheckWindow(ObjWindow::LuckyCoin1)|| gInterface.CheckWindow(ObjWindow::LuckyCoin2)|| gInterface.CheckWindow(ObjWindow::NPC_Duel)|| gInterface.CheckWindow(ObjWindow::NPC_Titus)|| gInterface.CheckWindow(ObjWindow::CashShop)|| gInterface.CheckWindow(ObjWindow::Lugard)|| gInterface.CheckWindow(ObjWindow::QuestList1)|| gInterface.CheckWindow(ObjWindow::QuestList2)|| gInterface.CheckWindow(ObjWindow::Jerint)|| gInterface.CheckWindow(ObjWindow::FullMap)|| gInterface.CheckWindow(ObjWindow::NPC_Dialog)|| gInterface.CheckWindow(ObjWindow::GensInfo)|| gInterface.CheckWindow(ObjWindow::NPC_Julia)|| gInterface.CheckWindow(ObjWindow::NPC_ChaosMix)|| gInterface.CheckWindow(ObjWindow::ExpandInventory)|| gInterface.CheckWindow(ObjWindow::ExpandWarehouse)|| gInterface.CheckWindow(ObjWindow::MuHelper)

struct DLCSEV_COUNTLIST
{
	PSWMSG_HEAD header;
	int Count;
};
struct XULY_CGPACKETDL
{
	PSBMSG_HEAD header; // C3:F3:03
	DWORD ThaoTac;
};
struct ITEM_INFO_DATA
{
	int IndexItem;
	int Level;
	int Skill;
	int Luck;
	int Option;
	int Exc;
	int Dur;
};

class MixItemDungLuyen
{
	public:
		void MixItemDungLuyen::TruyenXuongProtocol2A(BYTE* lpMsg);
		void MixItemDungLuyen::TruyenXuongProtocol2B(BYTE* lpMsg);
		void MixItemDungLuyen::ToolTipItem(float X, float Y, float W, float H, int iW, int iH, void* ItemSlot);
		void MixItemDungLuyen::DrawWindows();
		void MixItemDungLuyen::BackItemDungLuyen(int Type);
		void MixItemDungLuyen::NhanListItemDungLuyen(DLCSEV_COUNTLIST* lpMsg);
		void MixItemDungLuyen::CreatSlotItem(float x, float y, BYTE ItemSlot);
		bool DL_ActiveMix;
		bool DL_EffectsMix;
		bool SetStateDungLuyen;
		BYTE DL_ItemChinh[16];
		BYTE DL_ItemPhu[3][16];
		BYTE DL_ItemKetQua[16];
		int RateDL;
		int TypeDL;
		char TextDL[100];
		DWORD ClickTime;
		std::vector<ITEM_INFO_DATA> m_DungLuyenInfoList;
		void HienThiItem();
		bool RunCheckMe;
};
extern MixItemDungLuyen gMixDL;
#endif



