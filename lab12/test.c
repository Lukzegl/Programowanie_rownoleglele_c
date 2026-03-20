#include <stdio.h>
#include <omp.h>

int a = 7;   // zmienna globalna

#pragma omp threadprivate(a)

int main(void)
{
    int b = 5;
    int c = 4;
    int d = 1; // ta wartość i tak nie ma znaczenia, bo d będzie private

    #pragma omp parallel default(none) firstprivate(b) shared(c) private(d) num_threads(3)
    {
        #pragma omp barrier
        int e = b + c;
        a += omp_get_thread_num();
        #pragma omp atomic
        c += omp_get_thread_num();
        d += b + omp_get_num_threads();
        #pragma omp barrier
        printf("thread %d: a=%d, b=%d, c=%d, d=%d, e=%d\n",
               omp_get_thread_num(), a, b, c, d, e);
    }

    return 0;
}
