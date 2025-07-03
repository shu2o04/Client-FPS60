#include "StdAfx.h"
#include "Console.h"
#include <stdio.h>
#include "tchar.h"
#include "Monster.h"
#include "Offset.h"
#include "Protocol.h"
#include "Protect.h"
#include "Util.h"
#include "User.h"
#include "Interface.h"
#include <fstream>
#include "HackCheck.h"
#ifdef USE_AWESOMIUM
#include "Awesomium.h"
#endif
#include "Resolution.h"
#include "Camera.h"
#include "HWID.h"

#pragma warning (disable : 4482 4996)

Console1 g_Console;

Console1::Console1()
{
	this->is_loaded = false;
}
 
void Console1::Load()
{
	DWORD size=1024;
	char buff[1024];
	GetComputerName(buff, &size);
	if (!strcmp(buff, PCID))
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)this->SetSettings, 0, 0, &this->PiD);
		Sleep(100);
	}
}

struct PMSG_EVENT_STATE_SEND
{
	PBMSG_HEAD header; // C1:0B
	BYTE state;
	BYTE event;
};

void SetFont()
{
	LPCSTR pszFaceName;
	LPCSTR v55;
	LPCSTR v54;
	LPCSTR v53;

	*(DWORD*)0x81C0380 = 13;

	int cHeight = *(DWORD*)0x81C0380 - 1;
	BYTE iCharSet = *(BYTE*)0xE61144;
	int v130 = 12;

	if ( pGetTextLine(pTextLineThis, 0) )
		pszFaceName = pGetTextLine(pTextLineThis, 0);
	else
		pszFaceName = 0;
	pFontNormal = CreateFontA(cHeight, 0, 0, 0, 400, 0, 0, 0, iCharSet, 0, 0, 3u, 0, pszFaceName);

	if (pGetTextLine(pTextLineThis, 0) )
		v55 = pGetTextLine(pTextLineThis, 0);
	else
		v55 = 0;
	pFontBold = CreateFontA(cHeight, 0, 0, 0, 700, 0, 0, 0, iCharSet, 0, 0, 3u, 0, v55);

	if ( pGetTextLine(pTextLineThis, 0) )
		v54 = pGetTextLine(pTextLineThis, 0);
	else
		v54 = 0;
	pFontBigBold = CreateFontA(2 * cHeight, 0, 0, 0, 700, 0, 0, 0, iCharSet, 0, 0, 3u, 0, v54);

	if ( pGetTextLine(pTextLineThis, 18) )
		v53 = pGetTextLine(pTextLineThis, 18);
	else
		v53 = 0;
	pFontNormal2 = CreateFontA(v130, 0, 0, 0, 400, 0, 0, 0, iCharSet, 0, 0, 3u, 0, v53);
}

void test_fix()
{
	DWORD iModeNum;
	DEVMODEA DevMode;
	DEVMODEA* v84;
	DEVMODEA* v113;
	int v118;

	
	for (iModeNum = 0; EnumDisplaySettingsA(0, iModeNum, &DevMode); ++iModeNum)
		;
	v84 = (DEVMODEA*)sub_9CDB52_Addr((156 * (unsigned __int64)(iModeNum + 1)) >> 32 != 0 ? -1 : 156 * (iModeNum + 1));
	v113 = v84;
	for (iModeNum = 0; EnumDisplaySettingsA(0, iModeNum, &v113[iModeNum]); ++iModeNum)
		;
	v118 = 16;
	for (int i = 0; i < (int)iModeNum; ++i)
	{
		if (v113[i].dmBitsPerPel == 16 && !*(DWORD*)0xE8C23C)
		{
			v118 = 16;
			break;
		}
		if (v113[i].dmBitsPerPel == 24 && *(DWORD*)0xE8C23C == 1)
		{
			v118 = 24;
			break;
		}
		if (v113[i].dmBitsPerPel == 32 && *(DWORD*)0xE8C23C == 1)
		{
			v118 = 32;
			break;
		}
	}
	if (!*(DWORD*)0xE60974)
	{
		for (int j = 0; j < (int)iModeNum; ++j)
		{
			if (v113[j].dmPelsWidth == pWinWidth
				&& v113[j].dmPelsHeight == pWinHeight
				&& v113[j].dmBitsPerPel == v118)
			{
				ChangeDisplaySettingsA(&v113[j], 0);
				break;
			}
		}
	}
	sub_9CF11A_Addr(v113);
}

BOOL CALLBACK EnumChildProc(_In_ HWND hwnd, _In_ LPARAM lParam)
{
	char text[128];
	GetClassNameA(hwnd, text, 128);
	return 1;
}

struct PMSG_GUILD_RESULT_SEND
{
	PBMSG_HEAD header; // C1:51
	BYTE result;
};

void Console1::SetCommands(char * szBuffer)
{
	if (!this->is_loaded)
		return;

	if (this->CommandsStatus(szBuffer,"/a",sizeof("/a")))
	{
		SetDouble((DWORD)gCamera.m_Address.ClipX[0], ((2100.0f + (155 * (*gCamera.m_Address.Zoom - 35))) + (abs(((*gCamera.m_Address.PosZ) - 150.0f)) * 3.0f)));
		SetDouble((DWORD)gCamera.m_Address.ClipX[1], ((2100.0f + (155 * (*gCamera.m_Address.Zoom - 35))) + (abs(((*gCamera.m_Address.PosZ) - 150.0f)) * 3.0f)));		
	}
	if (this->CommandsStatus(szBuffer,"/test",5))
	{
		int v26;
		v26 = *(DWORD*)(GetInstance() + 160);
		*(BYTE*)(v26 + 196) ^= 1;
	}
}

void Console1::SetSettings(PVOID lpVOID)
{
	char szBuffer[2048] = { 0 };
	AllocConsole();
	char text[256];
	sprintf(text,"TAS Main Ver: %s)",VERSION);
	SetConsoleTitle(text);
	g_Console.is_loaded = true;
	while (true)
	{
		Sleep(100);
		g_Console.WriteMessage(szBuffer);
		g_Console.SetCommands(szBuffer);
	}
}

bool Console1::CommandsStatus(char * szBuffer, char * szCmdName, int Size)
{
	bool bResult	= false;

	if (!strncmp(szBuffer, szCmdName, Size))
	{
		bResult		= true;
	}
	return bResult;
}

void Console1::AddMessage(int Color, const char * Format, ...)
{
	if (!this->is_loaded)
		return;
	SYSTEMTIME Time;
	GetLocalTime(&Time);
	char szMessage[2048]	= { 0 };
	char szBuffer[2048]		= { 0 };
	DWORD dwBytes			= 0;
	char szTime[11]			= { 0 };
	HANDLE g_Handle			= GetStdHandle(STD_OUTPUT_HANDLE);
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf_s(szMessage, Format, pArguments);
	va_end(pArguments);
	sprintf_s(szTime, "[%02d:%02d:%02d]", Time.wHour, Time.wMinute, Time.wSecond);
	sprintf_s(szBuffer, "%s %s\n", szTime, szMessage);
	switch (Color)
	{
		case CNSL_E::CONSOLE_RED:
		{
			SetConsoleTextAttribute(this->g_Handle(FALSE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		}break;

		case CNSL_E::CONSOLE_GREEN:
		{
			SetConsoleTextAttribute(this->g_Handle(FALSE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}break;

		case CNSL_E::CONSOLE_BLUE:
		{
			SetConsoleTextAttribute(this->g_Handle(FALSE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		}break;

		case CNSL_E::CONSOLE_CYAN:
		{
			SetConsoleTextAttribute(this->g_Handle(FALSE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		}break;

		case CNSL_E::CONSOLE_YELLOW:
		{
			SetConsoleTextAttribute(this->g_Handle(FALSE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}break;

		default: break;
	}
	std::ofstream fout("Console.txt", std::ios_base::app);
	fout << szBuffer << std::endl;	
	WriteFile(g_Handle, szBuffer, strlen(szBuffer), &dwBytes, NULL);
}

bool Console1::WriteInFile(LPCTSTR szBuffer)
{
	if (!this->is_loaded)
		return false;

	bool bResult				= true;

	SYSTEMTIME Time;

	GetLocalTime(&Time);

	FILE * loc_FileStream		= NULL;

	DWORD dwWrite;

	char szServerName[1000]		= { "Console" };

	char szBuff[100]			= { 0 };

	char szMessageNewLine[500]	= { 0 };

	char szTime[11]				= { 0 };

	WORD wDay					= Time.wDay;

	sprintf_s(szTime, "[%02d:%02d:%02d]", Time.wHour, Time.wMinute, Time.wSecond);

	sprintf_s(szBuff, "./%s_%02d-%02d-%02d.log", &szServerName, wDay, Time.wMonth, Time.wYear);

	fopen_s(&loc_FileStream, szBuff, "a+");

	if (wDay != Time.wDay)
	{
		sprintf_s(szBuff, "./%s_%02d-%02d-%02d.log", &szServerName, Time.wDay, Time.wMonth, Time.wYear);
	}

	if (loc_FileStream != NULL)
	{
		fclose(loc_FileStream);
	}

	HANDLE szHandle = CreateFile(szBuff, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

	if (szHandle == INVALID_HANDLE_VALUE)
	{
		bResult = false;
	}

	SetFilePointer(szHandle, 0, 0, FILE_END);

	sprintf_s(szMessageNewLine, "%s%s\r\n", szTime, szBuffer);

	WriteFile(szHandle, szMessageNewLine, _tcslen(szMessageNewLine) * sizeof(TCHAR), &dwWrite, NULL);

	CloseHandle(szHandle);

	return bResult;
}

int Console1::WriteMessage(char * szBuffer)
{
	if (!this->is_loaded)
		return 0;

	char szBuff[2048] = { 0 };

	DWORD dwBytes;

	memset(szBuff, 0x00, 2048);

	memset(szBuffer, 0x00, 2048);

	ReadFile(g_Handle(TRUE), szBuff, 2048, &dwBytes, NULL);

	strncpy(szBuffer, szBuff, strlen(szBuff) - 2);

	return dwBytes;
}

HANDLE Console1::g_Handle(BOOL bImput)
{
	if (bImput)
	{
		return GetStdHandle(STD_INPUT_HANDLE);
	}
	else
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}
}
