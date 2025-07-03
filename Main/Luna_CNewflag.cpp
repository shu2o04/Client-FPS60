#include "StdAfx.h"
#if(HT_THUE_FLAG)
#include "Luna_CNewFlag.h"
#include "CustomRankUser.h"
#include "Interface.h"
#include "WindowsStruct.h"
#include "User.h"
#include "Common.h"
#include "ThueFlag.h"
#include "CustomModelFlag.h"

CFlagEquip Flag;

int HoolCreateManyFlay(int thisa)
{
	int v5; // ST48_4@11
	float* v15; // [sp+38h] [bp-5Ch]@13
	float* v24; // [sp+80h] [bp-14h]@12

	v5 = 1;
	int FlagID = gCustomRankUser.m_Data[*(WORD*)(thisa + 126)].m_RankTitle6 - 1;
	v5 = (FlagID != -1) ? 1 : 0;

	if (v5 == 0 && *(DWORD*)(thisa + 764))
	{
		sub_9CEA6C(thisa, *(LPVOID*)(thisa + 764));
		*(DWORD*)(thisa + 764) = 0;
	}
	if (DisableFlag == 0)
	{
		if (!*(DWORD*)(thisa + 764) && v5 == 1 && gCustomModelFlag.CheckFlagModelIsLoad(gProtect.m_MainInfo.m_mModelFlagData[FlagID].ModelIndex))
		{
			v24 = (float*)Operator_new(0x29Cu);
			if (v24)
			{
				v15 = CSParts2D(v24, gProtect.m_MainInfo.m_mModelFlagData[FlagID].ModelIndex + 1171, 20, 0, -45.0, -5.0, -0.0, 0.0, 0.0, 1);
			}
			else
			{
				v15 = 0;
			}
			*(DWORD*)(thisa + 764) = (DWORD)v15;
		}
	}
	return CreatePartsFactory(thisa);

}
void CFlagEquip::Load()
{
	SetCompleteHook(0xE8, 0x00588511, &HoolCreateManyFlay);
}
#endif