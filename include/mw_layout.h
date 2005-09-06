//////////////////////////////////////////////////////////////////////
// mw_layout
// -------------------------------------------------------------------
// $Id: mw_layout.h,v 1.1 2005-09-06 19:02:30 AngelD Exp $ 
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
//items_info
extern DWORD hook_addr_item_info;
extern DWORD addr_item_info_normal_exit;
extern DWORD addr_item_info_my_exit;

extern UCHAR drive;
BOOL DetectVersion();
