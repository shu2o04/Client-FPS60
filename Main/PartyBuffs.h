#pragma once
#include "Protocol.h"
#include <string>

struct PMSG_PARTY_EFFECT_LIST_SEND
{
	PBMSG_HEAD header; // C1:2E
	char name[11];
	BYTE count;
};

struct PMSG_PARTY_EFFECT_LIST
{
	#pragma pack(1)
	BYTE effect;
	DWORD count;
	#pragma pack()
};

struct PARTY_BUFFS
{
	BYTE effect;
	DWORD count;
};

struct PARTY_BUFFS_DATA
{
	char name[11];
	int count;
	PARTY_BUFFS Buffs[32];
};

class cPartyBuffs
{
	public:
	cPartyBuffs();
	void RecvPartyBuffs(PMSG_PARTY_EFFECT_LIST_SEND* lpMsg);
	PARTY_BUFFS_DATA* GetInfoByName(char* Name);
	void DrawPartyBuffs(float StartX, float StartY, char* MemberName);
	std::map<std::string,PARTY_BUFFS_DATA> m_PartyBuffsData;
	int m_Loaded;
}; 
extern cPartyBuffs gPartyBuffs;