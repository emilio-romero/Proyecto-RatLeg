#include <stdio.h>
#include <stdlib.h> 
#include "manejopgm.h"
#include "patarata.h"
#include <math.h> 
int main(int argc, char *argv[]){
char archivo[30]; 
readpgmParams(argc, argv, archivo);
pata myframe;
readFrame(archivo,&myframe);
puntoInicial(&myframe);
printf("Filas: %d, Columnas: %d\n",myframe.nr,myframe.nc);
printf("x inicial: %d, y inicial: %d\n",myframe.p0[0],myframe.p0[1]);
dibujaPunto(&myframe);
writePgm(myframe.imagen,myframe.nr,myframe.nc,myframe.gs,"modificado.pgm");
printf("\nSu programa ha terminado\n");
/*double theta; 
for(int i=0;i>=-90;i--){
theta=(double)i;
printf("angulo: %i, coseno:%lf, angulo*coseno:%d\n",(int)theta,cos(theta),
(int)round(theta*cos(theta)));
}*/
return 0;}

