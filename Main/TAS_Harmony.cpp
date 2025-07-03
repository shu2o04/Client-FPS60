#include "stdafx.h"
#if (CUSTOM_HARMONY)
#include "TAS_Harmony.h"
#include "MemScript.h"
#include "Util.h"
#include "Interface.h"
#include "Central.h"
#include "Defines.h"
#include "InterfaceElemental.h"
#include "User.h"
#include "CBUtil.h"
#include "TAS_ToolKit.h"
#include "PrintPlayer.h"
#include "CustomFont.h"
#include "TAS_ItemTrader.h"
#include "OffTrade.h"
CustomHarmony gCustomHarmony;

extern void* BCacheInfoItemDD;
extern DWORD CacheTimeShowInfoItem;
DWORD HarmonyEffect = 0;

CustomHarmony::CustomHarmony()
{
	this->Init();
}

void CustomHarmony::Init()
{
	this->m_HarmonyInfoList.clear();
	this->Harmony_ActiveMix = false;
	this->Harmony_EffectsMix = false;
	this->SetStateHarmony = false;
	this->Rate = 100;
	this->Price = 0;
	this->PriceType = -1;
	this->CountHarmony = 0;
	this->IndexRandom = -1;
	memset(this->ItemChuaEp, 0, sizeof(this->ItemChuaEp));
}

char* CustomHarmony::GetNamePrice()
{
	switch (this->PriceType)
	{
		case 1:		return "WC";		break;
		case 2:		return "WP";		break;
		case 3:		return "GP";		break;
	}
	return "Zen";
}

void BackItemHarmony(int Type)
{
	if ((GetTickCount() - gInterface.Data[eWindowHarmony].EventTick) > 300)
	{
		XULY_CGPACKET pMsg;
		pMsg.header.set(0xD5, 0x2C, sizeof(pMsg));
		pMsg.ThaoTac = Type; //
		DataSend((LPBYTE)&pMsg, pMsg.header.size);
		gInterface.Data[eWindowHarmony].EventTick = GetTickCount();
	}
}
void CustomHarmony::HienThiItem()
{
	if (gInterface.CheckWindow(SkillTree) || gInterface.CheckWindow(Shop) || gInterface.CheckWindow(CreateGuild) || gInterface.CheckWindow(ChatWindow) || gInterface.CheckWindow(FriendList) || gInterface.CheckWindow(MuHelper) || gInterface.CheckWindow(Store) || gInterface.CheckWindow(Warehouse) || gInterface.CheckWindow(Trade) || gInterface.CheckWindow(CashShop) || gInterface.CheckWindow(GuardNPC))
	{
		return;
	}
	gInterface.CloseCustomWindow();
	gInterface.OpenWindow(Inventory);
	gInterface.CloseWindow(Character);
}
void CustomHarmony::DrawHarmony()
{
	if (CheckTAS_WINDOWS3)
	{
		if (gInterface.Data[eWindowHarmony].OnShow == true)
		{
			gInterface.Data[eWindowHarmony].OnShow = false;
			pSetCursorFocus = false;
			return;
		}
	}

	if (!gInterface.Data[eWindowHarmony].OnShow)
	{
		if (gCustomHarmony.SetStateHarmony == 1)
		{
			XULY_CGPACKET pMsg;
			pMsg.header.set(0xD5, 0x2A, sizeof(pMsg));
			pMsg.ThaoTac = 111;
			DataSend((LPBYTE)&pMsg, pMsg.header.size);
			this->SetStateHarmony = false;
			this->Harmony_ActiveMix = false;
			this->Harmony_EffectsMix = false;
			this->RunCheckMe = false;
		}
		return;
	}
	else
	{
		gOffTrade.CGSendOffTrade(7);
		if (!RunCheckMe)
		{
			this->HienThiItem();
			this->RunCheckMe = true;
		}
		if (pCheckWindow(pWindowThis(), Inventory) == false)
		{
			gInterface.Data[eWindowHarmony].OnShow = false;
		}
	}
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	float StartX = JCResto+222;
	float StartY = 0;
	float WindowW = 228.0f;
	float WindowH = 190.0f;

	gCentral.gDrawWindowCustom(StartX, StartY, WindowW, WindowH, eWindowHarmony, "CƯỜNG HÓA DÒNG VÀNG");
	gToolKit.CloseButton(417, StartY, TAS_Harmony_BtnClose);
	if (pCheckMouseOver(417 + 10, StartY + 6, 15, 15) == 1)
	{
		if (pIsKeyPress(VK_LBUTTON) && GetTickCount() - this->ClickTime > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				gCentral.LockMouse = GetTickCount() + 500;
				this->ClickTime = GetTickCount();
				gInterface.Data[eWindowHarmony].OnShow = false;
			}
		}
	}

	gCentral.gItemBoxInv(StartX + 15, StartY + 65, 4, 2, 0);
	gCentral.gItemBoxInv(StartX + 170, StartY + 65, 4, 2, 0);
	gInterface.DrawFormat(eWhite, StartX + 3, StartY + 50, 65, 3, "Item Gốc");
	gInterface.DrawFormat(eWhite, StartX + 158, StartY + 50, 65, 3, "Ngọc Tạo Hóa");
	gCBUtil.DrawItem3D(StartX + 165, StartY + 60, 50, 50, 7210, 0, 0, 0, 0, 0.80);
	gToolKit.CRenderNumberEx(StartX + 195, StartY + 107, this->CountHarmony, 0.90, 0x7A69);
	gInterface.DrawFormat(eWhite, StartX + 60, StartY + 90, 65, 1, "Kết quả:");
	CustomFont.Draw((HFONT)pFontBold, StartX + 60, StartY + 100, 0x0, 0x00000069, 105, 30, 3, " ");
	gInterface.DrawFormat(eGold, StartX + 60, StartY + 65, 200, 1, "Giá cường hóa: %s %s / lần", gToolKit.QNumberFormat(this->Price), this->GetNamePrice());
	
	if (Coin1 >= this->Price)
	{
		gInterface.DrawFormat(eGold, StartX + 60, StartY + 77, 200, 1, "WcoinC hiện tại: %s WC", gToolKit.QNumberFormat(Coin1));
	}
	else
	{
		int CalcCoin = this->Price - Coin1;
		gInterface.DrawFormat(eRed, StartX + 60, StartY + 77, 200, 1, "WC hiện tại: %s WC => [-%s WC]", gToolKit.QNumberFormat(Coin1), gToolKit.QNumberFormat(CalcCoin));
	}
	
	if (this->Harmony_EffectsMix && HarmonyEffect > GetTickCount() && HarmonyEffect != 0 && Coin1 >= this->Price)
	{
		gToolKit.RenderMixEffect(this->Harmony_EffectsMix, StartX + 20, StartY + 70, 2, 4);
		gInterface.DrawFormat(eWhite, StartX + 57, StartY + 104, 113, 3, "Đang ép đá, vui lòng chờ...");
	}
	else if (Coin1 < this->Price)
	{
		gInterface.DrawFormat(eRed, StartX + 57, StartY + 104, 113, 3, "KHÔNG ĐỦ COIN ĐỂ ÉP!");
	}
	else if (HarmonyEffect != 0)
	{
		HarmonyEffect = 0;
		if (this->Harmony_ActiveMix)
		{
			if ((GetTickCount() - gInterface.Data[eWindowHarmony].EventTick) > 300 && HarmonyEffect == 0)
			{
				XULY_CGPACKET pMsg;
				pMsg.header.set(0xD5, 0x2D, sizeof(pMsg));
				pMsg.ThaoTac = 113; //
				DataSend((LPBYTE)&pMsg, pMsg.header.size);
				gInterface.Data[eWindowHarmony].EventTick = GetTickCount();
			}
		}
	}

	if (this->IndexRandom != -1)
	{
		gInterface.DrawFormat(eExcellent, StartX + 57, StartY + 115, 113, 3, "%s", m_HarmonyInfoList[this->IndexRandom].Name);
	}
	gInterface.DrawFormat(eExcellent, StartX + 10, StartY + 157, 218, 3, "Bấm nút NHẬN để nhận lại vật phẩm đã nâng cấp.");
	gInterface.DrawFormat(eExcellent, StartX + 10, StartY + 168, 218, 3, "Click phải vào món đồ để trả lại item trước đó!");

	if (gElemental.gDrawButton(StartX + 60, StartY + 132, 70, 12, "Xoay", 40))
	{
		if (this->Harmony_ActiveMix)
		{
			this->Harmony_EffectsMix = 1;
		}
		else
		{
			gElemental.OpenMessageBox("Lỗi", "Kiểm tra lại vật phẩm!");
		}
		HarmonyEffect = GetTickCount() + 2000;
		this->IndexRandom = -1;
	}

	if (gElemental.gDrawButton(StartX + 125, StartY + 132, 70, 12, "Nhận", 40))
	{
		BackItemHarmony(4);
	}

	if (pCheckMouseOver(StartX + 170, StartY + 80, 40, 40) == 1)
	{
		CustomFont.Draw((HFONT)pFontBold, (StartX + pCursorX) - 260, (StartY + pCursorY) + 10, 0x0, 0x000000A9, 80, 40, 3, " ");
		gInterface.DrawFormat(eGold,  (StartX + pCursorX) - 260, (StartY + pCursorY) + 13, 80, 3, "Đá Tạo Hóa");
		gInterface.DrawFormat(eWhite, (StartX + pCursorX) - 260, (StartY + pCursorY) + 25, 80, 3, "Ngọc gia cường món đồ");
		gInterface.DrawFormat(eWhite, (StartX + pCursorX) - 260, (StartY + pCursorY) + 37, 80, 3, "Số lượng còn lại là: x%d", this->CountHarmony);
	}
	ObjectItem* CTItemChinh = &*(ObjectItem*)(BPConvertByteItem(*(DWORD*)(GetInstance() + 36), gCustomHarmony.ItemChuaEp));
	if (CTItemChinh->ItemID > 0)
	{
		gCBUtil.DrawItem3D(StartX + 10, StartY + 78, 50, 50, CTItemChinh->ItemID, CTItemChinh->Level, CTItemChinh->ExcellentOption, CTItemChinh->AncientOption, 0, 1.0);//BMD MOdel
		if (pCheckMouseOver(StartX + 10 + 7, StartY + 68, 40, 80) == 1)
		{
			BCacheInfoItemDD = CTItemChinh;
			CacheTimeShowInfoItem = GetTickCount() + 50;
			if (GetKeyState(VK_RBUTTON) & 0x8000)
			{
				BackItemHarmony(0);
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

void CustomHarmony::RecvHarmony(CHCSEV_COUNTLIST* lpMsg) // OK
{
	m_HarmonyInfoList.clear();

	for (int n = 0; n < lpMsg->Count; n++)
	{
		OptionItemHarm* lpInfo = (OptionItemHarm*)(((BYTE*)lpMsg) + sizeof(CHCSEV_COUNTLIST)+(sizeof(OptionItemHarm)* n));
		m_HarmonyInfoList.push_back(*lpInfo);
	}
}
#endif