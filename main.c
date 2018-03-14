#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <signal.h>
#include <time.h>
#include <sys/time.h>

#include "myBigChars.h"
#include "myTerm.h"
#include "myReadKey.h"
#include "UserInterface.h"
#include "scLib.h"
#include "inputArea.h"
#include "alu.h"

int main()
{
    signal (SIGALRM, signalhandler);
    signal (SIGUSR1, reset);

    nval.it_interval.tv_sec  = 1;
    nval.it_interval.tv_usec = 0;
    nval.it_value.tv_sec  = 1;
    nval.it_value.tv_usec = 0;	
	
	sc_memoryInit();
    sc_regInit();
    termInit();
    accumValue = 0;
    opCounter = 0;

    enum Keys key = UNKNOWN;
	
	showAll();
    
    flag_key = 0;
    flag_ign = 0;
    
    while (key != QUIT) {
		
		rk_readKey(&key);
		
		if (key == STEP) {
			sc_regSet(F_ISRUN, 0);
			alarm(0); 
			flag_key = 0;
			cu();
		}
		
		if (!flag_key) {
			if (key == RUN)  {
				sc_regSet(F_ISRUN, 1);
				sc_regSet(F_IGNORE_FLAG, 0);
			}
			
			sc_regGet(F_ISRUN, &flag_key);
			
			if (flag_key) {
				timerStart();        
			}
			
			if (key == F5) inputAccum();
			if (key == F6) inputCounter();
			if (key == RIGHT) if (memoryPointer < 99) ++memoryPointer;
			if (key == LEFT) if (memoryPointer >  0) --memoryPointer;
			if (key == UP) if (memoryPointer - 10 >=  0) memoryPointer -= 10;
			if (key == DOWN) if (memoryPointer + 10 < 100) memoryPointer += 10;
			if (key == LOAD) sc_memoryLoad("mem.dat");
			if (key == SAVE) sc_memorySave("mem.dat");
			if (key == EDIT) inputMemory(); 
			if (key == RESET) {
				sc_memoryInit();
				sc_regInit();
				showAll();
			}
			showAll();
		}
		
	}
    
	return 0;
}