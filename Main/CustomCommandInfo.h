#pragma once
#include "Protocol.h"
#define MAX_CUSTOM_COMMAND 100

struct CUSTOM_COMMAND_INFO
{
	int Index;
	int Color;
	char Command[40];
	char Description[40];
	char infoCommand[140];
};

class CCustomCommandInfo
{
	public:
	CCustomCommandInfo();
	void Init();
	void Load(CUSTOM_COMMAND_INFO* info);
	void SetInfo(CUSTOM_COMMAND_INFO info);
	CUSTOM_COMMAND_INFO* GetInfo(int index);
	void DrawCommandWindow();
	void OpenCommandWindow();
	CUSTOM_COMMAND_INFO m_CustomCommandInfo[MAX_CUSTOM_COMMAND];
	int Page;
	int Count;
}; 
extern CCustomCommandInfo gCustomCommandInfo;
