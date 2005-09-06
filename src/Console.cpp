//////////////////////////////////////////////////////////////////////
// Console.cpp
// -------------------------------------------------------------------
// $Id: Console.cpp,v 1.1 2005-09-06 19:02:30 AngelD Exp $ 
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
const DWORD Version = MAKELONG(3,00);

typedef struct gamecommandstruct_t
{
	char*	szName;
	BOOL	(PRIVATE *pFunc)(char** argv, int argc);
	char*	szUsage;
} GAMECOMMANDSTRUCT;

GAMECOMMANDSTRUCT* PRIVATE FindGameCommand(char* name);
BOOL PRIVATE GameCommandLineHelp(char** argv, int argc);
BOOL PRIVATE GameCommandLineVersion(char** argv, int argc);
BOOL PRIVATE GameCommandLineCredits(char** argv, int argc);
BOOL PRIVATE GameCommandLinePriority(char** argv, int argc);
BOOL PRIVATE GameCommandLineFPS(char** argv, int argc);
BOOL PRIVATE GameCommandLineDump(char** argv, int argc);
BOOL PRIVATE GameCommandLinePrn(char** argv, int argc);

GAMECOMMANDSTRUCT GameCommands[] = {
	{
	 "help",
	 GameCommandLineHelp,
	 " .help Выдает список команд"},
	{
	 "version",
	 GameCommandLineVersion,
	 " .version Displays detailed version information."},
	{
	 "dump",
	 GameCommandLineDump,
	 " .dump <f|d|u|w|b|s> <adress>"},
	{
	 "priority",
	 GameCommandLinePriority,
	 " .priority <1|2|3> Set process priority to <Normal|High|Realtime>"},
	{
	 "fps",
	  GameCommandLineFPS,
	 " .fps max <maxfps> Set maxfps\n"
	 },
	{
	 NULL,
	 }
};

//////////////////////////////////////////////////////////////////////
// Con_Printf
// -------------------------------------------------------------------
// pechat' v console
//////////////////////////////////////////////////////////////////////
void Con_Printf( char *format, ... )
{
	char    tmp[1024];
	va_list argptr;

	va_start( argptr, format );
	_vsnprintf( tmp, 1024, format, argptr );
	va_end( argptr );
	game_con_printf( *gamedatap, tmp );

}

//////////////////////////////////////////////////////////////////////
// FindGameCommand
// -------------------------------------------------------------------
// Returns pointer to a COMMANDSTRUCT
//////////////////////////////////////////////////////////////////////
GAMECOMMANDSTRUCT *PRIVATE FindGameCommand( char *name )
{
	GAMECOMMANDSTRUCT *gcs = GameCommands;

	while ( gcs->szName )
	{
		if ( !stricmp( gcs->szName, name ) )
			return gcs;
		gcs++;
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////
// GameCommandLine
// -------------------------------------------------------------------
// This is where we take a command line, tokenize it, and send it to
// the right destination :)
//////////////////////////////////////////////////////////////////////
BOOL PRIVATE GameCommandLine( char *raw )
{
	char   *p;
	char    buf[1024];
	char   *argv[1024];
	int     argc = 0;
	GAMECOMMANDSTRUCT *gcs;

	if ( 0 == raw )
		return FALSE;

	// Parse through the command line for tokens, string characters, and the 
	// command separator.

	// Copy the command line to a temporary buffer so we can mangle it.
	sprintf( buf, "%s", raw );

	// Initialize a few pointers to it.
	argv[0] = p = buf;

	while ( *p <= ' ' && *p != 0 )
	{
		p++;
	}
	//esli ne '.' to ne nasha komanda
	if ( *p != '.' )
		return FALSE;
	p++;
	// Did we reach the end of the command line already?
	if ( *p == 0 )
	{
		return FALSE;
	}
	// Make sure we're starting with argc count properly set.
	// This is important if we've encountered multiple commands via the
	// command separator.
	argc = 0;
	argv[argc++] = p;

	// Reset the loop flag.  This will only get set to true
	// when we find another command to execute i.e. via the
	// command separator.
	//game_con_history(raw,1,console_hren);
	while ( *p != 0 )
	{
		// Spaces are our token separator.
		if ( *p <= ' ' )
		{
			// Set the first space encountered to null.
			*( p++ ) = 0;
			// Parse past the rest until we get to the start of the next
			// token.
			while ( *p <= ' ' && *p != 0 )
			{
				p++;
			}

			// If we're not at the end of cmdline then
			// this must be the start of the next token.
			if ( *p != 0 )
			{
				argv[argc++] = p;
			}


		} else
		{
			// Parse through the token.
			p++;
		}
	}
	gcs = FindGameCommand( argv[0] );
	// Is this a built-in function ?

	if ( gcs )
	{
		//
		// If functions returns false, show usage help
		if ( !gcs->pFunc( argv, argc ) )
		{
			Con_Printf( "Usage:%s", gcs->szUsage );
		}
	} else
	{
		Con_Printf( "Unknown command:%s", argv[0] );
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// GameCommandLineHelp
// -------------------------------------------------------------------
// Handles command line help
//////////////////////////////////////////////////////////////////////
BOOL PRIVATE GameCommandLineHelp( char **argv, int argc )
{
	if ( argc > 1 )
		return FALSE;
	//
	// Header
	Con_Printf( "Available AngelConsole commands:" );
	for ( int i = 0; GameCommands[i].szName != NULL; i++ )
	{
		Con_Printf( " .%s", GameCommands[i].szName );
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// GameCommandLineVersion
// -------------------------------------------------------------------
// 
//////////////////////////////////////////////////////////////////////
BOOL PRIVATE GameCommandLineVersion( char **argv, int argc )
{
	Con_Printf( "Version %d.%.3d (%s@%s)", LOWORD( Version ), HIWORD( Version ), __DATE__, __TIME__ );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// GameCommandLineCredits
// -------------------------------------------------------------------
// 
//////////////////////////////////////////////////////////////////////
BOOL PRIVATE GameCommandLineCredits( char **argv, int argc )
{
	return FALSE;
}

//////////////////////////////////////////////////////////////////////
// GameCommandLinePriority
// -------------------------------------------------------------------
// 
//////////////////////////////////////////////////////////////////////
BOOL PRIVATE GameCommandLinePriority( char **argv, int argc )
{
	if ( argc != 2 )
		return FALSE;

	switch ( atoi( argv[1] ) )
	{
	case 1:
		if ( SetPriorityClass( GetCurrentProcess(  ), NORMAL_PRIORITY_CLASS ) )
			Con_Printf( "Priority set to Normal" );
		else
			Con_Printf( "Cannon set priority" );
		break;
	case 2:
		if ( SetPriorityClass( GetCurrentProcess(  ), HIGH_PRIORITY_CLASS ) )
			Con_Printf( "Priority set to High" );
		else
			Con_Printf( "Cannon set priority" );
		break;
	case 3:
		if ( SetPriorityClass( GetCurrentProcess(  ), REALTIME_PRIORITY_CLASS ) )
			Con_Printf( "Priority set to Realtime" );
		else
			Con_Printf( "Cannon set priority" );
		break;
	default:
		return FALSE;
	}


	return TRUE;
};

//////////////////////////////////////////////////////////////////////
// GameCommandLineDump
// -------------------------------------------------------------------
// 
//////////////////////////////////////////////////////////////////////
BOOL GameCommandLineDump( char **argv, int argc )
{
	if ( argc == 2 && !strcmp( argv[1], "help" ) )
		return FALSE;
	if ( argc != 3 )
	{
		Con_Printf( "game_state adress: %8.8X", *gamedatap );
		return TRUE;
	};
	char   *endptr;
	DWORD   adress = strtol( argv[2], &endptr, 16 );

	if ( endptr - argv[2] == 0 || adress < 0x400000 )
	{
		Con_Printf( "incorrect adress: %s", argv[2] );
		return TRUE;
	};
	switch ( argv[1][0] )
	{
	case 'f':
		Con_Printf( "%8.8X: %f", adress, *( float * ) adress );
		break;
	case 'd':
		Con_Printf( "%8.8X: %8.8X", adress, *( double * ) adress );
		break;
	case 'u':
		Con_Printf( "%8.8X: %8.8X", adress, *( DWORD * ) adress );
		break;
	case 'w':
		Con_Printf( "%8.8X: %8.8X", adress, *( WORD * ) adress );
		break;
	case 'b':
		Con_Printf( "%8.8X: %2.2X", adress, *( BYTE * ) adress );
		break;
	case 's':
		Con_Printf( "%8.8X: %s", adress, ( char * ) adress );
		break;
	default:
		return FALSE;
	}
	return TRUE;
	//Con_Printf("%.0f %.0f",*(float*)(gamedata+0x10),*(float*)(gamedata+0x14));
};

//////////////////////////////////////////////////////////////////////
// GameCommandLinePrn
// -------------------------------------------------------------------
// 
//////////////////////////////////////////////////////////////////////
BOOL PRIVATE GameCommandLinePrn( char **argv, int argc )
{
	if ( argc != 4 )
		return FALSE;
	game_popup_print( argv[1], atoi( argv[2] ), atoi( argv[3] ) );
	return TRUE;
};



//////////////////////////////////////////////////////////////////////
// GameCommandLineVersion
// -------------------------------------------------------------------
// 
//////////////////////////////////////////////////////////////////////
BOOL PRIVATE GameCommandLineFPS( char **argv, int argc )
{
	if ( argc == 1 )
		return FALSE;
	if ( !stricmp( argv[1], "max" ) )
	{

	        DWORD& gamedata = *gamedatap;
		if ( argc == 3 )
		{
			*( float * ) ( gamedata + 0x10 ) = atof( argv[2] );
			Con_Printf( "Set max fps to %f", *( float * ) ( gamedata + 0x10 ) );
		} else
		{
			Con_Printf( "maxfps=%f, currentfps=%f", *( float * ) ( gamedata + 0x10 ),
				    *( float * ) ( gamedata + 0x14 ) );
		}
		return TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////
// 
// 
///////////////////////////////////////////////////
void __declspec(naked) ParseConsoleSTUB()
{
	__asm {
begin:
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
		jz done_error

		pushad
		mov      eax, [ebp+5ch]
		push eax
		call GameCommandLine
		add esp,4
		test eax,eax
		popad
		jnz done_error
		
done_ok:
		
		jmp  [con_hook_normal_exit]
done_error:
                jmp  [con_hook_error_exit]

	}
}
//////////////////////////////////////////////////////////////////////
// Con_Init()
// -------------------------------------------------------------------
// incializaciya console
//////////////////////////////////////////////////////////////////////

void InitConsole(  )
{
	ReplaceCode( INST_JMP, hook_addr_console, ( DWORD ) & ParseConsoleSTUB, 6 );	//fix in pathes
}

