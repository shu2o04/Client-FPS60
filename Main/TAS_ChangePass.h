#pragma once
short GetSymbolFromVK(WPARAM wParam);
struct CSENDGS_DOIMK
{
	PSBMSG_HEAD Head; // C3:F3:03
	BYTE	TYPE;
	char PASS_OLD[11];
	char PASS_NEW[11];
	char PASS_NEW1[11];
};
class TASTaiKhoan
{
	public:
	void DrawVoidDoiPass();
	void BinObeject();
	void WindowsChangePass();
	bool TextBoxChangePass(DWORD Event);
	bool EventClickChangePass(DWORD Event);

	void OpenWindowsChangePass() 
	{ 
		gInterface.Data[eChangePass_Main].OnShow ^= true; 
		gInterface.Data[eChangePass_Main].FirstLoad = true; 
		*(BYTE*)0xE8C5AC ^= 1;
	};

	float MainWidth;
	float MainHeight;
	float StartY;
	float StartX;
	DWORD ClickTick;

};
extern TASTaiKhoan gTaiKhoan;
