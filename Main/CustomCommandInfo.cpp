#include "StdAfx.h"
#include "CustomCommandInfo.h"
#include "Defines.h"
#include "Interface.h"
#include "Central.h"
#include "User.h"
#include "CustomFont.h"
#include "Config.h"
#include "TAS_ToolKit.h"
CCustomCommandInfo gCustomCommandInfo;

CCustomCommandInfo::CCustomCommandInfo()
{
	this->Init();
}

void CCustomCommandInfo::Init() // OK
{
	for(int n=0;n < MAX_CUSTOM_COMMAND;n++)
	{
		this->m_CustomCommandInfo[n].Index = -1;
	}
	this->Count = 0;
	this->Page = 0;
}

void CCustomCommandInfo::Load(CUSTOM_COMMAND_INFO* info) // OK
{

	for(int n=0;n < MAX_CUSTOM_COMMAND;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomCommandInfo::SetInfo(CUSTOM_COMMAND_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_COMMAND)
	{
		return;
	}
	this->Count = info.Index+1;
	this->m_CustomCommandInfo[info.Index] = info;
}

CUSTOM_COMMAND_INFO* CCustomCommandInfo::GetInfo(int index) // OK
{
	if(index < 0 || index >= MAX_CUSTOM_COMMAND)
	{
		return 0;
	}

	if(this->m_CustomCommandInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomCommandInfo[index];
}

void CCustomCommandInfo::DrawCommandWindow()
{
	if( !gInterface.Data[eCommand_MAIN].OnShow )
	{
		return;
	}
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	if ( gInterface.CheckWindow(Inventory)
	|| gInterface.CheckWindow(Character) //-- 13 & 16
	|| gInterface.CheckWindow(Warehouse) //-- 8
	|| gInterface.CheckWindow(Shop) //-- 12
	|| gInterface.CheckWindow(ChaosBox) //-- 9
	|| gInterface.CheckWindow(Trade) //-- 7
	|| gInterface.CheckWindow(Store) //-- 14
	|| gInterface.CheckWindow(OtherStore) //-- 15
	|| gInterface.CheckWindow(LuckyCoin1) //-- 60
	|| gInterface.CheckWindow(NPC_ChaosMix)
	|| gInterface.CheckWindow(MoveList) 
	) //-- 76
	{
		gInterface.Data[eCommand_MAIN].OnShow = false;
		return;
	}
	float MainWidth			= 380.0;
	float MainHeight		= 250.0;
	float StartBody			= ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);
	float StartY			= ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);
	float StartX			= JCResto+(MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (float)(29.0 / 2);
	DWORD Color = eGray100;
	float MoveX = 20.0f;
	float MoveY = 30.0f;
	gCentral.gDrawWindowCustom(StartX, StartY, MainWidth , MainHeight + 20, eCommand_MAIN, gConfig.TTAS_TEXT_ENGINE[41]);
	gToolKit.CloseButton(JCResto+477, 89, TAS_Comment_BtnClose);

	gCentral.gInfoBox(StartX + MoveX , StartY + 13 + MoveY, MainWidth - 50, 7.0, 0x00000096, 0, 0);
	gCentral.gInfoBox(StartX + MoveX , StartY + 35 + MoveY, MainWidth - 50, 180.0, 0x00000096, 0, 0);

	gInterface.DrawFormat(eGold,  StartX + 35,  StartBody + 46, 52, 1, gConfig.TTAS_TEXT_ENGINE[42]);
	gInterface.DrawFormat(eGold,  StartX + 125, StartBody + 46, 52, 1, gConfig.TTAS_TEXT_ENGINE[43]);
	gInterface.DrawFormat(eGold,  StartX + 210, StartBody + 46, 52, 1, gConfig.TTAS_TEXT_ENGINE[44]);

	for( int i = (25*Page)+0; i < (25*Page)+25; i++ )
	{
		if (this->m_CustomCommandInfo[i].Index == -1)
		{
			continue;
		}

		if (this->m_CustomCommandInfo[i].Color == 1)
		{
			Color = eGold;
		}
		else if (this->m_CustomCommandInfo[i].Color == 2)
		{
			Color = eWhite;
		}
		else if (this->m_CustomCommandInfo[i].Color == 3)
		{
			Color = eOrange;
		}
		else if (this->m_CustomCommandInfo[i].Color == 4)
		{
			Color = eRed2;
		}
		else if (this->m_CustomCommandInfo[i].Color == 5)
		{
			Color = eExcellent;
		}
		else if (this->m_CustomCommandInfo[i].Color == 6)
		{
			Color = eYellow;
		}
		else if (this->m_CustomCommandInfo[i].Color == 7)
		{
			Color = eSocket;
		}
		else
		{
			Color = eGold;
		}

		int x = i;

		if (this->Page > 0)
		{
			x = x-(25*Page);
		}

		gInterface.DrawFormat(Color, (int)StartX + 28, (int)StartBody + 70 + (x*10), 100, 1, this->m_CustomCommandInfo[i].Command);
		pDrawColorText(this->m_CustomCommandInfo[i].Description,  (int)StartX + 112, (int)StartBody + 70 + (x*10), 100, 0, Color, 0, 1);
		pDrawColorText(this->m_CustomCommandInfo[i].infoCommand,  (int)StartX + 200, (int)StartBody + 70 + (x*10), 180, 0, Color, 0, 1);
	}
	pDrawGUI(71520, StartX + (MainWidth / 2) - (200 / 2), StartBody + 285, 200, 1); //-- Divisor
}

void CCustomCommandInfo::OpenCommandWindow()
{
	if (gInterface.Data[eCommand_MAIN].OnShow == true)
	{
		gInterface.Data[eCommand_MAIN].OnShow = false;
		
		if(gProtect.m_MainInfo.CustomInterfaceType != 4)
		{
			pSetCursorFocus = false;
		}
		return;
	}

	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - gInterface.Data[TAS_Ranking_Main].EventTick);

	if(Delay < 1500 )
	{
		gInterface.Data[eCommand_MAIN].OnShow = false;
		return;
	}

	gInterface.CloseCustomWindow();
	gInterface.Data[eCommand_MAIN].EventTick = GetTickCount();
	gInterface.Data[eCommand_MAIN].OnShow = true;
	
	if(gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
}
