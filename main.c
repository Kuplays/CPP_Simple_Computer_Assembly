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
#include "centralUnit.h"

int main()
{
    signal (SIGALRM, signalhandler);
    signal (SIGUSR1, reset);

    enum Keys key = NONE;
    flag_key = 0;
    flag_ign = 0;
    accumValue = 0;
    opCounter = 0;

    setTimerVals(1, 0);
	
	sc_memoryInit();
    sc_regInit();
    termInit();

	showAll();
    
    while (key != QUIT) {
		
		rk_readKey(&key);
		
		if (key == STEP) {
			sc_regSet(F_ISRUN, 0);
			alarm(0); 
			flag_key = 0;
			cu_callBack();
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
			
			if (key == RIGHT) if (memoryPointer < 99) ++memoryPointer;
			if (key == LEFT) if (memoryPointer >  0) --memoryPointer;
			if (key == UP) if (memoryPointer - 10 >=  0) memoryPointer -= 10;
			if (key == DOWN) if (memoryPointer + 10 < 100) memoryPointer += 10;

			if (key == F5) displayBox("ACCUM", 1);
			if (key == F6) displayBox("COUNTER", 2);
			if (key == EDIT) displayBox("EDIT CELL", 3);

			if (key == LOAD) sc_memoryLoad("mem.dat");
			if (key == SAVE) sc_memorySave("mem.dat");

			if (key == RESET) {
				sc_memoryInit();
				sc_regInit();
			}

			showAll();
		}
		
	}
    
	return 0;
}