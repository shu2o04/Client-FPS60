	#include "stdafx.h"
	#include "HackCheck.h"
	#include "Offset.h"
	#include "Protect.h"
	#include "Util.h"
	#include "Common.h"
	typedef int(WINAPI*WSRECV)(SOCKET,char*,int,int);
	typedef int(WINAPI*WSSEND)(SOCKET,char*,int,int);

	WSRECV HookRecv;
	WSSEND HookSend;
	BYTE EncDecKey1;
	BYTE EncDecKey2;
	DWORD FrameValue = 0;
	DWORD SpeedValue = 0;
	DWORD MainTickCount = 0;
	DWORD SyncTickCount = 0;
	DWORD CountModifier = 0;
	DWORD DelayModifier = 0;
	DWORD HasteModifier = 0;
	DWORD SleepModifier = 0;
	DWORD SpeedModifier1 = 0;
	DWORD SpeedModifier2 = 0;
	DWORD ModelModifier1 = 0;
	DWORD ModelModifier2 = 0;
	DWORD ModelModifier3 = 0;

	void DecryptData(BYTE* lpMsg,int size) // OK
	{
		for(int n=0;n < size;n++)
		{
			lpMsg[n] = (lpMsg[n]^EncDecKey1)-EncDecKey2;
		}
	}

	void EncryptData(BYTE* lpMsg,int size) // OK
	{
		for(int n=0;n < size;n++)
		{
			lpMsg[n] = (lpMsg[n]+EncDecKey2)^EncDecKey1;
		}
	}

	bool CheckSocketPort(SOCKET s) // OK
	{
		SOCKADDR_IN addr;
		int addr_len = sizeof(addr);

		if(getpeername(s,(SOCKADDR*)&addr,&addr_len) == SOCKET_ERROR)
		{
			return 0;
		}

		if(PORT_RANGE(ntohs(addr.sin_port)) == 0)
		{
			return 0;
		}

		return 1;
	}

	int WINAPI MyRecv(SOCKET s, char* buf, int len, int flags) {
		int result = HookRecv(s, (char*)buf, len, flags);

		if (result == SOCKET_ERROR || result == 0) {
			return result;
		}

		if (CheckSocketPort(s) != 0) {
			if (result > 3) {
				DecryptData((BYTE*)buf + 3, result - 3);
			}
		}

		return result;
	}

	int WINAPI MySend(SOCKET s, char* buf, int len, int flags) // OK
	{
		// Chỉ mã hóa khi cần thiết
		if (CheckSocketPort(s) != 0)
		{
			EncryptData((BYTE*)buf, len); // Mã hóa dữ liệu
		}

		return HookSend(s, buf, len, flags);
	}


	_declspec(naked) void CheckTickCount1() // OK
	{
		static DWORD CheckTickCountAddress1 = 0x004DA29B;

		_asm
		{
			Mov Dword Ptr Ss:[Ebp-0x68],0x00
			Mov Edx,MainTickCount
			Mov Dword Ptr Ss:[Ebp-0x74],Edx
			Call Dword Ptr Ds:[GetTickCount]
			Mov MainTickCount,Eax
			Mov SyncTickCount,Eax
			Jmp [CheckTickCountAddress1]
		}
	}

#if(FPS_60 == 1)
	_declspec(naked) void CheckTickCount2() // OK
	{
		static DWORD CheckTickCountAddress1 = 0x004DA3F0;
		static const int SpeedMultiplier = 12.5;
		static const int SpeedDivisor = 10;

		_asm
		{
			// Cắt bớt các phép toán và chỉ sử dụng những gì cần thiết
			Mov Ecx, Dword Ptr Ss : [Ebp - 0x6C]
			Mov CountModifier, Ecx
			Mov Edx, Dword Ptr Ss : [Ebp - 0x74]
			Mov DelayModifier, Edx
			Mov Ecx, Dword Ptr Ss : [Ebp - 0x178]
			Mov HasteModifier, Ecx
			Mov Edx, Dword Ptr Ds : [MAIN_VIEWPORT_STRUCT]
			Mov Ecx, Dword Ptr Ds : [Edx + 0x214]
			Mov SpeedModifier1, Ecx
			Mov Edx, Dword Ptr Ds : [MAIN_VIEWPORT_STRUCT]
			Mov Ecx, Dword Ptr Ds : [Edx + 0x218]
			Mov SpeedModifier2, Ecx

			// Thực hiện phép toán cơ bản hơn
			Call Dword Ptr Ds : [GetTickCount]
			Mov MainTickCount, Eax
			Sub Eax, Dword Ptr Ss : [Ebp - 0x74]

			// Giảm thiểu phép toán phức tạp trong khi tính toán tốc độ
			Mov Ecx, SpeedMultiplier
			Mul Ecx
			Mov Ecx, SpeedDivisor
			Div Ecx
			Mov Dword Ptr Ss : [Ebp - 0x68] , Eax

			// Tiến hành kiểm tra thông số và so sánh
			Mov Ecx, Dword Ptr Ss : [Ebp - 0x6C]
			Cmp CountModifier, Ecx
			Jnz HACK
			Mov Edx, Dword Ptr Ss : [Ebp - 0x74]
			Cmp DelayModifier, Edx
			Jnz HACK
			Mov Ecx, Dword Ptr Ss : [Ebp - 0x178]
			Cmp HasteModifier, Ecx
			Jnz HACK
			Mov Ecx, Dword Ptr Ds : [MAIN_VIEWPORT_STRUCT]
			Mov Edx, Dword Ptr Ds : [Ecx + 0x214]
			Cmp SpeedModifier1, Edx
			Jnz HACK
			Mov Ecx, Dword Ptr Ds : [MAIN_VIEWPORT_STRUCT]
			Mov Edx, Dword Ptr Ds : [Ecx + 0x218]
			Cmp SpeedModifier2, Edx
			Jnz HACK

			// Đảm bảo rằng chỉ thực hiện các phép toán khi cần thiết
			CONTINUE :
			Mov Ecx, Dword Ptr Ss : [Ebp - 0x178]
				Add Ecx, Dword Ptr Ss : [Ebp - 0x68]
				Mov Dword Ptr Ss : [Ebp - 0x6C] , Ecx
				Jmp[CheckTickCountAddress1]

				HACK :
				Push 0
				Call Dword Ptr Ds : [ExitProcess]
		}
	}
#endif





	void InitHackCheck() // OK
	{
		WORD EncDecKey = 0;
		for(int n=0;n < sizeof(gProtect.m_MainInfo.CustomerName);n++)
		{
			EncDecKey += (BYTE)(gProtect.m_MainInfo.CustomerName[n]^gProtect.m_MainInfo.ClientSerial[(n%sizeof(gProtect.m_MainInfo.ClientSerial))]);
		}
		EncDecKey1 = (BYTE)0xF1;
		EncDecKey2 = (BYTE)0x1A; //default 76
		EncDecKey1 += LOBYTE(EncDecKey);
		EncDecKey2 += HIBYTE(EncDecKey);
		HookRecv = *(WSRECV*)(0x00D227B0);
		HookSend = *(WSSEND*)(0x00D227F8);
		SetDword(0x00D227B0,(DWORD)&MyRecv);
		SetDword(0x00D227F8,(DWORD)&MySend);
	}