#include "manejopgm.h" 
#include "patarata.h" 
void readpgmParams(int argc, char *argv[],char *pref, int *nf){
if(argc>1) strcpy(pref,argv[1]);
if(argc>2) *nf=atoi(argv[2]);
}

int **createMatrix(int nr, int nc){
  int **mat;
  mat=(int**)malloc(nr*sizeof(int*));
  if(mat==NULL) return(NULL);
  for(int i=0;i<nr;i++) mat[i]=(int*)malloc(nc*sizeof(int));
return(mat);}

void freeMatrix(int **mat, int nr){
 for(int i=0;i<nr;i++) free(mat[i]);
 free(mat);
}

int **rellenamatriz(int nr, int nc){
 int **mat;
 mat=createMatrix(nr,nc);

return(mat);}

int **readPgm(char *pgmfile, int *nr, int *nc, int *maxw){
int **mat; 
char ch; int val;
FILE *f1=fopen(pgmfile,"r");
 if(!f1) return(NULL);
  ch=getc(f1); 
  if(ch != 'P'){
    printf("Error: no es un archivo pgm valido\n");
    return(NULL); }
  ch=getc(f1);
// while(getc(f1) != '\n'); 
// while(getc(f1)!= '#'){while(getc(f1) != '\n');}
 fscanf(f1,"%d",nc); fscanf(f1,"%d",nr); fscanf(f1,"%d",maxw); 
 mat=createMatrix(*nr,*nc);
 for(int i=0;i<(*nr);i++){
   for(int j=0;j<(*nc);j++){
    fscanf(f1,"%d",&val);
    mat[i][j]=val;
   }
 }
fclose(f1);
return(mat);}

int readFrame(char *cfile,pata *frame){
frame->imagen=readPgm(cfile,&(frame->nr),&(frame->nc),&(frame->gs));
return(0);}

int **recortarPierna(int **Apgm, int nr, int nc, int *nnr, int *nnc){
int li,lr,lu,ld,flag=0;
int **nmat; 
   for(li=0;li<nc;li++){
    for(int i=0;i<nr;i++) {
      if(Apgm[i][li]!=0){flag=1; break;}}
    if(flag==1){flag=0; break;}
  }
  for(lr=(nc-1);lr>=0;lr--){
    for(int i=0;i<nr;i++){
      if(Apgm[i][lr] != 0) {flag=1; break;} }
    if(flag==1){flag=0; break;}
  }
  for(lu=0;lu<nr;lu++){
    for(int j=0;j<nc;j++) {
      if(Apgm[lu][j] != 0){flag=1; break;}} 
    if(flag==1){flag=0; break;}
  }
  for(ld=nr-1;ld>=0;ld--){
    for(int j=0;j<nc;j++) {
      if(Apgm[ld][j] != 0){flag=1; break;}}
    if(flag==1){flag=0; break;}
  }
 
  li=li-10; lr=lr+10;
 // printf("limite izquierdo: %d, lim derecho:%d\n",li,lr);
  *nnc=lr-li; printf("%d \n", *nnc);
  lu=lu-10; ld=ld+10; 
 // printf("limite sup: %d, lim inf:%d\n",lu,ld);
  *nnr=ld-lu; printf("%d \n", *nnr);
  nmat=createMatrix(*nnr,*nnc); 
 //Rellenar la nueva matriz 
  for(int i=0;i<(*nnr);i++){
    for(int j=0;j<(*nnc);j++){
      nmat[i][j]=Apgm[lu+i][li+j];
    }
  }
return(nmat);}

int writePgm(int **Npgm, int nr, int nc, int maxw, char *cfile){
FILE *out; 
  out=fopen(cfile,"w");
  fprintf(out,"P2\n");
  fprintf(out,"%d %d\n%d\n",nc,nr,maxw);
  for(int i=0;i<nr;i++){
    for(int j=0;j<nc;j++){
      fprintf(out,"%d ",Npgm[i][j]);
    }
    fprintf(out,"\n");
  }
fclose(out);
return(0);}

