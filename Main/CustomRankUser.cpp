#include "stdafx.h"
#include "Defines.h"
#include "Import.h"
#include "Interface.h"
#include "Offset.h"
#include "Protect.h"
#include "Util.h"
#include "HealthBar.h"
#include "Import.h"
#include "Object.h"
#include "PrintPlayer.h"
#include "WindowsStruct.h"
#include "CustomRankUser.h"
#include "CustomFont.h"

#include "TAS_DanhHieu.h"
#include "TAS_QuanHam.h"
#include "TAS_TuChan.h"
#include "TAS_NewVip.h"

CCustomRankUser gCustomRankUser;

void CCustomRankUser::RenderShowLogRank(DWORD ViewPortAddr, int index, int PosX, int PosY)
{
	if (*(BYTE*)(ViewPortAddr + 0xE) == 0 && gProtect.m_MainInfo.RankUserOnlyOnSafeZone != 0)
	{
		return;
	}
	if ((((pMapNumber)<18) ? 0 : ((pMapNumber)>23) ? (((pMapNumber) == 53) ? 1 : 0) : 1) == 1) //Disable in Chaos Castle
	{
		return; 
	}
	if (gProtect.m_MainInfo.RankUserShowOverHead != 0 || *(int*)0x0E609E8 == 4)
	{
		pSetBlend(true);
		glColor3f(1.0, 1.0, 1.0);
		pGLSwitchBlend();
		pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
		pSetBlend(false);
	}
	if (MinimizarOfRank == 0)
	{	
		#if TAS_DANHHIEU
		gDanhHieu.ShowDanhHieuTAS(index,PosX,PosY);
		#endif
		#if TAS_QUANHAM
		gQuanHam.ShowQuanHamTAS(index,PosX,PosY);
		#endif
		#if TAS_TUCHAN
		gTuLuyen.ShowTuLuyenTAS(index,PosX,PosY);		
		#endif
		#if TAS_NEWVIP
		//gNewVip.ShowNewVipTAS(index,PosX,PosY);		
		#endif
	}	
}
void CCustomRankUser::GCReqRankLevelUser(PMSG_CUSTOM_RANKUSER * aRecv)
{
	if (aRecv == NULL)
	{
		return;
	}
	this->m_Data[aRecv->iIndex].m_Enabled = true;
	this->m_Data[aRecv->iIndex].m_Level = aRecv->iLevel;

	this->m_Data[aRecv->iIndex].m_RankTitle1 = aRecv->m_RankTitle1;	
	#if TAS_QUANHAM
	this->m_Data[aRecv->iIndex].m_RankTitle2 = aRecv->m_RankTitle2;
	#endif
	#if TAS_TUCHAN
	this->m_Data[aRecv->iIndex].m_RankTitle3 = aRecv->m_RankTitle3;	
	#endif
	#if TAS_NEWVIP
	this->m_Data[aRecv->iIndex].m_RankTitle4 = aRecv->m_RankTitle4;
	#endif
	#if TAS_HONHOAN
	this->m_Data[aRecv->iIndex].m_RankTitle5 = aRecv->m_RankTitle5;
	#endif
	#if HT_THUE_FLAG
	this->m_Data[aRecv->iIndex].m_RankTitle6 = aRecv->m_RankTitle6;
	#endif
	#if RESETCHANGE
	for (int i = 0; i < MAX_NUM_RSCHANGE; i++)
	{
		ReqResetChange[i]		= aRecv->ReqResetChange[i];
		ReqResetUpPoint[i]		= aRecv->ReqResetUpPoint[i];
		ReqResetCoin[i]			= aRecv->ReqResetCoin[i];
	}
	#endif
}
