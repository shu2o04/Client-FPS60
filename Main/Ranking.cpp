#include "stdafx.h"
#include "Ranking.h"
#include "Import.h"
#include "Defines.h"
#include "Interface.h"
#include "Util.h"
#include "CustomMap.h"
#include "Controller.h"
#include "PartySearch.h"
#include "Central.h"
#include "User.h"
#include "WindowsStruct.h"
#include "CustomFont.h"
#include "UIControl.h"
#include "TAS_ToolKit.h"
#include "Import.h"
#include "Config.h"
#include "Console.h"
#include "ViewCharItem.h"
#include "TAS_FixSolution.h"
#include "CBNewUiEx.h"

cRanking gRanking;


char* CharacterCode(int a)
{
	switch (a)
	{
	case 0:  return pGetTextLine(pTextLineThis, 20);
	case 1:  return pGetTextLine(pTextLineThis, 25);
	case 2:  return pGetTextLine(pTextLineThis, 1669);
	case 3:  return pGetTextLine(pTextLineThis, 1669);
	case 16: return pGetTextLine(pTextLineThis, 21);
	case 17: return pGetTextLine(pTextLineThis, 26);
	case 18: return pGetTextLine(pTextLineThis, 1668);
	case 19: return pGetTextLine(pTextLineThis, 1668);
	case 32: return pGetTextLine(pTextLineThis, 22);
	case 33: return pGetTextLine(pTextLineThis, 27);
	case 34: return pGetTextLine(pTextLineThis, 1670);
	case 35: return pGetTextLine(pTextLineThis, 1670);
	case 48: return pGetTextLine(pTextLineThis, 23);
	case 50: return pGetTextLine(pTextLineThis, 1671);
	case 66: return pGetTextLine(pTextLineThis, 24);
	case 67: return pGetTextLine(pTextLineThis, 24);
	case 64: return pGetTextLine(pTextLineThis, 24);
	case 65: return pGetTextLine(pTextLineThis, 24);
	case 68: return pGetTextLine(pTextLineThis, 1672);
	case 80: return pGetTextLine(pTextLineThis, 1687);
	case 81: return pGetTextLine(pTextLineThis, 1688);
	case 82: return pGetTextLine(pTextLineThis, 1689);
	case 83: return pGetTextLine(pTextLineThis, 1689);
	case 96: return pGetTextLine(pTextLineThis, 3150);
	case 97: return pGetTextLine(pTextLineThis, 3151);
	case 98: return pGetTextLine(pTextLineThis, 3151);
	}
	return "unknown";
}
cRanking::cRanking()
{
	this->Active = true;
	this->Show = false;
	this->StartX = 0;
	this->StartY = 0;
	this->Page = 1;
	this->ClickTick = 0;
	this->TrangRanking = 1;
}

void cRanking::RecvInfo(DGCharTop* lpMsg)
{
	for (int i = 0; i < MAXTOP; i++)
	{
		strncpy(this->RankingChar[i].Name, lpMsg->tp[i].Name, 11);

		this->RankingChar[i].Is_Class = lpMsg->tp[i].Is_Class;
		this->RankingChar[i].Is_cLevel = lpMsg->tp[i].Is_cLevel;
		this->RankingChar[i].Is_ResetCount = lpMsg->tp[i].Is_ResetCount;
		this->RankingChar[i].Is_MasterResetCount = lpMsg->tp[i].Is_MasterResetCount;
		this->RankingChar[i].Is_ResetTime = lpMsg->tp[i].Is_ResetTime;
		this->RankingChar[i].Is_TotalPoint = lpMsg->tp[i].Is_TotalPoint;

#if MAXTOP <= 40
		this->RankingChar[i].Is_Strength = lpMsg->tp[i].Is_Strength;
		this->RankingChar[i].Is_Dexterity = lpMsg->tp[i].Is_Dexterity;
		this->RankingChar[i].Is_Vitality = lpMsg->tp[i].Is_Vitality;
		this->RankingChar[i].Is_Energy = lpMsg->tp[i].Is_Energy;
		this->RankingChar[i].Is_Leadership = lpMsg->tp[i].Is_Leadership;
		this->RankingChar[i].Is_Life = lpMsg->tp[i].Is_Life;
		this->RankingChar[i].Is_MaxLife = lpMsg->tp[i].Is_MaxLife;
		this->RankingChar[i].Is_Mana = lpMsg->tp[i].Is_Mana;
		this->RankingChar[i].Is_MaxMana = lpMsg->tp[i].Is_MaxMana;
		this->RankingChar[i].Is_BP = lpMsg->tp[i].Is_BP;
		this->RankingChar[i].Is_MaxBP = lpMsg->tp[i].Is_MaxBP;
		this->RankingChar[i].Is_Shield = lpMsg->tp[i].Is_Shield;
		this->RankingChar[i].Is_MaxShield = lpMsg->tp[i].Is_MaxShield;
		this->RankingChar[i].Is_LucChien = lpMsg->tp[i].Is_LucChien;
		this->RankingChar[i].Is_PkCount = lpMsg->tp[i].Is_PkCount;
		this->RankingChar[i].Is_Kills = lpMsg->tp[i].Is_Kills;
		this->RankingChar[i].Is_Deads = lpMsg->tp[i].Is_Deads;
		this->RankingChar[i].Is_WcoinC = lpMsg->tp[i].Is_WcoinC;
		this->RankingChar[i].Is_CoinAtm = lpMsg->tp[i].Is_CoinAtm;
		this->RankingChar[i].Is_ConnectStat = lpMsg->tp[i].Is_ConnectStat;
		this->RankingChar[i].Is_OnlineHours = lpMsg->tp[i].Is_OnlineHours;

		this->RankingChar[i].Is_BC = lpMsg->tp[i].Is_BC;
		this->RankingChar[i].Is_CC = lpMsg->tp[i].Is_CC;
		this->RankingChar[i].Is_DS = lpMsg->tp[i].Is_DS;
		this->RankingChar[i].Is_Win = lpMsg->tp[i].Is_Win;
		this->RankingChar[i].Is_Lose = lpMsg->tp[i].Is_Lose;
		this->RankingChar[i].Is_Kboss = lpMsg->tp[i].Is_Kboss;

		strncpy(this->RankingChar[i].Is_JoinDate, lpMsg->tp[i].Is_JoinDate, 22);
		strncpy(this->RankingChar[i].Is_LastIP, lpMsg->tp[i].Is_LastIP, 16);
#		endif
		strncpy(this->RankingChar[i].Is_SvSub, lpMsg->tp[i].Is_SvSub, 9);
	}
}
void cRanking::RecvInfoTP(DGCharTopTP* lpMsg)
{
	for (int i = 0; i < MAXTOP; i++)
	{
		strncpy(this->RankingCharTP[i].Name, lpMsg->tp[i].Name, 11);
		this->RankingCharTP[i].Is_WcoinC = lpMsg->tp[i].Is_WcoinC;
		this->RankingCharTP[i].Is_WcoinP = lpMsg->tp[i].Is_WcoinP;
		this->RankingCharTP[i].Is_WcoinG = lpMsg->tp[i].Is_WcoinG;
		this->RankingCharTP[i].Is_WcoinR = lpMsg->tp[i].Is_WcoinR;
		this->RankingCharTP[i].Is_CoinAtm = lpMsg->tp[i].Is_CoinAtm;
	}
}
void cRanking::RecvInfoET(DGCharTopET* lpMsg)
{
	for (int i = 0; i < MAXTOP; i++)
	{
		strncpy(this->RankingCharET[i].Name, lpMsg->tp[i].Name, 11);
		this->RankingCharET[i].Is_BloodCS = lpMsg->tp[i].Is_BloodCS;
		this->RankingCharET[i].Is_ChaosCS = lpMsg->tp[i].Is_ChaosCS;
		this->RankingCharET[i].Is_DevilCS = lpMsg->tp[i].Is_DevilCS;
	}
}
void cRanking::RecvInfoTG(DGCharTopTG* lpMsg)
{
	for (int i = 0; i < MAXTOP; i++)
	{
		strncpy(this->RankingCharTG[i].G_Name, lpMsg->tp[i].G_Name, 9);
		strncpy(this->RankingCharTG[i].G_Master, lpMsg->tp[i].G_Master, 11);
		this->RankingCharTG[i].Is_GLevel = lpMsg->tp[i].Is_GLevel;
		this->RankingCharTG[i].Is_GScore = lpMsg->tp[i].Is_GScore;
		this->RankingCharTG[i].Is_GMem = lpMsg->tp[i].Is_GMem;
		strncpy(this->RankingCharTG[i].Is_JoinDate, lpMsg->tp[i].Is_JoinDate, 22);
	}
}
void cRanking::RecvInfoPK(DGCharTopPK* lpMsg)
{
	for (int i = 0; i < MAXTOP; i++)
	{
		strncpy(this->RankingCharPK[i].Name, lpMsg->tp[i].Name, 11);
		this->RankingCharPK[i].Is_Kills = lpMsg->tp[i].Is_Kills;
		this->RankingCharPK[i].Is_Deads = lpMsg->tp[i].Is_Deads;
		this->RankingCharPK[i].Is_OnlineHours = lpMsg->tp[i].Is_OnlineHours;
		this->RankingCharPK[i].Is_Win = lpMsg->tp[i].Is_Win;
		this->RankingCharPK[i].Is_Lose = lpMsg->tp[i].Is_Lose;
		this->RankingCharPK[i].Is_Kboss = lpMsg->tp[i].Is_Kboss;
		strncpy(this->RankingCharPK[i].Is_JoinDate, lpMsg->tp[i].Is_JoinDate, 22);
	}
}
void cRanking::RecvInfoMT(DGCharTopMT* lpMsg)
{
	for (int i = 0; i < MAXTOP; i++)
	{
		strncpy(this->RankingCharMT[i].Name, lpMsg->tp[i].Name, 11);
		this->RankingCharMT[i].cLevel = lpMsg->tp[i].cLevel;
		this->RankingCharMT[i].cPoint = lpMsg->tp[i].cPoint;
		this->RankingCharMT[i].cExp = lpMsg->tp[i].cExp;
	}
}

void cRanking::GCReqInfoCharTop(DATA_VIEWTOPRANKING* lpMsg)
{
	this->CacheUserRank = true;
	this->SetItemCharTop = false;
	ZeroMemory(&this->CacheDataUserTop, sizeof(&this->CacheDataUserTop));
	memcpy(&this->CacheDataUserTop, lpMsg, sizeof(this->CacheDataUserTop));
	ViewCharItems.ClearSession();
	memcpy(&ViewCharItems.charItem.Guild[0], &this->CacheDataUserTop.GuildName[0], sizeof(ViewCharItems.charItem.Guild));
	memcpy(&ViewCharItems.charItem.Name[0], &this->CacheDataUserTop.NameChar[0], 10);
}
#define _DWORD		DWORD
#define B0042CFE0	((int (__thiscall*)(int This, unsigned int  a2)) 0x0042CFE0)
void __cdecl BCreateGuildMark(BYTE* mGuildMark, bool a2)
{
	int k; // [esp+4h] [ebp-24h]
	int j; // [esp+8h] [ebp-20h]
	int i; // [esp+Ch] [ebp-1Ch]
	_DWORD* v5; // [esp+10h] [ebp-18h]
	int* v6; // [esp+14h] [ebp-14h]
	BYTE* v7; // [esp+18h] [ebp-10h]
	int height; // [esp+1Ch] [ebp-Ch]
	int width; // [esp+20h] [ebp-8h]
	int v10; // [esp+24h] [ebp-4h]

	DWORD* dword_81C0450 = &*(DWORD*)0x81C0450;
	BYTE* byte_81CB59E = &*(BYTE*)0x81CB59E;
	v6 = (int*)B0042CFE0((int)0x9816AA0, 0x7BFCu);
	width = (int)*((float*)v6 + 65);
	height = (int)*((float*)v6 + 66);
	v5 = *(_DWORD**)((char*)v6 + 282);
	v10 = 128;
	if (a2)
	{
		v10 = 0;
	}

	for (int i = 0; i < 16; i++)
	{
		switch (i)
		{
		case 0:dword_81C0450[i] = (v10 << 24) + (0 << 16) + (0 << 8) + (0); break;
		case 1:dword_81C0450[i] = (255 << 24) + (0 << 16) + (0 << 8) + (0); break;
		case 2:dword_81C0450[i] = (255 << 24) + (128 << 16) + (128 << 8) + (128); break;
		case 3:dword_81C0450[i] = (255 << 24) + (255 << 16) + (255 << 8) + (255); break;
		case 4:dword_81C0450[i] = (255 << 24) + (0 << 16) + (0 << 8) + (255); break;
		case 5:dword_81C0450[i] = (255 << 24) + (0 << 16) + (128 << 8) + (255); break;
		case 6:dword_81C0450[i] = (255 << 24) + (0 << 16) + (255 << 8) + (255); break;
		case 7:dword_81C0450[i] = (255 << 24) + (0 << 16) + (255 << 8) + (128); break;
		case 8:dword_81C0450[i] = (255 << 24) + (0 << 16) + (255 << 8) + (0); break;
		case 9:dword_81C0450[i] = (255 << 24) + (128 << 16) + (255 << 8) + (0); break;
		case 10:dword_81C0450[i] = (255 << 24) + (255 << 16) + (255 << 8) + (0); break;
		case 11:dword_81C0450[i] = (255 << 24) + (255 << 16) + (128 << 8) + (0); break;
		case 12:dword_81C0450[i] = (255 << 24) + (255 << 16) + (0 << 8) + (0); break;
		case 13:dword_81C0450[i] = (255 << 24) + (255 << 16) + (0 << 8) + (128); break;
		case 14:dword_81C0450[i] = (255 << 24) + (255 << 16) + (0 << 8) + (255); break;
		case 15:dword_81C0450[i] = (255 << 24) + (128 << 16) + (0 << 8) + (255); break;
		}
	}
	BYTE GuildMark[64] = { 0 };
	for (int i = 0; i < 64; ++i)
	{
		if (i % 2 == 0)
			GuildMark[i] = (mGuildMark[i / 2] >> 4) & 0x0f;
		else
			GuildMark[i] = mGuildMark[i / 2] & 0x0f;
	}

	v7 = &*(BYTE*)GuildMark; //Mark
	for (j = 0; j < height; ++j)
	{
		for (k = 0; k < width; ++k)
			*v5++ = dword_81C0450[(unsigned __int8)*v7++];
	}
	glBindTexture(0xDE1u, *(_DWORD*)((char*)v6 + 277));
	glTexImage2D(0xDE1u, 0, *((char*)v6 + 276), width, height, 0, 0x1908u, 0x1401u, *(const GLvoid**)((char*)v6 + 282));
}
void GetInfoCharTop(char* Name)
{
	if (GetTickCount() < gInterface.Data[TAS_Ranking_Main].EventTick + 300) return;
	gInterface.Data[TAS_Ranking_Main].EventTick = GetTickCount();

	REQUESTINFO_CHARTOP pMsg;
	pMsg.header.set(0xD3, 0x40, sizeof(pMsg));
	pMsg.aIndex = 0;
	memcpy(pMsg.NameChar, Name, sizeof(pMsg.NameChar) - 1);
	DataSend((LPBYTE)&pMsg, pMsg.header.size);
}
void cRanking::GetPacketSender(DWORD ClickMouse, DWORD Delay, BYTE Pages, int Packet)
{
	if (ClickMouse == WM_LBUTTONDOWN)
	{
		pSetCursorFocus = true;
		return;
	}
	if (Delay < 300)
	{
		return;
	}
	if (TrangRanking = Pages)
	{
		ClickTick = GetTickCount();
		UP_SEND_REQ pRequest;
		pRequest.h.set(0x7A, Packet, sizeof(pRequest));
		DataSend((BYTE*)&pRequest, pRequest.h.size);
	}
}

void cRanking::ClickRanking(DWORD ClickMouse)
{
	if (!this->Active) return;
	if (!this->Show) return;
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - ClickTick);

	if (gInterface.IsWorkZone(ChonTopAll))
	{
		this->GetPacketSender(ClickMouse, Delay, 1, 0x01);
	}
	if (gInterface.IsWorkZone(ChonTopWC))
	{
		this->GetPacketSender(ClickMouse, Delay, 2, 0x02);
	}
	if (gInterface.IsWorkZone(ChonTopEvent))
	{
		this->GetPacketSender(ClickMouse, Delay, 3, 0x03);
	}
	if (gInterface.IsWorkZone(ChonTopGuild))
	{
		this->GetPacketSender(ClickMouse, Delay, 4, 0x04);
	}
	if (gInterface.IsWorkZone(ChonTopPK))
	{
		this->GetPacketSender(ClickMouse, Delay, 5, 0x05);
	}
	if (gInterface.IsWorkZone(ChonTopMT))
	{
		this->GetPacketSender(ClickMouse, Delay, 6, 0x06);
	}
}
void cRanking::SendMenuButton()
{
	UP_SEND_REQ pRequest;
	pRequest.h.set(0x7A, 0x01, sizeof(pRequest));
	DataSend((BYTE*)&pRequest, pRequest.h.size);
	this->Show = true;
}
void cRanking::LoadImg()
{
	LoadBitmapA("TAS\\MacroUI\\Btn_A_RankAll.tga", 0x17928, GL_LINEAR, 0x2901, 1, 0);
	LoadBitmapA("TAS\\MacroUI\\Btn_A_RankCoin.tga", 0x17929, GL_LINEAR, 0x2901, 1, 0);
	LoadBitmapA("TAS\\MacroUI\\Btn_A_Event.tga", 0x1792A, GL_LINEAR, 0x2901, 1, 0);
	LoadBitmapA("TAS\\MacroUI\\Btn_A_Guild.tga", 0x1792B, GL_LINEAR, 0x2901, 1, 0);
	LoadBitmapA("TAS\\MacroUI\\Btn_A_PkCount.tga", 0x1792C, GL_LINEAR, 0x2901, 1, 0);
	LoadBitmapA("TAS\\MacroUI\\Btn_A_Mter.tga", 0x1792D, GL_LINEAR, 0x2901, 1, 0);
	LoadBitmapA("TAS\\MacroUI\\Btn_B_PkCount.tga", 0x1792E, GL_LINEAR, 0x2901, 1, 0);

}
void cRanking::BingImg()
{
	gInterface.BindObject(ChonTopAll, 0x7AE5, 15, 17, -1, -1);
	gInterface.BindObject(ChonTopWC, 0x7AE5, 15, 17, -1, -1);
	gInterface.BindObject(ChonTopEvent, 0x7AE5, 15, 17, -1, -1);
	gInterface.BindObject(ChonTopGuild, 0x7AE5, 15, 17, -1, -1);
	gInterface.BindObject(ChonTopPK, 0x7AE5, 15, 17, -1, -1);
	gInterface.BindObject(ChonTopMT, 0x7AE5, 15, 17, -1, -1);
}

void DrawPlayerRank(int X, int Y, int W, int H)
{
	X = X + 40;
	Y = Y + 40;
	H = H - 100;

	if (!gRanking.CacheUserRank)
	{
		gInterface.DrawFormat(eGold, X /1.5 + (W / 2), Y + (H / 2), 52, 1, "Đang tải...");
	}
	else
	{
		gInterface.DrawFormat(eGold, X, Y - 40, 100, 3, "ViewChar: %s", gRanking.CacheDataUserTop.NameChar);
		if (pCheckMouseOver(X + 37, Y - 40, 40, 15) == 1)
		{
			if (pIsKeyPress(VK_LBUTTON) && GetTickCount() > gInterface.Data[TAS_Ranking_Main].EventTick + 300)
			{
				ViewCharItems.onView ^= 1;
				ViewCharItems.DangXem ^= 1;
				ViewCharItems.ActionTime = GetTickCount();
				gInterface.Data[TAS_Ranking_Main].EventTick = GetTickCount();
			}
			//pDrawToolTip(pCursorX - 60, pCursorY - 10, "Xem Đồ Nhân Vật");
		}
		if (!gRanking.SetItemCharTop)
		{
			for (int n = 0; n < 12; n++)
			{
				if (gRanking.CacheDataUserTop.Item[n][0] != 0xFF && gRanking.CacheDataUserTop.Item[n][0] != 0)
				{
					int GetInfoLoadItem = ((int(__thiscall*)(int a1, void* lp)) 0x7E1B10)(*(DWORD*)(GetInstance() + 36), gRanking.CacheDataUserTop.Item[n]);
					if (GetInfoLoadItem)
					{
						memcpy(&ViewCharItems.charItem.Item[n], (BYTE*)GetInfoLoadItem, sizeof(ViewCharItems.charItem.Item[n]));
					}
				}
			}
			gRanking.SetItemCharTop = true;
		}
	}
}
CNewUIScrollBar* ListScrollBarCase1 = NULL;
CNewUIScrollBar* ListScrollBarCase2 = NULL;
CNewUIScrollBar* ListScrollBarCase3 = NULL;
CNewUIScrollBar* ListScrollBarCase4 = NULL;
CNewUIScrollBar* ListScrollBarCase5 = NULL;
CNewUIScrollBar* ListScrollBarCase6 = NULL;
bool UpdateMaxPosCase1 = false;
bool UpdateMaxPosCase2 = false;
bool UpdateMaxPosCase3 = false;
bool UpdateMaxPosCase4 = false;
bool UpdateMaxPosCase5 = false;
bool UpdateMaxPosCase6 = false;
void cRanking::Draw()
{
	if (gInterface.Data[eChangePass_Main].OnShow)
	{
		return;
	}
	if (CheckTAS_WINDOWS4)
	{
		gRanking.Show = false;
		return;
	}
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	if (!this->Active) return;
	if (!this->Show) return;
	float MainWidth = 445.0 + 160.0;
	float MainHeight = 364.0;
	float StartY = ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);
	float StartX = JCResto+(MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);

	RenderBitmap(0x1791E, StartX + 130, StartY, 596, 450, 0, 0, 1, 1, 1, 1, 0.0);
	RenderBitmap(0x17920, StartX + 130, StartY, 408, 130, 0, 0, 1, 1, 1, 1, 0.0);

	gToolKit.CloseButton(JCResto+475, 39, TAS_Ranking_BtnClose);
	pSetCursorFocus = true;
	char ClassName[11] = { 0 };
	memcpy(ClassName, gObjUser.lpPlayer->Name, sizeof(gObjUser.lpPlayer->Name));
	float PosY_Add = 55;

	int playerRank = -1;
	int playerClass = -1;
	char playerScore[20];
	char playerPoint[20];
	char playerMap[20];
	char playerTime[17];

	gToolKit.DrawButtonIconRank(ChonTopAll, 0x17928, StartX + 140, StartY + 30, 16, 19, "Top Reset");
	gToolKit.DrawButtonIconRank(ChonTopWC, 0x17929, StartX + 155, StartY + 30, 16, 19, "Top Tài Phú");
	gToolKit.DrawButtonIconRank(ChonTopEvent, 0x1792A, StartX + 170, StartY + 30, 16, 19, "Top Event");
	gToolKit.DrawButtonIconRank(ChonTopPK, 0x1792C, StartX + 185, StartY + 30, 16, 19, "Top PK");
	gToolKit.DrawButtonIconRank(ChonTopMT, 0x1792D, StartX + 200, StartY + 30, 16, 19, "Top MT");

	CustomFont.Draw((HFONT)pFontBold, StartX + 147, StartY + 62, 0x0, 0xFF222299, 320, 0, 3, " ");
	DrawPlayerRank(StartX + 360, StartY + 45, 120, MainHeight - 110);

	int PosXInvetoryImg = 280;
	int PosYInvetoryImg = 52;
	switch (TrangRanking)
	{
	case 1:

		this->ListMaxPer[0] = 20;
		this->DataList[0] = iMaxCount;
		if (ListScrollBarCase1 == NULL)
		{
			ListScrollBarCase1 = new CNewUIScrollBar();
			ListScrollBarCase1->Create(JCResto+PosXInvetoryImg + 210, PosYInvetoryImg + 40, 270);
			if (ListScrollBarCase1)
			{
				ListScrollBarCase1->SetMaxPos((this->DataList[0] <= this->ListMaxPer[0]) ? 0 : (this->DataList[0] - this->ListMaxPer[0]));
				ListScrollBarCase1->SetPos(JCResto+PosXInvetoryImg + 210, PosYInvetoryImg + 40);
			}
		}
		if (ListScrollBarCase1)
		{
			if (UpdateMaxPosCase1)
			{
				ListScrollBarCase1->SetMaxPos((this->DataList[0] <= this->ListMaxPer[0]) ? 0 : (this->DataList[0] / this->ListMaxPer[0]));
				UpdateMaxPosCase1 = false;
			}

			ListScrollBarCase1->MouseWheelWindow = pCheckMouseOver(JCResto+PosXInvetoryImg - 113, PosYInvetoryImg + 40, 330, 270);
			ListScrollBarCase1->Render();
			ListScrollBarCase1->UpdateMouseEvent();
			ListScrollBarCase1->Update();
		}
		this->ListPage[0] = ListScrollBarCase1->GetCurPos();
		this->Count[0] = 0;
		this->CurPos[0] = ListScrollBarCase1->GetCurPos();
		gInterface.DrawFormat(eWhite, StartX + 105, StartY + 62, 100, 3, "TOP");
		gInterface.DrawFormat(eWhite, StartX + 135, StartY + 62, 100, 3, "Tên");
		gInterface.DrawFormat(eWhite, StartX + 185, StartY + 62, 100, 3, "Chủng Tộc");
		gInterface.DrawFormat(eWhite, StartX + 230, StartY + 62, 100, 3, "LV/RS/RL");
		gInterface.DrawFormat(eWhite, StartX + 270, StartY + 62, 100, 3, "Tổng Point");
		gInterface.DrawFormat(eWhite, StartX + 325, StartY + 62, 100, 3, "Máy Chủ");
		gInterface.DrawFormat(eWhite, StartX + 385, StartY + 62, 100, 3, "Thời Gian Reset");
		for (int i = 0; i < 100; i++)
		{
			char NameID[11];
			memcpy(NameID, this->RankingChar[i].Name, sizeof(this->RankingChar[i].Name));
			NameID[sizeof(NameID) - 1] = '\0';

			if (strcmp(gObjUser.lpPlayer->Name, NameID) == 0)
			{
				playerRank = i + 1;
				playerClass = this->RankingChar[i].Is_Class;
				sprintf(playerScore, "%d/%d/%d", this->RankingChar[i].Is_cLevel, this->RankingChar[i].Is_ResetCount, this->RankingChar[i].Is_MasterResetCount);
				sprintf(playerPoint, "%s", gToolKit.QNumberFormat(this->RankingChar[i].Is_TotalPoint));
				sprintf(playerMap, this->RankingChar[i].Is_SvSub);
				time_t mTime = this->RankingChar[i].Is_ResetTime;
				tm* lpTime = localtime(&mTime);
				if (lpTime)
				{
					sprintf(playerTime, "%02d:%02d:%02d [%02d/%02d]", lpTime->tm_hour, lpTime->tm_min, lpTime->tm_sec, lpTime->tm_mday, lpTime->tm_mon + 1);
				}
				break;
			}
		}
		for (int i = this->CurPos[0]; i < iMaxCount; i++)
		{
			DWORD Color;
			char NameID[11];
			char NameSub[9];

#if MAXTOP <= 40
			char OnMyDate[30];
			char LastIP[16];
#endif
			int up = i + ((this->Page - 1) * iMaxCount);
			if (this->RankingChar[up].Name[0] == NULL) continue;
			memcpy(NameID, this->RankingChar[up].Name, sizeof(this->RankingChar[up].Name));
			NameID[sizeof(NameID) - 1] = '\0';
#if MAXTOP <= 40
			memcpy(OnMyDate, this->RankingChar[up].Is_JoinDate, sizeof(this->RankingChar[up].Is_JoinDate));
			memcpy(LastIP, this->RankingChar[up].Is_LastIP, sizeof(this->RankingChar[up].Is_LastIP));
#endif
			memcpy(NameSub, this->RankingChar[up].Is_SvSub, sizeof(this->RankingChar[up].Is_SvSub));
			int mYear = 0;
			int mMonth = 0;
			int mDays = 0;
			int hours = 0;
			int minutes = 0;
			int seconds = 0;
			time_t mTime; tm* lpTime = NULL;
			mTime = this->RankingChar[up].Is_ResetTime;
			lpTime = localtime(&mTime);
			if (lpTime)
			{
				mYear = 1952 + lpTime->tm_year;	mMonth = 1 + lpTime->tm_mon; mDays = lpTime->tm_mday; hours = lpTime->tm_hour; minutes = lpTime->tm_min; seconds = lpTime->tm_sec;
			}

			if (i >= 0 && i <= 2)
			{
				Color = eGold;
			}
			else
			{
				Color = eWhite;
			}
#if MAXTOP <= 40
			if (this->RankingChar[up].Is_ConnectStat == 1)
			{
				RenderBitmap(0x17922, StartX + 160, StartY + gFixSolution.DotStatus + (i * 13), 4, 6, 0.0, 0.0, 0.878, 0.225, 1, 1, 0.0);
			}
			else
			{
				RenderBitmap(0x17922, StartX + 160, StartY + gFixSolution.DotStatus + (i * 13), 4, 6, 0.0, 0.2255f, 0.878, 0.225, 1, 1, 0.0);
			}
#endif

			if (this->Count[0] >= this->ListMaxPer[0]) break;
			float PosY = StartY + (this->Count[0] * 1);

			gInterface.DrawFormat(Color, StartX + 105, PosY + 75 + (this->Count[0] * MAX_LINE), 100, 3, "%02d", up + 1);
			gInterface.DrawFormat(Color, StartX + 135, PosY + 75 + (this->Count[0] * MAX_LINE), 100, 3, NameID);
			gInterface.DrawFormat(Color, StartX + 185, PosY + 75 + (this->Count[0] * MAX_LINE), 100, 3, CharacterCode(this->RankingChar[up].Is_Class));
			gInterface.DrawFormat(Color, StartX + 230, PosY + 75 + (this->Count[0] * MAX_LINE), 100, 3, "%d/%d/%d", this->RankingChar[up].Is_cLevel, this->RankingChar[up].Is_ResetCount, this->RankingChar[up].Is_MasterResetCount);
			gInterface.DrawFormat(Color, StartX + 270, PosY + 75 + (this->Count[0] * MAX_LINE), 100, 3, "%s", gToolKit.QNumberFormat(this->RankingChar[up].Is_TotalPoint));
			gInterface.DrawFormat(Color, StartX + 325, PosY + 75 + (this->Count[0] * MAX_LINE), 100, 3, NameSub);
			gInterface.DrawFormat(Color, StartX + 385, PosY + 75 + (this->Count[0] * MAX_LINE), 100, 3, "%02d:%02d:%02d [%02d/%02d]", hours, minutes, seconds, mDays, mMonth);

			if (pCheckMouseOver(StartX + 151, PosY + 75 + (this->Count[0] * MAX_LINE), (310), 13) == 1 && !ViewCharItems.getState())
			{
				if (strcmp(ClassName, "TAS") == 0)
				{
					CustomFont.Draw((HFONT)pFontBold, StartX + 147, PosY + 75 + (this->Count[0] * MAX_LINE), 0xFFFFFFFF, 0x00FBFF69, 320, 0, 3, " ");
#if MAXTOP <= 40
					RenderBitmap(0x1791F, StartX + 468, StartY - 0.5f, 212, 600, 0, 0, 1, 1, 1, 1, 0.0);
					CustomFont.Draw((HFONT)pFontBold, StartX + 479, (StartY - PosY_Add) + 90, 0xFFFFFFFF, 0x00FBFF69, 100, 0, 3, NameID);
					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 100, 107, 1, "Chủng tộc: %s", CharacterCode(this->RankingChar[up].Is_Class));
					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 110, 100, 1, "Level: %d / Reset: %d / Relife: %d", this->RankingChar[up].Is_cLevel, this->RankingChar[up].Is_ResetCount, this->RankingChar[up].Is_MasterResetCount);
					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 120, 100, 1, "Sưc mạnh: %s", gToolKit.QNumberFormat(this->RankingChar[up].Is_Strength));
					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 130, 100, 1, "Sức đỡ: %s", gToolKit.QNumberFormat(this->RankingChar[up].Is_Dexterity));
					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 140, 100, 1, "Thể lực: %s", gToolKit.QNumberFormat(this->RankingChar[up].Is_Vitality));
					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 150, 100, 1, "Năng lượng: %s", gToolKit.QNumberFormat(this->RankingChar[up].Is_Energy));
					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 160, 100, 1, "Mệnh lệnh: %s", gToolKit.QNumberFormat(this->RankingChar[up].Is_Leadership));
					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 170, 100, 1, "Lực Chiến: %s", gToolKit.QNumberFormat(this->RankingChar[up].Is_LucChien));

					this->GetBarInfo(StartX + 508, (StartY - PosY_Add) + 182, this->RankingChar[up].Is_Life, this->RankingChar[up].Is_MaxLife, 0xFF000069, "Life:");
					this->GetBarInfo(StartX + 508, (StartY - PosY_Add) + 197, this->RankingChar[up].Is_Mana, this->RankingChar[up].Is_MaxMana, 0x0026FF69, "Mana:");
					this->GetBarInfo(StartX + 508, (StartY - PosY_Add) + 212, this->RankingChar[up].Is_BP, this->RankingChar[up].Is_MaxBP, 0x8438FF69, "Stamina:");
					this->GetBarInfo(StartX + 508, (StartY - PosY_Add) + 227, this->RankingChar[up].Is_Shield, this->RankingChar[up].Is_MaxShield, 0xFFFF0069, "Giáp SD:");

					CustomFont.Draw((HFONT)pFontBold, StartX + 479, (StartY - PosY_Add) + 242, 0xFFFFFFFF, 0x00FBFF69, 100, 0, 3, "THÀNH TÍCH");

					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 252, 100, 1, "Giết địch: %s / %s (Tổng Kill: %s)", gToolKit.QNumberFormat(this->RankingChar[up].Is_Kills), gToolKit.QNumberFormat(this->RankingChar[up].Is_Deads), gToolKit.QNumberFormat(this->RankingChar[up].Is_PkCount));
					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 262, 100, 1, "Điểm Blood: %s", gToolKit.QNumberFormat(this->RankingChar[up].Is_BC));
					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 272, 100, 1, "Điểm Chaos: %s", gToolKit.QNumberFormat(this->RankingChar[up].Is_CC));
					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 282, 100, 1, "Điểm Devil: %s", gToolKit.QNumberFormat(this->RankingChar[up].Is_DS));
					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 292, 100, 1, "Duel: Thắng %s / Thua %s", gToolKit.QNumberFormat(this->RankingChar[up].Is_Win), gToolKit.QNumberFormat(this->RankingChar[up].Is_Lose));
					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 302, 100, 1, "Đã giết được %s con Boss!", gToolKit.QNumberFormat(this->RankingChar[up].Is_Kboss));

					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 312, 100, 1, "Tài sản WC: %s ", gToolKit.QNumberFormat(this->RankingChar[up].Is_WcoinC));
					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 322, 100, 1, "Số dư Atm: %s ", gToolKit.QNumberFormat(this->RankingChar[up].Is_CoinAtm));

					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 332, 100, 1, "Đã chơi được: %s tiếng", gToolKit.QNumberFormat(this->RankingChar[up].Is_OnlineHours));
					char ReversedDateTime[24];
					sprintf(ReversedDateTime, "%c%c-%c%c-%c%c%c%c %c%c:%c%c:%c%c",
						OnMyDate[8], OnMyDate[9],
						OnMyDate[5], OnMyDate[6],
						OnMyDate[0], OnMyDate[1], OnMyDate[2], OnMyDate[3],
						OnMyDate[11], OnMyDate[12],
						OnMyDate[14], OnMyDate[15],
						OnMyDate[17], OnMyDate[18]);
					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 342, 100, 1, "Tham chiến: %s", ReversedDateTime);
					gInterface.DrawFormat(eWhite, StartX + 479, (StartY - PosY_Add) + 352, 100, 1, "Last IP: %s", LastIP);

					CustomFont.Draw((HFONT)pFontBold, StartX + 479, (StartY - PosY_Add) + 362, 0xFFFFFFFF, 0x00FBFF69, 100, 0, 3, "GUILD");

					GetInfoCharTop(this->RankingChar[up].Name);
					if (gRanking.CacheDataUserTop.GuildName[0] != 0xFFFFFFFF && strlen(gRanking.CacheDataUserTop.GuildName) > 1)
					{
						BCreateGuildMark(gRanking.CacheDataUserTop.GuildMark, 1);
						RenderBitmap(31740, StartX + 514, (StartY - PosY_Add) + 384, 26, 26, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
					}
#endif
					if (pIsKeyPress(VK_LBUTTON) && GetTickCount() > gInterface.Data[TAS_Ranking_Main].EventTick + 100)
					{
						GetInfoCharTop(this->RankingChar[up].Name);
						gInterface.Data[TAS_Ranking_Main].EventTick = GetTickCount();
					}
				}
				else
				{
					CustomFont.Draw((HFONT)pFontBold, StartX + 147, PosY + 75 + (this->Count[0] * MAX_LINE), 0xFFFFFFFF, 0x00FBFF69, 320, 0, 3, " ");
					if (pIsKeyPress(VK_LBUTTON) && GetTickCount() > gInterface.Data[TAS_Ranking_Main].EventTick + 300)
					{
						GetInfoCharTop(this->RankingChar[up].Name);
						gInterface.Data[TAS_Ranking_Main].EventTick = GetTickCount();
					}
				}
			}
#if MAXTOP <= 100
			if (!gRanking.CacheUserRank)
			{
				GetInfoCharTop(NameID);
			}
#endif
			ViewCharItems.DrawCharInfo();
			this->Count[0]++;
		}

		if (pCheckMouseOver(StartX + 147, StartY + 338, (317), 13) == 1)
		{
			CustomFont.Draw((HFONT)pFontBold, StartX + 147, StartY + 338, 0xFFFFFFFF, 0x00FBFF69, 320, 12, 3, " ");
		}
		else
		{
			CustomFont.Draw((HFONT)pFontBold, StartX + 147, StartY + 338, 0xFFFFFFFF, 0xFF222299, 320, 12, 3, " ");
		}
		gInterface.DrawFormat(eRed, StartX + 125, StartY + 326, 100, 3, "Thứ hạng của bạn:");
		if (playerRank != -1)
		{
			gInterface.DrawFormat(eWhite, StartX + 105, StartY + 339, 100, 3, "%02d", playerRank);
			gInterface.DrawFormat(eWhite, StartX + 135, StartY + 339, 100, 3, gObjUser.lpPlayer->Name);
			gInterface.DrawFormat(eWhite, StartX + 185, StartY + 339, 100, 3, CharacterCode(playerClass));
			gInterface.DrawFormat(eWhite, StartX + 230, StartY + 339, 100, 3, playerScore);
			gInterface.DrawFormat(eWhite, StartX + 270, StartY + 339, 100, 3, playerPoint);
			gInterface.DrawFormat(eWhite, StartX + 325, StartY + 339, 100, 3, playerMap);
			gInterface.DrawFormat(eWhite, StartX + 385, StartY + 339, 100, 3, playerTime);
		}
		break;

	case 2:
		gInterface.DrawFormat(eWhite, StartX + 105, StartY + 62, 100, 3, "TOP");
		gInterface.DrawFormat(eWhite, StartX + 130, StartY + 62, 100, 3, "Tên");
		gInterface.DrawFormat(eWhite, StartX + 175, StartY + 62, 100, 3, "WC");
		gInterface.DrawFormat(eWhite, StartX + 225, StartY + 62, 100, 3, "WP");
		gInterface.DrawFormat(eWhite, StartX + 275, StartY + 62, 100, 3, "WG");
		gInterface.DrawFormat(eWhite, StartX + 325, StartY + 62, 100, 3, "WR");
		gInterface.DrawFormat(eWhite, StartX + 375, StartY + 62, 100, 3, "ATM");

		this->ListMaxPer[1] = 20;
		this->DataList[1] = iMaxCount;
		if (ListScrollBarCase2 == NULL)
		{
			ListScrollBarCase2 = new CNewUIScrollBar();
			ListScrollBarCase2->Create(JCResto+PosXInvetoryImg + 210, PosYInvetoryImg + 40, 270);
			if (ListScrollBarCase2)
			{
				ListScrollBarCase2->SetMaxPos((this->DataList[1] <= this->ListMaxPer[1]) ? 0 : (this->DataList[1] - this->ListMaxPer[1]));
				ListScrollBarCase2->SetPos(JCResto+PosXInvetoryImg + 210, PosYInvetoryImg + 40);
			}
		}
		if (ListScrollBarCase2)
		{
			if (UpdateMaxPosCase2)
			{
				ListScrollBarCase2->SetMaxPos((this->DataList[1] <= this->ListMaxPer[1]) ? 0 : (this->DataList[1] / this->ListMaxPer[1]));
				UpdateMaxPosCase2 = false;
			}

			ListScrollBarCase2->MouseWheelWindow = pCheckMouseOver(JCResto+PosXInvetoryImg - 113, PosYInvetoryImg + 40, 330, 270);
			ListScrollBarCase2->Render();
			ListScrollBarCase2->UpdateMouseEvent();
			ListScrollBarCase2->Update();
		}
		this->ListPage[1] = ListScrollBarCase2->GetCurPos();
		this->Count[1] = 0;
		this->CurPos[1] = ListScrollBarCase2->GetCurPos();

		for (int i = this->CurPos[1]; i < iMaxCount; i++)
		{
			DWORD Color;
			char NameID[11];
			int up = i + ((this->Page - 1) * iMaxCount);
			if (this->RankingCharTP[up].Name[0] == NULL) continue;
			memcpy(NameID, this->RankingCharTP[up].Name, sizeof(this->RankingCharTP[up].Name));
			NameID[sizeof(NameID) - 1] = '\0';

			if (this->Count[1] >= this->ListMaxPer[1]) break;
			float PosY = StartY + (this->Count[1] * 1);

			if (i >= 0 && i <= 2) { Color = eGold; }
			else { Color = eWhite; }

			gInterface.DrawFormat(Color, StartX + 105, PosY + 75 + (this->Count[1] * MAX_LINE), 100, 3, "%02d", up + 1);
			gInterface.DrawFormat(Color, StartX + 130, PosY + 75 + (this->Count[1] * MAX_LINE), 100, 3, NameID);
			gInterface.DrawFormat(Color, StartX + 175, PosY + 75 + (this->Count[1] * MAX_LINE), 100, 3, "%s", gToolKit.QNumberFormat(this->RankingCharTP[up].Is_WcoinC));
			gInterface.DrawFormat(Color, StartX + 225, PosY + 75 + (this->Count[1] * MAX_LINE), 100, 3, "%s", gToolKit.QNumberFormat(this->RankingCharTP[up].Is_WcoinP));
			gInterface.DrawFormat(Color, StartX + 275, PosY + 75 + (this->Count[1] * MAX_LINE), 100, 3, "%s", gToolKit.QNumberFormat(this->RankingCharTP[up].Is_WcoinG));
			gInterface.DrawFormat(Color, StartX + 325, PosY + 75 + (this->Count[1] * MAX_LINE), 100, 3, "%s", gToolKit.QNumberFormat(this->RankingCharTP[up].Is_WcoinR));
			gInterface.DrawFormat(Color, StartX + 375, PosY + 75 + (this->Count[1] * MAX_LINE), 100, 3, "%s", gToolKit.QNumberFormat(this->RankingCharTP[up].Is_CoinAtm));

			if (pCheckMouseOver(StartX + 151, PosY + 75 + (this->Count[1] * MAX_LINE), (310), 13) == 1)
			{
				CustomFont.Draw((HFONT)pFontBold, StartX + 150, PosY + 75 + (this->Count[1] * MAX_LINE), 0xFFFFFFFF, 0x00FBFF69, 310, 0, 3, " ");
				if (pIsKeyPress(VK_LBUTTON) && GetTickCount() > gInterface.Data[TAS_Ranking_Main].EventTick + 100)
				{
					GetInfoCharTop(this->RankingCharTP[up].Name);
					gInterface.Data[TAS_Ranking_Main].EventTick = GetTickCount();
				}
			}
			ViewCharItems.DrawCharInfo();
			this->Count[1]++;
		}
		break;

	case 3:
		gInterface.DrawFormat(eWhite, StartX + 105, StartY + 62, 100, 3, "TOP");
		gInterface.DrawFormat(eWhite, StartX + 130, StartY + 62, 100, 3, "Tên");
		gInterface.DrawFormat(eWhite, StartX + 175, StartY + 62, 100, 3, "BLOOD CS");
		gInterface.DrawFormat(eWhite, StartX + 225, StartY + 62, 100, 3, "CHAOS CS");
		gInterface.DrawFormat(eWhite, StartX + 275, StartY + 62, 100, 3, "DEVIL CS");
		gInterface.DrawFormat(eWhite, StartX + 325, StartY + 62, 100, 3, "I-TEMPLE");
		gInterface.DrawFormat(eWhite, StartX + 375, StartY + 62, 100, 3, "KING PLAYER");

		this->ListMaxPer[2] = 20;
		this->DataList[2] = iMaxCount;
		if (ListScrollBarCase3 == NULL)
		{
			ListScrollBarCase3 = new CNewUIScrollBar();
			ListScrollBarCase3->Create(PosXInvetoryImg + 210, PosYInvetoryImg + 40, 270);
			if (ListScrollBarCase3)
			{
				ListScrollBarCase3->SetMaxPos((this->DataList[2] <= this->ListMaxPer[2]) ? 0 : (this->DataList[2] - this->ListMaxPer[2]));
				ListScrollBarCase3->SetPos(PosXInvetoryImg + 210, PosYInvetoryImg + 40);
			}
		}
		if (ListScrollBarCase3)
		{
			if (UpdateMaxPosCase3)
			{
				ListScrollBarCase3->SetMaxPos((this->DataList[2] <= this->ListMaxPer[2]) ? 0 : (this->DataList[2] / this->ListMaxPer[2]));
				UpdateMaxPosCase3 = false;
			}

			ListScrollBarCase3->MouseWheelWindow = pCheckMouseOver(PosXInvetoryImg - 113, PosYInvetoryImg + 40, 330, 270);
			ListScrollBarCase3->Render();
			ListScrollBarCase3->UpdateMouseEvent();
			ListScrollBarCase3->Update();
		}
		this->ListPage[2] = ListScrollBarCase3->GetCurPos();
		this->Count[2] = 0;
		this->CurPos[2] = ListScrollBarCase3->GetCurPos();

		for (int i = this->CurPos[2]; i < iMaxCount; i++)
		{
			DWORD Color;
			char NameID[11];
			int up = i + ((this->Page - 1) * iMaxCount);
			if (this->RankingCharET[up].Name[0] == NULL) continue;
			memcpy(NameID, this->RankingCharET[up].Name, sizeof(this->RankingCharET[up].Name));
			NameID[sizeof(NameID) - 1] = '\0';

			if (this->Count[2] >= this->ListMaxPer[2]) break;
			float PosY = StartY + (this->Count[2] * 1);

			if (i >= 0 && i <= 2) { Color = eGold; }
			else { Color = eWhite; }

			gInterface.DrawFormat(Color, StartX + 105, PosY + 75 + (this->Count[2] * MAX_LINE), 100, 3, "%02d", up + 1);
			gInterface.DrawFormat(Color, StartX + 130, PosY + 75 + (this->Count[2] * MAX_LINE), 100, 3, NameID);
			gInterface.DrawFormat(Color, StartX + 175, PosY + 75 + (this->Count[2] * MAX_LINE), 100, 3, "%s", gToolKit.QNumberFormat(this->RankingCharET[up].Is_BloodCS));
			gInterface.DrawFormat(Color, StartX + 225, PosY + 75 + (this->Count[2] * MAX_LINE), 100, 3, "%s", gToolKit.QNumberFormat(this->RankingCharET[up].Is_ChaosCS));
			gInterface.DrawFormat(Color, StartX + 275, PosY + 75 + (this->Count[2] * MAX_LINE), 100, 3, "%s", gToolKit.QNumberFormat(this->RankingCharET[up].Is_DevilCS));
			gInterface.DrawFormat(Color, StartX + 325, PosY + 75 + (this->Count[2] * MAX_LINE), 100, 3, "0");
			gInterface.DrawFormat(Color, StartX + 375, PosY + 75 + (this->Count[2] * MAX_LINE), 100, 3, "0");

			if (pCheckMouseOver(StartX + 151, PosY + 75 + (this->Count[2] * MAX_LINE), (310), 13) == 1)
			{
				CustomFont.Draw((HFONT)pFontBold, StartX + 147, PosY + 75 + (this->Count[2] * MAX_LINE), 0xFFFFFFFF, 0x00FBFF69, 317, 0, 3, " ");
				if (pIsKeyPress(VK_LBUTTON) && GetTickCount() > gInterface.Data[TAS_Ranking_Main].EventTick + 100)
				{
					GetInfoCharTop(this->RankingCharET[up].Name);
					gInterface.Data[TAS_Ranking_Main].EventTick = GetTickCount();
				}
			}
			ViewCharItems.DrawCharInfo();
			this->Count[2]++;
		}
		break;

	case 4:
		gInterface.DrawFormat(eWhite, StartX + 105, StartY + 62, 100, 3, "TOP");
		gInterface.DrawFormat(eWhite, StartX + 130, StartY + 62, 100, 3, "GUILD");
		gInterface.DrawFormat(eWhite, StartX + 175, StartY + 62, 100, 3, "CẤP ĐỘ");
		gInterface.DrawFormat(eWhite, StartX + 225, StartY + 62, 100, 3, "CHỦ GUILD");
		gInterface.DrawFormat(eWhite, StartX + 275, StartY + 62, 100, 3, "ĐIỂM GUILD");
		gInterface.DrawFormat(eWhite, StartX + 325, StartY + 62, 100, 3, "THÀNH VIÊN");
		gInterface.DrawFormat(eWhite, StartX + 375, StartY + 62, 100, 3, "NGÀY TẠO");

		this->ListMaxPer[3] = 20;
		this->DataList[3] = iMaxCount;
		if (ListScrollBarCase4 == NULL)
		{
			ListScrollBarCase4 = new CNewUIScrollBar();
			ListScrollBarCase4->Create(PosXInvetoryImg + 210, PosYInvetoryImg + 40, 270);
			if (ListScrollBarCase4)
			{
				ListScrollBarCase4->SetMaxPos((this->DataList[3] <= this->ListMaxPer[3]) ? 0 : (this->DataList[3] - this->ListMaxPer[3]));
				ListScrollBarCase4->SetPos(PosXInvetoryImg + 210, PosYInvetoryImg + 40);
			}
		}
		if (ListScrollBarCase4)
		{
			if (UpdateMaxPosCase4)
			{
				ListScrollBarCase4->SetMaxPos((this->DataList[3] <= this->ListMaxPer[3]) ? 0 : (this->DataList[3] / this->ListMaxPer[3]));
				UpdateMaxPosCase4 = false;
			}

			ListScrollBarCase4->MouseWheelWindow = pCheckMouseOver(PosXInvetoryImg - 113, PosYInvetoryImg + 40, 330, 270);
			ListScrollBarCase4->Render();
			ListScrollBarCase4->UpdateMouseEvent();
			ListScrollBarCase4->Update();
		}
		this->ListPage[3] = ListScrollBarCase4->GetCurPos();
		this->Count[3] = 0;
		this->CurPos[3] = ListScrollBarCase4->GetCurPos();

		for (int i = this->CurPos[3]; i < iMaxCount; i++)
		{
			DWORD Color;
			char G_Name[9];
			char G_Master[11];
			char OnMyDate[30];
			int up = i + ((this->Page - 1) * iMaxCount);

			if (this->RankingCharTG[up].G_Master[0] == NULL) continue;

			memcpy(G_Master, this->RankingCharTG[up].G_Master, sizeof(this->RankingCharTG[up].G_Master));
			memcpy(G_Name, this->RankingCharTG[up].G_Name, sizeof(this->RankingCharTG[up].G_Name));
			memcpy(OnMyDate, this->RankingCharTG[up].Is_JoinDate, sizeof(this->RankingCharTG[up].Is_JoinDate));

			if (this->Count[3] >= this->ListMaxPer[3]) break;
			float PosY = StartY + (this->Count[3] * 1);

			if (i >= 0 && i <= 2) { Color = eGold; }
			else { Color = eWhite; }

			char ReversedDateTime[20];
			sprintf(ReversedDateTime, "%c%c:%c%c:%c%c %c%c-%c%c",
				OnMyDate[11], OnMyDate[12],
				OnMyDate[14], OnMyDate[15],
				OnMyDate[17], OnMyDate[18],
				OnMyDate[8], OnMyDate[9],
				OnMyDate[5], OnMyDate[6]);

			gInterface.DrawFormat(Color, StartX + 105, PosY + 75 + (this->Count[3] * MAX_LINE), 100, 3, "%02d", up + 1);
			gInterface.DrawFormat(Color, StartX + 130, PosY + 75 + (this->Count[3] * MAX_LINE), 100, 3, G_Name);
			gInterface.DrawFormat(Color, StartX + 175, PosY + 75 + (this->Count[3] * MAX_LINE), 100, 3, "%s", gToolKit.QNumberFormat(this->RankingCharTG[up].Is_GLevel));
			gInterface.DrawFormat(Color, StartX + 225, PosY + 75 + (this->Count[3] * MAX_LINE), 100, 3, G_Master);
			gInterface.DrawFormat(Color, StartX + 275, PosY + 75 + (this->Count[3] * MAX_LINE), 100, 3, "%s", gToolKit.QNumberFormat(this->RankingCharTG[up].Is_GScore));
			gInterface.DrawFormat(Color, StartX + 325, PosY + 75 + (this->Count[3] * MAX_LINE), 100, 3, "%s", gToolKit.QNumberFormat(this->RankingCharTG[up].Is_GMem));
			gInterface.DrawFormat(Color, StartX + 375, PosY + 75 + (this->Count[3] * MAX_LINE), 100, 3, ReversedDateTime);

			if (pCheckMouseOver(StartX + 151, PosY + 75 + (this->Count[3] * MAX_LINE), (310), 13) == 1)
			{
				CustomFont.Draw((HFONT)pFontBold, StartX + 147, PosY + 75 + (this->Count[3] * MAX_LINE), 0xFFFFFFFF, 0x00FBFF69, 317, 0, 3, " ");
				GetInfoCharTop(this->RankingCharTG[up].G_Master);
				if (gRanking.CacheDataUserTop.GuildName[0] != 0xFFFFFFFF && strlen(gRanking.CacheDataUserTop.GuildName) > 1)
				{
					BCreateGuildMark(gRanking.CacheDataUserTop.GuildMark, 1);
					RenderBitmap(31740, pCursorX + 20, pCursorY, 26, 26, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
				}
				if (pIsKeyPress(VK_LBUTTON) && GetTickCount() > gInterface.Data[TAS_Ranking_Main].EventTick + 100)
				{
					GetInfoCharTop(this->RankingCharTG[up].G_Master);
					gInterface.Data[TAS_Ranking_Main].EventTick = GetTickCount();
				}
			}
			if (!gRanking.CacheUserRank)
			{
				GetInfoCharTop(G_Master);
			}
			ViewCharItems.DrawCharInfo();
			this->Count[3]++;
		}

		break;
	case 5:
		gInterface.DrawFormat(eWhite, StartX + 105, StartY + 62, 100, 3, "TOP");
		gInterface.DrawFormat(eWhite, StartX + 130, StartY + 62, 100, 3, "NAME");
		gInterface.DrawFormat(eWhite, StartX + 175, StartY + 62, 100, 3, "Số Kill BOSS");
		gInterface.DrawFormat(eWhite, StartX + 225, StartY + 62, 100, 3, "KILL/DEAD");
		gInterface.DrawFormat(eWhite, StartX + 275, StartY + 62, 100, 3, "DUEL W/L");
		gInterface.DrawFormat(eWhite, StartX + 325, StartY + 62, 100, 3, "ĐÃ CHƠI");
		gInterface.DrawFormat(eWhite, StartX + 375, StartY + 62, 100, 3, "NGÀY TẠO");

		this->ListMaxPer[4] = 20;
		this->DataList[4] = iMaxCount;
		if (ListScrollBarCase5 == NULL)
		{
			ListScrollBarCase5 = new CNewUIScrollBar();
			ListScrollBarCase5->Create(PosXInvetoryImg + 210, PosYInvetoryImg + 40, 270);
			if (ListScrollBarCase5)
			{
				ListScrollBarCase5->SetMaxPos((this->DataList[4] <= this->ListMaxPer[4]) ? 0 : (this->DataList[4] - this->ListMaxPer[4]));
				ListScrollBarCase5->SetPos(PosXInvetoryImg + 210, PosYInvetoryImg + 40);
			}
		}
		if (ListScrollBarCase5)
		{
			if (UpdateMaxPosCase5)
			{
				ListScrollBarCase5->SetMaxPos((this->DataList[4] <= this->ListMaxPer[4]) ? 0 : (this->DataList[4] / this->ListMaxPer[4]));
				UpdateMaxPosCase5 = false;
			}

			ListScrollBarCase5->MouseWheelWindow = pCheckMouseOver(PosXInvetoryImg - 113, PosYInvetoryImg + 40, 330, 270);
			ListScrollBarCase5->Render();
			ListScrollBarCase5->UpdateMouseEvent();
			ListScrollBarCase5->Update();
		}
		this->ListPage[4] = ListScrollBarCase5->GetCurPos();
		this->Count[4] = 0;
		this->CurPos[4] = ListScrollBarCase5->GetCurPos();

		for (int i = this->CurPos[4]; i < iMaxCount; i++)
		{
			DWORD Color;
			char NameID[11];
			char OnMyDate[30];
			int up = i + ((this->Page - 1) * iMaxCount);
			if (this->RankingCharPK[up].Name[0] == NULL) continue;

			memcpy(NameID, this->RankingCharPK[up].Name, sizeof(this->RankingCharPK[up].Name));
			memcpy(OnMyDate, this->RankingCharPK[up].Is_JoinDate, sizeof(this->RankingCharPK[up].Is_JoinDate));

			if (this->Count[4] >= this->ListMaxPer[4]) break;
			float PosY = StartY + (this->Count[4] * 1);

			if (i >= 0 && i <= 2) { Color = eGold; }
			else { Color = eWhite; }

			char ReversedDateTime[20];
			sprintf(ReversedDateTime, "%c%c:%c%c:%c%c %c%c-%c%c",
				OnMyDate[11], OnMyDate[12],
				OnMyDate[14], OnMyDate[15],
				OnMyDate[17], OnMyDate[18],
				OnMyDate[8], OnMyDate[9],
				OnMyDate[5], OnMyDate[6]);

			gInterface.DrawFormat(Color, StartX + 105, PosY + 75 + (this->Count[4] * MAX_LINE), 100, 3, "%02d", up + 1);
			gInterface.DrawFormat(Color, StartX + 130, PosY + 75 + (this->Count[4] * MAX_LINE), 100, 3, NameID);
			gInterface.DrawFormat(Color, StartX + 175, PosY + 75 + (this->Count[4] * MAX_LINE), 100, 3, "%s", gToolKit.QNumberFormat(this->RankingCharPK[up].Is_Kboss));
			gInterface.DrawFormat(Color, StartX + 225, PosY + 75 + (this->Count[4] * MAX_LINE), 100, 3, "%s / %s", gToolKit.QNumberFormat(this->RankingCharPK[up].Is_Kills), gToolKit.QNumberFormat(this->RankingCharPK[up].Is_Deads));
			gInterface.DrawFormat(Color, StartX + 275, PosY + 75 + (this->Count[4] * MAX_LINE), 100, 3, "%s / %s", gToolKit.QNumberFormat(this->RankingCharPK[up].Is_Win), gToolKit.QNumberFormat(this->RankingCharPK[up].Is_Lose));
			gInterface.DrawFormat(Color, StartX + 325, PosY + 75 + (this->Count[4] * MAX_LINE), 100, 3, "%s tiếng", gToolKit.QNumberFormat(this->RankingCharPK[up].Is_OnlineHours));
			gInterface.DrawFormat(Color, StartX + 375, PosY + 75 + (this->Count[4] * MAX_LINE), 100, 3, "%s", ReversedDateTime);

			if (pCheckMouseOver(StartX + 151, PosY + 75 + (this->Count[4] * MAX_LINE), (310), 13) == 1)
			{
				CustomFont.Draw((HFONT)pFontBold, StartX + 147, PosY + 75 + (this->Count[4] * MAX_LINE), 0xFFFFFFFF, 0x00FBFF69, 317, 0, 3, " ");
				if (pIsKeyPress(VK_LBUTTON) && GetTickCount() > gInterface.Data[TAS_Ranking_Main].EventTick + 100)
				{
					GetInfoCharTop(this->RankingCharPK[up].Name);
					gInterface.Data[TAS_Ranking_Main].EventTick = GetTickCount();
				}
			}
			ViewCharItems.DrawCharInfo();
			this->Count[4]++;
		}
		break;

	case 6:
		gInterface.DrawFormat(eWhite, StartX + 105, StartY + 62, 100, 3, "TOP");
		gInterface.DrawFormat(eWhite, StartX + 130, StartY + 62, 100, 3, "NAME");
		gInterface.DrawFormat(eWhite, StartX + 175, StartY + 62, 100, 3, "LEVEL");
		gInterface.DrawFormat(eWhite, StartX + 225, StartY + 62, 100, 3, "POINT");
		gInterface.DrawFormat(eWhite, StartX + 275, StartY + 62, 100, 3, "EXP");

		this->ListMaxPer[5] = 20;
		this->DataList[5] = iMaxCount;
		if (ListScrollBarCase6 == NULL)
		{
			ListScrollBarCase6 = new CNewUIScrollBar();
			ListScrollBarCase6->Create(PosXInvetoryImg + 210, PosYInvetoryImg + 40, 270);
			if (ListScrollBarCase6)
			{
				ListScrollBarCase6->SetMaxPos((this->DataList[5] <= this->ListMaxPer[5]) ? 0 : (this->DataList[5] - this->ListMaxPer[5]));
				ListScrollBarCase6->SetPos(PosXInvetoryImg + 210, PosYInvetoryImg + 40);
			}
		}
		if (ListScrollBarCase6)
		{
			if (UpdateMaxPosCase6)
			{
				ListScrollBarCase6->SetMaxPos((this->DataList[5] <= this->ListMaxPer[5]) ? 0 : (this->DataList[5] / this->ListMaxPer[5]));
				UpdateMaxPosCase6 = false;
			}

			ListScrollBarCase6->MouseWheelWindow = pCheckMouseOver(PosXInvetoryImg - 113, PosYInvetoryImg + 40, 330, 270);
			ListScrollBarCase6->Render();
			ListScrollBarCase6->UpdateMouseEvent();
			ListScrollBarCase6->Update();
		}
		this->ListPage[5] = ListScrollBarCase6->GetCurPos();
		this->Count[5] = 0;
		this->CurPos[5] = ListScrollBarCase6->GetCurPos();

		for (int i = this->CurPos[5]; i < iMaxCount; i++)
		{
			DWORD Color;
			char NameID[11];
			int up = i + ((this->Page - 1) * iMaxCount);
			if (this->RankingCharMT[up].Name[0] == NULL) continue;

			memcpy(NameID, this->RankingCharMT[up].Name, sizeof(this->RankingCharMT[up].Name));

			if (this->Count[5] >= this->ListMaxPer[5]) break;
			float PosY = StartY + (this->Count[5] * 1);

			if (i >= 0 && i <= 2) { Color = eGold; }
			else { Color = eWhite; }

			gInterface.DrawFormat(Color, StartX + 105, PosY + 75 + (this->Count[5] * MAX_LINE), 100, 3, "%02d", up + 1);
			gInterface.DrawFormat(Color, StartX + 130, PosY + 75 + (this->Count[5] * MAX_LINE), 100, 3, NameID);
			gInterface.DrawFormat(Color, StartX + 175, PosY + 75 + (this->Count[5] * MAX_LINE), 100, 3, "%d", this->RankingCharMT[up].cLevel);
			gInterface.DrawFormat(Color, StartX + 225, PosY + 75 + (this->Count[5] * MAX_LINE), 100, 3, "%d", this->RankingCharMT[up].cPoint);
			gInterface.DrawFormat(Color, StartX + 275, PosY + 75 + (this->Count[5] * MAX_LINE), 100, 3, "%s", gToolKit.QNumberFormat(this->RankingCharMT[up].cExp));

			if (pCheckMouseOver(StartX + 151, PosY + 75 + (this->Count[5] * MAX_LINE), (310), 13) == 1)
			{
				CustomFont.Draw((HFONT)pFontBold, StartX + 147, PosY + 75 + (this->Count[5] * MAX_LINE), 0xFFFFFFFF, 0x00FBFF69, 317, 0, 3, " ");
				if (pIsKeyPress(VK_LBUTTON) && GetTickCount() > gInterface.Data[TAS_Ranking_Main].EventTick + 100)
				{
					GetInfoCharTop(this->RankingCharMT[up].Name);
					gInterface.Data[TAS_Ranking_Main].EventTick = GetTickCount();
				}
			}
			ViewCharItems.DrawCharInfo();
			this->Count[5]++;
		}
		break;
	default:
		break;
	}
}
void cRanking::GetBarInfo(int x, int y, int Value1, int Value2, DWORD BackColor, LPCSTR Char, ...)
{
	int CurentLife = Value1;
	float TyleLife = (70 * CurentLife) / Value2;

	if (TyleLife > 70)
	{
		TyleLife = 70;
	}
	CustomFont.Draw(CustomFont.FontBold, x, y, 0xFFFFFFFF, BackColor, TyleLife, 13, 3, " ");
	gInterface.DrawFormat(eWhite, x - 29, y + 2, 100, 1, Char);
	gInterface.DrawFormat(eWhite, x - 14, y + 1, 100, 3, "%s / %s", gToolKit.QNumberFormat(Value1), gToolKit.QNumberFormat(Value2));
}

