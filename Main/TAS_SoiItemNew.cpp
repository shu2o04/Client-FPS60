#include "stdafx.h"
#include "TAS_SoiItemNew.h"
#include "TAS_ItemTrader.h"
#include "Central.h"
#include "Defines.h"
#include "Interface.h"
#include "CustomFont.h"
#include "CBUtil.h"
int Result;

char Name[10];
XemThongTin gInfoChar;

int SlotEquipmentI[12] = { 0x7A82, 0x7A83, 0x7A7F, 0x7A84, 0x7A86, 0x7A85, 0x7A7E, 0x7A81, 0x7A80, 0x7a88, 0x7a87, 0x7a87 };
int PosItemX[12] = {22,147,87,89,88,27,146,139,24,54,54,116};
int PosItemY[12] = {135,120,60,118,162,162,167,70,63,92,153,153};
int PosItemW[12] = {20,15,15,15,15,13,20,20,20,20,20,20};
int PosItemH[12] = {30,47,47,50,50,50,45,30,45,45,50,50};

void XemThongTin::GCInfoChar(PMSG_INFOCHARVIEW_RECV* lpMsg)
{	
	Result = lpMsg->result;

	for (int i = 0; i < 12; i++)
	{
		this->GetVaultItems.Item[i].ItemID = lpMsg->ItemIndex[i];
		this->GetVaultItems.Item[i].Level = lpMsg->ItemLevel[i];
		this->GetVaultItems.Item[i].ExcellentOption = lpMsg->ItemNewOption[i];;
		this->GetVaultItems.Item[i].AncientOption = lpMsg->ItemSetOption[i];;
	}
	
	memcpy(Name, lpMsg->name, sizeof(Name));
	gInterface.Data[eWindowInfo].OnShow = true;

}
bool XemThongTin::ThongTinItem(WORD x, WORD y, WORD w, WORD h)
{
	return pCursorX >= x && pCursorX <= (x + w) && pCursorY >= y && pCursorY <= (y + h);
}
bool XemThongTin::IsWorkZone(WORD x, WORD y, WORD w, WORD h) {
	return pCursorX >= x && pCursorX <= (x + w) && pCursorY >= y && pCursorY <= (y + h);
}
#include "postInterface.h"
void XemThongTin::DrawWindowInfo()
{
	if (CheckTAS_WINDOWSX)
	{
		gInterface.Data[eWindowIntros].OnShow = false;
		return;
	}
	if (!gInterface.Data[eWindowInfo].OnShow)
	{
		return;
	}
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;
	float WindowW = 220;
	float WindowH = 270;
	gInterface.Data[eWindowInfo].Width = WindowW;
	float StartXA = JCResto+(MAX_WIN_WIDTH / 2) - (WindowW / 2);
	float StartX = StartXA - 48;
	float StartY = ((MAX_WIN_HEIGHT - 51) / 2) - (WindowH / 2);
	//gCentral.gDrawWindowCustom(StartX - 30, StartY - 30, WindowW + 150, WindowH + 80, eWindowInfo, "Info Nhân Vật");
	pDrawGUI(31322, StartX - 161, StartY - 30,  190, 186);
	pDrawGUI(31354, StartX - 161, StartY - 50,  190,  65);
	pDrawGUI(31355, StartX - 161, StartY + 14,   21, 100);
	pDrawGUI(31356, StartX + 8,   StartY + 14,   21, 100);
	pDrawGUI(31357, StartX - 161, StartY + 113, 190,  45);

	pSetBlend(1);

	pDrawGUI(SlotEquipmentI[0],  StartX - 150, StartY + 30, 45, 65);
	pDrawGUI(SlotEquipmentI[1],  StartX - 28,  StartY + 30, 45, 65);
	pDrawGUI(SlotEquipmentI[2],  StartX - 88,  StartY - 15, 45, 45);
	pDrawGUI(SlotEquipmentI[3],  StartX - 88,  StartY + 30, 45, 65);
	pDrawGUI(SlotEquipmentI[4],  StartX - 88,  StartY + 95, 45, 45);
	pDrawGUI(SlotEquipmentI[5],  StartX - 150, StartY + 95, 45, 45);
	pDrawGUI(SlotEquipmentI[6],  StartX - 28,  StartY + 95, 45, 45);
	pDrawGUI(SlotEquipmentI[7],  StartX - 43,  StartY - 15, 60, 45);
	pDrawGUI(SlotEquipmentI[8],  StartX - 150, StartY - 15, 45, 45);
	pDrawGUI(SlotEquipmentI[9],  StartX - 110, StartY + 30, 26, 26);
	pDrawGUI(SlotEquipmentI[10], StartX - 110, StartY + 95, 26, 26);
	pDrawGUI(SlotEquipmentI[11], StartX - 49,  StartY + 95, 26, 26);
	pSetBlend(0);
	if (Result == 1)
	{
		gInterface.DrawFormat(eGold, (int)StartX - 160, (int)StartY - 40, 187, 3, "Thông tin của %s", Name);
		pSetBlend(1);

		for (int i = 0; i < 12; ++i)
		{
			if (this->GetVaultItems.Item[i].ItemID != -1) 
			{
				gCBUtil.DrawItem3D(PosItemX[i], PosItemY[i], PosItemW[i], PosItemH[i],
					this->GetVaultItems.Item[i].ItemID, 
					this->GetVaultItems.Item[i].Level, 
					this->GetVaultItems.Item[i].ExcellentOption, 
					this->GetVaultItems.Item[i].AncientOption, 0, 1.4);
			}
		}
		glColor3f(1.0, 1.0, 1.0);
		pSetBlend(false);
		for (int i = 0; i < 12; ++i)
		{
			if (this->GetVaultItems.Item[i].ItemID != -1 && this->IsWorkZone(PosItemX[i], PosItemY[i], PosItemW[i], PosItemH[i])) 
			{
				gPostInterface.DrawItemToolTipText((void*)&this->GetVaultItems.Item[i], pCursorX + 25, pCursorY);
				break;
			}
		}


		glColor3f(1.0, 1.0, 1.0);
		pSetBlend(false);
	}
	
	if (pCheckMouseOver(168, 35, 17, 17) == 1)
	{
		if (pIsKeyPress(VK_LBUTTON) && GetTickCount() - this->ClickChuot > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				gCentral.LockMouse = GetTickCount() + 500;
				this->ClickChuot = GetTickCount();
				gInterface.Data[eWindowInfo].OnShow = false;
			}
		}
	}
	pSetCursorFocus = true;
}


