#include <stdio.h>
#include <omp.h>

int main() {
    int n;

    printf("Enter number of iterations: ");
    scanf("%d", &n);

    omp_set_num_threads(4);

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();

        #pragma omp for schedule(static,2)
        for (int i = 0; i < n; i++) {
            printf("Thread %d : Iteration %d\n", tid, i);
        }
    }

    return 0;
}

//gcc -fopenmp prog2.c -o prog2
//  ./prgm2
