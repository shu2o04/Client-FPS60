#pragma once
std::string FormatNumber(float value);
signed int __cdecl ColorMoneys(unsigned int a1);
#define GET_ITEMOPT_LEVEL(x)		((x >> 3) & 0xF)
class TAS_ToolKitMain
{
	public:
	enum GetColor
	{
		YellowGold	= RGB(255, 255, 000),
		Exicellent	= RGB(000, 225, 139),
		BlueMin		= RGB(036, 242, 252),
		GreenMin	= RGB(172, 255, 056),
	};
	void MakeShadowText(int X, int Y, int W, int Pos, LPCSTR String,...);
	char* QNumberFormat(QWORD Number);
	char* NumberFormat(DWORD Number);
	float RenderExNumberLevel2(float x, float y, int iNum, int iNum1, float fScale);
	void RunAntiHack();
	void DrawButtonIcon(int Enum, int ImgID, float X, float Y, float W, float H, LPCSTR Text);
	float CRenderNumberClassic(BYTE Color, float x, float y, int iNum, float fScale);
	double CRenderNumberExNew(float a1, float a2, double a3, int a5, float Scale);
	double CRenderNumberEx(float a1, float a2, double a3, float a4, DWORD ModelID);
	double CRenderNumberExBank(float a1, float a2, int a3, float a4, DWORD ModelID);
	void CreateFontNew(int X, int Y, int W, int Pos, int Size, int Bold, LPCSTR String, COLORREF TextColor, HFONT CrateSub);
	char* TAS_ToolKitMain::BGetItemName(int ItemType, int Level);
	void TAS_ToolKitMain::RenderMixEffect(int type, int x, int y, int w, int h );
	void DrawButtonIconRank(int Enum, int ImgID, float X, float Y, float W, float H, LPCSTR Text);
	void TAS_ToolKitMain::CloseButton(float X, float Y, int Enum);
	void TAS_ToolKitMain::DrawButtonIconMove(int Enum, int ImgID, float X, float Y, float W, float H);
};
extern TAS_ToolKitMain gToolKit;

