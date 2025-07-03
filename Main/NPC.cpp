#include "stdafx.h"
#include "Item.h"
#include "NPC.h"
#include "TMemory.h"
#include "Import.h"
#include "Defines.h"
#include "Util.h"
#include "CustomMessage.h"
// ----------------------------------------------------------------------------------------------

NPC gNPC;
// ----------------------------------------------------------------------------------------------

void NPC::Load() {
	SetRange((LPVOID)0x0057FCCF, 5, ASM::NOP);
	SetOp((LPVOID)0x0057FCCF, (LPVOID) this->ElfSoldier, ASM::JMP);
	// ----
	SetRange((LPVOID)0x005842B1, 5, ASM::NOP);
	SetOp((LPVOID)0x005842B1, (LPVOID) this->Marlon, ASM::JMP);
	//// ----
	SetRange((LPVOID)0x005852E4, 5, ASM::NOP);
	SetOp((LPVOID)0x005852E4, (LPVOID) this->ChaosCardMaster, ASM::JMP);
	// ----
	SetRange((LPVOID)0x00584A4E, 5, ASM::NOP);
	SetOp((LPVOID)0x00584A4E, (LPVOID) this->Guard1, ASM::JMP);
	// ----
	SetRange((LPVOID)0x00584B82, 5, ASM::NOP);
	SetOp((LPVOID)0x00584B82, (LPVOID) this->Guard2, ASM::JMP);
	// ----
	SetRange((LPVOID)0x00582FE6, 5, ASM::NOP);
	SetOp((LPVOID)0x00582FE6, (LPVOID) this->CursedWizard, ASM::JMP);
}
// ----------------------------------------------------------------------------------------------

Naked(NPC::ElfSoldier) {
	static ObjectPreview * gPreview;
	//----
	_asm {
		MOV ECX, DWORD PTR SS : [EBP + 0x08]
			MOV gPreview, ECX
	}
	// ----
	gPreview->HelmSlot = ITEM2(7, 24);
	gPreview->ArmorSlot = ITEM2(8, 24);
	gPreview->PantsSlot = ITEM2(9, 24);
	gPreview->GlovesSlot = ITEM2(10, 24);
	gPreview->BootsSlot = ITEM2(11, 24);
	gPreview->WeaponFirstSlot = ITEM2(4, 21);
	gPreview->WeaponSecondSlot = ITEM2(4, 1);
	gPreview->WingsSlot = ITEM2(12, 3);
	// ----
	gPreview->HelmLevel = 15;
	gPreview->ArmorLevel = 15;
	gPreview->PantsLevel = 15;
	gPreview->GlovesLevel = 15;
	gPreview->BootsLevel = 15;
	gPreview->WeaponFirstLevel = 15;
	gPreview->WeaponSecondLevel = 15;

	//
	gPreview->HelmExcellent = 63;
	gPreview->ArmorExcellent = 63;
	gPreview->PantsExcellent = 63;
	gPreview->GlovesExcellent = 63;
	gPreview->BootsExcellent = 63;
	gPreview->WeaponFirstExcellent = 63;
	gPreview->WeaponSecondExcellent = 63;
	// ----
	_asm {
		MOV ECX, 0x0057FD5B
			JMP ECX
	}
}
//// ----------------------------------------------------------------------------------------------

Naked(NPC::Marlon) {
	static ObjectPreview * gPreview;
	//----
	_asm {
		MOV ECX, DWORD PTR SS : [EBP - 0x14]
			MOV gPreview, ECX
	}
	// ----
	gPreview->HelmSlot = ITEM2(7, 6);
	gPreview->ArmorSlot = ITEM2(8, 6);
	gPreview->PantsSlot = ITEM2(9, 6);
	gPreview->GlovesSlot = ITEM2(10, 6);
	gPreview->BootsSlot = ITEM2(11, 6);
	gPreview->WeaponFirstSlot = ITEM2(0, 22);
	gPreview->WeaponSecondSlot = ITEM2(0, 22);
	gPreview->WingsSlot = ITEM2(12, 5);
	// ----
	gPreview->HelmLevel = 15;
	gPreview->ArmorLevel = 15;
	gPreview->PantsLevel = 15;
	gPreview->GlovesLevel = 15;
	gPreview->BootsLevel = 15;
	gPreview->WeaponFirstLevel = 15;
	gPreview->WeaponSecondLevel = 15;

	//
	gPreview->HelmExcellent = 63;
	gPreview->ArmorExcellent = 63;
	gPreview->PantsExcellent = 63;
	gPreview->GlovesExcellent = 63;
	gPreview->BootsExcellent = 63;
	gPreview->WeaponFirstExcellent = 63;
	gPreview->WeaponSecondExcellent = 63;
	// ----
	_asm {
		MOV ECX, 0x00584354
			JMP ECX
	}
}
// ----------------------------------------------------------------------------------------------
//
Naked(NPC::ChaosCardMaster) {
	static ObjectPreview * gPreview;
	//----
	_asm {
		MOV ECX, DWORD PTR SS : [EBP - 0x14]
			MOV gPreview, ECX
	}
	// ----
	gPreview->HelmSlot = ITEM2(7, 18);
	gPreview->ArmorSlot = ITEM2(8, 18);
	gPreview->PantsSlot = ITEM2(9, 18);
	gPreview->GlovesSlot = ITEM2(10, 18);
	gPreview->BootsSlot = ITEM2(11, 18);
	gPreview->WeaponFirstSlot = ITEM2(5, 12);
	gPreview->WeaponSecondSlot = ITEM2(6, 13);
	gPreview->WingsSlot = ITEM2(12, 4);
	// ----
	gPreview->HelmLevel = 15;
	gPreview->ArmorLevel = 15;
	gPreview->PantsLevel = 15;
	gPreview->GlovesLevel = 15;
	gPreview->BootsLevel = 15;
	gPreview->WeaponFirstLevel = 15;
	gPreview->WeaponSecondLevel = 15;
	// ----
	gPreview->HelmExcellent = 63;
	gPreview->ArmorExcellent = 63;
	gPreview->PantsExcellent = 63;
	gPreview->GlovesExcellent = 63;
	gPreview->BootsExcellent = 63;
	gPreview->WeaponFirstExcellent = 63;
	gPreview->WeaponSecondExcellent = 63;
	// ----
	_asm {
		MOV ECX, 0x00585390
			JMP ECX
	}
}
// ----------------------------------------------------------------------------------------------

Naked(NPC::Guard1) {
	static ObjectPreview * gPreview;
	//----
	_asm {
		MOV ECX, DWORD PTR SS : [EBP - 0x14]
			MOV gPreview, ECX
	}
	// ----
	gPreview->HelmSlot = ITEM2(7, 18);
	gPreview->ArmorSlot = ITEM2(8, 18);
	gPreview->PantsSlot = ITEM2(9, 18);
	gPreview->GlovesSlot = ITEM2(10, 18);
	gPreview->BootsSlot = ITEM2(11, 18);
	gPreview->WeaponFirstSlot = ITEM2(5, 12);
	//gPreview->WeaponSecondSlot = ITEM2(6, 14);
	gPreview->WingsSlot = ITEM2(12, 4);
	// ----
	gPreview->HelmLevel = 15;
	gPreview->ArmorLevel = 15;
	gPreview->PantsLevel = 15;
	gPreview->GlovesLevel = 15;
	gPreview->BootsLevel = 15;
	gPreview->WeaponFirstLevel = 15;
	gPreview->WeaponSecondLevel = 15;
	// ----
	gPreview->HelmExcellent = 63;
	gPreview->ArmorExcellent = 63;
	gPreview->PantsExcellent = 63;
	gPreview->GlovesExcellent = 63;
	gPreview->BootsExcellent = 63;
	gPreview->WeaponFirstExcellent = 63;
	gPreview->WeaponSecondExcellent = 63;



	_asm {
		MOV ECX, 0x00584AB7
			JMP ECX
	}
}
// ----------------------------------------------------------------------------------------------

Naked(NPC::Guard2) {
	static ObjectPreview * gPreview;
	//----
	_asm {
		MOV ECX, DWORD PTR SS : [EBP - 0x14]
			MOV gPreview, ECX
	}
	// ----
	gPreview->HelmSlot = ITEM2(7, 9);
	gPreview->ArmorSlot = ITEM2(8, 9);
	gPreview->PantsSlot = ITEM2(9, 9);
	gPreview->GlovesSlot = ITEM2(10, 9);
	gPreview->BootsSlot = ITEM2(11, 9);
	gPreview->WeaponFirstSlot = ITEM2(2, 24);
	gPreview->WeaponSecondSlot = ITEM2(6, 13);

	gPreview->WingsSlot = ITEM2(12, 5);
	// ----
	gPreview->HelmLevel = 15;
	gPreview->ArmorLevel = 15;
	gPreview->PantsLevel = 15;
	gPreview->GlovesLevel = 15;
	gPreview->BootsLevel = 15;
	gPreview->WeaponFirstLevel = 15;
	gPreview->WeaponSecondLevel = 15;

	//
	gPreview->HelmExcellent = 63;
	gPreview->ArmorExcellent = 63;
	gPreview->PantsExcellent = 63;
	gPreview->GlovesExcellent = 63;
	gPreview->BootsExcellent = 63;
	gPreview->WeaponFirstExcellent = 63;
	gPreview->WeaponSecondExcellent = 63;


	gPreview->Class = BladeMaster;
	// ----
	_asm {
		MOV ECX, 0x00584BDC
			JMP ECX
	}
}

// ----------------------------------------------------------------------------------------------
Naked(NPC::CursedWizard) {
	static ObjectPreview * gPreview;
	//----
	_asm {
		MOV ECX, DWORD PTR SS : [EBP - 0x14]
			MOV gPreview, ECX
	}

	// ----
	gPreview->HelmSlot = ITEM2(7, rand() % 73);
	gPreview->ArmorSlot = ITEM2(8, rand() % 73);
	gPreview->PantsSlot = ITEM2(9, rand() % 73);
	gPreview->GlovesSlot = ITEM2(10, rand() % 73);
	gPreview->BootsSlot = ITEM2(11, rand() % 73);
	gPreview->WeaponFirstSlot = ITEM2(rand() % 5, rand() % 81);
	gPreview->WeaponSecondSlot = ITEM2(6, rand() % 45);

	if ((rand() % 100 + 1) % 2 == 0){
		gPreview->WingsSlot = ITEM2(12, rand() % 50);
	}

	// ----
	gPreview->HelmLevel = 15;
	gPreview->ArmorLevel = 15;
	gPreview->PantsLevel = 15;
	gPreview->GlovesLevel = 15;
	gPreview->BootsLevel = 15;
	gPreview->WeaponFirstLevel = 15;
	gPreview->WeaponSecondLevel = 15;
	// ----
	gPreview->HelmExcellent = rand() % 63;
	gPreview->ArmorExcellent = rand() % 63;
	gPreview->PantsExcellent = rand() % 63;
	gPreview->GlovesExcellent = rand() % 63;
	gPreview->BootsExcellent = rand() % 63;
	gPreview->WeaponFirstExcellent = rand() % 63;
	gPreview->WeaponSecondExcellent = rand() % 63;
	// ----


	gPreview->Class = SoulMaster;


	// ----
	_asm {
		MOV ECX, 0x00583099
			JMP ECX
	}
}
// ----------------------------------------------------------------------------------------------