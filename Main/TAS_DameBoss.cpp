#include "Stdafx.h"
#if BXHDAME
#include "TAS_DameBoss.h"
#include "Interface.h"
#include "Central.h"
#include "CustomFont.h"
#include "Util.h"
#include "HealthBar.h"

#include "Console.h"
#include "User.h"
#include "Config.h"
#include "TAS_ToolKit.h"
#include "TAS_FixSolution.h"

TAS_DAMEBOSS_CLASS gDmgBoss;
 
void TAS_DAMEBOSS_CLASS::DAMECLEAR()
{
	for (int n = 0; n < 10; n++)
	{
		memset(gDmgBoss[n].szName, 0, sizeof(gDmgBoss[n].szName));
		gDmgBoss[n].Kill = 0;
	}
	this->CalcString;
}
void TAS_DAMEBOSS_CLASS::Initz()
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	this->guiX = MAX_WIN_WIDTH - 150;
	this->guiY = 10;
	this->curX = JCResto+pCursorX;
	this->curY = pCursorY;
	this->dragging = false;
}
void TAS_DAMEBOSS_CLASS::DAMEGETINFO(PMSG_NEW_HEALTH_BAR_RECV* lpMsg)
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	CalcString = 0;
	this->TAS_DAMEBOSS_ID = 0;
	this->MaxLife = 0;
	this->MinLife = 0;
	this->Level = 0;
	this->Rate = 0;
	for (int n = 0; n < 10; n++)
	{
		memset(gDmgBoss[n].szName, 0, sizeof(gDmgBoss[n].szName));
		gDmgBoss[n].Kill = 0;
	}

	for (int n = 0; n < lpMsg->count; n++)
	{
		TAS_DAMEBOSS_STR* lpInfo = (TAS_DAMEBOSS_STR*)(((BYTE*)lpMsg) + sizeof(PMSG_NEW_HEALTH_BAR_RECV) + (sizeof(TAS_DAMEBOSS_STR) * n));
		memcpy(gDmgBoss[n].szName, lpInfo->szName, sizeof(gDmgBoss[n].szName));
		gDmgBoss[n].Kill = lpInfo->Kill;
		CalcString++;
		TAS_DAMEBOSS_ID = lpInfo->monsterid;
		MaxLife			= lpInfo ->MaxLife;
		Level			= lpInfo->Level;
		MinLife			= lpInfo->MinLife;
		Rate			= lpInfo->Rate;
		if (CalcString > 10)
		{
			break;
		}
	}
}

void TAS_DAMEBOSS_CLASS::DAMEDRAW()
{
	if (!gInterface.Data[eTopDame].OnShow)
	{
		return;
	}
	unsigned long ADD_ANTOAN = *(unsigned long*)(0x07BC4F04);
	if (ADD_ANTOAN)
	{
		this->ADD_OFF_ANTOAN = *(DWORD*)(ADD_ANTOAN + 0x0E);
		if (ADD_OFF_ANTOAN == 0)
		{
			this->CheckDrawBxhDame = 1;
			if ((gInterface.CheckWindow(ObjWindow::CashShop) || gInterface.CheckWindow(ObjWindow::FullMap) || gInterface.CheckWindow(ObjWindow::ChatWindow) || gInterface.CheckWindow(ObjWindow::Inventory) || gInterface.CheckWindow(ObjWindow::SkillTree)
				|| gInterface.CheckWindow(ObjWindow::MoveList)))
			{
				return;
			}
			int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

			float ScaleWidth = 150;
			float ScaleHeight = 80 + (CalcString * 10);

			if (GetKeyState(VK_RBUTTON) & 0x8000 && GetTickCount() > this->ActionTime + 1000)
			{
				if (gInterface.IsWorkZone1(this->guiX, this->guiY, ScaleWidth, ScaleHeight))
				{
					if (!this->dragging)
					{
						this->dragging = true;
						this->curX = pCursorX;
						this->curY = pCursorY;
					}
				}
				if (this->dragging)
				{
					this->guiX += pCursorX - this->curX;
					this->guiY += pCursorY - this->curY;
					this->curX = pCursorX;
					this->curY = pCursorY;
				}
			}
			else
			{
				if (this->dragging)
				{
					this->dragging = false;
				}
			}

			if (this->guiX < 0)
				this->guiX = 0;
			if (this->guiY < 20)
				this->guiY = 20;

			if (this->guiX > 640 - ScaleWidth)
				this->guiX = 640 - ScaleWidth;
			if (this->guiY > 480 - ScaleHeight - 51)
				this->guiY = 480 - ScaleHeight - 51;

			float X = JCResto+this->guiX+120;
			float Y = this->guiY;

			int MaxLifeBoss = this->Rate / 10;
			float LifeProgress = (MaxLifeBoss > 20) ? 20 : MaxLifeBoss;

			COLORREF WhiteColor = RGB(255, 255, 255);
			HFONT IsText;

			char IsValue[255];
			ZeroMemory(IsValue, sizeof(IsValue));
			wsprintf(IsValue, "%s - HP: %d%% - Cấp %d", pGetMonsterName(this->TAS_DAMEBOSS_ID), this->Rate, this->Level);

			if (this->MinLife <= 0)
			{
				gInterface.Data[eTopDame].OnShow = false;
				this->CheckDrawBxhDame = 0;
			}
			else
			{
				int JCResto = pWinWidth / pWinHeightReal / 2 - 320;
				RenderBitmap(0x17926, 244+ JCResto, 39, 152, 19, 0, 0, 1, 1, 1, 1, 0.0);
				RenderBitmap(0x17925, 249+ JCResto, 41, LifeProgress * 16, 15, 0, 0, 1, 1, 1, 1, 0.0);
				gToolKit.CRenderNumberExNew(325+JCResto, 44, this->MinLife, 3, 0.88);
				RenderBitmap(0x17924, 244+JCResto, 39, 152, 18, 0, 0, 1, 1, 1, 1, 0.0);

				gToolKit.CreateFontNew(170+JCResto, gFixSolution.KillBoss_Text_Y, 300, 3, 13, 700, IsValue, WhiteColor, IsText);

				gCentral.gInfoBox(X - 25, Y + 142, 137, ScaleHeight - 55, 0x00000096, 0, 0);
				CustomFont.Draw(CustomFont.FontBold, X - 23, Y + 143, 0xFFFFFFFF, 0x00FBFF69, 144, 0, 3, "BXH Dame");

				Y += 12;
				CustomFont.Draw(CustomFont.FontBold, X - 20, Y + 147, 0xFABB00FF, 0x0, ScaleWidth / 2, 0, 1, "Name");
				CustomFont.Draw(CustomFont.FontBold, X + ScaleWidth / 2 - 40, Y + 147, 0xFABB00FF, 0x0, ScaleWidth / 2, 0, 4, gConfig.TTAS_TEXT_ENGINE[218]);
				DWORD ColorTextRank = 0xE0DFDCFF;
				for (int i = 0; i < CalcString; i++)
				{
					if (i % 2)
					{
						ColorTextRank = 0xA3A3A3FF;
					}
					else
					{
						ColorTextRank = 0xE0DFDCFF;
					}
					if (i < 3) { ColorTextRank = 0xFFE240FF; }
					CustomFont.Draw(CustomFont.FontBold, X - 20, Y + (157) + (i * 10), ColorTextRank, (i < 3) ? 0x0 : 0x0, ScaleWidth / 2, 0, 1, "%d - %s", i + 1, gDmgBoss[i].szName);
					CustomFont.Draw(CustomFont.FontBold, X + ScaleWidth / 2 - 40, Y + (157) + (i * 10), ColorTextRank, (i < 3) ? 0x0 : 0x0, ScaleWidth / 2, 0, 4, "%s", gToolKit.QNumberFormat(gDmgBoss[i].Kill));
				}
			}
		}
		else
		{
			gInterface.Data[eTopDame].OnShow = false;
			this->CheckDrawBxhDame = 0;
		}
	}	
}

#endif