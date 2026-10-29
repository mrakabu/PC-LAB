mpicc prog6a.c -o prog6a
mpirun -np 2 ./prog6a



#include <mpi.h>
#include <stdio.h>

#define MSG_SIZE 10000000
int msg_send[MSG_SIZE], msg_recv[MSG_SIZE];

int main(int argc, char *argv[]) {
    int rank, size;
    int msg_send = 100, msg_recv;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        if(rank == 0)
            printf("This program requires exactly 2 processes.\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        // Both processes do MPI_Send first causing deadlock
        MPI_Send(&msg_send, MSG_SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&msg_recv, MSG_SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);

        printf("Process 0 received %d\n", msg_recv);
    } else if (rank == 1) {
        MPI_Send(&msg_send, MSG_SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(&msg_recv, MSG_SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Process 1 received %d\n", msg_recv);
    }

    MPI_Finalize();
    return 0;
}
