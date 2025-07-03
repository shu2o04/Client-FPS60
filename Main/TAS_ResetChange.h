#if (RESETCHANGE==1)
#pragma once
#include "Protocol.h"
struct RESETCHANGE_REQ
{
	PSBMSG_HEAD h;
	int	numchange;
};

class CResetChange
{
	public:
	void		DrawResetChange();
	void        OpenResetChange();
	void        ButtonResetChange(DWORD Event);
	void		ResetChange(int numchange);
};
extern CResetChange gResetChange;
#endif