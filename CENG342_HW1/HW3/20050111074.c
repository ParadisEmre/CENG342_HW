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

void parallel_multiply(double **matrix, double *vector, int row, int column, int rank, int size) {
    
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
        int b = 0;
        for(b = 0; b < row; b++){
        	final_result[b] =0;
		}
    }
    
	MPI_Barrier(MPI_COMM_WORLD);	
    MPI_Reduce(result, final_result, row, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        double end_time = MPI_Wtime();
        printf("Time elapsed for parallel multiplication: %f seconds\n", end_time - start_time);
    }
    
	int a = 0; 
    for(a = 0; a < row; a++){
    	printf("\nResult: %f", final_result[a]);
	}

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
	double **large_arr, *large_vec, **small_arr, *small_vec;
        createArray(&large_arr, 1074, 1074);
        createVector(&large_vec, 1074);
    	createArray(&small_arr, 174, 174);
        createVector(&small_vec, 174);
        parallel_multiply(&*large_arr, &*large_vec, 1074, 1074, rank, size);
        //parallel_multiply(&*small_arr, &*small_vec, 174, 174, rank, size);
        MPI_Finalize();
    return 0;
}
