#pragma once

#define MAX_MAIN_VIEWPORT 400

struct NEW_HEALTH_BAR
{
	WORD index;
	BYTE type;
	BYTE rate;
	BYTE rate2;
	short Level;
	float Life;
	WORD MonsID;
};

void ClearNewHealthBar();
void InsertNewHealthBar(WORD index,BYTE type,BYTE rate,BYTE rate2,short Level, float Life, WORD MonsID);
NEW_HEALTH_BAR* GetNewHealthBar(WORD index,BYTE type);
void DrawNewHealthBar();
