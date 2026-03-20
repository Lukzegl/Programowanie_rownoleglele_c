#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10

int main() {
    double a[WYMIAR][WYMIAR];
    
 
    for(int i=0; i<WYMIAR; i++) 
    {
        for(int j=0; j<WYMIAR; j++) 
        {
            a[i][j] = 1.02*i + 1.01*j;
        }
    
    }
    double suma = 0.0;
    for(int i=0; i<WYMIAR; i++) 
    {
        for(int j=0; j<WYMIAR; j++) 
        {
            suma += a[i][j];
        }
    }

    printf("Suma wyrazów tablicy (sekwencyjnie): %lf\n\n", suma);
    
  
onp_set_num_threads(4);

    printf("DEKOMPOZYCJA 2D\n");
    double suma_parallel = 0.0;
    
    #pragma omp parallel for default(none) shared(a) collapse(2) reduction(+:suma_parallel) schedule(static) ordered
    for(int i=0; i<WYMIAR; i++) {
        for(int j=0; j<WYMIAR; j++) {
            //#pragma omp ordered
            {
                suma_parallel += a[i][j];
                printf("(%1d,%1d)-W_%1d ", i, j, omp_get_thread_num());
                if(j == WYMIAR-1) printf("\n");
            }
        }
    }
    
    printf("\nSuma wyrazów tablicy równolegle: %lf\n", suma_parallel);
   
    return 0;
}