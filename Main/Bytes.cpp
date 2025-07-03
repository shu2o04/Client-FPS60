#include "stdafx.h"
#include "Bytes.h"
#include "Util.h"

#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

#define pOpen		((FILE*(*)(const char *,const char*))0x009D0040)
#define pSeek		((int*(*)(FILE*,long,int))0x009D6A53)
#define pRead		((DWORD*(*)(void*,DWORD,DWORD,FILE*))0x009CFF5F)

void *EncDecJpegBuffer;
DWORD EncDecJpegBufferSize;

void InitEncDec()
{
	SetCompleteHook(0xE9, 0x004FCB85, &EncDecOpenJpegBuffer2);

	SetCompleteHook(0xE9, 0x004FCCBA, &EncDecOpenTga);
	SetCompleteHook(0xE9, 0x0054C28C, &EncDecOpenBmd);
	SetCompleteHook(0xE9, 0x005D68FF, &EncDecOpenAtt);
	SetCompleteHook(0xE9, 0x005D6ECF, &EncDecOpenMap);
	SetCompleteHook(0xE9, 0x005F34A8, &EncDecOpenObj);

	SetCompleteHook(0xFF, 0x004FC6C7, &EncDecOpenFile);
	SetCompleteHook(0xFF, 0x004FCC3E, &EncDecOpenFile);
	SetCompleteHook(0xFF, 0x0054C21D, &EncDecOpenFile);
	SetCompleteHook(0xFF, 0x005D6826, &EncDecOpenFile);
	SetCompleteHook(0xFF, 0x005D6E64, &EncDecOpenFile);
	SetCompleteHook(0xFF, 0x005F3402, &EncDecOpenFile);
}

FILE *EncDecOpenFile(const char *path, const char *f)
{
	char encpath[MAX_PATH] = { 0 };

	wsprintf(encpath, "%s.enc", path);

	if (PathFileExists(encpath) != 0)
	{
		return pOpen(encpath,f);
	}

	return pOpen(path, f);
}

int EncDecCheckFile(FILE *hFile)
{
	BYTE Buffer[0x18] = { 0 };

	pSeek(hFile, 0, SEEK_SET);
	pRead(Buffer, 1, sizeof(Buffer), hFile);

	if (Buffer[0] != 'E' || Buffer[1] != 'N' || Buffer[2] != 'C')
	{
		return 0;
	}

	if (Buffer[3] == 1)
	{
		return 2;
	}

	return 1;
}

BOOL EncDecDecryptFile(FILE *hFile, BYTE *Buffer,int Size,int Origin, int Offset)
{
	if (EncDecCheckFile(hFile) != 0)
	{
		pSeek(hFile, 0x18, SEEK_SET);
		pRead(Buffer, 1, Size, hFile);

		for (int n = 0; n < (Size-0x18); n++)
		{
			Buffer[n] += (BYTE)(0xA0 ^ HIBYTE(n));
			Buffer[n] ^= (BYTE)(0xAB ^ LOBYTE(n));
		}

		return 1;
	}

	pSeek(hFile, Offset, SEEK_SET);
	pRead(Buffer, 1, Size, hFile);

	return 0;
}

__declspec(naked) void EncDecOpenJpegBuffer2() 
{
	static DWORD Address1 = 0x004FCB8C;
	static DWORD Address2 = 0x009CF11A;

	_asm
	{
		Push EncDecJpegBuffer
		Call[Address2]
		Add Esp,0x04
		Mov EncDecJpegBuffer,0
		Mov Byte Ptr Ss : [Ebp-0x325],1
		Jmp Address1
	}
}

__declspec(naked) void EncDecOpenTga()
{
	static DWORD Address1 = 0x004FCCD0;
	static DWORD Address2 = 0x004FCCD0;

	_asm
	{
		Push 0
		Push 0x18
		Mov Edx, Dword Ptr Ss : [Ebp-0x34]
		Push Edx
		Mov Eax, Dword Ptr Ss : [Ebp-0x44]
		Push Eax
		Mov Ecx, Dword Ptr Ss : [Ebp-0x3C]
		Push Ecx
		Call[EncDecDecryptFile]
		Add Esp,0x14
		Jmp Address1
	}
}

__declspec(naked) void EncDecOpenBmd()
{
	static DWORD Address1 = 0x0054C2A2;
	static DWORD Address2 = 0x0054C2A2;

	_asm
	{
		Push 0
		Push 0x18
		Mov Edx, Dword Ptr Ss : [Ebp-0x64]
		Push Edx
		Mov Eax, Dword Ptr Ss : [Ebp-0x68]
		Push Eax
		Mov Ecx, Dword Ptr Ss : [Ebp-0x18]
		Push Ecx
		Call[EncDecDecryptFile]
		Add Esp,0x14
		Jmp Address1
	}
}

__declspec(naked) void EncDecOpenAtt()
{
	static DWORD Address1 = 0x005D6915;
	static DWORD Address2 = 0x005D6915;

	_asm
	{
		Push 0
		Push 0x18
		Mov Edx, Dword Ptr Ss : [Ebp-0x14]
		Push Edx
		Mov Eax, Dword Ptr Ss : [Ebp-0x0C]
		Push Eax
		Mov Ecx, Dword Ptr Ss : [Ebp-0x8]
		Push Ecx
		Call[EncDecDecryptFile]
		Add Esp,0x14
		Test Eax,Eax
		Je EXIT
		Mov Edx, Dword Ptr Ss : [Ebp-0x14]
		Sub Edx,0x18
		Mov Dword Ptr Ss : [Ebp-0x14],Edx
		Jmp Address1
		EXIT:
		Jmp Address2
	}
}

__declspec(naked) void EncDecOpenMap()
{
	static DWORD Address1 = 0x005D6EE5;
	static DWORD Address2 = 0x005D6EE5;

	_asm
	{
		Push 0
		Push 0x18
		Mov Edx, Dword Ptr Ss : [Ebp-0x14]
		Push Edx
		Mov Eax, Dword Ptr Ss : [Ebp-0x0C]
		Push Eax
		Mov Ecx, Dword Ptr Ss : [Ebp-0x8]
		Push Ecx
		Call[EncDecDecryptFile]
		Add Esp,0x14
		Test Eax,Eax
		Je EXIT
		Mov Edx, Dword Ptr Ss : [Ebp-0x14]
		Sub Edx,0x18
		Mov Dword Ptr Ss : [Ebp-0x14],Edx
		Jmp Address1
		EXIT:
		Jmp Address2
	}
}

__declspec(naked) void EncDecOpenObj() 
{
	static DWORD Address1 = 0x005F34BE;
	static DWORD Address2 = 0x005F34BE;

	_asm
	{
		Push 0
		Push 0x18
		Mov Edx, Dword Ptr Ss : [Ebp-0x18]
		Push Edx
		Mov Eax, Dword Ptr Ss : [Ebp-0x10]
		Push Eax
		Mov Ecx, Dword Ptr Ss : [Ebp-0x8]
		Push Ecx
		Call[EncDecDecryptFile]
		Add Esp,0x14
		Test Eax,Eax
		Je EXIT
		Mov Edx, Dword Ptr Ss : [Ebp-0x18]
		Sub Edx,0x18
		Mov Dword Ptr Ss : [Ebp-0x18],Edx
		Jmp Address1
		EXIT:
		Jmp Address2
	}
}