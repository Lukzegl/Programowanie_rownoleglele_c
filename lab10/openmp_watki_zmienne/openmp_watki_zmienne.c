#include<stdlib.h>
#include<stdio.h>
#include<omp.h>

//threadprivate
int f_threadprivate = 0;
#pragma omp threadprivate(f_threadprivate)

int main(){
  
#ifdef   _OPENMP
  printf("\nKompilator rozpoznaje dyrektywy OpenMP\n");
#endif

  int liczba_watkow;
  
  int a_shared = 1; // WAW zapisywane równolegle
  int b_private = 2;
  int c_firstprivate = 3; // WAR private in region
  int e_atomic = 5; // WAW atomic/critical
  

  omp_set_num_threads(5);
  
  printf("Liczba wątków: %d, ID wątku: %d\n",
         omp_get_num_threads(), omp_get_thread_num());
  printf("  a_shared \t\t= %d\n", a_shared);
  printf("  b_private \t\t= %d\n", b_private);
  printf("  c_firstprivate \t= %d\n", c_firstprivate);
  printf("  e_atomic \t\t= %d\n", e_atomic);
  printf("  f_threadprivate \t= %d\n", f_threadprivate);
int a_local_copy;
  a_local_copy = a_shared;
   
#pragma omp parallel default(none) shared(a_shared, e_atomic) private(b_private) firstprivate(c_firstprivate)
  {
    int i;
    int d_local_private;
    
    
     // Odczyt a_shared WRA - Read-After-Write - każdy watek nowe
     
    
    
    d_local_private = a_local_copy + c_firstprivate;
    
    
     /* 
        Write-After-Write */
    for(i = 0; i < 10; i++) 
    {
#pragma omp atomic
      a_shared++;
    }
    
     
    for(i = 0; i < 10; i++) 
    {
      c_firstprivate += omp_get_thread_num();
    }
    
     /*  e_atomic atomic linie 60 - 70
       WAW */
    for(i = 0; i < 10; i++) 
    {
#pragma omp atomic
      e_atomic += omp_get_thread_num();
    }
    
     /* Przypisanie f_threadprivate */
    f_threadprivate = omp_get_thread_num();
    
     
#pragma omp critical
    {
       printf("\n=========================================\n");
      printf("WĄTEK %d:\n", omp_get_thread_num());
      printf("  a_shared \t\t= %d\n", a_shared);
      printf("  b_private \t\t= %d\n", b_private);
      printf("  c_firstprivate \t= %d\n", c_firstprivate);
      printf("  d_local_private \t= %d\n", d_local_private);
      printf("  e_atomic \t\t= %d\n", e_atomic);
      printf("  f_threadprivate \t= %d\n", f_threadprivate);
    }
     /* BARIERA NIEJAWNA - koniec parallel region, wszystkie wątki czekają tutaj */
    }
  
  printf("\n=========================================\n");
  printf("  a_shared \t\t= %d\n", a_shared);
  printf("  b_private \t\t= %d\n", b_private); 
  printf("  e_atomic \t\t= %d\n", e_atomic);
  printf("  f_threadprivate \t= %d\n", f_threadprivate);

  
    /* RÓWNOLEGŁY REGION 2
    * Demonstracja threadprivate - każdy wątek ma swoją wartość f_threadprivate
    * z poprzedniego regionu (wartość zachowana między regionami)
    */
#pragma omp parallel default(none) shared(a_shared, e_atomic)
  {
     /* Wydruk wartości threadprivate dla każdego wątku */
#pragma omp critical
    {
      printf("Wątek %d: f_threadprivate = %d\n", omp_get_thread_num(), f_threadprivate);
    }
     /* BARIERA NIEJAWNA - koniec drugiego parallel region */
  }
  

  
  return 0;
}