#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <termios.h>

#include "scLib.h"
#include "myReadKey.h"
#include "inputArea.h"
#include "UserInterface.h"
#include "myTerm.h"
#include "alu.h"


int alu(int command, int operand)
{	
	int flag_MEM, flag_ZERO, flag_WRONG;
	int value = 0;
	
	switch (command) {
				
		case 30:
			if (sc_memoryGet(operand, &value) == 0) {
				if (value > 0x1FFF) {
                    value = value & 0x1FFF; 
                }
                accumValue = accumValue + value;
                if (accumValue > 0x1FFF) {
                    accumValue = accumValue & 0x1FFF; 
                    sc_regSet(F_OVERFLOW, 1); 
                }
            }
			break;

		
		default:
            sc_regSet(F_WRONG_COM, 1);   
            alarm(0);         
			break;			
	}
	
	sc_regGet(F_BOUNDS, &flag_MEM);
	sc_regGet(F_ZERO, &flag_ZERO);
	sc_regGet(F_WRONG_COM, &flag_WRONG);
	
	if (flag_MEM || flag_ZERO || flag_WRONG) {
		sc_regSet(F_IGNORE_FLAG, 1);
		return -1;
	}
	else
		return 0;
}

int cu()
{
	int term = open(TERM, O_RDWR);
	int flag_MEM, flag_ZERO, flag_WRONG, value = 0, command = 0, operand = 0, res;

	if ((sc_memoryGet(memoryPointer, &value) == 0) && (sc_commandDecode(value, &command, &operand) == 0)) {
		switch(command) {
			case 40:
			memoryPointer = operand;
			break;	
		}
	}				
	
		return 0;
}