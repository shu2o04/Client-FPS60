#ifndef _Config_H
#define _Config_H
#define MAX_RANGE_TEXT 322
#define MAX_RANGE_TOGGLE 10
#define MAX_RANGE_TMC 20
#define MAX_RANGE_MENU 41
class cConfig
{
	public:
	void Load();
	#if(TEXTVN_NEW)
	char MenuGame_TextVN[MAX_RANGE_MENU][120];
	char ToggleAuto_TextVN[MAX_RANGE_TOGGLE][120];
	char TextVN_ThanMaChien[MAX_RANGE_TMC][120];
	char TTAS_TEXT_ENGINE[MAX_RANGE_TEXT][120];
	char TTAS_TEXT_HD[30][350];
	#endif
};

extern cConfig gConfig;
#endif