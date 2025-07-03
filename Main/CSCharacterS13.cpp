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
#include "CustomPet.h"
#include "Pet.h"
#include "UIControl.h"
#include "CustomRankUser.h"
#include "TAS_HonHoan.h"
#include "Central.h"

#define MAX_CHAR 8

CSCharacterS13 gCSCharacterS13;

char CGetCharacterClass(unsigned __int8 a1)
{
	char v2, v3, v4;

	v2 = 0;
	v3 = ((signed int)a1 >> 3) & 1;
	v4 = ((signed int)a1 >> 4) & 1;
	switch (a1 & 7)
	{
	case 0:
		if (v4) { v2 = 11; }
		else if (v3) { v2 = 7; }
		else { v2 = 0; }
		break;
	case 1:
		if (v4) { v2 = 12; }
		else if (v3) { v2 = 8; }
		else { v2 = 1; }
		break;
	case 2:
		if (v4) { v2 = 13; }
		else if (v3) { v2 = 9; }
		else { v2 = 2; }
		break;
	case 3:
		if (v4)
			v2 = 14;
		else
			v2 = 3;
		break;
	case 4:
		if (v4)
			v2 = 15;
		else
			v2 = 4;
		break;
	case 5:
		if (v4) { v2 = 16; }
		else if (v3) { v2 = 10; }
		else { v2 = 5; }
		break;
	case 6:
		if (v4)
			v2 = 17;
		else
			v2 = 6;
		break;
	case 7:
		if (v4) { v2 = 22; }
		else if (v3) { v2 = 21; }
		else { v2 = 20; }
		break;
	default:
		return v2;
	}
	return v2;
}
int JCGetClassname(unsigned __int8 a4)
{
	int result;
	char v5;
	v5 = CGetCharacterClass(a4);
	if (v5)
	{
		switch (v5)
		{
			case 1:			result = (int)pGetTextLine(pTextLineThis, 21);			break; //-- Dark Knight
			case 2: 		result = (int)pGetTextLine(pTextLineThis, 22);			break;//-- Elf
			case 3: 		result = (int)pGetTextLine(pTextLineThis, 23);			break;//-- Magic Gladiator
			case 4: 		result = (int)pGetTextLine(pTextLineThis, 24);			break;//-- Dark Lord
			case 5: 		result = (int)pGetTextLine(pTextLineThis, 1687);		break;//-- Summoner
			case 6: 		result = (int)pGetTextLine(pTextLineThis, 3150);		break;//-- Rage Fighter
			case 7: 		result = (int)pGetTextLine(pTextLineThis, 25);			break;//-- Soul Master
			case 8: 		result = (int)pGetTextLine(pTextLineThis, 26);			break;//-- Blade Knight
			case 9: 		result = (int)pGetTextLine(pTextLineThis, 27);			break;//-- Muse Elf
			case 10:		result = (int)pGetTextLine(pTextLineThis, 1688);		break;//-- Bloody Summoner
			case 11:		result = (int)pGetTextLine(pTextLineThis, 1669);		break;//-- Grand Master
			case 12:		result = (int)pGetTextLine(pTextLineThis, 1668);		break;//-- Blade Master
			case 13:		result = (int)pGetTextLine(pTextLineThis, 1670);		break;//-- High Elf
			case 14:		result = (int)pGetTextLine(pTextLineThis, 1671);		break;//-- Dual Master
			case 15:		result = (int)pGetTextLine(pTextLineThis, 1672);		break;//-- Lord Emperor
			case 16:		result = (int)pGetTextLine(pTextLineThis, 1689);		break;//-- Dimension Master
			case 17:		result = (int)pGetTextLine(pTextLineThis, 3151);		break;//-- Fist Master
			case 20:		result = (int)pGetTextLine(pTextLineThis, 3175);		break;//-- Grow Lancer
			case 21:		result = (int)pGetTextLine(pTextLineThis, 3176);		break;//-- Mirage Lancer
			case 22:		result = (int)pGetTextLine(pTextLineThis, 3176);		break;//-- Shining Lancer
			default:		result = (int)pGetTextLine(pTextLineThis, 2305);		break;//-- Error Code :
		}
	}
	else
	{
		result = (int)pGetTextLine(pTextLineThis, 20); //-- Dark Wizard
	}
	return result;
}
void GetColorCTCode(BYTE CTLCODE)
{
	int v9; // [sp+4h] [bp-8h]@1

	if (CTLCODE & 1)
	{
		v9 = -256;
	}
	else if (CTLCODE & 0x12)
	{
		v9 = -14165505;
	}
	else if (CTLCODE & 4)
	{
		v9 = -1;
	}
	else if (CTLCODE & 8)
	{
		v9 = -16776961;
	}
	else if (CTLCODE & 0x20)
	{
		v9 = -16776961;
	}
	else
	{
		v9 = -1;
	}

	SetTextColorByHDC(pTextThis(), v9);
}
int GetStatus(BYTE GuildStatus)
{
	if (GuildStatus <= 64)
	{
		if (GuildStatus == 64)
		{
			return 1301;
		}
		else if (GuildStatus)
		{
			if (GuildStatus != 32)
				goto LABEL_29;
			return 1302;
		}
		else
		{
			return 1330;
		}
	}
	if (GuildStatus == 128)
	{
	LABEL_29:
		return 1300;
	}
	else if (GuildStatus == 255)
	{
		return 488;
	}

	return 488;
}

int CSCharacterS13::JPlayerAddList(PMSG_CHARACTER_CREATE_RECV* lpMsg)
{
	signed int result; // eax@10
	DWORD v10; // [sp+20h] [bp-10h]@8
	float v11; // [sp+1Ch] [bp-14h]@2
	float v12; // [sp+24h] [bp-Ch]@0
	float v13; // [sp+28h] [bp-8h]@0

	PMSG_CHARACTER_LIST* lpInfo;

	std::map<int, PMSG_CHARACTER_LIST>::iterator it;
	
	if (lpMsg->result == 1)
	{
		if (lpMsg->slot >= 0 && lpMsg->slot < MAX_CHAR)
		{
			lpInfo = new PMSG_CHARACTER_LIST;
			lpInfo->slot = lpMsg->slot;
			memcpy(lpInfo->Name, lpMsg->name, sizeof(lpInfo->Name));
			lpInfo->Level = 400;
			lpInfo->GuildStatus = 255;
			lpInfo->CtlCode = 0;
			lpInfo->CharSet[0] = lpMsg->Class;
			lpInfo->Reset = 1;
			lpInfo->MasterReset = 0;

			lpInfo->pDanhHieu = 0;
			lpInfo->pQuanHam = 0;
			lpInfo->pTuLuyen = 0;
			lpInfo->pHonHoan = 0;
			
			for (int o = 1; o < 18; o++)
			{
				lpInfo->CharSet[o] = 0xFF;
			}

			it = gCSCharacterS13.lpInfoPlayer.find(lpMsg->slot);

			if (it != gCSCharacterS13.lpInfoPlayer.end())
			{
				gCSCharacterS13.lpInfoPlayer.erase(it);
			}
			gCSCharacterS13.lpInfoPlayer.insert(std::pair<int, PMSG_CHARACTER_LIST >(lpMsg->slot, *(PMSG_CHARACTER_LIST*)lpInfo));

		}
	}
	return 1;
}

int CSCharacterS13::JPlayerList(PMSG_CHARACTER_LIST_RECV* lpMsg)
{
	int v4; // ST1C_4@11
	DWORD result; // eax@12
	int v10; // [sp+18h] [bp-1Ch]@5
	float v11; // [sp+1Ch] [bp-18h]@5
	float v12; // [sp+20h] [bp-14h]@0
	float v13; // [sp+24h] [bp-10h]@0
	int PlayerSlot;
	int PlayerSelect;

	sub_63CB40();
	sub_4D5130(lpMsg->ClassCode);

	if (pPlayerState == 4)
		*(DWORD*)0xE61E18 = 93;

	gCSCharacterS13.lpInfoPlayer.clear();
	PlayerSlot = 0;
	PlayerSelect = 1;

	for (int n = 0; n < lpMsg->count; n++)
	{
		PMSG_CHARACTER_LIST* lpInfo = (PMSG_CHARACTER_LIST*)(((BYTE*)lpMsg) + sizeof(PMSG_CHARACTER_LIST_RECV) + (sizeof(PMSG_CHARACTER_LIST) * n));

		if (lpInfo->slot >= 0 && lpInfo->slot < MAX_CHAR)
		{
			gCSCharacterS13.lpInfoPlayer.insert(std::pair<int, PMSG_CHARACTER_LIST >(lpInfo->slot, *(PMSG_CHARACTER_LIST*)lpInfo));
		}

		v10 = (unsigned __int8)sub_587380(lpInfo->CharSet[0]);	//class
		v11 = 0.0;

		switch (lpInfo->slot)
		{
		case 0:
			v12 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.CoordX;// 8008.0;
			v13 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.CoordY;// 18885.0;
			v11 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.Rotate;// 115.0;
			PlayerSlot = 1;
			break;
		case 1:
			v12 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.CoordX;// 8008.0;
			v13 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.CoordY;// 18885.0;
			v11 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.Rotate;// 115.0;
			PlayerSlot = 1;
			break;
		case 2:
			v12 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.CoordX;// 8008.0;
			v13 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.CoordY;// 18885.0;
			v11 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.Rotate;// 115.0;
			PlayerSlot = 1;
			break;
		case 3:
			v12 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.CoordX;// 8008.0;
			v13 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.CoordY;// 18885.0;
			v11 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.Rotate;// 115.0;
			PlayerSlot = 1;
			break;
		case 4:
			v12 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.CoordX;// 8008.0;
			v13 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.CoordY;// 18885.0;
			v11 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.Rotate;// 115.0;
			PlayerSlot = 1;
			break;
		case 5:
			v12 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.CoordX;// 8008.0;
			v13 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.CoordY;// 18885.0;
			v11 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.Rotate;// 115.0;
			PlayerSlot = 1;
			break;
		case 6:
			v12 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.CoordX;// 8008.0;
			v13 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.CoordY;// 18885.0;
			v11 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.Rotate;// 115.0;
			PlayerSlot = 1;
			break;
		case 7:
			v12 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.CoordX;// 8008.0;
			v13 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.CoordY;// 18885.0;
			v11 = gSelectCharRamdon.RenderSelect.PJ[lpInfo->slot].Coordenada1.Rotate;// 115.0;
			PlayerSlot = 1;
			break;
		default:
			break;
		}

		if (PlayerSlot == PlayerSelect)
		{
			PlayerSelect = 2;
			SetDword(0x004D6C73, lpInfo->slot);
		}

		v4 = JCSetModelCoord(lpInfo->slot, v10, 0, v12, v13, v11);//-- Agrega Personaje con Coordenada

		*(WORD*)(v4 + 130) = lpInfo->Level;

		*(BYTE*)(v4 + 21) = lpInfo->CtlCode;

		sub_9CF1C0((char*)(v4 + 56), lpInfo->Name, 0xAu);

		*(BYTE*)(v4 + 66) = 0;

		gCustomPet.PreviewCharSet(lpInfo->slot, &lpInfo->CharSet[1], 0, 0);//-- Mostrar Equipamiento

		*(BYTE*)(v4 + 24) = lpInfo->GuildStatus;

	}

	*(DWORD*)0x87935A4 = 51;

	pWarehouseExSet(pWarehouseExThis(pWindowThis()), lpMsg->ExtWarehouse);

	result = GetTickCount();
	*(DWORD*)0xE8CB30 = result;
	return result;
}

signed int JGCreateCharRecv(int JCCHARACTER)
{
	signed int result; // eax@10
	DWORD v10; // [sp+20h] [bp-10h]@8
	float v11; // [sp+1Ch] [bp-14h]@2
	float v12; // [sp+24h] [bp-Ch]@0
	float v13; // [sp+28h] [bp-8h]@0
	BYTE Slot;


	if (*(BYTE*)(JCCHARACTER + 4) == 1)
	{
		v11 = 0.0;
		Slot = *(BYTE*)(JCCHARACTER + 15);
		switch (Slot)
		{
		case 0:
			v12 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.CoordX;// 8008.0;
			v13 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.CoordY;// 18885.0;
			v11 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.Rotate;// 115.0;
			break;
		case 1:
			v12 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.CoordX;// 8008.0;
			v13 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.CoordY;// 18885.0;
			v11 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.Rotate;// 115.0;
			break;
		case 2:
			v12 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.CoordX;// 8008.0;
			v13 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.CoordY;// 18885.0;
			v11 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.Rotate;// 115.0;
			break;
		case 3:
			v12 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.CoordX;// 8008.0;
			v13 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.CoordY;// 18885.0;
			v11 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.Rotate;// 115.0;
			break;
		case 4:
			v12 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.CoordX;// 8008.0;
			v13 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.CoordY;// 18885.0;
			v11 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.Rotate;// 115.0;
			break;
		case 5:
			v12 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.CoordX;// 8008.0;
			v13 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.CoordY;// 18885.0;
			v11 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.Rotate;// 115.0;
			break;
		case 6:
			v12 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.CoordX;// 8008.0;
			v13 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.CoordY;// 18885.0;
			v11 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.Rotate;// 115.0;
			break;
		case 7:
			v12 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.CoordX;// 8008.0;
			v13 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.CoordY;// 18885.0;
			v11 = gSelectCharRamdon.RenderSelect.PJ[Slot].Coordenada2.Rotate;// 115.0;
			break;
		default:
			break;
		}

		sub_57D760(*(BYTE*)(JCCHARACTER + 15));
		JCSetModelCoord(*(BYTE*)(JCCHARACTER + 15), (unsigned __int8)*(BYTE*)0x7BD0483, *(BYTE*)0x7BD0484, v12, v13, v11);

		v10 = pGetPreviewStruct(pPreviewThis(), *(BYTE*)(JCCHARACTER + 15));

		if (v10)
		{
			*(WORD*)(v10 + 130) = *(WORD*)(JCCHARACTER + 16);
			*(BYTE*)(v10 + 19) = sub_587380(*(BYTE*)(JCCHARACTER + 18));
			sub_9CF1C0((char*)(v10 + 56), (const void*)(JCCHARACTER + 5), 0xAu);
			*(BYTE*)(v10 + 66) = 0;
		}

		*(DWORD*)0x87935A4 = 53;

		sub_668520((char*)sub_482B70());
		sub_4057B0((char*)sub_482B70() + 32632);
		result = sub_402AD0((char*)sub_482B70() + 36744);
}
	else
	{
		result = *(BYTE*)(JCCHARACTER + 4);
		if (*(BYTE*)(JCCHARACTER + 4))
		{
			if (*(BYTE*)(JCCHARACTER + 4) == 2)
			{
				result = sub_484A10(sub_482B70(), 55, 0);
			}
		}
		else
		{
			result = sub_484A10(sub_482B70(), 54, 0);
		}
	}
	return result;
}


int PushBackPlayer(int a4)
{
	signed int v4; 
	int v5;
	int v6;
	int result;
	char v12;

	v12 = *(BYTE*)(a4 + 4);

	if (v12)
	{
		if (v12 == 1)
		{
			v6 = sub_96A4C0(sub_402BC0(), SelectedHero);
			sub_57D760(*(WORD*)(v6 + 126));

			std::map<int, PMSG_CHARACTER_LIST>::iterator it = gCSCharacterS13.lpInfoPlayer.find(SelectedHero);

			if (it != gCSCharacterS13.lpInfoPlayer.end())
			{
				gCSCharacterS13.lpInfoPlayer.erase(it);
			}

			result = sub_484A10(sub_482B70(), 96, 0);
		}
		else if (v12 == 3)
		{
			result = sub_484A10(sub_482B70(), 98, 0);
		}
		else
		{
			result = sub_484A10(sub_482B70(), 137, 0);
		}
}
	else
	{
		result = sub_484A10(sub_482B70(), 146, 0);
	}
	return result;
}
void CSCharacterS13::GetBarSelectCharacter(int a, int b, int c, int d, BYTE Slot)
{
	VAngle Angle;

	float ACoord_X = 25.0f + d;
	float ACoord_Y = 70.0f - c;
	#define BitMapRenderW 95
	#define BitMapRenderX 19

	std::map<int, PMSG_CHARACTER_LIST>::iterator it = this->lpInfoPlayer.find(Slot);
	if (it != this->lpInfoPlayer.end())
	{
		char ClassName[11] = { 0 };
		memcpy(ClassName, it->second.Name, sizeof(it->second.Name));

		DWORD ViewportAddress = pGetPreviewStruct(pPreviewThis(), Slot);
		Angle.X = *(float*)(ViewportAddress + 1028);
		Angle.Y = *(float*)(ViewportAddress + 1032);
		Angle.Z = *(float*)(ViewportAddress + 1036) + *(float*)(ViewportAddress + 0x3E8) + 350.0f;

		pGetPosFromAngle(&Angle, &a, &b);
		RenderBitmap(0x1791C, a - ACoord_X - 1, b + ACoord_Y, BitMapRenderW, 60, 0, 0, 1, 1, 1, 1, 0.0);
		pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
		GetColorCTCode(it->second.CtlCode);
		g_pRenderText.CRenderText(a - (ACoord_X + BitMapRenderX), b + (ACoord_Y + 3), ClassName, BitMapRenderW, 0, 3, 0);

		char ClassLevel[255];
		ZeroMemory(ClassLevel, sizeof(ClassLevel));
		wsprintf(ClassLevel, "%s - %d", (char*)JCGetClassname((unsigned __int8)sub_587380(it->second.CharSet[0])), it->second.Level);
		SetTextColorByHDC(pTextThis(), pMakeColor(0xD8u, 0xA6u, 0x9u, 0xFFu));
		g_pRenderText.CRenderText(a - (ACoord_X + BitMapRenderX), b + (ACoord_Y + 12), ClassLevel, BitMapRenderW, 0, 3, 0);

		char IsStatus[255];
		ZeroMemory(IsStatus, sizeof(IsStatus));
		wsprintf(IsStatus, "(%s)", pGetTextLine(pTextLineThis, GetStatus(it->second.GuildStatus)));
		SetTextColorByHDC(pTextThis(), pMakeColor(0xFFu, 0xFFu, 0xFFu, 0xFFu));
		g_pRenderText.CRenderText(a - (ACoord_X + BitMapRenderX), b + (ACoord_Y + 21), IsStatus, BitMapRenderW, 0, 3, 0);
	}

}
void CSCharacterS13::StatusInfo()
{
	VAngle Angle;
	int v48;
	int v49;
	#if SELECT_CHAR_INFO
	GetBarSelectCharacter(v48, v49,  0, 0, 0);
	GetBarSelectCharacter(v48, v49, 10, 0, 1);
	GetBarSelectCharacter(v48, v49, 20, 5, 2);
	GetBarSelectCharacter(v48, v49, 30, 4, 3);
	GetBarSelectCharacter(v48, v49, 20, 5, 4);
	GetBarSelectCharacter(v48, v49, 10, 12, 5);
	GetBarSelectCharacter(v48, v49,  0, 15, 6);
	#endif
}
int sub_402A80(int a1)
{
	if (pPlayerState == 4) //Select Character
	{
		gCSCharacterS13.StatusInfo();
	}
	return 1;
}

void CSCharacterS13::initCharacter()
{
	#if(MAX_CHAR > 5)
	SetByte(0x004057E5, 0x7);
	SetByte(0x00405881, 0x7);
	SetByte(0x004D6F66, 0x7);
	SetByte(0x004D7075, 0x6);
	SetByte(0x004D70B0, 0x6);
	SetByte(0x004D71E0, 0x7);
	SetByte(0x004D72C7, 0x7);
	#endif
	
	SetByte(0x00402106, 0);
	SetDouble(0xD25508, 1);

	SetCompleteHook(0xE9, 0x00587620, &JCGetClassname);
	SetCompleteHook(0xE9, 0x0063D3D0, &JGCreateCharRecv);
	SetCompleteHook(0xE9, 0x0063D5E0, &PushBackPlayer);
	SetCompleteHook(0xE8, 0x004849C0, &sub_402A80);	
}