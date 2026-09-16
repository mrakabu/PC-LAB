#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int data[5];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) {
            printf("This program requires at least 2 MPI processes.\n");
        }

        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        for (int i = 0; i < 5; i++) {
            data[i] = i * 10;
        }

        printf("Process 0 sending data to process 1...\n");

        MPI_Send(data, 5, MPI_INT, 1, 0, MPI_COMM_WORLD);

        printf("Process 0 sent data.\n");

    } else if (rank == 1) {
        MPI_Status status;

        MPI_Recv(data, 5, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        printf("Process 1 received data: ");

        for (int i = 0; i < 5; i++) {
            printf("%d ", data[i]);
        }

        printf("\n");
    }

    MPI_Finalize();

    return 0;

  //mpicc prog5.c -o prog5
  //mpirun -np 2 ./prog5
}
