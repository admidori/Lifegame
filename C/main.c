#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void set_parameter(int**,int);
int **new_state(int**,int);

int main(void){
  static int map=100; //map size=map*map
  static int state=300+1;
  static int sleep=70000; //micro sec

  int **cell;
  cell=(int **)malloc(map*sizeof(int*));
  for(int i=0;i<map;i++){
    cell[i]=(int *)malloc(map*sizeof(int));
  }
  set_parameter(cell,map);

  FILE *plot,*rec;
  plot=popen("gnuplot -persist","w");
  fprintf(plot,"set xrange [0:%d]\n",map);
  fprintf(plot,"set yrange [0:%d]\n",map);
  fprintf(plot,"set grid linetype 1 linecolor 0\n");
  fprintf(plot,"set xtics 2\n");
  fprintf(plot,"set ytics 2\n");
  fprintf(plot,"unset key\n");
  fprintf(plot,"set format x ''\n");
  fprintf(plot,"set format y ''\n");

  int **new_cell;
  for(int t=0;t<state;t++){
    rec=fopen("point.txt","w");
    fprintf(plot,"set title 'LIFE GAME %dx%d -- state=%d'\n",map,map,t);
    new_cell=new_state(cell,map);
    for(int i=0;i<map;i++){
      for(int j=0;j<map;j++){
        if(new_cell[i][j]==1){
          fprintf(rec,"%d %d\n",i+1,j+1);
        }
      }
    }
    fclose(rec);
    for(int i=0;i<map;i++){
      for(int j=0;j<map;j++){
        cell[i][j]=new_cell[i][j];
      }
    }
    new_cell=NULL;
    fprintf(plot,"plot 'point.txt' w p pt 7 ps 0.5\n");
    fflush(plot);
    usleep(sleep);
  }
  fprintf(plot,"exit\n");
  fflush(plot);
  pclose(plot);
}
