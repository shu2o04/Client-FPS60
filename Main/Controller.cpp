#include "stdafx.h"
#include "resource.h"
#include "Controller.h"
#include "CustomCommandInfo.h"
#include "CustomEventTime.h"
#include "Defines.h"
#include "OffTrade.h"
#include "Protocol.h"
#include "Import.h"
#include "Interface.h"
#include "Protect.h"
#include "TMemory.h"
#include "CSCharacterS13.h"
#include "CMacroUIEx.h"
#include "Camera.h"
#include "TrayModeNew.h"
#include "MiniMap.h"
#include "MiniMapTron.h"
#include "WindowsStruct.h"
#include "Central.h"
#include "User.h"
#include "PartySearchSettings.h"
#include "PartySearch.h"
#include "CustomLuckySpin.h"
#include "CustomJewelBank.h"
#include "TAS_ResetChange.h"
#include "Ranking.h"
#include "TAS_ChangePass.h"
#include "TAS_CongHuongV2.h"
#include "TAS_CongPoint.h"
#include "TAS_Relife.h"
#include "TAS_MocNapNew.H"
#include "ThueFlag.h"
Controller	gController;

#if(NOTICE_MES==1)
char Notice_1[1024];
char Notice_2[1024];
char CameraNotAc[1024];
char CameraOn[1024];
char CameraOff[1024];
char CameraDefault[1024];
char GlowOn[1024];
char GlowOff[1024];
char AutoOn[1024];
char AutoOff[1024];
#endif

void __declspec(naked) iconHook()
{
	static DWORD dwIcon = (DWORD)LoadIcon(gController.Instance, MAKEINTRESOURCE(IDI_ICON1));
	static DWORD dwJmp = 0x004D0E3C;

	_asm
	{
		MOV EAX, dwIcon
		JMP dwJmp
	}
}

bool Controller::Load()
{
	if( !this->MouseHook )
	{
		this->MouseHook = SetWindowsHookEx(WH_MOUSE, this->Mouse, gController.Instance, GetCurrentThreadId());
		#if(NOTICE_MES==1)
		GetPrivateProfileString("Notice", "Notice_1", "", Notice_1, 1024, MENU_NOTE_FILE);
		GetPrivateProfileString("Notice", "Notice_2", "", Notice_2, 1024, MENU_NOTE_FILE);
		GetPrivateProfileString("Notice", "CameraNotAc", "", CameraNotAc, 1024, MENU_NOTE_FILE);
		GetPrivateProfileString("Message", "CameraOn", "", CameraOn, 1024, MENU_NOTE_FILE);
		GetPrivateProfileString("Message", "CameraOff", "", CameraOff, 1024, MENU_NOTE_FILE);
		GetPrivateProfileString("Message", "CameraDefault", "", CameraDefault, 1024, MENU_NOTE_FILE);
		GetPrivateProfileString("Message", "GlowOn", "", GlowOn, 1024, MENU_NOTE_FILE);
		GetPrivateProfileString("Message", "GlowOff", "", GlowOff, 1024, MENU_NOTE_FILE);
		GetPrivateProfileString("Message", "AutoOn", "", AutoOn, 1024, MENU_NOTE_FILE);
		GetPrivateProfileString("Message", "AutoOff", "", AutoOff, 1024, MENU_NOTE_FILE);
		#endif
		if( !this->MouseHook )
		{
			return false;
		}
	}
	if( !this->KeyboardHook )
	{
		this->KeyboardHook = SetWindowsHookExA(WH_KEYBOARD, this->Keyboard, gController.Instance, GetCurrentThreadId());
	}
	SetOp((LPVOID)0x004D0E2F, iconHook, ASM::CALL);
	return true;
}


LRESULT Controller::Mouse(int Code, WPARAM wParam, LPARAM lParam)
{
	if( GetForegroundWindow() != pGameWindow )
	{
		return CallNextHookEx(gController.MouseHook, Code, wParam, lParam);
	}
	// ----
	MOUSEHOOKSTRUCTEX * Mouse	= (MOUSEHOOKSTRUCTEX*)lParam;
	gController.wMouse = wParam;

	switch(wParam)
	{
		case WM_LBUTTONUP:
		case WM_LBUTTONDOWN:
		{
			
			gRanking.ClickRanking(wParam);
			gTaiKhoan.EventClickChangePass(wParam);
			gCustomJewelBank.CommandNext(wParam);
			gCustomJewelBank.CommandPrev(wParam);
			gCustomJewelBank.EventJewelBankWindow_Close(wParam);
			gCustomJewelBank.EventJewelBankWithDraw(wParam);

			gInterface.TAS_CtcMini_Close(wParam);
			gInterface.TAS_Ranking_Close(wParam);
			gInterface.TAS_Comment_Close(wParam);
			gInterface.TAS_TuChan_Close(wParam);
			gInterface.TAS_DanhHieu_Close(wParam);
			gInterface.TAS_QuanHam_Close(wParam);
			gInterface.TAS_HonHoan_Close(wParam);
			gInterface.TAS_ThueFlag_Close(wParam);
			gInterface.TAS_Relife_Close(wParam);
			gInterface.TAS_LSpin_Close(wParam);
			gInterface.TAS_MocNap_Close(wParam);
			gInterface.TAS_CuaHang_Close(wParam);
			gInterface.TAS_RsChange_Close(wParam);
			gInterface.TAS_NewVip_Close(wParam);
			gInterface.TAS_Harmony_Close(wParam);
			gInterface.TAS_ItemTrade_Close(wParam);
			gInterface.TAS_Arena_Close(wParam);
			gInterface.TAS_BoxAtm_Close(wParam);
			gInterface.TAS_EventTime_Close(wParam);
			gInterface.TAS_DungLuyen_Close(wParam);
			gInterface.TAS_BxhArena_Close(wParam);
			gInterface.TAS_Option_Close(wParam);

			gInterface.TASEventClick(wParam);
			
			gInterface.EventDrawMenu_Open(wParam);
			gInterface.TAS_DrawMenu_Close(wParam);
			gInterface.TAS_ResetAuto(wParam);
			gInterface.TAS_BomMauAuto(wParam);
			gInterface.TAS_BuffAuto(wParam);
			gInterface.TAS_Camera3D(wParam);
			gInterface.TAS_RsCamera3D(wParam);
			gInterface.TAS_OpenBoxAtm(wParam);
			gInterface.TAS_OpenBoxBSK(wParam);
			gInterface.TAS_OpenBoxCfg(wParam);
			gInterface.TAS_ItemBlock(wParam);
			gInterface.TAS_Pklock(wParam);

			#if (RESETCHANGE==1)
			gResetChange.ButtonResetChange(wParam);
			#endif
			#if (CongHuongV2)
			gCongHuong2.EventScrollPos(Mouse, wParam);
			#endif
			gCETime.EventMove(wParam);

            #if(PARTYSEARCH==1)
			gPartySearch.EventPartySearchWindow_All(wParam);
			gPartySearch.EventPartySettingsWindow_Main(wParam);
            #endif
			#if(VONGQUAY_NEW)
			gLuckySpin.EventWindow_Main(wParam);
			#endif

			gInterface.EventConfirm_CANCEL(wParam);
			gInterface.EventConfirm_OK(wParam);
			EventMuOffhelper(wParam);
			if(gProtect.m_MainInfo.CustomInterfaceType == 2)
			{
				gInterface.EventNewInterface_All(wParam);
			}
			gOffTrade.EventOffTradeWindow_Main(wParam);
			gOffTrade.EventCloseTradeWindow_Main(wParam);

			#if ADD_POINT
			gAddPoint.EventCharacterWindow(wParam);
			gAddPoint.EventStatsAddWindow(wParam);
			#endif
			#if RELIFE
			G_TASRelife.MainWindowsRelife(wParam);
			#endif
		}
		
		break;
		
	}
	return CallNextHookEx(gController.MouseHook, Code, wParam, lParam);
}

LRESULT Controller::Keyboard(int Code, WPARAM wParam, LPARAM lParam)
{
	if( GetForegroundWindow() != pGameWindow )
	{
		return CallNextHookEx(gController.KeyboardHook, Code, wParam, lParam);
	}

	if (Code < 0) return CallNextHookEx(gController.KeyboardHook, Code, wParam, lParam);
	
	if( (Code == HC_ACTION) && (wParam == WM_KEYDOWN))
	{
		KBDLLHOOKSTRUCT Hook = *((KBDLLHOOKSTRUCT*)lParam);
		switch(Hook.vkCode)
		{
			case 0x48:
			{
				gCETime.OpenWindow();
			}
			break;
			case VK_ESCAPE:
			{
				if (gInterface.Data[ePARTYSEARCH_MAIN].OnShow == true)
				{
					gInterface.Data[ePARTYSEARCH_MAIN].OnShow = false;				
					if(gProtect.m_MainInfo.CustomInterfaceType != 4)
					{
						pSetCursorFocus = false;
					}
				}

				if (gInterface.Data[ePARTYSETTINGS_MAIN].OnShow == true)
				{
					gInterface.Data[ePARTYSETTINGS_MAIN].OnShow == false;				
					if(gProtect.m_MainInfo.CustomInterfaceType != 4)
					{
						pSetCursorFocus = false;
					}
				}

				if (gInterface.Data[eCommand_MAIN].OnShow == true  && (gProtect.m_MainInfo.CustomInterfaceType != 4))
				{
					gInterface.Data[eCommand_MAIN].OnShow = false;
					pSetCursorFocus = false;
					return -1;
				}

				if (gInterface.Data[eEventTimePANEL_MAIN].OnShow == true && (gProtect.m_MainInfo.CustomInterfaceType != 4))
				{
					gInterface.Data[eEventTimePANEL_MAIN].OnShow = false;
					pSetCursorFocus = false;
					return -1;
				}
				if (gInterface.Data[eJewelBank_MAIN].OnShow)
				{
					gInterface.Data[eJewelBank_MAIN].Close();
					return -1;
				}
				if (gInterface.Data[TAS_ThueFlag_Main].OnShow)
				{
					gInterface.Data[TAS_ThueFlag_Main].Close();
					return -1;
				}
				if (gInterface.Data[eWindowInfo].OnShow)
				{
					gInterface.Data[eWindowInfo].Close();
					return -1;
				}
			
				if (gInterface.Data[TAS_Ranking_Main].OnShow)
				{
					gInterface.Data[TAS_Ranking_Main].Close();
					return -1;
				}
			}
			break;
			default:
			break;
		}
	}
	if( ((lParam >> 31) & 1) && (Code == HC_ACTION) )
	{
		if(GetForegroundWindow() != pGameWindow || pPlayerState != GameProcess)
		{
			return CallNextHookEx(gController.KeyboardHook, Code, wParam, lParam);
		}
		gController.wKeyBord = wParam;
	}
	if(GetForegroundWindow() == pGameWindow && pPlayerState == GameProcess) // 
	if(Code == HC_ACTION)
	{
		if(((DWORD)lParam & (1 << 30)) != 0 && ((DWORD)lParam & (1 << 31)) != 0)
		{
			if( GetForegroundWindow() == *(HWND*)(0x00E8C578) )
			{			
				gTaiKhoan.TextBoxChangePass(wParam);
				#if ADD_POINT
				gAddPoint.ControlTextBox(wParam);
				#endif
				
			}
		}
	}
	return CallNextHookEx(gController.KeyboardHook, Code, wParam, lParam);
}
LRESULT Controller::Window(HWND Window, DWORD Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{

		case TRAYMODE_ICON_MESSAGE:
		{
			switch(lParam)
			{
				case WM_LBUTTONDBLCLK:
				{
					gTrayMode.SwitchState();
				}
				break;
			}
		}
		break;
	}
	return CallWindowProc((WNDPROC)gTrayMode.TempWindowProc, Window, Message, wParam, lParam);
}


