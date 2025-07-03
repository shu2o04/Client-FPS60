#pragma once
void InitLoad();
class SuperKhung
{
public:
	float Level_X, Level_Y, Level_S;
	float Master_X, Master_Y, Master_S;
	float ResetCount_X, ResetCount_Y, ResetCount_S;
	float LevelUpPoint_X, LevelUpPoint_Y, LevelUpPoint_S;
	float WcoinC_X, WcoinC_Y, WcoinC_S;
	int mCharClass;
	int ChieuDaiChar, ChieuCaoChar, ToaDoXChar, ToaDoYChar;
	int ChieuDaiBg, ChieuCaoBg, ToaDoXBg, ToaDoYBg;

	float pPlayPos_X1, pPlayPos_Y1, pPlayPos_S1;
	float pPlayPos_X2, pPlayPos_Y2, pPlayPos_S2;
	void HienThiKhuonNhanVat();
	void LoadImg();
};
extern SuperKhung mTAS;
