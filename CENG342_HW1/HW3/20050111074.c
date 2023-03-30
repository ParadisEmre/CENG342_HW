#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <mpi.h>

//Emre Özçatal 20050111074

//Creates a vector with random values.
void createVector(double **vec, int column) {
	
    srand(200501); 

    *vec = (double *)malloc(column * sizeof(double));
    
	int i = 0;
    for (i = 0; i < column; i++) {
        (*vec)[i] = ((double) rand() / RAND_MAX) * (100 - 1) + 1; 
    }
}

//Creates an array with random values.
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

//Prints contents to a file
void printFile(char* f, double *arr, int size) {
    
	FILE *file;
    file = fopen(f, "w");
    
    int i = 0;
    for (i = 0; i < size; i++) {
        fprintf(file, "%.2f\n", arr[i]);
    }
    
    fclose(file);
}

//Matrix-Vector multiplication using MPI.
double* parallel_multiply(double **matrix, double *vector, int row, int column, int rank, int size) {
    
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
        printf("Process Amount: %d, Time: %f seconds\n", size, end_time - start_time);
    }

	return final_result;

}

int main(int argc, char **argv) {
    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc < 3) {
		printf("Not enough data.");
	}
	int row = atoi(argv[1]);
    int column = atoi(argv[2]);
    char *output = argv[3];
    
	double **large_arr, *large_vec, **small_arr, *small_vec;
	
	createArray(&large_arr, row, column);
    createVector(&large_vec, row);
	printFile(output, parallel_multiply(&*large_arr, &*large_vec, row, column, rank, size), row);
	
	//createArray(&small_arr, 174, 174);
    //createVector(&small_vec, 174);
    //parallel_multiply(&*small_arr, &*small_vec, 174, 174, rank, size);
    MPI_Finalize();
    
	return 0;
}
