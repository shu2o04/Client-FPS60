#pragma once
#define oUserPreviewStruct			*(int*)0x7BC4F04
struct CUSTOM_PET_INFO
{
	int Index;
	int ItemIndex;
	int IndexInventory;
	int PetType;
	char ModelName[50];
	int FenrrirEffect;
	float Scale_Inve;
	float Scale_Drop;
	float Scale_View;
};


class cCustomPet
{
public:
	cCustomPet();
	void Init();
	void Load(CUSTOM_PET_INFO* info);
	int GetInfoByItem(int ItemIndex);
	int GetInfoByItemInventory(int ItemIndex);
	int GetInfoPetType(int ItemIndex); // OK
	int GetInfoPetEffect(int ItemIndex); // OK
	int GetInfoPetTypex(int ItemIndex); //Fix Xpet muun
	float GetScaleInv(int ItemIndex);
	float GetScaleDrop(int ItemIndex);
	float GetScaleView(int ItemIndex);
	bool CheckCustomPetByItem(int ItemIndex);
	std::map<int, CUSTOM_PET_INFO> m_CustomPetInfo;
};

extern cCustomPet gCustomPet2;