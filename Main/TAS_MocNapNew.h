#pragma once
#define TAS_ITEM_KHIENG mDataListItemMocNapClient.ListItemMocNap[n].GetTypeItem == 6
#define TAS_ITEM_MU mDataListItemMocNapClient.ListItemMocNap[n].GetTypeItem == 7
#define TAS_ITEM_AO mDataListItemMocNapClient.ListItemMocNap[n].GetTypeItem == 8
#define TAS_ITEM_QUAN mDataListItemMocNapClient.ListItemMocNap[n].GetTypeItem == 9
#define TAS_ITEM_GANG mDataListItemMocNapClient.ListItemMocNap[n].GetTypeItem == 10
#define TAS_ITEM_GIAY mDataListItemMocNapClient.ListItemMocNap[n].GetTypeItem == 11
class NewMocNap
{
	public:
	void DrawWindowMocNap();
	void OpenWindowMocNap();
};
extern NewMocNap gNewMocNap;