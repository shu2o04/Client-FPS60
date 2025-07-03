#include "stdafx.h"
#if(ADD_POINT)
#include "Interface.h"
#include "TAS_CongPoint.h"
#include "User.h"
#include "Defines.h"
#include "PrintPlayer.h"
#include "TAS_ChangePass.h"
#include "Config.h"
#include "Central.h"
#include "TAS_ToolKit.h"
#include "UIControl.h"
#include "CustomFont.h"
#include "WideScreen.h"

TASAddPoint gAddPoint;

// Thêm biến lưu tick cho AutoHP
static DWORD s_AutoHP_Tick = 0;

// Đảm bảo đúng kiểu dữ liệu, ViewCurHP/ViewMaxHP thường là DWORD trong client Mu
extern DWORD ViewCurHP;
extern DWORD ViewMaxHP;

void TASAddPoint::BingObjectRenderAddPoint()
{
	gInterface.BindObject(eSTATSADD_MAIN, 0x7A5A, 222, 226, -1, -1);
	gInterface.BindObject(eSTATSADD_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eSTATSADD_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eSTATSADD_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eSTATSADD_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(eSTATSADD_TEXTBOX01, 0x9307, 170, 21, -1, -1);
	gInterface.BindObject(eSTATSADD_STATBOX01, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eSTATSADD_STATBOX02, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eSTATSADD_STATBOX03, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eSTATSADD_STATBOX04, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eSTATSADD_STATBOX05, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eSTATSADD_BTN_OK, 0x7A5B, 54, 30, -1, -1);
	gInterface.BindObject(eRESETSTATS_MAIN, 0x7A5A, 222, 140, -1, -1);
	gInterface.BindObject(eRESETSTATS_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eRESETSTATS_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eRESETSTATS_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eRESETSTATS_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(eRESETSTATS_POINT, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eRESETSTATS_BTN_OK, 0x7A5B, 54, 30, -1, -1);
	gInterface.BindObject(eCHARINFO_BTN_STAT, 0x7AA4, 16, 15, -1, -1); // Vị trí X, Y sẽ được tính toán lại lúc vẽ
	gInterface.BindObject(eCHARINFO_BTN_AUTOHP, 0x7AA4, 16, 15, -1, -1); // Vị trí X, Y sẽ được tính toán lại lúc vẽ
	gInterface.BindObject(eCHARINFO_BTN_RESSTAT, 0x7AA4, 16, 15, -1, -1); // Vị trí X, Y sẽ được tính toán lại lúc vẽ
	gInterface.BindObject(eCHARINFO_BTN_FAKE, 0x7AA3, 170, 21, -1, -1);
}

void TASAddPoint::GetFormat(char* str, char oldval, char newval)
{
	std::string Buff;
	Buff = str;
	std::replace(Buff.begin(), Buff.end(), oldval, newval);
	memcpy(str, Buff.c_str(), Buff.size());
}

void TASAddPoint::DrawColoredAnimatedGUI(short ObjectID, float X, float Y, DWORD Color)
{
	gInterface.Data[ObjectID].X = X;
	gInterface.Data[ObjectID].Y = Y;
	gInterface.Data[ObjectID].MaxX = X + gInterface.Data[ObjectID].Width;
	gInterface.Data[ObjectID].MaxY = Y + gInterface.Data[ObjectID].Height;
	pDrawColorButton(gInterface.Data[ObjectID].ModelID, X, Y,
		gInterface.Data[ObjectID].Width, gInterface.Data[ObjectID].Height, 0, 0, Color);
}

void TASAddPoint::DrawAnimatedButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	gInterface.Data[ObjectID].X = PosX;
	gInterface.Data[ObjectID].Y = PosY;
	gInterface.Data[ObjectID].MaxX = PosX + gInterface.Data[ObjectID].Width;
	gInterface.Data[ObjectID].MaxY = PosY + gInterface.Data[ObjectID].Height;
	pDrawButton(gInterface.Data[ObjectID].ModelID, PosX, PosY,
		gInterface.Data[ObjectID].Width, gInterface.Data[ObjectID].Height, ScaleX, ScaleY);
}

void TASAddPoint::DrawStatsAddWindow()
{
	if (!gInterface.Data[eSTATSADD_MAIN].OnShow)
	{
		return;
	}
	if (gInterface.CheckWindow(ChatWindow))
	{
		this->CloseStatsAddWindow();
		return;
	}
	int ObjectCount = 4;
	if ((gObjUser.lpPlayer->Class & 7) == 4)
	{
		ObjectCount = 5;
	}
	char szCharNames[5][32];
	memcpy(szCharNames[0], gConfig.TTAS_TEXT_ENGINE[270], sizeof(szCharNames[0]));
	memcpy(szCharNames[1], gConfig.TTAS_TEXT_ENGINE[271], sizeof(szCharNames[1]));
	memcpy(szCharNames[2], gConfig.TTAS_TEXT_ENGINE[272], sizeof(szCharNames[2]));
	memcpy(szCharNames[3], gConfig.TTAS_TEXT_ENGINE[273], sizeof(szCharNames[3]));
	memcpy(szCharNames[4], gConfig.TTAS_TEXT_ENGINE[274], sizeof(szCharNames[4]));
	int ObjectIDs[5] =
	{
		eSTATSADD_STATBOX01,
		eSTATSADD_STATBOX02,
		eSTATSADD_STATBOX03,
		eSTATSADD_STATBOX04,
		eSTATSADD_STATBOX05,
	};

	if (gInterface.Data[eSTATSADD_MAIN].ByClose == false)
	{
		if (gInterface.Data[eSTATSADD_MAIN].OpenedValue < 0)
		{
			gInterface.Data[eSTATSADD_MAIN].OpenedValue += gInterface.Data[eSTATSADD_MAIN].Speed;

			if (gInterface.Data[eSTATSADD_MAIN].OpenedValue >= -150)
			{
				gInterface.Data[eSTATSADD_MAIN].Speed = 15;
			}

			if (gInterface.Data[eSTATSADD_MAIN].OpenedValue > 0)
			{
				gInterface.Data[eSTATSADD_MAIN].OpenedValue = 0;
			}
		}
	}
	else
	{
		if (gInterface.Data[eSTATSADD_MAIN].OpenedValue > -226)
		{
			gInterface.Data[eSTATSADD_MAIN].OpenedValue -= gInterface.Data[eSTATSADD_MAIN].Speed;

			if (gInterface.Data[eSTATSADD_MAIN].OpenedValue <= -150)
			{
				gInterface.Data[eSTATSADD_MAIN].Speed = 20;
			}

			if (gInterface.Data[eSTATSADD_MAIN].OpenedValue <= -226)
			{
				gInterface.Data[eSTATSADD_MAIN].Close();
				for (int i = 0; i < ObjectCount; i++)
				{
					gInterface.Data[ObjectIDs[i]].Attribute = false;
				}
			}
		}
	}

	float MainWidth = 230.0f;
	float MainHeight = 226.0f;
	// Widescreen fix: use QTFrame.DisplayWin for correct centering
	float StartX = (QTFrame.DisplayWin / 2.0f) - (MainWidth / 2.0f) + gInterface.Data[eSTATSADD_MAIN].OpenedValue;
	float StartY = (QTFrame.DisplayHeight / 2.0f) - (MainHeight / 2.0f);

	float MainCenter = StartX + (MainWidth / 2.0f);
	float ButtonX = MainCenter - 85.0f;

	pSetCursorFocus = true;
	gInterface.DrawAnimatedGUI(eSTATSADD_MAIN, StartX, StartY + 2);
	gInterface.DrawAnimatedGUI(eSTATSADD_TITLE, StartX, StartY);
	float TempY = gInterface.DrawRepeatGUI(eSTATSADD_FRAME, StartX, StartY + 67.0, 8);
	gInterface.DrawAnimatedGUI(eSTATSADD_FOOTER, StartX, TempY);
	gInterface.DrawAnimatedGUI(eSTATSADD_CLOSE, StartX + MainWidth - gInterface.Data[eSTATSADD_CLOSE].Width, StartY - 2);
	if (gInterface.IsWorkZone(eSTATSADD_CLOSE))
	{
		DWORD Color = eGray100;
		if (gInterface.Data[eSTATSADD_CLOSE].OnClick)
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eSTATSADD_CLOSE, gInterface.Data[eSTATSADD_CLOSE].X, gInterface.Data[eSTATSADD_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[eSTATSADD_CLOSE].X + 5, gInterface.Data[eSTATSADD_CLOSE].Y + 25, gConfig.TTAS_TEXT_ENGINE[26]);
	}
	this->StatPoints = ViewPoint;

	for (int i = 0; i < ObjectCount; i++)
	{
		this->StatPoints -= atoi(gInterface.Data[ObjectIDs[i]].StatValue);
	}
	gInterface.DrawFormat(eGold, StartX + 10, StartY + 8, 210, 3, gConfig.TTAS_TEXT_ENGINE[275]);

	gCentral.gInfoBox(StartX + 25, StartY + 30, 180, 10, 0x00000096, 0, 0);
	gInterface.DrawFormat(eWhite, StartX + 10, StartY + 34, 210, 3, gConfig.TTAS_TEXT_ENGINE[276]);

	gToolKit.CRenderNumberExNew(StartX + 200, StartY + 35, this->StatPoints, 4, 1.08);
	gInterface.DrawFormat(eWhite, StartX + 10, StartY + 65, 210, 3, gConfig.TTAS_TEXT_ENGINE[277]);

	if (gInterface.Data[eSTATSADD_MAIN].FirstLoad == true)
	{
		gInterface.Data[eSTATSADD_STATBOX01].Attribute = 1;
	}

	for (int i = 0; i < ObjectCount; i++)
	{
		if (gInterface.Data[eSTATSADD_MAIN].FirstLoad == true)
		{
			sprintf(gInterface.Data[ObjectIDs[i]].StatValue, "0");
		}
		double statValue = atof(gInterface.Data[ObjectIDs[i]].StatValue);

		gInterface.DrawAnimatedGUI(ObjectIDs[i], StartX + 30, StartY + 63 + ((i + 1) * 21));
		gInterface.DrawFormat(eWhite, StartX + 35, StartY + 65 + ((i + 1) * 21), 210, 1, szCharNames[i]);
		gToolKit.CRenderNumberExNew(StartX + 170, StartY + 70 + ((i + 1) * 21), statValue, 4, 1.08);
	}

	for (int i = 0; i < ObjectCount; i++)
	{
		if (gInterface.Data[ObjectIDs[i]].Attribute == 1)
		{
			DWORD Color = eGray100;
			this->DrawColoredAnimatedGUI(ObjectIDs[i], StartX + 30, StartY + 63 + ((i + 1) * 21), Color);
		}
	}

	this->DrawAnimatedButton(eSTATSADD_BTN_OK, StartX + 88, StartY + 194, 0, 0);

	if (gInterface.IsWorkZone(eSTATSADD_BTN_OK))
	{
		int ScaleY = 30;
		if (gInterface.Data[eSTATSADD_BTN_OK].OnClick)
		{
			ScaleY = 60;
		}
		this->DrawAnimatedButton(eSTATSADD_BTN_OK, StartX + 88, StartY + 194, 0, ScaleY);
	}

	if (gInterface.Data[eSTATSADD_MAIN].FirstLoad == true)
	{
		gInterface.Data[eSTATSADD_MAIN].FirstLoad = false;
	}
}

void TASAddPoint::EventStatsAddWindow(DWORD Event)
{
	this->EventStatsAddWindow_Close(Event);
}

void TASAddPoint::EventStatsAddWindow_Close(DWORD Event)
{
	if (!gInterface.Data[eSTATSADD_MAIN].OnShow)
	{
		return;
	}

	DWORD CurrentTick = GetTickCount();

	int ObjectIDs[5] =
	{
		eSTATSADD_STATBOX01,
		eSTATSADD_STATBOX02,
		eSTATSADD_STATBOX03,
		eSTATSADD_STATBOX04,
		eSTATSADD_STATBOX05,
	};

	int ObjectCount = 4;
	if ((gObjUser.lpPlayer->Class & 7) == 4)
	{
		ObjectCount = 5;
	}

	for (int i = 0; i < ObjectCount; i++)
	{
		if (gInterface.IsWorkZone(ObjectIDs[i]))
		{
			DWORD Delay = (CurrentTick - gInterface.Data[ObjectIDs[i]].EventTick);
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[ObjectIDs[i]].OnClick = true;
				return;
			}
			gInterface.Data[ObjectIDs[i]].OnClick = false;
			if (Delay < 500)
			{
				return;
			}
			gInterface.Data[ObjectIDs[i]].EventTick = GetTickCount();

			for (int j = 0; j < ObjectCount; j++)
			{
				gInterface.Data[ObjectIDs[j]].Attribute = 0;
			}

			gInterface.Data[ObjectIDs[i]].Attribute = 1;
		}
	}

	if (gInterface.IsWorkZone(eSTATSADD_BTN_OK))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eSTATSADD_BTN_OK].EventTick);
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eSTATSADD_BTN_OK].OnClick = true;
			return;
		}
		gInterface.Data[eSTATSADD_BTN_OK].OnClick = false;
		if (Delay < 500)
		{
			return;
		}
		gInterface.Data[eSTATSADD_BTN_OK].EventTick = GetTickCount();
		gInterface.Data[eSTATSADD_MAIN].CloseAnimated(15);
		PMSG_UPDATE_STATS_SEND pMsg;
		pMsg.Str = atoi(gInterface.Data[eSTATSADD_STATBOX01].StatValue);
		pMsg.Agi = atoi(gInterface.Data[eSTATSADD_STATBOX02].StatValue);
		pMsg.Vit = atoi(gInterface.Data[eSTATSADD_STATBOX03].StatValue);
		pMsg.Ene = atoi(gInterface.Data[eSTATSADD_STATBOX04].StatValue);
		pMsg.Com = 0;
		if (ObjectCount == 5)
		{
			pMsg.Com = atoi(gInterface.Data[eSTATSADD_STATBOX05].StatValue);
		}
		this->CGSendStatsAdd(pMsg);
	}

	if (gInterface.IsWorkZone(eSTATSADD_CLOSE))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eSTATSADD_CLOSE].EventTick);
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eSTATSADD_CLOSE].OnClick = true;
			return;
		}
		gInterface.Data[eSTATSADD_CLOSE].OnClick = false;
		if (Delay < 500)
		{
			return;
		}
		gInterface.Data[eSTATSADD_CLOSE].EventTick = GetTickCount();
		gInterface.Data[eSTATSADD_MAIN].CloseAnimated(15);
	}
	return;
}
void SekcPacketPointAdd(DWORD CurrentTick, DWORD Event, int eNum, int Packet)
{
	DWORD Delay = (CurrentTick - gInterface.Data[eNum].EventTick);

	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eNum].OnClick = true;
		return;
	}
	gInterface.Data[eNum].OnClick = false;
	if (Delay < 500)
	{
		return;
	}
	gInterface.Data[eNum].EventTick = GetTickCount();
	PMSG_TICKET_SEND pMsg;
	pMsg.header.set(0xFC, Packet, sizeof(pMsg));
	DataSend((BYTE*)&pMsg, pMsg.header.size);
}
void TASAddPoint::EventCharacterWindow(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	if (!gInterface.CheckWindow(Character))
	{
		return;
	}
	if (gInterface.IsWorkZone(eCHARINFO_BTN_STAT))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eCHARINFO_BTN_STAT].EventTick);

		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eCHARINFO_BTN_STAT].OnClick = true;
			return;
		}
		gInterface.Data[eCHARINFO_BTN_STAT].OnClick = false;
		if (Delay < 500)
		{
			return;
		}
		gInterface.Data[eCHARINFO_BTN_STAT].EventTick = GetTickCount();

		if (ViewPoint != 0)
		{
			this->SwitchStatsWindowState();
		}
		else
		{
			pDrawMessage("Bạn không đủ Point dư để cộng.", 1);
		}
	}

	// --- Auto HP Button Toggle ---
	if (gInterface.IsWorkZone(eCHARINFO_BTN_AUTOHP))
	{
		AutoHP_Tick(Event);

		DWORD Delay = (CurrentTick - gInterface.Data[eCHARINFO_BTN_AUTOHP].EventTick);
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eCHARINFO_BTN_AUTOHP].OnClick = true;
			return;
		}
		gInterface.Data[eCHARINFO_BTN_AUTOHP].OnClick = false;
		if (Delay < 500)
		{
			return;
		}
		gInterface.Data[eCHARINFO_BTN_AUTOHP].EventTick = GetTickCount();
		m_AUTOHP = !m_AUTOHP;
		if (m_AUTOHP)
		{
			//pDrawMessage("Auto HP: Đã BẬT", 1);
		}
		else
		{
			//pDrawMessage("Auto HP: Đã TẮT", 1);
		}
	}

	// Gọi tick AutoHP mỗi frame
	AutoHP_Tick(Event);

	if (gInterface.IsWorkZone(eCHARINFO_BTN_RESSTAT))
	{
		SekcPacketPointAdd(CurrentTick, Event, eCHARINFO_BTN_RESSTAT, 101);
	}
}

void TASAddPoint::AutoHP_Tick(DWORD Event)
{
    if (!m_AUTOHP) return;

    // Sử dụng ViewCurHP và ViewMaxHP kiểu DWORD (theo PrintPlayer.h)
    extern DWORD ViewCurHP;
    extern DWORD ViewMaxHP;

    // Luôn lấy phần trăm máu là 99
    int percent = 99;

    if (ViewMaxHP <= 0) return;
    if (ViewCurHP >= (ViewMaxHP * percent / 100)) return;

    DWORD now = GetTickCount();
    if (now - s_AutoHP_Tick < 1000) // 1s delay
        return;
    s_AutoHP_Tick = now;

    PMSG_TICKET_SEND pMsg;
    pMsg.header.set(0xFC, 103, sizeof(pMsg)); // Bom mau Send
    DataSend((BYTE*)&pMsg, pMsg.header.size);
}

void TASAddPoint::EventResetStatsWindow_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eRESETSTATS_CLOSE].EventTick);
	if (!gInterface.Data[eRESETSTATS_MAIN].OnShow || !gInterface.IsWorkZone(eRESETSTATS_CLOSE))
	{
		return;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eRESETSTATS_CLOSE].OnClick = true;
		return;
	}
	gInterface.Data[eRESETSTATS_CLOSE].OnClick = false;
	if (Delay < 500)
	{
		return;
	}
	gInterface.Data[eRESETSTATS_CLOSE].EventTick = GetTickCount();
	this->SwitchResetStatsWindowState();
}

void TASAddPoint::CGSendStatsAdd(PMSG_UPDATE_STATS_SEND pMsg)
{
	pMsg.header.set(0xFF, 0x0C, sizeof(pMsg));
	DataSend((BYTE*)&pMsg, pMsg.header.size);
}

void TASAddPoint::ExtraCpanelGetInfo(EXTRA_CPANEL_SENDINFO* lpMsg)
{
	this->m_QuickAdd = lpMsg->QuickAdd;
	this->m_ResetStats = lpMsg->ResetStat;
	this->m_AUTOHP = lpMsg->AutoHP;

	this->d_Strength = lpMsg->dStrength;
	this->d_Dexterity = lpMsg->dDexterity;
	this->d_Vitality = lpMsg->dVitality;
	this->d_Energy = lpMsg->dEnergy;
	this->d_Leadership = lpMsg->dLeadership;

	for (int i = 0; i < MAX_ACCOUNT_LEVEL; i++)
	{
		this->m_MaxStatPoint[i] = lpMsg->MaxStatPoint[i];
	}
}
#define getCharacterInfo ((int(__thiscall*)(int This))0x00861440)
#define sub_779410 ((int(__thiscall*)(char *This, int X, int Y, int Width, int Height)) 0x00779410)
void TASAddPoint::ChangeCharInfo(LPVOID This)
{
	if (!gInterface.CheckWindow(Character))
	{
		return;
	}

	int ThisNew = getCharacterInfo((int)pWindowThis());
	float x = (double)*(signed int*)(ThisNew + 16);
	float y = (double)*(signed int*)(ThisNew + 20);

	float ButtonX = x + 20;
	int v639 = pGetCharClass(*(BYTE*)(*(DWORD*)0x7BC4F04 + 19));

	float AddX;
	int BtnW, BtnH;
	float IsY;

	if (gInterface.Data[eSTATSADD_MAIN].OnShow == true)
	{
		if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 4)
		{
			AddX = 172.0f;
			BtnW = 16;
			BtnH = 15;
			IsY = y;
		}
		else
		{
			AddX = 3040;
			BtnW = 24;
			BtnH = 24;
			IsY = y - 4;
		}
	}
	else
	{
		if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 4)
		{
			AddX = 72.0f;
			BtnW = 16;
			BtnH = 15;
			IsY = y;
		}
		else
		{
			AddX = 40;
			BtnW = 24;
			BtnH = 24;
			IsY = y - 4;
		}
	}

	sub_779410((char*)(ThisNew + 24), x + AddX, IsY + 120 + 2, BtnW, BtnH);
	sub_779410((char*)(ThisNew + 196), x + AddX, IsY + 175 + 2, BtnW, BtnH);
	sub_779410((char*)(ThisNew + 368), x + AddX, IsY + 240 + 2, BtnW, BtnH);
	sub_779410((char*)(ThisNew + 540), x + AddX, IsY + 295 + 2, BtnW, BtnH);

	if (v639 == 4)
	{
		sub_779410((char*)(ThisNew + 712), x + AddX, IsY + 350 + 2, 16, 15);
	}

	gInterface.DrawFormat(eGold, ButtonX, 56, 100, 1, gConfig.TTAS_TEXT_ENGINE[283], gObjUser.lpPlayer->Level, ViewReset);
	if (ViewPoint > 0)
	{
		gInterface.TASText(eYelloCam, ButtonX+70, 56, 100, 3, "Điểm: %d", ViewPoint);
	}

	if (gAddPoint.m_QuickAdd == 1)
	{
		gInterface.DrawButton(eCHARINFO_BTN_STAT, ButtonX, 73, 0, 0);
		gToolKit.MakeShadowText(ButtonX + 19, 76, 100, 1, gConfig.TTAS_TEXT_ENGINE[284]); // "Cộng điểm"
		if (gInterface.IsWorkZone(eCHARINFO_BTN_STAT))
		{
			if (gInterface.Data[eCHARINFO_BTN_STAT].OnClick)
			{
				gInterface.DrawButton(eCHARINFO_BTN_STAT, ButtonX, 73, 0, 14);
			}
		}
	}

	// Luôn vẽ button AutoHP
	DWORD color = gAddPoint.m_AUTOHP ? eGold : eGray100;
	gInterface.DrawButton(eCHARINFO_BTN_AUTOHP, ButtonX+ 83, 94, 0, 0);
	gToolKit.MakeShadowText(ButtonX + 100, 97, 100, 1, gAddPoint.m_AUTOHP ? "AutoHP[ON]" : "AutoHP[OFF]");
	if (gInterface.IsWorkZone(eCHARINFO_BTN_AUTOHP))
	{

		if (gInterface.Data[eCHARINFO_BTN_AUTOHP].OnClick)
		{
			gInterface.DrawButton(eCHARINFO_BTN_AUTOHP, ButtonX+83, 94, 0, 14);
		}
	}

	if (gAddPoint.m_ResetStats == 1)
	{
		gInterface.DrawButton(eCHARINFO_BTN_RESSTAT, ButtonX, 94, 0, 0);
		gToolKit.MakeShadowText(ButtonX + 19, 97, 100, 1, gConfig.TTAS_TEXT_ENGINE[285]); // "Tẩy điểm"

		if (gInterface.IsWorkZone(eCHARINFO_BTN_RESSTAT))
		{
			if (gInterface.Data[eCHARINFO_BTN_RESSTAT].OnClick)
			{
				gInterface.DrawButton(eCHARINFO_BTN_RESSTAT, ButtonX, 94, 0, 14);
			}
		}
	}
	else
	{
		((BOOL(__thiscall*)(LPVOID This))0x0077FAE0)(This);
	}
}

int TASAddPoint::GetMaxStatPoint(int AccountLevel)
{
	return this->m_MaxStatPoint[AccountLevel];
}
bool TASAddPoint::ControlTextBox(DWORD Event)
{
	if (gInterface.Data[eSTATSADD_MAIN].OnShow)
	{
		char Value[20];
		int IsBackspace = false;
		int IsDelete = false;
		int IsTab = false;

		int ObjectCount = 4;

		if ((gObjUser.lpPlayer->Class & 7) == 4)
		{
			ObjectCount = 5;
		}

		int SelectedIndex = 0;

		if (Event == VK_BACK)
		{
			IsBackspace = true;
		}
		else if (Event == VK_DELETE)
		{
			IsDelete = true;
		}
		else if (Event == VK_TAB)
		{
			IsTab = true;
		}
		else if ((Event >= 0x30 && Event <= 0x39) || (Event >= 0x60 && Event <= 0x69))
		{
			int Symbol = GetSymbolFromVK(Event);
			if (Symbol == 0)
			{
				return true;
			}
			char buff[10];
			sprintf(buff, "%c", Symbol);
			strcpy_s(Value, buff);
		}
		else
		{
			return true;
		}
		int ObjectIDs[5] =
		{
			eSTATSADD_STATBOX01,
			eSTATSADD_STATBOX02,
			eSTATSADD_STATBOX03,
			eSTATSADD_STATBOX04,
			eSTATSADD_STATBOX05,
		};

		for (int i = 0; i < ObjectCount; i++)
		{
			if (gInterface.Data[ObjectIDs[i]].Attribute == 1)
			{
				SelectedIndex = i;
				if (IsBackspace == true)
				{
					gInterface.Data[ObjectIDs[i]].StatValue[strlen(gInterface.Data[ObjectIDs[i]].StatValue) - 1] = '\0';

					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) == 0)
					{
						strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
					}
					break;
				}
				else if (IsDelete == true)
				{
					strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
				}
				else if (IsTab == true)
				{
					gInterface.Data[ObjectIDs[i]].Attribute = 0;

					if (i == ObjectCount - 1)
					{
						gInterface.Data[ObjectIDs[0]].Attribute = 1;
					}
					else
					{
						gInterface.Data[ObjectIDs[i + 1]].Attribute = 1;
					}
					break;
				}
				else
				{
					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) < 8)
					{
						if (!strcmp(gInterface.Data[ObjectIDs[i]].StatValue, "0"))
						{
							strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
						else
						{
							strcat_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
					}
				}
			}
		}

		int StatPoints = 0;

		for (int i = 0; i < ObjectCount; i++)
		{
			if (i == SelectedIndex)
			{
				continue;
			}
			StatPoints += atoi(gInterface.Data[ObjectIDs[i]].StatValue);
		}

		if (StatPoints + atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > ViewPoint)
		{
			char buff[20];
			sprintf(buff, "%d", ViewPoint - StatPoints);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}

		if (atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > this->GetMaxStatPoint(ViewAccountLevel))
		{
			char buff[20];
			sprintf(buff, "%d", this->GetMaxStatPoint(ViewAccountLevel) - 30);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}
	}
	return false;
}
#endif