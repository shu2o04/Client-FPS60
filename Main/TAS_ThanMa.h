#pragma once
#include "stdafx.h"
#if (THANMA)

struct PMSG_TIMEEVENT_CUSTOM
{
	PSBMSG_HEAD h;
	int TimeCount;
	int Map;
	int State;
};
struct PMSG_COUNTLIST_TM
{
	PSWMSG_HEAD header;
	int Count;
	int ScoreThienThan;
	int ScoreAcQuy;
	BYTE OpenBXHWindow;
};
struct EVENTHANMA_BXH
{
	char Name[11];
	int Kill;
	int Team;
};

class SubThanMa
{
public:
	void DrawTMPoint();
	void DrawWindowNPCTM();
	void DrawWindowBXHTM();
	float TyLeTGA;
	int totalseconds, hours, minutes, seconds, days;
	char ThoiGian[120];
	int DiemA, DiemB;

	void SendProtocol61();
	void SendProtocol62(BYTE* lpMsg);
	void SendProtocol63(BYTE* lpMsg);
	void DrawTMAllWindows();
	int	m_EventTMTimeCount;
	int m_EventTMState;
	int m_EventTMMap;
	int mCalcTimeEventTick;
	int m_TMScoreThienThan;
	int m_TMScoreAcQuy;
	int m_TMChienBXHC;
	EVENTHANMA_BXH m_ThanMaChienBXH[10];
	void TMReset() // OK
	{
		this->m_TMChienBXHC = 0;
		this->m_TMScoreThienThan = 0;
		this->m_TMScoreAcQuy = 0;
		this->mCalcTimeEventTick = 0;
		this->m_EventTMTimeCount = 0;
	}

};
extern SubThanMa gThanMa;
#endif