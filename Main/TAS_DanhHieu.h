#if(TAS_DANHHIEU)
#define pGetItemName	((const char(__cdecl*)(int ItemID, const char * Level, char * Buffer)) 0x005C2430)

struct DHCSEV_COUNTLIST
{
	PSWMSG_HEAD header;
	int Count;
};
struct XULY_DANHHIEU
{
	PSBMSG_HEAD header;
	DWORD ThaoTac;
};
struct CONFIDATA_DANHHIEU
{
	WORD LvDanhHieu;
	WORD YCItemSL;
	WORD YCItemID;
	WORD YCItemLv;
	DWORD YCWC;
	DWORD YCWP;
	DWORD YCGP;
	DWORD TangMau;
	DWORD TangSD;
	DWORD TangST;
	DWORD TangPT;
};
class cDanhHieu
{
	public:
	char* ItemDanhHieu(int ItemType, int Level);
	void LoadImageDanhHieu();
	void SendMenuButton();
	void SendPackDHButton();
	void SendDHProtocol(BYTE* lpMsg);
	void DrawWindowNangCapDanhHieu();
	void ShowDanhHieuTAS(int index,int PosX, int PosY);
	int TAS_DANHHIEU_LVL, KhoanCach_Distance;
	std::map<int, CONFIDATA_DANHHIEU> m_DataConfigDanhHieu;
};
extern cDanhHieu gDanhHieu;
#endif
