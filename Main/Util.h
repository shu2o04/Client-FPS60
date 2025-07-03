#pragma once

struct REFERENCE_INFO
{
	DWORD count;
	DWORD start;
	DWORD end;
};

struct REFERENCE_BASE
{
	DWORD address;
};

struct REFERENCE_DATA
{
	DWORD address;
	DWORD value;
};
void SetByte(DWORD offset,BYTE value);
void SetWord(DWORD offset,WORD value);
DWORD SetByte1(const LPVOID dwOffset, const BYTE btValue);

void SetDword(DWORD offset,DWORD value);
void SetFloat(DWORD offset,float value);
void SetDouble(DWORD offset,double value);
void SetCompleteHook(BYTE head,DWORD offset,...);
void MemoryCpy(DWORD offset,void* value,DWORD size);
void MemorySet(DWORD offset,DWORD value,DWORD size);
void VirtualizeOffset(DWORD offset,DWORD size);
void PacketArgumentEncrypt(char* out_buff,char* in_buff,int size);
char* ConvertModuleFileName(char* name);
void LoadReferenceAddressTable(HMODULE mod,char* name,DWORD address);
void SetJmp(DWORD offset,DWORD size,LPVOID function);
DWORD WriteMemory2(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize);
DWORD SetOp(const DWORD dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd);
DWORD SetRange(const DWORD dwAddress, const USHORT wCount, const BYTE btValue);
DWORD GetFileCRC(const char* szFileName);

//--
DWORD WriteMemoryT(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize);
DWORD SendPacked(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd);
DWORD SendPacked(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd, const BYTE cmd2);
DWORD SendPacked(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd, const BYTE cmd2, const BYTE cmd3);
//--

extern DWORD FrameValue;
extern DWORD MainTickCount;
extern BYTE NewAddressData1[240];
extern BYTE NewAddressData2[240];
extern BYTE NewAddressData3[6000];

void MsgBox(char* message,...);
#if ACTIVE_FIX_DISMOVE
#include <cstdint>

template<typename FuncType>
std::uintptr_t FuncToDWORD(FuncType Func)
{
    union FunctionPointerConverter
    {
        FuncType Func;
        std::uintptr_t functionAddress;
    };
    FunctionPointerConverter converter;
    converter.Func = Func;
    return converter.functionAddress;
}
#endif