mpicc -o prog9 prog9.c
     mpirun -np 4 ./prog9

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int local_val, max_val, min_val, sum_val, prod_val;
    int all_max, all_min, all_sum, all_prod;

    MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Each process sets its local value (rank + 1)
    local_val = rank + 1;

    // MPI_Reduce: gather results at root (rank 0)
    MPI_Reduce(&local_val, &max_val, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_val, &min_val, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_val, &sum_val, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_val, &prod_val, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("MPI_Reduce results (at root):\n");
        printf("MAX = %d\n", max_val);
        printf("MIN = %d\n", min_val);
        printf("SUM = %d\n", sum_val);
        printf("PROD = %d\n", prod_val);
    }

    // MPI_Allreduce: gather results and distribute to all processes
    MPI_Allreduce(&local_val, &all_max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    MPI_Allreduce(&local_val, &all_min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
    MPI_Allreduce(&local_val, &all_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&local_val, &all_prod, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);

    printf("Process %d received MPI_Allreduce results: MAX=%d MIN=%d SUM=%d PROD=%d\n",
           rank, all_max, all_min, all_sum, all_prod);

    MPI_Finalize();
    return 0;
}
