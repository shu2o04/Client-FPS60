#if(TAS_HONHOAN)
#define pGetItemName	((const char(__cdecl*)(int ItemID, const char * Level, char * Buffer)) 0x005C2430)

struct HHCSEV_COUNTLIST
{
	PSWMSG_HEAD header;
	int Count;
};
struct XULY_HONHOAN
{
	PSBMSG_HEAD header; // C3:F3:03
	DWORD ThaoTac;
};
struct CONFIDATA_HONHOAN
{
	WORD LvHonHoan;
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
	DWORD ItemReward;
};


enum ImgHonHoan
{
	eImgHonHoan = 20000,
	eDemoHonHoan = eImgHonHoan + 15,
	eImgHonHoanEnd,

};

class cHonHoan
{
	public:
	char* ItemHonHoan(int ItemType, int Level);
	void LoadImageHonHoan();
	void DrawWindowNangCapHonHoan();
	void AddHonHoanCape(DWORD ObjectPointer);
	void SendPackHHButton();
	void SendMenuButton();
	void SendHHProtocol(BYTE* lpMsg);
	std::map<int, CONFIDATA_HONHOAN> m_DataConfigHonHoan;
};
extern cHonHoan gHonHoan;
#endif
