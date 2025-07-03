#pragma once
#if(SLOTPET2)
#define CharToString			((void*(__thiscall*)(void *thisa, char *a4))0x00409A50)
#define InitializeButton		((void(__thiscall*)(void* thisa)) 0x00779150)
#define DestroyButton			((void(__thiscall*)(void* thisa)) 0x00779250)
#define Constructor_Btn			((void(__stdcall*)(char *thisa,int ObjSize, int ObjCount, void (__thiscall *)(void *) , void (__thiscall *)(void *) )) 0x009CFA13)
#define sub_9CF630  	        ((char(__cdecl*)(char *a1, int a2, int a3)) 0x009CF630)
#define ho						*(HGDIOBJ*)0x00E8C588

#define pDrawPutero				((void(__thiscall*)(int This, char a5, int a6, char a7, char a8, char a9))0x00779350)

typedef struct UIButton
{
	UIButton()
	{
		memset(&this->btn, 0, sizeof(this->btn));
		Constructor_Btn(this->btn, 172, 1, InitializeButton, DestroyButton);
	}

	void SetBtn(char* zbtn)
	{
		memcpy(&this->btn, zbtn, sizeof(this->btn));
	}

	void ChangeButtonImgState(bool imgregister, int imgindex, bool overflg = false, bool isimgwidth = false, bool bClickEffect = false)
	{
		((void(__thiscall*)(char*, bool, int, bool, bool, bool)) 0x00779350)(
			this->btn, imgregister, imgindex, overflg, isimgwidth, bClickEffect);
	}

	void ChangeButtonInfo1(int x, int y, int sx, int sy)
	{
		((void(__thiscall*)(char*, int, int, int, int)) 0x00779410)(this->btn, x, y, sx, sy);
	}

	void ChangeText(char* btname)
	{
		int std_string[7];
		CharToString(&std_string, btname);
		((void(__thiscall*)(char*, int, int, int, int, int, int, int))0x00790970)(
			this->btn, std_string[0], std_string[1], std_string[2], std_string[3], std_string[4], std_string[5], std_string[6]);
	}

	void SetTooltipText(char* btname)
	{
		int std_string[7];
		CharToString(&std_string, btname);
		((void(__thiscall*)(char*, int, int, int, int, int, int, int, bool))0x007853F0)(
			this->btn, std_string[0], std_string[1], std_string[2], std_string[3], std_string[4], std_string[5], std_string[6], true);
	}

	bool UpdateMouseEvent()
	{
		return ((bool(__thiscall*)(char*)) 0x00779860)(this->btn);
	}

	bool Render(bool RendOption = false)
	{
		return ((bool(__thiscall*)(char*, BYTE)) 0x007798F0)(this->btn, RendOption);
	}

	void ChangeImgColor(DWORD eventstate, unsigned int color)
	{
		((void(__thiscall*)(char*, int, unsigned int))0x00779740)(this->btn, eventstate, color);
	}

	char btn[172];
} DNewUIButton;

typedef struct
{
	__int64	m_loPreExp;
	__int64	m_loGetExp;
	BYTE m_ItemHotKey[27];
	bool m_bExpEffect;
	DWORD m_dwExpEffectTime;
	DWORD m_dwPreExp;
	DWORD m_dwGetExp;
	DNewUIButton m_BtnCShop;
	DNewUIButton m_BtnChaInfo;
	DNewUIButton m_BtnMyInven;
	DNewUIButton m_BtnFriend;
	DNewUIButton m_BtnWindow;
	bool m_bButtonBlink;
} MainFrame;

void CNewUIMainFrameLoad();

class CNewUIMainFrame
{
	public:

};
#endif
