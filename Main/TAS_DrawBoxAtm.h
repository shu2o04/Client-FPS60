#pragma once
#include "Interface.h"
class IsBoxAtm
{
	public:
		void DrawAtmWork();
		void DrawBoxAtm();
		void OpenDrawBoxAtm() 
		{ 
			gInterface.Data[ATM_BOX_MAIN].OnShow = true;
		};
};
extern IsBoxAtm gBoxAtm;