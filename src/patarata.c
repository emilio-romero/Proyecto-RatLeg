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

void dibujaPunto(pata *frame){
int x,y;
for(int i=frame->p0[1]-4;i<frame->p0[1]+4;i++){
  for(int j=(frame->p0[0])-4;j<(frame->p0[0])+4;j++){
    x=(i-(frame->p0[1]))*(i-(frame->p0[1]));  
    y=(j-(frame->p0[0]))*(j-(frame->p0[0]));  
    if((x+y)<16){frame->imagen[i][j]=127;}
  }
}
}

void dibujaLinea(pata *frame,int x0, int y0, double th, int dist){
int x,y; 
  for(int i=x0;i<=x0+((int)round(dist*sin(th)));i++){
    for(int j=y0;j<=y0+((int)round(dist*cos(th)));j++){
      x=(int)round(i*sin(th));
      y=(int)round(j*cos(th));
    printf("x:%d",x);
    printf(" ,y:%d\n",y);
      frame->imagen[x][y]=127;
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
void findRectangulo(int x0, int y0, int xf, int yf, int width){
double  m=(double)(yf-y0)/(double)(xf-x0);
printf("\nLa pendiente de la recta es: %lf",m);
double mper=-1.0/m; 
printf("\nLa pendiente de la recta perpendicular es: %lf",mper);
int x1,y1; int x2,y2; int x3,y3; int x4,y4;
printf("\nLa mitad de la distancia es: %d",width/2);
//============== un  punto
x1=x0; y1=y0; 
while((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)<width*width){
x1++; 
y1=mper*(x1-x0)+y0;
}
printf("\nUn punto del rectangulo es:\n (%d,%d)",x1,y1);
//============= otro punto 
x1=x0; y1=y0; 
while((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)<width*width){
x1--; 
y1=mper*(x1-x0)+y0;
}
printf("\nOtro punto del rectangulo es:\n (%d,%d)",x1,y1);
//============== un  punto
x1=xf; y1=yf; 
while((x1-xf)*(x1-xf)+(y1-yf)*(y1-yf)<width*width){
x1++; 
y1=mper*(x1-xf)+yf;
}
printf("\nUn punto del rectangulo es:\n (%d,%d)",x1,y1);
//============= otro punto 
x1=xf; y1=yf; 
while((x1-xf)*(x1-xf)+(y1-yf)*(y1-yf)<width*width){
x1--; 
y1=mper*(x1-xf)+yf;
}
printf("\nOtro punto del rectangulo es:\n (%d,%d)",x1,y1);
}


void dRectangulo(pata *frame,int x0, int y0, int xf, int yf, int width){
  int x1,y1; int x2,y2; int x3,y3; int x4,y4;
  int t1[]={x0,y0}; 
  int t2[]={xf,yf};
  int *p0,*pf;
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
