
//customfont.
#define pTextThis2				((LPVOID(*)()) 0x0041FE10)
#define pTextFormat2				((int(__cdecl*)(char * Buffer, int Arg2, int LineSize, LPCTSTR Text, int LineWidth, bool Arg6, BYTE Arg7)) 0x540880)
#define pDrawColorText2			((int(__cdecl*)(LPCTSTR Text, int PosX, int PosY, int Width, int Arg5, int Color, int Arg7, int Align)) 0x7D0380)
#define pGetTextLine2			((LPCSTR(__thiscall*)(LPVOID This, int LineNumber)) 0x00402320)
#define pMakeColor2				((DWORD(__cdecl*)(BYTE, BYTE, BYTE, BYTE)) 0x00412D20)
#define pSetTextColor2			((void(__thiscall*)(LPVOID This, int r, int g, int b, int h)) 0x00420040)
#define pSetBackgroundTextColor2	((void(__thiscall*)(LPVOID This, int r, int g, int b, int h)) 0x004200B0)
#define pSetTextSize2			((int(__thiscall*)(LPVOID This, HFONT a2)) 0x00420120)
#define pSetTextFont2			((int(__thiscall*)(LPVOID This, HFONT a2)) 0x00420120)
#define pDrawText2				((int(__thiscall*)(LPVOID This, int PosX, int PosY, LPCTSTR Text, int Width, int Height, LPINT Align, int unknow)) 0x00420150)
#define pUnknow00420080			((DWORD(__cdecl*)(LPVOID This, char Arg1)) 0x00420080)
#define pUnknow004200F0		((DWORD(__cdecl*)(LPVOID This, char Arg1)) 0x004200F0)
#define pSetBlend2				((void(__cdecl*)(BYTE Mode)) 0x635FD0)
#define pGetTextNumber2			((int(__cdecl*)(int a1))0x009CFF45)	

struct eColor {
	BYTE red;
	BYTE grn;
	BYTE blu;
	BYTE opl;
};

class eCustomFont
{
	public:
	void load();
	void Draw(HFONT font, int PosX, int PosY, DWORD color, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...);
	void DrawMultipleColor(HFONT font, int PosX, int PosY, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...);
	eColor	SinWaveColor(float frc1, float frc2, float frc3, BYTE phs1, BYTE phs2, BYTE phs3, BYTE center, BYTE width, BYTE step);

	HFONT	FontNormal;
	HFONT	FontBold;
	HFONT	FontSize15;
	HFONT	FontSize18;
	HFONT   FontSize19;
	HFONT   FontSize20;
	HFONT   FontSize25;
	HFONT   FontSize30;
	HFONT   FontSize35;
};
extern eCustomFont CustomFont;