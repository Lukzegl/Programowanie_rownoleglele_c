#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>

#include "pomiar_czasu.h"

int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku( void* argument )
{
  int zmiennna_lokalna = *(int*)argument;
  for(int i=0; i<1000000; i++)
  {
    zmienna_globalna++;
    zmiennna_lokalna++;
  } 

printf("Globalna = %d, Lokalna = %d \n",zmienna_globalna,zmiennna_lokalna);

  return 0;
}
 

int main()
{
 pid_t pid1;
 pid_t pid2;

 void *stos;
 void *stos2;

stos = malloc(ROZMIAR_STOSU);
stos2 = malloc(ROZMIAR_STOSU);
 int lokalna1 =0;
 int lokalna2 =0;

inicjuj_czas();

 pid2 = clone( &funkcja_watku, (void *) stos+ROZMIAR_STOSU, CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &lokalna1 );
 pid1 = clone( &funkcja_watku, (void *) stos2+ROZMIAR_STOSU, CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &lokalna2 );

  waitpid(pid2,NULL, __WCLONE);
  waitpid(pid1,NULL, __WCLONE);

  drukuj_czas();
  printf("Zmienne - Lokalna1 = %d, Lokalna2 = %d, Globalna = %d",lokalna1,lokalna2,zmienna_globalna);
  return 0;
}
