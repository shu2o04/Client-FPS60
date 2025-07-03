#include "stdafx.h"
#include "CustomModelFlag.h"
#include "MemScript.h"
#include "Object.h"
#include "Extras.h"
#include "User.h"
#include "CustomRankUser.h"
#include "Import.h"
#if(SLOTPET2)
#include "NewUIMyInventory.h"
#endif
#if(HT_THUE_FLAG)

CustomModelFlag gCustomModelFlag;

CustomModelFlag::CustomModelFlag()
{
	this->mModelFlagData.clear();
	this->mJPGFlagData.clear();
}

void CustomModelFlag::SetInfo(MODEL_FLAG* info) // OK
{

	for (int n = 0; n < MAX_MODEL_FLAG; n++)
	{
		if (info[n].Index < 0 || info[n].Index >= MAX_MODEL_FLAG)
		{
			return;
		}
		this->mModelFlagData.insert(std::pair<int, MODEL_FLAG>(info[n].ModelIndex, info[n]));
	}
}

void CustomModelFlag::SetInfoJPG(JPG_FLAG* info) // OK
{
	for (int n = 0; n < MAX_MODEL_FLAG; n++)
	{
		if (info[n].Index < 0 || info[n].Index >= MAX_MODEL_FLAG)
		{
			return;
		}
		this->mJPGFlagData.insert(std::pair<int, JPG_FLAG>(info[n].ImgIndex, info[n]));
	}
}
#define RenderTerrainAlphaBitmap             		((void(__cdecl*)(int Texture,float xf,float yf,float SizeX,float SizeY,vec3_t Light,float Xoay,float Alpha,float Height, int DoCao)) 0x005DAD80)

void CustomModelFlag::RenderEffectJPG(ObjectPreview* ObjectPointer, int ImgIndex)
{
	std::map<int, JPG_FLAG>::iterator it = this->mJPGFlagData.find(ImgIndex);

	if (it == this->mJPGFlagData.end())
	{
		return;
	}

	vec3_t Color;
	Vector(1.0, 1.0, 1.0, Color);
	EnableAlphaBlend();
	RenderTerrainAlphaBitmap(ImgIndex, ObjectPointer->m_Model.VecPos.X, ObjectPointer->m_Model.VecPos.Y, it->second.ScaleX, it->second.ScaleY, Color, WorldTime * 0.05f, 1.0, 5, 1);
	DisableAlphaBlend();
}


void CustomModelFlag::BIRender(int* This, int* a2)
{
	int v4; // [esp+8h] [ebp-24h]
	int v5; // [esp+8h] [ebp-24h]
	int Model; // [esp+14h] [ebp-18h]
	int v8; // [esp+14h] [ebp-18h]
	float v9[3]; // [esp+18h] [ebp-14h] BYREF

	float v10; // [esp+24h] [ebp-8h]
	static int BBBoneTransform;
	int BBGetObject;
	if (a2)
	{
		CHARACTER c = (CHARACTER)a2;
		OBJECT* pObj = &*(OBJECT*)CSGetObjectA(&*(int*)This);
		BBGetObject = (int)(&c->Object);

		if (*((float*)This + 39) >= 0.009999999776482582)
		{
			v4 = *((DWORD*)a2 + 206);
			Model = sub_969C50_Addr(sub_4CDA10_Addr(), v4);
			if (Model)
			{
				BBBoneTransform = GetBoneTransform(BBGetObject, *((DWORD*)This + 163));
				if (BBBoneTransform)
				{
					TransformPosition((int)Model, BBBoneTransform, (float* const)This + 164, v9, 1);
					{
						*((float*)This + 64) = v9[0];
						*((float*)This + 65) = v9[1];
						*((float*)This + 66) = v9[2];
					}
					if (!*((BYTE*)This + 9))
					{
						*((float*)This + 67) = *((float*)a2 + 260);
						*((float*)This + 68) = *((float*)a2 + 261);
						*((float*)This + 69) = *((float*)a2 + 262);
					}

					v5 = *((DWORD*)This + 13);
					v8 = sub_969C50_Addr(sub_4CDA10_Addr(), v5);
					if (v8)
					{
						*(WORD*)(v8 + 160) = *((WORD*)This + 11);
						v10 = *((float*)This + 31);
						BMDPlayAnimation(
							v8,
							(int)This + 144,
							(int)This + 148,
							(int)This + 24,
							v10,
							(int)This + 256,
							(int)This + 268);
						*(float*)(v8 + 72) = 1.0;
						*(float*)(v8 + 76) = 1.0;
						*(float*)(v8 + 80) = 1.0;
						RenderObject(pObj, 1, 0, 0);

					}
				}
			}
		}
	}
}
bool CustomModelFlag::CheckFlagModelIsLoad(int BMDIndex)
{
	if (BMDIndex != 0)
	{
		std::map<int, MODEL_FLAG>::iterator it = this->mModelFlagData.find(BMDIndex);

		if (it != this->mModelFlagData.end())
		{
			return 1;
		}
	}
	return 0;
}

void CustomModelFlag::RenderEffectBMD(int This, int BMDIndex, float* CacheBMD)
{
	std::map<int, MODEL_FLAG>::iterator it = this->mModelFlagData.find(BMDIndex);

	if (it == this->mModelFlagData.end())
	{
		return;
	}
	CHARACTER c = (CHARACTER)This;
	OBJECT* pObj = &*(OBJECT*)CSGetObjectA(&*(int*)CacheBMD);
	pObj->Velocity = it->second.AnimationSpeed; //Speed
	pObj->Scale = c->Object.Scale + it->second.ScaleView; //Size
	pObj->Owner = &c->Object;
	this->BIRender(&*(int*)CacheBMD, &*(int*)This);
}

bool CustomModelFlag::CheckFlag(int ItemIndex) // OK
{
	std::map<int, MODEL_FLAG>::iterator it = this->mModelFlagData.find(ItemIndex);
	if (it != this->mModelFlagData.end())
	{
		return  1;
	}
	return false;
}
#endif