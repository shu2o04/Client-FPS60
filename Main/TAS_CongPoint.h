#pragma once
#if ADD_POINT
#define MAX_ACCOUNT_LEVEL 4
struct PMSG_UPDATE_STATS_SEND
{
	PSBMSG_HEAD header;
	int Str;
	int Agi;
	int Vit;
	int Ene;
	int Com;
};

struct PMSG_RESET_STATS_SEND
{
	PSBMSG_HEAD header;
	int Type;
};

struct EXTRA_CPANEL_SENDINFO
{
	PSBMSG_HEAD h;
	BYTE QuickAdd;
	BYTE ResetStat;
	BYTE AutoHP;

	int	dStrength;
	int	dDexterity;
	int	dVitality;
	int	dEnergy;
	int	dLeadership;

	int MaxStatPoint[MAX_ACCOUNT_LEVEL];
};

class TASAddPoint
{
	public:
	BYTE m_QuickAdd;
	BYTE m_AUTOHP;
	BYTE m_ResetStats;

	int GetMaxStatPoint(int AccountLevel);

	int m_MaxStatPoint[MAX_ACCOUNT_LEVEL];

	int	d_Strength;
	int	d_Dexterity;
	int	d_Vitality;
	int	d_Energy;
	int	d_Leadership;

	void BingObjectRenderAddPoint();
	void GetFormat(char* str, char oldval, char newval);
	void DrawStatsAddWindow();
	bool ControlTextBox(DWORD Event);
	void EventStatsAddWindow(DWORD Event);
	void EventStatsAddWindow_Close(DWORD Event);
	void SwitchStatsWindowState() 
	{ 
		(gInterface.Data[eSTATSADD_MAIN].OnShow == true) ? gInterface.Data[eSTATSADD_MAIN].CloseAnimated(15) : gInterface.Data[eSTATSADD_MAIN].Open(-226, 20);
	};

	void CloseStatsAddWindow() 
	{ 
		gInterface.Data[eSTATSADD_MAIN].OnShow = false;
	};
	void EventResetStatsWindow_Close(DWORD Event);
	void SwitchResetStatsWindowState() 
	{ 
		(gInterface.Data[eRESETSTATS_MAIN].OnShow == true) ? gInterface.Data[eRESETSTATS_MAIN].Close() : gInterface.Data[eRESETSTATS_MAIN].Open(); 
	};
	void CloseResetStatsWindow() 
	{ 
		gInterface.Data[eRESETSTATS_MAIN].OnShow = false;
	};
	void EventCharacterWindow(DWORD Event);
	void DrawColoredAnimatedGUI(short ObjectID, float X, float Y, DWORD Color);
	void DrawAnimatedButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);
	void ExtraCpanelGetInfo(EXTRA_CPANEL_SENDINFO* lpMsg);
	void CGSendStatsAdd(PMSG_UPDATE_STATS_SEND pMsg);
	static void ChangeCharInfo(LPVOID This);
	void AutoHP_Tick(DWORD Event); // Thêm hàm AutoHP_Tick
	DWORD StatPoints;
};
extern TASAddPoint gAddPoint;
#endif