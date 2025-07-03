#pragma once
#define pDrawViewPortEffects	((int(__cdecl*)(DWORD ObjectPointer, DWORD ModelPointer, int a3)) 0x56F210)
#define sub_6D9070				((void(__cdecl*)(int a1, int a2, int a3, float * a4, int a5, int a6, __int16 a7, __int16 a8, __int16 a9, __int16 a10, float a11, __int16 a12)) 0x6D8F20)
#define sub_74CD30				((int(__cdecl*)(int a1, int a2, int a3, vec3_t a4, int a5, float a6, int a7)) 0x74CBE0)
class CCopyEffect
{
public:
	CCopyEffect();
	virtual ~CCopyEffect();
	void Load();
	static void DrawViewPortEffects(DWORD ObjectPointer, DWORD ModelPointer, DWORD a3);
};

extern CCopyEffect gCopyEffect;