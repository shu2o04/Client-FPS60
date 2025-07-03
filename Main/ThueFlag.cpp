#include "StdAfx.h"
#if(HT_THUE_FLAG)
#include "ThueFlag.h"
#include "Import.h"
#include "Interface.h"
#include "CustomFont.h"
#include "Util.h"
#include "TMemory.h"
#include "Defines.h"
#include "CustomModelFlag.h"
#include "Central.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "Common.h"
#include "Config.h"
#include "TAS_ToolKit.h"
std::string convertUnixTimestampToString(time_t timestamp) {
	std::tm* timeinfo = std::localtime(&timestamp);

	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << timeinfo->tm_hour << ":"
		<< std::setw(2) << std::setfill('0') << timeinfo->tm_min << " "
		<< std::setw(2) << std::setfill('0') << timeinfo->tm_mday << "/"
		<< std::setw(2) << std::setfill('0') << (timeinfo->tm_mon + 1) << "/"
		<< (timeinfo->tm_year + 1900);

	return oss.str();
}
cThueFlag ThueFlag;

cThueFlag::cThueFlag()
{
	this->Init();
}

void cThueFlag::SetRect(float a1, float a2, float a3, float a4)
{
	this->x = a1;
	this->y = a2;
	this->w = a3;
	this->h = a4;
}
bool cThueFlag::CheckRect()
{
	return this->Drawing && pCheckMouseOver(x, y, w, h);
	return gInterface.Data[TAS_ThueFlag_Main].OnShow = true && pCheckMouseOver(x, y, w, h);
}

void cThueFlag::Bind()
{
	gInterface.BindObject(TAS_ThueFlag_Main, 0x7A5A, 445, 364, 205, -1);
}

void cThueFlag::Init()
{
	this->Drawing = false;
	this->SetRect(120, 70, 400, 255);
}
void cThueFlag::OpenFlag()
{
	if ((GetTickCount() - gInterface.Data[TAS_ThueFlag_Main].EventTick) > 300)
	{
		gInterface.Data[TAS_ThueFlag_Main].EventTick = GetTickCount();

		if (gInterface.Data[TAS_ThueFlag_Main].OnShow)
		{
			ThueFlag.SendRequest(0x2, 0);
			gInterface.Data[TAS_ThueFlag_Main].OnShow = 0;
			return;
		}
		ThueFlag.SendRequest(0x0, ThueFlag.Selected);
		gInterface.Data[TAS_ThueFlag_Main].OnShow ^= 1;
	}

}
void BBDrawItem3D(float sx, float sy, float Width, float Height, int Type, int Level, int ExtOption, int Ancient, bool PickUp, float Scale, bool Center)
{
	glMatrixMode(0x1701);
	glPushMatrix();
	glLoadIdentity();
	sub_6363D0_Addr(0, 0, *(GLsizei*)0x00E61E58, *(GLsizei*)0x00E61E5C);
	float v2 = *(float*)0x00E61E58 / *(float*)0x00E61E5C;
	sub_6358A0_Addr(Scale, v2, *(float*)0xE61E38, *(float*)0xE61E3C);
	glMatrixMode(0x1700);
	glPushMatrix();
	glLoadIdentity();
	sub_635830_Addr((LPVOID)0x87933A0);
	sub_635DE0_Addr();
	sub_635E40_Addr();
	pDrawItemModel(sx, sy, Width, Height, Type, Level, ExtOption, Ancient, PickUp);
	glMatrixMode(0x1700u);
	glPopMatrix();
	glMatrixMode(0x1701u);
	glPopMatrix();
	glColor3f(1, 1, 1);
	pSetBlend(false);
	return;
}

void cThueFlag::Draw()
{
	if (gInterface.CheckWindow(ObjWindow::CashShop) || gInterface.CheckWindow(ObjWindow::FriendList) || gInterface.CheckWindow(ObjWindow::MoveList)
		|| gInterface.CheckWindow(ObjWindow::Party) || gInterface.CheckWindow(ObjWindow::Quest) || gInterface.CheckWindow(ObjWindow::NPC_Devin)
		|| gInterface.CheckWindow(ObjWindow::Guild) || gInterface.CheckWindow(ObjWindow::Trade) || gInterface.CheckWindow(ObjWindow::Warehouse)
		|| gInterface.CheckWindow(ObjWindow::ChaosBox) || gInterface.CheckWindow(ObjWindow::CommandWindow) || gInterface.CheckWindow(ObjWindow::PetInfo)
		|| gInterface.CheckWindow(ObjWindow::Shop) || gInterface.CheckWindow(ObjWindow::Inventory) || gInterface.CheckWindow(ObjWindow::Store)
		|| gInterface.CheckWindow(ObjWindow::OtherStore) || gInterface.CheckWindow(ObjWindow::Character) || gInterface.CheckWindow(ObjWindow::DevilSquare)
		|| gInterface.CheckWindow(ObjWindow::BloodCastle) || gInterface.CheckWindow(ObjWindow::CreateGuild) || gInterface.CheckWindow(ObjWindow::GuardNPC)
		|| gInterface.CheckWindow(ObjWindow::SeniorNPC) || gInterface.CheckWindow(ObjWindow::GuardNPC2) || gInterface.CheckWindow(ObjWindow::CastleGateSwitch)
		|| gInterface.CheckWindow(ObjWindow::CatapultNPC) || gInterface.CheckWindow(ObjWindow::CrywolfGate) || gInterface.CheckWindow(ObjWindow::IllusionTemple)
		|| gInterface.CheckWindow(ObjWindow::HeroList) || gInterface.CheckWindow(ObjWindow::ChatWindow) || gInterface.CheckWindow(ObjWindow::FastMenu)
		|| gInterface.CheckWindow(ObjWindow::Options) || gInterface.CheckWindow(ObjWindow::Help) || gInterface.CheckWindow(ObjWindow::FastDial)
		|| gInterface.CheckWindow(ObjWindow::SkillTree) || gInterface.CheckWindow(ObjWindow::GoldenArcher1) || gInterface.CheckWindow(ObjWindow::GoldenArcher2)
		|| gInterface.CheckWindow(ObjWindow::LuckyCoin1) || gInterface.CheckWindow(ObjWindow::LuckyCoin2) || gInterface.CheckWindow(ObjWindow::NPC_Duel)
		|| gInterface.CheckWindow(ObjWindow::NPC_Titus) || gInterface.CheckWindow(ObjWindow::CashShop) || gInterface.CheckWindow(ObjWindow::Lugard)
		|| gInterface.CheckWindow(ObjWindow::QuestList1) || gInterface.CheckWindow(ObjWindow::QuestList2) || gInterface.CheckWindow(ObjWindow::Jerint)
		|| gInterface.CheckWindow(ObjWindow::FullMap) || gInterface.CheckWindow(ObjWindow::NPC_Dialog) || gInterface.CheckWindow(ObjWindow::GensInfo)
		|| gInterface.CheckWindow(ObjWindow::NPC_Julia) || gInterface.CheckWindow(ObjWindow::NPC_ChaosMix) || gInterface.CheckWindow(ObjWindow::ExpandInventory)
		|| gInterface.CheckWindow(ObjWindow::ExpandWarehouse) || gInterface.CheckWindow(ObjWindow::MuHelper))
	{
		gInterface.Data[TAS_ThueFlag_Main].OnShow = false;
		return;
	}
	if (!gInterface.Data[TAS_ThueFlag_Main].OnShow)
	{
		return;
	}


	float MainWidth = 400.0;
	int JCResto = 0;
	x = (MAX_WIN_WIDTH / 2) - (MainWidth / 2) + JCResto;
	//==========
	glAlphaFunc(GL_GREATER, 0.0f);

	int Dakosmuoffset = 0;
	this->x = 100 + Dakosmuoffset;
	this->y = 50;
	float CuaSoW = 400;
	float CuaSoH = 280;
	float MaxX = this->x + CuaSoW;
	float MaxY = this->y + CuaSoH;

	gCentral.gDrawWindowCustom(170, 70, 296, 260, TAS_ThueFlag_Main, "THUÊ FLAG");
	gToolKit.CloseButton(433, 69, TAS_ThueFlag_BtnClose);

	glAlphaFunc(GL_GREATER, 0.25f);

	gCentral.gInfoBox(x + 85, y + 60, 80, 75, 0x00000096, 0, 0);
	gCentral.gInfoBox(x + 85, y + 150, 80, 75, 0x00000096, 0, 0);
	gCentral.gInfoBox(x + 179, y + 60, 165, 165, 0x00000096, 0, 0);

	THUE_FLAG_DATA* skin = this->FindId(this->Selected);

	this->DrawButton(32331, x + 78, y + 240, 73, 27, 128.0, 128.0, ThueFlag.DisableAction);
	CustomFont.Draw(CustomFont.FontNormal, x + 78, (y + 240) + 8.5, 0xFFFFFFFF, 0x0, 73, 0, 3, (DisableFlag == 1) ? gConfig.TTAS_TEXT_ENGINE[287] :gConfig.TTAS_TEXT_ENGINE[288]);

	this->DrawButton(32331, x + 148, y + 240, 73, 27, 128.0, 128.0, ThueFlag.BuyAction);

	this->DrawButton(32331, x + 218, y + 240, 73, 27, 128.0, 128.0, ThueFlag.NextAction);
	CustomFont.Draw(CustomFont.FontNormal, x + 218, (y + 240) + 8.5, 0xFFFFFFFF, 0x0, 73, 0, 3, gConfig.TTAS_TEXT_ENGINE[289]);
	
	if (this->Selected > 0)
	{
		this->DrawButton(32331, x + 288, y + 240, 73, 27, 128.0, 128.0, ThueFlag.PrevAction);
		CustomFont.Draw(CustomFont.FontNormal, x + 288, (y + 240) + 8.5, 0xFFFFFFFF, 0x0, 73, 0, 3, gConfig.TTAS_TEXT_ENGINE[290]);
	}

	if (skin != 0)
	{
		CustomFont.Draw(CustomFont.FontNormal, x + 95, (y + 0) + 65, 0x66FF66FF, 0x0, 150, 0, 1,  gConfig.TTAS_TEXT_ENGINE[291], skin->Value1);
		CustomFont.Draw(CustomFont.FontNormal, x + 95, (y + 0) + 80, 0x66FF66FF, 0x0, 150, 0, 1,  gConfig.TTAS_TEXT_ENGINE[292], skin->Value2);
		CustomFont.Draw(CustomFont.FontNormal, x + 95, (y + 0) + 95, 0x66FF66FF, 0x0, 150, 0, 1, gConfig.TTAS_TEXT_ENGINE[293], skin->Value3);
		CustomFont.Draw(CustomFont.FontNormal, x + 95, (y + 0) + 110, 0x66FF66FF, 0x0, 150, 0, 1, gConfig.TTAS_TEXT_ENGINE[294], skin->Value4);
		CustomFont.Draw(CustomFont.FontNormal, x + 95, (y + 0) + 125, 0x66FF66FF, 0x0, 150, 0, 1, gConfig.TTAS_TEXT_ENGINE[295], (skin->Time) / 60);

		if (gCustomModelFlag.CheckFlagModelIsLoad(gProtect.m_MainInfo.m_mModelFlagData[skin->Id].ModelIndex))
		{
			BBDrawItem3D(x + 135 + (25 * 4), y + 115, 50, 60,
				gProtect.m_MainInfo.m_mModelFlagData[skin->Id].ModelIndex, 0, 0, 0, 0, 0.8f, true);
		}

		if (skin->Time < 1)
		{
			CustomFont.Draw(CustomFont.FontNormal, x + 65, y + 160, 0xFF3300FF, 0x0, 150, 0, 1, gConfig.TTAS_TEXT_ENGINE[296], gToolKit.NumberFormat(skin->Price));
		}
		else
		{
			CustomFont.Draw(CustomFont.FontNormal, (x + 65) + 30, y + 160, 0xFF3300FF, 0x0, 150, 0, 1, gConfig.TTAS_TEXT_ENGINE[296], gToolKit.NumberFormat(skin->Price));
		}
		CustomFont.Draw(CustomFont.FontNormal, (x + 65) + 30, (y + 160) + 15, 0xFF3300FF, 0x0, 150, 0, 1, gConfig.TTAS_TEXT_ENGINE[297], skin->Value7);

		gInterface.DrawItem2(x + 120, y + 200, 15, 15, ITEM(skin->Value8, skin->Value9), 11, 0, 0, 0);

		if (skin->Value10 != -1)
		{
			if (skin->Value10 > 0)
			{
				time_t timestamp = skin->Value10;
				std::string dateTimeString = convertUnixTimestampToString(timestamp);
				CustomFont.Draw(CustomFont.FontNormal, x + 180, y + 60, 0xFFFFFFFF, 0x00FBFF69, 171, 0, 3, gConfig.TTAS_TEXT_ENGINE[298], strdup(dateTimeString.c_str()));
			}
			else
			{
				CustomFont.Draw(CustomFont.FontNormal, x + 4 + 75 * 2, y + 35, 0xffffffff, 0x0, 150, 0, 3, gConfig.TTAS_TEXT_ENGINE[299]);
			}
			CustomFont.Draw(CustomFont.FontNormal, x + 148, (y + 240) + 8.5, 0xffffffff, 0x0, 73, 0, 3, skin->Skin != this->Skin ? gConfig.TTAS_TEXT_ENGINE[300] : gConfig.TTAS_TEXT_ENGINE[301]);
		}
		else
		{
			CustomFont.Draw(CustomFont.FontNormal, x + 180, y + 60, 0xFFFFFFFF, 0x00FBFF69, 171, 0, 3, gConfig.TTAS_TEXT_ENGINE[302]);
			CustomFont.Draw(CustomFont.FontNormal, x + 148, (y + 240) + 8.5, 0xffffffff, 0x0, 73, 0, 3, gConfig.TTAS_TEXT_ENGINE[303]);
		}

	}
	else
	{
		char buf[25];
		int step = GetTickCount() / 1000 % 4;
		sprintf(buf, "Loading data%%.%ds", step);

		CustomFont.Draw(CustomFont.FontNormal, x + 25, y + 50 + 13 * 1, 0xffffffff, 0x0, 150, 0, 0, buf, "...");
	}
}

void cThueFlag::SendRequest(BYTE type, int value)
{
	PMSG_THUE_FLAG_SEND pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0x03, sizeof(pRequest));
	pRequest.Type = type;
	pRequest.Value = value;
	DataSend((LPBYTE)&pRequest, pRequest.h.size);
}


void cThueFlag::RecvData(BYTE* a)
{
	PMSG_THUE_FLAG_RECV* Packet = (PMSG_THUE_FLAG_RECV*)a;

	this->Skin = Packet->Skin;

	if (Packet->Data.Id == -1)
	{
		return;
	}

	this->Selected = Packet->Data.Id;

	THUE_FLAG_DATA* skin = this->FindId(Packet->Data.Id);

	if (skin != 0)
	{
		skin->Id = Packet->Data.Id;
		skin->Skin = Packet->Data.Skin;
		skin->Time = Packet->Data.Time;
		skin->Price = Packet->Data.Price;
		skin->Value1 = Packet->Data.Value1;
		skin->Value2 = Packet->Data.Value2;
		skin->Value3 = Packet->Data.Value3;
		skin->Value4 = Packet->Data.Value4;
		skin->Value5 = Packet->Data.Value5;
		skin->Value6 = Packet->Data.Value6;
		skin->Value7 = Packet->Data.Value7;
		skin->Value8 = Packet->Data.Value8;
		skin->Value9 = Packet->Data.Value9;
		skin->Value10 = Packet->Data.Value10;
	}
	else
	{
		THUE_FLAG_DATA new_skin;
		new_skin.Id = Packet->Data.Id;
		new_skin.Skin = Packet->Data.Skin;
		new_skin.Time = Packet->Data.Time;
		new_skin.Price = Packet->Data.Price;
		new_skin.Value1 = Packet->Data.Value1;
		new_skin.Value2 = Packet->Data.Value2;
		new_skin.Value3 = Packet->Data.Value3;
		new_skin.Value4 = Packet->Data.Value4;
		new_skin.Value5 = Packet->Data.Value5;
		new_skin.Value6 = Packet->Data.Value6;
		new_skin.Value7 = Packet->Data.Value7;
		new_skin.Value8 = Packet->Data.Value8;
		new_skin.Value9 = Packet->Data.Value9;
		new_skin.Value10 = Packet->Data.Value10;


		this->m_Data.push_back(new_skin);
		return;
	}
}


void cThueFlag::Clear()
{

	this->TickCount = 0;
	this->Skin = 0;
	this->Selected = 0;
	this->m_Data.clear();

}

THUE_FLAG_DATA* cThueFlag::FindSkin(int id)
{
	for (int i = 0; i < this->m_Data.size(); i++)
	{
		if (this->m_Data[i].Skin == id)
		{
			return &this->m_Data[i];
		}
	}
	return 0;
}
THUE_FLAG_DATA* cThueFlag::FindId(int id)
{
	for (int i = 0; i < this->m_Data.size(); i++)
	{
		if (this->m_Data[i].Id == id)
		{
			return &this->m_Data[i];
		}
	}
	return 0;
}


void cThueFlag::DrawButton(int IMGcode, float x, float y, float w, float h, float a6, float a7, PUSHEVENT_CALLBACK_LPVOID pCallbackFunc)
{
	if (pCheckMouseOver(x, y, w, h))
	{
		pSetCursorFocus = true;

		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			RenderBitmap(IMGcode, x, y, w, h, 0.0, h / a7 * 2.0, w / a6, h / a7, 1, 1, 0.0);
		}
		else
		{
			RenderBitmap(IMGcode, x, y, w, h, 0.0, h / a7, w / a6, h / a7, 1, 1, 0.0);
		}
		if (pIsKeyRelease(VK_LBUTTON))
		{
			pCallbackFunc(this);
			return;
		}
		return;
	}
	else
	{
		RenderBitmap(IMGcode, x, y, w, h, 0.0, 0.0, w / a6, h / a7, 1, 1, 0.0);
	}
	return;
}

void cThueFlag::DisableAction(LPVOID pClass)
{
	cThueFlag* This = (cThueFlag*)pClass;
	if (DisableFlag)
	{
		DisableFlag = 0;
	}
	else
	{
		DisableFlag = 1;
	}
	This->SendRequest(0x4, 0);
	gInterface.Data[TAS_ThueFlag_Main].OnShow = false;
}

void cThueFlag::BuyAction(LPVOID pClass)
{
	cThueFlag* This = (cThueFlag*)pClass;

	THUE_FLAG_DATA* skin = This->FindId(This->Selected);

	if (skin != 0)
	{
		if (skin->Skin == abs(This->Skin))
		{
			This->SendRequest(0x3, abs(This->Skin) >= 0);
		}
		else
		{
			This->SendRequest(0x1, This->Selected);
		}
	}
	gInterface.Data[TAS_ThueFlag_Main].OnShow = false;
}

void cThueFlag::NextAction(LPVOID pClass)
{
	cThueFlag* This = (cThueFlag*)pClass;

	This->SendRequest(0x0, This->Selected + 1);
}

void cThueFlag::PrevAction(LPVOID pClass)
{
	cThueFlag* This = (cThueFlag*)pClass;
	if (This->Selected > 0)
	{
		This->SendRequest(0x0, This->Selected - 1);
	}
}
#endif