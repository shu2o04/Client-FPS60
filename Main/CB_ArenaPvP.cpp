#include "StdAfx.h"
#include "CB_ArenaPvP.h"
#include "CustomFont.h"
#include "Interface.h"
#include "Object.h"
#include "Defines.h"
#include "Config.h"
#include "Central.h"
#include "TAS_ToolKit.h"

#if(CB_EventArenaPvP)
CBArenaPvP gCBArenaPvP;

char* StateEventArenaPvP[5] = { "NULL","Chờ Đăng Ký","Đang chờ","Thực Chiến","Trao Thưởng" };
CBArenaPvP::CBArenaPvP()
{
	char GetFotText[35] = { 0 };
	for (int st = 0; st < 50; st++)
	{
		wsprintf(GetFotText, "Text%d", st);
		GetPrivateProfileStringA("TextVN_ArenaPvP", GetFotText, "Null", TextVN[st], sizeof(TextVN[st]), MENU_GAME_FILE);
	}
}

void CBArenaPvP::DrawBXH()
{
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
	if (!gInterface.Data[eWindowBXHArenaPvP].OnShow)
	{
		return;
	}
	float CuaSoW = 250.0;
	float CuaSoH = 200.0;

	float StartX = (MAX_WIN_WIDTH / 2) - (CuaSoW / 2);
	float StartY = 45.0;

	gCentral.gDrawWindowCustom(StartX, StartY, CuaSoW, CuaSoH, eWindowBXHArenaPvP, this->TextVN[18]);
	gToolKit.CloseButton(412, 44, TAS_BxhArena_BtnClose);
	CustomFont.Draw(CustomFont.FontBold, StartX, StartY + 40, 0xFABB00FF, 0x0, CuaSoW / 3, 0, 3, "Top"); //
	CustomFont.Draw(CustomFont.FontBold, StartX + CuaSoW / 3, StartY + 40, 0xFABB00FF, 0x0, CuaSoW / 3, 0, 3, "Name"); //
	CustomFont.Draw(CustomFont.FontBold, StartX + ((CuaSoW / 3) * 2), StartY + 40, 0xFABB00FF, 0x0, CuaSoW / 3, 0, 3, "Score"); //
	DWORD ColorTextRank = 0xE0DFDCFF;

	for (int i = 0; i < this->mDataBXHKiller.size(); i++)
	{
		if (i % 2)
		{
			ColorTextRank = 0xA3A3A3FF;
		}
		else {
			ColorTextRank = 0xE0DFDCFF;
		}
		if (i < 3) { ColorTextRank = 0xFFE240FF; }
		CustomFont.Draw(CustomFont.FontBold, StartX, StartY + 55 + (i * 12), ColorTextRank, (i < 3) ? 0xFFE2400F : 0x0, CuaSoW / 3, 0, 3, "%d", i + 1); //
		CustomFont.Draw(CustomFont.FontBold, StartX + CuaSoW / 3, StartY + 55 + (i * 12), ColorTextRank, (i < 3) ? 0xFFE2400F : 0x0, CuaSoW / 3, 0, 3, "%s", this->mDataBXHKiller[i].Name); //
		CustomFont.Draw(CustomFont.FontBold, StartX + ((CuaSoW / 3) * 2), StartY + 55 + (i * 12), ColorTextRank, (i < 3) ? 0xFFE2400F : 0x0, CuaSoW / 3, 0, 3, "%d", this->mDataBXHKiller[i].Score); //
	}
}
void CBArenaPvP::DrawWindowNPC()
{
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
	if (!gInterface.Data[eWindowNPCArenaPvP].OnShow)
	{
		return;
	}


	float CuaSoW = 300;
	float CuaSoH = 170;

	float StartX = (MAX_WIN_WIDTH - CuaSoW) / 2;
	float StartY = 100;
	pSetCursorFocus = true;
	
	gCentral.gDrawWindowCustom(StartX, StartY, CuaSoW, CuaSoH, eWindowNPCArenaPvP, this->TextVN[0]);
	gToolKit.CloseButton(436, 99, Arena_CLOSE);

	RenderBitmap(0x17908, 280, 210, 150, 80, 0.0, 0.0, 1, 1, 1, 1, 0);
	if (pCheckMouseOver(280, 239, 80, 20) == 1)
	{
		RenderBitmap(0x17909, 280, 210, 150, 80, 0.0, 0.0, 1, 1, 1, 1, 0);
		if (GetTickCount() - gInterface.Data[eWindowNPC_ThanMaChien].EventTick > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				XULY_CGPACKET pMsg;
				pMsg.header.set(0xD3, 0x1E, sizeof(pMsg));
				pMsg.ThaoTac = 1;
				DataSend((LPBYTE)&pMsg, pMsg.header.size);
				gInterface.Data[eWindowNPCArenaPvP].OnShow ^= 1;
			}
		}
	}
	CustomFont.Draw(CustomFont.FontNormal, 280, 239, 0xE6FCF7FF, 0x0, 80, 0, 3, gConfig.TTAS_TEXT_ENGINE[15]);

	float TextStartY = StartY + 33;
	for (int ct = 0; ct < 7; ct++)
	{
		CustomFont.Draw((HFONT)pFontNormal, (StartX + (CuaSoW / 10)) - 5, TextStartY + (12 * ct) + 10, 0xFFDE26FF, 0x0, CuaSoW, 0, 1, this->TextVN[2 + ct]);
	}
}
void CBArenaPvP::DrawPoint()
{
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
	if (this->mDataTimeSend.empty())
	{
		return;
	}
	if (pMapNumber != this->mDataTimeSend[0].Map || this->mDataTimeSend[0].TimeCount == 0)
	{
		return;
	}

	float InfoW = 100;
	float InfoH = 40;
	float InfoX = MAX_WIN_WIDTH - (InfoW + 20) - 45;
	float InfoY = MAX_WIN_HEIGHT - (InfoH + 60);

	if (pCheckMouseOver(475, 356, 113, 12))
	{
		pSetCursorFocus = true;
	}
	if (gCentral.gDrawButton(InfoX - 3, InfoY - 28, 113, 12, this->TextVN[18]) && (GetTickCount() - gInterface.Data[eWindowBXHGuildPvP].EventTick) > 300)
	{
		gInterface.Data[eWindowBXHArenaPvP].OnShow ^= 1;
	}
	gCentral.gInfoBox(InfoX, InfoY, InfoW, InfoH, 0x00000096, 0, 0);
	if (this->mDataInfoUserKill.empty())
	{
		CustomFont.Draw(CustomFont.FontBold, InfoX, InfoY + 13, 0xE6FCF7FF, 0x00FFE564, InfoW + 7, 0, 3, "---"); //score
		CustomFont.Draw(CustomFont.FontBold, InfoX, (InfoY + InfoH) - 17, 0xE6FCF7FF, 0xFFBB0064, InfoW + 7, 0, 3, "---");//Death
	}
	else
	{
		CustomFont.Draw(CustomFont.FontBold, InfoX, InfoY + 13, 0xE6FCF7FF, 0x00FFE564, InfoW + 7, 0, 3, this->TextVN[16], this->mDataInfoUserKill[0].Score); //score
		CustomFont.Draw(CustomFont.FontBold, InfoX, (InfoY + InfoH) - 17, 0xE6FCF7FF, 0xFFBB0064, InfoW + 7, 0, 3, this->TextVN[17], this->mDataInfoUserKill[0].Kills,this->mDataInfoUserKill[0].Deaths);//Death
	}
	if (!this->mDataTimeSend.empty())
	{
		CustomFont.Draw(CustomFont.FontBold, InfoX, InfoY + 3, 0xE6FCF7FF, 0x0, InfoW + 7, 0, 3, StateEventArenaPvP[this->mDataTimeSend[0].State]);
		if (this->mDataTimeSend[0].TimeCount - GetTimeGMT() > 1)
		{
			BRenderTimeCountDown(InfoX, (InfoY + InfoH) - 7, InfoW + 10, this->mDataTimeSend[0].TimeCount - GetTimeGMT());
		}
	}
	return;
}
void CBArenaPvP::Draw()
{
	CBArenaPvP::DrawBXH();
	CBArenaPvP::DrawWindowNPC();
	CBArenaPvP::DrawPoint();
}

int CBArenaPvP::GetTimeGMT()
{
	time_t rawTime;
	struct tm* timeInfo;

	time(&rawTime);
	timeInfo = gmtime(&rawTime);

	timeInfo->tm_hour += (gProtect.m_MainInfo.TIME_GMT);
	return mktime(timeInfo);

}
void CBArenaPvP::BRenderTimeCountDown(float x, float y, float w, int MatchTime)
{
	char lpszStr[256];
	char lpszStrS[10];
	int iMinute = MatchTime / 60;
	DWORD ColorText = 0xE6FCF7FF;
	wsprintf(lpszStr, " %.2d :", iMinute);

	int iSecondTime = MatchTime - (iMinute * 60);
	if (iSecondTime >= 0)
	{
		wsprintf(lpszStrS, " %.2d", iSecondTime);
		strcat(lpszStr, lpszStrS);
	}

	if (iMinute < 5)
	{
		ColorText = 0xFF2121FF;
	}
	if (iMinute < 15)
	{
		wsprintf(lpszStrS, ": %.2d", ((int)WorldTime % 60));
		strcat(lpszStr, lpszStrS);
	}
	HFONT FontTextTime = CreateFontA(14, 0, 0, 0, 700, 0, 0, 0, 0x1, 0, 0, 3, 0, "Tahoma");
	CustomFont.Draw(FontTextTime, x, y, ColorText, 0x0, w, 0, 3, lpszStr); //
	DeleteObject(FontTextTime);
}

void CBArenaPvP::RecvPacketGS(BYTE* Data)
{
	if (!Data) return;
	
	PMSG_COUNTLIST* mRecv = (PMSG_COUNTLIST*)Data;
	switch (mRecv->TypeSend)
	{
		case eSendInfoNPCJoin: //Open window Tham Gia
		{
			gInterface.Data[eWindowNPCArenaPvP].OnShow = true;
		}
		break;
		case eSendTime: //Open Time
		{
			this->mDataTimeSend.clear();
			for (int i = 0; i < mRecv->Count; i++)
			{
				DATA_TIME_SEND lpInfo = *(DATA_TIME_SEND*)(((BYTE*)Data) + sizeof(PMSG_COUNTLIST) + (sizeof(DATA_TIME_SEND) * i));
				lpInfo.TimeCount += GetTimeGMT();
				this->mDataTimeSend.push_back(lpInfo);
			}
		}
		break;
		case eSendBXHKill: //Recv BXH
		{
			this->mDataBXHKiller.clear();
			for (int i = 0; i < mRecv->Count; i++)
			{
				DATA_BXH_KILL lpInfo = *(DATA_BXH_KILL*)(((BYTE*)Data) + sizeof(PMSG_COUNTLIST) + (sizeof(DATA_BXH_KILL) * i));
				this->mDataBXHKiller.push_back(lpInfo);
			}
		}
		break;
		case eSendInfoUser: //Recv Info Kill User
		{
			this->mDataInfoUserKill.clear();
			for (int i = 0; i < mRecv->Count; i++)
			{
				DATA_INFOUSER_SEND lpInfo = *(DATA_INFOUSER_SEND*)(((BYTE*)Data) + sizeof(PMSG_COUNTLIST) + (sizeof(DATA_INFOUSER_SEND) * i));
				this->mDataInfoUserKill.push_back(lpInfo);
			}
		}
		break;
		case eSendClearInfo: //Clear Info
		{
			this->mDataInfoUserKill.clear();
			this->mDataTimeSend.clear();
			this->mDataInfoUserKill.clear();
		}
		break;
		default:
			break;
	}
}
#endif