#include "assignment1.h"

double ** choleskyDecomp(double ** A, int n, int i){
	int loop, loop1, loop2, loop3, loop4; 
	double **Anext, **L; 

	//base case
	if (identity(A,n)) return A; 

	else{
		//create A
		initMatrix(&Anext, n); 
		//first populate diagonals with 1.0
		for (loop = 0; loop <= i; loop ++){ 
			Anext[loop][loop] = 1.0; 
		}
		//populate the rest as specfied in the math
		for (loop1 = i+1; loop1 < n; loop1++){ 
			for (loop2 = i+1; loop2<n; loop2++){ 
			Anext[loop1][loop2] = A[loop1][loop2] - A[loop1][i]*A[i][loop2] /A[i][i];  
			}
		}

		//create L
		initMatrix(&L, n);
		//populate the diagonals with 1.0 except the ith element
		for (loop3 = 0; loop3 < n; loop3++){	 
			if (loop3 == i) {
				L[loop3][loop3] = sqrt(A[i][i]); 
				}
			else L[loop3][loop3] = 1.0; 
		}
		//then populate the rest as specfied by the math
		for (loop4 = i+1; loop4 < n; loop4++){ 
			L[loop4][i] = A[loop4][i] / L[loop4][loop4]; 
		}	

		//freeMatrix
		freeMatrix(A,n); 
		A = NULL;
		//recursive call
		return mult(L, choleskyDecomp(Anext, n, i+1), n); 	

	}
}

double ** mult(double ** L1,double ** L2, int n){
	//initialize variables for loops
	int i;
	int rows1, rows2, columns2;

	//dynamically allocate memory for 2D array
	double **res;
	initMatrix(&res, n);
	
	//multiply the matrices and store it into result
	for (rows1=0; rows1<n; rows1++){
		for (columns2=0; columns2<n; columns2++){
			//res[rows1][columns2] = 0;
			for (rows2 = 0; rows2<n; rows2++){
				res[rows1][columns2] += (L1[rows1][rows2])*(L2[rows2][columns2]);
			}
		}
	}
	
	//free matrices L1 and L2
	if (L1 != L2){	
		freeMatrix(L1, n);
		freeMatrix(L2, n);	 	
	
	}

	else {
		freeMatrix(L1, n);
	}	

	return res;
}


int identity(double ** A, int n){
	//default answer: yes, it is an identity matrix
	int i, j;  
	for (i=0; i<n; i++){
		for (j=0; j<n; j++){
			if ( (i==j) && (A[i][j] != 1) ) return 0;
			else if ( (i!=j) && (A[i][j] != 0) ) return 0;
		}
	}
	return 1; 
}


void initMatrix(double ***mat,int n){
	//dynamically allocates memory for 2D array of size n
	//return triple pointer to 
	int i, j;
	double **matrix = (double **)malloc(sizeof(double*)*n);
	if (matrix != NULL){
	for (i=0; i<n; i++){
		//allocate space for 1D arrays
		matrix[i] = (double *)malloc(sizeof(double)*n);
		if (matrix[i] != NULL){
			//initialize elements to 0.00
			for (j= 0; j<n; j++){
				matrix[i][j] = 0.00; 
			}
		}
	}
	*mat = matrix; 
	}
}

double **readMatrix(char * filename){
	int i, j; 

	//dynamically allocate memory
	double **my_matrix; 
	initMatrix(&my_matrix, MATSIZE);	
	//open file contain matrix data
	FILE *fp = fopen(filename, "r");
	//read file into 2D matrix just declared
	for (i=0; i<MATSIZE; i++){
		for (j=0; j<MATSIZE; j++){
		fscanf(fp, "%lf", &(my_matrix[i][j]));
		}
	}
	fclose(fp);		
	return my_matrix; 	
}

void freeMatrix(double ** matrix, int n){
	int i; 
	for (i=0; i<n; i++){
		free(matrix[i]);
		matrix[i] = NULL;
	}	
	free(matrix);
	matrix = NULL;
}

void printMatrix(double ** A, int n)
{
	int i, j;
	for (i=0; i<n; i++){
		for (j=0; j<n; j++){
			printf("%lf ", A[i][j]);			
		}
	printf("\n");
	}
}

