#include "StdAfx.h"
#include "TAS_Intros.h"
#include "Interface.h"
#include "Defines.h"
#include "Central.h"
#include "TAS_ToolKit.h"
#include "CustomFont.h"
#include "Config.h"
NewIntros gNewIntros;

void NewIntros::OpenWindowMocNap()
{
	if (GetTickCount() < gInterface.Data[eWindowIntros].EventTick + 300)
	{
		return;
	}
	gInterface.Data[eWindowIntros].EventTick = GetTickCount();
	gInterface.Data[eWindowIntros].OnShow ^= 1;
}
#include "CBNewUiEx.h"
CNewUIScrollBar* ListScrollBar = NULL;
bool UpdateMaxPos = false;
int ListMaxPerPage = 15;
void NewIntros::DrawWindowMocNap()
{
	if (CheckTAS_WINDOWS5)
	{
		gInterface.Data[eWindowIntros].OnShow = 0;
		return;
	}
	if (!gInterface.Data[eWindowIntros].OnShow)
	{
		return;
	}
	float WindowW = 220;
	float WindowH = 270;
	float StartXA = (MAX_WIN_WIDTH / 2) - (WindowW / 2);
	float StartX = StartXA - 48;
	float StartY = ((MAX_WIN_HEIGHT - 51) / 2) - (WindowH / 2);

	//AI Code
	gCentral.gDrawWindowCustom(StartX - 30, StartY - 30, WindowW + 150, WindowH + 80, eWindowIntros, gConfig.TTAS_TEXT_HD[0]);
	{
		gCentral.gInfoBox(StartX - 15, StartY + 5, WindowW + 115, 3, 0x00000096, 0, 0);
		gCentral.gInfoBox(StartX - 15, StartY + 20, WindowW + 115, 280, 0x00000096, 0, 0);
		CustomFont.Draw(CustomFont.FontBold, StartX - 13, StartY + 5, 0xFFFFFFFF, 0xca0e0e69, WindowW + 124 - 5, 0, 3, " ");
		CustomFont.Draw(CustomFont.FontBold, StartX - 13, StartY + 5, 0xFFFFFFFF, 0xca0e0e69, WindowW + 124 - 5, 0, 3, gConfig.TTAS_TEXT_HD[1]);

		int PosXInvetoryImg = 280;
		int PosYInvetoryImg = 52;
		int DataListItem = sizeof(gConfig.TTAS_TEXT_HD) / sizeof(gConfig.TTAS_TEXT_HD[0]);
		if (ListScrollBar == NULL)
		{
			ListScrollBar = new CNewUIScrollBar();
			ListScrollBar->Create(PosXInvetoryImg + 190, PosYInvetoryImg + 50, 270);
			if (ListScrollBar)
			{
				ListScrollBar->SetMaxPos((DataListItem <= ListMaxPerPage) ? 0 : (DataListItem - ListMaxPerPage));
				ListScrollBar->SetPos(PosXInvetoryImg + 190, PosYInvetoryImg + 50);
			}
		}
		if (ListScrollBar)
		{
			if (UpdateMaxPos)
			{
				ListScrollBar->SetMaxPos((DataListItem <= ListMaxPerPage) ? 0 : (DataListItem / ListMaxPerPage) - 1);
				UpdateMaxPos = false;
			}

			ListScrollBar->MouseWheelWindow = pCheckMouseOver(PosXInvetoryImg + 65, PosYInvetoryImg + 50, 130, 270);
			ListScrollBar->Render();
			ListScrollBar->UpdateMouseEvent();
			ListScrollBar->Update();
		}
		int VipCharListPage = ListScrollBar->GetCurPos();

		int Count = 0;
		int CurPos = ListScrollBar->GetCurPos();
		for (int i = CurPos; i < DataListItem; i++)
		{
			if (Count >= ListMaxPerPage) break;
			float PosY = StartY + 23 + (Count * 10);  
			CustomFont.Draw(CustomFont.FontBold, StartX - 8, PosY, 0xFFFFFFFF, 0, WindowW + 124 - 5, 0, 1, gConfig.TTAS_TEXT_HD[i + 2]);
			Count++;
		}
	}
}
