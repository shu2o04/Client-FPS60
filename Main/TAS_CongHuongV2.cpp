#include "stdafx.h"
#include "Import.h"
#include "Central.h"
#include "TAS_CongHuongV2.h"
#include "Interface.h"
#include "Defines.h"
#include "CustomFont.h"
#include "postInterface.h"
#include "User.h"
#include "Util.h"
#include "Config.h"
#include "TAS_ToolKit.h"
#include "OffTrade.h"
#if (CongHuongV2)
#define BPConvertByteItem ((int (__thiscall*)(int a1, void *lp)) 0x7E1B10)
#define BPDrawInfoItem			((signed int (__thiscall*)(int a1, JCCoord a5, int a6, int a7, int a8, int a9)) 0x007E3E30)
#define pIsKeyRepeat	((bool(*)(int))0x00791090)
int mViTriScroll = 0;
CongHuongV2New gCongHuong2;

void CongHuongV2New::XoaDataCongHuong()
{

	this->m_ScrollPos = 0;
	this->CH_EffectMixOn = 0;
	this->CH_TyLeThanhCong = -1;
	this->CH_ResetMix = -1;
	this->CH_TypeMix = -1;
	this->CH_CheckLvItem = 0;
	for (int n = 0; n < 3; n++)
	{
		this->CH_IndexItem[n] = -1;
		this->CH_CoinMix[n] = -1;
		ZeroMemory(this->CH_InfoItem[n], sizeof(this->CH_InfoItem[n]));
	}
	XULY_CGPACKET pMsg;
	pMsg.header.set(0xFA, 0x16, sizeof(pMsg));
	pMsg.ThaoTac = 0;
	DataSend((LPBYTE)&pMsg, pMsg.header.size);
}

void CongHuongV2New::EventScrollPos(MOUSEHOOKSTRUCTEX* Mouse, WPARAM wParam) //Load Cac Cua So Custom
{
	if (gInterface.Data[eWindow_CongHuong].OnShow == 1 && gInterface.IsWorkZone2(5 + 190, 45 + 35, 140, 295))
	{
		if (wParam == WM_MOUSEWHEEL)
		{
			if ((int)Mouse->mouseData > 0)
			{
				if (this->m_ScrollPos > 0)
				{
					this->m_ScrollPos--;
				}
			}

			if ((int)Mouse->mouseData < 0)
			{
				if (this->m_ScrollPos < gItemManager.GetCountPhoiCongHuong(this->CH_IndexItem[0], this->CH_TypeMix) && mViTriScroll < 245)
				{
					this->m_ScrollPos++;
				}
			}
			return;
		}
	}
}
void CongHuongV2New::HienThiItem()
{
	if (gInterface.CheckWindow(SkillTree) || gInterface.CheckWindow(Shop) || gInterface.CheckWindow(CreateGuild) || gInterface.CheckWindow(ChatWindow) || gInterface.CheckWindow(FriendList) || gInterface.CheckWindow(MuHelper) || gInterface.CheckWindow(Store) || gInterface.CheckWindow(Warehouse) || gInterface.CheckWindow(Trade) || gInterface.CheckWindow(CashShop) || gInterface.CheckWindow(GuardNPC))
	{
		return;
	}
	gInterface.CloseCustomWindow();
	gInterface.OpenWindow(Inventory);
	gInterface.CloseWindow(Character);
}
void CongHuongV2New::DrawWindowCongHuong()
{
	if (!gInterface.Data[eWindow_CongHuong].OnShow)
	{
		if (this->CH_IndexItem[0] != -1 || this->CH_IndexItem[1] != -1 || this->CH_IndexItem[2] != -1)
		{
			this->XoaDataCongHuong();
		}
		this->RunCheckMe = false;
		return;

	}
	else
	{
		gOffTrade.CGSendOffTrade(7);
		if (!this->RunCheckMe)
		{
			this->HienThiItem();
			this->RunCheckMe = true;
		}
		if (pCheckWindow(pWindowThis(), Inventory) == false)
		{
			gInterface.Data[eWindow_CongHuong].OnShow = false;
		}
	}
	//gInterface.OpenWindow(ObjWindow::Inventory);
	pSetCursorFocus = true;
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	float CuaSoW = 340;
	float CuaSoH = 345;
	float StartX = JCResto+115;
	float StartY = 45.0;
	int GetInfoLoadItem = 0;

	pSetBlend(true);
	gCentral.gDrawWindowCustom(StartX - 5, StartY, CuaSoW, CuaSoH, eWindow_CongHuong, gConfig.TTAS_TEXT_ENGINE[193]);

	gCentral.gInfoBox(StartX + 7, StartY + 35, 170, 130, 0x00000096, 0, 0);
	CustomFont.Draw(CustomFont.FontNormal, StartX + 7, StartY + 39, 0xFFFFFFFF, 0x0, 170, 0, 3, gConfig.TTAS_TEXT_ENGINE[194]);
	gCentral.gItemBoxInv(StartX + 12, StartY + 55, 4, 2, (this->CH_IndexItem[0] > -1) ? 1 : 0);
	gCentral.gItemBoxInv(StartX + 12 + 50, StartY + 55, 4, 2, (this->CH_IndexItem[1] > -1) ? 1 : 0); 
	pDrawButton(31538, StartX + 12 + 50 + 45, StartY + 90, 15.0, 7.0, 13.0, 0); 
	gCentral.gItemBoxInv(StartX + 12 + 50 + 45 + 20, StartY + 55, 4, 2, (this->CH_IndexItem[2] > -1) ? 1 : 0);
	CustomFont.Draw(CustomFont.FontNormal, StartX + 12, StartY + 55 + (21 * 4), 0xFFFFFFFF, 0x0, 45, 0, 3, gConfig.TTAS_TEXT_ENGINE[195]);
	CustomFont.Draw(CustomFont.FontNormal, StartX + 12, StartY + 55 + (21 * 4) + 10, ((this->CH_IndexItem[0] > -1) ? 0x2B8EFFFF : 0xDE1616FF), 0x0, 45, 0, 3, "%d/1", (this->CH_IndexItem[0] > -1) ? 1 : 0); //

	if (this->CH_IndexItem[0] != -1)
	{
		GetInfoLoadItem = BPConvertByteItem(*(DWORD*)(GetInstance() + 36), this->CH_InfoItem[0]);
		gPostInterface.DrawItemIMG(StartX + 12, StartY + 22, (21 * 2), (21 * 4), *(WORD*)GetInfoLoadItem, *(DWORD*)(GetInfoLoadItem + 2), *(BYTE*)(GetInfoLoadItem + 23), *(BYTE*)(GetInfoLoadItem + 24), 0);
	}
	if (this->CH_IndexItem[1] != -1)
	{
		GetInfoLoadItem = BPConvertByteItem(*(DWORD*)(GetInstance() + 36), this->CH_InfoItem[1]);
		gPostInterface.DrawItemIMG(StartX + 12 + 50, StartY + 22, (21 * 2), (21 * 4), *(WORD*)GetInfoLoadItem, *(DWORD*)(GetInfoLoadItem + 2), *(BYTE*)(GetInfoLoadItem + 23), *(BYTE*)(GetInfoLoadItem + 24), 0);
	}
	CustomFont.Draw(CustomFont.FontNormal, StartX + 12 + 50, StartY + 55 + (21 * 4), 0xFFFFFFFF, 0x0, 45, 0, 3, gConfig.TTAS_TEXT_ENGINE[196]);
	CustomFont.Draw(CustomFont.FontNormal, StartX + 12 + 50, StartY + 55 + (21 * 4) + 10, ((this->CH_IndexItem[1] > -1) ? 0x2B8EFFFF : 0xDE1616FF), 0x0, 45, 0, 3, "%d/1", (this->CH_IndexItem[1] > -1) ? 1 : 0); //


	CustomFont.Draw(CustomFont.FontNormal, StartX + 12 + 50 + 45 + 20, StartY + 55 + (21 * 4), 0xFFFFFFFF, 0x0, 45, 0, 3, gConfig.TTAS_TEXT_ENGINE[197]);
	if (this->CH_IndexItem[2] != -1)
	{
		GetInfoLoadItem = BPConvertByteItem(*(DWORD*)(GetInstance() + 36), this->CH_InfoItem[2]);
		gPostInterface.DrawItemIMG(StartX + 12 + 50 + 45 + 20, StartY + 22, (21 * 2), (21 * 4), *(WORD*)GetInfoLoadItem, *(DWORD*)(GetInfoLoadItem + 2), *(BYTE*)(GetInfoLoadItem + 23), *(BYTE*)(GetInfoLoadItem + 24), 0);
	}
	gCentral.gInfoBox(StartX + 190, StartY + 35, 120, 295, 0x00000096, 0, 0);
	CustomFont.Draw(CustomFont.FontBold, StartX + 195, StartY + 40, 0xFFBA19FF, 0x0, 90, 0, 1, gConfig.TTAS_TEXT_ENGINE[198]);
	int iMaxScrollCount = 0;
	int CountItem = 0;
	if (this->CH_IndexItem[0] != -1)
	{
		std::map<int, ITEM_INFO>::iterator itemgoc = gItemManager.m_ItemInfo.find(this->CH_IndexItem[0]);

		if (itemgoc != gItemManager.m_ItemInfo.end())
		{
			for (std::map<int, ITEM_INFO>::iterator it = gItemManager.m_ItemInfo.begin(); it != gItemManager.m_ItemInfo.end(); it++)
			{
				if (it == gItemManager.m_ItemInfo.end() || (CountItem - this->m_ScrollPos) > 20)
				{
					break;
				}
				if ((it->second.ItemIndex / 512) == (itemgoc->second.ItemIndex / 512))
				{
					if (it->second.Level >= (itemgoc->second.Level) && this->CH_TypeMix == 1)
					{
						iMaxScrollCount++;
					}
					else if (this->CH_TypeMix == 0)
					{
						iMaxScrollCount++;
					}
					else if (this->CH_TypeMix == 2 && itemgoc->second.ItemIndex == it->second.ItemIndex)
					{
						iMaxScrollCount++;
					}
					else {
						continue;
					}
					if (iMaxScrollCount < this->m_ScrollPos)
					{
						continue;
					}

					CustomFont.Draw(CustomFont.FontNormal, StartX + 195, StartY + 55 + (13 * CountItem), 0x2B8EFFFF, 0x0, 120, 0, 1, "- %s", it->second.Name); //
					CountItem++;

				}
				if (CountItem >= 21)
				{
					break;
				}

			}
		}
	}
	else
	{
		CustomFont.Draw(CustomFont.FontNormal, StartX + 195, StartY + 55 + (13 * CountItem), 0xDE1616FF, 0x0, 120, 0, 1, gConfig.TTAS_TEXT_ENGINE[199]); //
	}
	float flScrollDiv = 0;

	if (gItemManager.GetCountPhoiCongHuong(this->CH_IndexItem[0], this->CH_TypeMix) > 0)
	{
		flScrollDiv = (10 * 30) / gItemManager.GetCountPhoiCongHuong(this->CH_IndexItem[0], this->CH_TypeMix);	//
	}
	pDrawButton(0x7A29, StartX + 310, StartY + 55 + (this->m_ScrollPos * flScrollDiv), 15, 30, 0, 0); //Scroll
	mViTriScroll = (int)(this->m_ScrollPos * flScrollDiv);
	if (pCheckMouseOver(StartX + 310, StartY + 55 + (this->m_ScrollPos * flScrollDiv), 15, 30) == 1)
	{
		if (pIsKeyPress(VK_LBUTTON) && GetTickCount() - gInterface.Data[eWindow_CongHuong].EventTick > 10)
		{
			PlayBuffer(25, 0, 0);
			glColor3f(1.0f, 0.0f, 0.0f);
			gInterface.Data[eWindow_CongHuong].EventTick = GetTickCount();
		}
		else if (pIsKeyRepeat(VK_LBUTTON))
		{
			int mSrollY = (int)(StartY + 55 + (this->m_ScrollPos * flScrollDiv) + 15);
			if ((pCursorY - mSrollY) > 5 && this->m_ScrollPos < gItemManager.GetCountPhoiCongHuong(this->CH_IndexItem[0], this->CH_TypeMix) && mViTriScroll < 245)
			{
				this->m_ScrollPos++;
			}
			else if ((mSrollY - pCursorY) > 5 && this->m_ScrollPos > 0)
			{
				this->m_ScrollPos--;
			}

		}

		pDrawColorButton(0x7A29, StartX + 310, StartY + 55 + (this->m_ScrollPos * flScrollDiv), 15, 30, 0, 0, pMakeColor(255, 204, 20, 130));
		gInterface.DrawToolTip(gObjUser.m_CursorX + 20, gObjUser.m_CursorY, "Scroll");
	}

	gCentral.gInfoBox(StartX + 7, StartY + 46 + 130, 170, 100, 0x00000096, 0, 0);
	CustomFont.Draw(CustomFont.FontNormal, StartX + 15, StartY + 180, 0xFFFFFFFF, 0x0, (170 / 2), 0, 1, gConfig.TTAS_TEXT_ENGINE[200]);
	if (this->CH_TyLeThanhCong == -1)
	{
		CustomFont.Draw(CustomFont.FontNormal, StartX + 20 + (170 / 2), StartY + 180, 0xDE1616FF, 0x0, 0, 0, 1, gConfig.TTAS_TEXT_ENGINE[199]);
	}
	else
	{
		CustomFont.Draw(CustomFont.FontNormal, StartX + 20 + (170 / 2), StartY + 180, 0x19FF9FFF, 0x0, 0, 0, 1, "%d %%", this->CH_TyLeThanhCong);
	}
	CustomFont.Draw(CustomFont.FontNormal, StartX + 15, StartY + 180 + 13, 0xFFFFFFFF, 0x0, (170 / 2), 0, 1, gConfig.TTAS_TEXT_ENGINE[202]);
	if (this->CH_ResetMix == -1)
	{
		CustomFont.Draw(CustomFont.FontNormal, StartX + 20 + (170 / 2), StartY + 180 + 13, 0xDE1616FF, 0x0, 0, 0, 1, gConfig.TTAS_TEXT_ENGINE[199]);
	}
	else
	{
		CustomFont.Draw(CustomFont.FontNormal, StartX + 20 + (170 / 2), StartY + 180 + 13, 0x19FF9FFF, 0x0, 0, 0, 1, "%d (RS)", this->CH_ResetMix);
	}
	CustomFont.Draw(CustomFont.FontNormal, StartX + 15, StartY + 180 + 26, 0xFFFFFFFF, 0x0, (170 / 2), 0, 1, gConfig.TTAS_TEXT_ENGINE[204]);
	if (this->CH_TypeMix == -1)
	{
		CustomFont.Draw(CustomFont.FontNormal, StartX + 20 + (170 / 2), StartY + 180 + 26, 0xDE1616FF, 0x0, 0, 0, 1, gConfig.TTAS_TEXT_ENGINE[199]);
	}
	else
	{
		CustomFont.Draw(CustomFont.FontNormal, StartX + 20 + (170 / 2), StartY + 180 + 26, 0x19FF9FFF, 0x0, 0, 0, 1, "%s", "");
	}
	CustomFont.Draw(CustomFont.FontNormal, StartX + 15, StartY + 225, 0xFFFFFFFF, 0x0, (170 / 2), 0, 1, gConfig.TTAS_TEXT_ENGINE[201]);
	CustomFont.Draw(CustomFont.FontNormal, StartX + 15, StartY + 225 + 13, 0xFFBA19FF, 0x0, (170 / 2), 0, 1, "WC: ");
	if (this->CH_CoinMix[0] == -1)
	{
		CustomFont.Draw(CustomFont.FontNormal, StartX + 20 + (170 / 2), StartY + 225 + 13, 0xDE1616FF, 0x0, 0, 0, 1, gConfig.TTAS_TEXT_ENGINE[199]);
	}
	else {
		CustomFont.Draw(CustomFont.FontNormal, StartX + 20 + (170 / 2), StartY + 225 + 13, 0x19FF9FFF, 0x0, 0, 0, 1, "%s", gToolKit.NumberFormat(this->CH_CoinMix[0]));
	}
	CustomFont.Draw(CustomFont.FontNormal, StartX + 15, StartY + 225 + (13 * 2), 0xFFBA19FF, 0x0, (170 / 2), 0, 1, "WP: ");
	if (this->CH_CoinMix[1] == -1)
	{
		CustomFont.Draw(CustomFont.FontNormal, StartX + 20 + (170 / 2), StartY + 225 + (13 * 2), 0xDE1616FF, 0x0, 0, 0, 1, gConfig.TTAS_TEXT_ENGINE[199]);
	}
	else {
		CustomFont.Draw(CustomFont.FontNormal, StartX + 20 + (170 / 2), StartY + 225 + (13 * 2), 0x19FF9FFF, 0x0, 0, 0, 1, "%s", gToolKit.NumberFormat(this->CH_CoinMix[1]));
	}

	CustomFont.Draw(CustomFont.FontNormal, StartX + 15, StartY + 225 + (13 * 3), 0xFFBA19FF, 0x0, (170 / 2), 0, 1, "GP: ");
	CustomFont.Draw(CustomFont.FontNormal, StartX + 15, StartY + 225 + (13 * 2), 0xFFBA19FF, 0x0, (170 / 2), 0, 1, "WP: ");
	if (this->CH_CoinMix[2] == -1)
	{
		CustomFont.Draw(CustomFont.FontNormal, StartX + 20 + (170 / 2), StartY + 225 + (13 * 3), 0xDE1616FF, 0x0, 0, 0, 1, gConfig.TTAS_TEXT_ENGINE[199]); //
	}
	else {
		CustomFont.Draw(CustomFont.FontNormal, StartX + 20 + (170 / 2), StartY + 225 + (13 * 3), 0x19FF9FFF, 0x0, 0, 0, 1, "%s", gToolKit.NumberFormat(this->CH_CoinMix[2])); //
	}
	gCentral.gInfoBox(StartX + 7, StartY + 50 + 140 + 100, 170, 40, 0x00000096, 0, 0);

	pDrawButton(31419, StartX + 7 + (170 / 2) - 15, StartY + 55 + 140 + 100, 44.0, 35.0, 0, 0); //ButtonMix
	if (pCheckMouseOver(StartX + 7 + (170 / 2) - 15, StartY + 55 + 140 + 100, 44.0, 35.0) == 1 && this->CH_IndexItem[2] != -1)
	{
		if (GetTickCount() - gInterface.Data[eWindow_CongHuong].EventTick > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				PlayBuffer(25, 0, 0);
				glColor3f(1.0f, 0.0f, 0.0f);
				this->LockMouseMoveClick = GetTickCount() + 500;
				gInterface.Data[eWindow_CongHuong].EventTick = GetTickCount();
				this->CH_EffectMixOn ^= 1;
				XULY_CGPACKET pMsg;
				pMsg.header.set(0xFA, 0x17, sizeof(pMsg));
				pMsg.ThaoTac = 1;
				DataSend((LPBYTE)&pMsg, pMsg.header.size);
			}
		}
		pDrawColorButton(31419, StartX + 7 + (170 / 2) - 15, StartY + 55 + 140 + 100, 44.0, 35.0, 0, 0, pMakeColor(255, 204, 20, 130));
		gInterface.DrawToolTip(gObjUser.m_CursorX + 20, gObjUser.m_CursorY, gConfig.TTAS_TEXT_ENGINE[203]);
	}
	if (this->CH_EffectMixOn)
	{
		gToolKit.RenderMixEffect(this->CH_EffectMixOn, StartX + 12 + 50 + 45 + 20, StartY + 55, 2, 4);
	}
	JCCoord B;
	BYTE ItemInfo[3][MAX_ITEM_INFO] = { 0x00 };
	if (pCheckMouseOver(StartX + 12, StartY + 55, 2 * 21, 4 * 21) == 1 && this->CH_IndexItem[0] != -1)
	{
		if (GetTickCount() - gInterface.Data[eWindow_CongHuong].EventTick > 300)
		{
			if (GetKeyState(VK_RBUTTON) & 0x8000)
			{
				PlayBuffer(25, 0, 0);
				gInterface.Data[eWindow_CongHuong].EventTick = GetTickCount();
				XULY_CGPACKET pMsg;
				pMsg.header.set(0xFA, 0x16, sizeof(pMsg));
				pMsg.ThaoTac = 0; //RollBack Item
				DataSend((LPBYTE)&pMsg, pMsg.header.size);
			}
		}
		B.X = (int)StartX + 130;
		B.Y = (int)StartY + 55;
		GetInfoLoadItem = BPConvertByteItem(*(DWORD*)(GetInstance() + 36), this->CH_InfoItem[0]);
		BPDrawInfoItem(*(DWORD*)(GetInstance() + 308), B, GetInfoLoadItem, 0, 0, 0);

	}
	//=== Phoi Item
	if (pCheckMouseOver(StartX + 12 + 50, StartY + 55, 2 * 21, 4 * 21) == 1 && this->CH_IndexItem[1] != -1)
	{
		if (GetTickCount() - gInterface.Data[eWindow_CongHuong].EventTick > 300)
		{
			if (GetKeyState(VK_RBUTTON) & 0x8000)
			{
				PlayBuffer(25, 0, 0);
				gInterface.Data[eWindow_CongHuong].EventTick = GetTickCount();
				XULY_CGPACKET pMsg;
				pMsg.header.set(0xFA, 0x16, sizeof(pMsg));
				pMsg.ThaoTac = 2; //RollBack Item
				DataSend((LPBYTE)&pMsg, pMsg.header.size);
			}
		}
		B.X = (int)StartX + 130 + 50;
		B.Y = (int)StartY + 55;
		GetInfoLoadItem = BPConvertByteItem(*(DWORD*)(GetInstance() + 36), this->CH_InfoItem[1]);
		BPDrawInfoItem(*(DWORD*)(GetInstance() + 308), B, GetInfoLoadItem, 0, 0, 0);

	}
	//== Xem Truoc
	if (pCheckMouseOver(StartX + 12 + 50 + 45 + 20, StartY + 55, 2 * 21, 4 * 21) == 1 && this->CH_IndexItem[2] != -1)
	{
		B.X = (int)StartX + 130 + 50 + 45 + 20;
		B.Y = (int)StartY + 55;
		GetInfoLoadItem = BPConvertByteItem(*(DWORD*)(GetInstance() + 36), this->CH_InfoItem[2]);

		BPDrawInfoItem(*(DWORD*)(GetInstance() + 308), B, GetInfoLoadItem, 0, 0, 0);
	}
	pGLSwitch();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	pSetBlend(0);
	DeleteObject(CustomFont.FontNormal);

}


void CongHuongV2New::CH_RecvInfoGSSend(PMSG_GSSendInfoClient* pMsg)
{
	if (pMsg->mCH_IndexItem[0] != -1)
	{
		this->CH_EffectMixOn = 0;
		this->CH_TyLeThanhCong = pMsg->mCH_TyLeThanhCong;
		this->CH_ResetMix = pMsg->mCH_ResetMix;
		this->CH_TypeMix = pMsg->mCH_TypeMix;
		this->CH_CheckLvItem = pMsg->mCH_CheckLvItem;;
		for (int n = 0; n < 3; n++)
		{
			this->CH_IndexItem[n] = pMsg->mCH_IndexItem[n];
			this->CH_CoinMix[n] = pMsg->mCH_CoinMix[n];
			memset(this->CH_InfoItem[n], 0x0, sizeof(this->CH_InfoItem[n]));
			memcpy(this->CH_InfoItem[n], pMsg->mCH_InfoItem[n], sizeof(this->CH_InfoItem[n]));
		}
	}
	else
	{
		this->m_ScrollPos = 0;
		this->CH_EffectMixOn = 0;
		this->CH_TyLeThanhCong = -1;
		this->CH_ResetMix = -1;
		this->CH_TypeMix = -1;
		this->CH_CheckLvItem = 0;
		for (int n = 0; n < 3; n++)
		{
			this->CH_IndexItem[n] = -1;
			this->CH_CoinMix[n] = -1;
			ZeroMemory(this->CH_InfoItem[n], sizeof(this->CH_InfoItem[n]));
		}
	}
}
#endif