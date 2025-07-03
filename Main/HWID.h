#pragma once

#include "Protocol.h"

struct CG_HWID_SEND
{
	PSBMSG_HEAD	Head;
	char HardwareId[36];
	char DLLVersion[30];
	DWORD GameGuardCRC;
	DWORD VerifyCRC;
	DWORD MainDLLCRC;
	DWORD MainEXECRC;
};

class cHwid
{
public:
	bool GetPhysicalDriveSerialNumber(int PhysicalDriveNumber,char* PhysicalDriveSerial,int PhysicalDriveSerialSize);
	char* GetHardwareId();
	void SendHwid();
}; extern cHwid gHwid;