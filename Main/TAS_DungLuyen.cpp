#include "stdafx.h"
#if(CUSTOM_DUNGLUYENITEM == 1)
#include "TAS_DungLuyen.h"
#include "Import.h"
#include "Object.h"
#include "TAS_ToolKit.h"
#include "Interface.h"
#include "Defines.h"
#include "Central.h"
#include "CustomFont.h"
#include "CBNewUiEx.h"
#include "CBUtil.h"
#include "InterfaceElemental.h"
#include "Common.h"
#include "TAS_ItemTrader.h"
#include "Console.h"
#include "OffTrade.h"
MixItemDungLuyen gMixDL;

void* gCacheItem_MixDl;
DWORD gCacheTime_MixDl = 0;
DWORD DungLuyenEffect = 0;
CNewUIScrollBar* DungLuyenListScrollBar = NULL;
int DungLuyenListMaxPerPage = 5;
bool UpdateMaxPosDL = false;

void MixItemDungLuyen::BackItemDungLuyen(int Type)
{
	if ((GetTickCount() - gInterface.Data[eWindowDungLuyenItem].EventTick) > 300)
	{
		XULY_CGPACKETDL pMsg;
		pMsg.header.set(0xD3, 0x2C, sizeof(pMsg));
		pMsg.ThaoTac = Type; //
		DataSend((LPBYTE)&pMsg, pMsg.header.size);
		gInterface.Data[eWindowDungLuyenItem].EventTick = GetTickCount();
	}
}

void MixItemDungLuyen::TruyenXuongProtocol2A(BYTE* lpMsg)
{
	XULY_CGPACKET* mRecv = (XULY_CGPACKET*)lpMsg;
	if (mRecv->ThaoTac != 111) return;
	if (GetTickCount() > gInterface.Data[eWindowDungLuyenItem].EventTick)
	{
		gInterface.Data[eWindowDungLuyenItem].EventTick = GetTickCount() + 300;
		gInterface.Data[eWindowDungLuyenItem].OnShow ^= 1;
	}
	gMixDL.SetStateDungLuyen = true;
}
void MixItemDungLuyen::TruyenXuongProtocol2B(BYTE* lpMsg)
{
	INFOITEM_DUNGLUYENT_CLIENT* mRecv = (INFOITEM_DUNGLUYENT_CLIENT*)lpMsg;
	memcpy(gMixDL.DL_ItemChinh,		mRecv->ItemChinh,	sizeof(gMixDL.DL_ItemChinh));
	memcpy(gMixDL.DL_ItemPhu,		mRecv->ItemPhu,		sizeof(gMixDL.DL_ItemPhu));
	memcpy(gMixDL.DL_ItemKetQua,	mRecv->ItemKetQua,	sizeof(gMixDL.DL_ItemKetQua));
	gMixDL.RateDL			= mRecv->Rate;
	gMixDL.TypeDL			= mRecv->TypeMix;
	gMixDL.DL_ActiveMix		= mRecv->ActiveMix;
	memcpy(gMixDL.TextDL, mRecv->Text, sizeof(gMixDL.TextDL));
	gMixDL.DL_EffectsMix	= false;
}

void MixItemDungLuyen::CreatSlotItem(float x, float y, BYTE ItemSlot)
{
	int Item3DX = x;
	int Item3DY = y;
	float fitemX = Item3DX;
	float fitemY = Item3DY;
	gCentral.gItemBoxInv(Item3DX, Item3DY, 2, 2, 0);
	ObjectItem* NguyenLieu = &*(ObjectItem*)(BPConvertByteItem(*(DWORD*)(GetInstance() + 36), gMixDL.DL_ItemPhu[ItemSlot]));
	if (NguyenLieu->ItemID > 0)
	{
		 gCBUtil.DrawItem3D(fitemX + 4, fitemY, 35, 35, NguyenLieu->ItemID, NguyenLieu->Level, NguyenLieu->ExcellentOption, NguyenLieu->AncientOption, 0, 0.8);
		if (pCheckMouseOver(fitemY + 4, fitemY, 35, 35) == 1)
		{
			gCacheItem_MixDl = NguyenLieu;
			gCacheTime_MixDl = GetTickCount() + 50;
			if (GetKeyState(VK_RBUTTON) & 0x8000)
			{
				this->BackItemDungLuyen(ItemSlot + 1);
			}
		}
	}
}

void MixItemDungLuyen::ToolTipItem(float X, float Y, float W, float H, int iW, int iH, void* ItemSlot)
{
	ObjectItem* SecondItemSlot = &*(ObjectItem*)(BPConvertByteItem(*(DWORD*)(GetInstance() + 36), ItemSlot));
	if (SecondItemSlot->ItemID > 0)
	{
		if (pCheckMouseOver(X, Y, W + iW, iH) == 1)
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
void MixItemDungLuyen::HienThiItem()
{
	if (gInterface.CheckWindow(SkillTree) || gInterface.CheckWindow(Shop) || gInterface.CheckWindow(CreateGuild) || gInterface.CheckWindow(ChatWindow) || gInterface.CheckWindow(FriendList) || gInterface.CheckWindow(MuHelper) || gInterface.CheckWindow(Store) || gInterface.CheckWindow(Warehouse) || gInterface.CheckWindow(Trade) || gInterface.CheckWindow(CashShop) || gInterface.CheckWindow(GuardNPC))
	{
		return;
	}
	gInterface.CloseCustomWindow();
	gInterface.OpenWindow(Inventory);
	gInterface.CloseWindow(Character);
}
void MixItemDungLuyen::DrawWindows()
{
	if (CheckNoVault_Inv)
	{
		if (gInterface.Data[eWindowDungLuyenItem].OnShow == true)
		{
			gInterface.Data[eWindowDungLuyenItem].OnShow = false;
			pSetCursorFocus = false;
			return;
		}
	}

	if (!gInterface.Data[eWindowDungLuyenItem].OnShow)
	{
		if (gMixDL.SetStateDungLuyen == 1)
		{
			XULY_CGPACKETDL pMsg;
			pMsg.header.set(0xD3, 0x2A, sizeof(pMsg));
			pMsg.ThaoTac = 111; //
			DataSend((LPBYTE)&pMsg, pMsg.header.size);
			gMixDL.SetStateDungLuyen = false;
			gMixDL.DL_EffectsMix = false;
			gMixDL.DL_ActiveMix = false;
			gMixDL.RateDL = false;
			gMixDL.TypeDL = false;			
		}
		if (DungLuyenListScrollBar)
		{
			DungLuyenListScrollBar = NULL;
		}
		memset(gMixDL.DL_ItemChinh, 0, sizeof(gMixDL.DL_ItemChinh));
		memset(gMixDL.DL_ItemPhu, 0, sizeof(gMixDL.DL_ItemPhu));
		memset(gMixDL.DL_ItemKetQua, 0, sizeof(gMixDL.DL_ItemKetQua));
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
			gInterface.Data[eWindowDungLuyenItem].OnShow = false;
		}
	}

	float StartX = 215;
	float StartY = 0;
	float WindowW = 235;
	float WindowH = 250;
	int XClose = StartX + 202;
	int YClose = StartY - 1;

	gCentral.gDrawWindowCustom(StartX, StartY, WindowW, WindowH, eWindowDungLuyenItem, "ĐỔI VŨ KHÍ");
	gToolKit.CloseButton(XClose, YClose, TAS_DungLuyen_BtnClose);
	if (pCheckMouseOver(XClose + 10, StartY + 6, 14, 14) == 1)
	{
		if (pIsKeyPress(VK_LBUTTON) && GetTickCount() - this->ClickTime > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				gCentral.LockMouse = GetTickCount() + 500;
				this->ClickTime = GetTickCount();
				gInterface.Data[eWindowDungLuyenItem].OnShow = false;
			}
		}
	}
	float BoxItemWH = 35;
	float PosXGroup1 = StartX + 20;
	float PosYGroup1 = StartY + 50;
	
	int PosXInvetoryImg = PosXGroup1 - 5;
	int PosYInvetoryImg = PosYGroup1 + 5;
	float PosXItemImg3D = PosXInvetoryImg + 15;
	float PosYItemImg3D = PosYInvetoryImg + 33;

	gCentral.gInfoBox(StartX + 14, StartY + 47, 55, 83, 0x00000096, 0, 0);
	gCentral.gInfoBox(StartX + 14, StartY + 147, 55, 83, 0x00000096, 0, 0);
	gCentral.gInfoBox(StartX + 82, StartY + 47, 130, 183, 0x00000096, 0, 0);

	CustomFont.Draw((HFONT)pFontBold, PosXInvetoryImg,  PosYInvetoryImg - 8, 0xEBA000FF, 0x00FBFF69, 61, 0, 3, "Item Chính");
	CustomFont.Draw((HFONT)pFontBold, PosXInvetoryImg,  PosYInvetoryImg + 92, 0xEBA000FF, 0x00FBFF69, 61, 0, 3, "Kết Quả");
	CustomFont.Draw((HFONT)pFontBold, PosXInvetoryImg + 68, PosYInvetoryImg - 8, 0xEBA000FF, 0x00FBFF69, 135, 0, 3,"Item Phụ");

	//Input
	gCentral.gItemBoxInv(PosXInvetoryImg, PosYInvetoryImg, 4, 3, 0);
	ObjectItem* CTItemChinh = &*(ObjectItem*)(BPConvertByteItem(*(DWORD*)(GetInstance() + 36), gMixDL.DL_ItemChinh));
	if (CTItemChinh->ItemID > 0)
	{
		 gCBUtil.DrawItem3D(PosXItemImg3D, PosYItemImg3D, 35, 35, CTItemChinh->ItemID, CTItemChinh->Level, CTItemChinh->ExcellentOption, CTItemChinh->AncientOption, 0, 1.0);
		if (pCheckMouseOver(PosXItemImg3D, PosYItemImg3D, 35, 35) == 1)
		{
			gCacheItem_MixDl = CTItemChinh;
			gCacheTime_MixDl = GetTickCount() + 50;
			if (GetKeyState(VK_RBUTTON) & 0x8000)
			{
				this->BackItemDungLuyen(0);
			}
		}
	}
	//OutPut
	gCentral.gItemBoxInv(PosXInvetoryImg, PosYInvetoryImg + 100, 4, 3, 0);
	ObjectItem* CTItemKetQua = &*(ObjectItem*)(BPConvertByteItem(*(DWORD*)(GetInstance() + 36), gMixDL.DL_ItemKetQua));
	if (CTItemKetQua->ItemID > 0)
	{
		gCBUtil.DrawItem3D(PosXItemImg3D, PosYItemImg3D + 100, 35, 35, CTItemKetQua->ItemID, CTItemKetQua->Level, CTItemKetQua->ExcellentOption, CTItemKetQua->AncientOption, 0, 1.0);
		if (pCheckMouseOver(PosXItemImg3D, PosYItemImg3D + 100, 35, 35) == 1)
		{
			gCacheItem_MixDl = CTItemKetQua;
			gCacheTime_MixDl = GetTickCount() + 50;
			if (GetKeyState(VK_RBUTTON) & 0x8000)
			{
				this->BackItemDungLuyen(5);
			}
		}
	}
	//ItemMix
	this->CreatSlotItem(PosXInvetoryImg + 70,  PosYInvetoryImg, 0);
	this->CreatSlotItem(PosXInvetoryImg + 110, PosYInvetoryImg, 1);
	this->CreatSlotItem(PosXInvetoryImg + 150, PosYInvetoryImg, 2);


	CustomFont.Draw((HFONT)pFontBold, PosXInvetoryImg + 70, PosYInvetoryImg + 50, 0x0, 0x00000069, 121, 70, 3, " ");

	int DataListItem = gMixDL.m_DungLuyenInfoList.size();

	if (DungLuyenListScrollBar == NULL)
	{
		DungLuyenListScrollBar = new CNewUIScrollBar();
		DungLuyenListScrollBar->Create(PosXInvetoryImg + 190, PosYInvetoryImg + 50, 70);
		if (DungLuyenListScrollBar)
		{
			DungLuyenListScrollBar->SetMaxPos((DataListItem <= DungLuyenListMaxPerPage) ? 0 : (DataListItem / DungLuyenListMaxPerPage) - 1);
			DungLuyenListScrollBar->SetPos(PosXInvetoryImg + 190, PosYInvetoryImg + 50);
		}
	}
	if (DungLuyenListScrollBar)
	{
		if (UpdateMaxPosDL)
		{
			DungLuyenListScrollBar->SetMaxPos((DataListItem <= DungLuyenListMaxPerPage) ? 0 : (DataListItem / DungLuyenListMaxPerPage) - 1);
			UpdateMaxPosDL = false;
		}

		DungLuyenListScrollBar->MouseWheelWindow = pCheckMouseOver(PosXInvetoryImg + 65, PosYInvetoryImg + 50, 130, 70);
		DungLuyenListScrollBar->Render();
		DungLuyenListScrollBar->UpdateMouseEvent();
		DungLuyenListScrollBar->Update();
	}

	int Count = 0;
	int VipCharListPage = DungLuyenListScrollBar->GetCurPos();
	for (int n = (VipCharListPage * DungLuyenListMaxPerPage); n < DataListItem; n++)
	{
		if (Count >= DungLuyenListMaxPerPage) break;
		CustomFont.Draw((HFONT)pFontNormal, PosXInvetoryImg + 75, PosYInvetoryImg + 55, 0xFFDD00FF, 0x0, 121, 0, 1, "%s", gToolKit.BGetItemName(gMixDL.m_DungLuyenInfoList[n].IndexItem, SET_ITEMOPT_LEVEL((gMixDL.m_DungLuyenInfoList[n].Level == 255) ? 0 : gMixDL.m_DungLuyenInfoList[n].Level)));
		
		if (gMixDL.m_DungLuyenInfoList[n].Luck >= 1)
		{
			CustomFont.Draw((HFONT)pFontNormal, PosXInvetoryImg + 55, PosYInvetoryImg + 55 + 12, 0xFFDD00FF, 0x0, 121, 0, 4, "+ Luck");
		}
		if (gMixDL.m_DungLuyenInfoList[n].Exc >= 1)
		{
			CustomFont.Draw((HFONT)pFontNormal, PosXInvetoryImg + 55, PosYInvetoryImg + 55 + 24, 0xFFDD00FF, 0x0, 121, 0, 4, "+ Excl");
		}
		if (gMixDL.m_DungLuyenInfoList[n].Option >= 1)
		{
			CustomFont.Draw((HFONT)pFontNormal, PosXInvetoryImg + 55, PosYInvetoryImg + 55 + 36, 0xFFDD00FF, 0x0, 121, 0, 4, "+ %d (Opt)", gMixDL.m_DungLuyenInfoList[n].Option);//
		}
		if (gMixDL.m_DungLuyenInfoList[n].Dur >= 1)
		{
			CustomFont.Draw((HFONT)pFontNormal, PosXInvetoryImg + 55, PosYInvetoryImg + 55 + 48, 0xFFDD00FF, 0x0, 121, 0, 4, "%s Stack", gToolKit.QNumberFormat(gMixDL.m_DungLuyenInfoList[n].Dur));//
		}
		Count++;
	}
	if (gMixDL.RateDL != 0)
	{
		CustomFont.Draw((HFONT)pFontBold, PosXInvetoryImg + 75, PosYInvetoryImg + 130, 0xB752FFFF, 0x0, 0, 0, 1, "Dung luyện: %s", gMixDL.TextDL);
	}

	CustomFont.Draw((HFONT)pFontBold, PosXInvetoryImg + 75, PosYInvetoryImg + 142, 0xEBA000FF, 0x0, 0, 0, 1, "Thất Bại: ");

	if (gMixDL.TypeDL == 0)
	{
		CustomFont.Draw((HFONT)pFontBold, PosXInvetoryImg + 100, PosYInvetoryImg + 142, 0xEBA000FF, 0x0, 0, 0, 1, "Trả lại item gốc");
	}
	else
	{
		CustomFont.Draw((HFONT)pFontBold, PosXInvetoryImg + 100, PosYInvetoryImg + 142, 0xEBA000FF, 0x0, 0, 0, 1, "Gãy mất Item gốc");
	}
	CustomFont.Draw((HFONT)pFontBold, PosXInvetoryImg + 75, PosYInvetoryImg + 154, 0xEBA000FF, 0x0, 0, 0, 1, "Tỉ lệ thành công: %d%%", gMixDL.RateDL);

	if (gMixDL.DL_EffectsMix && DungLuyenEffect > GetTickCount() && DungLuyenEffect != 0)
	{
		gToolKit.RenderMixEffect(gMixDL.DL_EffectsMix, PosXInvetoryImg, PosYInvetoryImg + 100, 3, 3);
	}
	else if (DungLuyenEffect != 0)
	{
		DungLuyenEffect = 0;
		if (gMixDL.DL_ActiveMix)
		{
			if ((GetTickCount() - gInterface.Data[eWindowDungLuyenItem].EventTick) > 300 && DungLuyenEffect == 0)
			{
				XULY_CGPACKET pMsg;
				pMsg.header.set(0xD3, 0x2D, sizeof(pMsg));
				pMsg.ThaoTac = 113; //
				DataSend((LPBYTE)&pMsg, pMsg.header.size);
				gInterface.Data[eWindowDungLuyenItem].EventTick = GetTickCount();
			}
		}
	}
	pDrawButton(31419, PosXInvetoryImg + 156, PosYInvetoryImg + 140, 44.0, 35.0, 0, 0); //ButtonMix
	if (pCheckMouseOver(PosXInvetoryImg + 156, PosYInvetoryImg + 140, 44.0, 35.0) == 1)
	{
		if (GetTickCount() - gInterface.Data[eWindowDungLuyenItem].EventTick > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				if (gMixDL.DL_ActiveMix)
				{
					gMixDL.DL_EffectsMix = 1;
				}
				else
				{
					gElemental.OpenMessageBox("Error", "Vui lòng đặt thêm Item !");
				}
				DungLuyenEffect = GetTickCount() + 2000;
			}
		}
		pDrawColorButton(31419, PosXInvetoryImg + 156, PosYInvetoryImg + 140, 44.0, 35.0, 0, 0, pMakeColor(255, 204, 20, 130));
	}

	this->ToolTipItem(PosXInvetoryImg, PosYInvetoryImg, 41, 3, 18, 80, gMixDL.DL_ItemChinh);
	this->ToolTipItem(PosXInvetoryImg, PosYInvetoryImg + 100, 41, 3, 18, 80, gMixDL.DL_ItemKetQua);
	this->ToolTipItem(PosXInvetoryImg + 70, PosYInvetoryImg, 21, 3, 18, 40, gMixDL.DL_ItemPhu[0]);
	this->ToolTipItem(PosXInvetoryImg + 110, PosYInvetoryImg, 21, 3, 18, 40, gMixDL.DL_ItemPhu[1]);
	this->ToolTipItem(PosXInvetoryImg + 150, PosYInvetoryImg, 21, 3, 18, 40, gMixDL.DL_ItemPhu[2]);
}

void MixItemDungLuyen::NhanListItemDungLuyen(DLCSEV_COUNTLIST* lpMsg) // OK
{
	m_DungLuyenInfoList.clear();

	for (int n = 0; n < lpMsg->Count; n++)
	{
		ITEM_INFO_DATA* lpInfo = (ITEM_INFO_DATA*)(((BYTE*)lpMsg) + sizeof(DLCSEV_COUNTLIST) + (sizeof(ITEM_INFO_DATA) * n));
		m_DungLuyenInfoList.push_back(*lpInfo);
	}
}
#endif