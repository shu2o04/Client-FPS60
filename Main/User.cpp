#include "stdafx.h"
#include "CustomNpcName.h"
#include "Offset.h"
#include "User.h"
#include "TMemory.h"
#include "Interface.h"
#include "Protocol.h"
#include "Object.h"
#include "Import.h"
#include "Defines.h"
#include "Util.h"
#include "User.h"
#include "PrintPlayer.h"
#include "Camera.h"
#include "Central.h"
#include "Controller.h"
#include "Config.h"
#include "HackCheck.h"
#include "TAS_CongPoint.h"

User gObjUser;

DWORD LastTime = 0;

void User::Load()
{
	this->m_TargetUpdateTick = 0;
	this->m_TargetType = false;
	this->m_CursorX = -1;
	this->m_CursorY = -1;
	this->m_MapNumber = -1;
	#if ADD_POINT
	SetCompleteHook(0xFF, 0x0077F822, &gAddPoint.ChangeCharInfo);
	#endif
}

void User::ToggleAuto() {


	if((GetTickCount() - gInterface.Data[ePLAYER_POINT].EventTick) < 1000)
	{
		return;
	}

	gInterface.Data[ePLAYER_POINT].EventTick = GetTickCount();

	this->is_auto = !this->is_auto;
}

void User::ToggleAutoTron() {


	if((GetTickCount() - gInterface.Data[ePLAYER_POINT].EventTick) < 1000)
	{
		return;
	}

	gInterface.Data[ePLAYER_POINT].EventTick = GetTickCount();

	this->is_autotron = !this->is_autotron;
}

void User::Refresh()
{
	float MainWidth = 230.0;
	float MainHeight = 70.0;
	float StartY = ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);

	this->lpPlayer			= &*(ObjectCharacter*)oUserObjectStruct;
	this->lpViewPlayer		= &*(ObjectPreview*)oUserPreviewStruct;
	this->GetTarget();

	this->m_CursorX			= pCursorX;
	this->m_CursorY			= pCursorY;
	this->m_MapNumber		= pMapNumber;

	if (pMapNumber == 62)
	{
		gCamera.Restore();
	}
	this->CoordenadaX = this->lpViewPlayer->MapPosX;
	this->CoordenadaY = this->lpViewPlayer->MapPosY;
	this->getLevel = gObjUser.lpPlayer->Level;
	this->GetPet = this->lpViewPlayer->PetSlot;
	this->InSafeZone = this->lpViewPlayer->InSafeZone;

	sprintf(this->getName,"%s",gObjUser.lpPlayer->Name);

	if ( gObjUser.GetActiveSkill() == 261 || 
		gObjUser.GetActiveSkill() == 552 || 
		gObjUser.GetActiveSkill() == 555 )
	{
		SetDouble(&pFrameSpeed1, 0.0004000);
		SetDouble(&pFrameSpeed2, 0.0002000);
	}
	else
	{
		SetDouble(&pFrameSpeed1, 0.0040000);
		SetDouble(&pFrameSpeed2, 0.0020000);
	}

	if (this->is_autotron != 1 && this->is_auto == 1) 
	{
		SetByte((PVOID)0x08793383, 1);
		gInterface.DrawFormat(eGold, 120,25, 200, 1,gConfig.ToggleAuto_TextVN[0]);
		gInterface.DrawFormat(eGold,  120,40, 100, 1,gConfig.ToggleAuto_TextVN[1]);
		gInterface.DrawFormat(eRed,  120,55, 200, 1,gConfig.ToggleAuto_TextVN[2]);
	}

	if (this->is_autotron == 1 && this->is_auto == 1) 
	{
		SetByte((PVOID)0x08793383, 1);
		gInterface.DrawFormat(eGold, 120,25, 200, 1,gConfig.ToggleAuto_TextVN[0]);
		gInterface.DrawFormat(eGold,  120,40, 100, 1,gConfig.ToggleAuto_TextVN[1]);
		gInterface.DrawFormat(eExcellent,  120,55, 200, 1,gConfig.ToggleAuto_TextVN[3]);

        pCursorX = (int)pWinWidth / pWinWidthReal / 2;
        pCursorY = (int)pWinHeight / pWinHeightReal / 2.1;

        int radius;
         
        (*(float*)gCamera.m_Address.Zoom <= 50)?radius = 120 -(*(float*)gCamera.m_Address.Zoom): (*(float*)gCamera.m_Address.Zoom >= 56)?radius = 120 -(*(float*)gCamera.m_Address.Zoom):radius = 110;

        int alpha = 100;
        static double angle = 0;
        angle += 0.1; 
         
        int Rand = rand() % 100;
        double x;
        double y;
        x = cos(angle) * radius;
        y = sin(angle) * radius;
        pCursorX -= x;
        pCursorY -= y;
	}
};

bool User::GetTarget()
{
	if( pViewNPCTargetID != -1 )
	{
		this->lpViewTarget	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), pViewNPCTargetID);

		this->m_TargetType	= 1;
		return true;
	}
	else if( pViewAttackTargetID != -1 )
	{
		this->lpViewTarget	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), pViewAttackTargetID);
		this->m_TargetType	= 2;
		return true;
	}
	
	if( this->lpViewTarget != 0 )
	{
		ZeroMemory(&this->lpViewTarget, sizeof(this->lpViewTarget));
	}
	
	this->m_TargetType = 0;
	return false;
}

int User::GetActiveSkill()
{
 lpCharObj lpPlayer  = &*(ObjectCharacter*)*(int*)(MAIN_CHARACTER_STRUCT);
 lpViewObj lpViewPlayer  = &*(ObjectPreview*)*(int*)(MAIN_VIEWPORT_STRUCT);
 return lpPlayer->pMagicList[lpViewPlayer->ActiveMagic];
}

void User::SetEventEffect(int PreviewStruct)
{

	lpViewObj lpPreview = &*(ObjectPreview*)PreviewStruct;

	if(lpPreview)
	{
		if(*(DWORD*)(MAIN_SCREEN_STATE) == GameProcess)
		{
			if (lpPreview->m_Model.ObjectType == emPlayer)
			{
					VAngle Angle;
					int PosX;
					int PosY;

					Angle.X = *(float*)(PreviewStruct+0x404);

					Angle.Y = *(float*)(PreviewStruct+0x408);

					Angle.Z = *(float*)(PreviewStruct+0x40C) + *(float*)(PreviewStruct+0x3E8) + 100.0f;

					pGetPosFromAngle(&Angle, &PosX, &PosY);
			}
		}
	}

	// ----
	if( lpPreview->CtlCode == 32 )
	{
		if( *(DWORD*)(PreviewStruct + 672) && lpPreview->Unknown23 != 5 )
		{
			pInitEventStatus(PreviewStruct);
		}
		// ----
		lpPreview->Unknown23 = 5;
	}
	// ----
	if( *(DWORD*)(PreviewStruct + 672) != 0 || !lpPreview->Unknown23 )
	{
		return;
	}
	// ----
	switch(lpPreview->Unknown23)
	{
	case 5:	//-> GM
		{
			if( pEventEffectThis(668) )
			{
				DWORD ModelID = 349;
				// ----
				if( !strncmp(lpPreview->Name, "[GM]", 4) )
				{
					ModelID = 406;
				}
				else if( !strncmp(lpPreview->Name, "[EM]", 4) )
				{
					ModelID = 407;
				}
				else if( !strcmp(lpPreview->Name, "Admin") )
				{
					ModelID = 408;
				}

				// ----
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect(pEventEffectThis(668), 408, 20, 1, 70.0, -5.0, 0.0, 0.0, 0.0, 45.0);
			}
		}
		break;
		// --
	case 6:
		{
			if( pEventEffectThis(668) )
			{
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect2(pEventEffectThis(668), 32241, 0, 20, 120.0, 0.0, 0.0);
			}
		}
		break;
		// --
	case 7:
		{
			if( pEventEffectThis(668) )
			{
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect2(pEventEffectThis(668), 32241, 1, 20, 120.0, 0.0, 0.0);
			}
		}
		break;
		// --
	case 8:
		{
			if( pEventEffectThis(668) )
			{
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect2(pEventEffectThis(668), 32241, 2, 20, 120.0, 0.0, 0.0);
			}
		}
		break;
		// --
	case 9:
		{
			if( pEventEffectThis(668) )
			{
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect2(pEventEffectThis(668), 32241, 3, 20, 120.0, 0.0, 0.0);
			}
		}
		break;
		// --
	case 10:
		{
			if( pEventEffectThis(668) )
			{
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect2(pEventEffectThis(668), 32241, 4, 20, 120.0, 0.0, 0.0);
			}
		}
		break;
		// --
	case 11:
		{
			if( pEventEffectThis(668) )
			{
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect2(pEventEffectThis(668), 32241, 5, 20, 120.0, 0.0, 0.0);
			}
		}
		break;
		// --
	case 12:
		{
			if( pEventEffectThis(668) )
			{
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect2(pEventEffectThis(668), 32241, 6, 20, 120.0, 0.0, 0.0);
			}
		}
		break;
		// --
	case 13:
		{
			if( pEventEffectThis(668) )
			{
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect2(pEventEffectThis(668), 32241, 7, 20, 120.0, 0.0, 0.0);
			}
		}
		break;
	default:
		{
			lpPreview->Unknown23 = 0;
		}
		break;
	}
}
#if(TAS_HONHOAN)
#define WorldTime					*(float*)0x005EF5A1C
#define EnableAlphaBlend			((void(__cdecl*)()) 0x636070)
#define DisableAlphaBlend			((void(__cdecl*)()) 0x00635F50)
#define RenderTerrainAlphaBitmap    ((void(__cdecl*)(int Texture,float xf,float yf,float SizeX,float SizeY,vec3_t Light,float Xoay,float Alpha,float Height, int DoCao)) 0x005DAD80)
void User::CBRenderCharacter(DWORD ObjectPointer, int Effect, float SizeX, float SizeY, vec3_t Color, int Type)
{
	lpViewObj a4 = &*(ObjectPreview*)(ObjectPointer);
	vec3_t vLight;
	float fLumi = sinf(WorldTime * 0.0015f) * 0.3f + 0.5f;
	Vector(fLumi * Color[0], fLumi * Color[1], fLumi * Color[2], vLight); //7 Mau
	EnableAlphaBlend();
	if (Type == 0)
	{
		RenderTerrainAlphaBitmap(Effect, a4->m_Model.VecPos.X, a4->m_Model.VecPos.Y, SizeX, SizeY, Color, WorldTime * 0.02f, 1.0, 5, 1);
	}
	else {
		RenderTerrainAlphaBitmap(Effect, a4->m_Model.VecPos.X, a4->m_Model.VecPos.Y, SizeX, SizeY, Color, -WorldTime * 0.02f, 1.0, 5, 1);
	}

	DisableAlphaBlend();
}
#endif
