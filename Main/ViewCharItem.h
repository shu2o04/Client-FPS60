#pragma once
#include "Protocol.h"
#include "Object.h"

#define VIEWCHARITEMS TRUE
#if(VIEWCHARITEMS)
#define INVENTORY_ITEMS		12

#define sub_637E80					((void(__cdecl*)(int x, float y, float w, float h, float giro, float a9, float a10, float a11, float a12, float a13))0x00637E80)
#define pSetItemOption				((void(__cdecl*)(ObjectItem * lpItem, BYTE Option, BYTE Special, BYTE Value)) 0x58B910)

struct CharItems
{
	BYTE Result;
	char Guild[9];
	char Name[11];
	ObjectItem Item[INVENTORY_ITEMS];
};

class cViewCharItems
{
	public:
	cViewCharItems();
	void Init();
	void ClearSession();
	bool DrawCharInfo();
	bool getState() { return this->onView; }
	void setState(bool a1) { this->onView = a1; }
	bool IsWorkZone(WORD, WORD, WORD, WORD);
	BOOL DrawItem3DCenterImage;
	CharItems charItem;
	bool onView;
	bool DangXem;
	DWORD ActionTime;
private:
	float Rot;
	float Zoom;
	float guiX;
	float guiY;
	short curX;
	short curY;

	bool  dragging;
	int Key;
};

extern cViewCharItems ViewCharItems;
#endif

