#pragma once

#include "stdafx.h"
#include "Protocol.h"
#include "Util.h"
#include "Defines.h"
#include "Import.h"
#include "Main.h"

#if(HT_THUE_FLAG)

class CFlagEquip
{
	public:
	int count;
	void Load();
}; 
extern CFlagEquip Flag;

#endif

#define sub_9CEA6C				((void (__cdecl*)(int thisa, LPVOID lpMem)) 0x009CEA6C)
#define CSIPartsMDL				((float *(__thiscall*)(float*a1, int a4, int a5, int a6, float a7, float a8, float a9)) 0x004F0730)
#define CSParts2D				((float *(__thiscall*)(float * thisa, int a4, int a5, char a6, float a7, float a8, float a9, float a10, float a11, float a12)) 0x004EFFF0)
#define Operator_new			((float *(__cdecl*)(unsigned int a4)) 0x009D00C5)
#define CreatePartsFactory		((int (__cdecl*)(int a1)) 0x004EF9A0)
#define sub_4EFF70				((int (__cdecl*)(int thisa)) 0x004EFF70)

