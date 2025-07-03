#include "stdafx.h"
#include "CustomJewelBank.h"
#include "Defines.h"
#include "Import.h"
#include "Interface.h"
#include "Offset.h"
#include "Protect.h"
#include "Util.h"
#include "HealthBar.h"
#include "Import.h"
#include "Object.h"
#include "PrintPlayer.h"
#include "User.h"
#include "Item.h"
#include "InterEx.h"
#include "UIControl.h"
#include "Console.h"
#include "TAS_ToolKit.h"
#include "Config.h"
#include "CustomFont.h"
CCustomJewelBank gCustomJewelBank;

CCustomJewelBank::CCustomJewelBank()
{
	for (int TAS = 0; TAS < MAX_ITEM_SLOT; TAS++)
	{
		this->m_Data.ItemBank[TAS] = 0;
	}
	this->Page = 0;
	this->MAX_PAGES = 0;
}

void CCustomJewelBank::JewelBankSend(int slot)
{
	if ((GetTickCount() - this->StatusTick) < 400)
	{
		return;
	}

	if (slot < 0)
	{
		return;
	}

	this->StatusTick = GetTickCount();
	PSBMSG_JEWELBANK_SEND pMsg;
	pMsg.slot = slot;
	pMsg.header.set(0xF3, 0xF5, sizeof(pMsg));
	DataSend((BYTE*)&pMsg, pMsg.header.size);
}

void CCustomJewelBank::GCCustomJewelBankInfoRecv(PSBMSG_JEWELBANK_RECV* lpMsg)
{
	for (int TAS = 0; TAS < MAX_ITEM_SLOT; TAS++)
	{
		this->m_Data.ItemBank[TAS]	= lpMsg->ItemBank[TAS];
	}

	this->JewelEnable	= lpMsg->JewelEnable;
	this->JewelMaxCount = lpMsg->JewelMaxCount;
	this->MAX_PAGES		= lpMsg->MAX_PAGES;
}

void InvetoryItemOver(int This)
{
	lpItemObj item = (lpItemObj) * (DWORD*)(This + 84);

	if (item)
	{
		if (GetKeyState(VK_RBUTTON) & 0x8000 && GetKeyState(VK_SHIFT) & 0x8000)
		{
			int start = 12;
			if (*(DWORD*)(This + 44) == 200)
			{
				start = 12;
			}
			else if (*(DWORD*)(This + 44) == 44)
			{
				start = 76;
			}
			else if (*(DWORD*)(This + 44) == 131)
			{
				start = 108;
			}

			int Slot = item->PosX + (item->PosY * 8) + start;

			gCustomJewelBank.JewelBankSend(Slot);
		}
	}

	((void(__thiscall*)(int))0x007DCF20)(This);
}

void CCustomJewelBank::Load()
{
	SetCompleteHook(0xE8, 0x007DD0D9, &InvetoryItemOver);
}

void CCustomJewelBank::SetPosGone()
{
	auto LuuTruTamThoi = [&](float& TAS1, int TAS2)
	{
		if (TAS2 >= 0 && TAS2 <= 9)		TAS1 = 27.0;
		else if (TAS2 <= 99)			TAS1 = 25.5;
		else if (TAS2 <= 999)			TAS1 = 24.0;
		else if (TAS2 <= 9999)			TAS1 = 22.5;
		else if (TAS2 <= 99999)			TAS1 = 21.0;
		else if (TAS2 <= 999999)		TAS1 = 19.5;
		else if (TAS2 <= 9999999)		TAS1 = 18.0;
		else if (TAS2 <= 99999999)		TAS1 = 16.5;
		else							TAS1 = 15.0;
	};
	for (int TAS = 0; TAS < MAX_ITEM_SLOT; TAS++)
	{
		LuuTruTamThoi(this->PosItemBank[TAS], this->m_Data.ItemBank[TAS]);
	}
}
void DrawItemText(float x, float StartBody, float AddBodyY, int posyy, float PosAdd, int ItemDraw, BYTE ItemType, WORD ItemIndex, BYTE Level, LPCSTR mString, int Ystring)
{
	ItemBmdStruct* ItemInfo = pGetItemBmdStruct(ITEM(12, 15));
	float MainWidth = 230.0;
	int WidthValue = 18;
	int HeightValue = 20;
	float barWidth = WidthValue * ItemInfo->ItemWidth;
	float barHeight = HeightValue * ItemInfo->ItemHeight;
	gInterface.DrawGUI(eJewelBank_Count, x + 85, StartBody + 55 + (22 * posyy));
	SetTextColorByHDC(pTextThis(), pMakeColor(218, 165, 32, 0xFFu));
	g_pRenderText.CRenderText(x - 40, gInterface.Data[eJewelBank_Count].Y - 3 + (18 * posyy) + Ystring, mString, 100, 0, 4, 0);
	gInterface.DrawItem2(x + 65, gInterface.Data[eJewelBank_Count].Y - 3 + (18 * posyy) + AddBodyY, barWidth, barHeight, GET_ITEM(ItemType, ItemIndex), ITEMS_LEVEL(Level), 0, 0, 0);
	gToolKit.CRenderNumberExBank(x + 85 + PosAdd, StartBody + 59 + (22 * posyy), ItemDraw, SIZE_NUMBER, 31337);
}
void CCustomJewelBank::DrawJewelBankWindow()
{
	if (gInterface.Data[eJewelBank_MAIN].OnShow == false)
	{
		return;
	}
	this->SetPosGone();
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	if (gInterface.CheckWindow(SkillTree) || gInterface.CheckWindow(Character) || gInterface.CheckWindow(Shop) || gInterface.CheckWindow(CreateGuild) || gInterface.CheckWindow(ChatWindow) || gInterface.CheckWindow(FriendList) || gInterface.CheckWindow(MuHelper) || gInterface.CheckWindow(Store) || gInterface.CheckWindow(Warehouse) || gInterface.CheckWindow(Trade) || gInterface.CheckWindow(CashShop) || gInterface.CheckWindow(MoveList) || gInterface.CheckWindow(ChaosBox))
	{
		if (gInterface.Data[eJewelBank_MAIN].OnShow == true)
		{
			gInterface.Data[eJewelBank_MAIN].OnShow = false;
			pSetCursorFocus = false;
			return;
		}
	}

	int BackSpace = 0;

	if (gInterface.CheckWindow(ExpandInventory))
	{
		BackSpace = 180.0;
	}

	pSetCursorFocus = true;
	float MainWidth = 230.0;
	float MainHeight = 180.0;
	float StartBody = 55.0;
	float StartY = 55.0;
	float StartX = JCResto+( MAX_WIN_WIDTH / 2) - (MainWidth / 2) - BackSpace;
	float MainCenter = StartX + (MainWidth / 3);

	gInterface.DrawGUI(eJewelBank_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eJewelBank_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eJewelBank_FRAME, StartX, StartY + 67.0, 13);
	gInterface.DrawGUI(eJewelBank_FOOTER, StartX, StartY);
	gInterface.DrawGUI(eJewelBank_CLOSE, StartX + MainWidth - gInterface.Data[eJewelBank_CLOSE].Width, gInterface.Data[eJewelBank_MAIN].Y - 2);

	DWORD Color = eGray100;
	if (gInterface.IsWorkZone(eJewelBank_CLOSE))
	{
		if (gInterface.Data[eJewelBank_CLOSE].OnClick)
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eJewelBank_CLOSE, gInterface.Data[eJewelBank_CLOSE].X, StartBody, Color);
		gInterface.DrawToolTip((int)gInterface.Data[eJewelBank_CLOSE].X + 5, (int)gInterface.Data[eJewelBank_CLOSE].Y + 25, gConfig.TTAS_TEXT_ENGINE[26]);
	}

	gInterface.DrawFormat(eGold, (int)StartX + 10, (int)StartBody + 10, 210, 3, gConfig.TTAS_TEXT_ENGINE[47]);


	if (this->JewelEnable == 1)
	{
		StartBody -= 15;

		float MoveLeft = 15.0f;
		float MoveDown = 20.0f;

		RenderBitmap(32344, StartX + MainWidth - gInterface.Data[TAS_JBank_Prev].Width - 130 + MoveLeft, 313 + MoveDown, 50.f, 18.f, 0, 0, 80.f / 128.f, 30.f / 34.f, 1, 1, 0.0);
		
		gToolKit.RenderExNumberLevel2(StartX + MainWidth - gInterface.Data[TAS_JBank_Prev].Width - 110 + MoveLeft, 318 + MoveDown, this->Page + 1, this->MAX_PAGES,0.77);

		gInterface.DrawGUI(eJewelBank_NEXT, StartX + MainWidth - gInterface.Data[TAS_JBank_Prev].Width - 80 + MoveLeft, 310 + MoveDown);
		gInterface.DrawGUI(eJewelBank_PREV, StartX + MainWidth - gInterface.Data[TAS_JBank_Prev].Width - 150 + MoveLeft, 310 + MoveDown);

		for (int i = (MAX_ITEM_BANK * this->Page); i < (MAX_ITEM_BANK * this->Page) + MAX_ITEM_BANK; i++)
		{
			int posxx = 0;
			int posyy = i;

			if (i >= 10 && i < 20)
			{
				posyy = i - 10;
			}
			else if (i >= 20 && i < 30)
			{
				posyy = i - 20;
			}
			switch (i)
			{
				case 0:	 DrawItemText(StartX+23,StartBody, 0,  posyy, this->PosItemBank[0],   this->m_Data.ItemBank[0], 14, 13 ,0, gConfig.TTAS_TEXT_ENGINE[48], 7);break;
				case 1:	 DrawItemText(StartX+23,StartBody, 4,  posyy, this->PosItemBank[1],   this->m_Data.ItemBank[1], 14, 14 ,0, gConfig.TTAS_TEXT_ENGINE[49], 11);break;
				case 2:	 DrawItemText(StartX+23,StartBody, 8,  posyy, this->PosItemBank[2],   this->m_Data.ItemBank[2], 14, 16 ,0, gConfig.TTAS_TEXT_ENGINE[50], 15);break;
				case 3:	 DrawItemText(StartX+23,StartBody, 12, posyy, this->PosItemBank[3],   this->m_Data.ItemBank[3], 14, 22 ,0, gConfig.TTAS_TEXT_ENGINE[51], 19);break;
				case 4:	 DrawItemText(StartX+23,StartBody, 16, posyy, this->PosItemBank[4],   this->m_Data.ItemBank[4], 14, 31 ,0, gConfig.TTAS_TEXT_ENGINE[52], 23);break;
				case 5:	 DrawItemText(StartX+23,StartBody, 20, posyy, this->PosItemBank[5],   this->m_Data.ItemBank[5], 14, 41 ,0, gConfig.TTAS_TEXT_ENGINE[53], 27);break;
				case 6:	 DrawItemText(StartX+23,StartBody, 24, posyy, this->PosItemBank[6],   this->m_Data.ItemBank[6], 14, 42 ,0, gConfig.TTAS_TEXT_ENGINE[54], 31);break;
				case 7:	 DrawItemText(StartX+23,StartBody, 28, posyy, this->PosItemBank[7],   this->m_Data.ItemBank[7], 12, 15 ,0, gConfig.TTAS_TEXT_ENGINE[55], 35);break;
				case 8:	 DrawItemText(StartX+23,StartBody, 32, posyy, this->PosItemBank[8],   this->m_Data.ItemBank[8], 14, 43 ,0, gConfig.TTAS_TEXT_ENGINE[56], 39);break;
				case 9:	 DrawItemText(StartX+23,StartBody, 36, posyy, this->PosItemBank[9],   this->m_Data.ItemBank[9], 14, 44 ,0, gConfig.TTAS_TEXT_ENGINE[57], 43);break;
				case 10: DrawItemText(StartX+23,StartBody, 0,  posyy, this->PosItemBank[10],  this->m_Data.ItemBank[10],14, 244,0, gConfig.TTAS_TEXT_ENGINE[58], 7);break;
				case 11: DrawItemText(StartX+23,StartBody, 4,  posyy, this->PosItemBank[11],  this->m_Data.ItemBank[11],14, 245,0, gConfig.TTAS_TEXT_ENGINE[59], 11);break;
				case 12: DrawItemText(StartX+23,StartBody, 8,  posyy, this->PosItemBank[12],  this->m_Data.ItemBank[12],14, 246,0, gConfig.TTAS_TEXT_ENGINE[60], 15);break;
				case 13: DrawItemText(StartX+23,StartBody, 12, posyy, this->PosItemBank[13],  this->m_Data.ItemBank[13],14, 247,0, gConfig.TTAS_TEXT_ENGINE[61], 19);break;
				case 14: DrawItemText(StartX+23,StartBody, 16, posyy, this->PosItemBank[14],  this->m_Data.ItemBank[14],14, 248,0, gConfig.TTAS_TEXT_ENGINE[62], 23);break;
				case 15: DrawItemText(StartX+23,StartBody, 20, posyy, this->PosItemBank[15],  this->m_Data.ItemBank[15],14, 249,0, gConfig.TTAS_TEXT_ENGINE[63], 27);break;
				case 16: DrawItemText(StartX+23,StartBody, 24, posyy, this->PosItemBank[16],  this->m_Data.ItemBank[16],14, 250,0, gConfig.TTAS_TEXT_ENGINE[64], 31);break;
				case 17: DrawItemText(StartX+23,StartBody, 28, posyy, this->PosItemBank[17],  this->m_Data.ItemBank[17],14, 251,0, gConfig.TTAS_TEXT_ENGINE[65], 35);break;
				case 18: DrawItemText(StartX+23,StartBody, 32, posyy, this->PosItemBank[18],  this->m_Data.ItemBank[18],14, 252,0, gConfig.TTAS_TEXT_ENGINE[66], 39);break;
				case 19: DrawItemText(StartX+23,StartBody, 36, posyy, this->PosItemBank[19],  this->m_Data.ItemBank[19],14, 260,0, gConfig.TTAS_TEXT_ENGINE[67], 43);break;
				case 20: DrawItemText(StartX+23,StartBody, 0,   posyy, this->PosItemBank[20], this->m_Data.ItemBank[20],12, 32 ,0, "Hộp Quà Đỏ",				  7);  break;
				case 21: DrawItemText(StartX+23,StartBody, 4,   posyy, this->PosItemBank[21], this->m_Data.ItemBank[21],12, 33 ,0, "Hộp Quà Xanh Lá",			  11); break;
				case 22: DrawItemText(StartX+23,StartBody, 8,   posyy, this->PosItemBank[22], this->m_Data.ItemBank[22],12, 34 ,0, "Hộp Quà Xanh Dương",		  15); break;
				case 23: DrawItemText(StartX+23,StartBody, 12,  posyy, this->PosItemBank[23], this->m_Data.ItemBank[23],14, 52 ,0, "Box GM",					  19); break;
				case 24: DrawItemText(StartX+23,StartBody, 16,  posyy, this->PosItemBank[24], this->m_Data.ItemBank[24],14, 55 ,0, "Box Trang Bị 380",		  23); break;
				case 25: DrawItemText(StartX+23,StartBody, 20,  posyy, this->PosItemBank[25], this->m_Data.ItemBank[25],14, 56 ,0, "Box Vũ Khí Cấp 4",		  27); break;
				case 26: DrawItemText(StartX+23,StartBody, 24,  posyy, this->PosItemBank[26], this->m_Data.ItemBank[26],14, 57 ,0, "Box Khiên Cấp 4",			  31); break;
				case 27: DrawItemText(StartX+23,StartBody, 28,  posyy, this->PosItemBank[27], this->m_Data.ItemBank[27],14, 51 ,0, "Pháo Hoa Ngôi Sao",		  35); break;
				case 28: DrawItemText(StartX+23,StartBody, 32,  posyy, this->PosItemBank[28], this->m_Data.ItemBank[28],14, 121,0, "Hộp Quà Vàng",			  39); break;
				case 29: DrawItemText(StartX+23,StartBody, 36,  posyy, this->PosItemBank[29], this->m_Data.ItemBank[29],14, 122,0, "Hộp Quà Bạc",				  43); break;
			}
			if (i < 10 || i >= 10 && i < 20 || i >= 20 && i < 30)
			{
				for (int j = (i * 4); j < (i * 4) + 4; j++)
				{
					gInterface.DrawGUI(eJewelBank_WITHDRAW + j,		 StartX+21 + 120 + (18 * posxx), StartBody + 55 + (22 * posyy));
					if (posxx == 0) gToolKit.CRenderNumberClassic(1, StartX+21 + 128 + (18 *  posxx), StartBody + 59 + (22 * posyy), 1, 0.72);
					if (posxx == 1) gToolKit.CRenderNumberClassic(1, StartX+21 + 128 + (18 *  posxx), StartBody + 59 + (22 * posyy), 1 * 10, 0.72);
					if (posxx == 2) gToolKit.CRenderNumberClassic(1, StartX+21 + 128 + (18 *  posxx), StartBody + 59 + (22 * posyy), 1 * 20, 0.72);
					//if (posxx == 3) gToolKit.CRenderNumberClassic(1, StartX + 128 + (18 *  posxx), StartBody + 59 + (22 * posyy), 1 * 30, 0.72);
					if (posxx == 3) gToolKit.CRenderNumberClassic(1, StartX+21 + 128 + (18 *  posxx), StartBody + 59 + (22 * posyy), 1*30, 0.72);
					posxx++;
				}
			}
		}
		gInterface.DrawFormat(eExcellent, StartX, StartBody + 280, 230, 3, gConfig.TTAS_TEXT_ENGINE[68]);
	}
	else
	{
		gInterface.DrawFormat(eGold, MainCenter + 30, StartBody + 100, 52, 1, gConfig.TTAS_TEXT_ENGINE[69]);
	}
}

void CCustomJewelBank::OpenWindow()
{
	if (gInterface.CheckWindow(SkillTree) || gInterface.CheckWindow(Shop) || gInterface.CheckWindow(CreateGuild) || gInterface.CheckWindow(ChatWindow) || gInterface.CheckWindow(FriendList) || gInterface.CheckWindow(MuHelper) || gInterface.CheckWindow(Store) || gInterface.CheckWindow(Warehouse) || gInterface.CheckWindow(Trade) || gInterface.CheckWindow(CashShop) || gInterface.CheckWindow(GuardNPC))
	{
		return;
	}

	if ((GetTickCount() - gInterface.Data[eJewelBank_MAIN].EventTick) < 500)
	{
		return;
	}

	gInterface.Data[eJewelBank_MAIN].EventTick = GetTickCount();

	if (gInterface.Data[eJewelBank_MAIN].OnShow == true)
	{
		gInterface.Data[eJewelBank_MAIN].OnShow = false;
		pSetCursorFocus = false;
		return;
	}

	gInterface.CloseCustomWindow();

	gInterface.OpenWindow(Inventory);
	gInterface.CloseWindow(Character);
	gInterface.Data[eJewelBank_MAIN].OnShow = true;
	pSetCursorFocus = true;
	this->Page = 0;

}

bool CCustomJewelBank::CommandNext(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eJewelBank_NEXT].EventTick);
	DWORD Delay2 = (CurrentTick - gInterface.Data[eJewelBank_PREV].EventTick);

	if (!gInterface.Data[eJewelBank_MAIN].OnShow)
	{
		return false;
	}

	if (!gInterface.IsWorkZone(eJewelBank_NEXT))
	{
		return false;
	}

	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eJewelBank_NEXT].OnClick = true;
		return true;
	}

	if (Delay < 300 || Delay2 < 300)
	{
		return false;
	}

	gInterface.Data[eJewelBank_NEXT].OnClick = false;

	if (this->Page >= this->MAX_PAGES - 1)
	{
		return false;
	}
	this->Page++;
	gInterface.Data[eJewelBank_NEXT].EventTick = GetTickCount();
	return true;
}

bool CCustomJewelBank::CommandPrev(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eJewelBank_PREV].EventTick);
	DWORD Delay2 = (CurrentTick - gInterface.Data[eJewelBank_NEXT].EventTick);

	if (!gInterface.Data[eJewelBank_MAIN].OnShow)
	{
		return false;
	}

	if (!gInterface.IsWorkZone(eJewelBank_PREV))
	{
		return false;
	}

	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eJewelBank_PREV].OnClick = true;
		return true;
	}

	if (Delay < 300 || Delay2 < 300)
	{
		return false;
	}

	gInterface.Data[eJewelBank_PREV].OnClick = false;
	if (this->Page <= 0)
	{
		return false;
	}
	this->Page--;	
	gInterface.Data[eJewelBank_PREV].EventTick = GetTickCount();
	return true;
}

bool CCustomJewelBank::EventJewelBankWindow_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eJewelBank_CLOSE].EventTick);

	if (!gInterface.Data[eJewelBank_MAIN].OnShow || !gInterface.IsWorkZone(eJewelBank_CLOSE))
	{
		return false;
	}

	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eJewelBank_CLOSE].OnClick = true;
		return true;
	}

	gInterface.Data[eJewelBank_CLOSE].OnClick = false;

	if (Delay < 500)
	{
		return false;
	}

	gInterface.Data[eJewelBank_CLOSE].EventTick = GetTickCount();
	gInterface.Data[eJewelBank_MAIN].OnShow = false;
	pSetCursorFocus = false;

	return false;
}

bool CCustomJewelBank::EventJewelBankWithDraw(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	if (!gInterface.Data[eJewelBank_MAIN].OnShow)
	{
		return false;
	}

	for (int i = (MAX_ITEM_BANK * 5) * Page; i < ((MAX_ITEM_BANK * 5) * Page) + (MAX_ITEM_BANK * 5); i++)
	{
		if (gInterface.IsWorkZone(eJewelBank_WITHDRAW + i))
		{
			DWORD Delay = (CurrentTick - gInterface.Data[eJewelBank_WITHDRAW + i].EventTick);

			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[eJewelBank_WITHDRAW + i].OnClick = true;
				return true;
			}
			gInterface.Data[eJewelBank_WITHDRAW + i].OnClick = false;
			if (Delay < 300)
			{
				return false;
			}
			// ----

			int type = 0;
			int num = -1;
			int count = -1;

			if (i >= 145 && i < 150) { type = 39; num = i - 145; }
			if (i >= 140 && i < 145) { type = 38; num = i - 140; }
			if (i >= 135 && i < 140) { type = 37; num = i - 135; }
			if (i >= 130 && i < 135) { type = 36; num = i - 130; }
			if (i >= 125 && i < 130) { type = 35; num = i - 125; }
			if (i >= 120 && i < 125) { type = 34; num = i - 120; }
			if (i >= 115 && i < 120) { type = 33; num = i - 115; }
			if (i >= 110 && i < 115) { type = 32; num = i - 110; }
			if (i >= 105 && i < 110) { type = 31; num = i - 105; }
			if (i >= 100 && i < 105) { type = 30; num = i - 100; }

			if (i >= 95  && i < 100) { type = 29; num = i - 95; }
			if (i >= 90  && i < 95)  { type = 28; num = i - 90; }
			if (i >= 85  && i < 90)  { type = 27; num = i - 85; }
			if (i >= 80  && i < 85)  { type = 26; num = i - 80; }
			if (i >= 75  && i < 80)  { type = 25; num = i - 75; }
			if (i >= 70  && i < 75)  { type = 24; num = i - 70; }
			if (i >= 65  && i < 70)  { type = 23; num = i - 65; }
			if (i >= 60  && i < 65)  { type = 22; num = i - 60; }
			if (i >= 55  && i < 60)  { type = 21; num = i - 55; }
			if (i >= 50  && i < 55)  { type = 20; num = i - 50; }
								    
			if (i >= 45  && i < 50)  { type = 9; num = i - 45; }
			if (i >= 40  && i < 45)  { type = 8; num = i - 40; }
			if (i >= 35  && i < 40)  { type = 7; num = i - 35; }
			if (i >= 30  && i < 35)  { type = 6; num = i - 30; }
			if (i >= 25  && i < 30)  { type = 5; num = i - 25; }
			if (i >= 20  && i < 25)  { type = 4; num = i - 20; }
			if (i >= 15  && i < 20)  { type = 3; num = i - 15; }
			if (i >= 10  && i < 15)  { type = 2; num = i - 10; }
			if (i >= 5   && i < 10)  { type = 1; num = i - 5; }
			if (i >= 0   && i < 5)   { type = 0; num = i; }

			if (num == 0) count = 1;
			if (num == 1) count = 10;
			if (num == 2) count = 20;
			if (num == 3) count = 30;
			if (num == 4) count = 99;

			if (count <= 0)
				return false;

			this->JewelBankWithDrawSend(type, count);
			gInterface.Data[eJewelBank_WITHDRAW + i].EventTick = GetTickCount();
		}
	}
	return false;
}

void CCustomJewelBank::JewelBankWithDrawSend(int type, int count)
{
	if ((GetTickCount() - this->StatusTick) < 400)
	{
		return;
	}

	if ((GetTickCount() - gInterface.Data[eJewelBank_MAIN].EventTick) < 400)
	{
		return;
	}

	if (type < 0 || count < 0)
	{
		return;
	}

	this->StatusTick = GetTickCount();
	PSBMSG_JEWELBANKWITHDRAW_SEND pMsg;
	pMsg.type = type;
	pMsg.count = count;
	pMsg.header.set(0xF3, 0xF6, sizeof(pMsg));
	DataSend((BYTE*)&pMsg, pMsg.header.size);
}
