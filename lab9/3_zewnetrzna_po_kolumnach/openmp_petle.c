#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10

int main() {
    double a[WYMIAR][WYMIAR];
    
    // Inicjalizacja
    for(int i=0; i<WYMIAR; i++) 
        for(int j=0; j<WYMIAR; j++) 
            a[i][j] = 1.02*i + 1.01*j;
    
    // Suma sekwencyjna
    double suma = 0.0;
    for(int i=0; i<WYMIAR; i++) {
        for(int j=0; j<WYMIAR; j++) {
            suma += a[i][j];
        }
    }
    printf("Suma wyrazów tablicy (sekwencyjnie): %lf\n\n", suma);
    
    // Dekompozycja kolumnowa
    printf("=== DEKOMPOZYCJA KOLUMNOWA (ręczna redukcja, static) ===\n");
    double suma_parallel = 0.0;
    
    #pragma omp parallel default(none) shared(a, suma_parallel)
    {
        double suma_lokalna = 0.0;
        
        #pragma omp for schedule(static) 
        for(int j=0; j<WYMIAR; j++) {
            for(int i=0; i<WYMIAR; i++) 
            {
                //#pragma omp ordered
                {
                    suma_lokalna += a[i][j];
                    
                    printf("(%1d,%1d)-W_%1d ", i, j, omp_get_thread_num());
                }
            }
            #pragma omp ordered
            printf("\n");
        }
        
        //sekcjia krytyczna
        #pragma omp critical
        {
            suma_parallel += suma_lokalna;
            printf("Wątek %d dodał swoją sumę lokalną: %lf\n", omp_get_thread_num(), suma_lokalna);
        }
    }
    
    printf("\nSuma wyrazów tablicy równolegle: %lf\n", suma_parallel);
   
    return 0;
}