#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char** argv) 
{
    int rank, size, prev, next;
    int data = 0;
    int rounds = 5;
    int i;
    MPI_Status status;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Obliczenie poprzednika i następnika
    prev = (rank + size - 1) % size;
    next = (rank + 1) % size;
    
    if(rank == 0) 
    {
        printf("Proces %d rozpoczyna sztafetę z liczbą: %d\n", rank, data);
    }
    
    
    for(i = 0; i < rounds; i++)
    {
        
        if(rank % 2 == 0)
        {
            
            MPI_Send(&data, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
            MPI_Recv(&data, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);
        }
        else
        {
            MPI_Recv(&data, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);
            MPI_Send(&data, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        }
        
        printf("Proces %d odebrał liczbę %d od procesu %d (runda %d)\n", rank, data, status.MPI_SOURCE, i+1);
        
        
        data++;
    }
    
    MPI_Finalize();
    return 0;
}

