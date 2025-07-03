#include "stdafx.h"
#if TAS_ITEMLOCK
#include "TAS_ItemLocker.h"
#include "Interface.h"
#include "Util.h"
#include "TMemory.h"
#include "Defines.h"
#include "Offset.h"
#include "UITextInputBox.h"
#include <sstream>
#include <iomanip>
#include <string>
#include "InterfaceElemental.h"

CNewUIWindowsClient nInterface;

CNewUIWindowsClient::CNewUIWindowsClient()
{
	this->ActiveLockMouse = 0;
	this->CustomLockItem = new GUIObj(200, 20, 230, 250, true); // Set X,Y,W,H
}

int StatusLock = 0;
CUITextInputBox* InputMatKhau = NULL;
char GetTextMatKhau[8 + 1] = { 0, };

void CNewUIWindowsClient::RenderLockWindow()
{
	if (!nInterface.CustomLockItem->onShow)
	{
		if (InputMatKhau)
		{
			InputMatKhau = NULL;
		}
		return;
	}
	pSetCursorFocus = true;
	float ThisY = 200;

	RenderBitmap(0x1791B, 200, 250 - ThisY, 230, 120, 0.0, 0.0, 1, 1, 1, 1, 0);

	float StartX = nInterface.CustomLockItem->X;
	float StartY = nInterface.CustomLockItem->Y;
	float WindowW = nInterface.CustomLockItem->Width;
	float WindowH = nInterface.CustomLockItem->Height;

	float TextX = StartX + 15;
	float TextY = StartY + 55;
	nInterface.DrawText((HFONT)pFontNormal, 215, 275 - ThisY, 0xFFFFFFFF, 0x0, 200, 0, 3, "Giao Dịch - Cửa Hàng - Phi Shop - Xoá Nhân Vật");
	gInterface.DrawGUI(FormPassLock, 215, 295 - ThisY);
	nInterface.DrawText((HFONT)pFontNormal, 80, 300 - ThisY, 0xFFFFFFFF, 0x0, 200, 0, 4, "Mật Khẩu Khoá");
	nInterface.DrawText((HFONT)pFontNormal, 215, 330 - ThisY, 0xFFFFFFFF, 0x0, 200, 0, 3, "Chú Ý : Vui lòng ghi nhớ mật khẩu!");
	nInterface.DrawText((HFONT)pFontNormal, 215, (330 + 11) - ThisY, 0xFFFFFFFF, 0x0, 200, 0, 3, "Hãy liên hệ Admin nếu bạn quên đi mật khẩu!");

	float TCoinX = (TextX + 78);
	float TCoinY = (TextY + 225) - ThisY;

	if (!InputMatKhau)
	{
		InputMatKhau = new CUITextInputBox;
		InputMatKhau->Init(pGameWindow, TCoinX, TCoinY, 8,TRUE);
		InputMatKhau->SetBackColor(0, 0, 0, 0);
		InputMatKhau->SetTextColor(255, 255, 157, 0);
		InputMatKhau->SetFont((HFONT)pFontNormal);
		InputMatKhau->SetState(UISTATE_NORMAL);
		InputMatKhau->SetOption(UIOPTION_NUMBERONLY);
		InputMatKhau->SetPosition(TCoinX, TCoinY);
	}
	else
	{
		if (nInterface.CustomLockItem->dragging)
		{
			InputMatKhau->SetPosition(TCoinX, TCoinY);
		}
		InputMatKhau->Render();

		InputMatKhau->GetText(GetTextMatKhau, 8+1);

		if (pCheckMouseOver(TCoinX - 5, TCoinY - 5, 100, 30) == 1)
		{
			if (GetKeyState(VK_LBUTTON) & 0x8000)
			{
				InputMatKhau->GiveFocus(1);
				PlayBuffer(25, 0, 0);
			}
		}
	}
	if (gElemental.gDrawButton(385, 294 - ThisY, 100, 11, "OK", 30))
	{
		CNewUIWindowsClient::SendLockUnLock(atoi(GetTextMatKhau));
		StatusLock ^= 1;
	}
}
void CNewUIWindowsClient::SendLockUnLock(int Pass)
{
	CGPACKET_LOCKWINDOW pMsg;
	pMsg.header.set(0xD3, 0x1B, sizeof(pMsg));
	pMsg.Status = StatusLock;
	pMsg.InPass = Pass; 
	DataSend((LPBYTE)& pMsg, pMsg.header.size);
}

void CNewUIWindowsClient::RecvGSSatusLockWindow(CGPACKET_LOCKWINDOW* lpMsg)
{
	StatusLock = lpMsg->Status; 
}
void CNewUIWindowsClient::OpenWindowLock()
{

	if ((GetTickCount() - nInterface.CustomLockItem->lastActionTime) > 300)
	{
		nInterface.CustomLockItem->lastActionTime = GetTickCount();

		if (nInterface.CustomLockItem->onShow)
		{
			nInterface.CustomLockItem->onShow = 0;
			return;
		}

		CGPACKET_LOCKWINDOW pMsg;
		pMsg.header.set(0xD3, 0x1A, sizeof(pMsg));
		pMsg.Status = 1;
		pMsg.InPass = 1234; 
		DataSend((LPBYTE)& pMsg, pMsg.header.size);
		nInterface.CustomLockItem->onShow ^= 1; 
	}
}
void CNewUIWindowsClient::RenderWindow()
{
	CNewUIWindowsClient::RenderLockWindow();
}

void CNewUIWindowsClient::DrawText(HFONT font, int PosX, int PosY, DWORD color, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...)
{
	char Buff[2048];
	int BuffLen = sizeof(Buff) - 1;
	ZeroMemory(Buff, BuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	int LineCount = 0;

	char* Line = strtok(Buff, "\n##");

	while (Line != NULL)
	{
		pSetFont(pTextThis(), (int)font);
		pSetTextColor(pTextThis(), (color & 0xff000000) >> 24, (color & 0x00ff0000) >> 16, (color & 0x0000ff00) >> 8, color & 0x000000ff);
		pSetBackgroundTextColor(pTextThis(), (bkcolor & 0xff000000) >> 24, (bkcolor & 0x00ff0000) >> 16, (bkcolor & 0x0000ff00) >> 8, bkcolor & 0x000000ff);
		pDrawText(pTextThis(), PosX, PosY, Line, Width, Height, (LPINT)Align, 0);
		PosY += 10;
		Line = strtok(NULL, "\n##");
		pSetFont(pTextThis(), (int)pFontNormal);
	}
}

void CNewUIWindowsClient::DrawGui(DWORD ModelID, float X, float Y, float W, float H, float SourceX, float SourceY, float SourceW, float SourceH, float ScaleW, float ScaleH, bool ScaleUp) {
	float v1, v2;

	if (W) {
		W /= ScaleW;
		v1 = ScaleW / (SourceW / W);
	}
	else {
		v1 = ScaleW;
	}

	if (H) {
		H /= ScaleH;
		v2 = ScaleH / (SourceH / H);
	}
	else {
		v2 = ScaleH;
	}
	pNIDrawGUI(ModelID, X, Y, W, H, SourceX / SourceW, SourceY / SourceH, v1, v2, ScaleUp, 1, 0);
}

void CNewUIWindowsClient::DrawFrame(DWORD ModelID, float X, float Y, float W, float H, float SourceX, float SourceY, float SourceW, float SourceH, float ScaleW, float ScaleH, bool ScaleUp) {
	float v1, v2;

	if (W) {
		W /= ScaleW;
		v1 = ScaleW / (SourceW / W);
	}
	else {
		v1 = ScaleW;
	}

	if (H) {
		H /= ScaleH;
		v2 = ScaleH / (SourceH / H);
	}
	else {
		v2 = ScaleH;
	}
	pNIDrawGUI(ModelID, X, Y, W, H, SourceX / SourceW, SourceY / SourceH, v1, v2, ScaleUp, 1, 0);
}

DWORD EventTickButton = 0;
bool CNewUIWindowsClient::BDrawButton(float PosX, float PosY, float SizeButton,float mSizeButtonH, bool IsEnter, LPCSTR Text, ...)
{
	static float v1;
	static float v2;
	static float v3;
	static float v4;
	static float v5;
	static float v6;
	static float v7;
	static float v8;
	static float v9;
	static float v10;

	char ButtonText[2048];
	int BuffLen = sizeof(ButtonText) - 1;
	ZeroMemory(ButtonText, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(ButtonText, BuffLen, Text, args);
	va_end(args);
	textSize tS = this->getTextSize(ButtonText);
	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);
	//============Button
	float SizeButtonW = SizeButton;
	float SizeButtonH = (SizeButton * 20) / 100;

	if (mSizeButtonH != 0)
	{
		SizeButtonH = mSizeButtonH;
	}

	v1 = (SizeButtonW * scale_ratio) / BUTTON_WIDTH;
	v2 = (SizeButtonH * scale_ratio) / BUTTON_HEIGHT;
	v3 = scale_width / v1;
	v4 = scale_height / v2;
	bool ActionButton = false;
	float StartX = PosX;
	float StartY = PosY;
	bool mreturn = false;
	float ScaleX = 0.0, ScaleY = 0.227;
	
	if (pCheckMouseOver(StartX, StartY, SizeButtonW, SizeButtonH) == 1)
	{
		ScaleX = ScaleY;
		if (GetTickCount() - EventTickButton > 500) //Click
		{
			if (GetKeyState(VK_LBUTTON) & 0x8000)
			{
				ScaleX = ScaleY * 2;
				EventTickButton = GetTickCount();
				PlayBuffer(25, 0, 0);
				mreturn = true;
				CNewUIWindowsClient::DrawFrame(0xF1003, StartX, StartY, BUTTON_WIDTH, BUTTON_HEIGHT, 404, 294, 1024, 512, v3, v4, 0);
				ActionButton = true;
			}
		}
		if (!ActionButton)
		{
			CNewUIWindowsClient::DrawFrame(0xF1003, StartX, StartY, BUTTON_WIDTH, BUTTON_HEIGHT, 706, 258, 1024, 512, v3, v4, 0);
			ActionButton = true;
		}
	}
	if ((GetKeyState(VK_RETURN) & 0x8000) && IsEnter)
	{
		gInterface.CloseWindow(ChatWindow);
		PlayBuffer(25, 0, 0);
		mreturn = true;

	}
	if (!ActionButton) CNewUIWindowsClient::DrawFrame(0xF1003, StartX, StartY, BUTTON_WIDTH, BUTTON_HEIGHT, 634, 258, 1024, 512, v3, v4, 0);

	CNewUIWindowsClient::DrawText((HFONT)pFontBold, StartX, StartY + (SizeButtonH / 2) - (tS.resize_height / 2.5), 0xE6FCF7FF, 0x0, SizeButtonW, 0, 3, ButtonText); //Buoc Vao
	glColor3f(1.0f, 1.0f, 1.0f); //Xoa mau
	pGLSwitch();
	EnableAlphaTest(0);
	return mreturn;
}
bool CNewUIWindowsClient::IsWorkZone(float a1, float a2, float a3, float a4) 
{
	return pCursorX <= (a1 + a3) && pCursorX >= a1 && pCursorY <= (a2 + a4) && pCursorY >= a2;
}

textSize CNewUIWindowsClient::getTextSize(char* a1)
{
	textSize res;
	struct tagSIZE psizl;
	sub_401C10();
	sub_9593B0((HDC)sub_41FF80(pTextThis()), a1, lstrlenA(a1), &psizl);

	if (pCheckWindow(pWindowThis(), 57) == 1)
		res.resize_height = (float)psizl.cy / (*(float*)0xE7C3D8 / 1.3);
	else
		res.resize_height = (float)psizl.cy / (*(float*)0xE7C3D8 / 1.1);
	res.width = (float)psizl.cx / *(float*)0xE7C3D4;
	res.height = (float)psizl.cy;
	res.resize_width = (float)psizl.cx / *(float*)0xE7C3D4;
	return res;
}

bool CNewUIWindowsClient::DrawBG(DWORD ModelID, float X, float Y, float W, float H, float rW, float rH, float sX, float sY, float sW, float sH)
{
	float v1;
	float v2;
	float v3;
	float v4;
	v1 = (W * scale_ratio) / rW;
	v2 = (H * scale_ratio) / rH;
	v3 = scale_width / v1;
	v4 = scale_height / v2;

	this->DrawGui(ModelID, X, Y, rW, rH, sX, sY, sW, sH, v3, v4);
	return true;
}

#endif