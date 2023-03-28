#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <mpi.h>

void createVector(double **vec, int column) {
	
    srand(200501); 

    *vec = (double *)malloc(column * sizeof(double));
    
	int i = 0;
    for (i = 0; i < column; i++) {
        (*vec)[i] = ((double) rand() / RAND_MAX) * (100 - 1) + 1; 
    }
    printf("VECTOR: \n");
	for (i = 0; i < column; i++) {
        printf("%.2f \n", (*vec)[i]);
    }

}

void createArray(double ***arr, int row, int column) {
	
    srand(11074); 

    *arr = (double **)malloc(row * sizeof(double *));
    
    int i = 0, j = 0;
    for (i = 0; i < row; i++) {
        (*arr)[i] = (double *)malloc(column * sizeof(double));
    }

    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            (*arr)[i][j] = ((double) rand() / RAND_MAX) * (100 - 1) + 1;
        }
    }
    printf("ARRAY: \n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            printf("%.2f ", (*arr)[i][j]);
        }
        printf("\n");
    }
    
}

void printFile(char* f, double *arr, int size) {
    
	FILE *file;
    file = fopen(f, "w");
    
    int i = 0;
    for (i = 0; i < size; i++) {
        fprintf(file, "%.2f\n", arr[i]);
    }
    
    fclose(file);
}

double *parallel_multiply(double **matrix, double *vector, int row, int column, int rank, int size) {
    
	double *result = (double *) malloc(row * sizeof(double));

    MPI_Barrier(MPI_COMM_WORLD);

    double start_time = MPI_Wtime();

    int i = 0, j = 0;
    for (i = rank; i < row; i += size) {
        result[i] = 0;
        for (j = 0; j < column; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    double *final_result = NULL;
    if (rank == 0) {
        final_result = (double *) malloc(row * sizeof(double));
    }

    MPI_Gather(result, row / size, MPI_DOUBLE, final_result, row / size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double end_time = MPI_Wtime();
        printf("Time elapsed for parallel multiplication: %f seconds\n", end_time - start_time);
    }

    return final_result;
}



int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc < 3) {
        if (rank == 0) {
            printf("Usage: mpirun -np <number of processes> %s <number of rows> <number of columns> <output file>\n", argv[0]);
        }
	}
	double **arr, *vec;
        createArray(&arr, 1074, 1074);
        createVector(&vec, 1074);
        double* result = parallel_multiply(&*arr, &*vec, 1074, 1074, rank, size);
        MPI_Finalize();
    return 0;
}
