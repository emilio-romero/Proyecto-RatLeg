#ifndef MANEJOPGM_H
#define MANEJOPGM_H
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "patarata.h" 
void readpgmParams(int argc, char *argv[], char *pref, int *nf);
int **createMatrix(int nr, int nc);
void freeMatrix(int **mat, int nr);
int **rellenamatriz(int nr, int nc);
int **readPgm(char *pgmfile, int *nr, int *nc, int *maxw);
int readFrame(char *cfile, pata *frame);
int **recortarPierna(int **Apgm, int nr, int nc, int *nnr, int *nnc);
int writePgm(int **Npgm, int nr, int nc, int maxw, char *cfile);
#endif 
