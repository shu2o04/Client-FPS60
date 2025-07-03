#include "stdafx.h"
#include "CSCharacterS13.h"
#include "Util.h"
#include "Interface.h"
#include "zzzMathLib.h"
#include "Offset.h"
#include "User.h"
#include "Defines.h"
#include "TMemory.h"
#include "import.h"
#include "MultiSelect.h"
#include "Central.h"
#include "UIControl.h"
#include "TAS_CharacterList.h"
#include "WindowsStruct.h"
#include "PrintPlayer.h"
TASCharacterList gCharList;

void TASCharacterList::ImgLoad()
{
	pLoadImage("Custom\\SuperKhung\\Other\\CharSelectBg.tga"			, 0x18909, GL_LINEAR, GL_REPEAT, 1, 0);
}

void TASCharacterList::StatusInfo(float X,float Y,int a1, float a2)
{
	char* Name;
	char* Status;
	int Class;
	char Level[256];
	int This = (int)sub_482B70() + 36744;
	int Hero00 = This;
	Hero00 = *(DWORD *)(This + 4) + 368 * a1;

	Name = strcpy((char *)Hero00 + 176, (const char *)(*((DWORD *)Hero00 + 42) + 56));
	Status = (char *)Hero00 + 240;
	Class = sub_587620(*(BYTE *)(*(DWORD *)(Hero00 + 168) + 19));

	pSetTextColor(pTextThis(), 255, 255, 255, 255);
	g_pRenderText.CRenderText(X - 66, Y + 5 + a2, (const char*)Name, 190, 0, 3, 0);
	gInterface.DrawFormat(eWhite255, X - 66, Y + 14 + a2, 190, 3, "%s", (const char*)Class);
	gInterface.DrawFormat(eYelloCam, X - 66, Y + 23 + a2, 190, 3, "Cấp độ %d", *(WORD*)(*(DWORD*)(Hero00 + 168) + 130));
	gInterface.DrawFormat(eWhite255, X - 66, Y + 32 + a2, 190, 3, (const char*)Status);

	//char* addressOfName = (char *)(Hero00 + 176);
	//gInterface.DrawFormat(eAncient, X - 66, Y + 50 + a2, 190, 3, "Name: %p", (void*)addressOfName);
}

void TASCharacterList::GetPosForm()
{
	for (int Num = 2; Num < 4; Num++)
	{
		if (ScreenSize == Num)
		{
			this->AddX = 15;
			this->AddY = 2;
			this->FormW = 109;
			this->FormH = 60;
		}
	}
	for (int Num = 4; Num < 10; Num++)
	{
		if (ScreenSize == Num)
		{
			this->AddX = 4;
			this->AddY = 2;
			this->FormW = 80;
			this->FormH = 60;
		}
	}	
}
void TASCharacterList::TAS_CharInfoLoad(int X, int Y , int mHeroID )
{
	gCharList.GetPosForm();
	if ( *(BYTE *)(pGetPreviewStruct(pPreviewThis(),mHeroID) + 780))
	{
		RenderBitmap(0x18909, X - this->AddX, Y - this->AddY, this->FormW, this->FormH, 0, 0, 1, 1, 1, 1, 0);

		if (ScreenSize == 0 || ScreenSize == 1)
		{
			this->StatusInfo(X + 1000, Y, mHeroID, 0);
		}
		else
		{
			this->StatusInfo(X, Y, mHeroID, 0);
		}
	}
}
void TASCharacterList::SelectChar()
{
	float XBPCoord = TransFor2X(320) - TransForX(320);	
	if ( !*(BYTE *)((int)sub_482B70() + 33948) )
	{
		TAS_CharInfoLoad(Return2X(XBPCoord + TransForX(90)),  160,0); //-- Char 1/5
		TAS_CharInfoLoad(Return2X(XBPCoord + TransForX(190)), 160,1); //-- Char 2/5		
		TAS_CharInfoLoad(Return2X(XBPCoord + TransForX(290)), 160,2); //-- Char 3/5	
		TAS_CharInfoLoad(Return2X(XBPCoord + TransForX(385)), 160,3); //-- Char 4/5	
		TAS_CharInfoLoad(Return2X(XBPCoord + TransForX(480)), 160,4); //-- Char 4/5				
	}
}