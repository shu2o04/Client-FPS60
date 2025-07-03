#if(TAS_QUANHAM)
#define pGetItemName	((const char(__cdecl*)(int ItemID, const char * Level, char * Buffer)) 0x005C2430)

struct QHCSEV_COUNTLIST
{
	PSWMSG_HEAD header;
	int Count;
};
struct XULY_QUANHAM
{
	PSBMSG_HEAD header;
	DWORD ThaoTac;
};
struct CONFIDATA_QUANHAM
{
	WORD LvQuanHam;
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
class cQuanHam
{
	public:
	char* ItemQuanHam(int ItemType, int Level);
	void LoadImageQuanHam();
	void SendMenuButton();
	void SendPackQHButton();
	void SendQHProtocol(BYTE* lpMsg);
	void DrawWindowNangCapQuanHam();
	void ShowQuanHamTAS(int index,int PosX, int PosY);
	int TAS_QUANHAM_LVL, KhoanCach_Distance;
	std::map<int, CONFIDATA_QUANHAM> m_DataConfigQuanHam;
};
extern cQuanHam gQuanHam;
#endif
