#include "stdafx.h"
#include "Fix.h"
#include "User.h"
#include "Util.h"
#include "Defines.h"
#include "Object.h"
#include "Util.h"
#include "TMemory.h"
#include "Import.h"
#include "Interface.h"


cFix gFix;

//=============================================================================================================
//                     Fix Agilidad
//=============================================================================================================

static DWORD ATTACK_RET = 0x00550A16;
static WORD CLASS = 0;
static WORD STR_SPEED = 0;
static WORD MAG_SPEED = 0;

__declspec(naked) void FixAttackSpeed()
{
    _asm
    {
        MOV EAX, DWORD PTR DS : [0x8128AC8]
        MOVZX ECX, WORD PTR DS : [EAX + 0xB]
        MOV CLASS, CX
        MOVZX ECX, WORD PTR DS : [EAX + 0x54]
        MOV STR_SPEED, CX
        MOVZX ECX, WORD PTR DS : [EAX + 0x60]
        MOV MAG_SPEED, CX
    }
    // --------------------------------------------

    gObjUser.MagickAttack = gObjUser.GetActiveSkill();

    // -> Elf
    if (CLASS == Elf || CLASS == MuseElf || CLASS == HightElf)
    {
        if (gObjUser.MagickAttack == 52 ||
            gObjUser.MagickAttack == 51 ||
            gObjUser.MagickAttack == 424 ||
            gObjUser.MagickAttack == 416)
        {
            if (STR_SPEED > 400)
            {
                STR_SPEED = 400;
            }
        }

        if (gObjUser.MagickAttack == 24 ||   //Fix Skill Triple Shot
            gObjUser.MagickAttack == 414)
        {
            if (STR_SPEED > 600)
            {
                STR_SPEED = 600;
            }
        }
    }
    // -> Magic Gladiator

    if (gObjUser.MagickAttack == 55 ||
        gObjUser.MagickAttack == 490)
    {
        if (STR_SPEED > 1368)
        {
            STR_SPEED = 1368;
        }
    }

    if (gObjUser.MagickAttack == 56 ||
        gObjUser.MagickAttack == 482)
    {
        if (STR_SPEED > 801)
        {
            STR_SPEED = 801;
        }
    }

    if (gObjUser.MagickAttack == 262 ||
        gObjUser.MagickAttack == 558 ||
        gObjUser.MagickAttack == 264 ||
        gObjUser.MagickAttack == 560)
    {
        if (STR_SPEED > 5002)
        {
            STR_SPEED = 5002;
        }
    }

    if (gObjUser.MagickAttack == 265)
    {
        if (STR_SPEED > 4502)
        {
            STR_SPEED = 4502;
        }
    }

    // --------------------------------------------
    _asm
    {
        MOVZX ECX, WORD PTR DS : [STR_SPEED]
        MOV DWORD PTR SS : [EBP - 0x28] , ECX
        FILD DWORD PTR SS : [EBP - 0x28]
        FMUL QWORD PTR DS : [0x0D27C88] ; FLOAT 0.0010007200189989805
        FSTP DWORD PTR SS : [EBP - 0x10]
        MOVZX EAX, WORD PTR DS : [MAG_SPEED]
        MOV DWORD PTR SS : [EBP - 0x2C] , EAX
        FILD DWORD PTR SS : [EBP - 0x2C]
        FMUL QWORD PTR DS : [0x0D27C88] ; FLOAT 0.0010007200189989805
        FSTP DWORD PTR SS : [EBP - 0x0C]
        MOVZX EDX, WORD PTR DS : [MAG_SPEED]
        MOV DWORD PTR SS : [EBP - 0x30] , EDX
        FILD DWORD PTR SS : [EBP - 0x30]
        FMUL QWORD PTR DS : [0x0D281C0] ; FLOAT 0.002000000094994903
        FSTP DWORD PTR SS : [EBP - 0x4]
        FLD DWORD PTR SS : [EBP - 0x10]

        JMP ATTACK_RET
    }
}
// --------------------------------------------------------------------------------------------   
static DWORD RETURN_attack2 = 0x0055157D;

__declspec(naked) void FixAttackSpeed2()
{
    _asm
    {
        MOVZX EDX, WORD PTR DS : [STR_SPEED]
        JMP RETURN_attack2
    }
}

void InitAttackSpeed()
{
    SetByte(0x00649E24 + 3, 14);   //-> Test 1
    SetByte(0x00556C32 + 6, 2);   //-> Test 2
    SetOp((LPVOID)0x005509CE, (LPVOID)FixAttackSpeed, ASM::JMP);
    SetOp((LPVOID)0x00551573, (LPVOID)FixAttackSpeed2, ASM::JMP);
}
//=============================================================================================================
//=============================================================================================================

void cFix::Load()
{
    SetOp((LPVOID)0x00559539, (LPVOID)this->CalculateAttackSpeed, ASM::CALL);
}

void cFix::CalculateAttackSpeed(lpCharObj lpUser, LPVOID EDX)
{
    //pGetAttackSpeed();

    //if (lpUser->AttackSpeed > 3000)
    //{
    ////lpUser->MagicSpeed = (WORD)800 + *(DWORD*)0x986C1CC;
    ////gVisualFix.AttackSpeed = lpUser->AttackSpeed;
    //lpUser->AttackSpeed = (WORD)3000 + *(DWORD*)0x986C1CC;
    //
    //}

    switch (lpUser->Class)
    {
        //gInterface.DrawFormat(eWhite180,  80, 80, 45, 1, "%f %f", pFrameSpeed1, pFrameSpeed2);

    case eClassCode::Monk:
    case eClassCode::FirstMaster:
    {
        //FIX RF SKILL BEAST UPPERCUT
        if (gObjUser.GetActiveSkill() == 261 || gObjUser.GetActiveSkill() == 552 || gObjUser.GetActiveSkill() == 555)
        {
            SetDouble(&pFrameSpeed1, 0.0002000);
            SetDouble(&pFrameSpeed2, 0.0001000);

            //lpUser->AttackSpeed = 10;

            //SetOp((LPVOID)0x00559539, (LPVOID)lpUser->AttackSpeed, ASM::CALL);

        }
        else
        {
            SetDouble(&pFrameSpeed1, 0.0040000);
            SetDouble(&pFrameSpeed2, 0.0020000);

        }
    }

    }


}

