#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//Set first parameter(Recommend use random)
void set_parameter(int **cell,int map){
  srand(time(NULL));
  double random;
  for(int i=0;i<map;i++){
    for(int j=0;j<map;j++){
      random=(double)rand()/(double)RAND_MAX;
      if(random>0.5){
        cell[i][j]=1;
      }else{
        cell[i][j]=0;
      }
    }
  }
}

int **new_state(int **cell,int map){
  int **new_cell;
  new_cell=malloc(map*sizeof(int *));
  for(int i=0;i<map;i++){
    new_cell[i]=malloc(map*sizeof(int));
  }

  int sum=0;
  for(int i=1;i<map-1;i++){
    for(int j=1;j<map-1;j++){
      if(cell[i][j]==0){
        for(int k=-1;k<2;k++){
          for(int m=-1;m<2;m++){
            if(cell[i+k][j+m]==1){
              sum++;
            }
          }
        }
        if(sum==3){
          new_cell[i][j]=1;
        }else{
          new_cell[i][j]=0;
        }
      }else{
        for(int k=-1;k<2;k++){
          for(int m=-1;m<2;m++){
            if(cell[i+k][j+m]==1){
              sum++;
            }
          }
        }
        sum--;
        if(sum==3||sum==2){
          new_cell[i][j]=1;
        }else{
          new_cell[i][j]=0;
        }
      }
      sum=0;
    }
  }
  return new_cell;
}