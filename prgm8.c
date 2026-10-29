mpicc -o prog8 prog8.c
mpirun -np 4 ./prog8


#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    const int N = 8;             
    int sendbuf[N];              
    int recvbuf[N / 4];          
    
    MPI_Init(&argc, &argv);      
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4) {
        if (rank == 0) 
            printf("Please run with 4 processes.\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        // Initialize the array with values 0 to 7
        for (int i = 0; i < N; i++) {
            sendbuf[i] = i;
        }
        printf("Root process has array: ");
        for (int i = 0; i < N; i++) {
            printf("%d ", sendbuf[i]);
        }
        printf("\n");
    }
MPI_Scatter(sendbuf, N / size, MPI_INT, recvbuf, N / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process prints its received chunk
    printf("Process %d received chunk: ", rank);
    for (int i = 0; i < N / size; i++) {
        printf("%d ", recvbuf[i]);
    }
    printf("\n");

    // Each process modifies its chunk (e.g., multiply each element by 2)
    for (int i = 0; i < N / size; i++) {
        recvbuf[i] *= 2;
    }

    // Gather the modified chunks back to root process
    MPI_Gather(recvbuf, N / size, MPI_INT, sendbuf, N / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Root process prints the gathered, modified array
    if (rank == 0) {
        printf("Root process gathered modified array: ");
        for (int i = 0; i < N; i++) {
            printf("%d ", sendbuf[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

