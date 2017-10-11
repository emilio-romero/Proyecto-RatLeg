#include "manejopgm.h"
int main(int argc, char *argv[]){
char imagen[30];
int r, c, gray,nr,nc; 
int **Mypgm; int **npgm;
readpgmParams(argc, argv, imagen);
Mypgm=readPgm(imagen,&r,&c,&gray);
npgm=recortarPierna(Mypgm,r,c,&nr,&nc);
writePgm(npgm,nr,nc,gray,"nuevo.pgm");
freeMatrix(Mypgm,r);
freeMatrix(npgm,nr);
printf("\nSu recorte ha terminado exitosamente\n");
return 0;}
