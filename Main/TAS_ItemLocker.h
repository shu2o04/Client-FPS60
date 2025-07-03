#pragma once
#if TAS_ITEMLOCK

#include "UITextInputBox.h"
#include "Protocol.h"

#define pNIDrawGUI	((void(__cdecl*)(DWORD ModelID, float PosX, float PosY, float Width, float Height, float SourceX, float SourceY, float ScaleX, float ScaleY, bool Scale, bool Arg11, float Arg12)) 0x637C60)

#define sub_41FF80					((int(__thiscall*)(LPVOID This)) 0x0041FF80)
#define sub_401C10					((int(*)())0x401C10)

#define scale_ratio				1.710526315789474
#define scale_width				scale_ratio / pWinWidthReal
#define scale_height			scale_ratio / pWinHeightReal

#define BUTTON_WIDTH			65
#define BUTTON_HEIGHT			30


struct textSize
{
	float	width;
	float	height;
	float	resize_width;
	float	resize_height;
};

struct GUIresource
{
	DWORD	ID;
	float	CellWidth;
	float	CellHeight;
	float	SourceX;
	float	SourceY;
	float	SourceWidth;
	float	SourceHeight;
	float	ScaleX;
	float	ScaleY;
	DWORD	TextColor;
	DWORD	TextBGColor;

	GUIresource(DWORD a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8 = 0, float a9 = 0, DWORD a10 = 0x999999FF, DWORD a11 = 0x0)
	{
		ID = a1;
		CellWidth = a2;
		CellHeight = a3;
		SourceX = a4;
		SourceY = a5;
		SourceWidth = a6;
		SourceHeight = a7;
		ScaleX = a8;
		ScaleY = a9;
		TextColor = a10;
		TextBGColor = a11;
	}
};


struct GUIButton
{
	float X;
	float Y;
	float Width;
	float Height;
	float Max_X;
	float Max_Y;
	bool  clickDown;
	BYTE  state;
	int	  delay;
	DWORD lastActionTime;

	GUIButton()
	{
		clickDown = false;
		state = 0;
		lastActionTime = GetTickCount();
	}

	GUIButton(float a1, float a2, float a3, float a4, int a5)
	{
		clickDown = false;
		state = 0;
		lastActionTime = GetTickCount();
		X = a1;
		Y = a2;
		Width = a3;
		Height = a4;
		Max_X = X + Width;
		Max_Y = Y + Height;
		delay = a5;
		lastActionTime = GetTickCount();
	}
};

struct GUIObj
{
	float X;
	float Y;
	float Default_X;
	float Default_Y;
	float curX;
	float curY;
	float Width;
	float Height;
	float Max_X;
	float Max_Y;
	bool  isFocus;
	bool onShow;
	bool dragging;
	bool allowDrag;
	bool scaleUp;
	BYTE state;
	DWORD lastActionTime;

	GUIObj() {
		onShow = false;
		dragging = false;
		lastActionTime = GetTickCount();
		state = 0;
		isFocus = false;
		allowDrag = false;
		scaleUp = true;
	}

	GUIObj(float a1, float a2, float a3, float a4, bool a5 = false, bool a6 = true) {
		onShow = false;
		dragging = false;
		lastActionTime = GetTickCount();
		state = 0;
		isFocus = false;
		allowDrag = false;
		scaleUp = true;

		X = a1;
		Y = a2;
		Default_X = a1;
		Default_Y = a2;
		Width = a3;
		Height = a4;
		Max_X = X + Width;
		Max_Y = Y + Height;
		allowDrag = a5;
		scaleUp = a6;
	}

};


struct uintInput
{
	bool	selected;
	UINT	value;
	UINT	max;
	int		delay;
	DWORD	lastActionTime;

	uintInput()
	{
		selected = false;
		value = 0;
		max = UINT_MAX;
		delay = 150;
		lastActionTime = GetTickCount();
	}
	uintInput(UINT a1, UINT a2, int a3)
	{
		selected = false;
		value = a1;
		max = a2;
		delay = a3;
		lastActionTime = GetTickCount();
	}
};


struct CGPACKET_LOCKWINDOW
{
	PSBMSG_HEAD header; // C3:F3:03
	DWORD Status;
	DWORD InPass;
};

class CNewUIWindowsClient
{
	public:
	CNewUIWindowsClient();
	uintInput* bufferUint;
	void		DrawGui(DWORD ModelID, float X, float Y, float W, float H, float SourceX = 0, float SourceY = 0, float SourceW = 1024, float SourceH = 512, float ScaleW = 1.5f, float ScaleH = 1.5f, bool ScaleUp = 0);
	void		DrawFrame(DWORD ModelID, float X, float Y, float W, float H, float SourceX = 0, float SourceY = 0, float SourceW = 1024, float SourceH = 512, float ScaleW = 1.5f, float ScaleH = 1.5f, bool ScaleUp = 0);
	bool		DrawBG(DWORD ModelID, float X, float Y, float W, float H, float rW, float rH, float sX = 0, float sY = 0, float sW = 1024, float sH = 1024);
	bool		IsWorkZone(float, float, float, float);
	textSize	getTextSize(char*);
	void		DrawText(HFONT font, int PosX, int PosY, DWORD color, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...);
	void		RenderWindow();
	DWORD		ActiveLockMouse;
	bool  BDrawButton(float PosX, float PosY, float SizeButton, float mSizeButtonH, bool IsEnter, LPCSTR Text, ...);
	void SendLockUnLock(int Pass);
	void OpenWindowLock();
	GUIObj* CustomLockItem;
	void RecvGSSatusLockWindow(CGPACKET_LOCKWINDOW* lpMsg);
	void	RenderLockWindow();
}; 
extern CNewUIWindowsClient nInterface;
#endif