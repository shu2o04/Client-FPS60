#include "stdafx.h"
#if TAS_NEWVIP
#include "Protocol.h"
#include "Interface.h"
#include "TAS_NewVip.h"
#include "CustomRankUser.h"
#include "User.h"
#include "Central.h"
#include "CustomFont.h"
#include "Controller.h"
#include "Item.h"
#include "Defines.h"
#include "Object.h"
#include <sstream>
#include "CustomJewelBank.h"
#include "Config.h"
#include "TAS_ToolKit.h"

cNewVip gNewVip;

char* cNewVip::ItemNewVip(int ItemType, int Level)
{
	char ItemNameGet[100];
	memset(ItemNameGet, 0, sizeof(ItemNameGet));
	pGetItemName(ItemType, (const char*)(GET_ITEMOPT_LEVEL(Level)), (char*)ItemNameGet);
	std::string a(ItemNameGet);
	return strdup(a.c_str());
}
void cNewVip::LoadImageNewVip()
{
	for (int i = 0; i < 6 ; i ++) 
	{
		char fileName[100];
		sprintf(fileName, "TAS\\RankTitle\\NewVip\\Sao_%d.tga", i);
		pLoadImage(fileName, TAS_NEWVIP_IMG + i , 0x2601, 0x2900, 1, 0);
	}
	this->m_DataConfigNewVip.clear();
}

CONFIDATA_NEWVIP* GetConfigLvNewVip(int LvNewVip)
{
	std::map<int, CONFIDATA_NEWVIP>::iterator it = gNewVip.m_DataConfigNewVip.find(LvNewVip);
	if (it == gNewVip.m_DataConfigNewVip.end())
	{
		return 0;
	}
	else
	{
		return &it->second;
	}
}

void cNewVip::ShowNewVipTAS(int index,int PosX, int PosY)
{
	this->TAS_NEWVIP_LVL = gCustomRankUser.m_Data[index].m_RankTitle4;

	for (int X = 0; X < 6; X++)
	{
		if (this->TAS_NEWVIP_LVL == X + 1)
		{
			RenderBitmap(TAS_NEWVIP_IMG + (X + 1), (float)PosX + 19, (float)PosY - 90, 60, 33, 0, 0, 1, 1, 1, 1, 0);
		}
	}
}
void cNewVip::SendMenuButton()
{
	XULY_NEWVIP pMsg;
	pMsg.header.set(0xD5, 0x09, sizeof(pMsg));
	pMsg.ThaoTac = 1;
	DataSend((LPBYTE)&pMsg, pMsg.header.size);
}
void cNewVip::SendPackNVButton()
{
	XULY_NEWVIP pMsg;
	pMsg.header.set(0xD5, 0x0A, sizeof(pMsg));
	pMsg.ThaoTac = 1;
	DataSend((LPBYTE)&pMsg, pMsg.header.size);
}
void cNewVip::SendNVProtocol(BYTE* lpMsg)
{
	gNewVip.m_DataConfigNewVip.clear();
	NVCSEV_COUNTLIST* mRecv = (NVCSEV_COUNTLIST*)lpMsg;
	for (int i = 0; i < mRecv->Count; i++)
	{
		CONFIDATA_NEWVIP lpInfo = *(CONFIDATA_NEWVIP*)(((BYTE*)lpMsg) + sizeof(NVCSEV_COUNTLIST) + (sizeof(CONFIDATA_NEWVIP) * i));
		gNewVip.m_DataConfigNewVip.insert(std::pair<int, CONFIDATA_NEWVIP>(lpInfo.LvNewVip, lpInfo));
	}
	if ((GetTickCount() - gInterface.Data[eWindow_NangCapNewVip].EventTick) > 300)
	{
		gInterface.Data[eWindow_NangCapNewVip].OnShow ^= 1;
		gInterface.Data[eWindow_NangCapNewVip].EventTick = GetTickCount();
	}
}
void cNewVip::DrawWindowNangCapNewVip()
{
	if (CheckTAS_WINDOWS)
	{
		gInterface.Data[eWindow_NangCapNewVip].OnShow = false;
		return;
	}
	if (!gInterface.Data[eWindow_NangCapNewVip].OnShow)
	{
		return;
	}
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	float CuaSoW = 200.0;
	float CuaSoH = 270.0;
	float StartX = JCResto+(MAX_WIN_WIDTH / 2) - (CuaSoW / 2);
	float StartY = ((MAX_WIN_HEIGHT - 51) / 2) - (CuaSoH / 2);
	int LvNewVip = gCustomRankUser.m_Data[gObjUser.lpViewPlayer->aIndex].m_RankTitle4;

	CONFIDATA_NEWVIP* GetInfoLvHienTai = GetConfigLvNewVip(LvNewVip);
	CONFIDATA_NEWVIP* GetInfoLvTiepTheo = GetConfigLvNewVip(LvNewVip + 1);
	gCentral.gDrawWindowCustom(StartX - 2, StartY, CuaSoW, CuaSoH, eWindow_NangCapNewVip, "HỆ THỐNG VIP");
	gToolKit.CloseButton(JCResto+385, 78, TAS_NewVip_BtnClose);
	{
		gCentral.gInfoBox(StartX + 10, StartY + 40, CuaSoW - 30, CuaSoH - 95, 0x00000096, 0, 0);
		CustomFont.Draw((HFONT)pFontBold, StartX + 10, StartY + 42, 0xFFFFFFFF, 0x00FBFF69, CuaSoW - 23, 0, 3, "Cấp độ VIP của bạn là: %d", LvNewVip);
		gInterface.DrawFormat(eExcellent, StartX + 10, StartY + 54, CuaSoW - 23, 3, "KÝ HIỆU HIỆN TẠI CỦA BẠN");

		RenderBitmap(TAS_NEWVIP_IMG + (LvNewVip), JCResto+StartY + 189, StartY + 55, 130, 72, 0, 0, 1, 1, 1, 1, 0);

		gInterface.DrawFormat(eGold, StartX + 10, StartY + 95, CuaSoW - 23, 3, "Tỷ lệ Exp thường được tăng thêm: +%s%%", gToolKit.QNumberFormat(GetInfoLvHienTai->ExpThuong));
		gInterface.DrawFormat(eGold, StartX + 10, StartY + 105, CuaSoW - 23, 3, "Tỷ lệ Exp Master được tăng thêm: +%s%%", gToolKit.QNumberFormat(GetInfoLvHienTai->ExpMaster));
		
		if (LvNewVip < MAX_LEVEL_NEW_VIP)
		{
			gInterface.TASText(eExcellent, StartX + 10, StartY + 134, CuaSoW - 23, 3, "KÝ HIỆU CẤP TIẾP THEO");

			RenderBitmap(TAS_NEWVIP_IMG +  (LvNewVip + 1), JCResto+ StartY + 189, StartY + 135, 130, 72, 0, 0, 1, 1, 1, 1, 0);

			gInterface.DrawFormat(eWhite, StartX + 10, StartY + 173, CuaSoW - 23, 3, "Tỷ lệ Exp thường được tăng thêm: +%s%%", gToolKit.QNumberFormat(GetInfoLvTiepTheo->ExpThuong));
			gInterface.DrawFormat(eWhite, StartX + 10, StartY + 183, CuaSoW - 23, 3, "Tỷ lệ Exp Master được tăng thêm: +%s%%", gToolKit.QNumberFormat(GetInfoLvTiepTheo->ExpMaster));
			gInterface.DrawFormat(eWhite, StartX + 10, StartY + 193, CuaSoW - 23, 3, "Ngày hết hạn được: +%s ngày", gToolKit.QNumberFormat(GetInfoLvTiepTheo->Days));
			gInterface.DrawFormat(eWhite, StartX + 10, StartY + 203, CuaSoW - 23, 3, "Yêu cầu: %s Wcoin", gToolKit.QNumberFormat(GetInfoLvTiepTheo->YCWC));
		}
		else
		{
			gInterface.DrawFormat(eExcellent, StartX + 10, StartY + 134, CuaSoW - 23, 3, "ĐÃ ĐẠT CẤP ĐỘ MAX VIP");
		}
	}
	
	if (LvNewVip < MAX_LEVEL_NEW_VIP)
	{
		if (gCentral.gDrawButton(StartX + 47, StartY + (CuaSoH - 40), 110, 14, gConfig.TTAS_TEXT_ENGINE[237]) && (GetTickCount() - gInterface.Data[eWindow_NangCapNewVip].EventTick) > 300)
		{
			this->SendPackNVButton();
		}
	}
}
#endif
