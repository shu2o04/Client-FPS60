#include "Defines.h"
#include "Protocol.h"
#if BXHDAME
struct TAS_DAMEBOSS_STR
{
	WORD monsterid;
	int Level;
	float MinLife;
	float MaxLife;
	char szName[11];
	QWORD Kill;
	BYTE Rate;
};

class TAS_DAMEBOSS_CLASS
{
	public:
	
	WORD TAS_DAMEBOSS_ID;
	int Level;
	float MinLife;
	float MaxLife;
	BYTE Rate;
	int CalcString ;
	void DAMEGETINFO(PMSG_NEW_HEALTH_BAR_RECV* lpMsg);
	void DAMEDRAW();
	TAS_DAMEBOSS_STR gDmgBoss[10];
	void DAMECLEAR();
	bool CheckDrawBxhDame;
	BYTE ADD_OFF_ANTOAN;
	void Initz();
private:
	float guiX;
	float guiY;
	short curX;
	short curY;
	bool  dragging;
	DWORD ActionTime;
	bool is_move;
};
extern TAS_DAMEBOSS_CLASS gDmgBoss;

#endif
