mpicc -o prog7 prog7.c
mpirun -np 4 ./prog7


*/

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int data;

    MPI_Init(&argc, &argv);                 // Initialize MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get current process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get number of processes

    if (rank == 0) {
        data = 100;  // Initialize data only in root process
        printf("Process %d broadcasting data = %d\n", rank, data);
    }

    // Broadcast data from process 0 to all processes
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf("Process %d received data = %d\n", rank, data);

    MPI_Finalize();  // Finalize MPI environment
    return 0;
}

