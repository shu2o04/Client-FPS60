#include "stdafx.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "TAS_ToolKit.h"
#include "Import.h"
#include "Interface.h"
#include "MessHacking.h"
#include "CustomJewelBank.h"
#include "UIControl.h"
#include "Object.h"
#include "Defines.h"
#include "Config.h"
TAS_ToolKitMain gToolKit;
#define pBGetItemName					((const char(__cdecl*)(int ItemID, const char * Level, char * Buffer)) 0x005C2430)
#define sub_637E80					((void(__cdecl*)(int x, float y, float w, float h, float giro, float a9, float a10, float a11, float a12, float a13))0x00637E80)

signed int __cdecl ColorMoneys(unsigned int a1)
{
	signed int color1 = eWhite; // eax@2

	if (a1 >= 1000 && a1 < 1000000)
	{
		color1 = eShinyGreen;
	}
	else if (a1 >= 1000000 && a1 < 10000000)
	{
		color1 = eGold;
	}
	else if (a1 >= 1000000 && a1 < 100000000)
	{
		color1 = eOrange;
	}
	else if (a1 >= 100000000)
	{
		color1 = eRed;
	}
	return color1;
}

void TAS_ToolKitMain::CloseButton(float X, float Y, int Enum)
{
	gInterface.DrawAnimatedGUI(Enum, X, Y);

	if (gInterface.IsWorkZone(Enum))
	{
		DWORD Color = eGray100;
		if (gInterface.Data[Enum].OnClick)
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(Enum, gInterface.Data[Enum].X, gInterface.Data[Enum].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[Enum].X + 5, gInterface.Data[Enum].Y + 25, gConfig.TTAS_TEXT_ENGINE[26]);
	}
}
std::string FormatNumber(float value)
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << value;
	std::string str = oss.str();

	size_t pos = str.find_last_not_of("0");
	if (pos != std::string::npos)
		str.erase(pos + 1);
	if (str.back() == '.')
		str.pop_back();

	return str;
}
void TAS_ToolKitMain::DrawButtonIconRank(int Enum, int ImgID, float X, float Y, float W, float H, LPCSTR Text)
{
	gInterface.DrawButtonRender(Enum, X + 1, Y, 0, 0.0f);
	if (gInterface.IsWorkZone(Enum))
	{
		gInterface.DrawToolTip(X, Y - 10, Text);
		if (gInterface.Data[Enum].OnClick) {
			RenderBitmap(ImgID, X, Y, W, H, 0.0, 0.451f, 0.878, 0.225, 1, 1, 0.0);}else {
			RenderBitmap(ImgID, X, Y, W, H, 0.0, 0.2255f, 0.878, 0.225, 1, 1, 0.0);}}else {
			RenderBitmap(ImgID, X, Y, W, H, 0.0, 0.0, 0.878, 0.225, 1, 1, 0.0);
	}
}
void TAS_ToolKitMain::RenderMixEffect(int type, int x, int y, int w, int h)
{
	int result; // eax
	float v4; // [esp+28h] [ebp-48h]
	float v5; // [esp+30h] [ebp-40h]
	GLfloat red; // [esp+44h] [ebp-2Ch]
	GLfloat green; // [esp+4Ch] [ebp-24h]
	float v8; // [esp+58h] [ebp-18h]
	float v9; // [esp+5Ch] [ebp-14h]
	float v10; // [esp+60h] [ebp-10h]
	float v11; // [esp+64h] [ebp-Ch]
	int j; // [esp+68h] [ebp-8h]
	int i; // [esp+6Ch] [ebp-4h]

	if (type > 0)
	{
		for (i = 1; i <= h; ++i)
		{
			for (j = 1; j <= w; ++j)
			{
				pSetBlend(1);
				pGLSwitchBlend();
				green = (double)(rand() % 4 + 4) * 0.1000000014901161;
				red = (double)(rand() % 6 + 6) * 0.1000000014901161;
				glColor3f(red, green, 0.2);
				v11 = (double)((int)0x5EF5A1C % 100) * 20.0;
				v8 = (double)(rand() % 10) + 5.0;
				v9 = (float)(x + rand() % (20 * j + 1));
				v10 = (float)(y + rand() % (20 * i + 1));
				sub_637E80(32113, LODWORD(v9), LODWORD(v10), LODWORD(v8), LODWORD(v8), 0.0, 0.0, 0.0, 1.0, 1.0);
				sub_637E80(32113, LODWORD(v9), LODWORD(v10), LODWORD(v8), LODWORD(v8), LODWORD(v11), 0.0, 0.0, 1.0, 1.0);
				v5 = v8 * 3.0;
				sub_637E80(32114, LODWORD(v9), LODWORD(v10), LODWORD(v5), LODWORD(v5), LODWORD(v11), 0.0, 0.0, 1.0, 1.0);
				v4 = v8 * 6.0;
				sub_637E80(32002, LODWORD(v9), LODWORD(v10), LODWORD(v4), LODWORD(v4), 0.0, 0.0, 0.0, 1.0, 1.0);
				pGLSwitch();
				glColor4f(1.0, 1.0, 1.0, 1.0);
				pSetBlend(0);
			}
		}
	}
}
char* TAS_ToolKitMain::BGetItemName(int ItemType, int Level)
{
	char ItemNameGet[100];
	memset(ItemNameGet, 0, sizeof(ItemNameGet));
	pBGetItemName(ItemType, (const char*)(GET_ITEMOPT_LEVEL(Level)), (char*)ItemNameGet);
	std::string a(ItemNameGet);
	return strdup(a.c_str());
}
void TAS_ToolKitMain::CreateFontNew(int X, int Y, int W, int Pos, int Size, int Bold, LPCSTR String, COLORREF TextColor, HFONT CrateSub)
{
	CrateSub = CreateFontA(Size, 0, 0, 0, Bold, 0, 0, 0, 0x1, 0, 0, 3, 0, "Verdana");
	pSetTextFont(pTextThis(), CrateSub);
	pSetTextColor(pTextThis(), GetRValue(TextColor), GetGValue(TextColor), GetBValue(TextColor), 255); // Thiết lập màu sắc từ tham số mới
	pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);
	g_pRenderText.CRenderText(X, Y, String, W, -1, Pos, 0);
	DeleteObject(CrateSub); // Giải phóng
}
void TAS_ToolKitMain::MakeShadowText(int X, int Y, int W, int Pos, LPCSTR String,...)
{

	pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);
	SetTextColorByHDC(pTextThis(), pMakeColor(0xFFu, 0xFFu, 0xFFu, 0xFFu));
	g_pRenderText.CRenderText(X, Y, String, W, 0, Pos, 0);
}
char* TAS_ToolKitMain::QNumberFormat(QWORD Number)
{
	if (Number < 0) { return "0"; }
	char OutPut[15];

	if (Number < 1000) {
		sprintf(OutPut, "%d", Number);
		return strdup(OutPut);
	}
	else if (Number < 1000000) {
		int part1 = Number % 1000;
		int part2 = (Number - part1) / 1000;
		sprintf(OutPut, "%d,%03d", part2, part1);
		return strdup(OutPut);
	}
	else if (Number < 1000000000) {
		int part1 = Number % 1000;
		Number = (Number - part1) / 1000;
		int part2 = Number % 1000;
		Number = (Number - part2) / 1000;
		int part3 = Number % 1000;

		sprintf(OutPut, "%d,%03d,%03d", part3, part2, part1);
		return strdup(OutPut);
	}
	else {
		int part1 = Number % 1000;
		Number = (Number - part1) / 1000;
		int part2 = Number % 1000;
		Number = (Number - part2) / 1000;
		int part3 = Number % 1000;
		int part4 = (Number - part3) / 1000;

		sprintf(OutPut, "%d,%03d,%03d,%03d", part4, part3, part2, part1);
		return strdup(OutPut);
	}
	return "0";
}

char* TAS_ToolKitMain::NumberFormat(DWORD Number)
{
	if (Number < 0) { return "0"; }

	char OutPut[15];

	if (Number < 1000) {
		sprintf(OutPut, "%u", Number);
		return strdup(OutPut);
	}
	else if (Number < 1000000) {
		int part1 = Number % 1000;
		int part2 = (Number - part1) / 1000;
		sprintf(OutPut, "%u,%03u", part2, part1);
		return strdup(OutPut);
	}
	else if (Number < 1000000000) {
		int part1 = Number % 1000;
		Number = (Number - part1) / 1000;
		int part2 = Number % 1000;
		Number = (Number - part2) / 1000;
		int part3 = Number % 1000;

		sprintf(OutPut, "%u,%03u,%03u", part3, part2, part1);
		return strdup(OutPut);
	}
	else {
		int part1 = Number % 1000;
		Number = (Number - part1) / 1000;
		int part2 = Number % 1000;
		Number = (Number - part2) / 1000;
		int part3 = Number % 1000;
		int part4 = (Number - part3) / 1000;

		sprintf(OutPut, "%u,%03u,%03u,%03u", part4, part3, part2, part1);
		return strdup(OutPut);
	}
	return "0";
}

float TAS_ToolKitMain::RenderExNumberLevel2(float x, float y, int iNum, int iNum1, float fScale)
{
	EnableAlphaTest(1);
	if (fScale < 0.3f)
	{
		return x;
	}

	char strText[32];
	char strText1[32];
	itoa(iNum, strText, 10);
	itoa(iNum1, strText1, 10);
	int iLength = (int)strlen(strText);
	int iLength1 = (int)strlen(strText1);
	float width = 11.f * (fScale - 0.3f);
	float height = 17.3f * (fScale - 0.3f);

	x -= width * iLength / 2;
	for (int i = 0; i < iLength; ++i)
	{
		float fU = (float)(strText[i] - 48) * 12.f / 128.f;
		RenderBitmap(31337, x + 0.5, y, width, height, fU, 0.f, 12.f / 128.f, 14.f / 16.f, 1, 1, 0.0);
		x += width * 0.8f;
	}
	RenderBitmap(0x1791A, x, y, width + 3, height, 0.f, 0.f, 9.f / 16.f, 14.f / 16.f, 1, 1, 0.0);
	x += width * 1.8f;
	x -= width * iLength1 / 2;
	for (int i = 0; i < iLength1; ++i)
	{
		float fU = (float)(strText1[i] - 48) * 12.f / 128.f;
		RenderBitmap(31337, x, y, width, height, fU, 0.f, 12.f / 128.f, 14.f / 16.f, 1, 1, 0.0);
	}
	return x;
}

void TAS_ToolKitMain::DrawButtonIcon( int Enum, int ImgID,float X, float Y, float W, float H, LPCSTR Text)
{
	gInterface.DrawButtonRender(Enum, X + 1.5f, Y+0.5f, 0, 0.0f);
	if (gInterface.IsWorkZone(Enum))
	{
		gInterface.DrawToolTip(X, Y + 40, Text);
		if (gInterface.Data[Enum].OnClick) {
			RenderBitmap(ImgID, X, Y, W, H, 0.0, 0.451f, 0.878, 0.225, 1, 1, 0.0);}else{
			RenderBitmap(ImgID, X, Y, W, H, 0.0, 0.2255f, 0.878, 0.225, 1, 1, 0.0);}}else{
			RenderBitmap(ImgID, X, Y, W, H, 0.0, 0.0, 0.878, 0.225, 1, 1, 0.0);
	}
}
void TAS_ToolKitMain::DrawButtonIconMove( int Enum, int ImgID,float X, float Y, float W, float H)
{
	gInterface.DrawButtonRender(Enum, X, Y, 0, 0.0f);
	if (gInterface.IsWorkZone(Enum))
	{
		if (gInterface.Data[Enum].OnClick) {
			RenderBitmap(ImgID, X, Y, W, H, 0.0, 0.451f, 0.878, 0.225, 1, 1, 0.0);}else{
			RenderBitmap(ImgID, X, Y, W, H, 0.0, 0.2255f, 0.878, 0.225, 1, 1, 0.0);}}else{
			RenderBitmap(ImgID, X, Y, W, H, 0.0, 0.0, 0.878, 0.225, 1, 1, 0.0);
	}
}
float TAS_ToolKitMain::CRenderNumberClassic(BYTE Color, float x, float y, int iNum, float fScale)
{
	EnableAlphaTest(1);
	if (fScale < 0.3f)
	{
		return x;
	}

	char strText[32];
	itoa(iNum, strText, 10);
	int iLength = (int)strlen(strText);

	if (Color == 1) // 
	{
		float width = 11.f * (fScale - 0.3f);
		float height = 17.3f * (fScale - 0.3f);
		x -= width * iLength / 2;
		for (int i = 0; i < iLength; ++i)
		{
			float fU = (float)(strText[i] - 48) * 12.f / 128.f;
			RenderBitmap(31337, x, y, width, height, fU, 0.f, 12.f / 128.f, 14.f / 16.f, 1, 1, 0.0);
			x += width * 0.8f;
		}
	}
	if (Color == 2) //
	{
		float width = 11.f * (fScale - 0.3f);
		float height = 17.3f * (fScale - 0.3f);
		x -= width * iLength / 2;
		for (int i = 0; i < iLength; ++i)
		{
			float fU = (float)(strText[i] - 48) * 12.f / 128.f;
			RenderBitmap(31337, x, y, width, height, fU, 0.f, 12.f / 128.f, 14.f / 16.f, 1, 1, 0.0);
			x += width * 0.8f;
		}
		RenderBitmap(41004, x, y, width + 3, height, 0.f, 0.f, 9.f / 16.f, 14.f / 16.f, 1, 1, 0.0);
	}
	return x;
}

double TAS_ToolKitMain::CRenderNumberExBank(float a1, float a2, int a3, float a4, DWORD ModelID)
{
	double result;
	float v5;
	float v6; 
	signed int i; 
	float v8;
	signed int v9; 
	char v10[32];
	float v11;

	EnableAlphaTest(1);
	glColor4f(1.0f, 0.7f, 0.0f, 1.0f);

	if (a4 >= 0.300000011920929)
	{
		v8 = (a4 - 0.4800000119209290) * 12.0;
		itoa(a3, v10, 10);
		v9 = strlen(v10);
		v11 = a1 - (double)v9 * v8 / 2.0;
		for (i = 0; i < v9; ++i)
		{
			v6 = (double)(v10[i] - 48) * 12.0 / 128.0;
			v5 = (a4 - 0.400000011920929) * 16.0;
			RenderBitmap(ModelID, v11, a2, v8, v5, v6, 0.0, 0.09375, 0.875, 1, 1, 0.0);
			v11 = v8 * 0.800000011920929 + v11;
		}
		result = v11;
	}
	else
	{
		result = a1;
	}
	pGLSupremo();
	return result;
}

double TAS_ToolKitMain::CRenderNumberEx(float a1, float a2, double a3, float a4, DWORD ModelID)
{
	double result;
	float v5;
	float v6;
	signed int i;
	float v8;
	signed int v9;
	char v10[32];
	float v11;
	float v12;

	if (a3 >= 0.0 && a3 <= 9.0)			v12 = 4.0f;
	else if (a3 <= 99.0)                v12 = 3.8f;
	else if (a3 <= 999.0)               v12 = 3.6f;
	else if (a3 <= 9999.0)              v12 = 3.4f;
	else if (a3 <= 99999.0)				v12 = 3.2f;
	else if (a3 <= 999999.0)            v12 = 3.0f;
	else if (a3 <= 9999999.0)			v12 = 2.8f;
	else if (a3 <= 99999999.0)			v12 = 1.4f;
	else if (a3 <= 999999999.0)			v12 = 2.4f;
	else if (a3 <= 2147000000.0)		v12 = 2.2f;
	else                                v12 = 2.0f;

	EnableAlphaTest(1);
	glColor4f(50, 50, 50, 190);

	if (a4 >= 0.300000011920929)
	{
		v8 = (a4 - 0.4800000119209290) * 12.0;
		_snprintf(v10, sizeof(v10), "%.0f", a3);
		v9 = strlen(v10);
		v11 = a1 - (double)v9 * v8 / 2.0;
		for (i = 0; i < v9; ++i)
		{
			v6 = (double)(v10[i] - 48) * 12.0 / 128.0;
			v5 = (a4 - 0.400000011920929) * 16.0;
			RenderBitmap(ModelID, v11 - v12, a2, v8, v5, v6, 0.0, 0.09375, 0.875, 1, 1, 0.0);
			v11 = v8 * 0.800000011920929 + v11;
		}
		result = v11;
	}
	else
	{
		result = a1;
	}
	pGLSupremo();
	return result;
}
double TAS_ToolKitMain::CRenderNumberExNew(float a1, float a2, double a3, int a5, float Scale)
{
	double result;
	float v5;
	float v6;
	signed int i;
	float v8;
	signed int v9;
	char v10[32];
	float v11;
	float v12;

	if (a5 == 1) // left
	{
		if (a3 >= 0 && a3 <= 9)				v12 = 27.0f;
		else if (a3 <= 99)					v12 = 25.5f;
		else if (a3 <= 999)					v12 = 24.0f;
		else if (a3 <= 9999)				v12 = 22.5f;
		else if (a3 <= 99999)				v12 = 21.0f;
		else if (a3 <= 999999)				v12 = 19.5f;
		else if (a3 <= 9999999)				v12 = 18.0f;
		else if (a3 <= 99999999)			v12 = 16.5f;
		else if (a3 <= 999999999)			v12 = 15.0f;
		else if (a3 <= 999999999)			v12 = 13.5f;
		else if (a3 <= 2147000000)			v12 = 12.0f;
		else								v12 = 10.5f;
	}
	else if (a5 == 2) //Right
	{
		if (a3 >= 0 && a3 <= 9)				v12 = 20.0f;
		else if (a3 <= 99)					v12 = 22.0f;
		else if (a3 <= 999)					v12 = 24.0f;
		else if (a3 <= 9999)				v12 = 26.0f;
		else if (a3 <= 99999)				v12 = 28.0f;
		else if (a3 <= 999999)				v12 = 30.0f;
		else if (a3 <= 9999999)				v12 = 32.0f;
		else if (a3 <= 99999999)			v12 = 34.0f;
		else if (a3 <= 999999999)			v12 = 36.0f;
		else if (a3 <= 999999999)			v12 = 38.0f;
		else if (a3 <= 2147000000)			v12 = 40.0f;
		else								v12 = 42.0f;
	}
	else if (a5 == 3) //Center
	{
		if (a3 >= 0.0 && a3 <= 9.0)			v12 = 4.0f;
		else if (a3 <= 99.0)                v12 = 3.8f;
		else if (a3 <= 999.0)               v12 = 3.6f;
		else if (a3 <= 9999.0)              v12 = 3.4f;
		else if (a3 <= 99999.0)				v12 = 3.2f;
		else if (a3 <= 999999.0)            v12 = 3.0f;
		else if (a3 <= 9999999.0)			v12 = 2.8f;
		else if (a3 <= 99999999.0)			v12 = 1.4f;
		else if (a3 <= 999999999.0)			v12 = 2.4f;
		else if (a3 <= 2147000000.0)		v12 = 2.2f;
		else                                v12 = 2.0f;
	}
	else if (a5 == 4) //Right AddPoint
	{
		if (a3 >= 0 && a3 <= 9)				v12 = 20.0f;
		else if (a3 <= 99)					v12 = 21.0f;
		else if (a3 <= 999)					v12 = 22.0f;
		else if (a3 <= 9999)				v12 = 23.0f;
		else if (a3 <= 99999)				v12 = 24.0f;
		else if (a3 <= 999999)				v12 = 25.0f;
		else if (a3 <= 9999999)				v12 = 26.0f;
		else if (a3 <= 99999999)			v12 = 27.0f;
		else if (a3 <= 999999999)			v12 = 28.0f;
		else if (a3 <= 999999999)			v12 = 29.0f;
		else if (a3 <= 2147000000)			v12 = 30.0f;
		else								v12 = 20.0f;
	}
	EnableAlphaTest(1);
	glColor4f(50, 50, 50, 190);

	if (Scale >= 0.300000011920929)
	{
		v8 = (Scale - 0.4800000119209290) * 12.0;
		_snprintf(v10, sizeof(v10), "%.0f", a3);
		v9 = strlen(v10);
		v11 = a1 - (double)v9 * v8 / 2.0;
		for (i = 0; i < v9; ++i)
		{
			v6 = (double)(v10[i] - 48) * 12.0 / 128.0;
			v5 = (Scale - 0.400000011920929) * 14.0;
			RenderBitmap(BG_IMG_NUM2, v11 - v12, a2, v8, v5, v6, 0.0, 0.09375, 0.875, 1, 1, 0.0);
			v11 = v8 * 0.800000011920929 + v11;
		}
		result = v11;
	}
	else
	{
		result = a1;
	}
	pGLSupremo();
	return result;
}

void TAS_ToolKitMain::RunAntiHack()
{
	if (SKILL_001)
	{
		MessageBoxW(NULL, L"Phát hiện tốc độ bất thường. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}
	if (SKILL_002)
	{
		MessageBoxW(NULL, L"Phát hiện skill hồi phục bất thường. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}
	if (SKILL_003)

	{
		MessageBoxW(NULL, L"Phát hiện sát thương không ổn định. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}
	if (SKILL_004)
	{
		MessageBoxW(NULL, L"Phát hiện tốc độ di chuyển không đúng. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}
	if (SKILL_005)
	{
		MessageBoxW(NULL, L"Không nhận diện được bị choáng, giật lùi của hiệu ứng. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}
	if (SKILL_006)
	{
		MessageBoxW(NULL, L"Không nhận diện được hiệu ứng. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}
	if (SKILL_007)
	{
		MessageBoxW(NULL, L"Phát hiện Hit bất thường. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}
	if (SKILL_008)
	{
		MessageBoxW(NULL, L"Phát hiện đanh liền skill bất thường. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}
	if (SKILL_009)
	{
		MessageBoxW(NULL, L"Phát hiện ra đòn không đúng vị trí. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}
	if (SKILL_010)
	{
		MessageBoxW(NULL, L"Phát hiện Hit bất thường. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}
	if (SKILL_011)
	{
		MessageBoxW(NULL, L"Phát hiện cỡi sói bất thường. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}

	if (SKILL_012)
	{
		MessageBoxW(NULL, L"Phát hiện tốc đánh bất thường. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}

	if (SKILL_013)
	{
		MessageBoxW(NULL, L"Phát hiện Hit bất thường. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}

	if (SKILL_014)
	{
		MessageBoxW(NULL, L"Phát hiện tốc độ tấn công không đúng. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}
	if (SKILL_015)
	{
		MessageBoxW(NULL, L"Phát hiện sát thương bất thường. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}
	if (SKILL_016)
	{
		MessageBoxW(NULL, L"Phát hiện tốc độ bất thường. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}
	if (SKILL_017)
	{
		MessageBoxW(NULL, L"Phát hiện đánh quá xa giới hạn. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}

	if (SKILL_018)
	{
		MessageBoxW(NULL, L"Phát hiện hành động bị loại bỏ. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR); ExitProcess(0);
	}
}
