#include "stdafx.h"
#include "Interface.h"
#include "Ranking.h"
#include "Defines.h"
#include "TAS_DrawBoxAtm.h"
#include "TAS_MocNapNew.H"
#include "TAS_ItemLocker.h"
#include "Common.h"
#include "Util.h"
#include "Config.h"

void HadleClickClose()
{
	gRanking.Show = false;
	gInterface.Data[eEventTimePANEL_MAIN].OnShow = false;
	gInterface.Data[eJewelBank_MAIN].OnShow = false;
	gInterface.Data[eWindowInfo].OnShow = false;
	gInterface.Data[ePARTYSETTINGS_MAIN].OnShow == false;
	gInterface.Data[ePARTYSEARCH_MAIN].OnShow == false;
	gInterface.Data[eCommand_MAIN].OnShow = false;
	gInterface.Data[eWindow_NangCapHonHoan].OnShow = false;
	gInterface.Data[eWindow_NangCapQuanHam].OnShow = false;
	gInterface.Data[eWindow_NangCapTuChan].OnShow = false;
	gInterface.Data[eWindow_NangCapDanhHieu].OnShow = false;
	gInterface.Data[eWindow_NangCapNewVip].OnShow = false;
	gInterface.Data[eChangePass_Main].OnShow = false;
	gInterface.Data[TMC_MAIN].OnShow = false;
	gInterface.Data[eCTCMiniWindow].OnShow = false;
	gInterface.Data[TAS_RsChange_Main].OnShow = false;
	gInterface.Data[TAS_Ranking_Main].OnShow = false;
	gInterface.Data[TAS_ThueFlag_Main].OnShow = false;
	gInterface.Data[eMenu_MAIN].OnShow = false;
	gInterface.Data[eTopDame].OnShow = false;
	gInterface.Data[eSTATSADD_MAIN].OnShow = false;
	gInterface.Data[eRESETSTATS_MAIN].OnShow = false;
	gInterface.Data[TASRelife_MainBox].OnShow = false;
	gInterface.Data[eCustomShop].OnShow = false;
	gInterface.Data[eWindowMocNap].OnShow = false;
	gInterface.Data[eWindowIntros].OnShow = false;
	gInterface.Data[eWindowInfo].OnShow = false;
	gInterface.Data[eWindowHarmony].OnShow = false;
	gInterface.Data[eWindowDungLuyenItem].OnShow = false;
	gInterface.Data[BAUCUA_MAIN].OnShow = false;
}
bool Interface::HandleCloseEvent(DWORD Event, int btnCloseID, int windowID)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[btnCloseID].EventTick);
	if (KiemTraCacEvent_1 || !IsWorkZone(btnCloseID))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[btnCloseID].OnClick = true;
		return true;
	}
	this->Data[btnCloseID].OnClick = false;
	if (Delay < 500)
	{
		return false;
	}
	this->Data[btnCloseID].EventTick = GetTickCount();
	this->CloseMenuWindow();
	gInterface.Data[windowID].OnShow = false;
	return false;
}
bool Interface::TAS_OpenBoxCfg(DWORD Event)
{
	#define OKMENU TAS_CONFIG_BOX
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[OKMENU].EventTick);
	if (KiemTraCacEvent_1 || !IsWorkZone(OKMENU))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[OKMENU].OnClick = true;
		HadleClickClose();
		return true;
	}
	this->Data[OKMENU].OnClick = false;;
	if (Delay < 500)
	{
		return false;
	}
	this->Data[OKMENU].EventTick = GetTickCount();
	this->CloseMenuWindow();
	gInterface.OpenConfig(0);
	return false;
}
bool Interface::TAS_OpenBoxBSK(DWORD Event)
{
#define OKMENU TAS_MAIN_BOXSK
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[OKMENU].EventTick);
	if (KiemTraCacEvent_1 || !IsWorkZone(OKMENU))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[OKMENU].OnClick = true;
		HadleClickClose();
		return true;
	}
	this->Data[OKMENU].OnClick = false;;
	if (Delay < 500)
	{
		return false;
	}
	this->Data[OKMENU].EventTick = GetTickCount();
	this->CloseMenuWindow();
	PMSG_RESET_SEND pMsg;
	//pMsg.header.set(0xF7, 0x02, sizeof(pMsg));
	DataSend((LPBYTE)&pMsg, pMsg.header.size);
	return false;
}
bool Interface::TAS_OpenBoxAtm(DWORD Event)
{
#define OKMENU TAS_MAIN_ATM
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[OKMENU].EventTick);
	if (KiemTraCacEvent_1 || !IsWorkZone(OKMENU))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[OKMENU].OnClick = true;
		HadleClickClose();
		return true;
	}
	this->Data[OKMENU].OnClick = false;;
	if (Delay < 500)
	{
		return false;
	}
	this->Data[OKMENU].EventTick = GetTickCount();
	this->CloseMenuWindow();
	gBoxAtm.OpenDrawBoxAtm();
	return false;
}
bool Interface::TAS_RsCamera3D(DWORD Event)
{
	#define OKMENU TAS_MAIN_ZMCAM
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[OKMENU].EventTick);
	if (KiemTraCacEvent_1 || !IsWorkZone(OKMENU))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[OKMENU].OnClick = true;
		HadleClickClose();

		return true;
	}
	this->Data[OKMENU].OnClick = false;;
	if (Delay < 500)
	{
		return false;
	}
	this->Data[OKMENU].EventTick = GetTickCount();
	this->CloseMenuWindow();
	gInterface.SwitchCamera();
	return false;
}
bool Interface::TAS_Camera3D(DWORD Event)
{
#define OKMENU TAS_MAIN_RSCAM
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[OKMENU].EventTick);
	if (KiemTraCacEvent_1 || !IsWorkZone(OKMENU))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[OKMENU].OnClick = true;
		HadleClickClose();

		return true;
	}
	this->Data[OKMENU].OnClick = false;;
	if (Delay < 500)
	{
		return false;
	}
	this->Data[OKMENU].EventTick = GetTickCount();
	this->CloseMenuWindow();
	gInterface.CameraInit();
	return false;
}
bool Interface::TAS_ResetAuto(DWORD Event)
{
	#define OKMENU TAS_MAIN_ARESET
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[OKMENU].EventTick);
	if (KiemTraCacEvent_1 || !IsWorkZone(OKMENU))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[OKMENU].OnClick = true;
		HadleClickClose();
		return true;
	}
	this->Data[OKMENU].OnClick = false;;
	if (Delay < 500)
	{
		return false;
	}
	this->Data[OKMENU].EventTick = GetTickCount();
	this->CloseMenuWindow();
	PMSG_TICKET_SEND pMsg;
	pMsg.header.set(0xFC, 102, sizeof(pMsg)); // AutoReset Send
	DataSend((BYTE*)&pMsg, pMsg.header.size);
	return false;
}
bool Interface::TAS_BomMauAuto(DWORD Event)
{
	#define OKMENU TAS_AUTO_HP
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[OKMENU].EventTick);
	if (KiemTraCacEvent_1 || !IsWorkZone(OKMENU))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[OKMENU].OnClick = true;
		HadleClickClose();
		return true;
	}
	this->Data[OKMENU].OnClick = false;;
	if (Delay < 500)
	{
		return false;
	}
	this->Data[OKMENU].EventTick = GetTickCount();
	this->CloseMenuWindow();
	PMSG_TICKET_SEND pMsg;
	pMsg.header.set(0xFC, 103, sizeof(pMsg)); // Bom mau Send
	DataSend((BYTE*)&pMsg, pMsg.header.size);
	return false;
}
bool Interface::TAS_BuffAuto(DWORD Event)
{
	#define OKMENU TAS_AUTO_BF
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[OKMENU].EventTick);
	if (KiemTraCacEvent_1 || !IsWorkZone(OKMENU))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[OKMENU].OnClick = true;
		HadleClickClose();
		return true;
	}
	this->Data[OKMENU].OnClick = false;;
	if (Delay < 500)
	{
		return false;
	}
	this->Data[OKMENU].EventTick = GetTickCount();
	this->CloseMenuWindow();
	PMSG_TICKET_SEND pMsg;
	pMsg.header.set(0xFC, 104, sizeof(pMsg)); // Buff Send
	DataSend((BYTE*)&pMsg, pMsg.header.size);
	return false;
}
bool Interface::TAS_ItemBlock(DWORD Event)
{
	#define OKMENU TAS_ITEM_BLOCK
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[OKMENU].EventTick);
	if (KiemTraCacEvent_1 || !IsWorkZone(OKMENU))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[OKMENU].OnClick = true;
		HadleClickClose();
		return true;
	}
	this->Data[OKMENU].OnClick = false;;
	if (Delay < 500)
	{
		return false;
	}
	this->Data[OKMENU].EventTick = GetTickCount();
	this->CloseMenuWindow();
	nInterface.OpenWindowLock();
	return false;
}
bool Interface::TAS_Pklock(DWORD Event)
{
#define OKMENU TAS_PK_LOCK
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[OKMENU].EventTick);
	if (KiemTraCacEvent_1 || !IsWorkZone(OKMENU))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[OKMENU].OnClick = true;
		HadleClickClose();
		return true;
	}
	this->Data[OKMENU].OnClick = false;;
	if (Delay < 500)
	{
		return false;
	}
	this->Data[OKMENU].EventTick = GetTickCount();
	this->CloseMenuWindow();
	PVPAttack = !PVPAttack;
	if (PVPAttack != 0)
	{
		gInterface.DrawMessage(1, gConfig.TTAS_TEXT_ENGINE[16]);
		SetByte(0x0059AF53 + 2, 0);
		SetByte(0x0059B248 + 2, 0);
	}
	else
	{
		gInterface.DrawMessage(1, gConfig.TTAS_TEXT_ENGINE[17]);
		SetByte(0x0059AF53 + 2, 1);
		SetByte(0x0059B248 + 2, 1);
	}
	return false;
}
bool Interface::TAS_DrawMenu_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	#define EVENTICK eMenu_CLOSE
	DWORD Delay = (CurrentTick - this->Data[EVENTICK].EventTick);
	if (!this->Data[eMenu_MAIN].OnShow || !IsWorkZone(EVENTICK))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[EVENTICK].OnClick = true;
		return true;
	}
	this->Data[EVENTICK].OnClick = false;
	if (Delay < 500)
	{
		return false;
	}
	this->Data[EVENTICK].EventTick = GetTickCount();
	this->CloseMenuWindow();
	return false;
}

bool Interface::TAS_Ranking_Close(DWORD Event)
{
	#define OKMENU TAS_Ranking_BtnClose
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[OKMENU].EventTick);
	if (KiemTraCacEvent_1 || !IsWorkZone(OKMENU))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[OKMENU].OnClick = true;
		return true;
	}
	this->Data[OKMENU].OnClick = false;;
	if (Delay < 500)
	{
		return false;
	}
	this->Data[OKMENU].EventTick = GetTickCount();
	this->CloseMenuWindow();
	gRanking.Show = false;
	return false;
}
bool Interface::TAS_CtcMini_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_CtcMini_BtnClose, eCTCMiniWindow);
}
bool Interface::TAS_Comment_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_Comment_BtnClose, eCommand_MAIN);
}
bool Interface::TAS_TuChan_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_TuChan_BtnClose, eWindow_NangCapTuChan);
}
bool Interface::TAS_DanhHieu_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_DanhHieu_BtnClose, eWindow_NangCapDanhHieu);
}
bool Interface::TAS_QuanHam_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_QuanHam_BtnClose, eWindow_NangCapQuanHam);
}
bool Interface::TAS_HonHoan_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_HonHoan_BtnClose, eWindow_NangCapHonHoan);
}
bool Interface::TAS_ThueFlag_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_ThueFlag_BtnClose, TAS_ThueFlag_Main);
}
bool Interface::TAS_Relife_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_Relife_BtnClose, TASRelife_MainBox);
}
bool Interface::TAS_LSpin_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_LSpin_BtnClose, eLuckySpin);
}
bool Interface::TAS_MocNap_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_MocNap_BtnClose, eWindowMocNap);
}
bool Interface::TAS_CuaHang_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_CuaHang_BtnClose, eCustomShop);
}
bool Interface::TAS_RsChange_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_RsChange_BtnClose, TAS_RsChange_Main);
}
bool Interface::TAS_NewVip_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_NewVip_BtnClose, eWindow_NangCapNewVip);
}
bool Interface::TAS_Harmony_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_Harmony_BtnClose, eWindowHarmony);
}
bool Interface::TAS_ItemTrade_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_ItemTrade_BtnClose, eWindowDoiItem);
}
bool Interface::TAS_Arena_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, Arena_CLOSE, eWindowNPCArenaPvP);
}
bool Interface::TAS_BoxAtm_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_BoxAtm_BtnClose, ATM_BOX_MAIN);
}
bool Interface::TAS_EventTime_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_EventTime_BtnClose, eEventTimePANEL_MAIN);
}
bool Interface::TAS_DungLuyen_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_DungLuyen_BtnClose, eWindowDungLuyenItem);
}
bool Interface::TAS_BxhArena_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_BxhArena_BtnClose, eWindowBXHArenaPvP);
}
bool Interface::TAS_Option_Close(DWORD Event)
{
	return this->HandleCloseEvent(Event, TAS_Option_BtnClose, Option_Main);
}