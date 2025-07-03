#pragma once
#include "Protocol.h"
#include <vector>
#include "Object.h"

struct BI_Data
{
	short	Index;
	char	Level;
	BYTE	Max;
};

struct PMSG_BUNDLE_ITEM_INFO_HEADER_RECV
{
	PSWMSG_HEAD header; // C3:F3:03
	DWORD Count;
};

struct PMSG_ITEM_MODIFY_RECV
{
	PSBMSG_HEAD header; // C1:F3:14
	BYTE slot;
	BYTE ItemInfo[12];
	BYTE mode; //custom
};

class cBundleItem
{
public:
	cBundleItem();
	void Init();
	void Hook();
	bool CanMakeBundleItem(lpItemObj pPickItem, lpItemObj pTargetItem);
	bool IsBundleItem(DWORD index);
	bool CheckBundleItemUnmix(WORD index, BYTE Level, int dur);
	void GCBundleItemConfigRecv(BYTE* lpMsg);
	int  ReceiveModifyItemMode(BYTE* lpMsg);

public:
	std::vector<BI_Data> m_List;
};

extern cBundleItem BundleItem;