#include "stdafx.h"

#include "TAS_MobileAvt.h"
#include "Interface.h"
#include "Defines.h"
#include "CMacroUIEx.h"
#include "WindowsStruct.h"
#include "User.h"
#include "PrintPlayer.h"
#include "Common.h"
#include "MuHelper.h"
#include "Central.h"
#include "Util.h"
#include "TAS_ToolKit.h"
#include "Config.h"

void Interface::DrawZenAndRud(int a1, int a2, int a3, int a4)
{
	DWORD v23;
	int v10 = *(DWORD*)(a1 + 40);
	int v11 = *(DWORD*)(a1 + 36);
	v23 = *(DWORD*)(*(DWORD*)0x8128AC4 + 5956);
	gInterface.DrawFormat(eGold, v11, v10 + 9, 186, 3, "Trang Bị");;

	if (gProtect.m_MainInfo.CustomInterfaceType != 2)
	{
		DWORD ColorKickSet, ColorKickSock;
		if ((signed int)(unsigned __int8)SetOption1((int)pUserStat()) <= 0 && (signed int)(unsigned __int8)SetOption2((int)pUserStat()) <= 0)
		{
			ColorKickSet = eGray100;
		}
		else
		{
			ColorKickSet = eGold;
		}
		gInterface.DrawFormat(ColorKickSet, v11 + 23, v10 + 34, 50, 1, "Set Thần");

		if (!sub_969000((void*)0x986C1B8))
		{
			ColorKickSock = eGray100;
		}
		else
		{
			ColorKickSock = eGold;
		}
		gInterface.DrawFormat(ColorKickSock, v11 + 117, v10 + 34, 50, 4, "Set Socket");

		#if TYPEZEN == 0
		gInterface.DrawGUI(FormZen, v11 + 11, v10 + 365);
		char textzen[50];
		ZeroMemory(textzen, sizeof(textzen));
		pGetMoneyFormat(v23, textzen, 0);
		DWORD Color;
		if (v23 > 0)
		{
			Color = ColorMoneys(v23);
		}
		gInterface.DrawFormat(Color, v11 + 52, v10 + 372, 190, 1, "%s", textzen);
		#endif
		#if TYPEZEN == 1
		char textzen[50], textGP[50], TextWC[50], textWP[50];
		ZeroMemory(textzen, sizeof(textzen));
		ZeroMemory(textGP, sizeof(textGP));
		ZeroMemory(TextWC, sizeof(TextWC));
		ZeroMemory(textWP, sizeof(textWP));

		pGetMoneyFormat(v23, textzen, 0);
		pGetMoneyFormat(Coin1, TextWC, 0);
		pGetMoneyFormat(Coin2, textWP, 0);
		pGetMoneyFormat(Coin3, textGP, 0);

		RenderBitmap(0x17915, v11 + 11, v10 + 363, 100.f, 16.f, 0, 0, 170.f / 256.f, 21.f / 32.f, 1, 1, 0.0);
		RenderBitmap(0x17915, v11 + 98, v10 + 363, 100.f, 16.f, 0, 0, 170.f / 256.f, 21.f / 32.f, 1, 1, 0.0);
		RenderBitmap(0x17915, v11 + 11, v10 + 377, 100.f, 16.f, 0, 0, 170.f / 256.f, 21.f / 32.f, 1, 1, 0.0);
		RenderBitmap(0x17915, v11 + 98, v10 + 377, 100.f, 16.f, 0, 0, 170.f / 256.f, 21.f / 32.f, 1, 1, 0.0);

		gInterface.DrawFormat(eGold, v11 + 37, v10 + 366, 54, 4, "%s", textzen);
		gInterface.DrawFormat(eGold, v11 + 126, v10 + 366, 54, 4, "%s", textGP);
		gInterface.DrawFormat(eGold, v11 + 37, v10 + 366 + 14, 54, 4, "%s", TextWC);
		gInterface.DrawFormat(eGold, v11 + 126, v10 + 380, 54, 4, "%s", textWP);
		#endif
		#if TYPEZEN == 2
		RenderBitmap(0x17915, v11 + 11, v10 + 363, 100.f, 16.f, 0, 0, 170.f / 256.f, 21.f / 32.f, 1, 1, 0.0);
		RenderBitmap(0x17915, v11 + 98, v10 + 363, 100.f, 16.f, 0, 0, 170.f / 256.f, 21.f / 32.f, 1, 1, 0.0);
		RenderBitmap(0x17915, v11 + 11, v10 + 377, 100.f, 16.f, 0, 0, 170.f / 256.f, 21.f / 32.f, 1, 1, 0.0);
		RenderBitmap(0x17915, v11 + 98, v10 + 377, 100.f, 16.f, 0, 0, 170.f / 256.f, 21.f / 32.f, 1, 1, 0.0);
		gInterface.DrawFormat(eWhite, v11 + 20, v10 + 366, 20, 1, gConfig.TTAS_TEXT_ENGINE[8]);
		gToolKit.CRenderNumberExNew(v11 + 107, v10 + 366, v23, 4, 0.88);
		gInterface.DrawFormat(eWhite, v11 + 110, v10 + 366, 20, 1, gConfig.TTAS_TEXT_ENGINE[9]);
		gToolKit.CRenderNumberExNew(v11 + 194, v10 + 366, Coin3, 4, 0.88);
		gInterface.DrawFormat(eWhite, v11 + 20, v10 + 380, 20, 1, gConfig.TTAS_TEXT_ENGINE[10]);
		gToolKit.CRenderNumberExNew(v11 + 108, v10 + 380, Coin1, 4, 0.88);
		gInterface.DrawFormat(eWhite, v11 + 110, v10 + 380, 20, 1, gConfig.TTAS_TEXT_ENGINE[11]);
		gToolKit.CRenderNumberExNew(v11 + 194.5f, v10 + 380, Coin2, 4, 0.88);
		#endif
	}
	else
	{
		gInterface.DrawGUI(eMainMenuSet, v11 + 15, v10 + 21);

		char textzen[50];
		ZeroMemory(textzen, sizeof(textzen));
		pGetMoneyFormat(v23, textzen, 0);

		gInterface.DrawFormat(eWhite, v11 + 25, v10 + 372, 20, 1, gConfig.TTAS_TEXT_ENGINE[8]);
		gInterface.DrawGUI(eZen, v11 + 40, v10 + 366);
		DWORD ZenCorlor;
		if (v23 >= 0 && v23 <= 99999)
		{
			ZenCorlor = MilkZen;
		}
		else if (v23 >= 100000 && v23 <= 999999)
		{
			ZenCorlor = GreenZen;
		}
		else if (v23 >= 1000000 && v23 <= 6999999)
		{
			ZenCorlor = OrgZen;
		}
		else if (v23 >= 7000000)
		{
			ZenCorlor = RedZen;
		}
		gInterface.DrawFormat(ZenCorlor, v11 + 46, v10 + 371, 54, 1, "%s", textzen);
	}
	
}

__declspec(naked) void InfoTooltipSocketX()
{
	static DWORD Addr_JMP = 0x00835CBD;
	static DWORD This; // [sp+74h] [bp-4h]@1
	static DWORD RenderY; // [sp+74h] [bp-4h]@1
	static DWORD RenderX; // [sp+74h] [bp-4h]@1

	This = GetInventory(GetInstance());

	RenderX = *(signed int*)(This + 36) + 54;
	RenderY = *(signed int*)(This + 40) + 10;

	_asm
	{
		PUSH RenderX
		PUSH RenderY
		JMP[Addr_JMP]
	}
}
__declspec(naked) void InfoTooltipAncestralX()
{
	static DWORD Addr_JMP = 0x00835C92;
	static DWORD This;
	static DWORD RenderY;

	This = GetInventory(GetInstance());

	RenderY = *(signed int*)(This + 40) + 10;

	_asm
	{
		PUSH RenderY
		JMP[Addr_JMP]
	}
}
__declspec(naked) void RemoveTextAncestralX()
{
	static DWORD Addr_JMP = 0x0083524C;

	_asm
	{
		JMP[Addr_JMP]
	}
}

__declspec(naked) void RemoveTextSocketX()
{
	static DWORD Addr_JMP = 0x00835364;

	_asm
	{
		JMP[Addr_JMP]
	}
}
bool CheckMouseAncestralX(int x, int y, int w, int h) //-- ataque automatico
{
	int This; // [sp+74h] [bp-4h]@1

	This = GetInventory(GetInstance());

	x = TransFor2X((double)*(signed int*)(This + 36));
	y = TransForY((double)*(signed int*)(This + 40));

	return pCheckMouseOver(Return2X(x + TransForX(28)), ReturnY(TransForY(33)), Return2X(TransForX(43)), ReturnY(TransForY(17)));
}

bool CheckMouseSocketX(int x, int y, int w, int h)
{
	int This; // [sp+74h] [bp-4h]@1

	This = GetInventory(GetInstance());

	x = TransFor2X((double)*(signed int*)(This + 36));
	y = TransForY((double)*(signed int*)(This + 40));

	return pCheckMouseOver(Return2X(x + TransForX(117)), ReturnY(y + TransForY(33)), Return2X(TransForX(133)), ReturnY(TransForY(17)));
}
void InitLoad()
{
	SetCompleteHook(0xE9, 0x00835CB1, &InfoTooltipSocketX); //-- Posicion Mostrar Tooltip de Equipamiento
	SetCompleteHook(0xE9, 0x00835C86, &InfoTooltipAncestralX); //-- Posicion Mostrar Tooltip de Equipamiento
	//--
	SetCompleteHook(0xE9, 0x0083516F, &RemoveTextAncestralX); //-- Text Ancient
	SetCompleteHook(0xE9, 0x008352B1, &RemoveTextSocketX); //-- Text Socket
	//--
	SetCompleteHook(0xE8, 0x0083538A, &CheckMouseSocketX); //-- InfoOption Socket Equip
	SetCompleteHook(0xE8, 0x00834C8D, &CheckMouseAncestralX); //-- InfoOption Ancient Equip
}
#if(TAS_STYLE == 1)
#include "TAS_ToolKit.h"
SuperKhung mTAS;

void SuperKhung::LoadImg()
{
	LoadBitmapA("TAS\\NhanVat\\DK1.tga", 531050, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("TAS\\NhanVat\\DW1.tga", 531051, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("TAS\\NhanVat\\FE1.tga", 531052, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("TAS\\NhanVat\\MG1.tga", 531053, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("TAS\\NhanVat\\DL1.tga", 531054, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("TAS\\NhanVat\\SM1.tga", 531055, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("TAS\\NhanVat\\RF1.tga", 531056, GL_LINEAR, GL_CLAMP, 1, 0);
	LoadBitmapA("TAS\\NhanVat\\BarFace.tga", 531049, GL_LINEAR, GL_CLAMP, 1, 0);
}


void SuperKhung::HienThiKhuonNhanVat()
{
	if (gInterface.CheckWindow(CashShop) || gInterface.CheckWindow(SkillTree) || gInterface.CheckWindow(MoveList) || gInterface.CheckWindow(ObjWindow::MoveList))
	{
		return;
	}
	if (gInterface.IsWorkZone2(Setting_X - 10, Setting_Y - 20, 200, 100))
	{
		pSetCursorFocus = true;
	}

	this->ChieuDaiChar = 34;
	this->ChieuCaoChar = 45;
	this->ToaDoXChar = 6;
	this->ToaDoYChar = 2;

	this->ChieuDaiBg = 155;
	this->ChieuCaoBg = 100;
	this->ToaDoXBg = 0;
	this->ToaDoYBg = 0;

	this->mCharClass = pGetCharClass(*(BYTE*)(*(DWORD*)0x7BC4F04 + 19));
	
	switch (this->mCharClass)
	{
		case 0:		RenderBitmap(531051, this->ToaDoXChar, this->ToaDoYChar, this->ChieuDaiChar, this->ChieuCaoChar, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0); break;
		case 1:		RenderBitmap(531050, this->ToaDoXChar, this->ToaDoYChar, this->ChieuDaiChar, this->ChieuCaoChar, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0); break;
		case 2:		RenderBitmap(531052, this->ToaDoXChar, this->ToaDoYChar, this->ChieuDaiChar, this->ChieuCaoChar, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0); break;
		case 3:		RenderBitmap(531053, this->ToaDoXChar, this->ToaDoYChar, this->ChieuDaiChar, this->ChieuCaoChar, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0); break;
		case 4:		RenderBitmap(531054, this->ToaDoXChar, this->ToaDoYChar, this->ChieuDaiChar, this->ChieuCaoChar, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0); break;
		case 5:		RenderBitmap(531055, this->ToaDoXChar, this->ToaDoYChar, this->ChieuDaiChar, this->ChieuCaoChar, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0); break;
		case 6:		RenderBitmap(531056, this->ToaDoXChar, this->ToaDoYChar, this->ChieuDaiChar, this->ChieuCaoChar, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0); break;
		default:	RenderBitmap(531051, this->ToaDoXChar, this->ToaDoYChar, this->ChieuDaiChar, this->ChieuCaoChar, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0); break;
	}
	float BODY_X1 = GetPrivateProfileIntA("TEST", "BODY_X1", 0, "./Settings.ini");
	float BODY_Y1 = GetPrivateProfileIntA("TEST", "BODY_Y1", 0, "./Settings.ini");
	float BODY_W1 = GetPrivateProfileIntA("TEST", "BODY_W1", 0, "./Settings.ini");
	float BODY_H1 = GetPrivateProfileIntA("TEST", "BODY_H1", 0, "./Settings.ini");

	RenderBitmap(HP_FACEB, this->ToaDoXBg + BODY_X1, (this->ToaDoYBg - this->ChieuCaoBg / 4) + BODY_Y1, this->ChieuDaiBg - BODY_W1, this->ChieuCaoBg - BODY_H1, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
	RenderBitmap(531049, this->ToaDoXBg, this->ToaDoYBg - this->ChieuCaoBg / 4, this->ChieuDaiBg, this->ChieuCaoBg, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);

	#if LUC_CHIEN
	static DWORD ShowLucChien = gObjUser.mLucChien;
	if (*(DWORD*)MAIN_SCREEN_STATE == 5)
	{
		float StartX = 180;
		float StartY = 5;

		if (gObjUser.mLucChien > ShowLucChien)
		{
			if ((gObjUser.mLucChien - ShowLucChien) > 10000)
			{
				ShowLucChien += 10000;
			}
			else if ((gObjUser.mLucChien - ShowLucChien) > 1000)
			{
				ShowLucChien += 1000;
			}
			else if ((gObjUser.mLucChien - ShowLucChien) > 100)
			{
				ShowLucChien += 100;
			}
			else if ((gObjUser.mLucChien - ShowLucChien) > 50)
			{
				ShowLucChien += 50;
			}
			else
			{
				ShowLucChien++;
			}
		}
		else if (gObjUser.mLucChien < ShowLucChien)
		{
			if ((ShowLucChien - gObjUser.mLucChien) > 10000)
			{
				ShowLucChien -= 10000;
			}
			else if ((ShowLucChien - gObjUser.mLucChien) > 1000)
			{
				ShowLucChien -= 1000;
			}
			else if ((ShowLucChien - gObjUser.mLucChien) > 100)
			{
				ShowLucChien -= 100;
			}
			else if ((ShowLucChien - gObjUser.mLucChien) > 50)
			{
				ShowLucChien -= 50;
			}
			else
			{
				ShowLucChien--;
			}
		}
	}
	#endif

	gToolKit.CRenderNumberExNew(26.5, 45, gObjUser.lpPlayer->Level, 3, 0.74);
	//gToolKit.CRenderNumberClassic(1, 70.0f, 36.4f, *(WORD*)0x87935D8, 0.72);
#if LUC_CHIEN
	char IsLucChien[255];
	ZeroMemory(IsLucChien, sizeof(IsLucChien));
	wsprintf(IsLucChien, "L.CHIẾN: %s", gToolKit.QNumberFormat(ShowLucChien));
	COLORREF WhiteColor = RGB(255, 255, 255);
	HFONT IsText;
	gToolKit.CreateFontNew(50, 7, 100, 1, 15, 700, IsLucChien, WhiteColor, IsText);
#endif
	//gToolKit.CRenderNumberClassic(1, 52.90f, 63.40f, gObjUser.CoordenadaX, 0.72);
	//gToolKit.CRenderNumberClassic(1, 67.60, 63.40f, gObjUser.CoordenadaY, 0.72);
	gInterface.DrawFormat(eWhite, -2, 53, 50, 3, "%s", gObjUser.lpPlayer->Name);

	if (pCheckMouseOver(46, 32, 58, 5) == 1)
	{
		gInterface.DrawToolTip(48, 32, "Mana: %d/%d", ViewCurMP, ViewMaxMP);
	}
	if (pCheckMouseOver(46, 38, 58, 5) == 1)
	{
		gInterface.DrawToolTip(48, 38, "Giáp: %d/%d", ViewCurSD, ViewMaxSD);
	}
	//glColor3f(1.0f, 0.5167, 0.0f);
	//
	//glColor3f(1.0, 1.0, 1.0);
	//EnableAlphaTest(1);
	//
	//gInterface.DrawButtonRender(ButtonSettings, Setting_X, Setting_Y, 0, 0);
	//if (gInterface.IsWorkZone(ButtonSettings))
	//{
	//	gInterface.DrawToolTip(Setting_X, Setting_Y + 40, "Cài đặt");
	//
	//	if (gInterface.Data[ButtonSettings].OnClick)
	//	{
	//		RenderBitmap(51546, Setting_X, Setting_Y, Setting_S, Setting_S, 0.0, 0.451f, 0.878, 0.225, 1, 1, 0.0);
	//	}
	//	else
	//	{
	//		RenderBitmap(51546, Setting_X, Setting_Y, Setting_S, Setting_S, 0.0, 0.2255f, 0.878, 0.225, 1, 1, 0.0);
	//	}
	//}
	//else
	//{
	//	RenderBitmap(51546, Setting_X, Setting_Y, Setting_S, Setting_S, 0.0, 0.0, 0.878, 0.225, 1, 1, 0.0);
	//}
	//
	//if (!*(BYTE*)(*(DWORD*)(MUHELPER_STRUC)+0x08))
	//{
	//	gInterface.DrawButtonRender(ButtonStart, PlayHeperX, PlayHeperY, 0, 0.0f);
	//	if (gInterface.IsWorkZone(ButtonStart))
	//	{
	//		gInterface.DrawToolTip(PlayHeperX, PlayHeperY + 40, "Chạy Auto");
	//		if (gInterface.Data[ButtonStart].OnClick)
	//		{
	//			RenderBitmap(51547, PlayHeperX, PlayHeperY, PlayHeperS, PlayHeperS, 0.0, 0.451f, 0.878, 0.225, 1, 1, 0.0);
	//		}
	//		else
	//		{
	//			RenderBitmap(51547, PlayHeperX, PlayHeperY, PlayHeperS, PlayHeperS, 0.0, 0.2255f, 0.878, 0.225, 1, 1, 0.0);
	//		}
	//	}
	//	else
	//	{
	//		RenderBitmap(51547, PlayHeperX, PlayHeperY, PlayHeperS, PlayHeperS, 0.0, 0.0, 0.878, 0.225, 1, 1, 0.0);
	//	}
	//}
	//else
	//{
	//	gInterface.DrawButtonRender(ButtonStop, PlayHeperX, PlayHeperY, 0, 0.0f);
	//
	//	if (offhelper == 1)
	//	{
	//		gMuHelper.RunningOffHelper();
	//	}
	//	if (gInterface.IsWorkZone(ButtonStop))
	//	{
	//		gInterface.DrawToolTip(PlayHeperX, PlayHeperY + 40, "Dừng Auto");
	//
	//		if (gInterface.Data[ButtonStop].OnClick)
	//		{
	//			RenderBitmap(51548, PlayHeperX, PlayHeperY, PlayHeperS, PlayHeperS, 0.0, 0.451f, 0.878, 0.225, 1, 1, 0.0);
	//		}
	//		else
	//		{
	//			RenderBitmap(51548, PlayHeperX, PlayHeperY, PlayHeperS, PlayHeperS, 0.0, 0.2255f, 0.878, 0.225, 1, 1, 0.0);
	//		}
	//	}
	//	else
	//	{
	//		RenderBitmap(51548, PlayHeperX, PlayHeperY, PlayHeperS, PlayHeperS, 0.0, 0.0, 0.878, 0.225, 1, 1, 0.0);
	//	}
	//}
	//
	//gInterface.DrawButtonRender(eMenu, gMenuX, gMenuY, 0, 0.0f);
	//if (gInterface.IsWorkZone(eMenu))
	//{
	//	gInterface.DrawToolTip(gMenuX, gMenuY + 40, "Menu - F8");
	//	// ----
	//	if (gInterface.Data[eMenu].OnClick)
	//	{
	//		RenderBitmap(51553, gMenuX, gMenuY, gMenuS, gMenuS, 0.0, 0.451f, 0.878, 0.225, 1, 1, 0.0);
	//	}
	//	else
	//	{
	//		RenderBitmap(51553, gMenuX, gMenuY, gMenuS, gMenuS, 0.0, 0.2255f, 0.878, 0.225, 1, 1, 0.0);
	//	}
	//}
	//else
	//{
	//	RenderBitmap(51553, gMenuX, gMenuY, gMenuS, gMenuS, 0.0, 0.0, 0.878, 0.225, 1, 1, 0.0);
	//}
}
#endif
