#include "stdafx.h"
#include "CustomEventTime.h"
#include "CustomMessage.h"
#include "Defines.h"
#include "HealthBar.h"
#include "Interface.h"
#include "Util.h"
#include "Object.h"
#include "Import.h"
#include "Central.h"
#include "Protocol.h"
#include "CustomFont.h"
#include "User.h"
#include "PrintPlayer.h"
#include "Protect.h"
#include "Config.h"
#include "TAS_ToolKit.h"
#include "CBNewUiEx.h"

CCustomEventTime gCETime;
CNewUIScrollBar* ListScrollBarEvent = NULL;
bool UpdateMaxPosEvent	= false;
int ListMaxPerPageEvent = 17;

void CCustomEventTime::Load(CUSTOM_EVENT_INFO* info) // OK
{
	for (int n = 0; n < MAX_EVENTTIME; n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomEventTime::SetInfo(CUSTOM_EVENT_INFO info) // OK
{
	if (info.Index < 0 || info.Index >= MAX_EVENTTIME)
	{
		return;
	}

	this->m_CustomEventInfo[info.Index] = info;
}

void CCustomEventTime::ClearCustomEventTime() // OK
{
	for (int n = 0; n < MAX_EVENTTIME; n++)
	{
		gCustomEventTime[n].time = -1;
	}
	this->count = 0;
	this->EventTimeEnable = 0;
}

void CCustomEventTime::GCReqEventTime(PMSG_CUSTOM_EVENTTIME_RECV* lpMsg) // OK
{
	this->count = lpMsg->count;

	for (int n = 0; n < lpMsg->count; n++)
	{
		CUSTOM_EVENTTIME_DATA* lpInfo = (CUSTOM_EVENTTIME_DATA*)(((BYTE*)lpMsg) + sizeof(PMSG_CUSTOM_EVENTTIME_RECV) + (sizeof(CUSTOM_EVENTTIME_DATA)*n));

		this->gCustomEventTime[n].index = lpInfo->index;
		this->gCustomEventTime[n].time = lpInfo->time;

		if (this->gCustomEventTime[n].index >= 28 && this->gCustomEventTime[n].time != -1) this->Arena = 1;
	}

	this->EventTimeEnable = 1;
}

int NextEvent = 0;
int PreventEvent = 0;

void CCustomEventTime::DrawEventTimePanelWindow()
{
    if (!gInterface.Data[eEventTimePANEL_MAIN].OnShow)
    {
        return;
    }
    if (CheckTAS_WINDOWS6)
    {
        gInterface.Data[eEventTimePANEL_MAIN].OnShow = false;
        return;
    }
    int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

    float MainWidth = 400.0;
    float MainHeight = 320.0;
    float StartY = ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);
    float StartX1 = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
    float StartX = JCResto + StartX1 + 40;

    RenderBitmap(0x1791E, StartX - 10, StartY - 10, 533, 360, 0, 0, 1, 1, 1, 1, 0.0);
    RenderBitmap(0x17921, StartX - 10, StartY - 15, 367, 120, 0, 0, 1, 1, 1, 1, 0.0);

    gToolKit.CloseButton(StartX + MainWidth - 115.0f, StartY, TAS_EventTime_BtnClose);

    int PosXInvetoryImg = 280;
    int PosYInvetoryImg = 52;
    int DataListItem = 27;
    int SrollPosX = JCResto+180;
    if (ListScrollBarEvent == NULL)
    {
        ListScrollBarEvent = new CNewUIScrollBar();
        ListScrollBarEvent->Create(PosXInvetoryImg + SrollPosX, PosYInvetoryImg + 50, 220);
        if (ListScrollBarEvent)
        {
            ListScrollBarEvent->SetMaxPos((DataListItem <= ListMaxPerPageEvent) ? 0 : (DataListItem - ListMaxPerPageEvent));
            ListScrollBarEvent->SetPos(PosXInvetoryImg + SrollPosX, PosYInvetoryImg + 50);
        }
    }

    if (ListScrollBarEvent)
    {
        if (UpdateMaxPosEvent)
        {
            ListScrollBarEvent->SetMaxPos((DataListItem <= ListMaxPerPageEvent) ? 0 : (DataListItem - ListMaxPerPageEvent));
            UpdateMaxPosEvent = false;
        }

        ListScrollBarEvent->MouseWheelWindow = pCheckMouseOver(PosXInvetoryImg - 163, PosYInvetoryImg + 50, 315, 220);
        ListScrollBarEvent->Render();
        ListScrollBarEvent->UpdateMouseEvent();
        ListScrollBarEvent->Update();
    }

    int VipCharListPage = ListScrollBarEvent->GetCurPos();
    int line = 0;

    if (this->EventTimeEnable == 1)
    {
        gInterface.DrawFormat(eGold, StartX + 13,  StartY + 50, 52, 1, gCustomMessage.GetMessage(149));
        gInterface.DrawFormat(eGold, StartX + 100, StartY + 50, 52, 1, gCustomMessage.GetMessage(150));
        gInterface.DrawFormat(eGold, StartX + 170, StartY + 50, 52, 1, gCustomMessage.GetMessage(152));
        gInterface.DrawFormat(eGold, StartX + 250, StartY + 50, 52, 1, gCustomMessage.GetMessage(153));

        if ((GetTickCount() - this->EventTimeTickCount) > 1000)
        {
            for (int i = 0; i < this->count; i++)
            {
                if (this->gCustomEventTime[i].time > 0)
                {
                    this->gCustomEventTime[i].time--;
                }
            }
            this->EventTimeTickCount = GetTickCount();
        }

        char text2[30];
        int totalseconds;
        int hours;
        int minutes;
        int seconds;
        int days;
        DWORD Color;
        int CurPos = ListScrollBarEvent->GetCurPos();
        for (int i = CurPos; i < DataListItem && line < ListMaxPerPageEvent; i++)
        {
            if (this->gCustomEventTime[i].time <= -1)
            {
                continue;
            }

            float YPos = StartY + 64 + (line * 12);

            if (this->gCustomEventTime[i].time == 0)
            {
                wsprintf(text2, gConfig.TTAS_TEXT_ENGINE[46]);
            }
            else
            {
                totalseconds = this->gCustomEventTime[i].time;
                hours = totalseconds / 3600;
                minutes = (totalseconds / 60) % 60;
                seconds = totalseconds % 60;

                if (hours > 23)
                {
                    days = hours / 24;
                    wsprintf(text2, "%d ngày", days);
                }
                else
                {
                    wsprintf(text2, "%02d:%02d:%02d", hours, minutes, seconds);
                }
            }

            if (this->gCustomEventTime[i].time <= -1)
            {
                Color = eRed2;
            }
            else if (this->gCustomEventTime[i].time == 0)
            {
                Color = eExcellent;
            }
            else if (this->gCustomEventTime[i].time < 300)
            {
                Color = eExcellent;
            }
            else
            {
                Color = eYellow;
            }

            gInterface.DrawFormat(eWhite, StartX + 10, YPos, 80, 1, this->m_CustomEventInfo[i].Name);
            gInterface.DrawFormat(eWhite, StartX + 100, YPos, 60, 1, this->m_CustomEventInfo[i].Note);
            gInterface.DrawFormat(Color, StartX + 170, YPos, 52, 1, text2);

            if (pCheckMouseOver(StartX - 10, YPos, 310, 13) == 1)
            {
                CustomFont.Draw((HFONT)pFontBold, StartX, YPos, 0xFFFFFFFF, 0x00FBFF69, 290, 0, 3, " ");
            }

            for (int x = 0; x < MAX_EVENTTIME; x++)
            {
                if (i == x)
                {
                    if (this->gCustomEventTime[i].time < 300)
                    {
                        int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

                        gToolKit.DrawButtonIconMove(TAS_MOVE_EVENT + x, 31461, StartX, YPos, 291, 9);
                        gInterface.DrawFormat(eWhite, StartX + 230, YPos, 80, 1, "MOVE");
                    }
                }
            }
            line++;
        }
    }
}

void CCustomEventTime::OpenInterFace()
{

	if (gInterface.CheckWindow(ObjWindow::CreateGuild) || gInterface.CheckWindow(ObjWindow::ChatWindow) || gInterface.CheckWindow(ObjWindow::FriendList) || gInterface.CheckWindow(ObjWindow::NPC_Dialog) || gInterface.CheckWindow(ObjWindow::MuHelper) || gInterface.CheckWindow(ObjWindow::Store) || gInterface.CheckWindow(ObjWindow::Warehouse) || gInterface.CheckWindow(ObjWindow::Trade) || gInterface.CheckWindow(ObjWindow::CashShop))
	{
		return;
	}

	if ((GetTickCount() - gInterface.Data[eEventTimePANEL_MAIN].EventTick) < 500)
	{
		return;
	}

	gInterface.Data[eEventTimePANEL_MAIN].EventTick = GetTickCount();


	if (gInterface.Data[eEventTimePANEL_MAIN].OnShow == true)
	{
		gInterface.Data[eEventTimePANEL_MAIN].OnShow = false;

		if (gProtect.m_MainInfo.CustomInterfaceType != 4)
		{
			pSetCursorFocus = false;
		}
		return;
	}

	gInterface.CloseCustomWindow();
	this->ClearCustomEventTime();
	PMSG_CUSTOM_EVENTTIME_SEND pMsg;
	pMsg.header.set(0xF3, 0xE8, sizeof(pMsg));
	DataSend((BYTE*)&pMsg, pMsg.header.size);
	gInterface.Data[eEventTimePANEL_MAIN].OnShow = true;

	if (gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
}

void CCustomEventTime::OpenWindow()
{

	if (gInterface.CheckWindow(ObjWindow::CreateGuild) || gInterface.CheckWindow(ObjWindow::ChatWindow) || gInterface.CheckWindow(ObjWindow::FriendList) || gInterface.CheckWindow(ObjWindow::NPC_Dialog) || gInterface.CheckWindow(ObjWindow::MuHelper) || gInterface.CheckWindow(ObjWindow::Store) || gInterface.CheckWindow(ObjWindow::Warehouse) || gInterface.CheckWindow(ObjWindow::Trade) || gInterface.CheckWindow(ObjWindow::CashShop))
	{
		return;
	}

	if ((GetTickCount() - gInterface.Data[eEventTimePANEL_MAIN].EventTick) < 500)
	{
		return;
	}

	gInterface.Data[eEventTimePANEL_MAIN].EventTick = GetTickCount();


	if (gInterface.Data[eEventTimePANEL_MAIN].OnShow == true)
	{
		gInterface.Data[eEventTimePANEL_MAIN].OnShow = false;

		if (gProtect.m_MainInfo.CustomInterfaceType != 4)
		{
			pSetCursorFocus = false;
		}
		return;
	}

	gInterface.CloseCustomWindow();
	this->ClearCustomEventTime();
	PMSG_CUSTOM_EVENTTIME_SEND pMsg;
	pMsg.header.set(0xF3, 0xE8, sizeof(pMsg));
	DataSend((BYTE*)&pMsg, pMsg.header.size);
	gInterface.Data[eEventTimePANEL_MAIN].OnShow = true;

	if (gProtect.m_MainInfo.CustomInterfaceType != 4)
	{
		pSetCursorFocus = false;
	}
}

void CCustomEventTime::MOVE_EVENT(int MOVE_EVENT)
{
	MOVE_EVENT_REQ pRequest;
	pRequest.h.set(0xF3, 0x27, sizeof(pRequest));
	pRequest.MOVE_EVENT = MOVE_EVENT;
	DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
bool CCustomEventTime::EventMove(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	if (!gInterface.Data[eEventTimePANEL_MAIN].OnShow)
	{
		return false;
	}
	for (int i =  0; i < MAX_EVENTTIME; i++)
	{
		DWORD Delay = (CurrentTick - gInterface.Data[TAS_MOVE_EVENT + i].EventTick);
				
		if (gInterface.IsWorkZone(TAS_MOVE_EVENT + i))
		{
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[TAS_MOVE_EVENT + i].OnClick = true;
				return true;
			}

			gInterface.Data[TAS_MOVE_EVENT + i].OnClick = false;

			if (Delay < 500)
			{
				return false;
			}

			gInterface.CloseMenuWindow();
			gInterface.Data[eEventTimePANEL_MAIN].OnShow = false;

			this->MOVE_EVENT(i + 1);
			gInterface.Data[TAS_MOVE_EVENT + i].EventTick = GetTickCount();
		}				
	}
	return false;
}
