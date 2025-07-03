#include "stdafx.h"
#if TAS_TUCHAN
#include "Protocol.h"
#include "Interface.h"
#include "TAS_TuChan.h"
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

cTuLuyen gTuLuyen;
const char* ItemNameBankTC[20] =
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
char* cTuLuyen::ItemTuLuyen(int ItemType, int Level)
{
	char ItemNameGet[100];
	memset(ItemNameGet, 0, sizeof(ItemNameGet));
	pGetItemName(ItemType, (const char*)(GET_ITEMOPT_LEVEL(Level)), (char*)ItemNameGet);
	std::string a(ItemNameGet);
	return strdup(a.c_str());
}
void cTuLuyen::LoadImageTuLuyen()
{
	for (int i = 0; i <= MAX_LEVEL_TU_LUYEN ; i ++) 
	{
		char fileName[100];
		sprintf(fileName, "TAS\\RankTitle\\TuLuyen\\TuLuyen_%d.tga", i);
		pLoadImage(fileName, TAS_TULUYEN_IMG + i , 0x2601, 0x2900, 1, 0);
	}
	this->m_DataConfigTuLuyen.clear();
}

CONFIDATA_TULUYEN* GetConfigLvTuLuyen(int LvTuLuyen)
{
	std::map<int, CONFIDATA_TULUYEN>::iterator it = gTuLuyen.m_DataConfigTuLuyen.find(LvTuLuyen);
	if (it == gTuLuyen.m_DataConfigTuLuyen.end())
	{
		return 0;
	}
	else
	{
		return &it->second;
	}
}

void cTuLuyen::ShowTuLuyenTAS(int index,int PosX, int PosY)
{
	this->TAS_TULUYEN_LVL = gCustomRankUser.m_Data[index].m_RankTitle3;
	if(this->TAS_TULUYEN_LVL >= 1 && this->TAS_TULUYEN_LVL <= MAX_LEVEL_TU_LUYEN )
	{
		glColor3f(1.0, 1.0, 1.0);
		RenderBitmap(TAS_TULUYEN_IMG + this->TAS_TULUYEN_LVL , (float)PosX + 21, (float)PosY - 72, 60, 20, 0, 0, 1, 1, 1, 1, 0.0);
	}	
}
void cTuLuyen::SendMenuButton()
{
	XULY_TULUYEN pMsg;
	pMsg.header.set(0xD5, 0x03, sizeof(pMsg));
	pMsg.ThaoTac = 1;
	DataSend((LPBYTE)&pMsg, pMsg.header.size);
}
void cTuLuyen::SendPackTCButton()
{
	XULY_TULUYEN pMsg;
	pMsg.header.set(0xD5, 0x04, sizeof(pMsg));
	pMsg.ThaoTac = 1;
	DataSend((LPBYTE)&pMsg, pMsg.header.size);
}
void cTuLuyen::SendTCProtocol(BYTE* lpMsg)
{
	gTuLuyen.m_DataConfigTuLuyen.clear();
	TCCSEV_COUNTLIST* mRecv = (TCCSEV_COUNTLIST*)lpMsg;
	for (int i = 0; i < mRecv->Count; i++)
	{
		CONFIDATA_TULUYEN lpInfo = *(CONFIDATA_TULUYEN*)(((BYTE*)lpMsg) + sizeof(TCCSEV_COUNTLIST) + (sizeof(CONFIDATA_TULUYEN) * i));
		gTuLuyen.m_DataConfigTuLuyen.insert(std::pair<int, CONFIDATA_TULUYEN>(lpInfo.LvTuLuyen, lpInfo));
	}
	if ((GetTickCount() - gInterface.Data[eWindow_NangCapTuChan].EventTick) > 300)
	{
		gInterface.Data[eWindow_NangCapTuChan].OnShow ^= 1;
		gInterface.Data[eWindow_NangCapTuChan].EventTick = GetTickCount();
	}
}
void cTuLuyen::DrawWindowNangCapTuLuyen()
{
	if (CheckTAS_WINDOWS)
	{
		gInterface.Data[eWindow_NangCapTuChan].OnShow = false;
		return;
	}
	if (!gInterface.Data[eWindow_NangCapTuChan].OnShow)
	{
		return;
	}
	float CuaSoW = 450.0;
	float CuaSoH = 270.0;
	float StartX = (MAX_WIN_WIDTH / 2) - (CuaSoW / 2);
	float StartY = ((MAX_WIN_HEIGHT - 51) / 2) - (CuaSoH / 2);

	int LvTuLuyen = gCustomRankUser.m_Data[gObjUser.lpViewPlayer->aIndex].m_RankTitle3;

	CONFIDATA_TULUYEN* GetInfoLvHienTai = GetConfigLvTuLuyen(LvTuLuyen);
	CONFIDATA_TULUYEN* GetInfoLvTiepTheo = GetConfigLvTuLuyen(LvTuLuyen + 1);

	gCentral.gDrawWindowCustom(StartX, StartY, CuaSoW, CuaSoH, eWindow_NangCapTuChan, gConfig.TTAS_TEXT_ENGINE[256]);
	gToolKit.CloseButton(512, 78, TAS_TuChan_BtnClose);

	gCentral.gInfoBox(StartX + 20, StartY + 40, (CuaSoW/4) + 10 , CuaSoH - 65, 0x00000096, 0, 0);
	gCentral.gInfoBox(StartX + (3 * CuaSoW / 4) - 40, StartY + 40, (CuaSoW/4) + 10, CuaSoH - 65, 0x00000096, 0, 0);
	this->KhoanCach_Distance = (3 * CuaSoW / 4);

	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);
	float TextPlusY = StartY + 155 + 15;

	float L_X = 23;
	float L_Y = 50;
	float L_W = 180;
	float L_H = 46;
	float R_X = 36;
	float R_Y = 50;
	float R_W = 180;
	float R_H = 46;

	if (LvTuLuyen < MAX_LEVEL_TU_LUYEN + 1)
	{
		if(LvTuLuyen != 0)
		{
			RenderBitmap(TAS_TULUYEN_IMG + LvTuLuyen , StartX + L_X, StartY + L_Y, L_W, L_H, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
			gInterface.TASText(eExcellent,StartX + 30, TextPlusY + 10, 125,				1, gConfig.TTAS_TEXT_ENGINE[220], (LvTuLuyen == 0 || GetInfoLvHienTai == 0) ? 0 : GetInfoLvHienTai->TangMau);
			gInterface.TASText(eExcellent,StartX + 30, TextPlusY + 20, 125,				1, gConfig.TTAS_TEXT_ENGINE[221], (LvTuLuyen == 0 || GetInfoLvHienTai == 0) ? 0 : GetInfoLvHienTai->TangSD);
			gInterface.TASText(eExcellent,StartX + 30, TextPlusY + (10 * 2) + 10, 125,  1, gConfig.TTAS_TEXT_ENGINE[222], (LvTuLuyen == 0 || GetInfoLvHienTai == 0) ? 0 : GetInfoLvHienTai->TangST);
			gInterface.TASText(eExcellent,StartX + 30, TextPlusY + (10 * 3) + 10, 125,  1, gConfig.TTAS_TEXT_ENGINE[223], (LvTuLuyen == 0 || GetInfoLvHienTai == 0) ? 0 : GetInfoLvHienTai->TangPT);
		}

		if (LvTuLuyen + 1 <= MAX_LEVEL_TU_LUYEN)
		{			
			RenderBitmap(TAS_TULUYEN_IMG + LvTuLuyen + 1, StartX + this->KhoanCach_Distance - R_X, StartY + R_Y, R_W, R_H, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
			gInterface.TASText(eWhite,StartX + this->KhoanCach_Distance - 30, TextPlusY + 10, 125,				1, gConfig.TTAS_TEXT_ENGINE[220], GetInfoLvTiepTheo->TangMau);
			gInterface.TASText(eWhite,StartX + this->KhoanCach_Distance - 30, TextPlusY + 20, 125,				1, gConfig.TTAS_TEXT_ENGINE[221], GetInfoLvTiepTheo->TangSD);
			gInterface.TASText(eWhite,StartX + this->KhoanCach_Distance - 30, TextPlusY + (10 * 2) + 10, 125,	1, gConfig.TTAS_TEXT_ENGINE[222], GetInfoLvTiepTheo->TangST);
			gInterface.TASText(eWhite,StartX + this->KhoanCach_Distance - 30, TextPlusY + (10 * 3) + 10, 125,	1, gConfig.TTAS_TEXT_ENGINE[223], GetInfoLvTiepTheo->TangPT);
			CustomFont.Draw(CustomFont.FontBold,			StartX + this->KhoanCach_Distance - 40, StartY + 55 + 110, 0xFFDE26FF, 0x0, 125, 0, 3, gConfig.TTAS_TEXT_ENGINE[224], LvTuLuyen + 1);
		}
	}
	else
	{
		CustomFont.Draw(CustomFont.FontBold, StartX + 160 + 40, TextPlusY + 10 , 0x1FD2FFFF, 0x0, CuaSoW - 140, 0, 1, gConfig.TTAS_TEXT_ENGINE[225]);
		CustomFont.Draw(CustomFont.FontBold, StartX + this->KhoanCach_Distance - 40, StartY + 55 + 110, 0xFFDE26FF, 0x0, 125, 0, 3, gConfig.TTAS_TEXT_ENGINE[226]);
	}
	CustomFont.Draw(CustomFont.FontBold, StartX + 23, StartY + 55 + 110, 0xFFDE26FF, 0x0, 125, 0, 3, gConfig.TTAS_TEXT_ENGINE[227], LvTuLuyen);
	
	pGLSwitch();
	EnableAlphaTest(0);
	int ct = 0;
	CustomFont.Draw(CustomFont.FontBold, StartX + 160, StartY + 45 + (12 * ct++), 0xC8FF00FF, 0x0, CuaSoW - 170, 0, 1,  gConfig.TTAS_TEXT_ENGINE[228]);
	CustomFont.Draw(CustomFont.FontBold, StartX + 160, StartY + 45 + (12 * ct++), 0xC8FF00FF, 0x0, CuaSoW - 170, 0, 1,  gConfig.TTAS_TEXT_ENGINE[229]);
	CustomFont.Draw(CustomFont.FontBold, StartX + 160, StartY + 45 + (12 * ct++), 0xC8FF00FF, 0x0, CuaSoW - 170, 0, 1,  gConfig.TTAS_TEXT_ENGINE[230]);

	float YUpCapTuLuyen = StartY + 35 + (12 * ct) + 15;
	if (LvTuLuyen < MAX_LEVEL_TU_LUYEN)
	{
		CustomFont.Draw(CustomFont.FontBold, StartX + 160 + 10, YUpCapTuLuyen, 0xFFDE26FF, 0x0, CuaSoW - 170, 0, 1, gConfig.TTAS_TEXT_ENGINE[231], LvTuLuyen + 1);
		#if MOVE_ITEMBANK_DIR
		CustomFont.Draw(CustomFont.FontBold, StartX + 160 + 30, YUpCapTuLuyen + 13, 0x1FD2FFFF, 0x0, CuaSoW - 140, 0, 1, gConfig.TTAS_TEXT_ENGINE[232], GetInfoLvTiepTheo->YCItemSL, this->ItemDanhHieu(GetInfoLvTiepTheo->YCItemID, GetInfoLvTiepTheo->YCItemLv));
		#else
		CustomFont.Draw(CustomFont.FontBold, StartX + 160 + 30, YUpCapTuLuyen + 13, 0x1FD2FFFF, 0x0, CuaSoW - 140, 0, 1,
			"Cần: %d Viên %s",
			GetInfoLvTiepTheo->YCItemSL,
			ItemNameBankTC[GetInfoLvTiepTheo->YCItemID]);
		if (gCustomJewelBank.m_Data.ItemBank[GetInfoLvTiepTheo->YCItemID] < GetInfoLvTiepTheo->YCItemSL)
		{
			int KetQua = GetInfoLvTiepTheo->YCItemSL - gCustomJewelBank.m_Data.ItemBank[GetInfoLvTiepTheo->YCItemID];
			if (KetQua)
			{
				CustomFont.Draw(CustomFont.FontBold, StartX + 160, YUpCapTuLuyen + 13 + (12 * 5) + 5, 0x1FD2FFFF, 0x0, CuaSoW - 170, 0, 1, "Còn lại: %d viên %s => Thiếu %d viên", gCustomJewelBank.m_Data.ItemBank[GetInfoLvTiepTheo->YCItemID], ItemNameBankTC[GetInfoLvTiepTheo->YCItemID], KetQua);
			}
		}
		else
		{
			CustomFont.Draw(CustomFont.FontBold, StartX + 160, YUpCapTuLuyen + 13 + (12 * 5) + 5, 0x1FD2FFFF, 0x0, CuaSoW - 170, 0, 1, "Còn lại: %d viên %s", gCustomJewelBank.m_Data.ItemBank[GetInfoLvTiepTheo->YCItemID], ItemNameBankTC[GetInfoLvTiepTheo->YCItemID]);
		}
		#endif
		gInterface.TASText(eExcellent, StartX + 160 + 30, YUpCapTuLuyen + 13 + (12 * 1), 125,1,gConfig.TTAS_TEXT_ENGINE[233], GetInfoLvTiepTheo->YCWC);
		gInterface.TASText(eExcellent, StartX + 160 + 30, YUpCapTuLuyen + 13 + (12 * 2), 125,1,gConfig.TTAS_TEXT_ENGINE[234], GetInfoLvTiepTheo->YCWP);
		gInterface.TASText(eExcellent, StartX + 160 + 30, YUpCapTuLuyen + 13 + (12 * 3), 125,1,gConfig.TTAS_TEXT_ENGINE[235], GetInfoLvTiepTheo->YCGP);
		CustomFont.Draw(CustomFont.FontBold, StartX + 160, YUpCapTuLuyen + 13 + (12 * 4) + 5, 0xFFDE26FF, 0x0, CuaSoW - 170, 0, 1, gConfig.TTAS_TEXT_ENGINE[236]);

		if (gCentral.gDrawButton((StartX + CuaSoW)/2 - 10, StartY + (CuaSoH - 40), 110, 14, gConfig.TTAS_TEXT_ENGINE[237]) && (GetTickCount() - gInterface.Data[eWindow_NangCapTuChan].EventTick) > 300)
		{
			this->SendPackTCButton();
		}
	}
	else
	{
		CustomFont.Draw(CustomFont.FontBold, StartX + 160, YUpCapTuLuyen, 0xFFDE26FF, 0x0, CuaSoW - 170, 0, 1, gConfig.TTAS_TEXT_ENGINE[238]);
	}	
}
#endif
