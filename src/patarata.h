#ifndef PATARATA_H 
#define PATARATA_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
typedef struct rata{
int nr; int nc; int gs;
int **imagen;
int p0[2]; 
int a1[2];
int a2[2];
int a3[2];
int pf[2];
}pata;

typedef struct agent{
int ancho; 
int p1[2]; 
int p2[2]; 
}individuo;
//Funciones para el manejo de la imagen 
void puntoInicial(pata *frame);
void puntoFinal(pata *frame);
void dibujaPunto(pata *frame, int p0[2]);
void angleBresenham(pata *frame,int i0, int j0, double th, int dist);
int sign(int x);
void pointBresenham(pata *frame, int p0[2], int pf[2]);
int *fPerpendicular(int p0[2],int pf[2],int width);
void dRectangulo(pata *frame,int t1[2], int t2[2], int width);
int medidaRectangulo(pata *frame, int t1[2], int t2[2], int width);
void findArticulaciones(pata *frame);
/*Funciones para la evolucion diferencial*/ 
void initPob(int **poblacion, int np, int *lims);
void representaPob(int **poblacion, pata *frame, int np);
void randPerm(int np, int *rs);
void mutationOp(int **poblacion, int **V, double F, int np,pata frame, int *lims);
double randx(); 
void crossOp(int **U,int **X, int **V, int np, double Cr);
double fob(int *x, pata frame);
void selectionOp(int **X, int **U, int np, pata frame);
void bestOp(int *xbest, int **X, int np, pata frame);
int *algorithmDE(int np, int iter, double F, double Cr,int *lims, pata frame);
#endif 
