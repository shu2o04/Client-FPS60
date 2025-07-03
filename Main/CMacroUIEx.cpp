#include "stdafx.h"
#include "CMacroUIEx.h"
#include "Util.h"
#include "Offset.h"
#include "Import.h"
#include "User.h"
#include "Interface.h"
#include "Defines.h"
#include "MuHelper.h"
#include "Protocol.h"
#include "PrintPlayer.h"
#include "Common.h"
#include "MiniMap.h"
#include "MiniMapTron.h"
#include "InfoLog.h"
#include "UIControl.h"
#include "WindowsStruct.h"
#include "TAS_ToolKit.h"
#include "Config.h"
CMacroUIEx gCMacroUIEx;
#define SizeBtnClickW 15
#define SizeBtnClickH 18
void CMacroUIEx::RenderFrame(int *This)
{
	#if(TAS_STYLE == 1)
	#else
	float CY;
	char Cord[256];
	float X = 0;
	float Y = 0;

	float renderMenu = 10.0f;

	EnableAlphaTest(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	#if TAS_OFF_BAR
	RenderBitmap(51550, X + 84.0 + renderMenu, Y, 124.0, 24.0, 0.0, 0.285, 0.715, 0.26, 1, 1, 0.0);
	RenderBitmap(51550, X, Y, 124.0, 24.0, 0.0, 0.0, 0.715, 0.28, 1, 1, 0.0);
	pSetFont(pTextThis(), (int)pFontNormal);	
	
	if (World >= 82 && World <= 100)
	{
		wsprintf(Cord, "%s  %d/%d", pGetTextLine(pTextLineThis, (3810 + World - 82)), gObjUser.CoordenadaX, gObjUser.CoordenadaY);
	}
	else
	{
		wsprintf(Cord, "%s  %d/%d", pGetMapName(World), gObjUser.CoordenadaX, gObjUser.CoordenadaY);
	}
	gToolKit.MakeShadowText(X - 40, Y + 4, 200, 3, Cord);
	renderMenu = 15.0f;

	gToolKit.DrawButtonIcon(ButtonSettings, 51546, X + 119 + renderMenu, Y + 7.0,19, 19, gConfig.TTAS_TEXT_ENGINE[27]);

	if (!*(BYTE*)(*(DWORD*)(MUHELPER_STRUC)+0x08))
	{
		gToolKit.DrawButtonIcon(ButtonStart, 51547, 138 + renderMenu, Y + 7.0, 19, 19, gConfig.TTAS_TEXT_ENGINE[28]);
	}
	else
	{
		if (offhelper == 1)
		{
			gMuHelper.RunningOffHelper();
		}
		gToolKit.DrawButtonIcon(ButtonStop, 51548, 138 + renderMenu, Y + 7.0, 19, 19, gConfig.TTAS_TEXT_ENGINE[29]);
	}
	gToolKit.DrawButtonIcon(eMenu, 51553, X + 100.0f + renderMenu, Y + 7.0, 19, 19, gConfig.TTAS_TEXT_ENGINE[30]);

	gToolKit.DrawButtonIcon(TAS_MAIN_ZMCAM,		151556,  X + 5.0f + renderMenu, Y + gMoveYButton,19, 19,gConfig.TTAS_TEXT_ENGINE[31]);
	gToolKit.DrawButtonIcon(TAS_MAIN_RSCAM,		151557, X + 24.0f + renderMenu, Y + gMoveYButton,19, 19,gConfig.TTAS_TEXT_ENGINE[32]);
	gToolKit.DrawButtonIcon(TAS_MAIN_ARESET,	151554, X + 43.0f + renderMenu, Y + gMoveYButton,19, 19,gConfig.TTAS_TEXT_ENGINE[33]);
	gToolKit.DrawButtonIcon(TAS_MAIN_ATM,		151558, X + 81.0f + renderMenu, Y + gMoveYButton,19, 19,gConfig.TTAS_TEXT_ENGINE[34]);
	gToolKit.DrawButtonIcon(TAS_MAIN_BOXSK,		151559, X + 156.0f + renderMenu, Y + 1,12, 12,gConfig.TTAS_TEXT_ENGINE[35]);
	#else

	gToolKit.DrawButtonIcon(ButtonSettings, 51546, X + 85.0f - 4, Y + 1, SizeBtnClickW, SizeBtnClickH, gConfig.TTAS_TEXT_ENGINE[27]);

	if (!*(BYTE*)(*(DWORD*)(MUHELPER_STRUC)+0x08))
	{
		gToolKit.DrawButtonIcon(ButtonStart, 51547, X + 101.0f - 4, Y + 1, SizeBtnClickW, SizeBtnClickH, gConfig.TTAS_TEXT_ENGINE[28]);
	}
	else
	{
		if (offhelper == 1)
		{
			gMuHelper.RunningOffHelper();
		}
		gToolKit.DrawButtonIcon(ButtonStop, 51548, X + 101.0f - 4, Y + 1, SizeBtnClickW, SizeBtnClickH, gConfig.TTAS_TEXT_ENGINE[29]);
	}
	gToolKit.DrawButtonIcon(eMenu, 51553, X + 117.0f - 4, Y + 1, SizeBtnClickW, SizeBtnClickH, gConfig.TTAS_TEXT_ENGINE[30]);
	gToolKit.DrawButtonIcon(TAS_MAIN_ZMCAM, 151556, X + 5.0f  - 4, Y + 1, SizeBtnClickW, SizeBtnClickH, gConfig.TTAS_TEXT_ENGINE[31]);
	gToolKit.DrawButtonIcon(TAS_MAIN_RSCAM, 151557, X + 21.0f - 4, Y + 1, SizeBtnClickW, SizeBtnClickH, gConfig.TTAS_TEXT_ENGINE[32]);
	gToolKit.DrawButtonIcon(TAS_MAIN_ARESET,151554, X + 37.0f - 4, Y + 1, SizeBtnClickW, SizeBtnClickH, gConfig.TTAS_TEXT_ENGINE[33]);
	gToolKit.DrawButtonIcon(TAS_MAIN_ATM,	151558,	X + 53.0f - 4, Y + 1, SizeBtnClickW, SizeBtnClickH, gConfig.TTAS_TEXT_ENGINE[34]);
	gToolKit.DrawButtonIcon(TAS_MAIN_BOXSK, 151559, X + 69.0f - 4, Y + 1, SizeBtnClickW, SizeBtnClickH, gConfig.TTAS_TEXT_ENGINE[35]);
	gToolKit.DrawButtonIcon(TAS_ITEM_BLOCK, 151560, X + 133.0f - 4, Y + 1, SizeBtnClickW, SizeBtnClickH, "Khóa Giao Dịch");
	gToolKit.DrawButtonIcon(TAS_PK_LOCK, 0xC942, X + 149.0f - 4, Y + 1, SizeBtnClickW, SizeBtnClickH, "Auto PK");
	gToolKit.DrawButtonIcon(TAS_AUTO_HP, 0xC942, X + 165.0f - 4, Y + 1, SizeBtnClickW, SizeBtnClickH, "Auto HP");
	gToolKit.DrawButtonIcon(TAS_AUTO_BF, 151562, X + 181.0f - 4, Y + 1, SizeBtnClickW, SizeBtnClickH, "Buff");
	#endif
	pGLSwitch();
	EnableAlphaTest(0);
#endif
}
char BarTime(int This)
{
	float v1; // ST10_4@2
	float v2; // ST0C_4@2
	float v3; // ST30_4@3
	float v4; // ST08_4@3
	float v5; // ST04_4@3
	int v13; // [sp+30h] [bp-4h]@1

	 v13 = This;

	if ( *(BYTE *)(v13 + 72) == 1 )
	{
		v1 = (double)*(signed int *)(This + 20);
		v2 = (double)*(signed int *)(This + 16);
		RenderImage2(51522, v5, v4);
		if ( *(DWORD *)(v13 + 88) == 1 )
		{
			v3 = *(float *)(v13 + 92) * 50.0;
			v4 = (double)(*(DWORD *)(v13 + 20) + 2);
			v5 = (double)(*(DWORD *)(v13 + 16) + 2);
			RenderImage(51549, v5 + 108.0, v4 - 16.0, v3, 3.0);
		}
		else if ( *(DWORD *)(v13 + 88) > 1 )
		{
			RenderImage2(51522, v5, v4);
			v3 = *(float *)(v13 + 92) * 50.0;
			v4 = (double)(*(DWORD *)(v13 + 20) + 2);
			v5 = (double)(*(DWORD *)(v13 + 16) + 2);
			RenderImage(51549, v5 + 108.0, v4 - 16.0, v3, 3.0);
		}
	}
  return 1;
}

__declspec(naked) void MuHelperRemake_01() 
{
	static DWORD Remake_Buffer = 0x007D26DA;
	#if(TAS_STYLE == 1)
	static DWORD W = Setting_S;
	static DWORD H = Setting_S;
	static DWORD X = Setting_X;
	static DWORD Y = Setting_Y;
	#else
	static DWORD W = 15;
	static DWORD H = 15;
	static DWORD X = 85.0f;
	static DWORD Y = 1;
	#endif
	_asm
	{
		PUSH H                                  ; |Arg6 = 0000000D
		PUSH W                                  ; |Arg5 = 00000012
		MOV EDX,DWORD PTR SS:[EBP-0xB8]         ; |
		MOV EAX,DWORD PTR DS:[EDX+0x18]            ; |
		PUSH Y                                 ; |Arg4
		MOV ECX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EDX,DWORD PTR DS:[ECX+0x14]            ; |
		MOV EAX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV ECX,DWORD PTR DS:[EAX+0xC]             ; |
		LEA EDX,DWORD PTR DS:[EDX+ECX+0x29]        ; |
		PUSH X                                 ; |Arg3
		JMP [Remake_Buffer]
	}
}
__declspec(naked) void MuHelperRemake_02()
{
	static DWORD Remake_Buffer = 0x007D2776;
	#if(TAS_STYLE == 1)
	static DWORD W = Setting_S;
	static DWORD H = Setting_S;
	static DWORD X = PlayHeperX;
	static DWORD Y = PlayHeperY;
	#else
	static DWORD W = 15;
	static DWORD H = 15;
	static DWORD X = 101.0f;
	static DWORD Y = 1;
	#endif
 	_asm
	{
		PUSH H                                     ; |Arg6 = 0000000D
		PUSH W                                     ; |Arg5 = 00000012
		MOV EAX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV ECX,DWORD PTR DS:[EAX+0x18]            ; |
		PUSH Y                                     ; |Arg4
		MOV EDX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EAX,DWORD PTR DS:[EDX+0x14]            ; |
		MOV ECX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EDX,DWORD PTR DS:[ECX+0xC]             ; |
		LEA EAX,DWORD PTR DS:[EAX+EDX+0x3B]        ; |
		PUSH X                                     ; |Arg3
		JMP [Remake_Buffer]
	}
}
//-- (007D25C0)
__declspec(naked) void MuHelperRemake_03()  //<- PauseHelper
{
	static DWORD Remake_Buffer = 0x007D2821;
	#if(TAS_STYLE == 1)
	static DWORD W = Setting_S;
	static DWORD H = Setting_S;
	static DWORD X = PlayHeperX;
	static DWORD Y = PlayHeperY;
	#else
	static DWORD W = 15;
	static DWORD H = 15;
	static DWORD X = 101.0f;
	static DWORD Y = 1;
	#endif
 
	_asm
	{
		PUSH H                                     ; |Arg6 = 0000000D
		PUSH W                                     ; |Arg5 = 00000012
		MOV EAX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV ECX,DWORD PTR DS:[EAX+0x18]            ; |
		PUSH Y                                     ; |Arg4
		MOV EDX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EAX,DWORD PTR DS:[EDX+0x14]            ; |
		MOV ECX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EDX,DWORD PTR DS:[ECX+0xC]             ; |
		LEA EAX,DWORD PTR DS:[EAX+EDX+0x3B]        ; |
		PUSH X                                     ; |Arg3
		JMP [Remake_Buffer]
	}
}


void CMacroUIEx::RenderHelperFrame(int *This)
{
	#if(TAS_STYLE == 0 )
	char Cord[256];
	float X = (double)*((DWORD *)This + 5);
	float Y = (double)*((signed int *)This + 6);
	float RenderX; 

	EnableAlphaTest(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	RenderImage(31602, X, Y, 22.0, 25.0);

	int Trans = 0;
	float MapNameText = 0;
	float PosX = 0;
	float PosY = 0;
	if (pWinWidth >= 1024)
	{
		Trans = 3;
		MapNameText = 48.0f;
		PosX = 93;
		PosY = 4;
	}
	else
	{
		Trans = 4;
		MapNameText = 32;
		PosX = 93 + 26;
		PosY = 2;
	}
	for(int i = 0 ; i < Trans; i ++)
	{
		RenderX = (double) X + 22.0 + (i * 26.0);
		RenderImage(31603, RenderX, Y, 26.0, 25.0);
	}

	RenderImage(31604, RenderX, Y, 98.0, 20.0);
	if (World >= 82 && World <= 100)
	{
		wsprintf(Cord, "%s  %d/%d", pGetTextLine(pTextLineThis, (3810 + World - 82)), gObjUser.CoordenadaX, gObjUser.CoordenadaY);
	}
	else
	{
		wsprintf(Cord, "%s  %d/%d", pGetMapName(World), gObjUser.CoordenadaX, gObjUser.CoordenadaY);
	}

	gInterface.DrawFormat(eWhite, X - MapNameText, Y + PosY, 190, 3, Cord);
	pGLSwitch();
	EnableAlphaTest(0);
	//-- Config
	
	gInterface.DrawButtonRender(ButtonSettings, PosX, 1, 0, 0);
	if (gInterface.IsWorkZone(ButtonSettings)){
		gInterface.DrawToolTip(PosX, Y + 50, gConfig.TTAS_TEXT_ENGINE[36]);
		if (gInterface.Data[ButtonSettings].OnClick){
			pDrawButton(31761, PosX, 1.6, 18.0f, 13.3, 0, 26.9);}else{
			pDrawButton(31761, PosX, 1.6, 18.0f, 13.3, 0, 13.6);}}else{
			pDrawButton(31761, PosX, 1.0, 18.0f, 13.3, 0, 0);
	}

	if (!*(BYTE*)(*(DWORD*)(MUHELPER_STRUC)+0x08))
	{
		gInterface.DrawButtonRender(ButtonStart, PosX + 18, 1, 0, 0);
		if (gInterface.IsWorkZone(ButtonStart))
		{
			gInterface.DrawToolTip(PosX + 18, Y + 50, gConfig.TTAS_TEXT_ENGINE[37]);
			if (gInterface.Data[ButtonStart].OnClick){
				pDrawButton(31762, PosX + 18, 1.6, 18.0f, 13.3, 0, 26.9);}else{
				pDrawButton(31762, PosX + 18, 1.6, 18.0f, 13.3, 0, 13.6);}}else{
				pDrawButton(31762, PosX + 18, 1.0, 18.0f, 13.3, 0, 0);
		}
	}
	else
	{
		gInterface.DrawButtonRender(ButtonStop, PosX + 18, 1, 0, 0);
		if(offhelper == 1)
		{
			gMuHelper.RunningOffHelper();
		}
		if (gInterface.IsWorkZone(ButtonStop))
		{
			gInterface.DrawToolTip(PosX + 18, Y + 50, gConfig.TTAS_TEXT_ENGINE[38]);
			if (gInterface.Data[ButtonStop].OnClick){
				pDrawButton(31763, PosX + 18, 1.6, 17.0f, 13.0, 0, 26.9);}else{
				pDrawButton(31763, PosX + 18, 1.6, 17.0f, 13.0, 0, 13.6);}}else{
				pDrawButton(31763, PosX + 18, 1.0, 17.0f, 13.0, 0, 0);
		}
	}
	gInterface.DrawButtonRender(eMenu, PosX + 36, 1.6, 0, 0);
	if (gInterface.IsWorkZone(eMenu))
	{
		gInterface.DrawToolTip(PosX + 36, 1.6 + 50, gConfig.TTAS_TEXT_ENGINE[39]);
		if (gInterface.Data[eMenu].OnClick)
		{
			pDrawButton(BTN_MENU_OFFSET,  PosX + 36, 2.0f, 18.0f, 13.3, 0, 26.9);}else{
			pDrawButton(BTN_MENU_OFFSET,  PosX + 36, 2.0f, 18.0f, 13.3, 0, 13.6);}}else{
			pDrawButton(BTN_MENU_OFFSET,  PosX + 36, 1.2f, 18.0f, 13.3, 0, 0); // Hiển thị
	}

	// Thêm nút AUTO PK và AUTO HP
	gInterface.DrawButtonRender(TAS_PK_LOCK, PosX + 54, 1, 0, 0);
	if (gInterface.IsWorkZone(TAS_PK_LOCK)) {
		gInterface.DrawToolTip(PosX + 54, Y + 50, "Auto PK");
	}
	gInterface.DrawButtonRender(TAS_AUTO_HP, PosX + 70, 1, 0, 0);
	if (gInterface.IsWorkZone(TAS_AUTO_HP)) {
		gInterface.DrawToolTip(PosX + 70, Y + 50, "Auto HP");
	}
	#endif
}

__declspec(naked) void MuHelperRemake2_01()  //<- ConfigHelper
{
	static DWORD PosX = 0;
	if (pWinWidth >= 1024)
	{
		PosX = 93;
	}
	else
	{
		PosX = 93 + 26;
	}

	static DWORD Addr_JMP = 0x007D26DA;
	static DWORD W = 18;
	static DWORD H = 13.3;
	static DWORD X = PosX;
	static DWORD Y = 1;
 
	_asm
	{
		PUSH H                                  ; |Arg6 = 0000000D
		PUSH W                                  ; |Arg5 = 00000012
		MOV EDX,DWORD PTR SS:[EBP-0xB8]         ; |
		MOV EAX,DWORD PTR DS:[EDX+0x18]            ; |
		PUSH Y                                 ; |Arg4
		MOV ECX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EDX,DWORD PTR DS:[ECX+0x14]            ; |
		MOV EAX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV ECX,DWORD PTR DS:[EAX+0xC]             ; |
		LEA EDX,DWORD PTR DS:[EDX+ECX+0x29]        ; |
		PUSH X                                 ; |Arg3
		JMP [Addr_JMP]
	}
}
//-- (007D25C0)
__declspec(naked) void MuHelperRemake2_02()  //<- PlayHelper
{
	static DWORD PosX = 0;
	if (pWinWidth >= 1024)
	{
		PosX = 93;
	}
	else
	{
		PosX = 93 + 26;
	}
	static DWORD Addr_JMP = 0x007D2776;
	static DWORD W = 18;
	static DWORD H = 13.3;
	static DWORD X = PosX + 18;
	static DWORD Y = 1;
 
	_asm
	{
		PUSH H                                     ; |Arg6 = 0000000D
		PUSH W                                     ; |Arg5 = 00000012
		MOV EAX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV ECX,DWORD PTR DS:[EAX+0x18]            ; |
		PUSH Y                                     ; |Arg4
		MOV EDX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EAX,DWORD PTR DS:[EDX+0x14]            ; |
		MOV ECX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EDX,DWORD PTR DS:[ECX+0xC]             ; |
		LEA EAX,DWORD PTR DS:[EAX+EDX+0x3B]        ; |
		PUSH X                                     ; |Arg3
		JMP [Addr_JMP]
	}
}
//-- (007D25C0)
__declspec(naked) void MuHelperRemake2_03()  //<- PauseHelper
{
	static DWORD PosX = 0;
	if (pWinWidth >= 1024)
	{
		PosX = 93;
	}
	else
	{
		PosX = 93 + 26;
	}
	static DWORD Addr_JMP = 0x007D2821;
	static DWORD W = 18;
	static DWORD H = 13.3;
	static DWORD X = PosX + 18.0f;
	static DWORD Y = 1;
 
	_asm
	{
		PUSH H                                     ; |Arg6 = 0000000D
		PUSH W                                     ; |Arg5 = 00000012
		MOV EAX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV ECX,DWORD PTR DS:[EAX+0x18]            ; |
		PUSH Y                                     ; |Arg4
		MOV EDX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EAX,DWORD PTR DS:[EDX+0x14]            ; |
		MOV ECX,DWORD PTR SS:[EBP-0xB8]            ; |
		MOV EDX,DWORD PTR DS:[ECX+0xC]             ; |
		LEA EAX,DWORD PTR DS:[EAX+EDX+0x3B]        ; |
		PUSH X                                     ; |Arg3
		JMP [Addr_JMP]
	}
}

void OffHelper(DWORD id, float x, float y, float w, float h)
{
	pDrawGUI(id, x, y, w, h);
	if( gInterface.IsWorkZone(ButtonStartAttack) )
	{
		if( gInterface.Data[ButtonStartAttack].OnClick )
		{
			if(offhelper == 0)
			{
				offhelper = 1;
			}
			else
			{
				offhelper = 0;
			}
			gInterface.Data[ButtonStartAttack].OnClick = false;
		}
	}
	if(offhelper == 1)
	{
		gInterface.DrawButtonRender(ButtonStartAttack, x + 50, y + 8, 0, 0);
	}
	else
	{
		gInterface.DrawButtonRender(ButtonStartAttack, x + 50, y + 8, 0, 15);
	}
	gInterface.DrawFormat(eGold, x + 50 + 16, y + 12, 60, 1, gConfig.TTAS_TEXT_ENGINE[40]);
}

#define pHelperMouseClick		((char(__thiscall*)(int a1)) 0x007D2920)

char FixHelperMouseClick(int a1)
{
	if(gInterface.CheckWindow(ChaosBox) || gInterface.CheckWindow(Warehouse))
		return 0;

	return pHelperMouseClick(a1);
}
bool CheckCursor(int x, int y, int w, int h)
{
	bool Check = false; // al@2
	return Check = pCheckMouseOver(1, 1, 200, 40);
}
__declspec(naked) void MoveTextArrow()
{
	static DWORD Addr_main = 0x007DF898;
	static DWORD MOVEY = -99;

	_asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x4]
			ADD ECX, MOVEY; |
			PUSH ECX; / Arg2
			MOV EDX, DWORD PTR SS : [EBP - 0x8]; |
			MOV EAX, DWORD PTR DS : [EDX + 0x10]; |
			PUSH EAX; | Arg1
			MOV ECX, DWORD PTR SS : [EBP - 0x8]; |
			JMP[Addr_main]
	}
}
void CMacroUIEx::Load()
{
	SetCompleteHook(0xE8,0x007D2B0C,&FixHelperMouseClick);
	SetCompleteHook(0xE8, 0x007F76CD, &OffHelper);
	SetCompleteHook(0xE8, 0x007D2B3D, &CheckCursor);
	if(gProtect.m_MainInfo.CustomInterfaceType == 4 )
	{
		SetCompleteHook(0xE9, 0x007D2BC0, this->RenderFrame);
		SetCompleteHook(0xE9, 0x0080B8E0, &BarTime);
		SetCompleteHook(0xE9, 0x007D26B5, &MuHelperRemake_01);
		SetCompleteHook(0xE9, 0x007D2751, &MuHelperRemake_02);
		SetCompleteHook(0xE9, 0x007D27FC, &MuHelperRemake_03);
		SetCompleteHook(0xE9, 0x007DF88A, &MoveTextArrow);		
	}
	else
	{
		SetCompleteHook(0xE9, 0x007D26B5, &MuHelperRemake2_01);
		SetCompleteHook(0xE9, 0x007D2751, &MuHelperRemake2_02);
		SetCompleteHook(0xE9, 0x007D27FC, &MuHelperRemake2_03);
		SetCompleteHook(0xE9, 0x007D2BC0, this->RenderHelperFrame);
	}
}
