#pragma once
#include "Protocol.h"
#include "Interface.h"

struct GS_ITEM00
{
	PSBMSG_HEAD	header;
	BYTE ItemRong;
};

class CLASS_ITEM00
{
	public:
	BYTE ItemRong;
	void SendData(GS_ITEM00* lpMsg);
};
extern CLASS_ITEM00 GCLASS_ITEM00;

struct GS_ITEM06
{
	PSBMSG_HEAD	header;
	BYTE ItemRong;
};

class CLASS_ITEM06
{
	public:
	BYTE ItemRong;
	void SendData(GS_ITEM06* lpMsg);
};
extern CLASS_ITEM06 GCLASS_ITEM06;

struct GS_ITEM07
{
	PSBMSG_HEAD	header;
	BYTE ItemRong;
};

class CLASS_ITEM07
{
public:
	BYTE ItemRong;
	void SendData(GS_ITEM07* lpMsg);
};
extern CLASS_ITEM07 GCLASS_ITEM07;

struct GS_ITEM08
{
	PSBMSG_HEAD	header;
	BYTE ItemRong;
};

class CLASS_ITEM08
{
public:
	BYTE ItemRong;
	void SendData(GS_ITEM08* lpMsg);
};
extern CLASS_ITEM08 GCLASS_ITEM08;

struct GS_ITEM09
{
	PSBMSG_HEAD	header;
	BYTE ItemRong;
};

class CLASS_ITEM09
{
public:
	BYTE ItemRong;
	void SendData(GS_ITEM09* lpMsg);
};
extern CLASS_ITEM09 GCLASS_ITEM09;

struct GS_ITEM10
{
	PSBMSG_HEAD	header;
	BYTE ItemRong;
};

class CLASS_ITEM10
{
public:
	BYTE ItemRong;
	void SendData(GS_ITEM10* lpMsg);
};
extern CLASS_ITEM10 GCLASS_ITEM10;

struct GS_ITEM11
{
	PSBMSG_HEAD	header;
	BYTE ItemRong;
};

class CLASS_ITEM11
{
public:
	BYTE ItemRong;
	void SendData(GS_ITEM11* lpMsg);
};
extern CLASS_ITEM11 GCLASS_ITEM11;

struct GS_ITEM12
{
	PSBMSG_HEAD	header;
	BYTE ItemRong;
};

class CLASS_ITEM12
{
public:
	BYTE ItemRong;
	void SendData(GS_ITEM12* lpMsg);
};
extern CLASS_ITEM12 GCLASS_ITEM12;

struct GS_ITEM13
{
	PSBMSG_HEAD	header;
	BYTE ItemRong;
};

class CLASS_ITEM13
{
	public:
	BYTE ItemRong;
	void SendData(GS_ITEM13* lpMsg);
};
extern CLASS_ITEM13 GCLASS_ITEM13;