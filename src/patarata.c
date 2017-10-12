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
