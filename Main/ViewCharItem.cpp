#include "stdafx.h"
#include "Object.h"
#include "Protocol.h"
#include "Defines.h"
#include "Import.h"
#include "TMemory.h"
#include "Util.h"
#include "Interface.h"
#include "postInterface.h"
#include "CBUtil.h"
#include "CustomFont.h"
#include "TAS_ToolKit.h"
#if BXH_LUCHIEN
#include "ViewCharItem.h"
cViewCharItems ViewCharItems;

int equipmentI[INVENTORY_ITEMS] = { 0x7A82, 0x7A83, 0x7A7F, 0x7A84, 0x7A86, 0x7A85, 0x7A7E, 0x7A81, 0x7A80, 0x7a88, 0x7a87, 0x7a87};
int equipmentX[INVENTORY_ITEMS] = { 15, 135, 75, 75, 75, 15, 135, 120, 15, 54, 54, 114};
int equipmentY[INVENTORY_ITEMS] = { 87, 87, 44, 87, 150, 150, 150, 44, 44, 87, 150, 150};
int equipmentW[INVENTORY_ITEMS] = { 46, 46, 46, 46, 46, 46, 46, 61, 46, 28, 28, 28};
int equipmentH[INVENTORY_ITEMS] = { 66, 66, 46, 66, 46, 46, 46, 46, 46, 28, 28, 28};

cViewCharItems::cViewCharItems()
{
	int i = 0;
	for (i = 0; i < INVENTORY_ITEMS; ++i)
	{
		this->charItem.Item[i].ItemID = i * 512 + 1;
		this->charItem.Item[i].Level = i << 3;
		this->charItem.Item[i].ExcellentOption = i;
	}

	this->onView = false;
	this->DangXem = false;
	this->Init();
}
bool nInGameShopIsInGameShopRect(float _x, float _y)
{
	if (ViewCharItems.DrawItem3DCenterImage)
		return true;
	if (pCheckWindow(pWindowThis(), ObjWindow::CashShop)) //ObjWindow::CashShop = 65
		return _x >= 0 && _x < 640 && _y < 429 && _y >= 0;
	return false;
}

void cViewCharItems::Init()
{
	this->guiX = 300;
	this->guiY = 20;
	this->curX = pCursorX;
	this->curY = pCursorY;
	this->dragging = false;

	SetCompleteHook(0xE8, 0x005CF3AC, &nInGameShopIsInGameShopRect);
	ClearSession();
}
bool cViewCharItems::IsWorkZone(WORD x, WORD y, WORD w, WORD h) {
	return pCursorX >= x && pCursorX <= (x + w) && pCursorY >= y && pCursorY <= (y + h);
}
bool cViewCharItems::DrawCharInfo()
{
	bool ret = false;
	if (!this->onView ||
		gInterface.CheckWindow(FullMap) ||
		gInterface.CheckWindow(CashShop))
	{
		this->onView = false;
		return ret;
	}
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	float startX = JCResto+436;
	float startY = 20;

	if (this->IsWorkZone(startX + 167.5, startY + 5, 15, 15) && GetKeyState(VK_LBUTTON) & 0x8000)
	{
		this->ActionTime = GetTickCount();
		this->onView = false;
		this->guiX = 300;
		this->guiY = 20;
		return true;
	}
	pDrawGUI(31322, startX + 2, startY + 6, 186, 200);
	pDrawGUI(31354, startX, startY, 190.0, 64.0);
	pDrawGUI(31355, startX, startY + 64, 21.0, 320.0 - 220);
	pDrawGUI(31356, startX + 169, startY + 64, 21.0, 320.0 - 220);
	pDrawGUI(31357, startX, startY + 384 - 220, 190.0, 45.0);
	
	CustomFont.Draw((HFONT)pFontBold, startX, startY + 9, 0xFFFFFFFF, 0, 192, 0, 3, this->charItem.Name);

	//---
	int i = 0;
	pSetBlend(1);
	for (i = 0; i < INVENTORY_ITEMS; ++i)
	{
		pDrawGUI(equipmentI[i], equipmentX[i] + startX, equipmentY[i] + startY, equipmentW[i], equipmentH[i]);
	}
	pGLSwitch();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	pSetBlend(1);

	for (i = 0; i < INVENTORY_ITEMS; ++i)
	{
		if (this->charItem.Item[i].ItemID != -1) {
			gCBUtil.DrawItem3D(equipmentX[i] + startX, equipmentY[i] + startY, equipmentW[i], equipmentH[i],
				this->charItem.Item[i].ItemID, this->charItem.Item[i].Level, this->charItem.Item[i].ExcellentOption, this->charItem.Item[i].AncientOption, 0, 1.4);
		}
	}
	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);

	for (i = 0; i < INVENTORY_ITEMS; ++i)
	{
		if (this->charItem.Item[i].ItemID != -1 && this->IsWorkZone(equipmentX[i] + startX, equipmentY[i] + startY, equipmentW[i], equipmentH[i])) {
			gPostInterface.DrawItemToolTipText((void*)&this->charItem.Item[i], pCursorX + 25, pCursorY);
			break;
		}
	}

	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);
	return ret || this->IsWorkZone(startX, startY, 190, 429.0 - 30);
}

void cViewCharItems::ClearSession()
{
	ZeroMemory(this->charItem.Name, sizeof(this->charItem.Name));
	memset(&this->charItem.Item, 0xFF, sizeof(this->charItem.Item));
	ZeroMemory(this->charItem.Guild, sizeof(this->charItem.Guild));
}
#endif