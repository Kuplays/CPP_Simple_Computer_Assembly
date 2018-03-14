#ifndef MYREADKEY_H
#define MYREADKEY_H

int rk_readKey(enum Keys *);
int rk_myTermSave();
int rk_myTermRestore();
int rk_myTermRegime(int, int, int, int, int);
#endif