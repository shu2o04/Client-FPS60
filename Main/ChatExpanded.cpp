#include "StdAfx.h"
#include "ChatExpanded.h"
#include "Import.h"
#include "TMemory.h"
#include <atlstr.h>
#include "ToolKit.h"
#include "Defines.h"
#include "Object.h"
#include "Common.h"
#include "Protect.h"
ChatExpanded	gChatExpanded;
Naked(FixSysMsg1)
{
	__asm
	{
		cmp dword ptr ss:[ebp+0x10], 3
		je _true
		call NewCall
		jmp FixSysMsg1_FALSE
		_true:
		pop eax
		jmp FixSysMsg1_TRUE
	}
}
Naked(FixSysMsg2)
{
	__asm 
	{
		cmp dword ptr ss:[ebp+0x10], 3
		je _true
		call NewCall
		jmp FixSysMsg2_FALSE
		_true:
		pop eax
		jmp FixSysMsg2_TRUE
	}
}
Naked(FixSysMsg3)
{
	__asm 
	{
		cmp dword ptr ss:[ebp+0x10], 3
		je _true
		call NewCall
		jmp FixSysMsg3_FALSE
		_true:
		pop eax
		jmp FixSysMsg3_TRUE
	}
}
void ChatExpanded::Load()
{
	SetOp((LPVOID)oShowChatMessage_Call, (LPVOID)this->ShowChatMessage, ASM::CALL);
	SetOp((LPVOID)FixSysMsg1_Hook, FixSysMsg1, ASM::JMP);
	SetOp((LPVOID)FixSysMsg2_Hook, FixSysMsg2, ASM::JMP);
	SetOp((LPVOID)FixSysMsg3_Hook, FixSysMsg3, ASM::JMP);
}
void ChatExpanded::SetInstance(LPVOID Instance)
{
	this->Instance			= Instance;
	this->PosYBuff			= this->GetPosY();
	this->HeightBuff		= this->GetHeight();
	this->MessageCountBuff	= this->GetMessageCount();
	this->MessageTypeBuff	= this->GetMessageType();
	this->ScrollPosBuff		= this->GetScrollPos();
}
void ChatExpanded::Restore()
{
	this->SetPosX(this->PosXBuff);
	this->SetPosY(this->PosYBuff);
	this->SetHeight(this->HeightBuff);
	this->SetMessageCount(this->MessageCountBuff);
	this->SetMessageType(this->MessageTypeBuff);
	this->SetScrollPos(this->ScrollPosBuff);
}
void ChatExpanded::Switch()
{
	if( gChatExpanded.m_separate == 0 )
	{
		SetOp((LPVOID)oShowChatMessage_Call, (LPVOID)this->ShowChatMessage, ASM::CALL);
		SetOp((LPVOID)FixSysMsg1_Hook, FixSysMsg1, ASM::JMP);
		SetOp((LPVOID)FixSysMsg2_Hook, FixSysMsg2, ASM::JMP);
		SetOp((LPVOID)FixSysMsg3_Hook, FixSysMsg3, ASM::JMP);
		gChatExpanded.m_separate = 1;
	}
	else
	{
		SetOp((LPVOID)FixSysMsg1_Hook, (LPVOID)oNewCall, ASM::CALL);
		SetOp((LPVOID)FixSysMsg2_Hook, (LPVOID)oNewCall, ASM::CALL);
		SetOp((LPVOID)FixSysMsg3_Hook, (LPVOID)oNewCall, ASM::CALL);
		gChatExpanded.m_separate = 0;
	}
}
bool ChatExpanded::ShowChatMessage(LPVOID This, LPVOID EDX)
{
	if(gChatExpanded.m_separate == 0)
	{
		return pShowChatMessage(This);
	}
	#if(TAS_STYLE)
	gChatExpanded.SetInstance(This);
	gChatExpanded.SetPosX(2);
	gChatExpanded.SetPosY(230);
	gChatExpanded.SetHeight(100);
	gChatExpanded.SetMessageCount(5);
	pSetChatMessageType(This, 3);
	pShowChatMessage(This);
	gChatExpanded.Restore();
	return pShowChatMessage(This);
	#else
	gChatExpanded.SetInstance(This);
	gChatExpanded.SetPosX(2);
	gChatExpanded.SetPosY(150);
	gChatExpanded.SetHeight(100);
	gChatExpanded.SetMessageCount(5);
	pSetChatMessageType(This, 3);
	pShowChatMessage(This);
	gChatExpanded.Restore();
	return pShowChatMessage(This);
	#endif
}
