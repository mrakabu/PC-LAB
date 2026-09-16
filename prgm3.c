#include <stdio.h>
#include <omp.h>

int fib(int n) {
    int x, y;

    if (n <= 1)
        return n;

    #pragma omp task shared(x)
    x = fib(n - 1);

    #pragma omp task shared(y)
    y = fib(n - 2);

    #pragma omp taskwait

    return x + y;
}

int main() {
    int n;

    printf("Enter the number of Fibonacci numbers to compute: ");
    scanf("%d", &n);

    double start = omp_get_wtime();

    printf("Fibonacci Series up to %d terms:\n", n);

    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < n; i++) {
                int result;

                #pragma omp task firstprivate(i) shared(result)
                {
                    int value = fib(i);

                    #pragma omp critical
                    {
                        printf("fib(%d) = %d\n", i, value);
                    }
                }
            }
        }
    }

    double end = omp_get_wtime();

    printf("Time taken: %f seconds\n", end - start);

    return 0;

  //gcc -fopenmp prog3.c -o prog3
  // ./prgm3
}
