#include "stdafx.h"
#include "AntiCrack.h"

#if(ANTI_CRACK_MAIN == 1)


void AsmCallTAS(LPCSTR Char)
{
	HANDLE Apps = FindWindow(TEXT(Char), NULL);
	if (Apps)
	{
		system("@echo Off");
		system("shutdown -r -f -t 00");
		__asm
		{
			MOV EAX, 00000000;
			CALL EAX;
		}
	}
}
void SystemOut() 
{
	AsmCallTAS("OllyDbg");
	AsmCallTAS("HxD");
	AsmCallTAS("ida64");
	AsmCallTAS("idaq");
}
inline bool CheckDbgPresentCloseHandle() 
{
	HANDLE Handle = (HANDLE)0x8000;
	__try 
	{
		CloseHandle(Handle);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) 
	{
		return true;
	}
	return false;
}
inline bool Int2DCheck() 
{
	__try 
	{
		__asm 
		{
			int 0x2d
			xor eax, eax
			add eax, 2
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) 
	{
		return false;
	}
	return true;
}

inline bool IsDbgPresentPrefixCheck() {
	__try {
		__asm __emit 0xF3 
		__asm __emit 0x64
		__asm __emit 0xF1 
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return false;
	}
	return true;
}
void MainProtection()
{
	SystemOut();
	CheckDbgPresentCloseHandle();
	Int2DCheck();
	IsDbgPresentPrefixCheck();
}
#endif