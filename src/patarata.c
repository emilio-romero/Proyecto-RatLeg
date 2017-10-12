#include "patarata.h" 

void puntoInicial(pata *frame){
int i,j,flag=0; 
  for(i=0;i<frame->nr;i++){
    for(j=0;j<frame->nc;j++){
      if(frame->imagen[i][j]!=0){flag=1; break;} 
    }
    if(flag==1) break;
  }
  frame->p0[0]=i+5; 
  frame->p0[1]=j;

}

void dibujaPunto(pata *frame){
int x,y;
for(int i=frame->p0[0]-4;i<frame->p0[0]+4;i++){
  for(int j=(frame->p0[1])-4;j<(frame->p0[1])+4;j++){
    x=(i-(frame->p0[0]))*(i-(frame->p0[0]));  
    y=(j-(frame->p0[1]))*(j-(frame->p0[1]));  
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

void angleBresenham(pata *frame, int i0, int j0, double th, int dist ){
int xf,yf;
xf=j0+(int)round(dist*cos(th));
yf=i0+(int)round(dist*sin(th));
int dx=xf-j0;
int dy=yf-i0;
int i=i0; 
int eps=dx-dy; 

for(int j=j0;j<xf-1;j++){
  frame->imagen[i][j]=127;
  if(eps>=0){
    i++;
    eps-=dx; 
  }
  eps+=dy;
}

}


