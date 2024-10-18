#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10000000

int main(int argc, char** argv) {
    int world_size, world_rank;
    double start_time, end_time;
    long long int i, sum = 0;
    int* data = (int*)malloc(ARRAY_SIZE * sizeof(int));

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

         // Initialize data
    srand(time(NULL) + world_rank);
    for (i = 0; i < ARRAY_SIZE; i++) {
        data[i] = rand() % 100;
    }
    start_time = MPI_Wtime();
    // Perform a simple sum
    for (i = world_rank; i < ARRAY_SIZE; i += world_size) {
        sum += data[i];
    }
    long long int global_sum;
    MPI_Reduce(&sum, &global_sum, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    end_time = MPI_Wtime();
    if (world_rank == 0) {
        printf("Sum: %lld\n", global_sum);
        printf("Time taken: %f seconds\n", end_time - start_time);
    }
    free(data);
    MPI_Finalize();
    return 0;
}
