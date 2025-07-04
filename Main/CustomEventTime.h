#pragma once

#include "Protocol.h"

#define MAX_EVENTTIME 42

struct PMSG_CUSTOM_EVENTTIME_RECV
{
	PSWMSG_HEAD h;
	int count;
};

struct PMSG_CUSTOM_EVENTTIME_SEND
{
	PSBMSG_HEAD header; // C1:BF:51

};

struct MOVE_EVENT_REQ
{
	PSBMSG_HEAD h;
	int	MOVE_EVENT;
	int MOVE_MAP;
};

struct CUSTOM_EVENTTIME_DATA
{
	int index;
	int time;
};

struct CUSTOM_EVENT_INFO
{
	int Index;
	char Name[40];
	char Note[40];
	char Gift[200];
	char BtnClick[40];
};


class CCustomEventTime
{
	public:
	void Load(CUSTOM_EVENT_INFO* info);
	void SetInfo(CUSTOM_EVENT_INFO info);
	void ClearCustomEventTime();
	void GCReqEventTime(PMSG_CUSTOM_EVENTTIME_RECV* lpMsg);
	void DrawEventTimePanelWindow();
	void OpenWindow();
	void OpenInterFace();
	bool CCustomEventTime::EventMove(DWORD Event);
	DWORD ClickTime;
	void MOVE_EVENT(int MOVE_EVENT);
	private:
	CUSTOM_EVENT_INFO m_CustomEventInfo[MAX_EVENTTIME];
	int count;
	CUSTOM_EVENTTIME_DATA gCustomEventTime[MAX_EVENTTIME];
	int EventTimeLoad;
	int EventTimeEnable;
	int EventTimeTickCount;
	int Page;
	int Arena;
	CUSTOM_EVENT_INFO Alldata;
	std::vector<CUSTOM_EVENT_INFO> m_EventInfoList;
};
extern CCustomEventTime gCETime;



