#include "StdAfx.h"
#include "Config.h"
#include "Util.h"
#include <stdlib.h>
#include "windows.h"
#include "atlstr.h"
#include "Protect.h"

cConfig gConfig;
void cConfig::Load()
{	
	for (int Menu = 0; Menu < MAX_RANGE_MENU; Menu++)
	{
		char section[50], key[50];
		sprintf_s(section, "MenuGame");
		sprintf_s(key, "MenuGame%0d", Menu);
		GetPrivateProfileStringA(section, key, "Null", MenuGame_TextVN[Menu], sizeof(MenuGame_TextVN[Menu]), MENU_GAME_FILE);
	}	
	for (int Key1 = 0; Key1 < MAX_RANGE_TOGGLE; Key1++)
	{
		char section[50], key[50];
		sprintf_s(section, "ToggleAuto");
		sprintf_s(key, "ToggleAuto%0d", Key1);
		GetPrivateProfileStringA(section, key, "Null", ToggleAuto_TextVN[Key1], sizeof(ToggleAuto_TextVN[Key1]), MENU_GAME_FILE);
	}
	#if(THANMA)	
	for (int ST = 0; ST < MAX_RANGE_TMC; ST++)
	{
		char section[250], key[250];
		sprintf_s(section, "TextVN_EventThanMa");
		sprintf_s(key, "Text%d", ST);
		GetPrivateProfileStringA(section, key, "Null", TextVN_ThanMaChien[ST], sizeof(TextVN_ThanMaChien[ST]), MENU_GAME_FILE);
	}
	#endif
	for (int Lang = 0; Lang < MAX_RANGE_TEXT; Lang++)
	{
		char section[MAX_RANGE_TEXT], key[MAX_RANGE_TEXT];
		sprintf_s(section, "TAS_TEXT");
		sprintf_s(key, "TAS_TEXT_%d", Lang);
		GetPrivateProfileStringA(section, key, "Null", TTAS_TEXT_ENGINE[Lang], sizeof(TTAS_TEXT_ENGINE[Lang]), MENU_GAME_FILE);
	}

	for (int Lang = 0; Lang < 30; Lang++)
	{
		char section[30], key[30];
		sprintf_s(section, "TEXT_HD");
		sprintf_s(key, "TEXT_%02d", Lang);
		GetPrivateProfileStringA(section, key, "Null", TTAS_TEXT_HD[Lang], sizeof(TTAS_TEXT_HD[Lang]), MENU_GAME_FILE);
	}
}