#if(TAS_TUCHAN)
#define pGetItemName	((const char(__cdecl*)(int ItemID, const char * Level, char * Buffer)) 0x005C2430)

struct TCCSEV_COUNTLIST
{
	PSWMSG_HEAD header;
	int Count;
};
struct XULY_TULUYEN
{
	PSBMSG_HEAD header;
	DWORD ThaoTac;
};
struct CONFIDATA_TULUYEN
{
	WORD LvTuLuyen;
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
class cTuLuyen
{
	public:
	char* ItemTuLuyen(int ItemType, int Level);
	void LoadImageTuLuyen();
	void SendMenuButton();
	void SendPackTCButton();
	void SendTCProtocol(BYTE* lpMsg);
	void DrawWindowNangCapTuLuyen();
	void ShowTuLuyenTAS(int index,int PosX, int PosY);
	int TAS_TULUYEN_LVL, KhoanCach_Distance;
	std::map<int, CONFIDATA_TULUYEN> m_DataConfigTuLuyen;
	void HienThiBankNgoc(float StartX, float StartY, float CuaSoW, int itemID);
};
extern cTuLuyen gTuLuyen;
#endif
