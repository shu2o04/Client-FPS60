#include "stdafx.h"
#include "Object.h"

// Fix Agilidad
void InitAttackSpeed();
//------------------------------------

class cFix
{
public:
	void Load();
	static void CalculateAttackSpeed(lpCharObj lpUser, LPVOID EDX);
private:

};
extern cFix gFix;
