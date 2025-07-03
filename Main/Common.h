#pragma once

#define Offset_CreateFontA1 0x004060D0
#define Offset_CreateFontA2 0x004D2882
#define Offset_CreateFontA3    0x004D28EB
#define Offset_CreateFontA4 0x004D2957
#define Offset_CreateFontA5 0x004D29C1

void InitCommon();
BOOL CheckIsLuckyItem(int ItemID);
BOOL CheckGensBattleMap(int map);
BOOL CheckGensMoveIndex(int idx);
void LoginTab();
void CheckMasterLevel();
void CompareGensMoveIndex();
void DrawEffectsPic(int &EffectID, float StartX, float StartY, float StartWidth, float StartHeight );
char FixHelperMouseClick(int a1); //ANTIHACK DUPE

extern BYTE GensBattleMapCount;
extern BYTE GensMoveIndexCount;
extern BYTE GensBattleMap[120];
extern BYTE GensMoveIndex[120];

extern int DisableStaticEffect;
extern int DisableDynamicEffect;
extern int DisableSkillEffect;
extern int DisableGlowEffect;
extern int DisableObject;
extern int DisableShadow;
extern int Anisotropy;
extern int MaxAnisotropy;
extern int Linear;
extern int Tron;
extern int Fog;
extern int MiniMap;
extern int MyNameOn;
extern int HideEffect;
extern int HienMauQuai;
extern int HienTenMem;
extern int SeparateChat;
extern int TimerBar;
extern int HpMonsterBar;
extern int HPMonsterName;
extern int HPMonster;
extern int PVPAttack;
extern char Main_Font_Name[100];
extern int Main_Font_Bold;
extern int Main_Font_Height;
extern int Main_Font_Italic;
extern int Main_Font_Unicode;
extern int Main_Font_Width;
extern int Main_Font_Underline;
extern int Main_Font_Quality;
extern int Main_Font_StrikeOut;
extern int SellPostColor;
extern int offhelper;
extern int OpenSwicthSkill;
extern int SkillPage;
extern int FontON;
extern int FontHeight;
#if FPS_OPTION
extern int ChangeFps;
#endif
extern int WIDESCREEN;
extern int SCALEITEM;

extern int ChangeResolution;
#if(HT_THUE_FLAG)
extern int DisableFlag;
#endif