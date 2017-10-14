#include <stdio.h>
#include <stdlib.h> 
#include "manejopgm.h"
#include "patarata.h"
#include <math.h> 
#define PI 3.141592
int main(int argc, char *argv[]){
char archivo[30]; 
readpgmParams(argc, argv, archivo);
pata myframe;
readFrame(archivo,&myframe);
puntoInicial(&myframe);
puntoFinal(&myframe);
printf("Filas: %d, Columnas: %d\n",myframe.nr,myframe.nc);
printf("x inicial: %d, y inicial: %d\n",myframe.p0[0],myframe.p0[1]);
dibujaPunto(&myframe);
//angleBresenham(&myframe,100,100,-PI/4,50);
//angleBresenham(&myframe,0,0,0.78540,141);
int p0[]={100,100};
int pf[]={125,75};
pointBresenham(&myframe,myframe.p0,myframe.pf);
dRectangulo(&myframe,myframe.p0[0],myframe.p0[1],myframe.pf[0],myframe.pf[1],16);
writePgm(myframe.imagen,myframe.nr,myframe.nc,myframe.gs,"modificado.pgm");
printf("\nSu programa ha terminado\n");
/*double theta; 
for(int i=0;i>=-90;i--){
theta=(double)i;
printf("angulo: %i, coseno:%lf, angulo*coseno:%d\n",(int)theta,cos(theta),
(int)round(i*cos(theta)));
}*/
//int cero=0;
/*
printf("\npruebas numericas: %d\n",15+(int)round(20*cos(1.5708)));
int d=5; double th=-PI/6; 
printf("nuevo x0 y0: %d %d\n",5+(int)(round(d*cos(th))),5+(int)(round(d*sin(th))));
printf("nuevo x1 y1: %d %d\n",5+(int)(round(d*cos(PI/2-th))),5+(int)(round(d*sin(PI/2-th))));
*/
return 0;}

