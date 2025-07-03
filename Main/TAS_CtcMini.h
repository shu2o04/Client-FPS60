#pragma once
#include "stdafx.h"
#include "Protocol.h"

struct CTCMINI_CGPACKET
{
	PSBMSG_HEAD header; // C3:F3:03
	BYTE CongVao;

};

struct INFOCTCMINI_SENDCLIENT
{
	PSBMSG_HEAD header; // C3:F3:03
	BYTE OpenWindow;
	BYTE GuildWinOld;
};

struct CTCMINIKILL_SENDCLIENT
{
	PSBMSG_HEAD header; // C3:F3:03
	int	TimeCTCMini;
	BYTE Cong[3];
	BYTE Tru[3];
};
class CtcMiniClass
{
	public:
	void DrawCTCMiniWindow();
	void DrawCTCMiNiMap();
};
extern CtcMiniClass gCtcMini;