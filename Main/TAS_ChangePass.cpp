#include "StdAfx.h"
#include "Interface.h"
#include "User.h"
#include "Protocol.h"
#include "PrintPlayer.h"
#include "SItemOption.h"
#include "Import.h"
#include "Central.h"
#include "TAS_ChangePass.h"
#include "Util.h"
#include "Config.h"
TASTaiKhoan gTaiKhoan;

void TASTaiKhoan::DrawVoidDoiPass()
{
	WindowsChangePass();
}

void TASTaiKhoan::BinObeject()
{
	gInterface.BindObject(eChangePass_Main, 31461, 640, 419, -1, -1);  // 31461
	gInterface.BindObject(eChangePass_BTCLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(eChangePass_OLD, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eChangePass_NEW, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eChangePass_NEW1, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eChangePass_BTOK, 0x7A5B, 54, 30, -1, -1);
	gInterface.BindObject(FormPassLock, 0x7AA3, 170, 21, -1, -1);
}
short GetSymbolFromVK(WPARAM wParam)
{
	BYTE btKeyState[256];
	HKL hklLayout = GetKeyboardLayout(0);
	WORD Symbol;
	GetKeyboardState(btKeyState);
	if ((ToAsciiEx(wParam, MapVirtualKey(wParam, 0), btKeyState, &Symbol, 0, hklLayout) == 1))
	{
		return Symbol;
	}
	return 0;
}
bool TASTaiKhoan::EventClickChangePass(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eChangePass_BTCLOSE].EventTick);
	DWORD Delay_2 = (CurrentTick - gInterface.Data[eChangePass_BTOK].EventTick);
	// ----
	if (!gInterface.Data[eChangePass_Main].OnShow)
	{
		return false;
	}

	if (gInterface.IsWorkZone(eChangePass_OLD))
	{
		gInterface.Data[eChangePass_OLD].Attribute = 1;
	}
	else
	{
		gInterface.Data[eChangePass_OLD].Attribute = 0;
	}

	if (gInterface.IsWorkZone(eChangePass_NEW))
	{
		gInterface.Data[eChangePass_NEW].Attribute = 1;
	}
	else
	{
		gInterface.Data[eChangePass_NEW].Attribute = 0;
	}

	if (gInterface.IsWorkZone(eChangePass_NEW1))
	{
		gInterface.Data[eChangePass_NEW1].Attribute = 1;
	}
	else
	{
		gInterface.Data[eChangePass_NEW1].Attribute = 0;
	}

	if (gInterface.IsWorkZone(eChangePass_BTCLOSE))
	{
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eChangePass_BTCLOSE].OnClick = true;
			return true;
		}
		gInterface.Data[eChangePass_BTCLOSE].OnClick = false;
		if (Delay < 500)
		{
			return false;
		}
		gInterface.Data[eChangePass_BTCLOSE].EventTick = GetTickCount();
		this->OpenWindowsChangePass();
		sprintf(gInterface.Data[eChangePass_OLD].StatValue, "");		//NONE
		sprintf(gInterface.Data[eChangePass_OLD_HIDE].StatValue, "");	//NONE
		sprintf(gInterface.Data[eChangePass_NEW].StatValue, "");		//NONE
		sprintf(gInterface.Data[eChangePass_NEW_HIDE].StatValue, "");	//NONE
		sprintf(gInterface.Data[eChangePass_NEW1].StatValue, "");		//NONE
		sprintf(gInterface.Data[eChangePass_NEW_HIDE1].StatValue, "");	//NONE
	}
	else if (gInterface.IsWorkZone(eChangePass_BTOK))
	{
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eChangePass_BTOK].OnClick = true;
			return true;
		}
		gInterface.Data[eChangePass_BTOK].OnClick = false;
		if (Delay_2 < 500)
		{
			return false;
		}
		gInterface.Data[eChangePass_BTOK].EventTick = GetTickCount();
		//=== SEND GS
		CSENDGS_DOIMK pMsg;
		pMsg.TYPE = 0x01;
		memcpy(pMsg.PASS_OLD, gInterface.Data[eChangePass_OLD].StatValue, sizeof(pMsg.PASS_OLD));
		memcpy(pMsg.PASS_NEW, gInterface.Data[eChangePass_NEW].StatValue, sizeof(pMsg.PASS_NEW));
		memcpy(pMsg.PASS_NEW1, gInterface.Data[eChangePass_NEW1].StatValue, sizeof(pMsg.PASS_NEW1));
		pMsg.Head.set(0xFF, 0x91, sizeof(pMsg));
		DataSend((BYTE*)& pMsg, pMsg.Head.size);
		//===========
		this->OpenWindowsChangePass();

		sprintf(gInterface.Data[eChangePass_OLD].StatValue, "");		//NONE
		sprintf(gInterface.Data[eChangePass_OLD_HIDE].StatValue, "");	//NONE
		sprintf(gInterface.Data[eChangePass_NEW].StatValue, "");		//NONE
		sprintf(gInterface.Data[eChangePass_NEW_HIDE].StatValue, "");	//NONE
		sprintf(gInterface.Data[eChangePass_NEW1].StatValue, "");		//NONE
		sprintf(gInterface.Data[eChangePass_NEW_HIDE1].StatValue, "");	//NONE
	}
	// ----
	return false;
}
bool BienRutGon(DWORD Event, int eNum, int eNum2)
{
	char value[20];
	int is_backspace = false;
	int is_enter = false;
	int IsDelete = false;

	if (Event == VK_BACK)
	{
		is_backspace = true;
	}
	else if (Event == VK_RETURN)
	{
		is_enter = true;
	}
	else if (Event == VK_DELETE)
	{
		IsDelete = true;
	}
	else if ((Event >= 0x30 && Event <= 0x39) || (Event >= 0x60 && Event <= 0x69) || (Event >= 0x41 && Event <= 0x5A))
	{
		const int symbol = GetSymbolFromVK(Event);
		if (symbol == 0)
		{
			return 1;
		}
		char buff[10];
		sprintf(buff, "%c", symbol);
		strcpy_s(value, buff);
	}
	else
	{
		return true;
	}

	if (is_backspace == true)
	{
		if (!strcmp(gInterface.Data[eNum].StatValue, ""))
		{
			return true;
		}
		gInterface.Data[eNum].StatValue[strlen(gInterface.Data[eNum].StatValue) - 1] = '\0';
		gInterface.Data[eNum2].StatValue[strlen(gInterface.Data[eNum2].StatValue) - 1] = '\0';
	}
	else if (IsDelete == true)
	{
		strcpy_s(gInterface.Data[eNum].StatValue, "");
		strcpy_s(gInterface.Data[eNum2].StatValue, "");
	}
	else
	{
		if (strlen(gInterface.Data[eNum].StatValue) < 10)
		{
			if (!strcmp(gInterface.Data[eNum].StatValue, ""))
			{
				strcpy_s(gInterface.Data[eNum].StatValue, value);
				strcpy_s(gInterface.Data[eNum2].StatValue, "*");
			}
			else
			{
				strcat_s(gInterface.Data[eNum].StatValue, value);
				strcat_s(gInterface.Data[eNum2].StatValue, "*");
			}
		}
	}
}
bool TASTaiKhoan::TextBoxChangePass(DWORD Event)
{
	if (gInterface.Data[eChangePass_Main].OnShow && gInterface.Data[eChangePass_OLD].Attribute == 1)
	{
		BienRutGon(Event, eChangePass_OLD, eChangePass_OLD_HIDE);
	}	
	else if (gInterface.Data[eChangePass_Main].OnShow && gInterface.Data[eChangePass_NEW].Attribute == 1)
	{
		BienRutGon(Event, eChangePass_NEW, eChangePass_NEW_HIDE);		
	}
	else if (gInterface.Data[eChangePass_Main].OnShow && gInterface.Data[eChangePass_NEW1].Attribute == 1)
	{
		BienRutGon(Event, eChangePass_NEW1, eChangePass_NEW_HIDE1);		
	}
	return false;
}
void TASTaiKhoan::WindowsChangePass()
{
	if (CheckTAS_WINDOWS)
	{
		gInterface.Data[eChangePass_Main].OnShow = false;
		return;
	}
	if (!gInterface.Data[eChangePass_Main].OnShow)
	{
		return;
	}	
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;
	float CuaSoW = 200;
	float CuaSoH = 200;
	float StartX = JCResto+(MAX_WIN_WIDTH / 2) - (CuaSoW / 2);
	float StartY = ((MAX_WIN_HEIGHT - 51) / 2) - (CuaSoH / 2);
	gInterface.Data[eChangePass_Main].MaxX = StartX + CuaSoW;
	gInterface.Data[eChangePass_Main].MaxY = StartY + CuaSoH;

	gCentral.gDrawWindowCustomXClose(StartX, StartY, CuaSoW, CuaSoH, eChangePass_Main, gConfig.TTAS_TEXT_ENGINE[304]);

	gInterface.DrawGUI(eChangePass_BTCLOSE, StartX + 167, StartY);
	if (gInterface.IsWorkZone(eChangePass_BTCLOSE))
	{
		DWORD Color = eGray150;
		gInterface.DrawColoredGUI(eChangePass_BTCLOSE, gInterface.Data[eChangePass_BTCLOSE].X, gInterface.Data[eChangePass_BTCLOSE].Y, Color);
	}

	if (gInterface.Data[eChangePass_Main].FirstLoad == true)
	{
		if (strlen(gInterface.Data[eChangePass_OLD].StatValue) == 0)
			sprintf(gInterface.Data[eChangePass_OLD].StatValue, ""); //NONE
		if (strlen(gInterface.Data[eChangePass_NEW].StatValue) == 0)
			sprintf(gInterface.Data[eChangePass_NEW].StatValue, ""); //NONE
		if (strlen(gInterface.Data[eChangePass_NEW1].StatValue) == 0)
			sprintf(gInterface.Data[eChangePass_NEW1].StatValue, ""); //NONE
	}
	//=== Pass Cu
	float StepY = 50.0f;
	gInterface.DrawGUI(eChangePass_OLD, StartX + 15, StartY + StepY);
	if (gInterface.Data[eChangePass_OLD].Attribute == 1)
	{
		gInterface.DrawColoredGUI(eChangePass_OLD, StartX + 15 , StartY + StepY, eGray190);
	}
	gInterface.TASText(eWhite, StartX + 25 , StartY + StepY + 5, 170, 1, gConfig.TTAS_TEXT_ENGINE[305]);
	gInterface.TASText(eWhite, StartX + 100 , StartY + StepY + 5, 100, 1, gInterface.Data[eChangePass_OLD_HIDE].StatValue);

	//=== Pass Moi
	StepY = 80.0f;
	gInterface.DrawGUI(eChangePass_NEW, StartX + 15 , StartY + StepY);
	if (gInterface.Data[eChangePass_NEW].Attribute == 1)
	{
		gInterface.DrawColoredGUI(eChangePass_NEW, StartX + 15 , StartY + StepY, eGray190);
	}

	gInterface.TASText(eWhite,  StartX + 25 , StartY + StepY + 5, 170, 1, gConfig.TTAS_TEXT_ENGINE[306]);
	gInterface.TASText(eWhite,  StartX + 100 , StartY + StepY + 5, 100, 1, gInterface.Data[eChangePass_NEW_HIDE].StatValue);

	//=== Pass Moi 2
	StepY = 105.0f;
	gInterface.DrawGUI(eChangePass_NEW1, StartX + 15, StartY + StepY);
	if (gInterface.Data[eChangePass_NEW1].Attribute == 1)
	{
		gInterface.DrawColoredGUI(eChangePass_NEW1, StartX + 15, StartY + StepY, eGray190);
	}

	gInterface.TASText(eWhite, StartX + 25, StartY + StepY + 5, 170, 1, gConfig.TTAS_TEXT_ENGINE[307]);
	gInterface.TASText(eWhite, StartX + 100, StartY + StepY + 5, 100, 1, gInterface.Data[eChangePass_NEW_HIDE1].StatValue);

	gInterface.DrawButton(eChangePass_BTOK, StartX + (CuaSoW / 2) - 20 , StartY + CuaSoH - (50), 0, 0);

	if (gInterface.IsWorkZone(eChangePass_BTOK))
	{
		int ScaleY = 30;
		if (gInterface.Data[eChangePass_BTOK].OnClick)
		{
			ScaleY = 60;
		}
		gInterface.DrawButton(eChangePass_BTOK, StartX + (CuaSoW / 2) - 20 , StartY + CuaSoH - (50), 0, ScaleY);
	}
	if (gInterface.Data[eChangePass_Main].FirstLoad == true)
	{
		gInterface.Data[eChangePass_Main].FirstLoad = false;
	}
}
