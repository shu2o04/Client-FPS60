#pragma once
#include "stdafx.h"
#if NEWXSHOP
#include "import.h"
#include "Protocol.h"
typedef char tooltiparray[100];
typedef void(*PUSHEVENT_CALLBACK_LPVOID)(LPVOID);
enum ImgElemental
{
	eNumElemental_NULL = 68000,
	eNumElemental_Fire,
	eNumElemental_Water,
	eNumElemental_Earth,
	eNumElemental_Wind,
	eNumElemental_Darkness,
	eNumElemental_MainSub,
};

struct COUNTER_INFO
{
	int Elemental;
	int RateToFire;
	int RateToWater;
	int RateToEarth;
	int RateToWind;
	int RateToDark;
	int RateToNomal;
};


struct OPTIONRATE_INFO
{
	int Elemental;
	int DmgRate;
	int EffectRate;
	int EffectID;
};
typedef struct ELEMENTAL_SENDUSERLOGIN
{
	PSWMSG_HEAD header;
	WORD Elemental;
	WORD Level;
	WORD MaxLevel;
	WORD DmgRateLv;
	WORD EffectRateLv;
	int Count;
};
struct ITEMPOINT_INFO
{
	WORD IndexItem;
	BYTE Level;
	BYTE ExlOp;
	DWORD PointVIP;
};
struct NEXTINFO_UPLEVEL
{
	PSWMSG_HEAD header;
	DWORD Point;
	DWORD WC;
	DWORD WP;
	DWORD GP;
};
class CElemental
{
public:
	CElemental();
	void gDrawWindowCustom(float StartX, float StartY, float CuaSoW, float CuaSoH, int eNumWindow, char* WindowName);
	void gInfoBox(float PosX, float PosY, float Width, float Height, DWORD bkcolor, float Arg5, int Arg6);
	bool gDrawButton(float PosX, float PosY, float SizeButton, int FontSize, char* ButtonText, float mSizeButtonW = 0);
	bool gDrawButtonClassic(float PosX, float PosY, float SizeButton, int FontSize, char* ButtonText, float mSizeButtonW);
	void DrawFrame(DWORD ModelID, float X, float Y, float W, float H, float SourceX = 0, float SourceY = 0, float SourceW = 225, float SourceH = 225, float ScaleW = 1.5f, float ScaleH = 1.5f, bool ScaleUp = 0);
	void CElemental::DrawText(HFONT font, int PosX, int PosY, DWORD color, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...);
	DWORD LockMouseMoveClick;
	char MsgBoxCaption[50];
	char MsgBoxText[512];
	int MsgBoxType;
	int MsgLine;
	PUSHEVENT_CALLBACK_LPVOID MsgBoxCallback;
	void CElemental::DrawMessageBox();
	void CElemental::OpenMessageBox(char* caption, char* Format, ...);
	void CElemental::OpenMessageBoxOkCancel(PUSHEVENT_CALLBACK_LPVOID pCallbackFunc, char* caption, char* Format, ...);
	bool CElemental::gDrawButtonEx(float PosX, float PosY, float SizeButton, int FontSize, float mSizeButtonW, char* ButtonText);
	DWORD  LockMouse;
	std::map<int, OPTIONRATE_INFO> m_OptionRate;
	std::map<int, COUNTER_INFO> m_Counter;
	std::vector<ITEMPOINT_INFO> m_ItemPoint;

	int mElemental;
	int mLevel;
	int mMaxLevel;
	int mDmgRateLv;
	int mEffectRateLv;

	DWORD mPoint;
	DWORD mWC;
	DWORD mWP;
	DWORD mGP;
	bool LockButtonHover;
private:

};
extern CElemental gElemental;
#endif