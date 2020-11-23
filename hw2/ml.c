/* 
 * 
 * This code calculates the house price of a house by learing from
 * training data. It uses pseudo inverse of a given matrix to find the 
 * weight of different features.
 * 
 * Predicted Price : Y = W0 + W1*x1 + W2*X2 + W3*X3 + W4*X4
 * Weight Matrix : W = pseudoInv(X)*Y
 * pseudoInv(X) = inverse(transpose(X)*X) * transpose(X)  
 * 
 * weight(w) = pseudoInv(X) * Y
 * 			where	X = Input data matrix
 * 					Y = Target vector
 * 
 */
 
#include<stdio.h>
#include<stdlib.h>

// all methods declarations
double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2);
double** transposeMatrix(double** mat, int row, int col);
double** inverseMatrix(double **matA, int dimension);
void printMatrix(double** matrix, int rows, int cols);
void freeArray(double **a, int m);

// main method starts here
int main(int argc, char** argv){

    //Scanner for file
    FILE* fp = fopen(argv[1], "r");

    //Initialize dimension variables
    int K, N;
    fscanf(fp, "%d\n", &K);
    fscanf(fp, "%d\n", &N);
    K = K+1;

    //Initialize X and Y matrices to all 0's, and sets first columnof X to 1s
    double **X = (double**) malloc(N * sizeof(double*));
    for (int i = 0; i < N; i++){
        X[i] = (double*) malloc(K * sizeof(double));
    }
    double **Y = (double**) malloc(N * sizeof(double*));
    for (int i = 0; i < N; i++){
        Y[i] = (double*) malloc(1 * sizeof(double));
    }

    //Sets initial values in to matrices
    for (int i = 0; i < N; i++){
        X[i][0] = 1.0;
        for (int j = 1; j < K; j++){
            X[i][j] = 0.0;
        }
    }
    for (int i = 0; i < N; i++){
        Y[i][0] = 0.0;
    }

    //Scans document for X and Y matrices
    for (int i = 0; i < N; i++){
        for (int j = 1; j < K; j++){
            fscanf(fp,"%lf,", &X[i][j]);
        }
        fscanf(fp,"%lf\n", &Y[i][0]);
    }
    fclose(fp);
    // printf("X\n");
    // printMatrix(X, N, K);
    // printf("Y\n");
    // printMatrix(Y, N, 1);

    //Transpose of X
    double** X_Trans = transposeMatrix(X, N, K);
    //printf("Transpose of X\n");
    //printMatrix(X_Trans, K, N);

    //Product of X^T and X
    double** XtX = multiplyMatrix(X_Trans, X, K, N, N, K);
    //printf("X^t * X\n");
    //printMatrix(XtX, K, K);

    //Inverse of XtX
    double** XtX_Inverse = inverseMatrix(XtX, K);
    //printf("Inverse of X^t * X\n");
    //printMatrix(XtX_Inverse, K, K);

    //Multiplying inverse matrix by X^T (step 4)
    double** psuedo = multiplyMatrix(XtX_Inverse, X_Trans, K, K, K, N);
    //printf("Inverse times transpose of X\n");
    //printMatrix(psuedo, K, N);

    //Multiply psuedo by Y
    double** W = multiplyMatrix(psuedo, Y, K, N, N, 1);
    printf("W\n");
    printMatrix(W, K, 1);

    FILE* mp = fopen(argv[2], "r");
    int M = 0;
    fscanf(mp, "%d\n", &M);

    //Initiates X prime matrix
    double **X_prime = (double**) malloc(M * sizeof(double*));
    for (int i = 0; i < M; i++){
        X_prime[i] = (double*) malloc(K * sizeof(double));
    }
    //Sets all values of x prime to o.o, except for first column that corresponds to first 
    for (int i = 0; i < M; i++){
        X_prime[i][0] = 1.0;
        for (int j = 1; j < K; j++){
            X_prime[i][j] = 0.0;
        }
    }

    //Scans text document and sets attributs in X Prime
    for (int i = 0; i < M; i++){
        for (int j = 1; j < K; j++){
            fscanf(mp,"%lf,", &X_prime[i][j]);
        }
        fscanf(mp,"\n");
    }
    fclose(mp);
    //printf("X Prime\n");
    //printMatrix(X_prime, M, K);

    //Creats matrix for the price of the houses
    double** Y_prime = multiplyMatrix(X_prime, W, M, K, K, 1);
    //printf("Y_Prime\n");
    printMatrix(Y_prime, M, 1);

    //Free arrays
    freeArray(X, N);
    freeArray(Y, N);
    freeArray(X_Trans, K);
    freeArray(XtX, K);
    freeArray(XtX_Inverse, K);
    freeArray(psuedo, K);
    freeArray(W, K);
    freeArray(X_prime, M);	
    freeArray(Y_prime, M);
	return 0;
}

double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2)
{
    double** result=malloc(r1*sizeof(double*)); 
    for (int i = 0; i < r1; i++){
        result[i] = malloc(c2 * sizeof(double));
    }

    for (int i = 0; i < r1; i++){
        for (int j = 0; j < c2; j++){
            result[i][j] = 0.0;
        }
    }
    
    for (int i = 0; i < r1; i++){
        for (int j = 0; j < c2 ; j++){
            for (int k = 0; k < c1; k++){
                result[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
    
    return result;
}


double** transposeMatrix(double** mat, int row, int col)
{
  
	double** matTran=malloc(col*sizeof(double*)); 
    for (int i = 0; i < col; i++){
        matTran[i] = malloc(row * sizeof(double));
    }

    for (int i = 0; i < col; i++){
        for (int j = 0; j < row; j++){
            matTran[i][j] = 0.0;
        }
    }
    
    for (int i = 0; i < col; i++){
        for (int j = 0; j < row; j++){
            matTran[i][j] = mat[j][i];
        }
    }
    
    return matTran;        
}


double** inverseMatrix(double **matA, int dimension)
{
    //Initialize the identity matrix
    double** matI = malloc(dimension*sizeof(double*)); 
    for (int i = 0; i < dimension; i++){
        matI[i] = malloc(dimension * sizeof(double));
    }
    for (int i = 0; i < dimension; i++){
        for (int j = 0; j < dimension; j++){
            if (i == j){
                matI[i][j] = 1.0;
            } else {
                matI[i][j] = 0.0;  
            } 
        }
    }

    for (int p = 0; p < dimension; p++){
        double f = matA[p][p];
        for (int j = 0; j < dimension; j++){
            matA[p][j] = (matA[p][j] / f);
        }
        for (int j = 0; j < dimension; j++){
            matI[p][j] = (matI[p][j] / f);
        }
        for (int i = p + 1; i < dimension; i++){
            f = matA[i][p];
            for (int j = 0; j < dimension; j++){
                matA[i][j] = matA[i][j] - (f * matA[p][j]);
            }
            for (int j = 0; j < dimension; j++){
                matI[i][j] = matI[i][j] - (f * matI[p][j]);
            }
        }
    }
    for (int p = (dimension - 1); p > -1; p--){
        for (int i = (p - 1); i > -1; i--){
            double f = matA[i][p];
            for (int j = 0; j < dimension; j++){
                matA[i][j] = matA[i][j] - (f * matA[p][j]);
            }
            for (int j = 0; j < dimension; j++){
                matI[i][j] = matI[i][j] - (f * matI[p][j]);
            }
        }
    }
	return matI;
}

void printMatrix(double** matrix, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%0.0lf ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void freeArray(double **a, int m) {
    int i;
    for (i = 0; i < m; ++i) {
        free(a[i]);
    }
    free(a);
}
