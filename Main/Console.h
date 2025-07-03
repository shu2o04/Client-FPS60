#pragma once
#define sub_483540_Addr		((int(__cdecl*)(int)) 0x00483540)
#define sub_5BD4C0_addr		((void(__cdecl*)(__int16 a1, float a2, BYTE a3, int a4, int a5, BYTE a6, BYTE a7)) 0x5BD4C0)
#define sub_9CF11A_Addr		((void(__cdecl*)(void *a1)) 0x9CF11A)
#define sub_9CDB52_Addr		((int(__cdecl*)(int)) 0x9CDB52)
#define sub_407B90	((char(__thiscall*)(int This, int a2, int a3, int a4)) 0x407B90)
#define sub_421800				((int(__thiscall*)(DWORD this_, LPWSTR lpString, int nMaxCount)) 0x00421800)
#define sub_9D5961_Addr	((int(__cdecl*)(unsigned int a1, int a2)) 0x9D5961)
#define sub_859F90_Addr	((bool(__thiscall*)(int *this_)) 0x859F90)
#define sub_630BC0   ((bool(*)()) 0x630BC0)
#define PCID "HOCSINH"
namespace CNSL_E
{
	enum T
	{
		CONSOLE_RED		= 1,
		CONSOLE_GREEN	= 2,
		CONSOLE_BLUE	= 3,
		CONSOLE_CYAN	= 4,
		CONSOLE_YELLOW	= 5,
	};
}

class Console1
{
	public:
	Console1();
	void Load();
	int WriteMessage(char * szBuffer);
	bool CommandsStatus(char * szBuffer, char * szCmdName, int Size);
	bool WriteInFile(LPCTSTR szBuffer);
	void SetCommands(char * szBuffer);
	void AddMessage(int Color, const char * Format, ...);
	static void SetSettings(PVOID lpVOID);
	DWORD PiD;
	HANDLE g_Handle(BOOL bImput);
	bool is_loaded;
}; 
extern Console1 g_Console;
