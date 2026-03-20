#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>


#define WYMIAR 18


int main() 
{
    double a[WYMIAR];
    
   //omp_set_num_threads(4);
    
    #pragma omp parallel for default(none) shared(a)
    for(int i=0; i<WYMIAR; i++)
    { 
        a[i] = 1.02 * i;
    }

    //sekwencyjna
    double suma = 0.0;
    for(int i=0; i<WYMIAR; i++) 
    {
        suma += a[i];
    }
    printf("Suma wyrazów tablicy (sekwencyjnie): %lf\n", suma);
    
    //schedule(static, 3)
    printf("\nschedule(static, 3)\n");
    double suma_parallel1 = 0.0;

    omp_set_num_threads(10);

    #pragma omp parallel for default(none) shared(a) reduction(+:suma_parallel1) schedule(static, 3) num_threads(4) 
    
    for(int i=0; i<WYMIAR; i++) 
    {
        int id_w = omp_get_thread_num();
        suma_parallel1 += a[i];
       
        printf("a[%2d] -> W_%1d\n", i, id_w);
    }
    printf("Suma: %lf\n", suma_parallel1);
    
    //schedule(static) - domyslny
    printf("\nschedule(static) - domyślny\n");

    double suma_parallel2 = 0.0;

    #pragma omp parallel for default(none) shared(a) reduction(+:suma_parallel2) schedule(static) num_threads(4)
    
        for(int i=0; i<WYMIAR; i++) 
        {
            int id_w = omp_get_thread_num();
            suma_parallel2 += a[i];

           
            printf("a[%2d] -> W_%1d\n", i, id_w);
        }
    printf("Suma: %lf\n", suma_parallel2);
    
    // schedule(dynamic, 2)
    printf("\n schedule(dynamic, 2)\n");
    double suma_parallel3 = 0.0;
    #pragma omp parallel for default(none) shared(a) reduction(+:suma_parallel3) schedule(dynamic, 2) num_threads(4)
    for(int i=0; i<WYMIAR; i++) 
    {
        int id_w = omp_get_thread_num();
        suma_parallel3 += a[i];
       
        printf("a[%2d] -> W_%1d\n", i, id_w);
    }
    printf("Suma: %lf\n", suma_parallel3);
    
    // schedule(dynamic) - domyślny
    printf("\n schedule(dynamic) - domyślny \n");
    double suma_parallel4 = 0.0;
    #pragma omp parallel for default(none) shared(a) reduction(+:suma_parallel4) schedule(dynamic) num_threads(4)
            
    for(int i=0; i<WYMIAR; i++) 
    {
        int id_w = omp_get_thread_num();
        suma_parallel4 += a[i];
        
        printf("a[%2d] -> W_%1d\n", i, id_w);
    }
    printf("Suma: %lf\n", suma_parallel4);
    
    return 0;
}

/*
schedule(static, 3) – 3 KOL
schedule(static) –  5 5 4 4  18I 4W
schedule(dynamic, 2) – 2 IT
schedule(dynamic) = 1 IT
*/

/*
gcc -fopenmp openmp_petle_simple.c -o openmp_petle_simple
gcc -fopenmp openmp_petle.c -o openmp_petle
*/