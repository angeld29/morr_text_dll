/*

Copyright (C) 2004-2005 Angel Death 

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the included (LICENSE.txt) GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
//////////////////////////////////////////////////////////////////////
// mw_layout
// -------------------------------------------------------------------
// $Id: mw_layout.h,v 1.2 2005-09-15 17:20:13 AngelD Exp $ 
//////////////////////////////////////////////////////////////////////

#pragma once

#include "define.h"

typedef enum { MW_UNKNOWN = 0, MW_MORROWIND = 1, MW_TRIBUNAL, MW_BLOODMOON }mw_version_t;
#define MORROWIND_CRC -1
#define TRIBUNAL_CRC 0x6E8390C1 
#define BLOODMOON_CRC 0x385688af 
extern mw_version_t mw_version;
extern DWORD exe_crc;

extern DWORD* gamedatap;
extern DWORD con_hook_error_exit;
extern DWORD con_hook_normal_exit;
extern DWORD hook_addr_console;


extern void (*game_con_printf) (DWORD,char*,...);
extern void (*game_popup_print) (char*,DWORD ,DWORD );


//Dialog engine 
extern DWORD hook_addr_dictstr;
extern DWORD hook_addr_travel_printf;
extern DWORD hook_addr_alphavit_prn1;
extern DWORD hook_addr_alphavit_prn2;
extern DWORD hook_addr_alphavit_cmp;
extern DWORD hook_addr_checktopic;
extern DWORD hook_addr_mark_topic;
extern DWORD addr_char_convert_tbl1;
extern DWORD addr_char_convert_tbl2;
extern DWORD addr_page_break_str;

//journal convertsion tribunal & bloodmoon only
extern DWORD hook_addr_QuestsParse; 
extern DWORD addr_journal_parse;

//keyboard
extern DWORD hook_addr_EnterChar;
extern DWORD hook_addr_EnterCharMultiString;
extern DWORD hook_addr_GetKeyData;

extern DWORD unarmored_fix_addr;
extern DWORD hook_addr_enter_menu;
extern DWORD hook_addr_leave_menu;
extern DWORD addr_update_ac;

//items_info
extern DWORD hook_addr_item_info;
extern DWORD addr_item_info_normal_exit;
extern DWORD addr_item_info_my_exit;

extern UCHAR drive;
BOOL DetectVersion();
