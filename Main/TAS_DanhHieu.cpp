#include "stdafx.h"
#if TAS_DANHHIEU
#include "Protocol.h"
#include "Interface.h"
#include "TAS_DanhHieu.h"
#include "CustomRankUser.h"
#include "User.h"
#include "Central.h"
#include "CustomFont.h"
#include "Controller.h"
#include "Item.h"
#include "Defines.h"
#include "Object.h"
#include "CustomJewelBank.h"
#include <sstream>
#include "Console.h"
#include "Config.h"
#include "TAS_ToolKit.h"
cDanhHieu gDanhHieu;
const char* ItemNameBankDH[20] =
{
	"Ngọc Ước Nguyện",
	"Ngọc Tâm Linh",
	"Ngọc Sinh Mệnh",
	"Ngọc Sáng Tạo",
	"Đá Hộ Mệnh",
	"Đá Nguyên Thủy",
	"Đá Tạo Hóa",
	"Ngọc Hỗn Nguyên",
	"Đá Cấp Thấp",
	"Đá Cấp Cao",
	"Ngọc Cấp Độ",
	"Ngọc Kỹ Năng",
	"Ngọc May Mắn",
	"Ngọc Tính Năng",
	"Ngọc Hoàn Hảo",
	"Ngọc Socket",
	"Ngọc Thần 1",
	"Ngọc Thần 2",
	"Ngọc Full",
	"Ngọc Nâng Cấp"
};
char* cDanhHieu::ItemDanhHieu(int ItemType, int Level)
{
	char ItemNameGet[100];
	memset(ItemNameGet, 0, sizeof(ItemNameGet));
	pGetItemName(ItemType, (const char*)(GET_ITEMOPT_LEVEL(Level)), (char*)ItemNameGet);
	std::string a(ItemNameGet);
	return strdup(a.c_str());
}
void cDanhHieu::LoadImageDanhHieu()
{
	for (int i = 0; i <= MAX_LEVEL_DANH_HIEU ; i ++) 
	{
		char fileName[100];
		sprintf(fileName, "TAS\\RankTitle\\DanhHieu\\DanhHieu_%d.tga", i);
		pLoadImage(fileName, TAS_DANHHIEU_IMG + i , 0x2601, 0x2900, 1, 0);
	}
	this->m_DataConfigDanhHieu.clear();
}

CONFIDATA_DANHHIEU* GetConfigLvDanhHieu(int LvDanhHieu)
{
	std::map<int, CONFIDATA_DANHHIEU>::iterator it = gDanhHieu.m_DataConfigDanhHieu.find(LvDanhHieu);
	if (it == gDanhHieu.m_DataConfigDanhHieu.end())
	{
		return 0;
	}
	else
	{
		return &it->second;
	}
}
void cDanhHieu::ShowDanhHieuTAS(int index,int PosX, int PosY)
{
	this->TAS_DANHHIEU_LVL = gCustomRankUser.m_Data[index].m_RankTitle1;
	if(this->TAS_DANHHIEU_LVL >= 1 && this->TAS_DANHHIEU_LVL <= MAX_LEVEL_DANH_HIEU )
	{
		glColor3f(1.0, 1.0, 1.0);
		RenderBitmap(TAS_DANHHIEU_IMG + this->TAS_DANHHIEU_LVL , (float)PosX + 3.0f, (float)PosY - 70.0f, 100.0f, 100.0f, 0, 0, 1, 1, 1, 1, 0.0);
	}	
}
void cDanhHieu::SendMenuButton()
{
	XULY_DANHHIEU pMsg;
	pMsg.header.set(0xD5, 0x05, sizeof(pMsg));
	pMsg.ThaoTac = 1;
	DataSend((LPBYTE)&pMsg, pMsg.header.size);
}
void cDanhHieu::SendPackDHButton()
{
	XULY_DANHHIEU pMsg;
	pMsg.header.set(0xD5, 0x06, sizeof(pMsg));
	pMsg.ThaoTac = 1;
	DataSend((LPBYTE)&pMsg, pMsg.header.size);
}
void cDanhHieu::SendDHProtocol(BYTE* lpMsg)
{
	gDanhHieu.m_DataConfigDanhHieu.clear();
	DHCSEV_COUNTLIST* mRecv = (DHCSEV_COUNTLIST*)lpMsg;
	for (int i = 0; i < mRecv->Count; i++)
	{
		CONFIDATA_DANHHIEU lpInfo = *(CONFIDATA_DANHHIEU*)(((BYTE*)lpMsg) + sizeof(DHCSEV_COUNTLIST) + (sizeof(CONFIDATA_DANHHIEU) * i));
		gDanhHieu.m_DataConfigDanhHieu.insert(std::pair<int, CONFIDATA_DANHHIEU>(lpInfo.LvDanhHieu, lpInfo));
	}
	if ((GetTickCount() - gInterface.Data[eWindow_NangCapDanhHieu].EventTick) > 300)
	{
		gInterface.Data[eWindow_NangCapDanhHieu].OnShow ^= 1;
		gInterface.Data[eWindow_NangCapDanhHieu].EventTick = GetTickCount();
	}
}

void cDanhHieu::DrawWindowNangCapDanhHieu()
{
	if (CheckTAS_WINDOWS)
	{
		gInterface.Data[eWindow_NangCapDanhHieu].OnShow = false;
		return;
	}
	if (!gInterface.Data[eWindow_NangCapDanhHieu].OnShow)
	{
		return;
	}
	float CuaSoW = 450.0;
	float CuaSoH = 270.0;
	float StartX = (MAX_WIN_WIDTH / 2) - (CuaSoW / 2);
	float StartY = ((MAX_WIN_HEIGHT - 51) / 2) - (CuaSoH / 2);
	gInterface.Data[eWindow_NangCapDanhHieu].MaxX = StartX + CuaSoW;
	gInterface.Data[eWindow_NangCapDanhHieu].MaxY = StartY + CuaSoH;
	int LvDanhHieu = gCustomRankUser.m_Data[gObjUser.lpViewPlayer->aIndex].m_RankTitle1;
	CONFIDATA_DANHHIEU* GetInfoLvHienTai = GetConfigLvDanhHieu(LvDanhHieu);
	CONFIDATA_DANHHIEU* GetInfoLvTiepTheo = GetConfigLvDanhHieu(LvDanhHieu + 1);
	gCentral.gDrawWindowCustom(StartX, StartY, CuaSoW, CuaSoH, eWindow_NangCapDanhHieu, gConfig.TTAS_TEXT_ENGINE[219]);
	gToolKit.CloseButton(512, 78, TAS_DanhHieu_BtnClose);
	gCentral.gInfoBox(StartX + 20, StartY + 40, (CuaSoW/4) + 10 , CuaSoH - 65, 0x00000096, 0, 0);
	gCentral.gInfoBox(StartX + (3 * CuaSoW / 4) - 40, StartY + 40, (CuaSoW/4) + 10, CuaSoH - 65, 0x00000096, 0, 0);
	this->KhoanCach_Distance = (3 * CuaSoW / 4);

	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);
	float TextPlusY = StartY + 155 + 15;
	float IMG_H = 40.0f;
	float IMG_W = 126.0f;
	EnableAlphaTest(0);
	if (LvDanhHieu < MAX_LEVEL_DANH_HIEU + 1)
	{
		if (LvDanhHieu != 0)
		{
			RenderBitmap(TAS_DANHHIEU_IMG + LvDanhHieu , StartX + 23, StartY + 10, 160, 156, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
		}
		gInterface.TASText(eExcellent,StartX + 30, TextPlusY + 10, 125,				1,	 gConfig.TTAS_TEXT_ENGINE[220], (LvDanhHieu == 0 || GetInfoLvHienTai == 0) ? 0 : GetInfoLvHienTai->TangMau);
		gInterface.TASText(eExcellent,StartX + 30, TextPlusY + 20, 125,				1,	 gConfig.TTAS_TEXT_ENGINE[221], (LvDanhHieu == 0 || GetInfoLvHienTai == 0) ? 0 : GetInfoLvHienTai->TangSD);
		gInterface.TASText(eExcellent,StartX + 30, TextPlusY + (10 * 2) + 10, 125,  1,   gConfig.TTAS_TEXT_ENGINE[222], (LvDanhHieu == 0 || GetInfoLvHienTai == 0) ? 0 : GetInfoLvHienTai->TangST);
		gInterface.TASText(eExcellent,StartX + 30, TextPlusY + (10 * 3) + 10, 125,  1,   gConfig.TTAS_TEXT_ENGINE[223], (LvDanhHieu == 0 || GetInfoLvHienTai == 0) ? 0 : GetInfoLvHienTai->TangPT);

		if( LvDanhHieu + 1 < MAX_LEVEL_DANH_HIEU )
		{
			RenderBitmap(TAS_DANHHIEU_IMG + LvDanhHieu + 1, StartX + this->KhoanCach_Distance - 38, StartY + 10, 160, 156, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
		}

		gInterface.TASText(eWhite,StartX + this->KhoanCach_Distance - 30, TextPlusY + 10, 125,				1,gConfig.TTAS_TEXT_ENGINE[220], GetInfoLvTiepTheo->TangMau);
		gInterface.TASText(eWhite,StartX + this->KhoanCach_Distance - 30, TextPlusY + 20, 125,				1,gConfig.TTAS_TEXT_ENGINE[221], GetInfoLvTiepTheo->TangSD);
		gInterface.TASText(eWhite,StartX + this->KhoanCach_Distance - 30, TextPlusY + (10 * 2) + 10, 125,	1,gConfig.TTAS_TEXT_ENGINE[222], GetInfoLvTiepTheo->TangST);
		gInterface.TASText(eWhite,StartX + this->KhoanCach_Distance - 30, TextPlusY + (10 * 3) + 10, 125,	1,gConfig.TTAS_TEXT_ENGINE[223], GetInfoLvTiepTheo->TangPT);
		CustomFont.Draw(CustomFont.FontBold,			StartX + this->KhoanCach_Distance - 40, StartY + 55 + 110, 0xFFDE26FF, 0x0, 125, 0, 3, gConfig.TTAS_TEXT_ENGINE[224], LvDanhHieu + 1);
	}
	else
	{
		RenderBitmap(TAS_DANHHIEU_IMG + LvDanhHieu , StartX + 23, StartY + 10, 160, 156, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
		CustomFont.Draw(CustomFont.FontBold, StartX + 160 + 40, TextPlusY + 10 , 0x1FD2FFFF, 0x0, CuaSoW - 140, 0, 1, gConfig.TTAS_TEXT_ENGINE[225]);
		CustomFont.Draw(CustomFont.FontBold, StartX + this->KhoanCach_Distance - 40, StartY + 55 + 110, 0xFFDE26FF, 0x0, 125, 0, 3, gConfig.TTAS_TEXT_ENGINE[226]);
	}
	CustomFont.Draw(CustomFont.FontBold, StartX + 23, StartY + 55 + 110, 0xFFDE26FF, 0x0, 125, 0, 3, gConfig.TTAS_TEXT_ENGINE[227], LvDanhHieu);
	
	pGLSwitch();
	pSetBlend(false);
	EnableAlphaTest(0);
	int ct = 0;
	CustomFont.Draw(CustomFont.FontBold, StartX + 160, StartY + 45 + (12 * ct++), 0xC8FF00FF, 0x0, CuaSoW - 170, 0, 1, gConfig.TTAS_TEXT_ENGINE[228]);
	CustomFont.Draw(CustomFont.FontBold, StartX + 160, StartY + 45 + (12 * ct++), 0xC8FF00FF, 0x0, CuaSoW - 170, 0, 1, gConfig.TTAS_TEXT_ENGINE[229]);
	CustomFont.Draw(CustomFont.FontBold, StartX + 160, StartY + 45 + (12 * ct++), 0xC8FF00FF, 0x0, CuaSoW - 170, 0, 1, gConfig.TTAS_TEXT_ENGINE[230]);
	
	float YUpCapDanhHieu = StartY + 35 + (12 * ct) + 15;
	if (LvDanhHieu < MAX_LEVEL_DANH_HIEU)
	{
		CustomFont.Draw(CustomFont.FontBold, StartX + 160 + 10, YUpCapDanhHieu, 0xFFDE26FF, 0x0, CuaSoW - 170, 0, 1, gConfig.TTAS_TEXT_ENGINE[231], LvDanhHieu + 1);
		#if MOVE_ITEMBANK_DIR
		CustomFont.Draw(CustomFont.FontBold, StartX + 160 + 30, YUpCapDanhHieu + 13, 0x1FD2FFFF, 0x0, CuaSoW - 140, 0, 1, gConfig.TTAS_TEXT_ENGINE[232], GetInfoLvTiepTheo->YCItemSL, this->ItemDanhHieu(GetInfoLvTiepTheo->YCItemID, GetInfoLvTiepTheo->YCItemLv));
		#else
		CustomFont.Draw(CustomFont.FontBold, StartX + 160 + 30, YUpCapDanhHieu + 13, 0x1FD2FFFF, 0x0, CuaSoW - 140, 0, 1,
			"Cần: %d Viên %s",
			GetInfoLvTiepTheo->YCItemSL,
			ItemNameBankDH[GetInfoLvTiepTheo->YCItemID]);
		if (gCustomJewelBank.m_Data.ItemBank[GetInfoLvTiepTheo->YCItemID] < GetInfoLvTiepTheo->YCItemSL)
		{
			int KetQua = GetInfoLvTiepTheo->YCItemSL - gCustomJewelBank.m_Data.ItemBank[GetInfoLvTiepTheo->YCItemID];
			if (KetQua)
			{
				CustomFont.Draw(CustomFont.FontBold, StartX + 160, YUpCapDanhHieu + 13 + (12 * 5) + 5, 0x1FD2FFFF, 0x0, CuaSoW - 170, 0, 1, "Còn lại: %d viên %s => Thiếu %d viên", gCustomJewelBank.m_Data.ItemBank[GetInfoLvTiepTheo->YCItemID], ItemNameBankDH[GetInfoLvTiepTheo->YCItemID], KetQua);
			}
		}
		else
		{
			CustomFont.Draw(CustomFont.FontBold, StartX + 160, YUpCapDanhHieu + 13 + (12 * 5) + 5, 0x1FD2FFFF, 0x0, CuaSoW - 170, 0, 1, "Còn lại: %d viên %s", gCustomJewelBank.m_Data.ItemBank[GetInfoLvTiepTheo->YCItemID], ItemNameBankDH[GetInfoLvTiepTheo->YCItemID]);
		}
		#endif
		gInterface.TASText(eExcellent, StartX + 160 + 30, YUpCapDanhHieu + 13 + (12 * 1), 125,1, gConfig.TTAS_TEXT_ENGINE[233], GetInfoLvTiepTheo->YCWC);
		gInterface.TASText(eExcellent, StartX + 160 + 30, YUpCapDanhHieu + 13 + (12 * 2), 125,1, gConfig.TTAS_TEXT_ENGINE[234], GetInfoLvTiepTheo->YCWP);
		gInterface.TASText(eExcellent, StartX + 160 + 30, YUpCapDanhHieu + 13 + (12 * 3), 125,1, gConfig.TTAS_TEXT_ENGINE[235], GetInfoLvTiepTheo->YCGP);
		CustomFont.Draw(CustomFont.FontBold, StartX + 160, YUpCapDanhHieu + 13 + (12 * 4) + 5, 0xFFDE26FF, 0x0, CuaSoW - 170, 0, 1, gConfig.TTAS_TEXT_ENGINE[236]);
		//
		if (gCentral.gDrawButton((StartX + CuaSoW)/2 - 10, StartY + (CuaSoH - 40), 110, 14, gConfig.TTAS_TEXT_ENGINE[237]) && (GetTickCount() - gInterface.Data[eWindow_NangCapDanhHieu].EventTick) > 300)
		{
			this->SendPackDHButton();
		}
	}
	else
	{
		CustomFont.Draw(CustomFont.FontBold, StartX + 160, YUpCapDanhHieu, 0xFFDE26FF, 0x0, CuaSoW - 170, 0, 1, gConfig.TTAS_TEXT_ENGINE[238]);
	}	
}
#endif
