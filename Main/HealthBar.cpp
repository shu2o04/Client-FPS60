#include "stdafx.h"
#include "CustomRankUser.h"
#include "Defines.h"
#include "HealthBar.h"
#include "Interface.h"
#include "User.h"
#include "Util.h"
#include "Object.h"
#include "Protect.h"
#include "Import.h"
#include "Common.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "TAS_DameRender.h"
#include "UIControl.h"
#include "Central.h"
#include "MonsterHpBar.h"

NEW_HEALTH_BAR gNewHealthBar[MAX_MAIN_VIEWPORT];
#define HPBARNEW 0
void ClearNewHealthBar() // OK
{
	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
		gNewHealthBar[n].index = 0xFFFF;
		gNewHealthBar[n].type	= 0;
		gNewHealthBar[n].rate	= 0;
		gNewHealthBar[n].rate2	= 0;
		gNewHealthBar[n].Level	= 0;
		gNewHealthBar[n].Life	= 0;
		gNewHealthBar[n].MonsID = 0;
	}
}

void InsertNewHealthBar(WORD index,BYTE type,BYTE rate,BYTE rate2,short Level, float Life, WORD MonsID) // OK
{
	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
		if(gNewHealthBar[n].index == 0xFFFF)
		{
			gNewHealthBar[n].index	= index;
			gNewHealthBar[n].type	= type;
			gNewHealthBar[n].rate	= rate;
			gNewHealthBar[n].rate2	= rate2;
			gNewHealthBar[n].Level	= Level;
			gNewHealthBar[n].Life	= Life;
			gNewHealthBar[n].MonsID = MonsID;
			return;
		}
	}
}

NEW_HEALTH_BAR* GetNewHealthBar(WORD index,BYTE type) // OK
{
	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
		if(gNewHealthBar[n].index != 0xFFFF)
		{
			if(gNewHealthBar[n].index == index && gNewHealthBar[n].type == type)
			{
				return &gNewHealthBar[n];
			}
		}
	}

	return 0;
}
void DrawNewHealthBar() // OK
{

	if ( pPlayerState == 4) //Select Character
	{
		return;
	}

	int PosX, PosY, LifeProgress, ShieldProgress;
	float LifeBarWidth = 40.0f;
	char LifeDisplay[25];

	VAngle Angle;

	if ( gProtect.m_MainInfo.DisablePartyHpBar == 1 )
	{
		if (pPartyMemberCount > 0)
		{
			for (int j = 0; j < pPartyMemberCount; j++)
			{
				signed int PartyNummber = *((DWORD*)&pPartyListStruct + 8 * j + 7);
				DWORD ViewportAddress = ((DWORD(__thiscall*)(void*,DWORD))0x0096A4C0)(((void*(*)())0x00402BC0)(),PartyNummber);
				if ( ViewportAddress )
				{
					Angle.X = *(float*)(ViewportAddress + 0x404);
					Angle.Y = *(float*)(ViewportAddress + 0x408);
					Angle.Z = *(float*)(ViewportAddress + 0x40C) + *(float*)(ViewportAddress + 0x3E8) + 100.0f;
					pGetPosFromAngle(&Angle, &PosX, &PosY);
					RenderBitmap(30019, (float)(PosX - 8), (float)(PosY - 32), 24.0, 24.0, 0.0, 0.40000001f, 1.4f, 1.4f, 1, 1, 0.0);
				}
			}
		}
	}
	else if (gProtect.m_MainInfo.DisablePartyHpBar == 0)
	{
		((void(*)())0x005BA770)();
	}
	
	if(HPMonsterName == 1)
	{	
		for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
		{
			lpViewObj lpObj = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), n);
			lpViewObj lpTarget = gObjUser.lpViewTarget;
			bool isTarget = 1;

			if (!lpTarget || (lpTarget->m_Model.ObjectType != emMonster && lpTarget->m_Model.ObjectType != emPlayer) || !lpTarget->m_Model.Unknown4 || lpTarget->aIndex != lpObj->aIndex)
			{
				isTarget = 0;
			}

			if (!lpObj)
			{
				continue;
			}

			if (lpObj->m_Model.Unknown4 == 0)
			{
				continue;
			}

			DWORD ViewportAddress = ((DWORD(__thiscall*)(void*,DWORD))0x0096A4C0)(((void*(*)())0x00402BC0)(), n);

			gObjUser.m_Logo[n].Active = 0;

			if(!ViewportAddress)
			{
				continue;
			}

			if(*(BYTE*)(ViewportAddress+0x30C) == 0)
			{
				continue;
			}
			Angle.X = *(float*)(ViewportAddress+0x404);
			Angle.Y = *(float*)(ViewportAddress+0x408);
			Angle.Z = *(float*)(ViewportAddress+0x40C) + *(float*)(ViewportAddress+0x3E8) + 100.0f;
			pGetPosFromAngle(&Angle, &PosX, &PosY);

			if (*(BYTE*)(ViewportAddress+0x320) == 1) //Check User Type
			{
				gObjUser.m_Logo[n].Active = 1;
				gObjUser.m_Logo[n].X = PosX;
				gObjUser.m_Logo[n].Y = PosY;
			}

			PosX -= (int)floor(LifeBarWidth / (double)2.0);

			PosY -= 10;

			NEW_HEALTH_BAR* lpNewHealthBar = GetNewHealthBar(*(WORD*)(ViewportAddress+0x7E),*(BYTE*)(ViewportAddress+0x320));
			char* name = (char*)(ViewportAddress+0x38);

			if(lpNewHealthBar == 0)
			{
				continue;
			}
			int LifePercent = lpNewHealthBar->rate / 10;
			int ShieldPercent = lpNewHealthBar->rate2 / 10;

			LifeProgress = (LifePercent > 10) ? 10 : LifePercent;
			ShieldProgress = (ShieldPercent > 10) ? 10 : ShieldPercent;

			if (*(BYTE*)(ViewportAddress + 0x320) == 1) //Check User
			{
				
				//HP
				glColor4f(0.19607843, 0.039215688, 0.0, 0.8);
				pDrawBarForm((double)(PosX + 1), (double)(PosY + 0.5), LifeBarWidth + 1, 5.0, 0.0, 0);
				pGLSwitch();
				
				glColor3f(0.98039216, 0.039215688, 0.0);
				for (int j = 0; j < LifeProgress; ++j)
				{
					pDrawBarForm((double)(PosX + 4 * j + 2), (double)(PosY + 2), 3.0, 2.0, 0.0, 0);
				}
				pGLSwitch();
				//SD
				glColor4f(0.19607843, 0.039215688, 0.0, 0.8);
				pDrawBarForm((double)(PosX + 1), (double)(PosY + 4), LifeBarWidth + 1, 5.0, 0.0, 0);
				pGLSwitch();
				glColor3f(0.98039216f, 5.039215688f, 0.0);
				for (int i = 0; i < ShieldProgress; ++i)
				{
					pDrawBarForm((double)(PosX + 4 * i + 2), (double)(PosY + 6), 3.0, 2.0, 0.0, 0);
				}
				pGLSwitch();
			}
			else
			{
				if (!isTarget)
				{
					continue;
				}
				CUSTOM_HPBAR* HpBarEx = gMonsterHpBar.GetHpBar(lpNewHealthBar->MonsID);
				if (HpBarEx == 0)
				{
					if (isTarget)
					{
						glColor4f(0.19607843, 0.039215688, 0.0, 0.8);
						pDrawBarForm((double)(PosX + 1), (double)(PosY + 1), LifeBarWidth, 4.0, 0.0, 0);
						pGLSwitch();

						glColor3f(0.98039216, 0.039215688, 0.0);

						for (int j = 0; j < LifeProgress; ++j)
						{
							pDrawBarForm((double)(PosX + 4 * j + 2), (double)(PosY + 2), 3.0, 2.0, 0.0, 0);
						}

						char IsTargetName[255];
						wsprintf(IsTargetName, "HP: %d%% - Lv: %d", lpNewHealthBar->rate, lpNewHealthBar->Level);
						pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
						pSetTextColor(pTextThis(), 255, 189, 25, 255);
						g_pRenderText.CRenderText(PosX - 8, PosY - 8, IsTargetName, 60, 0, 3, 0);
						g_pRenderText.CRenderText(PosX - 8, PosY - 15, name, 60, 0, 3, 0);
					}
				}
			}
			pGLSwitch();
		}
	}
	for (int n = 0; n < MAX_MAIN_VIEWPORT; n++)
	{
		DWORD ViewportAddress = ((DWORD(__thiscall*)(void*, DWORD))0x0096A4C0)(((void*(*)())0x00402BC0)(), n);
		gObjUser.m_Logo[n].Active = 0;
		if (!ViewportAddress)
		{
			continue;
		}
		if (*(BYTE*)(ViewportAddress + 0x30C) == 0)
		{
			continue;
		}
		Angle.X = *(float*)(ViewportAddress + 0x404);
		Angle.Y = *(float*)(ViewportAddress + 0x408);
		Angle.Z = *(float*)(ViewportAddress + 0x40C) + *(float*)(ViewportAddress + 0x3E8) + 100.0f;
		pGetPosFromAngle(&Angle, &PosX, &PosY);
		if (*(BYTE*)(ViewportAddress + 0x320) == 1) //Check User Type
		{
			gObjUser.m_Logo[n].Active = 1;
			gObjUser.m_Logo[n].X = PosX;
			gObjUser.m_Logo[n].Y = PosY;
			gCustomRankUser.RenderShowLogRank(ViewportAddress, *(WORD*)(ViewportAddress + 0x7E), PosX - 42, PosY);
		}						
		pGLSwitch();
	}
	#if(DAMAGE_RENDER_ENABLE)
	g_DamageRender.DrawRender();
	#endif
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
}