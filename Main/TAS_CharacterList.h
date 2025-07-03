#define ScreenSize	*(int*)0x00E8C240
class TASCharacterList
{
	public:
	void StatusInfo(float X,float Y,int a1, float a2);
	void TAS_CharInfoLoad(int X, int Y, int mHeroID );
	void SelectChar();
	void ImgLoad();
	void GetPosForm();
	int FormW, FormH;
	float AddX, AddY;
};
extern TASCharacterList gCharList;