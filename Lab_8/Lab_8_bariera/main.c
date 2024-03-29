#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

#include "bariera.h"

extern void bariera_init(int l_w, typ_bariery* tb);
extern void bariera(typ_bariery* tb);

#define LICZBA_W 4
//#define LICZBA_W 44

pthread_t watki[LICZBA_W];

typ_bariery b1;
typ_bariery b2;

void *cokolwiek( void *arg);

int main( int argc, char *argv[] ){

  int i, indeksy[LICZBA_W]; for(i=0;i<LICZBA_W;i++) indeksy[i]=i; 

  // use of pthread_once (once_control, init_routine) ?
  // int pthread_once(pthread_once_t *once_control, void (*init_routine)(void));
  // but init_routine has no arguments...

  bariera_init(LICZBA_W, &b1);
  bariera_init(2, &b2);

  for(i=0; i<LICZBA_W; i++ ) {
    pthread_create( &watki[i], NULL, cokolwiek, (void *) &indeksy[i] );
  }

  for(i=0; i<LICZBA_W; i++ ) pthread_join( watki[i], NULL );

  pthread_exit( NULL);  
}


void *cokolwiek( void *arg){

  int i, moj_id;

  moj_id = *( (int *) arg ); 

  printf("przed bariera 1 - watek %d\n",moj_id);

  bariera(&b1);

   printf("przed bariera 2 - watek %d\n",moj_id);

  bariera(&b1);

  printf("przed bariera 3 - watek %d\n",moj_id);

  bariera(&b1);

  printf("przed bariera 4 - watek %d\n",moj_id);

  bariera(&b1);

  printf("po ostatniej barierze - watek %d\n",moj_id);  

  pthread_exit( (void *)0);
}
