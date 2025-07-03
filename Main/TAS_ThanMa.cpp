#include "stdafx.h"
#include "Interface.h"
#include "Central.h"
#include "CustomFont.h"
#include "Defines.h"
#include "Config.h"
#include "TAS_ThanMa.h"

#if(THANMA)
SubThanMa gThanMa;
DWORD ClickCount = 0;
void SubThanMa::SendProtocol61()
{
	if ((GetTickCount() - gInterface.Data[eWindowNPC_ThanMaChien].EventTick) > 300)
	{
		gInterface.Data[eWindowNPC_ThanMaChien].EventTick = GetTickCount();
		gInterface.Data[eWindowNPC_ThanMaChien].OnShow ^= 1;
	}
}
void SubThanMa::SendProtocol62(BYTE* lpMsg)
{
	PMSG_TIMEEVENT_CUSTOM* mRecv = (PMSG_TIMEEVENT_CUSTOM*)lpMsg;
	this->m_EventTMMap = mRecv->Map;
	this->m_EventTMState = mRecv->State;
	this->m_EventTMTimeCount = mRecv->TimeCount;
	this->mCalcTimeEventTick = GetTickCount();
}
void SubThanMa::SendProtocol63(BYTE* lpMsg)
{
	PMSG_COUNTLIST_TM* mRecv = (PMSG_COUNTLIST_TM*)lpMsg;
	this->m_TMChienBXHC = 0;
	this->m_TMScoreThienThan = mRecv->ScoreAcQuy;
	this->m_TMScoreAcQuy = mRecv->ScoreThienThan;
	for (int n = 0; n < 10; n++)
	{
		memset(this->m_ThanMaChienBXH[n].Name, 0, sizeof(this->m_ThanMaChienBXH[n].Name));
		this->m_ThanMaChienBXH[n].Kill = 0;
		this->m_ThanMaChienBXH[n].Team = 0;
	}
	for (int n = 0; n < mRecv->Count; n++)
	{
		EVENTHANMA_BXH* lpInfo = (EVENTHANMA_BXH*)(((BYTE*)mRecv) + sizeof(PMSG_COUNTLIST_TM) + (sizeof(EVENTHANMA_BXH) * n));
		memcpy(this->m_ThanMaChienBXH[n].Name, lpInfo->Name, sizeof(this->m_ThanMaChienBXH[n].Name));
		this->m_ThanMaChienBXH[n].Kill = lpInfo->Kill;
		this->m_ThanMaChienBXH[n].Team = lpInfo->Team;
		this->m_TMChienBXHC++;

		if (this->m_TMChienBXHC > 10)
		{
			break;
		}
	}
	if (mRecv->OpenBXHWindow == 1)
	{
		gInterface.Data[eWindowBXH_ThanMaChien].OnShow = 1;
	}
}
void SubThanMa::DrawTMPoint()
{
	if (pMapNumber != this->m_EventTMMap || this->m_EventTMTimeCount == 0)
	{
		return;
	}
	this->DiemA = this->m_TMScoreAcQuy;
	this->DiemB = this->m_TMScoreThienThan;
	float StartX = 555.0f;
	float StartY = -27.0f;

	RenderBitmap(0x17908, StartX, StartY, 169.0f, 90.0f, 0.0, 0.0, 1, 1, 1, 1, 0);
	if (pCheckMouseOver(StartX, StartY + 30, 95.0f, 19.0f) == 1) {
		RenderBitmap(0x17909, StartX, StartY, 169.0f, 90.0f, 0.0, 0.0, 1, 1, 1, 1, 0);
		if (GetTickCount() - gInterface.Data[eWindowNPC_ThanMaChien].EventTick > 300)
		{
			if (GetTickCount() - ClickCount > 300)
			{
				if (GetKeyState(1) & 0x8000)
				{
					gInterface.Data[eWindowBXH_ThanMaChien].OnShow ^= 1;
					ClickCount = GetTickCount();
				}
			}
		}
	}
	CustomFont.Draw(CustomFont.FontNormal, StartX, StartY + 30 + (19.0f / 4), 0xE6FCF7FF, 0x0, 95.0f, 0, 3, gConfig.TTAS_TEXT_ENGINE[257]);
	if ((GetTickCount() - this->mCalcTimeEventTick) > 1000)
	{
		if (this->m_EventTMTimeCount > 0) {
			this->m_EventTMTimeCount = this->m_EventTMTimeCount - 1;
		}
		this->mCalcTimeEventTick = GetTickCount();
	}

	this->totalseconds = this->m_EventTMTimeCount;
	this->hours = this->totalseconds / 3600;
	this->minutes = (this->totalseconds / 60) % 60;
	this->seconds = this->totalseconds % 60;

	if (hours > 23) {
		days = hours / 24;
		wsprintf(this->ThoiGian, "%d day(s)+", days);
	}
	else {
		wsprintf(this->ThoiGian, "%02d:%02d", minutes, seconds);
	}
	pSetBlend(true);
	glColor4f((GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, (float)0.8);
	pDrawBarForm(StartX - 155, 2, 155.0f, 15.0f, 0.0f, 0);
	pGLSwitchBlend();
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);
	gInterface.DrawFormat(eWhite, StartX - 150, 5, 150, 3, gConfig.TTAS_TEXT_ENGINE[258], this->DiemA, this->ThoiGian, this->DiemB);
	return;
}
void SubThanMa::DrawWindowNPCTM()
{
	if (!gInterface.Data[eWindowNPC_ThanMaChien].OnShow)
	{
		return;
	}

#define MoveButtonToLeft 70
#define MoveButtonToDown 0

	float MainWidth = 230.0;
	float StartY = 55;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float CloseX = StartX + MainWidth - 35;
	float CloseY = StartY;
	float SizeButtonW = 95.0;
	float SizeButtonH = 19.0;
	float CuaSoW = 300.0;
	float StartYMove = 190;

	gInterface.DrawAnimatedGUI(TMC_MAIN, StartX, StartY + 2);
	gInterface.DrawAnimatedGUI(TMC_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(TMC_FRAME, StartX, StartY + 67.0, 8);
	gInterface.DrawAnimatedGUI(TMC_FOOTER, StartX, StartY);

	pSetCursorFocus = true;
	pDrawGUI(0x7EC5, CloseX, CloseY, 36.0f, 29.0f);
	if (pCheckMouseOver(CloseX, CloseY, 36, 36) == 1)
	{
		if (GetTickCount() - ClickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				gInterface.Data[eWindowNPC_ThanMaChien].OnShow ^= 1;
				ClickCount = GetTickCount();
			}
		}
		pDrawColorButton(0x7EC5, CloseX, CloseY, 36, 29, 0, 0, pMakeColor(255, 204, 20, 130));
		gInterface.DrawFormat(eGold, CloseX + 15, CloseY + 30, 0, 1, gConfig.TTAS_TEXT_ENGINE[26]);
	}
	gInterface.DrawFormat(eGold, StartX + 10, gInterface.Data[TMC_MAIN].Y + 8, 210, 3, gConfig.TTAS_TEXT_ENGINE[259]);

	StartY = StartY + 45;	CustomFont.Draw(CustomFont.FontNormal, StartX + (CuaSoW / 10) - 10, StartY - StartYMove, 0xFFDE26FF, 0x0, CuaSoW, 0, 1, gConfig.TTAS_TEXT_ENGINE[260]);
	StartY = StartY + 12;	CustomFont.Draw(CustomFont.FontNormal, StartX + (CuaSoW / 10) - 10, StartY - StartYMove, 0xFFDE26FF, 0x0, CuaSoW, 0, 1, gConfig.TTAS_TEXT_ENGINE[261]);
	StartY = StartY + 12;	CustomFont.Draw(CustomFont.FontNormal, StartX + (CuaSoW / 10) - 10, StartY - StartYMove, 0xFFDE26FF, 0x0, CuaSoW, 0, 1, gConfig.TTAS_TEXT_ENGINE[262]);
	StartY = StartY + 12;	CustomFont.Draw(CustomFont.FontBold, StartX + (CuaSoW / 10) - 10, StartY - StartYMove, 0x00FFCCFF, 0x0, CuaSoW, 0, 1,   gConfig.TTAS_TEXT_ENGINE[263]);
	StartY = StartY + 12;	CustomFont.Draw(CustomFont.FontBold, StartX + (CuaSoW / 10) - 10, StartY - StartYMove, 0x00FF90FF, 0x0, CuaSoW, 0, 1,   gConfig.TTAS_TEXT_ENGINE[264]);
	StartY = StartY + 12;	CustomFont.Draw(CustomFont.FontBold, StartX + (CuaSoW / 10) - 10, StartY - StartYMove, 0x00FF90FF, 0x0, CuaSoW, 0, 1,   gConfig.TTAS_TEXT_ENGINE[265]);
	StartY = StartY + 12;	CustomFont.Draw(CustomFont.FontBold, StartX + (CuaSoW / 10) - 10, StartY - StartYMove, 0x00FF90FF, 0x0, CuaSoW, 0, 1,   gConfig.TTAS_TEXT_ENGINE[266]);
	StartY = StartY + 12;	CustomFont.Draw(CustomFont.FontBold, StartX + (CuaSoW / 10) - 10, StartY - StartYMove, 0x00FF90FF, 0x0, CuaSoW, 0, 1,   gConfig.TTAS_TEXT_ENGINE[267]);
	StartY = StartY + 12;	CustomFont.Draw(CustomFont.FontBold, StartX + (CuaSoW / 10) - 10, StartY - StartYMove, 0x00FF90FF, 0x0, CuaSoW, 0, 1,   gConfig.TTAS_TEXT_ENGINE[268]);
	StartY = StartY - 170;
	RenderBitmap(0x17908, StartX + MoveButtonToLeft, StartY, 169.0f, 90.0f, 0.0, 0.0, 1, 1, 1, 1, 0);
	if (pCheckMouseOver(StartX + MoveButtonToLeft, StartY + 30, SizeButtonW, SizeButtonH) == 1)
	{
		RenderBitmap(0x17909, StartX + MoveButtonToLeft, StartY, 169.0f, 90.0f, 0.0, 0.0, 1, 1, 1, 1, 0);
		if (GetTickCount() - gInterface.Data[eWindowNPC_ThanMaChien].EventTick > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				XULY_CGPACKET pMsg;
				pMsg.header.set(0xFF, 0x92, sizeof(pMsg));
				pMsg.ThaoTac = 1;
				DataSend((LPBYTE)&pMsg, pMsg.header.size);
				gInterface.Data[eWindowNPC_ThanMaChien].OnShow ^= 1;
			}
		}
	}
	CustomFont.Draw(CustomFont.FontNormal, StartX + MoveButtonToLeft, StartY + 30 + (SizeButtonH / 4), 0xE6FCF7FF, 0x0, SizeButtonW, 0, 3, gConfig.TTAS_TEXT_ENGINE[269]);
}
void SubThanMa::DrawWindowBXHTM()
{
	if (!gInterface.Data[eWindowBXH_ThanMaChien].OnShow)
	{
		return;
	}
	float CuaSoW = 250.0;
	float CuaSoH = 200.0;

	float StartX = (MAX_WIN_WIDTH / 2) - (CuaSoW / 2);
	float StartY = 45.0;

	gCentral.gDrawWindowCustom(StartX, StartY, CuaSoW, CuaSoH, eWindowBXH_ThanMaChien, gConfig.TextVN_ThanMaChien[18]);
	//====================================
	CustomFont.Draw(CustomFont.FontBold, StartX, StartY + 40, 0xFABB00FF, 0x0, CuaSoW / 4, 0, 3, "Top"); //
	CustomFont.Draw(CustomFont.FontBold, StartX + CuaSoW / 4, StartY + 40, 0xFABB00FF, 0x0, CuaSoW / 4, 0, 3, "Name"); //
	CustomFont.Draw(CustomFont.FontBold, StartX + ((CuaSoW / 4) * 2), StartY + 40, 0xFABB00FF, 0x0, CuaSoW / 4, 0, 3, "Kill"); //
	CustomFont.Draw(CustomFont.FontBold, StartX + ((CuaSoW / 4) * 3), StartY + 40, 0xFABB00FF, 0x0, CuaSoW / 4, 0, 3, "Team"); //
	DWORD ColorTextRank = 0xE0DFDCFF;

	for (int i = 0; i < this->m_TMChienBXHC; i++)
	{
		if (i % 2)
		{
			ColorTextRank = 0xA3A3A3FF;
		}
		else {
			ColorTextRank = 0xE0DFDCFF;
		}
		if (i < 3) { ColorTextRank = 0xFFE240FF; }
		CustomFont.Draw(CustomFont.FontBold, StartX, StartY + 55 + (i * 12), ColorTextRank, (i < 3) ? 0xFFE2400F : 0x0, CuaSoW / 4, 0, 3, "%d", i + 1); //
		CustomFont.Draw(CustomFont.FontBold, StartX + CuaSoW / 4, StartY + 55 + (i * 12), ColorTextRank, (i < 3) ? 0xFFE2400F : 0x0, CuaSoW / 4, 0, 3, "%s", this->m_ThanMaChienBXH[i].Name); //
		CustomFont.Draw(CustomFont.FontBold, StartX + ((CuaSoW / 4) * 2), StartY + 55 + (i * 12), ColorTextRank, (i < 3) ? 0xFFE2400F : 0x0, CuaSoW / 4, 0, 3, "%d", this->m_ThanMaChienBXH[i].Kill); //
		CustomFont.Draw(CustomFont.FontBold, StartX + ((CuaSoW / 4) * 3), StartY + 55 + (i * 12), ColorTextRank, (i < 3) ? 0xFFE2400F : 0x0, CuaSoW / 4, 0, 3, "%s", (this->m_ThanMaChienBXH[i].Team > 0) ? gConfig.TextVN_ThanMaChien[15 + this->m_ThanMaChienBXH[i].Team] : "NULL"); //

	}
}
void SubThanMa::DrawTMAllWindows()
{
	gThanMa.DrawTMPoint();
	gThanMa.DrawWindowNPCTM();
	gThanMa.DrawWindowBXHTM();
}
#endif