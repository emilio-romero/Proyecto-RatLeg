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
int *xbest3=(int*)malloc(5*sizeof(int));
int *xbest4=(int*)malloc(5*sizeof(int));
readFrame(archivo,&myframe);
puntoInicial(&myframe);
puntoFinal(&myframe);
printf("Filas: %d, Columnas: %d\n",myframe.nr,myframe.nc);
printf("x inicial: %d, y inicial: %d\n",myframe.p0[0],myframe.p0[1]);
//angleBresenham(&myframe,100,100,-PI/4,50);
//angleBresenham(&myframe,0,0,0.78540,141);
//findArticulaciones(&myframe);
//findArticulaciones4(&myframe);
//algorithmHarris(&myframe);
findArticulaciones2(&myframe);
//initPob(poblacion, myframe,10);
//mutationOp(poblacion,V,1.3,10,myframe);
//crossOp(U,poblacion, V,10,0.7);
//selectionOp(poblacion,U,10, myframe);
//bestOp(xbest,poblacion,10,myframe);
int lim1[5]={6,myframe.p0[0],myframe.p0[1],myframe.a1[0],myframe.a1[1]};
int lim2[5]={6,myframe.a1[0],myframe.a1[1],myframe.a2[0],myframe.a2[1]};
int lim3[5]={6,myframe.a2[0],myframe.a2[1],myframe.a3[0],myframe.a3[1]};
int lim4[5]={6,myframe.a3[0],myframe.a3[1],myframe.pf[0],myframe.pf[1]};
xbest1=algorithmDE(10,10,1.3,0.7,lim1,myframe);
int p01[2]={xbest1[1],xbest1[2]};
int pf1[2]={xbest1[3],xbest1[4]};
//printf("a donde llegas?\n");
xbest2=algorithmDE(10,10,1.3,0.7,lim2,myframe);
int p02[2]={xbest2[1],xbest2[2]};
int pf2[2]={xbest2[3],xbest2[4]};
xbest3=algorithmDE(10,10,1.3,0.7,lim3,myframe);
int p03[2]={xbest3[1],xbest3[2]};
int pf3[2]={xbest3[3],xbest3[4]};
//xbest4=algorithmDE(10,10,1.3,0.7,lim4,myframe);
printf("legas aca?\n");
//int p04[2]={xbest4[1],xbest4[2]};
//int pf4[2]={xbest4[3],xbest4[4]};
dRectangulo(&myframe,p01,pf1,xbest1[0]);
dRectangulo(&myframe,p02,pf2,xbest2[0]);
dRectangulo(&myframe,p03,pf3,xbest3[0]);
//dRectangulo(&myframe,p04,pf4,xbest4[0]);

dibujaPunto(&myframe,myframe.p0);
dibujaPunto(&myframe,myframe.a1);
dibujaPunto(&myframe,myframe.a2);
dibujaPunto(&myframe,myframe.a3);
dibujaPunto(&myframe,myframe.pf);
pointBresenham(&myframe,myframe.p0,myframe.a1);
pointBresenham(&myframe,myframe.a1,myframe.a2);
pointBresenham(&myframe,myframe.a2,myframe.a3);
pointBresenham(&myframe,myframe.a3,myframe.pf);
//representaPob(poblacion, &myframe,10);
//printf("El valor de fob para uno: %lf\n",fob(poblacion[0],myframe));
free(xbest1);
free(xbest2);
free(xbest3);
free(xbest4);
writePgm(myframe.imagen,myframe.nr,myframe.nc,myframe.gs,"mejores.pgm");
printf("\nSu programa ha terminado\n");
return 0;}

