#include "StdAfx.h"
#include "Util.h"
#include "ServerListMove.h"

CServerSelWin g_ServerSelWin;

void CServerSelWin::SelWin_SetSize(BYTE * pCWin, int nWidth, int nHeight, int eChangedPram)
{
	CWin_SetSize(pCWin, WindowWidth, nHeight, eChangedPram);
}

void CServerSelWin::SetPositionServerGroupA(BYTE * CButton, int cx, int cy, int eChangedPram)
{
	cx = 100;//(WindowWidth / 2) - 400;
	ServerSel_SpiriteSetPosition(CButton, cx, cy, eChangedPram);
}

void CServerSelWin::SetPositionServerGroupB(BYTE * CButton, int cx, int cy, int eChangedPram)
{
	cx = 100;//(WindowWidth / 2) - 400;
	ServerSel_SpiriteSetPosition(CButton, cx, cy, eChangedPram);
}

void CServerSelWin::Init()
{
	SetCompleteHook(0xE8, 0x00413EFE, &CServerSelWin::SelWin_SetSize);
	SetCompleteHook(0xE8, 0x004140D9, &CServerSelWin::SetPositionServerGroupA);
	SetCompleteHook(0xE8, 0x0041412E, &CServerSelWin::SetPositionServerGroupB);
}