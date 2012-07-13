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
// Cdcheck.cpp
// -------------------------------------------------------------------
// $Id: cdcheck.cpp,v 1.1 2005-09-06 19:02:30 AngelD Exp $ 
// Cdcheck
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>

//#ifdef AngelPROTECT

//#define CD_CHECK_GET_SIZE
#define SHOW_MESSAGE_BOX

const char NOCDMSG[] = "Вставьте CD игры Morrowind";
char    CDLABEL[] = "MORROWIND";

char    checkname[] = "C:\\Video\\mw_intro.bik";
const ULARGE_INTEGER CorrectDiskSize = { 0x287a0000, 0 };	//{0x287b4000,0};

UCHAR   drive = 0;

BOOL    CheckDriveSize( char c );

char CD_Check(  )
{

	DWORD   size = 1000, i, tmp;

	char    drives[1000], label[20] /*,path[1000],fname[1000],command[1000] */ , fsname[1000];

	size = GetLogicalDriveStrings( 500, drives );
	drive = 0;
	for ( ;; )
	{
		for ( i = 0; i < size / 4; i++ )
		{
			if ( GetDriveType( drives + i * 4 ) == 5 )
			{
				if ( !GetVolumeInformation( drives + i * 4, label, 20, NULL, &tmp, &tmp, fsname, 100 ) )
					continue;
				CharUpperBuff( label, lstrlen( label ) );
				CharUpperBuff( fsname, lstrlen( fsname ) );
				CharUpperBuff( CDLABEL, lstrlen( CDLABEL ) );
				if ( ( !strcmp( label, CDLABEL ) ) && ( !strcmp( fsname, "CDFS" ) ) )
				{

					*checkname = *( drives + i * 4 );
					if ( ( GetFileAttributes( checkname ) != -1 ) && CheckDriveSize( *checkname ) )
						drive = *( drives + i * 4 );
				};
			};
		};
		if ( drive )
			break;
#ifdef SHOW_MESSAGE_BOX
		if ( MessageBox( NULL, NOCDMSG, "Ошибка", MB_OKCANCEL | MB_ICONERROR ) == IDCANCEL )
			TerminateProcess( GetCurrentProcess(  ), -1 );	//exit(-1);
#else
		return 0;
#endif
	};

	return drive;
}

BOOL CheckDriveSize( char c )
{
	char    tmp[4];

	sprintf( tmp, "%c:\\", c );

	ULARGE_INTEGER i64FreeBytesToCaller, i64TotalBytes, i64FreeBytes;

	if ( !GetDiskFreeSpaceEx( tmp,
				  ( PULARGE_INTEGER ) & i64FreeBytesToCaller,
				  ( PULARGE_INTEGER ) & i64TotalBytes, ( PULARGE_INTEGER ) & i64FreeBytes ) )
		return FALSE;

#ifdef CD_CHECK_GET_SIZE
	char    ttmp[50];

	sprintf( ttmp, "%8.8x %8.8x - %8.8x %8.8x ",
		 i64TotalBytes.HighPart, i64TotalBytes.LowPart, CorrectDiskSize.HighPart, CorrectDiskSize.LowPart );
	MessageBox( NULL, ttmp, tmp, MB_OK );
#endif

	if ( ( i64TotalBytes.HighPart != CorrectDiskSize.HighPart ) ||
	     ( i64TotalBytes.LowPart < CorrectDiskSize.LowPart ) )
		return FALSE;

	return TRUE;
}

//#endif //Protect
