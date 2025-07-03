#pragma once
#include "stdafx.h"

#if(CongHuongV2)
struct PMSG_GSSendInfoClient
{
	PSBMSG_HEAD header;
	int mCH_TyLeThanhCong;
	int mCH_ResetMix;
	int mCH_TypeMix;
	int mCH_CheckLvItem;
	int mCH_CoinMix[3];
	int mCH_IndexItem[3];
	BYTE mCH_InfoItem[3][12];
};
class CongHuongV2New
{
	public:
	struct JCCoord
	{
		int X;
		int Y;
	};
	int  m_ScrollPos;
	void EventScrollPos(MOUSEHOOKSTRUCTEX* Mouse, WPARAM wParam);

	BOOL CH_EffectMixOn;
	int CH_IndexItem[3];
	int CH_CoinMix[3];
	int CH_TyLeThanhCong;
	int CH_ResetMix;
	int CH_TypeMix;
	int CH_CheckLvItem;
	BYTE CH_InfoItem[3][12];
	void XoaDataCongHuong();
	void DrawWindowCongHuong();
	DWORD LockMouseMoveClick;
	void CH_RecvInfoGSSend(PMSG_GSSendInfoClient* pMsg);
	void HienThiItem();
	bool RunCheckMe;
};
extern CongHuongV2New gCongHuong2;
#endif