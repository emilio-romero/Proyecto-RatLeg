#ifndef PATARATA_H 
#define PATARATA_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct rata{
int nr; int nc; int gs;
int **imagen;
int p0[2]; 
int a1[2];
int a2[2];
int a3[2];
int pf[2];
}pata;
//Funciones para el manejo de la imagen 
void puntoInicial(pata *frame);
void puntoFinal(pata *frame);
void dibujaPunto(pata *frame);
void dibujaLinea(pata *frame,int x0, int y0, double th, int dist);
void angleBresenham(pata *frame,int i0, int j0, double th, int dist);
#endif 
