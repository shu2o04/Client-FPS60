#pragma once
#if(CB_EventArenaPvP)
#include "Protocol.h"
class CBArenaPvP
{
	#define WorldTime				*(float*)0x005EF5A1C
	enum TypeDataSend
	{
		eSendInfoNPCJoin = 0x01,
		eSendTime = 0x02,
		eSendBXHKill = 0x03,
		eSendInfoUser = 0x04,
		eSendInfoTeamPvP = 0x05,
		eSendClearInfo = 0x06,
	};
	struct PMSG_COUNTLIST
	{
		PSWMSG_HEAD header;
		int Count;
		BYTE TypeSend;
	};
	struct DATA_TIME_SEND
	{
		short Map;
		DWORD TimeCount;
		DWORD State;
	};
	struct DATA_BXH_KILL
	{
		char Name[11];
		int Kill;
		int Score;
	};
	struct DATA_INFOUSER_SEND
	{
		int Score;
		int Kills;
		int Deaths;
		int Rank;
	};
public:
	CBArenaPvP();
	void Draw();
	void RecvPacketGS(BYTE* Data);
	char TextVN[50][255];
	std::vector<DATA_INFOUSER_SEND> mDataInfoUserKill;
	std::vector<DATA_TIME_SEND> mDataTimeSend;
	std::vector<DATA_BXH_KILL> mDataBXHKiller;

private:

	 int GetTimeGMT();
	 void BRenderTimeCountDown(float x, float y, float w, int MatchTime);
	void DrawBXH();
	void DrawWindowNPC();
	void DrawPoint();
	
};
extern CBArenaPvP gCBArenaPvP;
#endif
