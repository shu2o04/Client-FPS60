#include "stdafx.h"
#include "User.h"
#include "Protocol.h"
#include "PrintPlayer.h"
#include "SItemOption.h"
#include "Import.h"
#include "Central.h"
#include "User.h"
#include "Config.h"
#include "TAS_DrawBoxAtm.h"
#include "CustomMessage.h"
#include "Defines.h"
#include "Interface.h"
#include "TAS_ToolKit.h"
IsBoxAtm gBoxAtm;

void IsBoxAtm::DrawAtmWork()
{
	this->DrawBoxAtm();
}
void IsBoxAtm::DrawBoxAtm()
{
	if (gInterface.CheckWindow(CashShop)
		|| gInterface.CheckWindow(SkillTree)
		|| gInterface.CheckWindow(FullMap)
		|| gInterface.CheckWindow(MoveList)
		|| gInterface.CheckWindow(Inventory)
		|| gInterface.CheckWindow(ExpandInventory)
		|| gInterface.CheckWindow(Store)
		|| gInterface.CheckWindow(Inventory)
		|| gInterface.CheckWindow(Party)
		|| gInterface.CheckWindow(Trade)
		|| gInterface.CheckWindow(Warehouse)
		|| gInterface.CheckWindow(ExpandWarehouse))
	{
		return;
	}
	if (!gInterface.Data[ATM_BOX_MAIN].OnShow)
	{
		return;
	}
	float CuaSoW = 250.0;
	float CuaSoH = 270.0;
	float StartX = (MAX_WIN_WIDTH / 2) - (CuaSoW / 2);
	float StartY = ((MAX_WIN_HEIGHT - 51) / 2) - (CuaSoH / 2);

	gCentral.gDrawWindowCustom(StartX, StartY, CuaSoW, CuaSoH, ATM_BOX_MAIN, gConfig.TTAS_TEXT_ENGINE[239]);
	gToolKit.CloseButton(411, 78, TAS_BoxAtm_BtnClose);
	RenderBitmap(0x17918, StartX + 9, StartY + 65, 430, 270, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
	gInterface.DrawFormat(eGold, StartX + 25, StartY + 35, 200, 3, gConfig.TTAS_TEXT_ENGINE[240], gObjUser.lpPlayer->Name);
	gInterface.DrawFormat(eGold, StartX + 25, StartY + 45, 200, 3, gConfig.TTAS_TEXT_ENGINE[241], gObjUser.lpPlayer->Name);
	gInterface.DrawFormat(eGold, StartX + 25, StartY + 55, 200, 3, gConfig.TTAS_TEXT_ENGINE[242]);
}