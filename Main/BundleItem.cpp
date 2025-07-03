#include "stdafx.h"
#include "BundleItem.h"
#include "Util.h"
#include "TMemory.h"
#include "Import.h"
#include "Object.h"

cBundleItem BundleItem;

cBundleItem::cBundleItem()
{
	this->Init();
}

void cBundleItem::Init()
{
	this->Hook();
	this->m_List.clear();
}

void __declspec(naked) CheckBundleItem()
{
	static DWORD ItemIndex = 0;
	static DWORD AddressJNE = 0x007DCDC3;
	static DWORD AddressJmp = 0x007DCD51;

	_asm
	{
		mov ItemIndex, eax
	}
	if (ItemIndex == 7301)
	{
		_asm
		{
			jmp AddressJmp;
		}
	}
	else
	{
		_asm
		{
			Mov Edx, Dword Ptr Ss : [Ebp - 0x18];
			Movsx Eax, Word Ptr Ds : [Edx];
			Push Eax;
			Lea Ecx, BundleItem;
			Call[cBundleItem::IsBundleItem];
			Test Eax, Eax;
			Jne Success;
			Jmp AddressJNE;
		Success:
			jmp AddressJmp;
		}
	}
}

bool CheckRepairBan(lpItemObj item)
{
	if (((bool(__cdecl*)(lpItemObj item)) 0x005C9A00)(item))
	{
		return !BundleItem.CheckBundleItemUnmix(item->ItemID, (item->Level >> 3) & 15, item->Durability);
	}
	return false;
}

void __declspec(naked) ReceiveModifyItemCheck()
{
	static DWORD address_64BD1A = 0x0064BD1A;
	static DWORD address_64BD15 = 0x0064BD15;
	static DWORD address_64BD79 = 0x0064BD79;
	static DWORD Result = 0;
	_asm
	{
		push	eax;
		lea		ecx, BundleItem;
		call[cBundleItem::ReceiveModifyItemMode];
		mov		Result, eax;
	}

	if (Result == 2)
	{
		_asm
		{
			jmp address_64BD79;
		}
	}
	else if (Result == 1)
	{
		_asm
		{
			jmp address_64BD15;
		}
	}
	else
	{
		_asm
		{
			jmp address_64BD1A;
		}
	}
}



void cBundleItem::Hook()
{
	SetRange(0x007DCD4A, 7, 144);
	SetJmp((LPVOID)0x007DCD4A, CheckBundleItem);
	SetJmp((LPVOID)0x0064BD0C, ReceiveModifyItemCheck);

	SetCompleteHook(0xE8, 0x0083B438, &CheckRepairBan);
}

int cBundleItem::ReceiveModifyItemMode(BYTE* lpMsg)
{
	PMSG_ITEM_MODIFY_RECV* Data = (PMSG_ITEM_MODIFY_RECV*)lpMsg;

	if (Data->mode == 2)
	{
		if (((int(*)()) 0x007DD0F0)())
		{
			int pOwner = ((DWORD(__thiscall*)(int)) 0x007D9410)(*(DWORD*)0x9816F7C);
			lpItemObj item = (lpItemObj)((int(__thiscall*)(int)) 0x007D9430)(((int(*)()) 0x007DD0F0)());

			int slot = 12 + item->PosX + item->PosY * 8;

			if (pOwner &&
				Data->slot == slot)
			{
				item->Durability = Data->ItemInfo[2];
			}
		}
		return 2;
	}
	else if (Data->mode == 1)
	{
		return 0;
	}
	else
	{
		return (bool)((int(*)()) 0x007DD0F0)();
	}
}

bool cBundleItem::CheckBundleItemUnmix(WORD index, BYTE Level, int dur)
{
	for (int i = 0; i < this->m_List.size(); i++)
	{
		if (index == this->m_List[i].Index &&
			(Level == this->m_List[i].Level || this->m_List[i].Level == -1) &&
			dur != 1)
		{
			return true;
		}
	}
	return false;
}

bool cBundleItem::IsBundleItem(DWORD index)
{
	for (int i = 0; i < this->m_List.size(); i++)
	{
		if (index == this->m_List[i].Index && index != 0)
		{
			return true;
		}
	}
	return false;
}

bool cBundleItem::CanMakeBundleItem(lpItemObj pPickItem, lpItemObj pTargetItem)
{
	if (pPickItem->ItemID != pTargetItem->ItemID)
	{
		return 0;
	}
	return 1;
}
#include "Interface.h"
void cBundleItem::GCBundleItemConfigRecv(BYTE* lpMsg)
{
	this->m_List.clear();
	PMSG_BUNDLE_ITEM_INFO_HEADER_RECV* Data = (PMSG_BUNDLE_ITEM_INFO_HEADER_RECV*)lpMsg;
	if (Data->Count > 0) {
		int Offset = sizeof(PMSG_BUNDLE_ITEM_INFO_HEADER_RECV);
		for (int i = 0; i < Data->Count; i++) {
			BI_Data* Data2 = (BI_Data*)(lpMsg + Offset);

			BI_Data Info = {};

			Info.Index = Data2->Index;
			Info.Level = Data2->Level;
			Info.Max = Data2->Max;
			this->m_List.push_back(Info);
			Offset += sizeof(BI_Data);
		}
	}
}
