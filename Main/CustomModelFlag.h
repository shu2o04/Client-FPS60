#pragma once
#include "Object.h"
#define MAX_MODEL_FLAG 50
#define CSGetObjectA			((char * (__thiscall*)(int *This)) 0x00588B90)
#define BMDPlayAnimation					((char(__thiscall*)(int This, int a2, int a3, int a4, float a5, int a6, int a7)) 0x545180)

#if(HT_THUE_FLAG)
struct MODEL_FLAG
{
	int Index;
	int ModelIndex;
	char ModelName[99];
	float ScaleView;
	float AnimationSpeed;
};

struct JPG_FLAG
{
	int Index;
	int ImgIndex;
	char ImgName[99];
	float ScaleX;
	float ScaleY;
};

class CustomModelFlag
{
	public:
	CustomModelFlag();
	void SetInfo(MODEL_FLAG* info);
	void SetInfoJPG(JPG_FLAG* info);
	bool CheckFlag(int ItemIndex);
	std::map<int, MODEL_FLAG> mModelFlagData;
	std::map<int, JPG_FLAG> mJPGFlagData;
	void RenderEffectJPG(ObjectPreview* ObjectPointer, int ImgIndex);
	void RenderEffectBMD(int This, int BMDIndex, float* CacheBMD);
	void BIRender(int* This, int* a2);
	bool CustomModelFlag::CheckFlagModelIsLoad(int BMDIndex);
};

extern CustomModelFlag gCustomModelFlag;
#endif