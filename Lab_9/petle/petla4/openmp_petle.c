#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10

int main ()
{
  double a[WYMIAR][WYMIAR];

  for(int i=0;i<WYMIAR;i++) for(int j=0;j<WYMIAR;j++) a[i][j]=1.02*i+1.01*j;

  // podwĂłjna pÄtla - sekwencyjnie
  double suma=0.0;
  for(int i=0;i<WYMIAR;i++) {
    for(int j=0;j<WYMIAR;j++) {
      suma += a[i][j];
    }
  }
  
  printf("Suma wyrazów tablicy: %lf\n", suma);

  omp_set_nested(1);

  // podwĂłjna pÄtla - docelowo rĂłwnolegle
  double suma_parallel=0.0; int i,j;
  #pragma omp parallel for schedule(static) default(none) shared(a) private(j) reduction(+:suma_parallel) ordered
  for(i=0;i<WYMIAR;i++) {
    int id_w = omp_get_thread_num();
    #pragma omp ordered
    #pragma omp parallel for schedule(static) default(none) shared(a,i,id_w) reduction(+:suma_parallel) ordered
    for(j=0;j<WYMIAR;j++) {
      suma_parallel += a[i][j];
      #pragma omp ordered
      printf("(%1d,%1d)-W_[%1d,%1d] ",i,j,id_w,omp_get_thread_num()); 
    }
    #pragma omp ordered
    printf("\n");
  }

  printf("Suma wyrazów tablicy równolegle: %lf\n", suma_parallel);

}