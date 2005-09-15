// morr_text_dll.cpp : Defines the entry point for the DLL application.
// $Id: mw_layout.cpp,v 1.2 2005-09-15 17:20:13 AngelD Exp $ 
//

#include "stdafx.h"

mw_version_t mw_version = MW_UNKNOWN;
DWORD exe_crc = 0;

DWORD* gamedatap;
DWORD con_hook_error_exit;
DWORD con_hook_normal_exit;
DWORD hook_addr_console;


void (*game_con_printf) (DWORD,char*,...);
void (*game_popup_print) (char*,DWORD ,DWORD );


//Dialog engine 
DWORD hook_addr_dictstr;
DWORD hook_addr_travel_printf;
DWORD hook_addr_alphavit_prn1;
DWORD hook_addr_alphavit_prn2;
DWORD hook_addr_alphavit_cmp;
DWORD hook_addr_checktopic;
DWORD hook_addr_mark_topic;
DWORD addr_char_convert_tbl1;
DWORD addr_char_convert_tbl2;
DWORD addr_page_break_str;

//journal convertsion tribunal & bloodmoon only
DWORD hook_addr_QuestsParse; 
DWORD addr_journal_parse;

//keyboard
DWORD hook_addr_EnterChar;
DWORD hook_addr_EnterCharMultiString;
DWORD hook_addr_GetKeyData;

//items_info
DWORD hook_addr_item_info;
DWORD addr_item_info_normal_exit;
DWORD addr_item_info_my_exit;

DWORD unarmored_fix_addr;
DWORD hook_addr_enter_menu;
DWORD hook_addr_leave_menu;
DWORD hook_addr_gameframe;
DWORD addr_update_ac;

void setup_mw_layout()
{
}
void setup_tribunal_layout()
{
	 gamedatap = (DWORD*)0x7BE11C;
         con_hook_error_exit = 0x4FA09E;
         con_hook_normal_exit = 0x4F9F86;
         hook_addr_console = 0x4F9F80;

         game_con_printf = (void (__cdecl *)(DWORD,char *,...))0x40F990;
         game_popup_print = (void (__cdecl *)(char *,DWORD ,DWORD ))0x5F30E0;


         //Dialog engine 
         hook_addr_dictstr			= 0x5768fe;
         hook_addr_travel_printf		= 0x613476;

         hook_addr_alphavit_prn1		= 0x5D1B3C;
         hook_addr_alphavit_prn2		= 0x5D1C8E;
         hook_addr_alphavit_cmp		        = 0x5D18A8;
         hook_addr_checktopic			= 0x40b8d2;
         hook_addr_mark_topic			= 0x4afc85;
         addr_char_convert_tbl1		       = 0x76eafc;
         addr_char_convert_tbl2		       = 0x78bb88;
         addr_page_break_str		       = 0x76fc48;

         //journal convertsion tribunal & bloodmoon only
         hook_addr_QuestsParse		= 0x431d91; 
         addr_journal_parse			= 0x4b0910;

         //keyboard
         hook_addr_EnterChar			= 0x645119;
         hook_addr_EnterCharMultiString = 0x63eb72;
         hook_addr_GetKeyData			= 0x406754;

         unarmored_fix_addr			= 0x549B4D;
         hook_addr_enter_menu                   = 0x58f4d0;
         hook_addr_leave_menu                   = 0x58F660;
         addr_update_ac                         = 0x5C7F30;

         //items_info
         hook_addr_item_info			= 0x58B676;
         addr_item_info_normal_exit	= 0x58B67B;
         addr_item_info_my_exit		= 0x58B90A;
         
         hook_addr_gameframe = 0x0416FE7;

}
void setup_bloodmoon_layout()
{
		 gamedatap = (DWORD*)0x7C67dC;
         con_hook_error_exit = 0x4FCE3E;
         con_hook_normal_exit = 0x4FCD26;
         hook_addr_console = 0x4fcd20;

         game_con_printf = (void (__cdecl *)(DWORD,char *,...))0x40f970;
         game_popup_print = (void (__cdecl *)(char *,DWORD ,DWORD ))0x5F90C0;


         //Dialog engine 
         hook_addr_dictstr			= 0x57c6de;
         hook_addr_travel_printf		= 0x6194b1;
         hook_addr_alphavit_prn1		= 0x5d783c;
         hook_addr_alphavit_prn2		= 0x5d798e;
         hook_addr_alphavit_cmp		= 0x5d75a8;
         hook_addr_checktopic			= 0x40b872;
         hook_addr_mark_topic			= 0x4b1ff5;
         addr_char_convert_tbl1		= 0x775afc;
         addr_char_convert_tbl2		= 0x7934b8;
         addr_page_break_str			= 0x776cd0;

         //journal convertsion tribunal & bloodmoon only
         hook_addr_QuestsParse		= 0x432561; 
         addr_journal_parse			= 0x4b2c50;

         //keyboard
         hook_addr_EnterChar			= 0x64b319;
         hook_addr_EnterCharMultiString = 0x644d72;
         hook_addr_GetKeyData			= 0x4066b4;

         unarmored_fix_addr			= 0x0054d87d;
         hook_addr_enter_menu                   = 0x595020;
         hook_addr_leave_menu                   = 0x5951b0;
         addr_update_ac                         = 0x5CDC30;

         //items_info
         hook_addr_item_info			= 0x591219;
         addr_item_info_normal_exit	= 0x59121E;
         addr_item_info_my_exit		= 0x59146B;

         hook_addr_gameframe = 0x417227;
}
struct section_head {
	char    name[8];
	DWORD   VirtSize, RVA, PhysSize, FileOffset;
};
DWORD   crc32( DWORD crc, PBYTE buf, int len );
DWORD CalcExeCRC()
{
	section_head morr_text_head;
	newmemcpy( ( DWORD ) & morr_text_head, 0x400228, sizeof( section_head ) );

	if( strcmp(morr_text_head.name,".text") || morr_text_head.RVA != 0x1000 )
		return 0;
	PBYTE   section_code = new BYTE[morr_text_head.VirtSize];
	newmemcpy( ( DWORD ) section_code, 0x400000 + morr_text_head.RVA, morr_text_head.VirtSize );

	exe_crc = crc32( 0, section_code, morr_text_head.VirtSize );
#ifndef AngelPROTECT
	if( GetPrivateProfileInt("General","ShowCRC",0,".\\Angel.ini"))
	{
		FILE*f=fopen("crc.txt","wt");
		fprintf(f,"%8.8x",exe_crc);
		fclose(f);
	}
#endif
	delete[]section_code;
	return exe_crc;
}
BOOL DetectVersion()
{
	DWORD crc = CalcExeCRC();
	if( crc == BLOODMOON_CRC )
	{
		setup_bloodmoon_layout();
		mw_version = MW_BLOODMOON;
		return TRUE;
	}
	if( crc == TRIBUNAL_CRC )
	{
		setup_tribunal_layout();
		mw_version = MW_TRIBUNAL;
		return TRUE;
	}
	if( crc == MORROWIND_CRC )
	{
		setup_mw_layout();
		mw_version = MW_MORROWIND;
		return TRUE;
	}
	return FALSE;
}