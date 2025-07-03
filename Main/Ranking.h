#pragma once
#include "stdafx.h"
#include "Protocol.h"

#define pIsKeyPress	((bool(*)(int))0x00791070)

#define iMaxCount	50
#define MAXTOP		100
#define MAXPAGE		5
#define MOVE_UP		40
#define MAX_LINE	11
#define MAX_LISTR	6
struct CharTop
{
	char Name[11];
	BYTE Is_Class;
	int Is_cLevel;
	int Is_ResetCount;
	int Is_MasterResetCount;
	int Is_ResetTime;
	int Is_TotalPoint;

	#if MAXTOP <= 40

	int Is_Strength;
	int Is_Dexterity;
	int Is_Vitality;
	int Is_Energy;
	int Is_Leadership;

	int Is_Life;
	int Is_MaxLife;
	int Is_Mana;
	int Is_MaxMana;
	int Is_BP;
	int Is_MaxBP;
	int Is_Shield;
	int Is_MaxShield;
	int Is_LucChien;
	int Is_PkCount;
	int Is_Kills;
	int Is_Deads;
	int Is_WcoinC;
	int Is_CoinAtm;
	int Is_ConnectStat;
	int Is_OnlineHours;

	int Is_BC;
	int Is_CC;
	int Is_DS;
	int Is_Win;
	int Is_Lose;
	int Is_Kboss;

	char Is_JoinDate[22];
	char Is_LastIP[16];
	#endif
	char Is_SvSub[11];
};
struct DGCharTop
{
	PWMSG_HEAD h;
	CharTop	tp[MAXTOP];
};
//
struct CharTopTP
{
	char Name[11];
	int Is_WcoinC;
	int Is_WcoinP;
	int Is_WcoinG;
	int Is_WcoinR;
	int Is_CoinAtm;
};
struct DGCharTopTP
{
	PWMSG_HEAD h;
	CharTopTP	tp[MAXTOP];
};
//
struct CharTopET
{
	char Name[11];
	int Is_BloodCS;
	int Is_ChaosCS;
	int Is_DevilCS;
};
struct DGCharTopET
{
	PWMSG_HEAD h;
	CharTopET	tp[MAXTOP];
};
//
struct CharTopTG
{
	char G_Name[8];
	char G_Master[11];
	int Is_GLevel;
	int Is_GScore;
	int Is_GMem;
	char Is_JoinDate[22];
};

struct DGCharTopTG
{
	PWMSG_HEAD h;
	CharTopTG	tp[MAXTOP];
};
//
struct CharTopPK
{
	char Name[11];
	int Is_Kills;
	int Is_Deads;
	int Is_OnlineHours;
	int Is_Win;
	int Is_Lose;
	int Is_Kboss;
	char Is_JoinDate[22];
};

struct DGCharTopPK
{
	PWMSG_HEAD h;
	CharTopPK	tp[MAXTOP];
};
//
struct CharTopMT
{
	char Name[11];
	int cLevel;
	int cPoint;
	int cExp;
};

struct DGCharTopMT
{
	PWMSG_HEAD h;
	CharTopMT	tp[MAXTOP];
};
struct DATA_VIEWTOPRANKING
{
	PSWMSG_HEAD header;
	char NameChar[11];
	char GuildName[11];
	BYTE GuildMark[32];
	BYTE Item[12][16];
	int aIndex;
};
struct REQUESTINFO_CHARTOP
{
	PSBMSG_HEAD header; // C3:F3:03
	char NameChar[11];
	int aIndex;
};
class cRanking
{
	public:
	cRanking();
	void cRanking::LoadImg();
	void cRanking::BingImg();
	void cRanking::GetPacketSender(DWORD ClickMouse, DWORD Delay, BYTE Pages, int Packet);
	void cRanking::ClickRanking(DWORD ClickMouse);

	void RecvInfo(DGCharTop* lpMsg);
	CharTop RankingChar[MAXTOP];

	void RecvInfoTP(DGCharTopTP* lpMsg);
	CharTopTP RankingCharTP[MAXTOP];

	void RecvInfoET(DGCharTopET* lpMsg);
	CharTopET RankingCharET[MAXTOP];

	void RecvInfoTG(DGCharTopTG* lpMsg);
	CharTopTG RankingCharTG[MAXTOP];

	void RecvInfoPK(DGCharTopPK* lpMsg);
	CharTopPK RankingCharPK[MAXTOP];

	void RecvInfoMT(DGCharTopMT* lpMsg);
	CharTopMT RankingCharMT[MAXTOP];

	std::vector<CharTop> DanhSachRank;

	void cRanking::SendMenuButton();
	void cRanking::GetBarInfo(int x, int y, int Value1, int Value2, DWORD BackColor, LPCSTR Char, ...);
	void Draw();
	bool Active;
	bool Show;
	int StartX;
	int StartY;
	int Page;
	DWORD ClickTick;
	int TrangRanking;
	DWORD ClickTime;

	DATA_VIEWTOPRANKING CacheDataUserTop;
	void GCReqInfoCharTop(DATA_VIEWTOPRANKING* lpMsg);
	bool CacheUserRank;
	bool SetItemCharTop;
	int Count[MAX_LISTR];
	int ListPage[MAX_LISTR];
	int CurPos[MAX_LISTR];
	int DataList[MAX_LISTR];
	bool UpdateMaxPos[MAX_LISTR];
	int ListMaxPer[MAX_LISTR];


};
extern cRanking gRanking;

void GetInfoCharTop(char* Name);
