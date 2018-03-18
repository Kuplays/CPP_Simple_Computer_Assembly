#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "scLib.h"
#include "myReadKey.h"
#include "inputArea.h"
#include "UserInterface.h"
#include "myTerm.h"

void inputAccum()
{
    printf("ENTER ACUUM VALUE: ");
    scanf("%d", &accumValue);

    clearInput();
}

void inputCounter()
{
    printf("ENTER COUNTER: ");
    scanf("%d", &opCounter);
    if(opCounter >= 0 && opCounter < MEM_COUNT)
		memoryPointer = opCounter;
	else
		sc_regSet(F_BOUNDS, 1);
    
    clearInput();;
}

void inputMemory()
{
    int com = 0, oper = 0, value;
    sc_memoryGet(memoryPointer, &value);
    sc_commandDecode(value, &com, &oper);
    printf("ENCODE: ");
    scanf("%d %d", &com, &oper);
    sc_commandEncode(com, oper, &value);
    sc_memorySet(memoryPointer, value); 
    clearInput();
}

void clearInput()
{
    int term = open(TERM, O_RDWR);

    int i;
    mt_gotoXY (25, 1);
    for (i = 0; i < 80; ++i)
        write (term, " ", 1);
    mt_gotoXY (25, 1);

    close (term);
}