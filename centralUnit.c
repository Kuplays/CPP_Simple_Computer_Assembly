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

int cu_callBack()
{
	int term = open(TERM, O_RDWR);
	int flag_MEM, flag_ZERO, flag_WRONG, value = 0, command = 0, operand = 0, res;

	if ((sc_memoryGet(memoryPointer, &value) == 0) && (sc_commandDecode(value, &command, &operand) == 0)) {
		switch(command) {
			case 40:
			memoryPointer = operand;
			break;

			default:
			alu(command, operand);
			++memoryPointer;
			break;	
		}
	}				
	
		return 0;
}