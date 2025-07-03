#include "stdafx.h"
#include "CustomPet.h"
#include "Defines.h"
#include "Pet.h"
cCustomPet gCustomPet2;

cCustomPet::cCustomPet() // OK
{
	this->Init();
}

void cCustomPet::Init() // OK
{
	this->m_CustomPetInfo.clear();
}

void cCustomPet::Load(CUSTOM_PET_INFO* info) // OK
{
	for (int n = 0; n < MAX_PET_ITEM; n++)
	{
		if (info[n].Index < 0 || info[n].Index >= MAX_PET_ITEM)
		{
			return;
		}
		this->m_CustomPetInfo.insert(std::pair<int, CUSTOM_PET_INFO>(info[n].ItemIndex,info[n]));
	}
}

int cCustomPet::GetInfoByItem(int ItemIndex) // OK
{
	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if(it != this->m_CustomPetInfo.end())
	{
		if(it->second.PetType == 6)
		{
			return it->second.ItemIndex + 1171;
		}
	}
	return -1;
}

int cCustomPet::GetInfoByItemInventory(int ItemIndex) // OK
{
	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if(it != this->m_CustomPetInfo.end())
	{
		return it->second.IndexInventory + 1171;
	}
	return -1;
}

int cCustomPet::GetInfoPetType(int ItemIndex) //  OK
{
	lpViewObj Object = &*(ObjectPreview*)oUserPreviewStruct;

	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if (it != this->m_CustomPetInfo.end())
	{
		if (it->second.PetType == 5 || it->second.PetType == 6 || it->second.PetType == 7)
		{
			if (Object->InSafeZone)
			{
				return 8;
			}
			else
			{
				return it->second.PetType;
			}
		}
		else
		{
			return it->second.PetType;
		}
	}
	return -1;
}

int cCustomPet::GetInfoPetEffect(int ItemIndex) // OK
{
	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if(it != this->m_CustomPetInfo.end())
	{
		return it->second.FenrrirEffect;
	}
	return 0;
}

float cCustomPet::GetScaleInv(int ItemIndex)
{
	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if(it != this->m_CustomPetInfo.end())
	{
		return it->second.Scale_Inve;
	}
	return -1;
}

float cCustomPet::GetScaleDrop(int ItemIndex)
{
	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if(it != this->m_CustomPetInfo.end())
	{
		return it->second.Scale_Drop;
	}
	return -1;
}

float cCustomPet::GetScaleView(int ItemIndex)
{
	lpViewObj Object = &*(ObjectPreview*)oUserPreviewStruct;

	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if (it != this->m_CustomPetInfo.end())
	{
		if (it->second.PetType == 5 || it->second.PetType == 6 || it->second.PetType == 7)
		{

			if (Object->InSafeZone)
			{
				return it->second.Scale_View - 0.4;
			}
			else
			{
				return it->second.Scale_View;
			}
		}
		else
		{
			return it->second.Scale_View;
		}
	}
	return -1;
}

bool cCustomPet::CheckCustomPetByItem(int ItemIndex) // OK
{
	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if(it != this->m_CustomPetInfo.end())
	{
		return true;
	}
	return false;
}

int cCustomPet::GetInfoPetTypex(int ItemIndex) // OK
{

	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if (it != this->m_CustomPetInfo.end())
	{
		return it->second.PetType;
	}
	return -1;
}