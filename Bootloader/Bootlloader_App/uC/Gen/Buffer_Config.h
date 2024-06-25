/******************************************************************
                A Z E T E C H    S O L U T I O N S                 
-------------------------------------------------------------------
        T O O L   G E N E R A T E D   S O U R C E   C O D E        
                    D O   N O T   M O D I F Y                      
-------------------------------------------------------------------
 This file is generated with the Azetech copyrighted software tool 
 No modification should be done in this file without a written     
 consent from Azetech Solutions. Incase of any such instances,     
 Azetech Solutions will not be liable to any damages it cause.     
-------------------------------------------------------------------
 Any Distribution, Alteration, Removal, Disassemble, Decompile or  
 or Reverse Engineer the given software, without written consent   
 from Azetech Solutions by the Licensee or third parties were not  
 allowed. Such instance is considered as a breach and the Licensee 
 is the sole responsible and liable to any damages it cause.       
******************************************************************/

#ifndef __BUFFER_CONFIG_H__
#define __BUFFER_CONFIG_H__

#include <Includes.h>
#include PLATFORM_TYPES_H

/*************************************************/
/* Functional Switches and Parameter Definitions */
/*************************************************/

/* Total number of Buffers */
#define BUFFER_MAX_COUNT                  2

/* Maximum Size of each configured Buffer */
#define BUFFER_MAX_SIZE                   255


/* Buffer for UART3 */
#define P_BUFFER_ID_UART3            0
#define P_BUFFER_LENGTH_UART3        255

/* Buffer for Debug */
#define P_BUFFER_ID_Debug            1
#define P_BUFFER_LENGTH_Debug        100



/*************************************************/
/*               Macro Definitions               */
/*************************************************/

#define UART3_Buffer_Create()             Buffer_Create(P_BUFFER_ID_UART3, BufferArray_UART3, P_BUFFER_LENGTH_UART3)
#define UART3_Buffer_Get()                Buffer_GetBuffer(P_BUFFER_ID_UART3)
#define UART3_Buffer_EnQueue(Data)        Buffer_EnQueue(P_BUFFER_ID_UART3, Data)
#define UART3_Buffer_DeQueue(Data)        Buffer_DeQueue(P_BUFFER_ID_UART3, Data)
#define UART3_Buffer_Length()             Buffer_Length(P_BUFFER_ID_UART3)
#define UART3_Buffer_Clear()              Buffer_Clear(P_BUFFER_ID_UART3)
#define UART3_IsBufferEmpty()             (UART3_Buffer_Length() == 0)

#define Debug_Buffer_Create()             Buffer_Create(P_BUFFER_ID_Debug, BufferArray_Debug, P_BUFFER_LENGTH_Debug)
#define Debug_Buffer_Get()                Buffer_GetBuffer(P_BUFFER_ID_Debug)
#define Debug_Buffer_EnQueue(Data)        Buffer_EnQueue(P_BUFFER_ID_Debug, Data)
#define Debug_Buffer_DeQueue(Data)        Buffer_DeQueue(P_BUFFER_ID_Debug, Data)
#define Debug_Buffer_Length()             Buffer_Length(P_BUFFER_ID_Debug)
#define Debug_Buffer_Clear()              Buffer_Clear(P_BUFFER_ID_Debug)
#define Debug_IsBufferEmpty()             (Debug_Buffer_Length() == 0)


/*************************************************/
/*               Type Definitions                */
/*************************************************/

typedef UBYTE BufferLengthType;

/*************************************************/
/*               Global Variables                */
/*************************************************/

extern UBYTE BufferArray_UART3[];
extern UBYTE BufferArray_Debug[];

/*************************************************/
/*          Extern Function Declarations         */
/*************************************************/

extern void Buffer_Init(void);

#endif /* __BUFFER_CONFIG_H__ */

