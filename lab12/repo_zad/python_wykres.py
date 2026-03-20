import matplotlib.pyplot as plt
import numpy as np


threads_processes = [1, 2, 4, 8]
time_openmp = [0.163169, 0.100511, 0.077576, 0.054851]  
time_mpi = [0.066297, 0.044164, 0.030251,0.032386]    


speedup_openmp = [time_openmp[0]/t for t in time_openmp]
speedup_mpi = [time_mpi[0]/t for t in time_mpi]


efficiency_openmp = [s/p for s, p in zip(speedup_openmp, threads_processes)]
efficiency_mpi = [s/p for s, p in zip(speedup_mpi, threads_processes)]


plt.figure(figsize=(10, 4))

plt.subplot(1, 2, 1)
plt.plot(threads_processes, speedup_openmp, 'bo-', label='OpenMP')
plt.plot(threads_processes, speedup_mpi, 'ro-', label='MPI')
plt.plot(threads_processes, threads_processes, 'k--', label='Idealne')
plt.xlabel('Liczba wątków/procesów')
plt.ylabel('Przyspieszenie')
plt.title('Przyspieszenie obliczeń')
plt.legend()
plt.grid(True)


plt.subplot(1, 2, 2)
plt.plot(threads_processes, efficiency_openmp, 'bo-', label='OpenMP')
plt.plot(threads_processes, efficiency_mpi, 'ro-', label='MPI')
plt.axhline(y=1.0, color='k', linestyle='--', label='Idealna')
plt.xlabel('Liczba wątków/procesów')
plt.ylabel('Efektywność')
plt.title('Efektywność zrównoleglenia')
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.savefig('wydajnosc_wykresy.png', dpi=300)
plt.show()