#include "stdafx.h"
#include "Defines.h"
#include "Monster.h"
CCustomMonsterNameColor gCustomMonsterNameColor;
CCustomMonsterNameColor::CCustomMonsterNameColor() // OK
{
	this->Init();
}

void CCustomMonsterNameColor::Init() // OK
{
	for(int n=0;n < MAX_NAME_COLOR;n++)
	{
		this->m_CustomMonsterColorInfo[n].Index = -1;
	}
}

void CCustomMonsterNameColor::Load(CUSTOM_MONSTER_COLOR_INFO* info) // OK
{
	for(int n=0;n < MAX_NAME_COLOR;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomMonsterNameColor::SetInfo(CUSTOM_MONSTER_COLOR_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_NAME_COLOR)
	{
		return;
	}

	this->m_CustomMonsterColorInfo[info.Index] = info;
}

CUSTOM_MONSTER_COLOR_INFO* CCustomMonsterNameColor::GetNPCNameByIndex(int index) // OK
{
	if(index < 0 || index >= MAX_NAME_COLOR)
	{
		return 0;
	}

	if(this->m_CustomMonsterColorInfo[index].Index != index)
	{
		return 0;
	}
	return &this->m_CustomMonsterColorInfo[index];
}