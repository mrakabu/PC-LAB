mpicc prog6b.c -o prog6b
mpirun -np 2 ./prog6b



#include <mpi.h>
#include <stdio.h>

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
        // rank 0 receives first, then sends
        MPI_Recv(&msg_recv, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        MPI_Send(&msg_send, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 received %d\n", msg_recv);
    } else if (rank == 1) {
        // rank 1 sends first, then receives
        MPI_Send(&msg_send, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(&msg_recv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Process 1 received %d\n", msg_recv);
    }

    MPI_Finalize();
    return 0;
}
