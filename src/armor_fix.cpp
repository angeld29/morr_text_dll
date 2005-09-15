//////////////////////////////////////////////////////////////////////
// items_info.cpp
// -------------------------------------------------------------------
// $Id: armor_fix.cpp,v 1.1 2005-09-15 17:20:13 AngelD Exp $ 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

BOOL inmenu = TRUE;
void EnterMenu()
{
        inmenu = TRUE;
}
void LeaveMenu()
{
        inmenu = FALSE;
}
///////////////////////////////////////////////////
// 
// 
///////////////////////////////////////////////////
void __declspec(naked) EnterMenu_STUB()
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
		pushad
		call EnterMenu
		call [addr_update_ac]
                popad
		ret
	}
};

///////////////////////////////////////////////////
// 
// 
///////////////////////////////////////////////////
void __declspec(naked) LeaveMenu_STUB()
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
		pushad
		call LeaveMenu
                popad
		ret
	}
};
///////////////////////////////////////////////////
/*void ApplyACHook(float dmg, float ar)
{
        
}

void __declspec(naked) ApplyAC_STUB()
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
//		pushad
//                popad
		ret
	}
}*/
//////////////////////////////////////////////////////////////////////
// ItemInfo_Init()
// -------------------------------------------------------------------
// 
//////////////////////////////////////////////////////////////////////

void InitArmorFix()
{
        int fix_unarmored = GetPrivateProfileInt("Rules","fix_unarmored_bug",0,".\\Angel.ini");
	if(  fix_unarmored != 0 )
	{
/*	        if( fix_unarmored == 2)
	        {
	                ReplaceCode(INST_CALL, unarmored_fix_addr , (DWORD)&ApplyAC_STUB , 6); 
	                
	        }
	        else*/
		FillBytes(unarmored_fix_addr,0x90,6);
	}
        Intercept(INST_CALL, hook_addr_enter_menu , (DWORD)&EnterMenu_STUB , 6); 
        Intercept(INST_CALL, hook_addr_leave_menu , (DWORD)&LeaveMenu_STUB , 6); 
}



