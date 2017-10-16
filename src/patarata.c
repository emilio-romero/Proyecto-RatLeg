#include "patarata.h" 

void puntoInicial(pata *frame){
int i,j,flag=0; 
  for(i=0;i<frame->nr;i++){
    for(j=0;j<frame->nc;j++){
      if(frame->imagen[i][j]!=0){flag=1; break;} 
    }
    if(flag==1) break;
  }
  frame->p0[0]=j; 
  frame->p0[1]=i+5;

}
void puntoFinal(pata *frame){
int i,j,flag=0; 
  for(i=frame->nr-1;i>=0;i--){
    for(j=frame->nc-1;j>=0;j--){
      if(frame->imagen[i][j]!=0){flag=1; break;} 
    }
    if(flag==1) break;
  }
  frame->pf[0]=j; 
  frame->pf[1]=i-5;
}

void dibujaPunto(pata *frame,int p0[2]){
int x,y;
for(int i=p0[1]-3;i<p0[1]+3;i++){
  for(int j=(p0[0])-3;j<(p0[0])+3;j++){
    x=(i-(p0[1]))*(i-(p0[1]));  
    y=(j-(p0[0]))*(j-(p0[0]));  
    if((x+y)<9){frame->imagen[i][j]=100;}
  }
}
}

void angleBresenham(pata *frame, int x0, int y0, double th, int dist ){
  int xf,yf; 
  xf=x0+(int)round(dist*cos(th));
  yf=y0+(int)round(dist*sin(th));
  int p0[]={x0,y0}; 
  int pf[]={xf,yf};
  pointBresenham(frame,p0,pf);
}

int sign(int x){
if(x<0) return -1; 
if(x>=0) return 1;
}

void pointBresenham(pata *frame, int p0[2],int pf[2]){
  int dx,dy; //Recordar emparejamiento i->y, j->x
  int sx,sy;
  int x=p0[0], y=p0[1];
  dx=abs(pf[0]-p0[0]);
  dy=abs(pf[1]-p0[1]);
  sx=sign(pf[0]-p0[0]);
  sy=sign(pf[1]-p0[1]);
  int swap=0,temp; 
  if(dy>dx){ //mejor implementar la funcion swap para invertir dx y dy
    temp=dx;dx=dy;dy=temp;swap=1;
  }
  int D=2*dy-dx; 
  for(int j=0;j<dx;j++){
    frame->imagen[y][x]=127;
    while(D>=0){
      D=D-2*dx;
      if(swap) x+=sx; 
      else y+=sy; 
    }
    D=D+2*dy;
    if(swap) y+=sy; 
    else x+=sx;
  }
}
int *fPerpendicular(int p0[2],int pf[2], int width){
  double  m=(double)(pf[1]-p0[1])/(double)(pf[0]-p0[0]);
  double mper=-1.0/m;
  int *p=(int*)malloc(4*sizeof(int));
  int x1,y1; int x2,y2; 
  x1=p0[0]; y1=p0[1]; 
  while((x1-p0[0])*(x1-p0[0])+(y1-p0[1])*(y1-p0[1])<width*width){
    x1++; 
    y1=mper*(x1-p0[0])+p0[1];
  }
  x2=p0[0]; y2=p0[1]; 
  while((x2-p0[0])*(x2-p0[0])+(y2-p0[1])*(y2-p0[1])<width*width){
    x2--; 
    y2=mper*(x2-p0[0])+p0[1];
  }
  p[0]=x1; p[1]=y1; p[2]=x2; p[3]=y2;

return p;}


void dRectangulo(pata *frame,int t1[2], int t2[2], int width){
  int *p0=(int*)malloc(4*sizeof(int));
  int *pf=(int*)malloc(4*sizeof(int));
/*Dibuja una linea delimitante*/
  p0=fPerpendicular(t1,t2,width);
  int p1[]={p0[0],p0[1]}; int p2[]={p0[2],p0[3]};
  pointBresenham(frame,p1,p2);
/* El otro extremo delimitante*/
  pf=fPerpendicular(t2,t1,width);
  int p3[]={pf[0],pf[1]}; int p4[]={pf[2],pf[3]};
  pointBresenham(frame,p3,p4);
/*Dibuja los lados paralelos a la linea*/
  pointBresenham(frame,p1,p3);
  pointBresenham(frame,p2,p4);
/*Libera*/
free(p0); free(pf);
}

int medidaRectangulo(pata *frame, int t1[2], int t2[2], int width){
int *p0=(int*)malloc(4*sizeof(int));
int *pf=(int*)malloc(4*sizeof(int)); 
  p0=fPerpendicular(t1,t2,width);
  pf=fPerpendicular(t2,t1,width);
int p1[]={p0[0],p0[1]}; int p2[]={p0[2],p0[3]};
int p3[]={pf[0],pf[1]}; int p4[]={pf[2],pf[3]};
int xi,xf,yi,yf; 
int cant=0;
  /*Busqueda del mas pequenio*/ 
  xi=p1[0]; yi=p1[1]; 
  if(xi>p2[0]) xi=p2[0]; //x
  if(xi>p3[0]) xi=p3[0]; //x
  if(xi>p4[0]) xi=p4[0]; //x
  if(yi>p2[1]) yi=p2[1]; //y 
  if(yi>p3[1]) yi=p3[1]; //y
  if(yi>p4[1]) yi=p4[1]; //y
  /*Busqueda del mas grande*/ 
  xf=p1[0]; yf=p1[1]; 
  if(xf<p2[0]) xf=p2[0]; //x
  if(xf<p3[0]) xf=p3[0]; //x
  if(xf<p4[0]) xf=p4[0]; //x
  if(yf<p2[1]) yf=p2[1]; //y 
  if(yf<p3[1]) yf=p3[1]; //y
  if(yf<p4[1]) yf=p4[1]; //y
  //printf("p0(%d,%d), pf(%d,%d)\n",xi,yi,xf,yf);
 /*Recorremos el rectangulo formado por (xi,yi) y (xf,yf)*/
 for(int i=yi;i<yf;i++){
    for(int j=xi;j<xf ;j++){
    /*Condicion de entrada al rectangulo*/
      if(frame->imagen[i][j]<130 && frame->imagen[i][j]>120){
        for(int k=j+1;k<xf;k++){
          if(frame->imagen[i][k]==255) {cant++;} 
          if(frame->imagen[i][k]==127) {j=k;break;}  
        } 
      } 
    }
  }

free(p0); free(pf);
return cant;}

/*void findArticulaciones(pata *frame){
int xi,yi,xf,yf;
int distp=0, dista=0; 
  xi=frame->p0[0]; yi=frame->p0[1];
  xf=frame->pf[0]; yf=frame->pf[1];
  if(xi>xf) xi=frame->pf[0]; xf=frame->p0[0];
  if(yi>yf) yi=frame->pf[1]; yf=frame->p0[1];
  for(int i=yi;i<yf;i++){
    for(int j=xi;j<xf;j++){
      if(frame->imagen[i][j]==127){
      
      }
      if(frame->imagen[i][j]==255){
        int k=j+1;
        while(frame->imagen[i][k]==255){
          k++;
          distp++;
        }
      }
    }
  }
}*/

void findArticulaciones(pata *frame){
int art1[2], art2[2], art3[2];
int dir1, dir2,dir3;
int flag=0;
  for(int i=0;i<frame->nr-2;i++){
    for(int j=0;j<frame->nc;j++){
      if(frame->imagen[i][j]==255){dir1=j;
        for(int k=0;k<frame->nc;k++){
          if(frame->imagen[i+1][k]==255) {dir2=k; break;} 
        }
      if(dir2-dir1>0){
        frame->a1[0]=dir2; frame->a1[1]=i;
        flag=1; break;}
      else{break;}
      }
    }
    if(flag==1){ flag=0; break;}  }
  for(int i=frame->a1[1]+1;i<frame->nr-2;i++){
    for(int j=0;j<frame->nc;j++){
      if(frame->imagen[i][j]==255){dir1=j;
        for(int k=0;k<frame->nc;k++){
          if(frame->imagen[i+1][k]==255) {dir2=k; break;} 
        }
      if(dir2-dir1<0){
        frame->a2[0]=dir2; frame->a2[1]=i;
        flag=1; break;}
      else{break;}
      }
    }
    if(flag==1){ flag=0; break;}  }
printf("Primera articulacion: %d, %d\n",frame->a1[0],frame->a1[1]);
printf("Segunda articulacion: %d, %d\n",frame->a2[0],frame->a2[1]);
}

/* Funciones para la Evolucion Diferencial*/
void initPob(int **poblacion,int np, int *lims){
 for(int i=0;i<np;i++){
    poblacion[i][0]=2+rand()%lims[0];
    poblacion[i][1]=lims[1]+rand()%(5);//(rand()%3-1)*
    poblacion[i][2]=lims[2]+rand()%(5);//(rand()%3-1)*(rand()%(5));
    poblacion[i][3]=lims[3]+rand()%(5);//(rand()%3-1)*(rand()%(5));
    poblacion[i][4]=lims[4]+rand()%(5);//(rand()%3-1)*(rand()%(5));
 }
}
void representaPob(int **poblacion, pata *frame, int np){
  int p1[2], p2[2];
  for(int i=0;i<np;i++){
    p1[0]=poblacion[i][1]; p1[1]=poblacion[i][2];
    p2[0]=poblacion[i][3]; p2[1]=poblacion[i][4];
    dRectangulo(frame,p1,p2,poblacion[i][0]);
  }
}
void randPerm(int np, int *rs){
  rs[0]=rand()%np; 
  do{
  rs[1]=rand()%np;
  rs[2]=rand()%np;
  }while(rs[0]==rs[1] || rs[0]==rs[2] || rs[1]==rs[2]);
}

void mutationOp(int **poblacion, int **V, double F, int np, pata frame, int *lims){
int rs[3]; 
  for(int i=0;i<np;i++){
    randPerm(np,rs);
    for(int j=0;j<5;j++){
      V[i][j]=poblacion[rs[0]][j]+(int)(F*(double)(poblacion[rs[1]][j]-poblacion[rs[2]][j]));
   }
   if(V[i][0]>7) V[i][0]=2+rand()%lims[0];
   if(V[i][1]>lims[1]+15 || V[i][1]<lims[1]-5) V[i][1]=lims[1]+rand()%(5);
   if(V[i][2]>lims[2]+15 || V[i][2]<lims[2]-5) V[i][2]=lims[2]+rand()%(5);
   if(V[i][3]>lims[3]+15 || V[i][3]<lims[3]-5) V[i][3]=lims[3]+rand()%(5);
   if(V[i][4]>lims[4]+15 || V[i][4]<lims[4]-5) V[i][4]=lims[4]+rand()%(5);

  }

}
double randx(){
  return (double)rand()/(double)RAND_MAX;
}
void crossOp(int **U,int **X, int **V, int np, double Cr){
int rn;
  for(int i=0;i<np;i++){
    for(int j=0;j<5;j++){
      rn=rand()%5;
      if(randx()<=Cr || rn ==j){
        U[i][j]=V[i][j];
      } 
      else U[i][j]=X[i][j];
    }
  }
}

double fob(int *x, pata frame){
pata paux;
int **aux=(int**)malloc(frame.nr*sizeof(int*));
for(int i=0;i<frame.nr;i++) {aux[i]=(int*)malloc(frame.nc*sizeof(int));
  for(int j=0;j<frame.nc;j++)aux[i][j]=frame.imagen[i][j];}
  paux.imagen=aux;
  paux.nr=frame.nr; paux.nc=frame.nc; 
  int cb;
  int t1[]={x[1],x[2]};
  int t2[]={x[3],x[4]};
  dRectangulo(&paux,t1,t2,x[0]);
  cb=medidaRectangulo(&paux,t1,t2,x[0]);
  double dx=(double)(x[3]-x[1]);
  double dy=(double)(x[4]-x[2]);
  double area=(double)(2*x[0])*sqrt(dx*dx+dy*dy);
  double razon=(double)(cb*x[0])/area; 
  for(int i=0;i<frame.nr;i++) free(aux[i]);
  free(aux);
return(razon);}

void selectionOp(int **X, int **U, int np, pata frame){
double xi, ui; 
  for(int i=0;i<np;i++){
    xi=fob(X[i],frame);
    ui=fob(U[i],frame);
    if(ui>xi){
      for(int j=0;j<5;j++) X[i][j]=U[i][j];
    }
  }
}

void bestOp(int *xbest, int **X, int np, pata frame){
int b=0;
double best=fob(X[0],frame);
  for(int i=1;i<np;i++){
    if(fob(X[i],frame)>best) b=i;
  }
  for(int i=0;i<5;i++){
    xbest[i]=X[b][i];
  } 
}

int *algorithmDE(int np, int iter, double F, double Cr, int *lims, pata frame){
int *xbest=(int*)malloc(5*sizeof(int));
int **X=(int**)malloc(np*sizeof(int*));
int **V=(int**)malloc(np*sizeof(int*));
int **U=(int**)malloc(np*sizeof(int*));
for(int i=0;i<np;i++){
  X[i]=(int*)malloc(5*sizeof(int));
  V[i]=(int*)malloc(5*sizeof(int));
  U[i]=(int*)malloc(5*sizeof(int));
}
  initPob(X,np,lims);

  for(int k=0;k<iter;k++){
    mutationOp(X,V,F,np,frame,lims);
    crossOp(U,X,V,np,Cr);
    selectionOp(X,U,np,frame);
  }
  bestOp(xbest,X,np,frame);

for(int i=0;i<np;i++){free(X[i]); free(V[i]); free(U[i]);}
free(X); free(V); free(U);

return(xbest);}
