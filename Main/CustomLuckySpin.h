#pragma once

#include "Interface.h"
#include <vector>

#if(VONGQUAY_NEW)
#define MAX_ITEM_SPIN 12
#define SET_ITEMOPT_LEVEL(x)		(x << 3)
struct LuckySpin_Data
{
	int ItemType;
	int ItemIndex;
	int ItemLevel;
	int ItemSkill;
	int ItemLuck;
	int ItemOption;
	int ItemExc;
	int ItemTime;
};

struct GC_LuckySpin_Data
{
	PSBMSG_HEAD h;
	int ItemType;
	int ItemIndex;
	int ItemLevel;
	int ItemSkill;
	int ItemLuck;
	int ItemOption;
	int ItemExc;
	int ItemTime;
	int WCoinC;
};

struct GC_LuckySpinInit
{
	PSBMSG_HEAD h;
	bool result;
};

struct CG_LUCKYSPIN_REQ
{
	PSBMSG_HEAD	h;
};

struct GC_LuckySpinUpdateData
{
	PSBMSG_HEAD header; // C1:F3:E3
	int	RollNumber;
};

class CLuckySpin
{
	public:
	CLuckySpin();
	void SwitchLuckySpinWindowState();
	void CGLuckySpinSend();
	void GCLuckySpinInit(GC_LuckySpinInit* aRecv);
	void GCItemSend(GC_LuckySpin_Data* aRecv);
	void LuckySpinData(GC_LuckySpinUpdateData * aRecv);
	void Draw();
	void EventWindow_Main(DWORD Event);
	std::vector<LuckySpin_Data> itemdata;
	DWORD StartRoll;
	int RollNumber;
	int WCoinC;
	BYTE RandThis;
};
extern CLuckySpin gLuckySpin;
#endif