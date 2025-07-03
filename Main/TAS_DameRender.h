#pragma once

#include "Protocol.h"
#if(DAMAGE_RENDER_ENABLE)

#define DAMAGE_RENDER_DEBUG			1
#define DAMAGE_RENDER_VERSION		1
#define DAMAGE_RENDER_MAX			1000
#define DAMAGE_AnimationNum			20//
#define eImgID_NUMBER_FONT_BIG2		2333339
#define DAMAGE_RENDER_SPEED			3.8 //Toc Do Frame
#define FloatPoint					1.5
//===Size Number DMG
#define NUM_DMG_W					3/FloatPoint
#define NUM_DMG_H					4/FloatPoint
#define TEXT_DMG_W					8/FloatPoint
#define TEXT_DMG_H					4/FloatPoint


#define RGBTOGLFLOAT(x) ((float)x/255.0f)
#define FLOATTORGB(x)	((float)x*255)
#define ABS(x) (((x) < 0) ? (-(x)) : (x))


#define pDrawGUFULL				((int(__cdecl*)(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)) 0x637C60)

struct DAMAGE_INFO
{
	int Active;
	//WORD TargetIndex;
	int DamageType;
	vec3_t DamageColor;
	QWORD DamageNumber;
	int DrawX;
	int DrawY;
	float DrawSize;
	float AnimationNum;
	float AnimationMax;
	vec3_t VAngle;
	DWORD   AnimationTick;
};

class CDamageRender
{
public:
	CDamageRender();

	void Init();
	void Load();
	static void RunNumber(char a1);
	void DrawRender();
	int GetEmptyData();
	int GetObjectIndex(int aTargetIndex);
	void DrawDamage(float PosX, float PosY, vec3_t Color, QWORD Number, float PlusSize, int TypeDmg);
	void DrawMiss(float PosX, float PosY, vec3_t Color, QWORD Number, float PlusSize);
	DAMAGE_INFO	m_Data[DAMAGE_RENDER_MAX];
	int mINumberDmg;
	void SetDmgTarget(vec3_t Position, vec3_t Color, int Type, float scale, QWORD Number);
	void CDamageRender::DrawTextTypeDmg(float PlusSize, int PosX, int PosY, int TypeDmg);

};

extern CDamageRender g_DamageRender;

#endif