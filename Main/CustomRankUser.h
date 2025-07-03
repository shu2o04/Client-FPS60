#ifndef _CUSTOM_RANK_USER_H
#define _CUSTOM_RANK_USER_H
#include "Protocol.h"
#include "Object.h"

struct PMSG_CUSTOM_RANKUSER
{
	PSBMSG_HEAD h;
	char szName[20];
	int iIndex;
	int iLevel;
	int m_RankTitle1;
	#if TAS_QUANHAM
	int m_RankTitle2;
	#endif
	#if TAS_TUCHAN
	int m_RankTitle3;
	#endif
	#if TAS_NEWVIP
	int m_RankTitle4;
	#endif
	#if(TAS_HONHOAN)
	WORD m_RankTitle5;
	#endif
	#if(HT_THUE_FLAG)
	int m_RankTitle6;
	#endif
	#if RESETCHANGE
	int ReqResetChange[MAX_NUM_RSCHANGE];
	int ReqResetCoin[MAX_NUM_RSCHANGE];
	int ReqResetUpPoint[MAX_NUM_RSCHANGE];
	#endif
};
// ---
struct CUSTOM_RANKUSER_DATA
{
	WORD m_Index;
	WORD m_Level;
	WORD m_RankTitle1;
	#if TAS_QUANHAM
	WORD m_RankTitle2;
	#endif
	#if TAS_TUCHAN
	WORD m_RankTitle3;
	#endif
	#if TAS_NEWVIP
	WORD m_RankTitle4;
	#endif
	#if(TAS_HONHOAN)
	WORD m_RankTitle5;
	#endif
	#if(HT_THUE_FLAG)
	int m_RankTitle6;
	#endif

	WORD m_iVipIcon;
	char m_Vip[20];
	BOOL m_Enabled;
	BYTE	Attribute;
};
// ---
class CCustomRankUser
{
	public:
	void RenderShowLogRank(DWORD ViewPortAddr, int index, int PosX, int PosY);
	void GCReqRankLevelUser(PMSG_CUSTOM_RANKUSER * aRecv);

	#if RESETCHANGE
	int ReqResetChange[MAX_NUM_RSCHANGE];
	int ReqResetCoin[MAX_NUM_RSCHANGE];
	int ReqResetUpPoint[MAX_NUM_RSCHANGE];
	#endif
	
	CUSTOM_RANKUSER_DATA m_Data[14000];
};
extern CCustomRankUser gCustomRankUser;
#endif