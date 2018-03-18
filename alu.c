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
            accumValue += operand;
		break;

		case 31:
			accumValue -= operand;
			break;
		case 32:
			if (operand != 0) accumValue /= operand;
			else sc_regSet(F_ZERO, 1);
			break;
		case 33:
			accumValue *= operand;
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