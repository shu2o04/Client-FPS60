#pragma once

#define MAX_CUSTOM_ITEM 2000

struct CUSTOM_ITEM_INFO
{
	int Index;
	int ItemIndex;
	int ColorR;
	int ColorG;
	int ColorB;
	char ModelName[32];
};

class CCustomItem
{
	public:
	CCustomItem();
	void Load(CUSTOM_ITEM_INFO* info);
	CUSTOM_ITEM_INFO* GetInfoByItem(int ItemIndex);
	BOOL GetCustomItemColor(int ItemIndex,float* ItemColor);
	int IsCustomItem(int ItemIndex);
	std::map<int, CUSTOM_ITEM_INFO> m_CustomItemInfo;
};

extern CCustomItem gCustomItem;
