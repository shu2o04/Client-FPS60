#pragma once

#define Offset_CreateFontA1 0x004060D0
#define Offset_CreateFontA2 0x004D2882
#define Offset_CreateFontA3 0x004D28EB
#define Offset_CreateFontA4 0x004D2957
#define Offset_CreateFontA5 0x004D29C1


#define pFontNormal * (HGDIOBJ *) 0x00E8C588
#define pFontBold * (HGDIOBJ * ) 0x00E8C58C
#define pFontBigBold * (HGDIOBJ *) 0x00E8C590
#define pFontNormal2 * (HGDIOBJ *) 0x00E8C594

class Font{
public:
	Font(){};
	~Font(){};
	void Load();
	HFONT LoadNewFont();
	HFONT LoadNewFont2();
	HFONT LoadNewFont3();
	HFONT LoadNewFont4();
	HFONT FontBSize[30];
	HFONT FontSize[30];
	void FontSizeLoad(int a1);

}; extern Font gFont;
