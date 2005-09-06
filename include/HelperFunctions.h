//////////////////////////////////////////////////////////////////////
// HelperFunctions
// -------------------------------------------------------------------
// $Id: HelperFunctions.h,v 1.1 2005-09-06 19:02:30 AngelD Exp $ 
//////////////////////////////////////////////////////////////////////

#pragma once

#include "define.h"

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */


#define INST_NOP 0x90
#define INST_CALL 0xe8
#define INST_JMP 0xe9

typedef struct patch_code_t
{
    DWORD		Type;
    DWORD		Instruction;
    DWORD		Source;
    DWORD		Dest;
    DWORD		PatchSize;
}PATCHCODESTRUCT;


VOID*	PRIVATE newmemcpy(DWORD lpDest, DWORD lpSource, int len);
BOOL	PRIVATE Intercept(int instruction, DWORD lpSource, DWORD lpDest, int len);
BOOL    PRIVATE ReplaceCode(int instruction, DWORD lpSource, DWORD lpDest, int len);
VOID*   PRIVATE FillBytes(DWORD lpDest, BYTE ch, int len=1);
VOID*   PRIVATE PutDWord(DWORD lpDest, DWORD ch);
VOID*   PRIVATE PutWord(DWORD lpDest, WORD ch);
//void    PRIVATE InterceptTable(PATCHCODESTRUCT*);
#ifdef __cplusplus
}		             /* Assume C declarations for C++ */
#endif  /* __cplusplus */
