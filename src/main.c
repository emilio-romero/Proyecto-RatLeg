#include <stdio.h>
#include <stdlib.h> 
#include "manejopgm.h"
#include "patarata.h"
#include <math.h> 
#define PI 3.141592
int main(int argc, char *argv[]){
srand(time(NULL));
char prefijo[30]; 
int frames;
readpgmParams(argc, argv, prefijo,&frames);
double **ang=(double**)malloc(frames*sizeof(double*));
for(int f=0;f<=frames;f++) ang[f]=(double*)malloc(4*sizeof(double));
  
  ratMove(prefijo,frames,ang,10,10,1.3,0.7);


printf("\nSu programa ha terminado\n");
return 0;}

