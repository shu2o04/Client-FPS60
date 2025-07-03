#if(TAS_NEWVIP)
#define pGetItemName	((const char(__cdecl*)(int ItemID, const char * Level, char * Buffer)) 0x005C2430)

struct NVCSEV_COUNTLIST
{
	PSWMSG_HEAD header;
	int Count;
};
struct XULY_NEWVIP
{
	PSBMSG_HEAD header;
	DWORD ThaoTac;
};
struct CONFIDATA_NEWVIP
{
	WORD LvNewVip;
	DWORD YCWC;
	DWORD ExpThuong;
	DWORD ExpMaster;
	int Days;
};
class cNewVip
{
	public:
	char* ItemNewVip(int ItemType, int Level);
	void LoadImageNewVip();
	void SendMenuButton();
	void SendPackNVButton();
	void SendNVProtocol(BYTE* lpMsg);
	void DrawWindowNangCapNewVip();
	void ShowNewVipTAS(int index,int PosX, int PosY);
	int TAS_NEWVIP_LVL, KhoanCach_Distance;
	std::map<int, CONFIDATA_NEWVIP> m_DataConfigNewVip;
};
extern cNewVip gNewVip;
#endif
