#pragma once
#pragma once
#include "Protocol.h"
#include "Object.h"
#define pBGetItemName ((const char(__cdecl*)(int ItemID, const char * Level, char * Buffer)) 0x005C2430)
#define CheckShopWindows gInterface.CheckWindow(ObjWindow::MoveList) || gInterface.CheckWindow(ObjWindow::CashShop) || gInterface.CheckWindow(ObjWindow::SkillTree) || gInterface.CheckWindow(ObjWindow::FullMap) || (gInterface.CheckWindow(Inventory) && gInterface.CheckWindow(ExpandInventory)	&& gInterface.CheckWindow(Store)) || (gInterface.CheckWindow(Inventory) && gInterface.CheckWindow(Warehouse) && gInterface.CheckWindow(ExpandWarehouse))
struct PMSG_CASHSHOP_SEND
{
	PSWMSG_HEAD header; // C2:F3:E2
	BYTE count;
};

struct ListShopSend
{
	int IndexShop;
	char Name[90];
};

struct PMSG_LISTITEMSHOP_SEND
{
	PSWMSG_HEAD header; // C2:F3:E2
	BYTE count;
};

struct LISTITEMCASHSHOP_SENDINFO
{
	float SizeBMD;
	int PriceType;
	int Price;
	int Class[7];
	short Index;
	BYTE TypeItem;
	BYTE Dur;
	BYTE Item[12];
	int  PeriodTime;
};
struct INFO_SHOP_ITEM
{
	float SizeBMD;
	int PriceType;
	int Price;
	int Class[7];
	short Index;
	BYTE TypeItem;
	ObjectItem Item;
};

struct XULY_CGPACKET_SSHOP
{
	PSBMSG_HEAD header; // C3:F3:03
	DWORD Shop;
	DWORD ViTri;
};


class CNewCashShop
{
	public:
	CNewCashShop();
	void Init();
	void DrawShop();
	void OpenCustomShop();
	void SendPacketToProtocol11(BYTE* lpMsg);
	void SendPacketToProtocol12(BYTE* lpMsg);
	char* MemCoin[5];
	std::vector<INFO_SHOP_ITEM> ListItemCashShop;
	std::vector<ListShopSend> DanhSachCashShop;
};

extern CNewCashShop gNewCashShop;