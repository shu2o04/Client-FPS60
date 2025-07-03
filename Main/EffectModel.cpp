#include "stdafx.h"
#include "EffectModel.h"
#include "Import.h"
#include "Defines.h"
#include "Object.h"
#include "Interface.h"
#include "TMemory.h"
#include "Protect.h"
#include "Config.h"
#include "ModelEffect.h"
#include "Util.h"
#include "zzzmathlib.h"
CCopyEffect gCopyEffect;

CCopyEffect::CCopyEffect()
{

}
CCopyEffect::~CCopyEffect()
{

}

void CCopyEffect::DrawViewPortEffects(DWORD ObjectPointer, DWORD ObjectModel, DWORD a3)
{
	lpViewObj Object = &*(ObjectPreview*)(ObjectPointer);

	MU3Float lBone[MAX_MODEL_EFFECT];
	MU3Float lBone2[MAX_MODEL_EFFECT];
	vec3_t Color;
	vec3_t ColorRandom;
	//
	for (int i = 0; i < MAX_MODEL_EFFECT; i++)
	{
		lBone[i].X = *(float*)(ObjectModel + 252);
		lBone[i].Y = *(float*)(ObjectModel + 256);
		lBone[i].Z = *(float*)(ObjectModel + 260);
		lBone2[i].X = *(float*)(ObjectModel + 264);
		lBone2[i].Y = *(float*)(ObjectModel + 268);
		lBone2[i].Z = *(float*)(ObjectModel + 272);
	}
	//
	Vector(1.0, 1.0, 1.0, Color);
	Vector(((float)(rand() % 100) / 100), ((float)(rand() % 100) / 100), ((float)(rand() % 100) / 100), ColorRandom);
	for (int i = 0; i < MAX_MODEL_EFFECT; i++)
		//QUANGKY
	{
		if (Object->HelmSlot == ITEM2(gCustomModelEffect.m_CustomModelEffectInfo[i].ItemType, gCustomModelEffect.m_CustomModelEffectInfo[i].ItemIndex) &&
			Object->HelmLevel >= gCustomModelEffect.m_CustomModelEffectInfo[i].MinLevel && Object->HelmLevel <= gCustomModelEffect.m_CustomModelEffectInfo[i].MaxLevel &&
			Object->HelmExcellent >= gCustomModelEffect.m_CustomModelEffectInfo[i].MinExcellent && Object->HelmExcellent <= gCustomModelEffect.m_CustomModelEffectInfo[i].MaxExcellent)
		{
			lBone[i].Z = lBone[i].Z + (float)(150);
			lBone2[i].Z = lBone2[i].Z + (float)(150);
			Vector(gCustomModelEffect.m_CustomModelEffectInfo[i].Color[0], gCustomModelEffect.m_CustomModelEffectInfo[i].Color[1], gCustomModelEffect.m_CustomModelEffectInfo[i].Color[2], Color);
			if (gCustomModelEffect.m_CustomModelEffectInfo[i].EffectIndex == 1)
			{
				sub_74CD30(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectType, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectScale, 0);
			} // 3}
			else if (gCustomModelEffect.m_CustomModelEffectInfo[i].EffectIndex == 2)
			{
				sub_6D9070(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectType, 0, 0, 0, 0, 0, 0.0, -1);
			}
			else
				pPlayStaticEffect(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (DWORD*)&lBone[i], gCustomModelEffect.m_CustomModelEffectInfo[i].EffectScale, Color, (int)&lBone2[i], 0, 0);
		}
	}
	for (int i = 0; i < MAX_MODEL_EFFECT; i++)
	{
		if (Object->ArmorSlot == ITEM2(gCustomModelEffect.m_CustomModelEffectInfo[i].ItemType, gCustomModelEffect.m_CustomModelEffectInfo[i].ItemIndex) &&
			Object->ArmorLevel >= gCustomModelEffect.m_CustomModelEffectInfo[i].MinLevel && Object->ArmorLevel <= gCustomModelEffect.m_CustomModelEffectInfo[i].MaxLevel &&
			Object->ArmorExcellent >= gCustomModelEffect.m_CustomModelEffectInfo[i].MinExcellent && Object->ArmorExcellent <= gCustomModelEffect.m_CustomModelEffectInfo[i].MaxExcellent)
		{
			lBone[i].Z = lBone[i].Z + (float)(120);
			lBone2[i].Z = lBone2[i].Z + (float)(120);
			Vector(gCustomModelEffect.m_CustomModelEffectInfo[i].Color[0], gCustomModelEffect.m_CustomModelEffectInfo[i].Color[1], gCustomModelEffect.m_CustomModelEffectInfo[i].Color[2], Color);
			if (gCustomModelEffect.m_CustomModelEffectInfo[i].EffectIndex == 1)
			{
				sub_74CD30(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectType, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectScale, 0);
			} // 3}
			else if (gCustomModelEffect.m_CustomModelEffectInfo[i].EffectIndex == 2)
			{
				sub_6D9070(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectType, 0, 0, 0, 0, 0, 0.0, -1);
			}
			else
				pPlayStaticEffect(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (DWORD*)&lBone[i], gCustomModelEffect.m_CustomModelEffectInfo[i].EffectScale, Color, (int)&lBone2[i], 0, 0);
		}
	}
	for (int i = 0; i < MAX_MODEL_EFFECT; i++)
	{

		if (Object->PantsSlot == ITEM2(gCustomModelEffect.m_CustomModelEffectInfo[i].ItemType, gCustomModelEffect.m_CustomModelEffectInfo[i].ItemIndex) &&
			Object->PantsLevel >= gCustomModelEffect.m_CustomModelEffectInfo[i].MinLevel && Object->PantsLevel <= gCustomModelEffect.m_CustomModelEffectInfo[i].MaxLevel &&
			Object->PantsExcellent >= gCustomModelEffect.m_CustomModelEffectInfo[i].MinExcellent && Object->PantsExcellent <= gCustomModelEffect.m_CustomModelEffectInfo[i].MaxExcellent)
		{
			lBone[i].Z = lBone[i].Z + (float)(60);
			lBone2[i].Z = lBone2[i].Z + (float)(60);
			Vector(gCustomModelEffect.m_CustomModelEffectInfo[i].Color[0], gCustomModelEffect.m_CustomModelEffectInfo[i].Color[1], gCustomModelEffect.m_CustomModelEffectInfo[i].Color[2], Color);
			if (gCustomModelEffect.m_CustomModelEffectInfo[i].EffectIndex == 1)
			{
				sub_74CD30(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectType, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectScale, 0);
			} // 3}
			else if (gCustomModelEffect.m_CustomModelEffectInfo[i].EffectIndex == 2)
			{
				sub_6D9070(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectType, 0, 0, 0, 0, 0, 0.0, -1);
			}
			else
				pPlayStaticEffect(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (DWORD*)&lBone[i], gCustomModelEffect.m_CustomModelEffectInfo[i].EffectScale, Color, (int)&lBone2[i], 0, 0);
		}
	}
	for (int i = 0; i < MAX_MODEL_EFFECT; i++)
		//QUANGKY
	{
		if (Object->BootsSlot == ITEM2(gCustomModelEffect.m_CustomModelEffectInfo[i].ItemType, gCustomModelEffect.m_CustomModelEffectInfo[i].ItemIndex) &&
			Object->BootsLevel >= gCustomModelEffect.m_CustomModelEffectInfo[i].MinLevel && Object->BootsLevel <= gCustomModelEffect.m_CustomModelEffectInfo[i].MaxLevel &&
			Object->BootsExcellent >= gCustomModelEffect.m_CustomModelEffectInfo[i].MinExcellent && Object->BootsExcellent <= gCustomModelEffect.m_CustomModelEffectInfo[i].MaxExcellent)
		{
			if (Object->WingsSlot >= 1)
			{
				if (Object->InSafeZone)
				{
					lBone[i].Z = lBone[i].Z + (float)(20);
					lBone2[i].Z = lBone2[i].Z + (float)(20);
				}
				else
					lBone[i].Z = lBone[i].Z + (float)(80);
				lBone2[i].Z = lBone2[i].Z + (float)(80);
			}
			else
			{
				lBone[i].Z = lBone[i].Z + (float)(20);
				lBone2[i].Z = lBone2[i].Z + (float)(20);
			}
			Vector(gCustomModelEffect.m_CustomModelEffectInfo[i].Color[0], gCustomModelEffect.m_CustomModelEffectInfo[i].Color[1], gCustomModelEffect.m_CustomModelEffectInfo[i].Color[2], Color);
			if (gCustomModelEffect.m_CustomModelEffectInfo[i].EffectIndex == 1)
			{
				sub_74CD30(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectType, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectScale, 0);
			} // 3}
			else if (gCustomModelEffect.m_CustomModelEffectInfo[i].EffectIndex == 2)
			{
				sub_6D9070(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectType, 0, 0, 0, 0, 0, 0.0, -1);
			}
			else
				pPlayStaticEffect(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (DWORD*)&lBone[i], gCustomModelEffect.m_CustomModelEffectInfo[i].EffectScale, Color, (int)&lBone2[i], 0, 0);
		}
	}
	pDrawViewPortEffects(ObjectPointer, ObjectModel, a3);
}

void CCopyEffect::Load()	
{
	SetCompleteHook(0xFF, 0x0040487D, &this->DrawViewPortEffects);
	SetCompleteHook(0xFF, 0x0048E56C, &this->DrawViewPortEffects);
	SetCompleteHook(0xFF, 0x0057D4FF, &this->DrawViewPortEffects);
	SetCompleteHook(0xFF, 0x0057D513, &this->DrawViewPortEffects);
}