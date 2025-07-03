#include "stdafx.h"
#include "Import.h"
#include "TAS_FixSolution.h"

SuaLoiKhungHinh gFixSolution;

void SuaLoiKhungHinh::StartLoadPos()
{
	if (pWinWidth == 640)
	{
		this->SD_PosY = 4.0f;
		this->BP_PosY = 4.0f;
		this->DotStatus = 79.0f;
		this->KillBoss_Text_Y = 25;
	}
	else if (pWinWidth == 800)
	{
		this->SD_PosY = 5.0f;
		this->BP_PosY = 5.0f;
		this->DotStatus = 79.0f;
		this->KillBoss_Text_Y = 27;
	}
	else if (pWinWidth == 1024)
	{
		this->SD_PosY = 6.0f;
		this->BP_PosY = 6.0f;
		this->DotStatus = 77.5f;

		this->KillBoss_Text_Y = 30;
	}
	else if (pWinWidth == 1280)
	{
		this->SD_PosY = 8.0f;
		this->BP_PosY = 8.0f;
		this->DotStatus = 76.5f;
		this->KillBoss_Text_Y = 33;
	}
	else if (pWinWidth == 1360)
	{
		this->SD_PosY = 8.5f;
		this->BP_PosY = 8.5f;
		this->DotStatus = 76.5f;
		this->KillBoss_Text_Y = 33;
	}
	else if (pWinWidth == 1440)
	{
		this->SD_PosY = 8.9f;
		this->BP_PosY = 8.9f;
		this->DotStatus = 76.5f;
		this->KillBoss_Text_Y = 33;
	}
	else if (pWinWidth == 1600)
	{
		this->SD_PosY = 8.9f;
		this->BP_PosY = 8.9f;
		this->DotStatus = 76.5f;
		this->KillBoss_Text_Y = 34;
		this->HP_PosX = 48;
		this->HP_PosY = 48;
	}
	else if (pWinWidth == 1680)
	{
		this->SD_PosY = 11.0f;
		this->BP_PosY = 11.0f;
		this->DotStatus = 75.0f;
	}
	else if (pWinWidth == 1700)
	{
		this->SD_PosY = 11.0f;
		this->BP_PosY = 11.0f;
		this->DotStatus = 75.0f;
	}
	else if (pWinWidth == 1800)
	{
		this->SD_PosY = 11.0f;
		this->BP_PosY = 11.0f;
		this->DotStatus = 75.0f;
	}
	else if (pWinWidth == 1920)
	{
		this->SD_PosY = 12.0f;
		this->BP_PosY = 12.0f;
		this->DotStatus = 75.0f;
	}
}