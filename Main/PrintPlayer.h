#pragma once
#include "Object.h"
#define GET_MAX_WORD_VALUE(x) (((x)>65000)?65000:((WORD)(x)))
//add fix mau dua len tren
#define pDrawBar ((double(__cdecl*)(float a1, float a2, int a3, float a4)) 0x791000)
//static void DrawHp(float a1, float a2, int a3, float a4);
static void DrawMp(float a1, float a2, int a3, float a4);
void InitPrintPlayer();
#if(DAMAGE_RENDER_ENABLE)
void PrintDamageOnScreenHP(vec3_t Position, DWORD Value, vec3_t Color, float scale, bool bMove);
void PrintDamageOnScreenSD(vec3_t Position, DWORD Value, vec3_t Color, float scale, bool bMove);
void PrintDamageOnScreenRF(vec3_t Position, DWORD Value, vec3_t Color, float scale, bool bMove);
#else
void PrintDamageOnScreenHP(DWORD a, DWORD b, DWORD c, DWORD d, DWORD e, DWORD f);
void PrintDamageOnScreenSD(DWORD a, DWORD b, DWORD c, DWORD d, DWORD e, DWORD f);
void PrintDamageOnScreenRF(DWORD a, DWORD b, DWORD c, DWORD d, DWORD e, DWORD f);
#endif
void PrintTextReplace(DWORD* value,DWORD type);
void PrintFixStatPoint(DWORD type);
void GetViewPhisyDamage(DWORD* DamageMin,DWORD* DamageMax);
void GetViewSkillDamage(DWORD* DamageMin,DWORD* DamageMax);
void GetViewMagicDamage(DWORD* DamageMin,DWORD* DamageMax);
void GetViewMagicDamage(DWORD* DamageMin,DWORD* DamageMax,DWORD* DamageRate);
void GetViewCurseDamage(DWORD* DamageMin,DWORD* DamageMax);
void GetViewCurseDamage(DWORD* DamageMin,DWORD* DamageMax,DWORD* DamageRate);
void GetViewDarkSpiritDamage(DWORD* DamageMin,DWORD* DamageMax);
void GetViewDarkHorseDamage(DWORD* DamageMin,DWORD* DamageMax);
void PrintPlayerLevel1();
void PrintPlayerLevel2();
void PrintPlayerViewHP1();
void PrintPlayerViewHP2();
void PrintPlayerViewMP1();
void PrintPlayerViewMP2();
void PrintPlayerViewBP1();
void PrintPlayerViewBP2();
void PrintPlayerViewSD1();
void PrintPlayerViewSD2();
void PrintPlayerViewLevelUpExperience1();
void PrintPlayerViewLevelUpExperience2();
void PrintPlayerViewLevelUpMasterExperience1();
void PrintPlayerViewLevelUpMasterExperience2();
void PrintPlayerViewText();
void PrintPlayerSetAttackSpeed();
void PrintPlayerGetSkillMagicDamage();
void PrintPlayerGetSkillPhysiDamage();
void PrintPlayerViewStrength();
void PrintPlayerViewDexterity();
void PrintPlayerViewVitality();
void PrintPlayerViewEnergy();
void PrintPlayerViewLeadership();

#if BAUCUA
extern int hotkq1;
extern int hotkq2;
extern int hotkq3;
extern int tongtrathuong;
#endif

extern DWORD ObjectDir;

extern DWORD ViewIndex;
extern DWORD ViewReset;
extern DWORD ViewValue;
extern DWORD ViewPoint;
extern DWORD ViewCurHP;
extern DWORD ViewMaxHP;
extern DWORD ViewCurMP;
extern DWORD ViewMaxMP;
extern DWORD ViewCurBP;
extern DWORD ViewMaxBP;
extern DWORD ViewCurSD;
extern DWORD ViewMaxSD;
extern DWORD ViewDamageHP;
extern DWORD ViewDamageSD;
extern DWORD ViewDamageTable[4];
extern DWORD ViewDamageCount;
extern DWORD ViewDamageValue;
extern DWORD ViewExperience;
extern DWORD ViewNextExperience;
extern QWORD ViewMasterExperience;
extern QWORD ViewMasterNextExperience;
extern DWORD ViewStrength;
extern DWORD ViewDexterity;
extern DWORD ViewVitality;
extern DWORD ViewEnergy;
extern DWORD ViewLeadership;
extern DWORD ViewAddStrength;
extern DWORD ViewAddDexterity;
extern DWORD ViewAddVitality;
extern DWORD ViewAddEnergy;
extern DWORD ViewAddLeadership;
extern DWORD ViewPhysiDamageMin;
extern DWORD ViewPhysiDamageMax;
extern DWORD ViewMagicDamageMin;
extern DWORD ViewMagicDamageMax;
extern DWORD ViewCurseDamageMin;
extern DWORD ViewCurseDamageMax;
extern DWORD ViewMulPhysiDamage;
extern DWORD ViewDivPhysiDamage;
extern DWORD ViewMulMagicDamage;
extern DWORD ViewDivMagicDamage;
extern DWORD ViewMulCurseDamage;
extern DWORD ViewDivCurseDamage;
extern DWORD ViewMagicDamageRate;
extern DWORD ViewCurseDamageRate;
extern DWORD ViewPhysiSpeed;
extern DWORD ViewMagicSpeed;
extern DWORD ViewAttackSuccessRate;
extern DWORD ViewAttackSuccessRatePvP;
extern DWORD ViewDefense;
extern DWORD ViewDefenseSuccessRate;
extern DWORD ViewDefenseSuccessRatePvP;
extern DWORD ViewDamageMultiplier;
extern DWORD ViewRFDamageMultiplierA;
extern DWORD ViewRFDamageMultiplierB;
extern DWORD ViewRFDamageMultiplierC;
extern DWORD ViewDarkSpiritAttackDamageMin;
extern DWORD ViewDarkSpiritAttackDamageMax;
extern DWORD ViewDarkSpiritAttackSpeed;
extern DWORD ViewDarkSpiritAttackSuccessRate;
extern DWORD ViewSkillMagicDamage;
extern int Coin1;
extern int Coin2;
extern int Coin3;
extern int Ruud;
extern int CoinAtm;
#if(CTCMINI)
extern BYTE CheckVaoLanhDia;
extern int	CTCMINI_TimeCTCMini;
extern BYTE CTCMINI_Cong[3];
extern BYTE CTCMINI_Tru[3];
extern char CTCMINI_GNameTru1[9];
extern char CTCMINI_GNameTru2[9];
extern char CTCMINI_GNameTru3[9];
#endif
extern DWORD ViewDamageTYPE;
#if ADD_POINT
extern DWORD ViewAccountLevel;
#endif