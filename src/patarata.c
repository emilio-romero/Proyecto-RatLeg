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
