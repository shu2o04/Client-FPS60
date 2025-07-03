#include "StdAfx.h"
#include "Import.h"
#include "zzzmathlib.h"
#include "Util.h"
#include "Object.h"
#include "Defines.h"
#include "CustomPet.h"
#include "CustomEarthQuakeSkill.h"

cCEarthQuake gCustomEarthQuake;

cCEarthQuake::cCEarthQuake() {
	this->m_EarthQuake.clear();
}
cCEarthQuake::~cCEarthQuake()
{
}

void cCEarthQuake::Load(HORSE_EARTH_QUAKE* info) {
	for (int n = 0; n < MAX_EARTH_QUAKE; n++) {
		if (info[n].Index < 0 || info[n].Index >= MAX_EARTH_QUAKE) {
			return;
		}
		this->m_EarthQuake.push_back(info[n]);
	}
}

void RenderDarkHorseSkill(lpModelObj1 lpObjModel, lpViewObj lpObj) {
	if (lpObjModel && lpObj) {
		vec3_t Color;
		++lpObjModel->OnAttacking;
		if (!(pMoveSceneFrame % 10))
			for (std::vector<HORSE_EARTH_QUAKE>::iterator it = gCustomEarthQuake.m_EarthQuake.begin(); it != gCustomEarthQuake.m_EarthQuake.end(); it++) {
				if (it->ItemIndex == (*(DWORD*)((int)lpObjModel + 48) - 1171)) {
					Color[0] = it->ColorR;
					Color[1] = it->ColorG;
					Color[2] = it->ColorB;
					if (it->UseRGB == 1) {
						pCreateEffect2(it->EffectCode, &lpObjModel->VecPosX, &lpObjModel->WorldPos.X, Color, it->EffectSize, 0, -1, 0, 0, 0, 0.0, -1);
					}
					else {
						pCreateEffect2(it->EffectCode, &lpObjModel->VecPosX, &lpObjModel->WorldPos.X, &lpObjModel->ColorR, it->EffectSize, 0, -1, 0, 0, 0, 0.0, -1);
					}
				}
				
			}
		if (lpObjModel->CoordX < 8.0 || lpObjModel->CoordX > 9.5) {
			if (lpObjModel->OnAttacking == 19) {
				for (std::vector<HORSE_EARTH_QUAKE>::iterator it = gCustomEarthQuake.m_EarthQuake.begin(); it != gCustomEarthQuake.m_EarthQuake.end(); it++) {
					if (it->ItemIndex == (*(DWORD*)((int)lpObjModel + 48) - 1171)) {
						pCreateEffect2(it->SkillEarthQuake1, &lpObjModel->VecPosX, &lpObjModel->WorldPos.X, &lpObjModel->ColorR, 0, (int)lpObjModel, -1, 0, 2, 0, 0.0, -1);
					}
					
				}
				lpObjModel->OnAttacking = -3;
			}
		}
		else {
			for (std::vector<HORSE_EARTH_QUAKE>::iterator it = gCustomEarthQuake.m_EarthQuake.begin(); it != gCustomEarthQuake.m_EarthQuake.end(); it++) {
				if (lpObjModel->OnAttacking % 2 == 1) {
					vec3_t WorldPos;
					vec3_t AnglePos;
					Vector(0.0, (double)(lpObjModel->OnAttacking / 2) * 150.0, 0.0, WorldPos);
					Vector(0.0, 0.0, (double)(rand() % 360), AnglePos);
					vec34_t Matrix;
					vec3_t ResultPosition;
					for (int i = 0; i < 6; ++i) {
						AnglePos[2] += 60;
						pAngleMatrix2(AnglePos, Matrix);
						pVectorRotate2(WorldPos, Matrix, ResultPosition);
						ResultPosition[0] += lpObjModel->VecPosX;
						ResultPosition[1] += lpObjModel->VecPosY;
						ResultPosition[2] += lpObjModel->VecPosZ;
						if (it->ItemIndex == (*(DWORD*)((int)lpObjModel + 48) - 1171)) {
							pCreateEffect2(it->SkillEarthQuake2, ResultPosition, &lpObjModel->WorldPos.X, &lpObjModel->ColorR, 0, 0, -1, 0, 0, 0, 0.0, -1);
						}
						
					}
					pEarthQuake = (double)(rand() % 3 - 3) * 0.699999988079071;
				}
			}
		}
	}
}

void cCEarthQuake::LoadRenderSkill() {
	MemorySet(0x00502A95, 0x90, 0x5);
	SetCompleteHook(0xE8, 0x00502A95, &RenderDarkHorseSkill);
}