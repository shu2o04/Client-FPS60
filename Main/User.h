#pragma once
#include "Object.h"
#include "Protocol.h"


#pragma pack(push, 1)
struct PMSG_TARGETDATA_REQ
{
	PSWMSG_HEAD header;
	int			aIndex;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PMSG_TARGETDATA_ANS
{
	PSWMSG_HEAD header;
	int aIndex;
    bool isMonster;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PMSG_TARGET_MONSTER_DATA : PMSG_TARGETDATA_ANS
{
    int Life;
    int MaxLife;
    short Level;
};
#pragma pack(pop)
#pragma pack(push, 1)
struct PMSG_TARGET_PLAYER_DATA : PMSG_TARGET_MONSTER_DATA
{
    int SD;
    int MaxSD;
    short Reset;
	short RankTitle;
	short Long;
};
#pragma pack(pop)

struct CUSTOM_LOGO
{
	int Active;
	int	X;
	int	Y;
};

class User
{
public:
	int CoordenadaX;
	int CoordenadaY;
	int getLevel;
	int getReset;
	char getName[11];
	//-- post item
	int				PostItemID;
	int				PostItemLV;
	int				PostItemExc;
	int				PostItemAcc;
	int				PostItemHarmony;
	int				PostItem380;
	char*			PostItemSocket;
	int				PostItemX;
	int				PostItemY;
	int				GetPet;
	//--
	void			Load();
	
	void			Refresh();	
	bool			GetTarget();
	void			ToggleAuto();
	void			ToggleAutoTron();
	lpCharObj		lpPlayer;
	lpViewObj		lpViewPlayer;
	lpViewObj		lpViewTarget;
	BYTE			m_TargetType;	//1 - npc, 2 - attack
	int				m_MapNumber;
	int				m_CursorX;
	int				MagickAttack;
	int				m_CursorY;
	DWORD			m_TargetUpdateTick;
	DWORD		IsSendMove;
	DWORD		MoveToX;
	DWORD		MoveToY;
	BYTE		IsMove;
	int        AutoMoveCheckMap;
	bool InSafeZone;
	//--

	int Zen;
	int WCoinC;
	int WCoinP;
	int WCoinG;

	int GetActiveSkill();
	static void	SetEventEffect(int PreviewStruct);
	BOOL        is_auto;
	BOOL        is_autotron;
	CUSTOM_LOGO m_Logo[400];

	int DH_WC,DH_WP,DH_WG;
	int SatThuong,SatThuongDouble,PhongThu,TangMau,TangSD;

	#if(TAS_HONHOAN)
	void      CBRenderCharacter(DWORD ObjectPointer, int Effect, float SizeX, float SizeY, vec3_t Color, int Type = 0);
	#endif
	#if LUC_CHIEN
	DWORD mLucChien;
	#endif
};
extern User gObjUser;
