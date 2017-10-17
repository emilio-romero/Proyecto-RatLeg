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
  double mper;
  int *p=(int*)malloc(4*sizeof(int));
  int x1,y1; int x2,y2; 
  if(fabs(m)<0.05){
   x1=p0[0]; x2=p0[0];
   y1=p0[1]+width; y2=p0[1]-width;
  }
  else
  {mper=-1.0/m;
  x1=p0[0]; y1=p0[1]; 
  while((x1-p0[0])*(x1-p0[0])+(y1-p0[1])*(y1-p0[1])<width*width){
    x1++; 
    y1=mper*(x1-p0[0])+p0[1];
  }
  x2=p0[0]; y2=p0[1]; 
  while((x2-p0[0])*(x2-p0[0])+(y2-p0[1])*(y2-p0[1])<width*width){
    x2--; 
    y2=mper*(x2-p0[0])+p0[1];
  }}
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
  for(int i=0;i<frame->nr-2;i+=2){
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
void findArticulaciones4(pata *frame){
pointBresenham(frame,frame->p0,frame->pf);
int art1[2], art2[2], art3[2];
int dir1, dir2=1,dir3;
int mx, my;
int flag=0;
  for(int i=0;i<frame->nr-2;i++){
    for(int j=0;j<frame->nc;j++){
      dir1=0;
      if(frame->imagen[i][j]==255){
        do{
          dir1++;
        }while(frame->imagen[i][j+dir1]!=127);
      }
      if(frame->imagen[i][j]==127){
        do{
          dir1++;
        }while(frame->imagen[i][j+dir1]!=255);
       }
     if(dir1>dir2){
      dir2=dir1;
      mx=j; my=i;
     } 
    }
    }
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


void findArticulaciones2(pata *frame){
  int ll, ul, li, ld;
  int flag=0; 
  for(li=0;li<frame->nc;li++){
    for(int i=0;i<frame->nr;i++)
      if(frame->imagen[i][li]!=0){flag=1; break;}
    if(flag==1) {flag=0;break;}
  }
  for(ld=(frame->nc -1);ld>=0;ld--){
    for(int i=0;i<frame->nr;i++)
      if(frame->imagen[i][ld]!=0){flag=1; break;}
    if(flag==1) {flag=0;break;}
  }
  for(ul=0;ul<frame->nr;ul++){
    for(int j=0;j<frame->nc;j++)
      if(frame->imagen[ul][j]!=0){flag=1; break;}
    if(flag==1) {flag=0;break;}
  }
  for(ll=(frame->nr -1);ll>=0;ll--){
    for(int j=0;j<frame->nc;j++)
      if(frame->imagen[ll][j]!=0){flag=1; break;}
    if(flag==1) {flag=0;break;}
  }
  
int dir1, dir2,dir3;
  for(int i=0;i<frame->nr-2;i+=2){
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

  frame->a2[0]=(frame->pf[0]+frame->p0[0])/2; frame->a2[1]=10+ul+2*(ll-ul)/4;
  if(frame->p0[0]>frame->pf[0]){
    frame->a2[0]=frame->a1[0]+5+rand()%10;
  }
  if(abs(frame->a2[0]-frame->pf[0])<30){
    frame->a3[0]=li+10; frame->a3[1]=(frame->a2[1]+frame->pf[1])/2;
  }
  else if(frame->a2[0]<frame->pf[0]){
  frame->a3[0]=frame->a2[0]+10; frame->a3[1]=frame->pf[1]-10;
  }
  else{
  frame->a3[0]=frame->pf[0]-10; frame->a3[1]=frame->a2[1]+rand()%7;
  }
}

void findArticulaciones3(pata *frame){
int i,j;
int gi,gj;
int G[3][3];
  for(int i;i<frame->nr;i++){
    for(int j;j<frame->nc;j++){
      if(frame->imagen[i][j]==255){
         gi=i; gj=j;
         for(int ni=0;ni<3;ni++){
          for(int nj=0;nj<3;nj++){
            G[ni][nj]=frame->imagen[gi+ni-1][gj+nj-1];
          }
         }
      }
    }
  }


}

void algorithmHarris(pata *frame){
double A[2][2]; 
int p[2];
double Response,traza; 
double lamb1, lamb2; 
double Ix, Iy;
   for(int i=4;i<frame->nr-3;i++){
     for(int j=4;j<frame->nc-3;j++){
        for(int x=-2;x<=2;x++){
          for(int y=-2;y<=2;y++){
          Ix+=(double)(frame->imagen[i+y][j+x+1]-frame->imagen[i+y][j+x-1])/2.0;
          Iy+=(double)(frame->imagen[i+y+1][j+x]-frame->imagen[i+y-1][j+x])/2.0;
        }}
        A[0][0]=Ix*Ix; A[1][1]=Iy*Iy; 
        A[0][1]=Ix*Iy; A[1][0]=Ix*Iy;
        traza=A[0][0]+A[1][1];
        Response=A[0][0]*A[1][1]-A[1][0]*A[0][1]-0.06*traza*traza;
        if(frame->imagen[i][j]!=0)printf("%lf\n",Response);
        if(fabs(Response)>100000000){
         p[0]=j; p[1]=i;
         dibujaPunto(frame,p);
        }
        Ix=0; Iy=0;
     }
   }
     
}

   




/* Funciones para la Evolucion Diferencial*/
void initPob(int **poblacion,int np, int *lims){
 for(int i=0;i<np;i++){
    poblacion[i][0]=2+rand()%lims[0];
    poblacion[i][1]=lims[1]+(rand()%3-1)*(rand()%(10));
    poblacion[i][2]=lims[2]+(rand()%3-1)*(rand()%(10));
    poblacion[i][3]=lims[3]+(rand()%3-1)*(rand()%(10));
    poblacion[i][4]=lims[4]+(rand()%3-1)*(rand()%(10));
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
      V[i][j]=poblacion[rs[0]][j]+(int)(F*randx()*(double)(poblacion[rs[1]][j]-poblacion[rs[2]][j]));
   }
   if(V[i][0]>lims[0]+10 || V[i][0]<3) V[i][0]=2+rand()%lims[0];
   if(V[i][1]>lims[1]+15 || V[i][1]<lims[1]-15) V[i][1]=lims[1]+rand()%(15);
   if(V[i][2]>lims[2]+15 || V[i][2]<lims[2]-15) V[i][2]=lims[2]+rand()%(15);
   if(V[i][3]>lims[3]+15 || V[i][3]<lims[3]-15) V[i][3]=lims[3]+rand()%(15);
   if(V[i][4]>lims[4]+15 || V[i][4]<lims[4]-15) V[i][4]=lims[4]+rand()%(15);
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

double *obtenerAngulos(pata *frame, int iter, int np, double F, double Cr){
double *aux=(double*)malloc(4*sizeof(double));
int *xb1=(int*)malloc(5*sizeof(int));
int *xb2=(int*)malloc(5*sizeof(int));
int *xb3=(int*)malloc(5*sizeof(int));
int *xb4=(int*)malloc(5*sizeof(int));
  puntoInicial(frame);
  puntoFinal(frame);
  findArticulaciones2(frame);
int lim1[5]={6,frame->p0[0],frame->p0[1],frame->a1[0],frame->a1[1]};
int lim2[5]={6,frame->a1[0],frame->a1[1],frame->a2[0],frame->a2[1]};
int lim3[5]={6,frame->a2[0],frame->a2[1],frame->a3[0],frame->a3[1]};
int lim4[5]={6,frame->a3[0],frame->a3[1],frame->pf[0],frame->pf[1]};
  xb1=algorithmDE(np,iter,F,Cr,lim1,*frame);
  int p01[2]={xb1[1],xb1[2]};
  int pf1[2]={xb1[3],xb1[4]};
  xb2=algorithmDE(np,iter,F,Cr,lim2,*frame);
  int p02[2]={xb2[1],xb2[2]};
  int pf2[2]={xb2[3],xb2[4]};
  xb3=algorithmDE(np,iter,F,Cr,lim3,*frame);
//printf("y aca?\n");
  int p03[2]={xb3[1],xb3[2]};
  int pf3[2]={xb3[3],xb3[4]};
  xb4=algorithmDE(np/2,iter/2,F,Cr,lim4,*frame);
  int p04[2]={xb4[1],xb4[2]};
  int pf4[2]={xb4[3],xb4[4]};
  dRectangulo(frame,p01,pf1,xb1[0]);
  dRectangulo(frame,p02,pf2,xb2[0]);
  dRectangulo(frame,p03,pf3,xb3[0]);
  dRectangulo(frame,p04,pf4,xb4[0]);
  aux[0]=atan2((double)(pf1[1]-p01[1]),(double)(pf1[0]-p01[0]));  
  aux[1]=atan2((double)(pf2[1]-p02[1]),(double)(pf2[0]-p02[0]));  
  aux[2]=atan2((double)(pf3[1]-p03[1]),(double)(pf3[0]-p03[0]));  
  aux[3]=atan2((double)(pf4[1]-p04[1]),(double)(pf4[0]-p04[0]));  
free(xb1);free(xb2);free(xb3);free(xb4);
return(aux);}
void ratMove(char *pref, int nf,double **ang,int iter,int np,double F,double Cr){
 int nr, nc, maxw;
 int tp=strlen(pref);
  double Pi=4*atan(1);
 pata myframe;
 FILE *out; 
 out=fopen("angulos.dat","w");
for(int f=0;f<nf;f++){
  sprintf(&pref[tp],"_%d.pgm",f+1);
  readFrame(pref,&myframe);
  ang[f]=obtenerAngulos(&myframe,np,iter,F,Cr);
  fprintf(out,"%d %lf %lf %lf %lf\n",f+1,ang[f][0]/Pi,ang[f][1]/Pi,ang[f][2]/Pi,ang[f][3]/Pi);
  printf("Se termino de procesar el frame <%d>\n",f+1);
  //for(int i=0;i<4;i++)printf("%lf ",ang[f][i]);
  //printf("\n");
  sprintf(&pref[tp],"_ang%d.pgm",f+1);
  writePgm(myframe.imagen,myframe.nr,myframe.nc,myframe.gs,pref);
}   
fclose(out);

}
