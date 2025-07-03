#include "stdafx.h"
#include "Import.h"
#include "Util.h"
#include "Defines.h"
#include "Central.h"
#include "postInterface.h"
#include "Interface.h"
#include "Protect.h"
#include "PrintPlayer.h"
#include "MiniMap.h"
#include "Common.h"
#include "CSCharacterS13.h"
#include "WindowsStruct.h"
#include "PartyBuffs.h"
#include "User.h"
#include "InfoLog.h"
#include "JCOptionBox.h"
#include "MiniMapTron.h"
#include "Config.h"
#include "Ranking.h"
#include "Font.h"
#include "TMemory.h"
#include "TAS_CharacterList.h"
#include "TAS_ToolKit.h"
Centralizado gCentral;
#if ZOOM_MAX_CAM
#define MaxValueCam 4190.0
#else
#define MaxValueCam 2000.0
#endif
Centralizado::Centralizado()
{
	this->JCOption[0].SetText("Effect Dinamic");
	this->JCOption[0].LoadAction(DisableDynamicEffect, JCDINAMIC_EFFECT);
	this->JCOption[1].SetText("Effect Static");
	this->JCOption[1].LoadAction(DisableStaticEffect, JCSTATIC_EFFECT);
	this->JCOption[2].SetText("Effect Skill");
	this->JCOption[2].LoadAction(DisableSkillEffect, JCSKILL_EFFECT);
	this->JCOption[3].SetText("Item Glow");
	this->JCOption[3].LoadAction(DisableGlowEffect, JCITEMGLOW_EFFECT);
	this->JCOption[4].SetText("Object Shadow");
	this->JCOption[4].LoadAction(DisableShadow, JCOBJECTSHADOW);
	this->JCOption[5].SetText("Map Object");
	this->JCOption[5].LoadAction(DisableObject, JCOBJECTWORLDHIDE);
}


void Centralizado::RenderCursor()
{
	float v3;
	float v4;
	float v5;
	float v6;
	int v31;
	int v36;
	int v39;
	float v44;
	DWORD* v51;
	int v60;
	float v61;
	float v62;

	int* dword_8787D58 = (int*)0x8787D58;

	pSetBlend(1);
	glColor3f(1.0, 1.0, 1.0);

	v61 = 0.0;
	v62 = 0.0;

	v3 = (double)CursorY - 2.0;
	v4 = (double)CursorX - 2.0;
	v5 = (double)CursorY + 18.0;
	v6 = (double)CursorX + 5.0;

	if (*(DWORD*)0x81F6BE8 || *(DWORD*)0xE8CB3C)
	{
		if (pCheckWindow(pWindowThis(), 10))
		{
			v31 = sub_8615E0((int)pWindowThis());

			if (sub_78ECE0(v31) == 9)
			{
				RenderBitmap(31239, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
			}
			else
			{
				if (sub_78ECE0(v31))
				{
					if (sub_78ECE0(v31) == 1)
					{
						RenderBitmap(30013, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
					}
				}
				else
				{
					RenderBitmap(30012, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
				}
			}
		}
		else
		{
			if (pCheckWindow(pWindowThis(), 13)
				&& (v36 = sub_861260((int)pWindowThis()), CheckRepairInv(v36) == 1)
				|| pCheckWindow(pWindowThis(), 12)
				&& (v39 = GetWindowShop((int)pWindowThis()), CheckRepairShop(v39) == 2))
			{
				if (*(BYTE*)0x8793386)
				{
					sub_637E80(30017, v6, v5, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 45.0, 0.0, 0.0, 1.0, 1.0);
				}
				else
				{
					RenderBitmap(30017, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
				}
			}
			else if (*(DWORD*)0x81F6BE0 == 2)
			{
				v44 = *(float*)0x5EF5A1C * 0.01999999955296516;
				sub_4F6170(v44);
				if (v44 <= 0.0)
				{
					sub_637E80(30017, v6, v5, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 45.0, 0.0, 0.0, 1.0, 1.0);
				}
				else
				{
					sub_637E80(30017, (double)*(DWORD*)0x879340C + 10.0, (double)*(DWORD*)0x8793410 + 10.0, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 0.0, 1.0, 1.0);
				}
			}
			else
			{
				if (*(BYTE*)0x8793386)
				{
					if (!*(BYTE*)0x81C03AA)//-- clic
					{
						RenderBitmap(30013, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
					}
				}
				else
				{
					RenderBitmap(30012, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
				}
			}
		}
	}
	else if (ItemTarget == -1)	//-- recoger item
	{
		if (NpcTarget == -1) //-- NPC TARGET
		{
			if (*(DWORD*)0xE61734 == -1)
			{
				if (*(BYTE*)(0x7BC4F04 + 14) || PlayerTarget == -1) //-- PLAYER TARGET
				{
					if (pCheckWindow(pWindowThis(), 10))
					{
						v31 = sub_8615E0((int)pWindowThis());

						if (sub_78ECE0(v31) == 9)
						{
							RenderBitmap(31239, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
						}
						else
						{
							if (sub_78ECE0(v31))
							{
								if (sub_78ECE0(v31) == 1)
								{
									if (*(BYTE*)0x8793386)
									{
										if (!*(BYTE*)0x81C03AA)//-- clic
										{
											RenderBitmap(30013, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
										}
									}
									else
									{
										RenderBitmap(30012, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
									}
								}
							}
							else
							{
								RenderBitmap(30012, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
							}
						}
					}
					else
					{
						if (pCheckWindow(pWindowThis(), 13)
							&& (v36 = sub_861260((int)pWindowThis()), CheckRepairInv(v36) == 1)
							|| pCheckWindow(pWindowThis(), 12)
							&& (v39 = GetWindowShop((int)pWindowThis()), CheckRepairShop(v39) == 2))
						{
							if (*(BYTE*)0x8793386)
							{
								sub_637E80(30017, v6, v5, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 45.0, 0.0, 0.0, 1.0, 1.0);
							}
							else
							{
								RenderBitmap(30017, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
							}
						}
						else if (*(DWORD*)0x81F6BE0 == 2)
						{
							v44 = *(float*)0x5EF5A1C * 0.01999999955296516;
							sub_4F6170(v44);
							if (v44 <= 0.0)
							{
								sub_637E80(30017, v6, v5, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 45.0, 0.0, 0.0, 1.0, 1.0);
							}
							else
							{
								sub_637E80(30017, (double)*(DWORD*)0x879340C + 10.0, (double)*(DWORD*)0x8793410 + 10.0, TransFor2X(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 0.0, 1.0, 1.0);
							}
						}
						else
						{
							if (pCheckWindow(pWindowThis(), 13)
								&& (v51 = (DWORD*)GetWindowShop((int)pWindowThis()), sub_83C310(v51)))
							{
								RenderBitmap(30021, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
							}
							else if (*(BYTE*)0x8793386)
							{
								if (*(BYTE*)0x81C03AA)
								{
									RenderBitmap(30020, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
								}
								else
								{
									RenderBitmap(30013, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
								}
							}
							else
							{
								RenderBitmap(30012, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
							}
						}
					}
				}
				else if (!sub_59A8B0() || *(BYTE*)0x813DDCE)
				{
					RenderBitmap(30012, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
				}
				else if ((unsigned __int8)sub_4DB0E0(*(DWORD*)0xE61E18))
				{
					RenderBitmap(30011, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
				}
				else
				{
					RenderBitmap(30014, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
				}
				//-- finaliza la carroña
			}
			else if (
				(*(DWORD*)0xE61E18 || *(DWORD*)(dword_8787D58[3 * *(DWORD*)0xE61734] + 48) != 133)
				&& (*(DWORD*)0xE61E18 != 1 || *(DWORD*)(dword_8787D58[3 * *(DWORD*)0xE61734] + 48) != 60)
				&& (*(DWORD*)0xE61E18 != 2 || *(DWORD*)(dword_8787D58[3 * *(DWORD*)0xE61734] + 48) != 91)
				&& (*(DWORD*)0xE61E18 != 3 || *(DWORD*)(dword_8787D58[3 * *(DWORD*)0xE61734] + 48) != 38))
			{
				RenderBitmap(30019, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
			}
			else
			{
				RenderBitmap(30018, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
			}
		}
		else if (*(DWORD*)0xE61E18 == 38)//-- ATACAR UN MONSTER
		{
			RenderBitmap(30011, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
		}
		else//-- HABLAR CON NPC
		{
			v60 = (int)(timeGetTime() * 0.009999999776482582) % 6;
			if (v60 == 1 || v60 == 3 || v60 == 5)
			{
				v61 = 0.5;
			}
			if (v60 == 2 || v60 == 3 || v60 == 4)
			{
				v62 = 0.5;
			}

			RenderBitmap(30016, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), v61, v62, 0.5, 0.5, 1, 1, 0.0);
		}
	}
	else
	{
		RenderBitmap(30015, v4, v3, ReturnX(TransForX(24.0)), ReturnY(TransForY(24.0)), 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
	}
}

int Centralizado::MoveRenderCameraDefault()
{
	pSetCursorFocus = false;
	int Width = TransForX(190);
	int a3 = 640;
	int t;

	if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 4)
	{
		if (gInterface.Data[eCONFIRM_MAIN].OnShow)
		{
			pSetCursorFocus = true;
		}
		if (gInterface.CheckWindow(13) && gInterface.CheckWindow(Character)
			|| gInterface.CheckWindow(8)
			|| gInterface.CheckWindow(12)
			|| gInterface.CheckWindow(9)
			|| gInterface.CheckWindow(7)
			|| gInterface.CheckWindow(14)
			|| gInterface.CheckWindow(15)
			|| gInterface.CheckWindow(60)
			|| gInterface.CheckWindow(76))
		{
			a3 = Return2X(TransFor2X(640) - (Width * 2));
		}
		else
		{
			if (gInterface.CheckWindow(16) && (gInterface.CheckWindow(4) || gInterface.CheckWindow(69)))
			{
				a3 = Return2X(TransFor2X(640) - (Width * 2));
			}
			else
			{
				if (gInterface.CheckWindow(16) && gInterface.CheckWindow(11))
				{
					a3 = Return2X(TransFor2X(640) - (Width * 2));
				}
				else
				{
					if (gInterface.CheckWindow(27))
					{
						a3 = Return2X(TransFor2X(640) - (Width * 2));
					}
					else
					{
						if (gInterface.CheckWindow(13)
							|| gInterface.CheckWindow(16)
							|| gInterface.CheckWindow(3)
							|| gInterface.CheckWindow(21)
							|| gInterface.CheckWindow(6)
							|| gInterface.CheckWindow(22)
							|| gInterface.CheckWindow(23)
							|| gInterface.CheckWindow(24)
							|| gInterface.CheckWindow(4)
							|| gInterface.CheckWindow(18)
							|| gInterface.CheckWindow(10)
							|| gInterface.CheckWindow(5)
							|| gInterface.CheckWindow(25)
							|| gInterface.CheckWindow(26)
							|| gInterface.CheckWindow(19)
							|| gInterface.CheckWindow(20)
							|| gInterface.CheckWindow(58)
							|| gInterface.CheckWindow(59)
							|| gInterface.CheckWindow(62)
							|| gInterface.CheckWindow(73)
							|| gInterface.CheckWindow(68)
							|| gInterface.CheckWindow(69)
							|| gInterface.CheckWindow(70)
							|| gInterface.CheckWindow(66)
							|| gInterface.CheckWindow(75)
							|| gInterface.CheckWindow(74))
						{
							a3 = Return2X(TransFor2X(640) - Width);
						}
						else
						{
							if (gInterface.CheckWindow(79))
							{
								if (gInterface.CheckWindow(80))
								{
									a3 = Return2X(TransFor2X(640) - (Width * 2));
								}
								else
								{
									a3 = Return2X(TransFor2X(640) - Width);
								}
							}
							else
							{
								a3 = Return2X(TransFor2X(640));
							}
						}
					}
				}
			}
		}

		if (gInterface.CheckWindow(77))
		{
			if (gInterface.CheckWindow(Warehouse) ||
				gInterface.CheckWindow(ChaosBox) ||
				gInterface.CheckWindow(Store) ||
				gInterface.CheckWindow(OtherStore) ||
				gInterface.CheckWindow(Character))
			{
				a3 = Return2X(TransFor2X(640) - (Width * 3));
			}
			else
			{
				a3 = Return2X(TransFor2X(640) - (Width * 2));
			}
		}
		else if (gInterface.CheckWindow(78))
		{
			a3 = Return2X(TransFor2X(640) - (Width * 3));
		}

		if (gInterface.CheckWindow(Shop))
		{
			t = Return2X(Width);

			if (gInterface.CheckWindow(ExpandInventory))
			{
				a3 = Return2X(TransFor2X(640) - (Width * 2));
			}
			else
			{
				a3 = Return2X(TransFor2X(640) - Width);
			}
			if (pCursorX <= t || pCursorX >= a3)
			{
				pSetCursorFocus = true;
			}
		}
		else if (gInterface.CheckWindow(Warehouse))
		{
			t = Return2X(Width);

			if (gInterface.CheckWindow(ExpandWarehouse))
			{
				t = Return2X(Width * 2);
			}
			if (gInterface.CheckWindow(ExpandInventory))
			{
				a3 = Return2X(TransFor2X(640) - (Width * 2));
			}
			else
			{
				a3 = Return2X(TransFor2X(640) - Width);
			}
			if (pCursorX <= t || pCursorX >= a3)
			{
				pSetCursorFocus = true;
			}
		}
		else if (pCursorX >= a3)
		{
			pSetCursorFocus = true;
		}

		if (gInterface.Data[eMenu_MAIN].OnShow ||
			gInterface.Data[eEventTimePANEL_MAIN].OnShow ||
			gInterface.Data[eCommand_MAIN].OnShow ||
			gInterface.Data[TAS_Ranking_Main].OnShow ||
			gInterface.Data[TAS_Ranking_Main].OnShow ||
			gInterface.Data[eJewelBank_MAIN].OnShow ||
			gInterface.Data[TAS_ThueFlag_Main].OnShow ||
			gInterface.Data[eWindowInfo].OnShow ||
			gInterface.Data[eWindowDoiItem].OnShow ||
			gInterface.Data[eWindowHarmony].OnShow ||
			gInterface.Data[eWindowDungLuyenItem].OnShow ||
			gInterface.Data[eCONFIRM_MAIN].OnShow
#if CongHuongV2
			|| gInterface.Data[eWindow_CongHuong].OnShow
#endif
			)
		{
			pSetCursorFocus = true;
		}

		if (gInterface.CheckWindow(33))
		{
			if (pCheckMouseOver(0, *(signed int*)(*(DWORD*)(GetInstance() + 12) + 24) + 10, (int)Return2X(TransForX(15.625)), (int)ReturnY(TransForY(15.625))))
			{
				pSetCursorFocus = true;
			}
		}

		if (gRenderMap.DataMap.ModelID != -1 && MiniMap)
		{
			if (pCheckMouseOver(gRenderMap.DataMap.XSW_Minimap, gRenderMap.DataMap.YSW_Minimap, 128, 128))
			{
				pSetCursorFocus = true;
			}
		}
		if (gRanking.Show == true)
		{
			pSetCursorFocus = true;
		}

		if (*(DWORD*)(*(DWORD*)0x7BC4F04 + 676) != 0 || *(DWORD*)(*(DWORD*)0x7BC4F04 + 556) != 65535)
		{
			if (pCheckMouseOver(2, 31, Return2X(TransForX(74)), 20))
			{
				pSetCursorFocus = true;
			}
		}
	}
	else
	{
		if (gInterface.Data[eCONFIRM_MAIN].OnShow)
		{
			pSetCursorFocus = true;
		}
		else if (gInterface.CheckWindow(Inventory) && gInterface.CheckWindow(Character) //-- 13 & 16
			|| gInterface.CheckWindow(Warehouse) //-- 8
			|| gInterface.CheckWindow(Shop) //-- 12
			|| gInterface.CheckWindow(ChaosBox) //-- 9
			|| gInterface.CheckWindow(Trade) //-- 7
			|| gInterface.CheckWindow(Store) //-- 14
			|| gInterface.CheckWindow(OtherStore) //-- 15
			|| gInterface.CheckWindow(LuckyCoin1) //-- 60
			|| gInterface.CheckWindow(NPC_ChaosMix)
			|| gInterface.CheckWindow(MoveList)
			) //-- 76

		{
			gInterface.Data[eMenu_MAIN].OnShow = false;
			gInterface.Data[eEventTimePANEL_MAIN].OnShow = false;
			gInterface.Data[eCommand_MAIN].OnShow = false;
			gInterface.Data[TAS_Ranking_Main].OnShow = false;
			gInterface.Data[TAS_ThueFlag_Main].OnShow = false;
			gInterface.Data[eJewelBank_MAIN].OnShow = false;
			gInterface.Data[eWindowHarmony].OnShow = false;
			gInterface.Data[eWindowDungLuyenItem].OnShow = false;
			gInterface.Data[eWindowInfo].OnShow = false;


			if (pCursorX >= 260)
			{
				pSetCursorFocus = true;
			}
		}
		else
		{
			if (gInterface.CheckWindow(16) && (gInterface.CheckWindow(4) || gInterface.CheckWindow(69)))
			{
				gInterface.Data[eMenu_MAIN].OnShow = false;
				gInterface.Data[eEventTimePANEL_MAIN].OnShow = false;
				gInterface.Data[eCommand_MAIN].OnShow = false;
				gInterface.Data[TAS_ThueFlag_Main].OnShow = false;
				gInterface.Data[TAS_Ranking_Main].OnShow = false;
				gInterface.Data[eJewelBank_MAIN].OnShow = false;
				gInterface.Data[eWindowHarmony].OnShow = false;
				gInterface.Data[eWindowDungLuyenItem].OnShow = false;
				gInterface.Data[eWindowInfo].OnShow = false;



				if (pCursorX >= 260)
				{
					pSetCursorFocus = true;
				}
			}
			else
			{
				if (gInterface.CheckWindow(16) && gInterface.CheckWindow(11))
				{
					gInterface.Data[eMenu_MAIN].OnShow = false;
					gInterface.Data[eEventTimePANEL_MAIN].OnShow = false;
					gInterface.Data[eCommand_MAIN].OnShow = false;
					gInterface.Data[TAS_Ranking_Main].OnShow = false;
					gInterface.Data[TAS_ThueFlag_Main].OnShow = false;
					gInterface.Data[eWindowHarmony].OnShow = false;
					gInterface.Data[eJewelBank_MAIN].OnShow = false;
					gInterface.Data[eWindowDungLuyenItem].OnShow = false;
					gInterface.Data[eWindowInfo].OnShow = false;

					if (pCursorX >= 260)
					{
						pSetCursorFocus = true;
					}
				}
				else
				{
					if (gInterface.CheckWindow(27))
					{
						gInterface.Data[eMenu_MAIN].OnShow = false;
						gInterface.Data[TAS_ThueFlag_Main].OnShow = false;
						gInterface.Data[eEventTimePANEL_MAIN].OnShow = false;
						gInterface.Data[eCommand_MAIN].OnShow = false;
						gInterface.Data[TAS_Ranking_Main].OnShow = false;
						gInterface.Data[eJewelBank_MAIN].OnShow = false;
						gInterface.Data[eWindowDungLuyenItem].OnShow = false;
						gInterface.Data[eWindowInfo].OnShow = false;
						gInterface.Data[eWindowHarmony].OnShow = false;

						if (pCursorX >= 260)
						{
							pSetCursorFocus = true;
						}
					}
					else
					{
						if (gInterface.CheckWindow(13)
							|| gInterface.CheckWindow(16)
							|| gInterface.CheckWindow(3)
							|| gInterface.CheckWindow(21)
							|| gInterface.CheckWindow(6)
							|| gInterface.CheckWindow(22)
							|| gInterface.CheckWindow(23)
							|| gInterface.CheckWindow(24)
							|| gInterface.CheckWindow(4)
							|| gInterface.CheckWindow(18)
							|| gInterface.CheckWindow(10)
							|| gInterface.CheckWindow(5)
							|| gInterface.CheckWindow(25)
							|| gInterface.CheckWindow(26)
							|| gInterface.CheckWindow(19)
							|| gInterface.CheckWindow(20)
							|| gInterface.CheckWindow(58)
							|| gInterface.CheckWindow(59)
							|| gInterface.CheckWindow(62)
							|| gInterface.CheckWindow(73)
							|| gInterface.CheckWindow(68)
							|| gInterface.CheckWindow(69)
							|| gInterface.CheckWindow(70)
							|| gInterface.CheckWindow(66)
							|| gInterface.CheckWindow(75)
							|| gInterface.CheckWindow(74))
						{
							if (pCursorX >= 450)
							{
								pSetCursorFocus = true;

							}
						}
						else
						{
							if (gInterface.CheckWindow(79))
							{
								gInterface.Data[eMenu_MAIN].OnShow = false;
								gInterface.Data[TAS_ThueFlag_Main].OnShow = false;
								gInterface.Data[eEventTimePANEL_MAIN].OnShow = false;
								gInterface.Data[eCommand_MAIN].OnShow = false;
								gInterface.Data[TAS_Ranking_Main].OnShow = false;
								gInterface.Data[eJewelBank_MAIN].OnShow = false;
								gInterface.Data[eWindowDungLuyenItem].OnShow = false;
								gInterface.Data[eWindowHarmony].OnShow = false;
								gInterface.Data[eWindowInfo].OnShow = false;

								if (gInterface.CheckWindow(80))
								{
									if (pCursorX >= 260)
									{
										pSetCursorFocus = true;
									}
								}
								else
								{
									if (pCursorX >= 450)
									{
										pSetCursorFocus = true;
									}
								}
							}
							else
							{
								if (gInterface.Data[eMenu_MAIN].OnShow ||
									gInterface.Data[eEventTimePANEL_MAIN].OnShow ||
									gInterface.Data[TAS_ThueFlag_Main].OnShow ||
									gInterface.Data[eCommand_MAIN].OnShow ||
									gInterface.Data[TAS_Ranking_Main].OnShow ||
									gInterface.Data[eWindowInfo].OnShow ||
									gInterface.Data[eWindowDungLuyenItem].OnShow ||
									gInterface.Data[eWindowHarmony].OnShow ||
									gInterface.Data[eJewelBank_MAIN].OnShow)
								{
									pSetCursorFocus = true;
								}
							}
						}
					}
				}
			}

			if (gInterface.CheckWindow(77))
			{
				if (gInterface.CheckWindow(Warehouse) ||
					gInterface.CheckWindow(ChaosBox) ||
					gInterface.CheckWindow(Store) ||
					gInterface.CheckWindow(OtherStore) ||
					gInterface.CheckWindow(Character) ||
					gInterface.CheckWindow(Shop))
				{
					gInterface.Data[eMenu_MAIN].OnShow = false;
					gInterface.Data[TAS_ThueFlag_Main].OnShow = false;
					gInterface.Data[eEventTimePANEL_MAIN].OnShow = false;
					gInterface.Data[eCommand_MAIN].OnShow = false;
					gInterface.Data[TAS_Ranking_Main].OnShow = false;
					gInterface.Data[eWindowDungLuyenItem].OnShow = false;
					gInterface.Data[eWindowHarmony].OnShow = false;
					gInterface.Data[eJewelBank_MAIN].OnShow = false;
					gInterface.Data[eWindowInfo].OnShow = false;

					if (pCursorX >= 70)
					{
						pSetCursorFocus = true;
					}
				}
				else
				{
					gInterface.Data[eMenu_MAIN].OnShow = false;
					gInterface.Data[TAS_ThueFlag_Main].OnShow = false;
					gInterface.Data[eEventTimePANEL_MAIN].OnShow = false;
					gInterface.Data[eCommand_MAIN].OnShow = false;
					gInterface.Data[eWindowDungLuyenItem].OnShow = false;
					gInterface.Data[eWindowHarmony].OnShow = false;
					gInterface.Data[TAS_Ranking_Main].OnShow = false;
					gInterface.Data[eJewelBank_MAIN].OnShow = false;
					gInterface.Data[eWindowInfo].OnShow = false;

					if (pCursorX >= 260)
					{
						pSetCursorFocus = true;
					}
				}
			}
			else if (gInterface.CheckWindow(78))
			{
				pSetCursorFocus = true;
			}
		}

		if (gRenderMap.DataMap.ModelID != -1 && MiniMap)
		{
			if (pCheckMouseOver(gRenderMap.DataMap.XSW_Minimap, gRenderMap.DataMap.YSW_Minimap, 128, 128))
			{
				pSetCursorFocus = true;
			}
		}

		if (*(DWORD*)(*(DWORD*)0x7BC4F04 + 676) != 0 || *(DWORD*)(*(DWORD*)0x7BC4F04 + 556) != 65535)
		{
			if (pCheckMouseOver(2, 31, Return2X(TransForX(74)), 20))
			{
				pSetCursorFocus = true;
			}
		}

		if (gCentral.LockMouse != 0)
		{
			if (gCentral.LockMouse > GetTickCount())
			{

				pSetCursorFocus = true;
			}
			else
			{
				gCentral.LockMouse = 0;
			}
		}
	}
	return 640;
}

int CameraGuiReset()
{
	int v49; // eax@55
	signed int v52; // [sp+0h] [bp-4h]@11

	pSetCursorFocus = false;

	if (gInterface.Data[eMenu_MAIN].OnShow ||
		gInterface.Data[eEventTimePANEL_MAIN].OnShow ||
		gInterface.Data[TAS_ThueFlag_Main].OnShow ||
		gInterface.Data[eCommand_MAIN].OnShow ||
		gInterface.Data[TAS_Ranking_Main].OnShow ||
		gInterface.Data[ePARTYSEARCH_MAIN].OnShow ||
		gInterface.Data[eWindowHarmony].OnShow ||
		gInterface.Data[eJewelBank_MAIN].OnShow ||
		gInterface.Data[eWindowDungLuyenItem].OnShow ||
		gInterface.Data[eWindowInfo].OnShow ||
		gInterface.Data[eCONFIRM_MAIN].OnShow)
	{
		pSetCursorFocus = true;
	}

	if (pCheckWindow(pWindowThis(), 13) && pCheckWindow(pWindowThis(), 16) //-- 13 & 16
		|| pCheckWindow(pWindowThis(), 8) //-- 8
		|| pCheckWindow(pWindowThis(), 12) //-- 12
		|| pCheckWindow(pWindowThis(), 9) //-- 9
		|| pCheckWindow(pWindowThis(), 7) //-- 7
		|| pCheckWindow(pWindowThis(), 14) //-- 14
		|| pCheckWindow(pWindowThis(), 15) //-- 15
		|| pCheckWindow(pWindowThis(), 60) //-- 60
		|| pCheckWindow(pWindowThis(), 76)) //-- 76
	{
		v52 = 260;
	}
	else
	{
		if (pCheckWindow(pWindowThis(), 16)
			&& pCheckWindow(pWindowThis(), 4)
			|| pCheckWindow(pWindowThis(), 69))
		{
			v52 = 260;
		}
		else
		{
			if (pCheckWindow(pWindowThis(), 16) && pCheckWindow(pWindowThis(), 11))
			{
				v52 = 260;
			}
			else
			{
				if (pCheckWindow(pWindowThis(), 27))
				{
					v52 = 260;
				}
				else
				{
					if (pCheckWindow(pWindowThis(), 13)
						|| (pCheckWindow(pWindowThis(), 16))
						|| (pCheckWindow(pWindowThis(), 3))
						|| (pCheckWindow(pWindowThis(), 21))
						|| (pCheckWindow(pWindowThis(), 6))
						|| (pCheckWindow(pWindowThis(), 22))
						|| (pCheckWindow(pWindowThis(), 23))
						|| (pCheckWindow(pWindowThis(), 24))
						|| (pCheckWindow(pWindowThis(), 4))
						|| (pCheckWindow(pWindowThis(), 18))
						|| (pCheckWindow(pWindowThis(), 10))
						|| (pCheckWindow(pWindowThis(), 5))
						|| (pCheckWindow(pWindowThis(), 25))
						|| (pCheckWindow(pWindowThis(), 26))
						|| (pCheckWindow(pWindowThis(), 19))
						|| (pCheckWindow(pWindowThis(), 20))
						|| (pCheckWindow(pWindowThis(), 58))
						|| (pCheckWindow(pWindowThis(), 59))
						|| (pCheckWindow(pWindowThis(), 62))
						|| (pCheckWindow(pWindowThis(), 73))
						|| (pCheckWindow(pWindowThis(), 68))
						|| (pCheckWindow(pWindowThis(), 69))
						|| (pCheckWindow(pWindowThis(), 70))
						|| (pCheckWindow(pWindowThis(), 66))
						|| (pCheckWindow(pWindowThis(), 75))
						|| (pCheckWindow(pWindowThis(), 74)))
					{
						v52 = 450;
					}
					else
					{
						if (pCheckWindow(pWindowThis(), 79))
						{
							if (pCheckWindow(pWindowThis(), 80))
								v52 = 260;
							else
								v52 = 450;
						}
						else
						{
							v52 = 640;
						}
					}
				}
			}
		}
	}
	if (pCheckWindow(pWindowThis(), 77))
	{
		v49 = sub_861A60((int)pWindowThis());
		if (sub_7D6270(v49, 0))
			v52 = 70;
		else
			v52 = 260;
	}
	else
	{
		if (pCheckWindow(pWindowThis(), 78))
			v52 = 70;
	}

	if (gRenderMap.DataMap.ModelID != -1 && MiniMap)
	{
		if (pCheckMouseOver(gRenderMap.DataMap.XSW_Minimap_Frame, gRenderMap.DataMap.YSW_Minimap_Frame, 154, 162))
		{
			pSetCursorFocus = true;
		}
	}

	if (gRanking.Show == true)
	{
		pSetCursorFocus = true;
	}

	return v52;
}

void Centralizado::PrintDropBox(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6)
{
	EnableAlphaTest(1);

	glColor4f(0.0, 0.0, 0.0, 0.80000001);
	pDrawBarForm(PosX, PosY, Width, Height, Arg5, Arg6); //central

	float RightX = PosX - 8.0f;
	float LeftX = (PosX + Width) - 8.0f;
	float TopY = PosY - 8.0f;
	float DownY = (PosY + Height) - 8.0f;
	bool horizontal = true;
	bool vertical = true;
	//--
	float IniciarX = PosX - 8.0f;
	float w = 16.0f;
	//--
	float IniciarY = PosY - 8.0f;
	float H = 16.0f;

	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);

	while (vertical || horizontal)
	{
		if (vertical)
		{
			IniciarX += 16.0f;

			if ((IniciarX + w) > LeftX)
			{
				vertical = false;
				w = LeftX - IniciarX;
			}
			pDrawGUI(71512, IniciarX, TopY, w, 16.0f); //arriba

			pDrawGUI(71517, IniciarX, DownY, w, 16.0f); //abajo
		}
		if (horizontal)
		{
			IniciarY += 16.0f;

			if ((IniciarY + H) > DownY)
			{
				horizontal = false;
				H = DownY - IniciarY;
			}

			pDrawGUI(71514, RightX, IniciarY, 16.0f, H); // Lado Izquierdo

			pDrawGUI(71515, LeftX, IniciarY, 16.0f, H); //Lado Derecho
		}
	}

	pDrawGUI(71511, RightX, TopY, 16.0f, 16.0f);
	pDrawGUI(71513, LeftX, TopY, 16.0f, 16.0f);
	pDrawGUI(71516, RightX, DownY, 16.0f, 16.0f);
	pDrawGUI(71518, LeftX, DownY, 16.0f, 16.0f);

	pGLSwitch();
	EnableAlphaTest(0);
}

void RenderSellItem()
{
	if (gPostInterface.item_post_ && pCursorX < 180)
	{
		gPostInterface.DrawItemToolTipText(gPostInterface.item_post_, 320, 150);

		if (gPostInterface.last_tickcount_view_ + 100 < GetTickCount())
		{
			gPostInterface.item_post_ = nullptr;
		}
	}
}

void Centralizado::RenderGame()
{
	if (*(DWORD*)(MAIN_SCREEN_STATE) == ObjState::GameProcess)
	{
		RenderSellItem();
	}
	gCentral.RenderCursor();
}


bool Centralizado::EventPushCursor(int x, int y, int w, int h)
{
	if (pCheckMouseOver(x, y, w, h))
	{
		if (*(BYTE*)0x8793386)
		{
			if (GetTickCount() >= this->TimerPush + 200)
			{
				this->TimerPush = GetTickCount();
				return true;
			}
		}
	}
	return false;
}
int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

DWORD RESOLUTION = pWinWidth + JCResto;
#define sub_630BC0   ((bool(*)()) 0x630BC0)
void ChangeSize(int a1, int a2)
{
	if (!pMUIsLoaded)
		return;

	pWinWidth = a1;
	pWinHeight = a2;

	double aspectRatio = (double)pWinWidth / (double)pWinHeight;

	// Auto scale theo tỉ lệ thực
	pWinWidthReal = (double)pWinWidth / 640.0;
	pWinHeightReal = (double)pWinHeight / 480.0;

	// Ưu tiên preset nếu có
	switch (pGameResolutionMode)
	{
	case 0: case 1:
		pWinWidthReal = (double)pWinWidth / 640.0;
		pWinHeightReal = (double)pWinHeight / 480.0;
		break;
	case 2: case 3: case 4: case 5: case 6:
		pWinWidthReal = 1.25;
		pWinHeightReal = 1.25;
		break;
	default:
		// Nếu là widescreen, lấy theo hệ số tùy biến
		switch (WIDESCREEN)
		{
		case 0: pWinWidthReal = 1.50; break;
		case 1: pWinWidthReal = 1.55; break;
		case 2: pWinWidthReal = 1.60; break;
		case 3: pWinWidthReal = 1.65; break;
		case 4: pWinWidthReal = 1.70; break;
		case 5: pWinWidthReal = 1.75; break;
		case 6: pWinWidthReal = 1.80; break;
		case 7: pWinWidthReal = 1.85; break;
		case 8: pWinWidthReal = 1.90; break;
		case 9: pWinWidthReal = 1.95; break;
		case 10: pWinWidthReal = 2.00; break;
		default:
			// Nếu không xác định, tự tính theo tỉ lệ
			pWinWidthReal = (double)pWinWidth / 640.0;
			break;
		}
		pWinHeightReal = pWinWidthReal * (480.0 / 640.0); // đảm bảo giữ nguyên tỉ lệ gốc 4:3
		break;
	}

	// Tính toán lại JCResto và RESOLUTION
	int JCResto = (int)((double)pWinWidth / pWinHeightReal / 2.0) - 320;
	RESOLUTION = pWinWidth + JCResto;

	// Thay đổi kích thước cửa sổ
	SetWindowPos(pGameWindow, 0, 0, 0, a1, a2 + 30, 0x116);

	// Reload UI
	sub_630BC0();
	sub_596AC0(1);

	// Update Viewport memory
	int v4 = sub_482B70();
	*(DWORD*)(v4 + JCResto + 40) = (DWORD)a1;
	*(DWORD*)(v4 + JCResto + 44) = (DWORD)a2;

	int v5 = sub_407B20();
	*(DWORD*)(v5 + 40) = (DWORD)a1;
	*(DWORD*)(v5 + 44) = (DWORD)a2;

	DWORD* v6 = (DWORD*)pWindowThis();
	sub_785870(v6[3], *v6, v6[4], 0, 382);

	// Các bước làm mới layout/UI
	int instance = GetInstance();
	int screen = sub_861AC0(instance);
	sub_7F0D40(screen);
	sub_7F0C80(v6[78], *v6, 450, 0);

	dword_81C0380 = FontHeight;

	// Render lại font
	sub_830B70(v6[45], *v6, 1, 1);

	// Reset lại camera
	SetFloat((PVOID)(0x00D2C848), MaxValueCam);
	SetFloat((PVOID)(0x00D2C898), MaxValueCam);
}


void RegeditData(BYTE data)
{
	HKEY hKey;
	DWORD dwType, dwSize;
	DWORD buffer;
	LONG result;

	RegOpenKeyA(HKEY_CURRENT_USER, "SOFTWARE\\Webzen\\Mu\\Config", &hKey);
	DWORD value = data;
	ChangeResolution = data;
	RegSetValueExA(hKey, TEXT("Resolution"), 0, REG_DWORD, (const BYTE*)&value, REG_DWORD);
	RegCloseKey(hKey);
	if (data >= 0 && data <= 9)
	{
		char buffer[32];
		sprintf(buffer, " %d", data);
		WritePrivateProfileStringA("Interface", "ChangeResolution", buffer, ".\\Settings.ini");
	}
}

void EventPanelOption()
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	float x;
	float y;
	int This;

	This = *(DWORD*)(GetInstance() + 160);

	x = JCResto + (double)*(signed int*)(This + 16);
	y = (double)*(signed int*)(This + 20);
	if (gCentral.EventPushCursor(x + 27, y + 97, 15, 15)) {
		PVPAttack = !PVPAttack;
		if (PVPAttack != 0)
		{
			gInterface.DrawMessage(1, gConfig.TTAS_TEXT_ENGINE[16]);
			SetByte(0x0059AF53 + 2, 0);
			SetByte(0x0059B248 + 2, 0);
		}
		else
		{
			gInterface.DrawMessage(1, gConfig.TTAS_TEXT_ENGINE[17]);
			SetByte(0x0059AF53 + 2, 1);
			SetByte(0x0059B248 + 2, 1);
		}
	}

	if (gCentral.EventPushCursor(x + 140, y + 37, 15, 15)) {
		HPMonster = !HPMonster;
		if (HPMonster != 0)
			HienMauQuai = 1;
		else
			HienMauQuai = 0;
	}

	if (gCentral.EventPushCursor(x + 140, y + 57, 15, 15)) {
		MyNameOn = !MyNameOn;
		if (MyNameOn != 0)
			SetByte((PVOID)(0x81C03FA), 1);
		else
			SetByte((PVOID)(0x81C03FA), 0);
	}

	if (gCentral.EventPushCursor(x + 140, y + 77, 15, 15)) {
		MiniMap = !MiniMap;
		if (MiniMap != 0)
			WritePrivateProfileStringA("Graphics", "MiniMap", "1", "./Settings.ini");
		else
			WritePrivateProfileStringA("Graphics", "MiniMap", "0", "./Settings.ini");
	}

	if (gCentral.EventPushCursor(x + 140, y + 97, 15, 15)) {
		HideEffect = !HideEffect;
		if (HideEffect != 0)
			MinimizarOfRank = 1;
		else
			MinimizarOfRank = 0;
	}

	if (gCentral.EventPushCursor(x - 45, y + 40, 40, 12)) {
		RegeditData(0);
		ChangeSize(640, 360);
		gFont.FontSizeLoad(11);
		FontHeight = 11;
	}
	else if (gCentral.EventPushCursor(x - 45, y + 58, 40, 12)) {
		RegeditData(1);
		ChangeSize(800, 450);
		gFont.FontSizeLoad(12);
		FontHeight = 12;
	}
	else if (gCentral.EventPushCursor(x - 45, y + 78, 40, 12)) {
		RegeditData(2);
		ChangeSize(1024, 576);
		gFont.FontSizeLoad(12);
		FontHeight = 12;
	}
	else if (gCentral.EventPushCursor(x - 45, y + 98, 40, 12)) {
		RegeditData(3);
		ChangeSize(1280, 720);
	}
	else if (gCentral.EventPushCursor(x - 45, y + 118, 40, 12)) {
		RegeditData(4);
		ChangeSize(1360, 765);
		gFont.FontSizeLoad(12);
		FontHeight = 12;

	}
	else if (gCentral.EventPushCursor(x - 45, y + 138, 40, 12)) {
		RegeditData(5);
		ChangeSize(1440, 810);
		gFont.FontSizeLoad(15);
		FontHeight = 15;
	}
	else if (gCentral.EventPushCursor(x - 45, y + 158, 40, 12)) {
		RegeditData(6);
		ChangeSize(1600, 900);
		gFont.FontSizeLoad(15);
		FontHeight = 15;
	}
	else if (gCentral.EventPushCursor(x - 45, y + 178, 40, 12)) {
		RegeditData(7);
		ChangeSize(1700, 956);
		gFont.FontSizeLoad(15);
		FontHeight = 15;
	}
	else if (gCentral.EventPushCursor(x - 45, y + 198, 40, 12)) {
		RegeditData(8);
		ChangeSize(1800, 1013);
		gFont.FontSizeLoad(15);
		FontHeight = 15;
	}
	else if (gCentral.EventPushCursor(x - 45, y + 218, 40, 12)) {
		RegeditData(9);
		ChangeSize(1920, 1080);
		gFont.FontSizeLoad(15);
		FontHeight = 15;
	}
	if (gCentral.EventPushCursor(x + 97, y + 285, 18, 12)) {
		gFont.FontSizeLoad(11);
		FontHeight = 11;
	}
	if (gCentral.EventPushCursor(x + 117, y + 285, 18, 12)) {
		gFont.FontSizeLoad(12);
		FontHeight = 12;
	}
	if (gCentral.EventPushCursor(x + 137, y + 285, 18, 12)) {
		gFont.FontSizeLoad(14);
		FontHeight = 13;
	}
	if (gCentral.EventPushCursor(x + 157, y + 285, 18, 12)) {
		gFont.FontSizeLoad(15);
		FontHeight = 14;
	}
	if (gCentral.EventPushCursor(x + 177, y + 285, 18, 12)) {
		gFont.FontSizeLoad(16);
		FontHeight = 15;
	}
	if (gCentral.EventPushCursor(x + 197, y + 285, 18, 12)) {
		gFont.FontSizeLoad(17);
		FontHeight = 16;
	}
	if (gCentral.EventPushCursor(x + 78, y + 286, 15, 15)) {
		FontON = !FontON;
		if (FontON != 0)
			WritePrivateProfileStringA("FontConfig", "FontON", "1", "./Settings.ini");
		else
			WritePrivateProfileStringA("FontConfig", "FontON", "0", "./Settings.ini");
	}
	if (gCentral.EventPushCursor(x + 177, y + 285, 18, 12)) {
		gFont.FontSizeLoad(16);
		FontHeight = 15;
	}
#if FPS_OPTION
	int AddX = 30;
	if (gCentral.EventPushCursor(254 + AddX, 213, 15, 15)) // 60
	{
		WritePrivateProfileStringA("Interface", "ChangeFps", "0", "./Settings.ini");
		ChangeFps = 0;
	}
	if (gCentral.EventPushCursor(274 + AddX, 213, 15, 15)) // 45
	{
		WritePrivateProfileStringA("Interface", "ChangeFps", "15", "./Settings.ini");
		ChangeFps = 15;
	}
	if (gCentral.EventPushCursor(294 + AddX, 213, 15, 15)) // 35
	{
		WritePrivateProfileStringA("Interface", "ChangeFps", "25", "./Settings.ini");
		ChangeFps = 25;
	}
	if (gCentral.EventPushCursor(314 + AddX, 213, 15, 15)) // 30
	{
		WritePrivateProfileStringA("Interface", "ChangeFps", "35", "./Settings.ini");
		ChangeFps = 35;
	}
	if (gCentral.EventPushCursor(334 + AddX, 213, 15, 15)) // 15
	{
		WritePrivateProfileStringA("Interface", "ChangeFps", "60", "./Settings.ini");
		ChangeFps = 60;
	}
#endif
}

void FontSizeButton(float x, float y, float a)
{
	if (CheckButtonPressed(x + a, y + 284, 18, 12))
	{
		RenderBitmap(71521, x + a, y + 284, 18, 12, 0.01, 0.4499999583, 0.8799999952, 0.3700000346, 1, 1, 0);
	}
	else
	{
		RenderBitmap(71521, x + a, y + 284, 18, 12, 0.01, 0.02999999747, 0.8799999952, 0.3700000346, 1, 1, 0);
	}
}
void ScreenSizeButton(float x, float y, float a)
{
	if (CheckButtonPressed(x - 45, y + a, 40, 12))
	{
		RenderBitmap(71521, x - 45, y + a, 40, 12, 0.01, 0.4499999583, 0.8799999952, 0.3700000346, 1, 1, 0);
	}
	else
	{
		RenderBitmap(71521, x - 45, y + a, 40, 12, 0.01, 0.02999999747, 0.8799999952, 0.3700000346, 1, 1, 0);
	}
}

void ScreenFpsButton(float x, float y, float a)
{
	if (CheckButtonPressed(x + a, y + 143, 18, 12))
	{
		RenderBitmap(71521, x + a, y + 143, 18, 12, 0.01, 0.4499999583, 0.8799999952, 0.3700000346, 1, 1, 0);
	}
	else
	{
		RenderBitmap(71521, x + a, y + 143, 18, 12, 0.01, 0.02999999747, 0.8799999952, 0.3700000346, 1, 1, 0);
	}
}

void ScreenFaceButton(float x, float y, float a)
{
	if (CheckButtonPressed(x + a, y + 143, 30, 12))
	{
		RenderBitmap(71521, x + a, y + 143, 30, 12, 0.01, 0.4499999583, 0.8799999952, 0.3700000346, 1, 1, 0);
	}
	else
	{
		RenderBitmap(71521, x + a, y + 143, 30, 12, 0.01, 0.02999999747, 0.8799999952, 0.3700000346, 1, 1, 0);
	}
}


void RenderWindowsOption(int a1)
{
	float x;
	float y;
	int This;
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	This = *(DWORD*)(GetInstance() + 160);

	*(signed int*)(This + 16) = 320 - (190 / 2); // Esto dice desde donde empieza las opcion
	x = JCResto + (double)*(signed int*)(This + 16);
	y = (double)*(signed int*)(This + 20);

	pSetFont(pTextThis(), (int)pFontBigBold);
	pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);
	pSetTextColor(pTextThis(), 0xACu, 0xFFu, 0x38u, 0xFFu);

	RenderBitmap(0x1791E, x - 70, y - 10, 513, 430, 0, 0, 1, 1, 1, 1, 0.0);
	RenderBitmap(71520, x + 15, y + 30, 200, 1, 0, 0, 0.7600000501, 1.0, 1, 1, 0); //BARRA DE ARRIBA

	pDrawText(pTextThis(), x - 150, y + 10, gConfig.TTAS_TEXT_ENGINE[18], 250, 0, (LPINT)3, 0);
	RenderBitmap(71520, x - 50, y + 30, 50, 1, 0, 0, 0.7600000501, 1.0, 1, 1, 0); //BARRA DE ARRIBA NUEVA
	pSetCursorFocus = true;
	for (int k = 0; k < 9; k++)
	{
		gCentral.JCOption[k].mouseClicked();
	}
	EventPanelOption();

	if (FontON == 1)
	{
		switch (FontHeight)
		{
		case 11:	FontSizeButton(x, y, 97);			break;
		case 12:	FontSizeButton(x, y, 117);			break;
		case 13:	FontSizeButton(x, y, 137);			break;
		case 14:	FontSizeButton(x, y, 157);			break;
		case 15:	FontSizeButton(x, y, 177);			break;
		case 16:	FontSizeButton(x, y, 197);			break;
		}
	}
#if FPS_OPTION
	switch (ChangeFps)
	{
	case 0:		ScreenFpsButton(x + 24, y, 33);			break;
	case 15:	ScreenFpsButton(x + 24, y, 53);			break;
	case 25:	ScreenFpsButton(x + 24, y, 73);			break;
	case 35:	ScreenFpsButton(x + 24, y, 93);			break;
	case 60:	ScreenFpsButton(x + 24, y, 113);		break; //15
	}
#endif
	switch (ChangeResolution)
	{
	case 0: ScreenSizeButton(x, y, 40); break;
	case 1: ScreenSizeButton(x, y, 58); break;
	case 2: ScreenSizeButton(x, y, 78); break;
	case 3: ScreenSizeButton(x, y, 98); break;
	case 4: ScreenSizeButton(x, y, 118); break;
	case 5: ScreenSizeButton(x, y, 138); break;
	case 6: ScreenSizeButton(x, y, 158); break;
	case 7: ScreenSizeButton(x, y, 178); break;
	case 8: ScreenSizeButton(x, y, 198); break;
	case 9: ScreenSizeButton(x, y, 218); break;
	}

	sub_779410((char*)(This + 24), (x + 215) + 10, y + 4, 16, 16);
	gToolKit.CloseButton(x + 215, y, TAS_BxhArena_BtnClose);
	if (pCheckMouseOver((x + 215) + 10, y + 4, 16, 16) == 1)
	{
		pSetCursorFocus = true;
	}
}

void RenderOptionText(int a1)
{
	int This; // [sp+74h] [bp-4h]@1
	float x; // [sp+2Ch] [bp-8h]@1
	float y; // ST34_4@1
	char buffer[255]; // ST08_4@1

	This = *(DWORD*)(GetInstance() + 160);
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	x = JCResto + (double)*(signed int*)(This + 16);
	y = (double)*(signed int*)(This + 20);

	pSetFont(pTextThis(), (int)pFontNormal);
	pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
	sub_4200F0_Addr(pTextThis(), 0);
	pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);

	//OPCIONES IZQUIERDA
	pDrawText(pTextThis(), x + 45, y + 40, pGetTextLine(pTextLineThis, 386), 0, 0, (LPINT)1, 0); //-- Attack Automatic
	pDrawText(pTextThis(), x + 45, y + 60, pGetTextLine(pTextLineThis, 387), 0, 0, (LPINT)1, 0); //-- Beep Sound
	pDrawText(pTextThis(), x + 45, y + 80, pGetTextLine(pTextLineThis, 919), 0, 0, (LPINT)1, 0); //-- Slide Help
	pDrawText(pTextThis(), x + 45, y + 100, gConfig.TTAS_TEXT_ENGINE[19], 0, 0, (LPINT)1, 0); //-- HP Monster
	//OPCIONES DERECHA
	pDrawText(pTextThis(), x + 158, y + 40, gConfig.TTAS_TEXT_ENGINE[20], 0, 0, (LPINT)1, 0); //-- HP Monster
	pDrawText(pTextThis(), x + 158, y + 60, gConfig.TTAS_TEXT_ENGINE[21], 0, 0, (LPINT)1, 0); //-- Time Bar
	pDrawText(pTextThis(), x + 158, y + 80, gConfig.TTAS_TEXT_ENGINE[22], 0, 0, (LPINT)1, 0); //-- Show MiniMap
	pDrawText(pTextThis(), x + 158, y + 100, gConfig.TTAS_TEXT_ENGINE[23], 0, 0, (LPINT)1, 0); //-- Show MiniMap
	//TAMAÑO DE FUENTE
	pDrawText(pTextThis(), x + 25, y + 285, gConfig.TTAS_TEXT_ENGINE[24], 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x + 103, y + 285, "11", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x + 123, y + 285, "12", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x + 143, y + 285, "13", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x + 163, y + 285, "14", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x + 183, y + 285, "15", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x + 203, y + 285, "16", 0, 0, (LPINT)1, 0);
#if FPS_OPTION
	pDrawText(pTextThis(), x + 33, y + 145, "Chọn FPS:", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x + 33 + 30, y + 145, "60", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x + 53 + 30, y + 145, "45", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x + 73 + 30, y + 145, "35", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x + 93 + 30, y + 145, "30", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x + 113 + 30, y + 145, "15", 0, 0, (LPINT)1, 0);
#endif
	//RESOLUCIONES
	pDrawText(pTextThis(), x - 40, y + 40, "640x360", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x - 40, y + 60, "800x450", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x - 40, y + 80, "1024x576", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x - 40, y + 100, "1280x720", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x - 40, y + 120, "1360x765", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x - 40, y + 140, "1440x810", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x - 40, y + 160, "1600x900", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x - 40, y + 180, "1700x956", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x - 40, y + 200, "1800x1013", 0, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x - 40, y + 220, "1920x1080", 0, 0, (LPINT)1, 0);

	RenderBitmap(71520, x + 15, y + 115, 200, 1, 0, 0, 0.7600000501, 1.0, 1, 1, 0);

	pSetFont(pTextThis(), (int)*(HGDIOBJ*)0xE8C58C);
	pSetTextColor(pTextThis(), 0xACu, 0xFFu, 0x38u, 0xFFu);
	pDrawText(pTextThis(), x, y + 118, pGetTextLine(pTextLineThis, 389), 230, 0, (LPINT)3, 0);
	RenderBitmap(71520, x + 15, y + 160, 200, 1, 0, 0, 0.7600000501, 1.0, 1, 1, 0);
	pSetTextColor(pTextThis(), 0xFFu, 0xBDu, 0x19u, 0xFFu);
	pDrawText(pTextThis(), x, y + 165, pGetTextLine(pTextLineThis, 1840), 230, 0, (LPINT)3, 0);
	RenderBitmap(71520, x + 15, y + 275, 200, 1, 0, 0, 0.7600000501, 1.0, 1, 1, 0);
	RenderBitmap(71520, x + 15, y + 310, 200, 1, 0, 0, 0.7600000501, 1.0, 1, 1, 0);
}


int OptionBuffer;

void RenderOptionPanel(int a1)
{
	int This;
	float x;
	float y;

	This = *(DWORD*)(GetInstance() + 160);
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	x = JCResto + (double)*(signed int*)(This + 16);
	y = (double)*(signed int*)(This + 20);
	EnableAlphaTest(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	pDrawButton(31593, x + 27, y + 37, 15, 15, 0, (*(BYTE*)(This + 196)) ? 0.0 : 15.0); //-- Attack Automatic
	pDrawButton(31593, x + 27, y + 57, 15, 15, 0, (*(BYTE*)(This + 197)) ? 0.0 : 15.0); //-- Beep Sound
	pDrawButton(31593, x + 27, y + 77, 15, 15, 0, (*(BYTE*)(This + 198)) ? 0.0 : 15.0); //-- Slide Show
	pDrawButton(31593, x + 27, y + 97, 15, 15, 0.0, (PVPAttack != 0) ? 0.0 : 15.0); //-- HP Monster
	pDrawButton(31593, x + 140, y + 37, 15, 15, 0.0, (HPMonster != 0) ? 0.0 : 15.0); //-- HP Monster
	pDrawButton(31593, x + 140, y + 57, 15, 15, 0.0, (MyNameOn != 0) ? 0.0 : 15.0); //-- MyNameOn
	pDrawButton(31593, x + 140, y + 77, 15, 15, 0.0, (MiniMap != 0) ? 0.0 : 15.0); //-- MiniMap
	pDrawButton(31593, x + 140, y + 97, 15, 15, 0.0, (HideEffect != 0) ? 0.0 : 15.0); //-- Off Effect
	pDrawButton(71523, x + 27, y + 124, 18, 15, 0, 0);

	pDrawGUI(31596, x + 45, y + 124, 124.0, 16.0);

	if (*(DWORD*)(This + 200) > 0)
	{
		pDrawGUI(31597, x + 45, y + 124, (double)*(signed int*)(This + 200) * 12.40000057220459, 16.0);
	}
	int* SystemAntiLag[6] = { &DisableDynamicEffect, &DisableStaticEffect, &DisableSkillEffect, &DisableGlowEffect, &DisableShadow, &DisableObject };
	float JCRenderY = y + 170;
	float JCRenderX = x + 27;
	for (int k = 0; k < 6; k++)
	{
		gCentral.JCOption[k].SetLocation(JCRenderX, JCRenderY);
		*(int*)SystemAntiLag[k] = gCentral.JCOption[k].SetVisible();

		JCRenderY += 20;

		if (k == 4)
		{
			JCRenderY = y + 170;
			JCRenderX = x + 140;
		}
	}

	if (OptionBuffer != DisableGlowEffect)
	{
		OptionBuffer = DisableGlowEffect;
		*(DWORD*)(This + 204) = (DisableGlowEffect != 0) ? 1 : 5;
	}
	pGLSwitch();
	EnableAlphaTest(0);
}
bool CheckOptionMouseOver(int x, int y, int w, int h)
{
	int This; // [sp+74h] [bp-4h]@1
	This = *(DWORD*)(GetInstance() + 160);
	x = (double)*(signed int*)(This + 16) - 4;
	y = (double)*(signed int*)(This + 20) - 4;
	return pCheckMouseOver(x - 70, y, 308, 347);
}

bool CheckAttackMouseOver(int x, int y, int w, int h) //-- ataque automatico
{
	int This; // [sp+74h] [bp-4h]@1
	This = *(DWORD*)(GetInstance() + 160);
	y = (double)*(signed int*)(This + 20);
	x = (double)*(signed int*)(This + 16);
	return pCheckMouseOver(x + 27, y + 37, 15, 15);
}

bool CheckBeepMouseOver(int x, int y, int w, int h) //-- ataque automatico
{
	int This; // [sp+74h] [bp-4h]@1
	This = *(DWORD*)(GetInstance() + 160);
	y = (double)*(signed int*)(This + 20);
	x = (double)*(signed int*)(This + 16);
	return pCheckMouseOver(x + 27, y + 57, 15, 15);
}

bool CheckSlideMouseOver(int x, int y, int w, int h) //-- ataque automatico
{
	int This; // [sp+74h] [bp-4h]@1
	This = *(DWORD*)(GetInstance() + 160);
	y = (double)*(signed int*)(This + 20);
	x = (double)*(signed int*)(This + 16);
	return pCheckMouseOver(x + 27, y + 77, 15, 15);
}

bool CheckSoundMouseOver(int x, int y, int w, int h) //-- ataque automatico
{
	int This; // [sp+74h] [bp-4h]@1
	This = getWindowConfig_35((int)pWindowThis());
	y = *(DWORD*)(This + 20) + 124;
	return pCheckMouseOver(x, y, w, h);
}

bool CheckEffectMouseOver(int x, int y, int w, int h) //-- ataque automatico
{
	return false;
}

void RenderPane(DWORD id, float x, float y, float w, float h)
{
	gCentral.PrintDropBox(x, y, w, h, 0, 0);
}

void RenderPane_none(DWORD id, float x, float y, float w, float h)
{
	pDrawGUI(31461, x, y, w, h);
}

void RenderPane_Esc(DWORD id, float x, float y, float w, float h)
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	h = 250.0;
	w = 230.0;
	x = (MAX_WIN_WIDTH + JCResto / 2) - (w / 2);
	y = (MAX_WIN_HEIGHT / 2) - (h / 2) - 45;

	gCentral.PrintDropBox(x, y, w, h, 0, 0);
	pSetFont(pTextThis(), (int)pFontBold);
	pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);
	pSetTextColor(pTextThis(), 0xACu, 0xFFu, 0x38u, 0xFFu);
	pDrawText(pTextThis(), x, y + 15, gConfig.TTAS_TEXT_ENGINE[25], 230, 0, (LPINT)3, 0);
	pDrawGUI(71520, x + (w / 2) - (200 / 2), y + 40, 200, 1);
	pDrawGUI(71520, x + (w / 2) - (200 / 2), y + 209.5, 200, 1);
}

bool InfoOverParty(int x, int y, int w, int h)
{
	return pCheckMouseOver(x, y, 77, 30);
}

bool MouseBlockParty(int x, int y, int w, int h)
{
	return pCheckMouseOver(x, y, 77, 43 * pPartyMemberCount);
}

__declspec(naked) void RemoveShadoW()
{
	static DWORD pShadow;
	static DWORD RenderI;
	static DWORD main_addr;

	_asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x14]
		MOV RenderI, ECX
		MOV EDX, DWORD PTR SS : [EBP - 0x10]
		MOV pShadow, EDX
	}

	if (DisableShadow != 0)
		pShadow = RenderI;

	main_addr = (RenderI < pShadow) ? 0x0054A325 : 0x0054A31F;

	_asm
	{
		JMP[main_addr]
	}
}
__declspec(naked) void GlobalMessagem()
{
	static DWORD ADDS = 0x00597698;

	_asm
	{
		CMP DWORD PTR SS : [EBP - 8] , 1200
		JMP[ADDS]
	}
}

void fix_resolution_items_size_1()
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	return sub_6363D0_Addr(0, 0, pWinWidth + JCResto, pWinHeight);
}

int fix_resolution_items_size_2()
{
	float v2 = (float)pWinWidth / (float)pWinHeight;
	return sub_6358A0_Addr(1.0, v2, 20.0, 2000.0);
}
void Centralizado::gDrawWindowCustomXClose(float StartX, float StartY, float CuaSoW, float CuaSoH, int eNumWindow, char* WindowName)
{
	if (!gInterface.Data[eNumWindow].OnShow)
	{
		return;
	}

	if (pCheckMouseOver(StartX, StartY, CuaSoW, CuaSoH) == 1)
	{
		gCentral.LockMouseMoveClick = GetTickCount() + 500;
	}
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	float ScaleW = (225 + JCResto / CuaSoW) / pWinWidthReal;
	float ScaleH = (225 / CuaSoH) / pWinHeightReal;
	pSetCursorFocus = true;
	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);

	gCentral.DrawFrame(0x7A5A, StartX, StartY + 10, 225, 215, 0.0, 0.0, 270, 225, ScaleW, ScaleH);	//Background
	for (int i = StartX + 10; i < (StartX + CuaSoW) - 10; i += 10)
	{
		pDrawButton(0x7A79, i, StartY, 10.0, 64.0, 60.0, 0);											//Frame ngang Trên
		pDrawButton(0x7A7D, i, (StartY + CuaSoH) - 45.0, 10.0, 45.0, 60.0, 0);							//Frame ngang dưới
	}
	for (int doc = StartY + 10; doc < (StartY + CuaSoH) - 10; doc += 10)
	{
		pDrawButton(0x7A7B, StartX, doc, 21.0, 10, 0, 0);												//Frame dọc trái
		pDrawButton(0x7A7C, (StartX + CuaSoW) - 21.0, doc, 21.0, 10, 0, 0);								//Frame dọc phải
	}

	pDrawButton(0x7A79, StartX, StartY, 60.0, 64.0, 0, 0);												//Bo gốc trái trên
	pDrawButton(0x7A79, (StartX + CuaSoW) - 60.0, StartY, 60.0, 64.0, 130.0, 0);						//Bo gốc phải trên
	pDrawButton(0x7A7D, StartX, (StartY + CuaSoH) - 45.0, 60.0, 45.0, 0, 0);							//Bo gốc trái dưới
	pDrawButton(0x7A7D, (StartX + CuaSoW) - 60.0, (StartY + CuaSoH) - 45.0, 60.0, 45.0, 130.0, 0);		//Bo gốc phải dưới
	gInterface.DrawFormat(eGold, StartX, StartY + 9, CuaSoW, 3, WindowName);
	pGLSwitch();
	EnableAlphaTest(0);
}

void Centralizado::gDrawWindowCustom(float StartX, float StartY, float CuaSoW, float CuaSoH, int eNumWindow, char* WindowName)
{
	if (!gInterface.Data[eNumWindow].OnShow)
	{
		return;
	}

	if (pCheckMouseOver(StartX, StartY, CuaSoW, CuaSoH) == 1)
	{
		gCentral.LockMouseMoveClick = GetTickCount() + 500;
	}
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	float ScaleW = (225 + JCResto / CuaSoW) / pWinWidthReal;
	float ScaleH = (225 / CuaSoH) / pWinHeightReal;
	pSetCursorFocus = true;
	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0); // Màu xám trắng nhạt

	float IsResize = 216;
	if (CuaSoH >= 210)
	{
		IsResize = 220;
	}
	else if (CuaSoH >= 270)
	{
		IsResize = 222;
	}
	else if (CuaSoH >= 350)
	{
		IsResize = 224;
	}
	gCentral.DrawFrame(0x7A5A, StartX, StartY + 10, 225, IsResize, 0.0, 0.0, 270, 225, ScaleW, ScaleH);	//Background
	for (int i = StartX + 10; i < (StartX + CuaSoW) - 110; i += 10)
	{
		pDrawButton(0x7A79, i + 50, StartY, 10.0, 64.0, 60.0, 0);											//Frame ngang Trên
		pDrawButton(0x7A7D, i + 50, (StartY + CuaSoH) - 40.0, 10.0, 45.0, 60.0, 0);							//Frame ngang dưới
	}
	for (int doc = StartY + 10; doc < (StartY + CuaSoH) - 90; doc += 10)
	{
		pDrawButton(0x7A7B, StartX, doc + 50, 21.0, 10, 0, 0);												//Frame dọc trái
		pDrawButton(0x7A7C, (StartX + CuaSoW) - 21.0, doc + 50, 21.0, 10, 0, 0);								//Frame dọc phải
	}

	pDrawButton(0x7A79, StartX, StartY, 60.0, 64.0, 0, 0);												//Bo gốc trái trên
	pDrawButton(0x7A79, (StartX + CuaSoW) - 60.0, StartY, 60.0, 64.0, 130.0, 0);						//Bo gốc phải trên
	pDrawButton(0x7A7D, StartX, (StartY + CuaSoH) - 40.0, 60.0, 45.0, 0, 0);							//Bo gốc trái dưới
	pDrawButton(0x7A7D, (StartX + CuaSoW) - 60.0, (StartY + CuaSoH) - 40.0, 60.0, 45.0, 130.0, 0);		//Bo gốc phải dưới

	gInterface.DrawFormat(eGold, StartX, StartY + 9, CuaSoW, 3, WindowName);
	pGLSwitch();
	EnableAlphaTest(0);
}
void Centralizado::DrawFrame(DWORD ModelID, float X, float Y, float W, float H, float SourceX, float SourceY, float SourceW, float SourceH, float ScaleW, float ScaleH, bool ScaleUp) {
	float v1, v2;

	if (W) {
		W /= ScaleW;
		v1 = ScaleW / (SourceW / W);
	}
	else {
		v1 = ScaleW;
	}

	if (H) {
		H /= ScaleH;
		v2 = ScaleH / (SourceH / H);
	}
	else {
		v2 = ScaleH;
	}
	RenderBitmap(ModelID, X, Y, W, H, SourceX / SourceW, SourceY / SourceH, v1, v2, ScaleUp, 1, 0.0);
}
#include "CustomFont.h"
bool Centralizado::gDrawButton(float PosX, float PosY, float SizeButton, int FontSize, char* ButtonText)
{
	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	float SizeButtonW = SizeButton;
	float SizeButtonH = (SizeButton * 20) / 100;
	float StartX = PosX + JCResto;
	float StartY = PosY;
	bool mreturn = false;
	HFONT FontTextButton = CreateFontA(FontSize, Main_Font_Width, 0, 0, 700, Main_Font_Italic, Main_Font_Underline, Main_Font_StrikeOut, 0x1, 0, 0, Main_Font_Quality, 0, "Tahoma");
	if (pCheckMouseOver(StartX, StartY, SizeButtonW, SizeButtonH) == 1)
	{
		glColor3f(1.0f, 0.6742f, 0.15f);
		if (GetTickCount() - gInterface.Data[eTIME].EventTick > 300) //Click
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(0.72f, 0.438f, 0.0432f);
				gInterface.Data[eTIME].EventTick = GetTickCount();
				mreturn = true;
			}
		}
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	RenderBitmap(31563, StartX, StartY, SizeButtonW, SizeButtonH, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
	CustomFont.Draw(FontTextButton, StartX, StartY + (SizeButtonH / 2) - (FontSize / 2.5) + 2, 0xE6FCF7FF, 0x0, SizeButtonW, 0, 3, ButtonText); //Buoc Vao
	glColor3f(1.0f, 1.0f, 1.0f); //Xoa mau
	DeleteObject(FontTextButton);
	DeleteObject(ButtonText);
	pGLSwitch();
	EnableAlphaTest(0);
	return mreturn;
}
void Centralizado::InitCentral()
{
	SetCompleteHook(0xE9, 0x0054A319, &RemoveShadoW);
	SetCompleteHook(0xE8, 0x0084BC0F, &InfoOverParty);
	SetCompleteHook(0xE8, 0x0084BD1D, &MouseBlockParty);
	SetCompleteHook(0xE8, 0x008490F5, &CheckOptionMouseOver);

	SetCompleteHook(0xE9, 0x008494B0, &RenderWindowsOption);
	SetCompleteHook(0xE9, 0x00849730, &RenderOptionText);
	SetCompleteHook(0xE9, 0x008499E0, &RenderOptionPanel);

	SetCompleteHook(0xE8, 0x00848E5D, &CheckAttackMouseOver);
	SetCompleteHook(0xE8, 0x00848EB2, &CheckBeepMouseOver);
	SetCompleteHook(0xE8, 0x00848F07, &CheckSlideMouseOver);
	SetCompleteHook(0xE8, 0x00848F4B, &CheckSoundMouseOver);
	SetCompleteHook(0xE8, 0x00849087, &CheckEffectMouseOver);
	SetCompleteHook(0xE9, 0x005BB0B0, &this->RenderGame);

	if (gProtect.m_MainInfo.CustomInterfaceType == 4)
	{
		SetCompleteHook(0xE9, 0x00597691, &GlobalMessagem);
		SetCompleteHook(0xE9, 0x005C6E80, &this->MoveRenderCameraDefault);
	}
	else
	{
		SetCompleteHook(0xE9, 0x005C6E80, &CameraGuiReset);
		SetCompleteHook(0xE9, 0x00597691, &GlobalMessagem);

	}
	SetCompleteHook(0xE8, 0x00772960, &fix_resolution_items_size_1);
	SetCompleteHook(0xE8, 0x007729B3, &fix_resolution_items_size_2);
}
void Centralizado::gInfoBox(float PosX, float PosY, float Width, float Height, DWORD bkcolor, float Arg5, int Arg6)
{
	float Red = (float)((bkcolor & 0xff000000) >> 24) / 255.0f;
	float Green = (float)((bkcolor & 0x00ff0000) >> 16) / 255.0f;
	float Blue = (float)((bkcolor & 0x0000ff00) >> 8) / 255.0f;
	float Alpha = (float)(bkcolor & 0x000000ff) / 255.0f;
	pSetBlend(1);
	if (bkcolor)
	{
		glColor4f(Red, Green, Blue, Alpha);
		pDrawBarForm(PosX, PosY, Width + 6.5, Height + 5, Arg5, Arg6); //central
	}
	float RightX = PosX - 2.0f;
	float LeftX = (PosX + Width) - 2.0f;
	float TopY = PosY - 2.0f;
	float DownY = (PosY + Height) - 2.0f;
	bool horizontal = true;
	bool vertical = true;
	float IniciarX = PosX - 2.0f;
	float w = 14.0f;
	float IniciarY = PosY - 2.0f;
	float H = 14.0f;

	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);

	while (vertical || horizontal)
	{
		if (vertical)
		{
			IniciarX += 14.0f;

			if ((IniciarX + w) > LeftX)
			{
				vertical = false;
				w = LeftX - IniciarX;
			}
			pDrawGUI(31344, IniciarX, TopY, w, 14.0f); //Ngang
			pDrawGUI(31345, IniciarX, DownY, w, 14.0f); //Ngang 2
		}
		if (horizontal)
		{
			IniciarY += 14.0f;
			if ((IniciarY + H) > DownY)
			{
				horizontal = false;
				H = DownY - IniciarY;
			}

			pDrawGUI(31346, RightX, IniciarY, 14.0f, H); // Doc 1
			pDrawGUI(31347, LeftX, IniciarY, 14.0f, H); //Doc 2
		}
	}

	pDrawGUI(31340, RightX, TopY, 14.0f, 14.0f); //Goc tren ben trai
	pDrawGUI(31341, LeftX, TopY, 14.0f, 14.0f); //Goc tren ben phai
	pDrawGUI(31342, RightX, DownY, 14.0f, 14.0f);  //Goc duoi trai
	pDrawGUI(31343, LeftX, DownY, 14.0f, 14.0f);  //Goc Duoi phai

	pGLSwitch();
	EnableAlphaTest(0);
}
void Centralizado::gInfoBoxColor(float PosX, float PosY, float Width, float Height, DWORD bkcolor, float Arg5, int Arg6)
{
	float Red = (float)((bkcolor & 0xff000000) >> 24) / 255.0f;
	float Green = (float)((bkcolor & 0x00ff0000) >> 16) / 255.0f;
	float Blue = (float)((bkcolor & 0x0000ff00) >> 8) / 255.0f;
	float Alpha = (float)(bkcolor & 0x000000ff) / 255.0f;
	pSetBlend(1);
	if (bkcolor)
	{
		glColor4f(Red, Green, Blue, Alpha);
		pDrawBarForm(PosX, PosY, Width + 6.5, Height + 5, Arg5, Arg6); //central
	}
	pGLSwitch();
	pSetBlend(0);
	EnableAlphaTest(0);
}
void Centralizado::gItemBoxInv(int X, int Y, int Doc, int Ngang, int Use)
{
	float v6;
	float v7;
	GLfloat red;
	GLfloat green;
	int j;
	int i;

	for (i = 0; i < Doc; ++i)
	{
		for (j = 0; j < Ngang; ++j)
		{
			pSetBlend(1);
			if (Use)
			{
				glColor4f(0.30000001, 0.5, 0.5, 0.60000002);
			}
			else
			{
				glColor4f(0.3, 0.3, 0.3, 0.60000002);
			}
			v7 = (float)(Y + 20 * i);
			v6 = (float)(X + 20 * j);
			pDrawBarForm(LODWORD(v6), LODWORD(v7), 20.0, 20.0, 0.0, 0);
			pSetBlend(true);
			glColor3f(1.0, 1.0, 1.0);
			green = (float)(Y + 20 * i);
			red = (float)(X + 20 * j);
			pDrawGUI(31339, LODWORD(red), LODWORD(green), 21.0, 21.0);
			pGLSwitch();
			EnableAlphaTest(0);
		}
	}
}

