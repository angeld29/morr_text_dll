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
/////////////////////////////////////////////////////////////////////////////
// HelperFunctions.cpp
// --------------------------------------------------------------------------
// $Id: HelperFunctions.cpp,v 1.2 2005-09-15 17:20:13 AngelD Exp $ 
// Helper functions
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// overloaded memcpy()
// --------------------------------------------------------------------------
// Takes care of giving the regions of memory the righ access rights needed
// when copying blocks of data.
/////////////////////////////////////////////////////////////////////////////
VOID   *PRIVATE newmemcpy( DWORD lpDest, DWORD lpSource, int len )
{
	DWORD   oldSourceProt, oldDestProt = 0;
	if( !lpDest || !lpSource )
	        return NULL;
	VirtualProtect( ( void * ) lpSource, len, PAGE_EXECUTE_READWRITE, &oldSourceProt );
	VirtualProtect( ( void * ) lpDest, len, PAGE_EXECUTE_READWRITE, &oldDestProt );
	memcpy( ( void * ) lpDest, ( void * ) lpSource, len );
	VirtualProtect( ( void * ) lpDest, len, oldDestProt, &oldDestProt );
	VirtualProtect( ( void * ) lpSource, len, oldSourceProt, &oldSourceProt );
	return ( void * ) lpDest;
};

/////////////////////////////////////////////////////////////////////////////
// overloaded memcpy()
// --------------------------------------------------------------------------
// Takes care of giving the regions of memory the righ access rights needed
// when copying blocks of data.
/////////////////////////////////////////////////////////////////////////////
VOID   *PRIVATE FillBytes( DWORD lpDest, BYTE ch, int len )
{
	DWORD   oldDestProt = 0;
	if( !lpDest )
	        return NULL;

	VirtualProtect( ( void * ) lpDest, len, PAGE_EXECUTE_READWRITE, &oldDestProt );
	memset( ( void * ) lpDest, ch, len );
	VirtualProtect( ( void * ) lpDest, len, oldDestProt, &oldDestProt );
	return ( void * ) lpDest;
};

/////////////////////////////////////////////////////////////////////////////
// 
/////////////////////////////////////////////////////////////////////////////
VOID   *PRIVATE PutDWord( DWORD lpDest, DWORD ch )
{
	DWORD   oldDestProt = 0;
	if( !lpDest )
	        return NULL;

	VirtualProtect( ( void * ) lpDest, 4, PAGE_EXECUTE_READWRITE, &oldDestProt );
	*( DWORD * ) ( lpDest ) = ch;
	VirtualProtect( ( void * ) lpDest, 4, oldDestProt, &oldDestProt );
	return ( void * ) lpDest;
};

VOID   *PRIVATE PutWord( DWORD lpDest, WORD ch )
{
	DWORD   oldDestProt = 0;
	if( !lpDest )
	        return NULL;

	VirtualProtect( ( void * ) lpDest, 4, PAGE_EXECUTE_READWRITE, &oldDestProt );
	*( WORD * ) ( lpDest ) = ch;
	VirtualProtect( ( void * ) lpDest, 4, oldDestProt, &oldDestProt );
	return ( void * ) lpDest;
};

/////////////////////////////////////////////////////////////////////////////
// Intercept()
// --------------------------------------------------------------------------
// Intercepts a code location to route it somewhere else.
// Also inserts original code at the destination.
/////////////////////////////////////////////////////////////////////////////

BOOL PRIVATE Intercept( int instruction, DWORD lpSource, DWORD lpDest, int len )
{
	/*char t[1024];
	   sprintf(t,"Code at %.8x intercepted and routed to %.8x",lpSource,lpDest);
	   fep->GamePrintVerbose(t); */
	if( !lpDest || !lpSource )
	        return FALSE;

	BYTE   *buffer = new BYTE[len];

	buffer[0] = instruction;
	*( DWORD * ) ( buffer + 1 ) = lpDest - ( lpSource + 5 );
	memset( buffer + 5, 0x90, len - 5 );	// nops
	newmemcpy( lpDest, lpSource, len );	// Patch in old code to new location
	newmemcpy( lpSource, ( DWORD ) buffer, len );	// Route old location to new
	delete[]  buffer;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// ReplaceCode()
// --------------------------------------------------------------------------
// Replace a code location to route it somewhere else.
/////////////////////////////////////////////////////////////////////////////

BOOL PRIVATE ReplaceCode( int instruction, DWORD lpSource, DWORD lpDest, int len )
{

	BYTE   *buffer = new BYTE[len];
	if( !lpDest || !lpSource )
	        return FALSE;

	buffer[0] = instruction;
	*( DWORD * ) ( buffer + 1 ) = lpDest - ( lpSource + 5 );
	memset( buffer + 5, 0x90, len - 5 );	// nops
	//newmemcpy(lpDest, lpSource, len);             // Patch in old code to new location
	newmemcpy( lpSource, ( DWORD ) buffer, len );	// Route old location to new
	delete[]  buffer;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// 
// --------------------------------------------------------------------------
// 
/////////////////////////////////////////////////////////////////////////////

/*void PRIVATE InterceptTable( PATCHCODESTRUCT * patchlist )
{

	for ( int i = 0; patchlist[i].Type != 0; i++ )
	{
		switch ( patchlist[i].Type )
		{
		case 1:
			Intercept( patchlist[i].Instruction, patchlist[i].Source, patchlist[i].Dest,
				   patchlist[i].PatchSize );
			break;
		case 2:
			ReplaceCode( patchlist[i].Instruction, patchlist[i].Source, patchlist[i].Dest,
				     patchlist[i].PatchSize );
			break;
		default:
			break;
		}
	}
};*/
