#ifndef PATARATA_H 
#define PATARATA_H
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
#endif 
