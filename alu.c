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
		case 31:
			if (sc_memoryGet(operand, &value) == 0) {
				if (value > 0x1FFF) {
                    value = value & 0x1FFF; 
                }
                accumValue = accumValue - value;
                if (accumValue > 0x1FFF) {
                    accumValue = accumValue & 0x1FFF; 
                    sc_regSet(F_OVERFLOW, 1); 
                }
            }
			break;
		case 32: 
			if (sc_memoryGet(operand, &value) == 0) {
				if (value > 0x1FFF) {
                    value = value & 0x1FFF; 
                }
                if (value != 0) {
                    accumValue = accumValue / value;
                    if (accumValue > 0x1FFF) {
                        accumValue = accumValue & 0x1FFF; 
                        sc_regSet(F_OVERFLOW, 1); 
                    }
                } else sc_regSet(F_ZERO, 1); 
            }
			break;			
		case 33:
			if (sc_memoryGet(operand, &value) == 0) {
				if (value > 0x1FFF) {
                    value = value & 0x1FFF; 
                }
                accumValue = accumValue * value;
                if (accumValue > 0x1FFF) {
                    accumValue = accumValue & 0x1FFF; 
                    sc_regSet(F_OVERFLOW, 1); 
                }
            }
			break;
			
		case 52: 
			if (sc_memoryGet(operand, &value) == 0) {
				if (value > 0x1FFF) {
                    value = value & 0x1FFF; 
                }
                accumValue = accumValue & value;
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
					
	char buf[5];
	int flag_MEM, flag_ZERO, flag_WRONG;
	int value = 0, command = 0, operand = 0;
	int res;
	struct termios oldState, termState;
	
	sc_regSet(F_WRONG_COM, 0);
	sc_regSet(F_OVERFLOW, 0);
	
	if ((sc_memoryGet(memoryPointer, &value) == 0) && (sc_commandDecode(value, &command, &operand) == 0)) {
            switch (command)
            {
                case 10: 
					rk_myTermSave(&oldState);
					defaultTermSettings(&termState);
					tcsetattr(1, TCSANOW, &termState);
					alarm(0);
					write(term, "ENTER DATA > ", 14);
					read(term, buf, 5);
					sscanf(buf, "%d", &res);

					if (res > 0x1FFF) {
						res = res & 0x1FFF;
						sc_regSet(F_OVERFLOW, 1);
					}

					sc_memorySet(operand, (1 << 14) | res);
					rk_myTermRestore(&oldState);
					timerStart();
					++memoryPointer;
					clearInput();
					break;
				case 11:
										
					sc_memoryGet(operand, &value);
					sprintf(buf, "%04d", value & 0x1FFF);

					write(1, buf, sizeof(buf));
					++memoryPointer;
					close(term); 
					break;
					
				case 20:
					if (sc_memoryGet(operand, &value) == 0) {						
                        accumValue = value;
                        if (accumValue > 0x1FFF) {
							accumValue = accumValue & 0x1FFF;
						}
                        ++memoryPointer;
                    }
					break;
				case 21:
					sc_memorySet(operand, accumValue);
                    ++memoryPointer;
					break;
								
				case 40:
					memoryPointer = operand;
					break;
				case 41:
					if ((accumValue >> 14) & 1)
						memoryPointer = operand;
                    else 
						++memoryPointer;
					break;
				case 42:
					if (accumValue == 0)
						memoryPointer = operand;
                    else
						++memoryPointer;
					break;
				case 43:
					sc_regSet(F_ISRUN, 0);
					alarm(0);
					flag_key = 0;
					break;
					
				default: 
                	if (alu(command, operand) == 0) 
                        ++memoryPointer;
                    
					break;
			}
    }
    
    sc_regGet(F_BOUNDS, &flag_MEM);
	sc_regGet(F_ZERO, &flag_ZERO);
	sc_regGet(F_WRONG_COM, &flag_WRONG);
	
	close(term);
	if (flag_MEM || flag_ZERO || flag_WRONG) {
		sc_regSet(F_IGNORE_FLAG, 1);
		return -1;
	}
	else
		return 0;
}