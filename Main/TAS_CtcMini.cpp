#include "stdafx.h"
#include "TAS_CtcMini.h"
#include "Interface.h"
#include "Defines.h"
#include "CustomFont.h"
#include "User.h"
#include "PrintPlayer.h"
#include "Config.h"

#if(CTCMINI)
DWORD ClickTickCount = 0;
CtcMiniClass gCtcMini;
void CGMoveCTCMini(int Type)
{
	if (Type > 0)
	{
		CTCMINI_CGPACKET pMsg;
		pMsg.header.set(0xF3, 0x39, sizeof(pMsg));
		pMsg.CongVao = Type - 1;
		DataSend((LPBYTE)&pMsg, pMsg.header.size);
	}
}

void CtcMiniClass::DrawCTCMiniWindow()
{
	if (!gInterface.Data[eCTCMiniWindow].OnShow)
	{
		return;
	}

	pSetCursorFocus = true;

	float MainWidth = 230.0;
	float CuaSoW = MainWidth;
	float StartY = 55;
	float StartYMove = 210;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (29.0 / 2);

	gInterface.DrawAnimatedGUI(CTCMINI_MAIN, StartX, StartY + 2);
	gInterface.DrawAnimatedGUI(CTCMINI_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(CTCMINI_FRAME, StartX, StartY + 67.0, 10);
	gInterface.DrawAnimatedGUI(CTCMINI_FOOTER, StartX, StartY);
	int CloseX = StartX + CuaSoW - 35;
	int CloseY = StartY - 6;
	pDrawGUI(0x7EC5, CloseX, CloseY - StartYMove, 36.0f, 29.0f);
	if (pCheckMouseOver(CloseX, CloseY - StartYMove, 36, 36) == 1)
	{
		if (GetTickCount() - ClickTickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				gInterface.Data[eCTCMiniWindow].OnShow ^= 1;
				ClickTickCount = GetTickCount();
			}
		}
		pDrawColorButton(0x7EC5, CloseX, CloseY - StartYMove, 36, 29, 0, 0, pMakeColor(255, 204, 20, 130));
		gInterface.DrawFormat(eGold, CloseX + 15, CloseY + 30 - StartYMove, 0, 1, gConfig.TTAS_TEXT_ENGINE[26]);
	}
	gInterface.DrawFormat(eGold, StartX + 10, gInterface.Data[CTCMINI_MAIN].Y + 8, 210, 3, gConfig.TTAS_TEXT_ENGINE[205]);
	gInterface.DrawFormat(eBlue, StartX + 10, gInterface.Data[CTCMINI_MAIN].Y + 30, 210, 3, gConfig.TTAS_TEXT_ENGINE[206], gObjUser.lpPlayer->Name);
	gInterface.DrawAnimatedGUI(CTCMINI_DIV, StartX, gInterface.Data[CTCMINI_MAIN].Y + 33);

	StartY = StartY + 45;
	CustomFont.Draw(CustomFont.FontNormal, StartX + (CuaSoW / 10), StartY - StartYMove, 0xFFDE26FF, 0x0, CuaSoW, 0, 1, gConfig.TTAS_TEXT_ENGINE[207]); //
	StartY = StartY + 12;
	CustomFont.Draw(CustomFont.FontNormal, StartX + (CuaSoW / 10), StartY - StartYMove, 0xFFDE26FF, 0x0, CuaSoW, 0, 1, gConfig.TTAS_TEXT_ENGINE[208]); //
	StartY = StartY + 12;
	CustomFont.Draw(CustomFont.FontNormal, StartX + (CuaSoW / 10), StartY - StartYMove, 0xFFDE26FF, 0x0, CuaSoW, 0, 1, gConfig.TTAS_TEXT_ENGINE[209]); //
	StartY = StartY + 12;
	CustomFont.Draw(CustomFont.FontBold, StartX + (CuaSoW / 10), StartY - StartYMove, 0x00FFCCFF, 0x0, CuaSoW, 0, 1, gConfig.TTAS_TEXT_ENGINE[210]); //
	StartY = StartY + 12;
	CustomFont.Draw(CustomFont.FontBold, StartX + (CuaSoW / 10), StartY - StartYMove, 0x00FF90FF, 0x0, CuaSoW, 0, 1, gConfig.TTAS_TEXT_ENGINE[211]); //
	StartY = StartY + 25;
	pDrawGUI(32583, StartX, StartY - StartYMove, 128.0f, 128.0f);

	StartY = StartY + 10;
	float SizeButtonW = 95.0;
	float SizeButtonH = 19.0;
	StartX = StartX + (CuaSoW / 2);

	if (pCheckMouseOver(StartX, StartY - StartYMove, SizeButtonW, SizeButtonH) == 1)
	{
		glColor3f(1.0f, 0.6742f, 0.15f);
		if (GetTickCount() - gInterface.Data[eCTCMiniWindow].EventTick > 300) //Click
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(0.72f, 0.438f, 0.0432f);
				CGMoveCTCMini(1);
				gInterface.Data[eCTCMiniWindow].OnShow = 0;
				gInterface.Data[eCTCMiniWindow].EventTick = GetTickCount();
			}
		}
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	RenderBitmap(31563, StartX, StartY - StartYMove, SizeButtonW, SizeButtonH, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
	CustomFont.Draw(CustomFont.FontNormal, StartX, StartY + (SizeButtonH / 4) - StartYMove, 0xE6FCF7FF, 0x0, SizeButtonW, 0, 3, gConfig.TTAS_TEXT_ENGINE[212]); //Buoc Vao
	StartY = StartY + 22;
	if (pCheckMouseOver(StartX, StartY - StartYMove, SizeButtonW, SizeButtonH) == 1)
	{
		glColor3f(1.0f, 0.6742f, 0.15f);
		if (GetTickCount() - gInterface.Data[eCTCMiniWindow].EventTick > 300) //Click
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(0.72f, 0.438f, 0.0432f);
				CGMoveCTCMini(2);
				gInterface.Data[eCTCMiniWindow].OnShow = 0;
				gInterface.Data[eCTCMiniWindow].EventTick = GetTickCount();
			}
		}
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	RenderBitmap(31563, StartX, StartY - StartYMove, SizeButtonW, SizeButtonH, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
	CustomFont.Draw(CustomFont.FontNormal, StartX, StartY + (SizeButtonH / 4) - StartYMove, 0xE6FCF7FF, 0x0, SizeButtonW, 0, 3, gConfig.TTAS_TEXT_ENGINE[213]); //Buoc Vao
	StartY = StartY + 22;
	if (pCheckMouseOver(StartX, StartY - StartYMove, SizeButtonW, SizeButtonH) == 1)
	{
		glColor3f(1.0f, 0.6742f, 0.15f);
		if (GetTickCount() - gInterface.Data[eCTCMiniWindow].EventTick > 300) //Click
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(0.72f, 0.438f, 0.0432f);
				CGMoveCTCMini(3);
				gInterface.Data[eCTCMiniWindow].OnShow = 0;
				gInterface.Data[eCTCMiniWindow].EventTick = GetTickCount();
			}
		}
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	RenderBitmap(31563, StartX, StartY - StartYMove, SizeButtonW, SizeButtonH, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
	CustomFont.Draw(CustomFont.FontNormal, StartX, StartY + (SizeButtonH / 4) - StartYMove, 0xE6FCF7FF, 0x0, SizeButtonW, 0, 3, gConfig.TTAS_TEXT_ENGINE[214]); //Buoc Vao
	StartY = StartY + 22;
	if (pCheckMouseOver(StartX, StartY - StartYMove, SizeButtonW, SizeButtonH) == 1)
	{
		glColor3f(1.0f, 0.6742f, 0.15f);
		if (GetTickCount() - gInterface.Data[eCTCMiniWindow].EventTick > 300) //Click
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(0.72f, 0.438f, 0.0432f);
				CGMoveCTCMini(4);
				gInterface.Data[eCTCMiniWindow].OnShow = 0;
				gInterface.Data[eCTCMiniWindow].EventTick = GetTickCount();
			}
		}
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
	}

	RenderBitmap(31563, StartX, StartY - StartYMove, SizeButtonW, SizeButtonH, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
	CustomFont.Draw(CustomFont.FontNormal, StartX, StartY + (SizeButtonH / 4) - StartYMove, 0xE6FCF7FF, 0x0, SizeButtonW, 0, 3, gConfig.TTAS_TEXT_ENGINE[215]); //Buoc Vao
	StartY = StartY + 22;

	if (pCheckMouseOver(StartX, StartY - StartYMove, SizeButtonW, SizeButtonH) == 1 && CheckVaoLanhDia)
	{
		glColor3f(1.0f, 0.6742f, 0.15f);
		if (GetTickCount() - gInterface.Data[eCTCMiniWindow].EventTick > 300) //Click
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(0.72f, 0.438f, 0.0432f);
				CGMoveCTCMini(5);
				gInterface.Data[eCTCMiniWindow].OnShow = 0;
				gInterface.Data[eCTCMiniWindow].EventTick = GetTickCount();
			}
		}
	}
	else if (!CheckVaoLanhDia)
	{
		glColor3f(0.42f, 0.42f, 0.42f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	RenderBitmap(31563, StartX, StartY - StartYMove, SizeButtonW, SizeButtonH, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
	CustomFont.Draw(CustomFont.FontNormal, StartX, StartY + (SizeButtonH / 4) - StartYMove, 0xE6FCF7FF, 0x0, SizeButtonW, 0, 3, gConfig.TTAS_TEXT_ENGINE[216]);
	glColor3f(1.0f, 1.0f, 1.0f);
}

void CtcMiniClass::DrawCTCMiNiMap()
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
	if (gObjUser.m_MapNumber != 98)
	{
		return;
	}
	float MainWidth = 138.0;
	float MainHeight = 265.0;
	float StartY = 264.0;
	float StartX = 512.0; //512

	pDrawGUI(32584, StartX, StartY, 128.0f, 157.0f); //UI
	pDrawGUI(32583, StartX, StartY + 28.0, 128.0f, 128.0f); //MAP

	if ((GetTickCount() - gInterface.Data[eTimeCTC].EventTick) > 1000)
	{
		if (CTCMINI_TimeCTCMini > 0)
		{
			CTCMINI_TimeCTCMini = CTCMINI_TimeCTCMini - 1;
		}
		gInterface.Data[eTimeCTC].EventTick = GetTickCount();
	}

	int hours = CTCMINI_TimeCTCMini / 3600;
	int minutes = (CTCMINI_TimeCTCMini / 60) % 60;
	int seconds = CTCMINI_TimeCTCMini % 60;
	CustomFont.Draw(CustomFont.FontBold, StartX + 10, StartY + 10, 0x16FAC1FF, 0x0, 100, 0, 3, " %02d:%02d:%02d", hours, minutes, seconds); //

	if (CTCMINI_Cong[0] == 0) 
	{
		RenderBitmap(31681, (float)(StartX - 3 + 96 / 2), (float)(294 - 5 + (255 - 130) / 2), 7.0, 7.0, 0.0, 0.0, 0.875, 0.875, 1, 1, 0.0);
	}
	if (CTCMINI_Cong[1] == 0) 
	{
		RenderBitmap(31681, (float)(StartX - 3 + 128 / 2), (float)(294 - 5 + (255 - 130) / 2), 7.0, 7.0, 0.0, 0.0, 0.875, 0.875, 1, 1, 0.0);
	}
	if (CTCMINI_Cong[2] == 0) 
	{
		RenderBitmap(31681, (float)(StartX - 2.5 + 161 / 2), (float)(294 - 5 + (255 - 130) / 2), 7.0, 7.0, 0.0, 0.0, 0.875, 0.875, 1, 1, 0.0);
	}

	if (CTCMINI_Tru[0] == 0)
	{
		RenderBitmap(31680, (float)(StartX - 4.5 + 96 / 2), (float)(294 - 6 + (255 - 165) / 2), 9.0, 8.0, 0.0, 0.0, 0.5625, 1.0, 1, 1, 0.0);
	}
	else {
		RenderBitmap(31683, (float)(StartX - 4.5 + 96 / 2), (float)(294 - 6 + (255 - 165) / 2), 9.0, 8.0, 0.0, 0.0, 0.5625, 1.0, 1, 1, 0.0);
	}
	if (CTCMINI_Tru[1] == 0) 
	{
		RenderBitmap(31680, (float)(StartX - 4.5 + 128 / 2), (float)(294 - 6 + (255 - 165) / 2), 9.0, 8.0, 0.0, 0.0, 0.5625, 1.0, 1, 1, 0.0);
	}
	else 
	{
		RenderBitmap(31683, (float)(StartX - 4.5 + 128 / 2), (float)(294 - 6 + (255 - 165) / 2), 9.0, 8.0, 0.0, 0.0, 0.5625, 1.0, 1, 1, 0.0);
	}
	if (CTCMINI_Tru[2] == 0) 
	{
		RenderBitmap(31680, (float)(StartX - 4.5 + 161 / 2), (float)(294 - 6 + (255 - 165) / 2), 9.0, 8.0, 0.0, 0.0, 0.5625, 1.0, 1, 1, 0.0);
	}
	else 
	{
		RenderBitmap(31683, (float)(StartX - 4.5 + 161 / 2), (float)(294 - 6 + (255 - 165) / 2), 9.0, 8.0, 0.0, 0.0, 0.5625, 1.0, 1, 1, 0.0);
	}


	int Model;

	for (int i = 0; i < 400; i++)
	{
		Model = pGetPreviewStruct(pPreviewThis(), i);
		if (!Model) {
			continue;
		}
		if (Model
			&& *(BYTE*)(Model + 780)
			&& *(BYTE*)(Model + 800) == emPlayer
			)
		{
			if (Model != *(DWORD*)0x7BC4F04)
			{
				gInterface.DrawGUI(ePLAYER_POINT, (float)(StartX - 1 + *(DWORD*)(Model + 172) / 2), (float)(294 - 1 + (255 - *(DWORD*)(Model + 176)) / 2));
			}
			else {
				gInterface.DrawGUI(ePLAYER_POINT, (float)(StartX - 1 + *(DWORD*)(Model + 172) / 2), (float)(294 - 1 + (255 - *(DWORD*)(Model + 176)) / 2));
			}
		}
	}
}
#endif