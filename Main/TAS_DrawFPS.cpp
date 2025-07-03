#include "stdafx.h"
#include "TAS_DrawFPS.h"
#include "Interface.h"
#include "Defines.h"

TASXemFps gFpsView;
bool TASXemFps::CombinedChecks()
{
	if ((gInterface.CheckWindow(Inventory)
		&& gInterface.CheckWindow(ExpandInventory)
		&& gInterface.CheckWindow(Store)) ||
		(gInterface.CheckWindow(Inventory)
			&& gInterface.CheckWindow(Warehouse)
			&& gInterface.CheckWindow(ExpandWarehouse)) ||
		(gInterface.CheckWindow(Inventory)
			&& gInterface.CheckWindow(Character)
			&& gInterface.CheckWindow(Store)))
		return true;
	return false;
}

void TASXemFps::RenderObjectFps()
{
	this->lastReport = GetTickCount();
	this->frameCount = 0;
}
void TASXemFps::MainFps() 
{
	this->frameCount++;
	if (GetTickCount() - this->lastReport >= 1000)
	{
		this->frameRate = this->frameCount / ((GetTickCount() - this->lastReport) / 1000);
		sprintf(this->FPS_REAL, "FPS: %d", this->frameRate);
		this->lastReport = GetTickCount();
		this->frameCount = 0;
	}
}