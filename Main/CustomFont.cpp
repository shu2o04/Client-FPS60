#include "stdafx.h"
#include "CustomFont.h"
#include "Interface.h"

eCustomFont CustomFont;

void eCustomFont::load() {
	DWORD Width = 0;
	DWORD Italic = 0;
	DWORD UnderLine = 0;
	DWORD StrikeOut = 0;
	DWORD Quality = 3;

	this->FontNormal = CreateFontA(13, Width, 0, 0, 400, Italic, UnderLine, StrikeOut, 0x1, 0, 0, Quality, 0, "Verdana");
	this->FontBold = CreateFontA(13, Width, 0, 0, 700, Italic, UnderLine, StrikeOut, 0x1, 0, 0, Quality, 0,   "Verdana");
	this->FontSize15 = CreateFontA(15, Width, 0, 0, 400, Italic, UnderLine, StrikeOut, 0x1, 0, 0, Quality, 0, "Verdana");
	this->FontSize18 = CreateFontA(18, Width, 0, 0, 400, Italic, UnderLine, StrikeOut, 0x1, 0, 0, Quality, 0, "Verdana");
	this->FontSize19 = CreateFontA(19, Width, 0, 0, 400, Italic, UnderLine, StrikeOut, 0x1, 0, 0, Quality, 0, "Verdana");
	this->FontSize20 = CreateFontA(20, Width, 0, 0, 700, Italic, UnderLine, StrikeOut, 0x1, 0, 0, Quality, 0, "Verdana");
	this->FontSize20 = CreateFontA(25, Width, 0, 0, 700, Italic, UnderLine, StrikeOut, 0x1, 0, 0, Quality, 0, "Verdana");
	this->FontSize20 = CreateFontA(30, Width, 0, 0, 700, Italic, UnderLine, StrikeOut, 0x1, 0, 0, Quality, 0, "Verdana");
	this->FontSize20 = CreateFontA(35, Width, 0, 0, 700, Italic, UnderLine, StrikeOut, 0x1, 0, 0, Quality, 0, "Verdana");
}

eColor eCustomFont::SinWaveColor(float frc1, float frc2, float frc3, BYTE phs1, BYTE phs2, BYTE phs3, BYTE center, BYTE width, BYTE step) {
	eColor result;

	result.red = std::sin(frc1*step + phs1) * width + center;
	result.grn = std::sin(frc2*step + phs2) * width + center;
	result.blu = std::sin(frc3*step + phs3) * width + center;
	result.opl = 0xff;
	return result;
}

void eCustomFont::Draw(HFONT font, int PosX, int PosY, DWORD color, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...) {
	char Buff[2048];
	int BuffLen = sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	int LineCount = 0;

	char * Line = strtok(Buff, "\n");

	while (Line != NULL)
	{
		pSetTextSize2(pTextThis2(), font);
		pSetTextColor2(pTextThis2(), (color & 0xff000000) >> 24, (color & 0x00ff0000) >> 16, (color & 0x0000ff00) >> 8, color & 0x000000ff);
		pSetBackgroundTextColor2(pTextThis2(), (bkcolor & 0xff000000) >> 24, (bkcolor & 0x00ff0000) >> 16, (bkcolor & 0x0000ff00) >> 8, bkcolor & 0x000000ff);
		pDrawText2(pTextThis2(), PosX, PosY, Line, Width, Height, (LPINT)Align, 0);
		PosY += 10;
		Line = strtok(NULL, "\n");
	}
}

void eCustomFont::DrawMultipleColor(HFONT font, int PosX, int PosY, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...) {
	char Buff[2048];
	int BuffLen = sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	int LineCount = 0;

	char * Line = strtok(Buff, "\n");
	BYTE len = strlen(Line);

	char filter[10];
	char bufer[255];
	while (Line != NULL)
	{
		pSetTextSize2(pTextThis2(), font);

		pSetBackgroundTextColor2(pTextThis2(), (bkcolor & 0xff000000) >> 24, (bkcolor & 0x00ff0000) >> 16, (bkcolor & 0x0000ff00) >> 8, bkcolor & 0x000000ff);
		for (BYTE i = 0; i < len; i++) {
			eColor mColor = CustomFont.SinWaveColor(0.1f, 0.1f, 0.1f, 0, 2, 4, 128, 127, i + GetTickCount() / 100 % 255);
			pSetTextColor2(pTextThis2(), mColor.red, mColor.grn, mColor.blu, mColor.opl);
			sprintf(filter, "%%.%ds", len - i);
			sprintf(bufer, filter, Line);
			pDrawText2(pTextThis2(), PosX, PosY, bufer, Width, Height, (LPINT)Align, 0);
		}
		PosY += 10;
		Line = strtok(NULL, "\n");
	}
}