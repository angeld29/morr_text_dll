// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
// $Id: stdafx.h,v 1.2 2005-09-15 17:20:13 AngelD Exp $ 
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <define.h>
#include <mw_layout.h>
#include <HelperFunctions.h>
#include <stdio.h>

void NoCDPatch();
void FixLoadBsa();

void WarningPrn(char*error,...);
void Con_Printf( char *format, ... );

BOOL InitDialogEngine( void );
void InitMWKeyboard();
void InitItemInfo();
void InitConsole();
void InitArmorFix();
extern BOOL inmenu;

// TODO: reference additional headers your program requires here
