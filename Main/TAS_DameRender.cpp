#include "stdafx.h"
#include "Interface.h"
#include "TAS_DameRender.h"
#include "User.h"
#include "Import.h"
#include "TMemory.h"
#include "Defines.h"
#include "PrintPlayer.h"
#include "Util.h"
#include "Common.h"
#if(DAMAGE_RENDER_ENABLE)
CDamageRender g_DamageRender;

CDamageRender::CDamageRender()
{
	this->Init();
	this->mINumberDmg = -1;
}

void CDamageRender::Init()
{
	memset(this->m_Data, 0, sizeof(this->m_Data));
}

void  RenderPoints(BYTE a1)
{
	float v1; // [esp+8h] [ebp-Ch]
	int* v2; // [esp+Ch] [ebp-8h]
	int i; // [esp+10h] [ebp-4h]
	int* byte_9772028 = (int*)0x9772028;
	EnableAlphaTest(1);
	((void(*)())0x00635E10)(); // Sửa lại: Thêm cặp ngoặc để gọi hàm
	for (i = 0; i < 100; ++i)
	{
		v2 = &byte_9772028[132 * i];
		if (!*v2)
			continue;
		if (a1 == 1)
		{
			if (*((float*)v2 + 7) > 350.0)
				continue;
		LABEL_13:
			v1 = *((float*)v2 + 20) * 0.4000000059604645;
			((void(__cdecl*)(int a1, int Value, int a3, float a4, float a5))0x006372D0)((int)(v2 + 20), *((DWORD*)v2 + 1), (int)(v2 + 32), v1, *((float*)v2 + 4));
			continue;
		}
		if (a1 == 2)
		{
			if (*((float*)v2 + 7) <= 300.0)
				continue;
			goto LABEL_13;
		}
		if (!v2[124] || *((float*)v2 + 32) < (double)*((float*)v2 + 7))
			goto LABEL_13;
	}
}
void CDamageRender::Load()
{
	pLoadImage("TAS\\TAS_DmgText.tga", eImgID_NUMBER_FONT_BIG2, 0x2601, 0x2901, 1, 0);
}

void CDamageRender::RunNumber(char a1)
{
	return;
}

void CDamageRender::DrawRender()
{
	int Count = 0;
	int LastY = 0;
	for (int i = 0; i < DAMAGE_RENDER_MAX; i++)
	{
		DAMAGE_INFO* pDamage = &this->m_Data[i];

		if (!pDamage->Active)
		{
			continue;
		}

		// =================================================================
		// >>> BẮT ĐẦU THAY ĐỔI LOGIC TỐC ĐỘ ANIMATION <<<
		// =================================================================

		// Tính toán thời gian đã trôi qua (tính bằng mili-giây)
		DWORD elapsedTime = GetTickCount() - pDamage->AnimationTick;

		// Quy đổi thời gian sang số khung hình animation với tốc độ 30 FPS
		// 1000ms / 30 FPS = ~33ms mỗi frame animation
		pDamage->AnimationNum = elapsedTime / 33;

		VAngle Angle = { 0 };
		int BPosX = 0;
		int BPosY = 0;
		float PosX = 0;
		float PosY = 0;
		int DevX = 20;
		int Wind = 70;
		Angle.X = pDamage->VAngle[0];
		Angle.Y = pDamage->VAngle[1];
		Angle.Z = pDamage->VAngle[2]; //Chieu Cao
		pGetPosFromAngle(&Angle, &BPosX, &BPosY);
		PosX = BPosX;
		PosY = BPosY;

		int div = 0;

		if (pDamage->AnimationNum == 0)
		{
			if (LastY == PosY)
			{
				div = pDamage->AnimationNum * 2;
			}
		}
		LastY = PosY;
		if (pDamage->DamageType == 0) // máu bị đánh
		{
			if (pDamage->AnimationNum < DAMAGE_AnimationNum)
			{
				PosY -= pDamage->AnimationNum * DAMAGE_RENDER_SPEED;
			}
			if (pDamage->DrawSize < 4.5)
			{
				pDamage->DrawSize += 1.55;
			}
		}

		if (pDamage->DamageType >= 10 && pDamage->DamageType <= 15)
		{

			if (pDamage->AnimationNum < DAMAGE_AnimationNum)
			{
				PosY -= pDamage->AnimationNum * 1;
			}
			if (pDamage->DrawSize < 2.5)
			{
				pDamage->DrawSize += 1.55;
			}
		}

		if (pDamage->DamageType == 1)//ignor // xuyên giáp
		{
			if (pDamage->AnimationNum < DAMAGE_AnimationNum)
			{
				PosY -= pDamage->AnimationNum * DAMAGE_RENDER_SPEED;
			}

			if (pDamage->DrawSize > 3.1)
			{
				pDamage->DrawSize -= 0.1;
			}
		}

		if (pDamage->DamageType == 2)//exe hoàn hảo
		{
			if (pDamage->AnimationNum < DAMAGE_AnimationNum)
			{
				PosY -= pDamage->AnimationNum * DAMAGE_RENDER_SPEED;
			}

			if (pDamage->DrawSize > 3.1)
			{
				pDamage->DrawSize -= 0.1;
			}
		}

		if (pDamage->DamageType == 3)//crit chí mạng
		{
			if (pDamage->AnimationNum < DAMAGE_AnimationNum)
			{
				PosY -= pDamage->AnimationNum * DAMAGE_RENDER_SPEED;
			}

			if (pDamage->DrawSize > 3.1)
			{
				pDamage->DrawSize -= 0.1;
			}
		}

		if (pDamage->DamageType == 4)//critstun//ref phản dame
		{
			if (pDamage->AnimationNum < DAMAGE_AnimationNum)
			{
				PosY -= pDamage->AnimationNum * DAMAGE_RENDER_SPEED;
			}

			if (pDamage->DrawSize < 2.5)
			{
				pDamage->DrawSize += 0.10;
			}
		}

		if (pDamage->DamageType == 5)//vamp//poison độc
		{
			if (pDamage->AnimationNum < DAMAGE_AnimationNum)
			{
				PosY -= pDamage->AnimationNum * DAMAGE_RENDER_SPEED;
			}

			if (pDamage->DrawSize < 2.5)
			{
				pDamage->DrawSize += 0.10;
			}
		}

		if (pDamage->DamageType == 6)//power crit 150
		{
			if (pDamage->AnimationNum < DAMAGE_AnimationNum)
			{
				PosY -= pDamage->AnimationNum * DAMAGE_RENDER_SPEED;
			}

			if (pDamage->DrawSize < 2.5)
			{
				pDamage->DrawSize += 0.10;
			}

		}

		if (pDamage->DamageType == 7)//crit300
		{
			if (pDamage->AnimationNum < DAMAGE_AnimationNum)
			{
				PosY -= pDamage->AnimationNum * DAMAGE_RENDER_SPEED;
			}

			if (pDamage->DrawSize < 2.5)
			{
				pDamage->DrawSize += 0.10;
			}
		}

		if (pDamage->DamageType > 7)
		{
			PosY -= pDamage->AnimationNum * DAMAGE_RENDER_SPEED;

			if (pDamage->AnimationNum > DAMAGE_AnimationNum)
			{
				PosX += pDamage->AnimationNum;
			}

			if (pDamage->DrawSize > 0.5)
			{
				pDamage->DrawSize -= 0.1;
			}
		}

		if (pDamage->DamageType == 128)
		{
			PosY -= pDamage->AnimationNum * 1;

			if (pDamage->DrawSize > 0.5)
			{
				pDamage->DrawSize -= 0.01;
			}
		}

		if (pDamage->DamageType == 64)
		{
			PosY -= pDamage->AnimationNum * 1;

			if (pDamage->DrawSize > 0.5)
			{
				pDamage->DrawSize -= 0.01;
			}
		}

		if (pDamage->DamageType == 15)//heal
		{
			PosY += pDamage->AnimationNum * 1;
			if (pDamage->AnimationNum < DAMAGE_AnimationNum)
			{
				PosY += pDamage->AnimationNum * DAMAGE_RENDER_SPEED;
			}

			if (pDamage->DrawSize < 2.5)
			{
				pDamage->DrawSize += 0.10;
			}

		}

		if (pDamage->DamageType == 16)//dark raven basik attack
		{
			PosY += pDamage->AnimationNum * DAMAGE_RENDER_SPEED;

			if (pDamage->DrawSize > 0.5)
			{
				pDamage->DrawSize -= 0.01;
			}
		}
		if (pDamage->DamageType == 17)//dark raven exe
		{
			if (pDamage->AnimationNum < DAMAGE_AnimationNum)
			{
				PosY -= pDamage->AnimationNum * DAMAGE_RENDER_SPEED;
			}

			if (pDamage->DrawSize < 2.5)
			{
				pDamage->DrawSize += 0.10;
			}
		}

		if (pDamage->DamageType == 18)//dark raven crit
		{
			if (pDamage->AnimationNum < DAMAGE_AnimationNum)
			{
				PosY -= pDamage->AnimationNum * DAMAGE_RENDER_SPEED;
			}

			if (pDamage->DrawSize < 2.5)
			{
				pDamage->DrawSize += 0.10;
			}
		}

		if (pDamage->DamageNumber > 1)
		{
			this->DrawDamage(PosX, PosY, pDamage->DamageColor, pDamage->DamageNumber, pDamage->DrawSize, pDamage->DamageType);
		}
		else
		{
			this->DrawMiss(PosX, PosY, pDamage->DamageColor, 0, pDamage->DrawSize);
		}

		//pDamage->AnimationNum++; // -> XÓA HOẶC VÔ HIỆU HÓA DÒNG NÀY
		Count++;

		if (pDamage->AnimationNum >= pDamage->AnimationMax)
		{
			pDamage->Active = 0;
		}
	}

	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
}
void CDamageRender::SetDmgTarget(vec3_t Position, vec3_t Color, int Type, float scale, QWORD Number)
{
	this->mINumberDmg = this->GetEmptyData();
	int iNumber = this->mINumberDmg;
	if (iNumber == -1)
	{
		return;
	}

	DAMAGE_INFO* pDamage = &this->m_Data[iNumber];

	pDamage->Active = 1;
	pDamage->DamageType = Type;

	pDamage->DrawX = 0;
	pDamage->DrawY = 0;

	if (pDamage->DamageType == 128)
	{
		pDamage->DrawSize = 3.0;
	}
	else if (pDamage->DamageType == 64)
	{
		pDamage->DrawSize = 3.0;
	}
	else if (pDamage->DamageType == 7)
	{
		pDamage->DrawSize = 3.0;
	}
	else if (pDamage->DamageType == 6)
	{
		pDamage->DrawSize = 3.0;
	}
	else if (pDamage->DamageType == 5)
	{
		pDamage->DrawSize = 2.0;
	}
	else if (pDamage->DamageType == 15)//heal
	{
		pDamage->DrawSize = 0.7;
	}
	else if (pDamage->DamageType == 32 || pDamage->DamageType == 16)
	{
		pDamage->DrawSize = 3.0;
	}

	else if (pDamage->DamageType == 2 || pDamage->DamageType == 3)
	{
		pDamage->DrawSize = 10.0;
	}
	else if (pDamage->DamageType == 1)
	{
		pDamage->DrawSize = 12.0;
	}

	else
	{
		pDamage->DrawSize = 2.7;
	}
	pDamage->DamageNumber = Number;
	Vector(Position[0], Position[1], Position[2], pDamage->VAngle);
	Vector(Color[0], Color[1], Color[2], pDamage->DamageColor);

	pDamage->AnimationNum = 0;
	pDamage->AnimationMax = DAMAGE_AnimationNum;
	pDamage->AnimationTick = GetTickCount(); // -> THÊM DÒNG NÀY ĐỂ KHỞI TẠO THỜI GIAN
}


int CDamageRender::GetEmptyData()
{
	int Result = -1;
	int Count = 0;

	for (int i = 0; i < DAMAGE_RENDER_MAX; i++)
	{
		if (!this->m_Data[i].Active)
		{
			Result = i;
			break;
		}
	}
	return Result;
}

int CDamageRender::GetObjectIndex(int aTargetIndex)
{
	int Result = -1;

	for (int i = 0; i < 400; i++)
	{
		lpViewObj lpObj = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), i);

		if (!lpObj || !lpObj->m_Model.Unknown4)
		{
			continue;
		}

		if (lpObj->aIndex != aTargetIndex)
		{
			continue;
		}

		Result = i;

		break;
	}

	return Result;
}
void CDamageRender::DrawTextTypeDmg(float PlusSize, int PosX, int PosY, int TypeDmg)		//khoang cach di chuyen chu chi mang, hoan hoan, xuyen giap
{
	float TWidth = TEXT_DMG_W * PlusSize;
	float THeight = TEXT_DMG_H * PlusSize;

	switch (TypeDmg)
	{
	case 1: //Dmg Xuyen Giap
	{
		PosX += 2;
		RenderBitmap(eImgID_NUMBER_FONT_BIG2, PosX - (TWidth * 0.7f), PosY - 2, TWidth, THeight, 0.f, 0.f, 1.0, 64.f / 256.f, 1, 1, 0);
	}
	break;
	case 2: //Dmg Hoan Hao
	{
		PosX += 3;
		RenderBitmap(eImgID_NUMBER_FONT_BIG2, PosX - (TWidth * 0.7f), PosY - 2, TWidth, THeight, 0.f, (64.f / 256.f) * 2, 1.0, 64.f / 256.f, 1, 1, 0);
	}
	break;
	case 3: //Chi Mang
	{
		PosX += 3;
		RenderBitmap(eImgID_NUMBER_FONT_BIG2, PosX - (TWidth * 0.7f), PosY - 2, TWidth, THeight, 0.f, (64.f / 256.f) * 1, 1.0, 64.f / 256.f, 1, 1, 0);
	}
	break;
	default:
		break;
	}
	if ((int)(TypeDmg) >= 10) //Nguyen To
	{
		RenderBitmap(eImgID_NUMBER_FONT_BIG2, PosX - (TWidth * 0.7f), PosY - 2, TWidth, THeight, 0.f, (64.f / 256.f) * 3, 1.0, 64.f / 256.f, 1, 1, 0);
	}
}
void CDamageRender::DrawDamage(float PosX, float PosY, vec3_t Color, QWORD Number, float PlusSize, int TypeDmg)
{
	QWORD iNum = Number;
	QWORD iArr[32] = { 0 };
	int iCount = 0;

	while (iNum != 0)
	{
		iArr[iCount] = iNum % 10;
		iNum = iNum / 10;
		iCount++;
	}
	float Width = NUM_DMG_W * PlusSize;
	float Height = NUM_DMG_H * PlusSize;

	PosX += Width * iCount / 2;
	PosY -= 40;

	pSetBlend(true);
	glColor3f(Color[0], Color[1], Color[2]);//	

	for (int i = 0; i < iCount; i++)
	{
		float u = iArr[i] * 16.f / 256.f;
		RenderBitmap(30003, PosX, PosY, Width, Height, u, 0.f, 16.f / 256.f, 17.0f / 32.f, 1, 1, 0);
		PosX -= Width * 0.8f;
	}
	CDamageRender::DrawTextTypeDmg(PlusSize, PosX, PosY, TypeDmg);
	pSetBlend(false);
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
}

void CDamageRender::DrawMiss(float PosX, float PosY, vec3_t Color, QWORD Number, float PlusSize)
{
	pSetBlend(true);
	glColor3f(Color[0], Color[1], Color[2]);//	
	RenderBitmap(30003, PosX, PosY, 30, 15, 0.0, 0.6, 0.2, 0.5, 1, 1, 0.0);//  chuan miss
	pSetBlend(false);
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
}
#endif