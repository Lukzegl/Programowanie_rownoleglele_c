CC = mpicc
CFLAGS = -O3 -Wall
LDFLAGS = -lm
OMP_FLAGS = -fopenmp

# Programy
TARGETS = MPI_pi mat_vec_row_MPI_modified calka_omp oblicz_PI_original

all: $(TARGETS)

MPI_pi: MPI_pi.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

mat_vec_row_MPI_modified: mat_vec_row_MPI_modified.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

calka_omp: calka_omp.c
	gcc $(CFLAGS) $(OMP_FLAGS) -o $@ $< $(LDFLAGS)

oblicz_PI_original: oblicz_PI_original.c
	gcc $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(TARGETS) *.o

run_pi: MPI_pi
	mpiexec -np 4 ./MPI_pi

run_matvec: mat_vec_row_MPI_modified
	mpiexec -np 4 ./mat_vec_row_MPI_modified

run_calka: calka_omp
	export OMP_NUM_THREADS=4 && ./calka_omp

.PHONY: all clean run_pi run_matvec run_calka