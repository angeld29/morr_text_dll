//////////////////////////////////////////////////////////////////////
// items_info.cpp
// -------------------------------------------------------------------
// $Id: items_info.cpp,v 1.1 2005-09-06 19:02:30 AngelD Exp $ 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

///////////////////////////////////////////////////
// 
// 
///////////////////////////////////////////////////
void __declspec(naked) AMMO_dmg_STUB()
{
	__asm {
		nop									// Make room for original code
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		cmp eax, 4f4d4d41h // AMMO
		je done_my

		cmp eax, 4f4d5241h  // ARMO
		jmp [addr_item_info_normal_exit]
done_my:
                jmp  [addr_item_info_my_exit]

	}
};

//////////////////////////////////////////////////////////////////////
// ItemInfo_Init()
// -------------------------------------------------------------------
// 
//////////////////////////////////////////////////////////////////////

void InitItemInfo()
{
        ReplaceCode(INST_JMP, hook_addr_item_info , (DWORD)&AMMO_dmg_STUB , 5); 
}



