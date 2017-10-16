#include <stdio.h>
#include <stdlib.h> 
#include "manejopgm.h"
#include "patarata.h"
#include <math.h> 
#define PI 3.141592
int main(int argc, char *argv[]){
srand(time(NULL));
char archivo[30]; 
readpgmParams(argc, argv, archivo);
pata myframe;
int *xbest1=(int*)malloc(5*sizeof(int));
int *xbest2=(int*)malloc(5*sizeof(int));
readFrame(archivo,&myframe);
puntoInicial(&myframe);
puntoFinal(&myframe);
printf("Filas: %d, Columnas: %d\n",myframe.nr,myframe.nc);
printf("x inicial: %d, y inicial: %d\n",myframe.p0[0],myframe.p0[1]);
//angleBresenham(&myframe,100,100,-PI/4,50);
//angleBresenham(&myframe,0,0,0.78540,141);
findArticulaciones(&myframe);
//pointBresenham(&myframe,myframe.p0,myframe.a1);
//pointBresenham(&myframe,myframe.a1,myframe.a2);
//pointBresenham(&myframe,myframe.a2,myframe.pf);
//initPob(poblacion, myframe,10);
//mutationOp(poblacion,V,1.3,10,myframe);
//crossOp(U,poblacion, V,10,0.7);
//selectionOp(poblacion,U,10, myframe);
//bestOp(xbest,poblacion,10,myframe);
int lim1[5]={6,myframe.p0[0],myframe.p0[1],myframe.a1[0],myframe.a1[1]};
int lim2[5]={6,myframe.a1[0],myframe.a1[1],myframe.a2[0],myframe.a2[1]};
xbest1=algorithmDE(10,10,1.3,0.7,lim1,myframe);
int p0[2]={xbest1[1],xbest1[2]};
int pf[2]={xbest1[3],xbest1[4]};
//printf("a donde llegas?\n");
dRectangulo(&myframe,p0,pf,xbest1[0]);
xbest2=algorithmDE(10,10,1.3,0.7,lim2,myframe);
  p0[0]=xbest2[1]; p0[1]=xbest2[2];
  pf[0]=xbest2[3]; pf[1]=xbest2[4];
dRectangulo(&myframe,p0,pf,xbest2[0]);

dibujaPunto(&myframe,myframe.p0);
dibujaPunto(&myframe,myframe.a1);
dibujaPunto(&myframe,myframe.a2);
//representaPob(poblacion, &myframe,10);
//printf("El valor de fob para uno: %lf\n",fob(poblacion[0],myframe));
free(xbest1);
free(xbest2);
writePgm(myframe.imagen,myframe.nr,myframe.nc,myframe.gs,"mejores.pgm");
printf("\nSu programa ha terminado\n");
return 0;}

