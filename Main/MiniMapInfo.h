#pragma once


#include "Protocol.h"

#define MAX_PLAYER_PARTY 10

struct MINIMAP_PARTY_INFO_RECV
{
	PSWMSG_HEAD header; // C1:E7:01
	BYTE count;
};

struct MINIMAP_PARTY_INFO
{
	char name[11];
	BYTE map;
	BYTE x;
	BYTE y;
};


struct MINIMAP_INFO_RECV
{
	PSWMSG_HEAD header; // C1:E7:03
	BYTE index;
	BYTE group;
	BYTE type;
	BYTE flag;
	BYTE x;
	BYTE y;
	char text[31];
};

class cMiniMap
{
public:
	void ClearPartyInfo();
	void RecvPartyInfo(MINIMAP_PARTY_INFO_RECV* lpMsg);
	void InsertPartyInfo(MINIMAP_PARTY_INFO* lpInfo);
	// ----
	MINIMAP_PARTY_INFO gPartyInfo[MAX_PLAYER_PARTY];
	int ListsCount;
	// ----
}; extern cMiniMap gMiniMap;