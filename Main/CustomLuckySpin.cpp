#include "stdafx.h"
#include "CustomLuckySpin.h"
#include "Interface.h"
#include "Defines.h"
#include "Item.h"
#include "User.h"
#include "CustomWing.h"
#include "Protect.h"
#include "Protocol.h"
#include "Config.h"
#include "SItemOption.h"
#include "Central.h"
#include "TAS_ToolKit.h"

#if(VONGQUAY_NEW)
CLuckySpin gLuckySpin;

CLuckySpin::CLuckySpin()
{
	this->StartRoll = 0;
	this->RollNumber = -1;
	this->itemdata.clear();
}

void CLuckySpin::SwitchLuckySpinWindowState()
{
	(gInterface.Data[eLuckySpin].OnShow == true) ? gInterface.Data[eLuckySpin].Close() : this->CGLuckySpinSend();
}

void CLuckySpin::GCLuckySpinInit(GC_LuckySpinInit* aRecv)
{
	if (aRecv->result)
	{
		gInterface.Data[eLuckySpin].Open();
	}
}

void CLuckySpin::GCItemSend(GC_LuckySpin_Data* aRecv)
{
	LuckySpin_Data pData;
	pData.ItemType = aRecv->ItemType;
	pData.ItemIndex = aRecv->ItemIndex;
	pData.ItemLevel = aRecv->ItemLevel;
	pData.ItemExc = aRecv->ItemExc;
	this->WCoinC = aRecv->WCoinC;
	this->itemdata.push_back(pData);
}

void CLuckySpin::CGLuckySpinSend()
{
	CG_LUCKYSPIN_REQ pRequest;
	pRequest.h.set(0xFC, 0x17, sizeof(pRequest));
	DataSend((LPBYTE)&pRequest, pRequest.h.size);
}

void CLuckySpin::LuckySpinData(GC_LuckySpinUpdateData * aRecv)
{
	this->StartRoll = 0;
	this->RollNumber = aRecv->RollNumber;
}


void CLuckySpin::Draw()
{
	if (gInterface.CheckWindow(CashShop) ||
		gInterface.CheckWindow(ChaosBox) ||
		gInterface.CheckWindow(FullMap) ||
		gInterface.CheckWindow(MoveList) ||
		gInterface.CheckWindow(Party) ||
		gInterface.CheckWindow(Trade) ||
		gInterface.CheckWindow(ExpandInventory) ||
		gInterface.CheckWindow(Store) ||
		gInterface.CheckWindow(Character) ||

		gInterface.CheckWindow(SkillTree))
		return;

	if (!gInterface.Data[eLuckySpin].OnShow)
	{
		return;
	}

	float MainWidth = 230.0;
	float MainHeight = 313.0;
	float StartY = 80.0;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (29.0 / 2);

	if (gInterface.IsWorkZone(eLuckySpin))
	{
		pSetCursorFocus = true;
	}
	else pSetCursorFocus = false;
		
	gCentral.gDrawWindowCustom(StartX - 45, gInterface.Data[eLuckySpin].Y + 70, MainWidth + 83, MainHeight - 50, eLuckySpin, "LUCKY SPIN");
	gToolKit.CloseButton(440, 68, TAS_LSpin_BtnClose);

	gCentral.gInfoBox(355, 104, 90, 100, 200, 0, 0);//1
	gCentral.gInfoBox(355, 219, 90, 7,	 200, 0, 0);//2
	
	float RanW = 40 - 2;
	float RanH = 47 + 4;

	if (this->StartRoll >= 1)
	{
		pSetBlend(true);
		glColor4f(1.0, 1.0, 0.0, 0.3);
		int ran = rand() % MAX_ITEM_SPIN;
		
		switch (ran)
		{
			case 0:	pDrawBarForm(186 , 103, RanW, RanH, 0, 0);	break;
			case 1:	pDrawBarForm(227 , 103, RanW, RanH, 0, 0);	break;
			case 2:	pDrawBarForm(268 , 103, RanW, RanH, 0, 0);	break;
			case 3:	pDrawBarForm(309 , 103, RanW, RanH, 0, 0);	break;
			case 4:	pDrawBarForm(309 , 157, RanW, RanH, 0, 0);	break;
			case 5:	pDrawBarForm(309 , 212, RanW, RanH, 0, 0);	break;
			case 6:	pDrawBarForm(310 , 268, RanW, RanH, 0, 0);	break;
			case 7:	pDrawBarForm(269 , 266, RanW, RanH, 0, 0);	break;
			case 8:	pDrawBarForm(227 , 267, RanW, RanH, 0, 0);	break;
			case 9:	pDrawBarForm(187 , 268, RanW, RanH, 0, 0);	break;
			case 10:pDrawBarForm(185 , 157, RanW, RanH, 0, 0);	break;
			case 11:pDrawBarForm(186 , 212, RanW, RanH, 0, 0);	break;

			pGLSwitchBlend();
			glColor3f(1.0, 1.0, 1.0);
		}
		pSetBlend(false);
	}

	if (this->RollNumber >= 0)
	{
		pSetBlend(true);
		glColor4f(1.0, 1.0, 0.0, 0.3);
		switch (RollNumber)
		{
			case 0:	pDrawBarForm(186 , 103, RanW, RanH, 0, 0);	break;
			case 1:	pDrawBarForm(227 , 103, RanW, RanH, 0, 0);	break;
			case 2:	pDrawBarForm(268 , 103, RanW, RanH, 0, 0);	break;
			case 3:	pDrawBarForm(309 , 103, RanW, RanH, 0, 0);	break;
			case 4:	pDrawBarForm(309 , 157, RanW, RanH, 0, 0);	break;
			case 5:	pDrawBarForm(309 , 212, RanW, RanH, 0, 0);	break;
			case 6:	pDrawBarForm(310 , 268, RanW, RanH, 0, 0);	break;
			case 7:	pDrawBarForm(269 , 266, RanW, RanH, 0, 0);	break;
			case 8:	pDrawBarForm(227 , 267, RanW, RanH, 0, 0);	break;
			case 9:	pDrawBarForm(187 , 268, RanW, RanH, 0, 0);	break;
			case 10:pDrawBarForm(185 , 157, RanW, RanH, 0, 0);	break;
			case 11:pDrawBarForm(186 , 212, RanW, RanH, 0, 0);	break;

			pGLSwitchBlend();
			glColor3f(1.0, 1.0, 1.0);
		}
		pSetBlend(false);
	}
	gCentral.gInfoBox(186,			104, 30, 43, 200, 0, 0);//1
	gCentral.gInfoBox(186 + 41,		104, 30, 43, 200, 0, 0);//2
	gCentral.gInfoBox(186 + 82,		104, 30, 43, 200, 0, 0);//3
	gCentral.gInfoBox(186 + 123,	104, 30, 43, 200, 0, 0);//4

	gCentral.gInfoBox(186 + 123,	158, 30, 43, 200, 0, 0);//5
	gCentral.gInfoBox(186 + 123,	212, 30, 43, 200, 0, 0);//6

	gCentral.gInfoBox(186,			266, 30, 43, 200, 0, 0);//7
	gCentral.gInfoBox(186 + 41,		266, 30, 43, 200, 0, 0);//8
	gCentral.gInfoBox(186 + 82,		266, 30, 43, 200, 0, 0);//9
	gCentral.gInfoBox(186 + 123,	266, 30, 43, 200, 0, 0);//10

	gCentral.gInfoBox(186 , 158, 30, 43, 200, 0, 0);//11
	gCentral.gInfoBox(186 , 212, 30, 43, 200, 0, 0);//12

	gInterface.DrawItem2(170, 97 , 70, 50, ITEM(this->itemdata[0].ItemType, this->itemdata[0].ItemIndex), SET_ITEMOPT_LEVEL(this->itemdata[0].ItemLevel), this->itemdata[0].ItemExc, 0, 0);
	gInterface.DrawItem2(212, 100, 65, 47, ITEM(this->itemdata[1].ItemType, this->itemdata[1].ItemIndex), SET_ITEMOPT_LEVEL(this->itemdata[1].ItemLevel), this->itemdata[1].ItemExc, 0, 0);
	gInterface.DrawItem2(254, 100, 65, 47, ITEM(this->itemdata[2].ItemType, this->itemdata[2].ItemIndex), SET_ITEMOPT_LEVEL(this->itemdata[2].ItemLevel), this->itemdata[2].ItemExc, 0, 0);
	gInterface.DrawItem2(294, 97 , 65, 50, ITEM(this->itemdata[3].ItemType, this->itemdata[3].ItemIndex), SET_ITEMOPT_LEVEL(this->itemdata[3].ItemLevel), this->itemdata[3].ItemExc, 0, 0);
	gInterface.DrawItem2(294, 148, 65, 50, ITEM(this->itemdata[4].ItemType, this->itemdata[4].ItemIndex), SET_ITEMOPT_LEVEL(this->itemdata[4].ItemLevel), this->itemdata[4].ItemExc, 0, 0);
	gInterface.DrawItem2(294, 199, 63, 50, ITEM(this->itemdata[5].ItemType, this->itemdata[5].ItemIndex), SET_ITEMOPT_LEVEL(this->itemdata[5].ItemLevel), this->itemdata[5].ItemExc, 0, 0);
	gInterface.DrawItem2(290, 262, 70, 45, ITEM(this->itemdata[6].ItemType, this->itemdata[6].ItemIndex), SET_ITEMOPT_LEVEL(this->itemdata[6].ItemLevel), this->itemdata[6].ItemExc, 0, 0);
	gInterface.DrawItem2(248, 262, 70, 45, ITEM(this->itemdata[7].ItemType, this->itemdata[7].ItemIndex), SET_ITEMOPT_LEVEL(this->itemdata[7].ItemLevel), this->itemdata[7].ItemExc, 0, 0);
	gInterface.DrawItem2(206, 262, 70, 45, ITEM(this->itemdata[8].ItemType, this->itemdata[8].ItemIndex), SET_ITEMOPT_LEVEL(this->itemdata[8].ItemLevel), this->itemdata[8].ItemExc, 0, 0);
	gInterface.DrawItem2(168, 262, 70, 45, ITEM(this->itemdata[9].ItemType, this->itemdata[9].ItemIndex), SET_ITEMOPT_LEVEL(this->itemdata[9].ItemLevel), this->itemdata[9].ItemExc, 0, 0);
	gInterface.DrawItem2(168, 148, 70, 50, ITEM(this->itemdata[10].ItemType, this->itemdata[10].ItemIndex), SET_ITEMOPT_LEVEL(this->itemdata[10].ItemLevel), this->itemdata[10].ItemExc, 0, 0);
	gInterface.DrawItem2(168, 199, 70, 50, ITEM(this->itemdata[11].ItemType, this->itemdata[11].ItemIndex), SET_ITEMOPT_LEVEL(this->itemdata[11].ItemLevel), this->itemdata[11].ItemExc, 0, 0);
	// item nhận thưởng
	if (this->RollNumber >= 0)
	{
		gInterface.DrawItem2(377, 110, 50, 50, ITEM(this->itemdata[RollNumber].ItemType, this->itemdata[RollNumber].ItemIndex), SET_ITEMOPT_LEVEL(this->itemdata[RollNumber].ItemLevel), this->itemdata[RollNumber].ItemExc, 0, 0);
	}
	//
	gInterface.DrawGUI(eLuckySpinRoll, 378, 241);
	if (gInterface.IsWorkZone(eLuckySpinRoll))
	{
		DWORD Color = eGray150;

		gInterface.DrawColoredGUI(eLuckySpinRoll, gInterface.Data[eLuckySpinRoll].X, gInterface.Data[eLuckySpinRoll].Y, Color);
	}
	gInterface.DrawFormat(eYellow, 300, 222, 210, 3, gConfig.TTAS_TEXT_ENGINE[70], this->WCoinC); // "Giá"
	gInterface.DrawFormat(eYellow, 300, 249, 210, 3, gConfig.TTAS_TEXT_ENGINE[71]); // "Quay"
}

void CLuckySpin::EventWindow_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if (!gInterface.Data[eLuckySpin].OnShow)
	{
		return;
	}

	if (gInterface.IsWorkZone(eLuckySpinRoll))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eLuckySpinRoll].EventTick);
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eLuckySpinRoll].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eLuckySpinRoll].OnClick = false;
		pSetCursorFocus = false;
		if (Delay < 6000)
		{
			return;
		}
		gInterface.Data[eLuckySpinRoll].EventTick = GetTickCount();
		RollNumber = -1;
		CG_LUCKYSPIN_REQ pRequest;
		pRequest.h.set(0xFC, 0x16, sizeof(pRequest));
		DataSend((LPBYTE)&pRequest, pRequest.h.size);
	}

	if (gInterface.IsWorkZone(eLuckySpinClose))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eLuckySpinClose].EventTick);
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eLuckySpinClose].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		gInterface.Data[eLuckySpinClose].OnClick = false;
		pSetCursorFocus = false;
		if (Delay < 500)
		{
			return;
		}
		gInterface.Data[eLuckySpinClose].EventTick = GetTickCount();
		this->SwitchLuckySpinWindowState();
	}
}
#endif