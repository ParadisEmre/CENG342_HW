#include <stdio.h>
#include <time.h>
#include <stdlib.h>


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


double* multiply(double **matrix, double *vector, int row, int column) {
	
    double *result = (double *)malloc(row * sizeof(double));
    int i = 0, j = 0;
    
    for(i = 0; i < row; i++)
    {
        result[i] = 0;
        for(j = 0; j < column; j++)
        {
            result[i] += matrix[i][j] * vector[j];
        }                  
    }
    
    return result;

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

int main(int argc, char *argv[]){

    if(argc < 3 ){
        printf("Give more information.");
    }
    else{
    	int row = atoi(argv[1]);
        int column = atoi(argv[2]);
        char *output = argv[3];
        
        double **arr, *vec;
        createArray(&arr, row, column);
        createVector(&vec, column);
        double *result = multiply(&*arr, &*vec, row, column);
        int i = 0;
        printf("RESULT: \n");
        for(i = 0; i < row; i++){
        	printf("%.2f \n", result[i]);
		}
		
		printFile(output, result, row);
	}      
    

    return 0;
}


