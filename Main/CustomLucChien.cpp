#include "StdAfx.h"
#if LUC_CHIEN
#include "CustomLucChien.h"
#include "Object.h"
#include "ItemManager.h"

CustomLucChien gCustomLucChien;

CustomLucChien::CustomLucChien()
{
	this->Init();
}

void CustomLucChien::Init() // OK
{
	for (int n = 0; n < MAX_CUSTOM_LUCCHIEN; n++)
	{
		this->mLucChienDataItem[n].Index = -1;
	}
}

void CustomLucChien::Load(ITEMDATA_LUCCHIEN* info) // OK
{
	for (int n = 0; n < MAX_CUSTOM_LUCCHIEN; n++)
	{
		this->SetInfo(info[n]);
	}
}

void CustomLucChien::SetInfo(ITEMDATA_LUCCHIEN info) // OK
{
	if (info.Index < 0 || info.Index >= MAX_CUSTOM_LUCCHIEN)
	{
		return;
	}

	this->mLucChienDataItem[info.Index] = info;
}

ITEMDATA_LUCCHIEN* CustomLucChien::GetInfoLucChien(int IndexItem)
{
	for (int n = 0; n < MAX_CUSTOM_LUCCHIEN; n++)
	{
		if (this->mLucChienDataItem[n].IndexMin >= IndexItem && IndexItem <= this->mLucChienDataItem[n].IndexMax)
		{
			return &this->mLucChienDataItem[n];
		}
	}
	return 0;
}
bool CustomLucChien::CheckItemIsSkill(ObjectItem* ItemSearch)
{
	for (int i = 0; i < ItemSearch->SpecialCount; i++)
	{
		if (ItemSearch->SpecialType[i] >= 18 && ItemSearch->SpecialType[i] <=24||
			ItemSearch->SpecialType[i] == 54 ||
			ItemSearch->SpecialType[i] == 56 ||
			ItemSearch->SpecialType[i] == 509 ||
			ItemSearch->SpecialType[i] == 66 ||
			ItemSearch->SpecialType[i] == 62 ||
			ItemSearch->SpecialType[i] == 76 ||
			ItemSearch->SpecialType[i] == 260  ||
			ItemSearch->SpecialType[i] == 261  ||
			ItemSearch->SpecialType[i] == 270)
		{
			return 1;
		}
	}
	return 0;
}
bool CustomLucChien::CheckItemIsLuck(ObjectItem* ItemSearch)
{
	for (int i = 0; i < ItemSearch->SpecialCount; i++)
	{
		if (ItemSearch->SpecialType[i] == 85)
		{
			return 1;
		}
	}
	return 0;
}
int CustomLucChien::CheckItemIsOptLife(ObjectItem* ItemSearch)
{
	for (int i = 0; i < ItemSearch->SpecialCount; i++)
	{
		if (ItemSearch->SpecialType[i] == 84 || ItemSearch->SpecialType[i] == 86 )
		{
			return ItemSearch->SpecialValue[i];
		}
	}
	return 0;
}
BYTE CustomLucChien::GetNewOptionCount(BYTE NewOption) // OK
{
	BYTE count = 0;

	for (int n = 0; n < 6; n++)
	{
		if ((NewOption & (1 << n)) != 0)
		{
			count++;
		}
	}

	return count;
}
BYTE CustomLucChien::GetSocketOptionCount(BYTE SocketOption[5]) // OK
{
	BYTE count = 0;

	for (int n = 0; n < 5; n++)
	{
		if (SocketOption[n] != 0xFF)
		{
			count++;
		}
	}

	return count;
}

int CustomLucChien::TinhToanLucChien(ObjectItem* ItemSearch)
{
	DWORD TinhToanLucChien = 0;
	for (int n = 0; n < MAX_CUSTOM_LUCCHIEN; n++)
	{
		if ((ItemSearch->ItemID) >= this->mLucChienDataItem[n].IndexMin && (ItemSearch->ItemID) <= this->mLucChienDataItem[n].IndexMax)
		{
			TinhToanLucChien += this->mLucChienDataItem[n].LCGoc;
			TinhToanLucChien += this->mLucChienDataItem[n].LCLevel * ((ItemSearch->Level >> 3) & 15);

			TinhToanLucChien += gItemManager.GetItemLevel(ItemSearch->ItemID) *this->mLucChienDataItem[n].LCCap ;
			if (gCustomLucChien.CheckItemIsSkill(ItemSearch))
			{
				TinhToanLucChien += this->mLucChienDataItem[n].LCOptSkill;
			}
			if (gCustomLucChien.CheckItemIsLuck(ItemSearch))
			{
				TinhToanLucChien += this->mLucChienDataItem[n].LCOptLuck;
			}
			if (gCustomLucChien.CheckItemIsOptLife(ItemSearch))
			{
				TinhToanLucChien += (this->mLucChienDataItem[n].LCOptLife * gCustomLucChien.CheckItemIsOptLife(ItemSearch));
			}
			if (ItemSearch->ExcellentOption)
			{
				TinhToanLucChien += (this->mLucChienDataItem[n].LCOptExl * gCustomLucChien.GetNewOptionCount(ItemSearch->ExcellentOption));
			}
			if (ItemSearch->HarmonyType)
			{
				TinhToanLucChien += this->mLucChienDataItem[n].LCOptHarmony;
			}
			if (ItemSearch->Is380Item)
			{
				TinhToanLucChien += this->mLucChienDataItem[n].LCOpt380;
			}
			if (ItemSearch->AncientOption)
			{
				TinhToanLucChien += this->mLucChienDataItem[n].LCOptAnc;
			}
			if (ItemSearch->SocketSet)
			{
				TinhToanLucChien += (this->mLucChienDataItem[n].LCOptSocket * gCustomLucChien.GetSocketOptionCount((BYTE*)ItemSearch->SocketOption));
			}
		}
	}
	return TinhToanLucChien;
}
#endif