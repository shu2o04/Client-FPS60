#include "stdafx.h"
#include "NewUIMainFrame.h"
#include "Import.h"
#include "Util.h"
#include "WindowsStruct.h"
#include "Offset.h"
#include "CMacroUIEx.h"
#include "User.h"
#include "MiniMap.h"

#if(SLOTPET2)

void MuHelperRenderFrame(int This)
{
	HGDIOBJ alpha;
	char Cordenadas[10];
	EnableAlphaTest(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	pSetFont(pTextThis(), (int)ho);
	pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
	pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);
	float green = (double)*(signed int*)(This + 24);
	float red = (double)*(signed int*)(This + 20);
	RenderImage(532019, red, green, 70.0, 25.0);
	int v21 = *(DWORD*)(This + 24) + 4;
	int v22 = *(DWORD*)(This + 20) + 16;
	wsprintf(Cordenadas, "%d %d", gObjUser.CoordenadaX, gObjUser.CoordenadaY);
	pDrawText(pTextThis(), v22, v21, Cordenadas, 34, 9, (PINT)3, 0);
	pGLSwitch();
	EnableAlphaTest(0);
}

void CNewUIMainFrameLoad()
{
	SetCompleteHook(0xE9, 0x007D2BC0, &MuHelperRenderFrame);
	MemorySet(0x7D2FF0, 0x90, 0x92);	
	MemorySet(0x0080F2B5, 0x90, 0x5);	
	MemorySet(0x0080F2CD, 0x90, 0x5);	
	MemorySet(0x0080F2E8, 0x90, 0x5);	
	SetByte(0x0080F287 + 3, 38);		
	SetByte(0x0080F28E + 3, 42);		
	SetDword(0x0080F279 + 3, 450);		
}
#endif