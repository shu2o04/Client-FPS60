#pragma once
#include "Protocol.h"

struct PMSG_ACTIVE_INVASIONS_RECV
{
	PSWMSG_HEAD header; // C2:F3:E2
	BYTE count;
};

struct InvasionsData
{
	InvasionsData(int count, int max_count) : _count(count), _max_count(max_count) {	}
	InvasionsData() : _count(0), _max_count(0) {}
	int _count;
	int _max_count;
};

struct PMSG_ACTIVE_INVASIONS
{
	int monster_id;
	InvasionsData count;
};

struct PMSG_INVASION_MONSTER_UPDATE_RECV
{
	PSBMSG_HEAD header; // C2:F3:E2
	int monster_id;
	int count;
};

struct ACTIVE_INVASIONS
{
	int monster_id;
	InvasionsData count;
};

#define MAXSLOTLIST 1
class CActiveInvasions
{
public:
	CActiveInvasions();
	void list_recv(PMSG_ACTIVE_INVASIONS_RECV* lpMsg);
	void update_monster_recv(PMSG_INVASION_MONSTER_UPDATE_RECV* lpMsg);
	//
	void render();
	int Count[MAXSLOTLIST];
	int ListPage[MAXSLOTLIST];
	int CurPos[MAXSLOTLIST];
	int DataList[MAXSLOTLIST];
	bool UpdateMaxPos[MAXSLOTLIST];
	int ListMaxPer[MAXSLOTLIST];
private:

	std::vector <ACTIVE_INVASIONS> m_data;
	bool is_move;

}; extern CActiveInvasions gActiveInvasions;