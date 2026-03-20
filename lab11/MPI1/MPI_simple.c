#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include<unistd.h>

#define HOSTNAME_LEN 256

#include "mpi.h"

int main( int argc, char** argv )
{ 

  char hostname[HOSTNAME_LEN];
  
  int rank, ranksent, size, source, dest, tag, i; 
  MPI_Status status;


  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  if(size>1)
  {
    
    if( rank != 0 )
    { 
      dest=0; tag=0; 

      gethostname(hostname, HOSTNAME_LEN);
      
      MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
      MPI_Send( hostname, HOSTNAME_LEN, MPI_CHAR, dest, tag, MPI_COMM_WORLD );
      
    } 
    else 
    {
      for( i=1; i<size; i++ ) 
      { 
        char recv_hostname[HOSTNAME_LEN];
        
	      MPI_Recv( &ranksent, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status );

        MPI_Recv( recv_hostname, HOSTNAME_LEN, MPI_CHAR, status.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status );

	    printf("Dane od procesu %d: ranga=%d, host=%s\n", status.MPI_SOURCE, ranksent, recv_hostname);
      
      }
      
    }

  }
  else
  {
	printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }

  
  MPI_Finalize(); 
  
  return(0);

}

