#include "StdAfx.h"
#if(TAS_ITEMTRADE)
#include "TAS_ItemTrader.h"
#include "Offset.h"
#include "Defines.h"
#include "Interface.h"
#include "TAS_ToolKit.h"
#include "Common.h"
#include "Central.h"
#include "CustomFont.h"
#include "Config.h"
#include "CBUtil.h"
#include "OffTrade.h"

TAS_NPC_TRADER gItemTrade;
int DoiItem = -1;

void* BCacheInfoItemDD;
DWORD CacheTimeShowInfoItem = 0;

struct INFOITEM_DOIITEM_CLIENT
{
	PSWMSG_HEAD header;
	BYTE ActiveMix;
	BYTE ItemChinh[16];
	BYTE ItemPhu[3][16];
	BYTE ItemKetQua[6][16];
	int WCoinC ;
	int WCoinP ;
	int WCoinG ;
	int CoinAtm;
};
void TAS_NPC_TRADER::SendToProtocol6A(BYTE* lpMsg)
{
	XULY_CGPACKET* mRecv = (XULY_CGPACKET*)lpMsg;
	if (mRecv->ThaoTac != 111) return;
	if (GetTickCount() > gInterface.Data[eWindowDoiItem].EventTick)
	{
		gInterface.Data[eWindowDoiItem].EventTick = GetTickCount() + 300;
		gInterface.Data[eWindowDoiItem].OnShow ^= 1;
	}
	this->SetStateDoiItem = true;
}
void TAS_NPC_TRADER::SendToProtocol6B(BYTE* lpMsg)
{
	INFOITEM_DOIITEM_CLIENT* mRecv = (INFOITEM_DOIITEM_CLIENT*)lpMsg;
	memcpy(this->ItemChinh, mRecv->ItemChinh, sizeof(this->ItemChinh));
	memcpy(this->ItemPhu, mRecv->ItemPhu, sizeof(this->ItemPhu));
	for (int n = 0; n < 6; n++)
	{
		memcpy(this->ItemKetQua[n], mRecv->ItemKetQua[n], sizeof(this->ItemKetQua[n]));
	}
	this->WCoinC 			= mRecv->WCoinC ;
	this->WCoinP 			= mRecv->WCoinP ;
	this->WCoinG 			= mRecv->WCoinG ;
	this->CoinAtm			= mRecv->CoinAtm;
	this->ActiveMix			= mRecv->ActiveMix;
	this->EffectsMix	= false;
}
void TAS_NPC_TRADER::DrawInfoItemSet()
{
	if (*(DWORD*)(MAIN_SCREEN_STATE) == ObjState::GameProcess)
	{
		if (BCacheInfoItemDD && CacheTimeShowInfoItem > GetTickCount())
		{
			JCCoord JCShowSellItem;
			JCShowSellItem.X = pCursorX + 50;
			JCShowSellItem.Y = pCursorY;
			pSetBlend(true);
			glColor3f(1.0, 1.0, 1.0);
			sub_7E3E30(*(DWORD*)(GetInstance() + 308), JCShowSellItem, (int)BCacheInfoItemDD, 0, 0, 0);
			pGLSwitch();
			pSetBlend(false);
		}
		else if (BCacheInfoItemDD)
		{
			BCacheInfoItemDD = nullptr;
		}
	}
}

void TAS_NPC_TRADER::BackDoiItem(int Type)
{
	if ((GetTickCount() - gInterface.Data[eWindowDoiItem].EventTick) > 300)
	{
		XULY_CGPACKET pMsg;
		pMsg.header.set(0xD3, 0x6C, sizeof(pMsg));
		pMsg.ThaoTac = Type; //
		DataSend((LPBYTE)&pMsg, pMsg.header.size);
		gInterface.Data[eWindowDoiItem].EventTick = GetTickCount();
	}
}
void TAS_NPC_TRADER::DrawItemSlotSelect(float X, float Y, float W, float H, BYTE ItemSlot)
{
	if (DoiItem == ItemSlot)
	{
		gCentral.gInfoBox(X, Y + 2, W + 18, 72, 0x26E0A596, 0, 0);
	}

	gCentral.gItemBoxInv( X, Y, 4, 3, 0);

	ObjectItem* SecondItemSlot = &*(ObjectItem*)(BPConvertByteItem(*(DWORD*)(GetInstance() + 36), this->ItemKetQua[ItemSlot - 1]));
	if (SecondItemSlot->ItemID > 0)
	{
		gCBUtil.DrawItem3D((X + 20) , (Y + 20) + 9, W, H, SecondItemSlot->ItemID, SecondItemSlot->Level, SecondItemSlot->ExcellentOption, SecondItemSlot->AncientOption, 0, 1.4);
		
		if (pCheckMouseOver(X, Y, W + 18, 80) == 1)
		{
			BCacheInfoItemDD = SecondItemSlot;
			CacheTimeShowInfoItem = GetTickCount() + 50;
			if (GetKeyState(VK_LBUTTON) & 0x8000)
			{
				DoiItem = ItemSlot;
			}
		}
	}
}

void TAS_NPC_TRADER::DrawItemSlotToolTip(float X, float Y, float W, float H, BYTE ItemSlot)
{
	ObjectItem* SecondItemSlot = &*(ObjectItem*)(BPConvertByteItem(*(DWORD*)(GetInstance() + 36), this->ItemKetQua[ItemSlot - 1]));
	if (SecondItemSlot->ItemID > 0)
	{
		if (pCheckMouseOver(X, Y, W + 18, 80) == 1)
		{
			JCCoord mousePosition;
			mousePosition.X = pCursorX + 50;
			mousePosition.Y = pCursorY;
			pSetBlend(true);
			glColor3f(1.0, 1.0, 1.0);
			sub_7E3E30(*(DWORD*)(GetInstance() + 308), mousePosition, (int)SecondItemSlot, 0, 0, 0);
			pGLSwitch();
			pSetBlend(false);
		}
	}
}
void CheckCoinItem(int Coin, float X, float Y, LPCSTR Text)
{
	if (Coin > 0)
	{
		gInterface.DrawFormat(eWhite, X, Y, 100, 0, Text);
		gInterface.DrawFormat(MauVangCam, X + 47, Y, 65, 4, "-%s", gToolKit.NumberFormat(Coin));
	}
	else
	{
		gInterface.DrawFormat(eGray100, X, Y, 100, 0, Text);
		gInterface.DrawFormat(MauVangCam, X + 47, Y, 65, 4, "%s", gToolKit.NumberFormat(Coin));
	}
}
void TAS_NPC_TRADER::HienThiItemTrade()
{
	if (gInterface.CheckWindow(SkillTree) || gInterface.CheckWindow(Shop) || gInterface.CheckWindow(CreateGuild) || gInterface.CheckWindow(ChatWindow) || gInterface.CheckWindow(FriendList) || gInterface.CheckWindow(MuHelper) || gInterface.CheckWindow(Store) || gInterface.CheckWindow(Warehouse) || gInterface.CheckWindow(Trade) || gInterface.CheckWindow(CashShop) || gInterface.CheckWindow(GuardNPC))
	{
		return;
	}
	gInterface.CloseCustomWindow();
	gInterface.OpenWindow(Inventory);
	gInterface.CloseWindow(Character);
}
void TAS_NPC_TRADER::DrawDoiItem()
{
	if (!gInterface.Data[eWindowDoiItem].OnShow)
	{
		if (this->SetStateDoiItem == 1)
		{
			XULY_CGPACKET pMsg;
			pMsg.header.set(0xD3, 0x6A, sizeof(pMsg));
			pMsg.ThaoTac = 111;
			DataSend((LPBYTE)&pMsg, pMsg.header.size);
			this->SetStateDoiItem = false;
			this->EffectsMix = false;
			this->ActiveMix = false;
			this->WCoinC = false;
			this->WCoinP = false;
			this->WCoinG = false;
			this->CoinAtm = false;
			this->RunCheckMe = false;
			DoiItem = -1;
		}
		return;
	}
	else
	{
		gOffTrade.CGSendOffTrade(7);
		if (!RunCheckMe)
		{
			this->HienThiItemTrade();
			RunCheckMe = true;
		}
		if (pCheckWindow(pWindowThis(), Inventory) == false)
		{
			gInterface.Data[eWindowDoiItem].OnShow = false;
		}
	}
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	float StartX = JCResto+101;
	float StartY = 0;
	float WindowW = 350;
	float WindowH = 263;
	int CheckItemOK = 0;
	pSetCursorFocus = true;
	gCentral.gDrawWindowCustom(StartX, StartY, WindowW, WindowH, eWindowDoiItem, gConfig.TTAS_TEXT_ENGINE[314]);
	gToolKit.CloseButton(417, 0, TAS_ItemTrade_BtnClose);
	if (pCheckMouseOver(417 + 10, 0 + 6, 15, 15) == 1)
	{
		if (pIsKeyPress(VK_LBUTTON) && GetTickCount() - this->ClickTime > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				gCentral.LockMouse = GetTickCount() + 500;
				this->ClickTime = GetTickCount();
				gInterface.Data[eWindowDoiItem].OnShow = false;
			}
		}
	}
	float BoxItemWH = 35;
	//===Item Chinh
	float PosXGroup1 = StartX + 20;
	float PosYGroup1 = StartY + 40;
	float PosYGroup2 = PosYGroup1 + 85;
	float PosYGroup3 = PosYGroup2 + 85;

	gCentral.gInfoBox(PosXGroup1 - 10,  PosYGroup1 - 5, 120, 110, 0x00000096, 0, 0);
	gCentral.gInfoBox(PosXGroup1 - 10,  PosYGroup1 + 116, 120, 89, 0x00000096, 0, 0);

	gCentral.gInfoBox(PosXGroup1 + 120, PosYGroup1 - 5, 190, 210, 0x00000096, 0, 0);

	CustomFont.Draw((HFONT)pFontBold, PosXGroup1 - 8, PosYGroup1 - 5, 0xEBA000FF, 0x00FBFF69, 124, 0, 3, gConfig.TTAS_TEXT_ENGINE[315]);//
	gCentral.gItemBoxInv(PosXGroup1 + ((WindowW - 40) / 2) - (BoxItemWH / 2) - 127, PosYGroup1 + 20, 4, 4, 0);

	ObjectItem* CTItemChinh = &*(ObjectItem*)(BPConvertByteItem(*(DWORD*)(GetInstance() + 36), this->ItemChinh));
		
	this->DrawItemSlotSelect(PosXGroup1 + ((WindowW - 40) / 2) - (BoxItemWH / 2) - 13,	PosYGroup1 + 0,BoxItemWH, BoxItemWH,1);
	this->DrawItemSlotSelect(PosXGroup1 + ((WindowW - 40) / 2) - (BoxItemWH / 2) + 52,	PosYGroup1 + 0,BoxItemWH, BoxItemWH,2);
	this->DrawItemSlotSelect(PosXGroup1 + ((WindowW - 40) / 2) - (BoxItemWH / 2) + 117,	PosYGroup1 + 0,BoxItemWH, BoxItemWH,3);
	this->DrawItemSlotSelect(PosXGroup1 + ((WindowW - 40) / 2) - (BoxItemWH / 2) - 13,	PosYGroup1 + 85,BoxItemWH, BoxItemWH,4);
	this->DrawItemSlotSelect(PosXGroup1 + ((WindowW - 40) / 2) - (BoxItemWH / 2) + 52,	PosYGroup1 + 85,BoxItemWH, BoxItemWH,5);
	this->DrawItemSlotSelect(PosXGroup1 + ((WindowW - 40) / 2) - (BoxItemWH / 2) + 117,	PosYGroup1 + 85,BoxItemWH, BoxItemWH,6);
		
	float PosYTextInfo = PosYGroup3 + 0;

	CustomFont.Draw((HFONT)pFontBold, PosXGroup1 - 8, PosYTextInfo - 53, 0xFFFFFFFF, 0x00FBFF69, 124, 0, 3, gConfig.TTAS_TEXT_ENGINE[316]);//

	CheckCoinItem(this->WCoinC,		PosXGroup1, PosYTextInfo - 35, gConfig.TTAS_TEXT_ENGINE[10]);
	CheckCoinItem(this->WCoinP,		PosXGroup1, PosYTextInfo - 25, gConfig.TTAS_TEXT_ENGINE[11]);
	CheckCoinItem(this->WCoinG,		PosXGroup1, PosYTextInfo - 15, gConfig.TTAS_TEXT_ENGINE[9]);
	CheckCoinItem(this->CoinAtm,	PosXGroup1, PosYTextInfo - 5, gConfig.TTAS_TEXT_ENGINE[12]);

	if (gCentral.gDrawButton(PosXGroup1 - 4, PosYGroup1 + 180, 115, Main_Font_Height, gConfig.TTAS_TEXT_ENGINE[317]))
	{
		PlayBuffer(25, 0, 0);
		BackDoiItem(DoiItem);
		DoiItem = -1;
		gInterface.Data[eWindowDoiItem].OnShow ^= 1;
	}

	gInterface.DrawFormat(eWhite, PosXGroup1 + 121, PosYGroup1 + 180, 194, 3, "Hãy chọn một item mới để tiến hành giao dịch!");

	this->DrawItemSlotToolTip(PosXGroup1 + ((WindowW - 40) / 2) - (BoxItemWH / 2) - 13, PosYGroup1 + 0, BoxItemWH, BoxItemWH, 1);
	this->DrawItemSlotToolTip(PosXGroup1 + ((WindowW - 40) / 2) - (BoxItemWH / 2) + 52, PosYGroup1 + 0, BoxItemWH, BoxItemWH, 2);
	this->DrawItemSlotToolTip(PosXGroup1 + ((WindowW - 40) / 2) - (BoxItemWH / 2) + 117, PosYGroup1 + 0, BoxItemWH, BoxItemWH, 3);
	this->DrawItemSlotToolTip(PosXGroup1 + ((WindowW - 40) / 2) - (BoxItemWH / 2) - 13, PosYGroup1 + 85, BoxItemWH, BoxItemWH, 4);
	this->DrawItemSlotToolTip(PosXGroup1 + ((WindowW - 40) / 2) - (BoxItemWH / 2) + 52, PosYGroup1 + 85, BoxItemWH, BoxItemWH, 5);
	this->DrawItemSlotToolTip(PosXGroup1 + ((WindowW - 40) / 2) - (BoxItemWH / 2) + 117, PosYGroup1 + 85, BoxItemWH, BoxItemWH, 6);

	if (CTItemChinh->ItemID > 0)
	{
		gCBUtil.DrawItem3D((PosXGroup1 + ((WindowW - 40) / 2) - (BoxItemWH / 2) + 7) - 112, (PosYGroup1 + 20) + 25, BoxItemWH, BoxItemWH, CTItemChinh->ItemID, CTItemChinh->Level, CTItemChinh->ExcellentOption, CTItemChinh->AncientOption, 0, 1.4);//BMD MOdel
		if (pCheckMouseOver(PosXGroup1 + ((WindowW - 40) / 2) - (BoxItemWH / 2) - 112, (PosYGroup1 + 20) + 25, 50, 50) == 1)
		{
			BCacheInfoItemDD = CTItemChinh;
			CacheTimeShowInfoItem = GetTickCount() + 50;
			if (GetKeyState(VK_RBUTTON) & 0x8000)
			{
				BackDoiItem(0);
			}
			JCCoord mousePosition;	
			mousePosition.X = pCursorX + 50;
			mousePosition.Y = pCursorY;
			pSetBlend(true);
			glColor3f(1.0, 1.0, 1.0);
			sub_7E3E30(*(DWORD*)(GetInstance() + 308), mousePosition, (int)CTItemChinh, 0, 0, 0);
			pGLSwitch();
			pSetBlend(false);
		}
	}
}
#endif