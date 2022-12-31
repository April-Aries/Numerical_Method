#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h>

/* functions */
void free_matrix( double **matrix, int32_t row, int32_t col);
double** matrix_transpose( double **matrix, int32_t row, int32_t col );
double **matrix_mul( double **A, int32_t rowA, int32_t colA, double **B, int32_t rowB, int32_t colB );
double *gaussian( double **A, int32_t rowA, int32_t colA, double *b, int32_t rowb );
void print_matrix( double **matrix, int32_t row, int32_t col );
void print_vector( double *vector, int32_t row, int32_t col );

void print_vector( double *vector, int32_t row, int32_t col )
{
    for( int32_t i = 0; i < col; i++ )
    {
	if( vector[i] < 0 )
	{
	    printf("%.5lf ", vector[i]);
	}
	else
	{
	    printf(" %.5lf ", vector[i]);
	}
    }

    return;
}

void print_matrix( double **matrix, int32_t row, int32_t col )
{
    for(int32_t i = 0; i < row; i++ )
    {
	for( int32_t j = 0; j < col; j++ )
	{
	    if( matrix[i][j] < 0 )
	    {
		printf("%.4lf ", matrix[i][j]);
	    }
	    else
	    {
		printf(" %.4lf ", matrix[i][j]);
	    }
	}
	printf("\n");
    }

    return;
}

void free_matrix( double **matrix, int32_t row, int32_t col)
{
    for(int32_t i = 0; i < row; i++)
    {
	free(matrix[i]);
    }
    free(matrix);
    return;
}

double** matrix_transpose( double **matrix, int32_t row, int32_t col )
{
    double **result = calloc( col, sizeof(double));
    for(int32_t i = 0; i < col; i++)
    {
	result[i] = calloc( row, sizeof(double));
    }

    for(int32_t i = 0; i < row; i++)
    {
	for(int32_t j = 0; j < col; j++)
	{
	    result[j][i] = matrix[i][j];
	}
    }

    return result;
}

double **matrix_mul( double **A, int32_t rowA, int32_t colA, double **B, int32_t rowB, int32_t colB )
{
    if( colA != rowB )
    {
	printf("Matrix cannot be multiplied\n");
	return NULL;
    }

    double **C = calloc( rowA, sizeof(double));
    for(int32_t i = 0; i < rowA; i++)
    {
	C[i] = calloc( colB, sizeof(double));
    }

    for(int32_t i = 0; i < rowA; i++)
    {
	for(int32_t j = 0; j < colB; j++)
	{
	    double sum = 0.0;
	    for(int32_t k = 0; k < colA; k++ )
	    {
		sum += A[i][k] * B[k][j];
	    }
	    C[i][j] = sum;
	}
    }

    return C;
}

double *matrix_vector_mul( double **matrix, int32_t rowA, int32_t colA, double *vector, int32_t size )
{
    if( colA != size )	return NULL;

    double *ans = calloc( rowA , sizeof(double));

    for(int32_t i = 0; i < rowA; i++ )
    {
	double sum = 0.0;
	for(int32_t j = 0; j < colA; j++ )
	{
	    sum += matrix[i][j] * vector[j];
	}
	ans[i] = sum;
    }
    return ans;
}

double *gaussian( double **A, int32_t rowA, int32_t colA, double *b, int32_t rowb )
{
    /* format checking */
    if( rowA != colA && rowA != rowb )
    {
        printf("Format unmatched!\n");
        return NULL;
    }

    /* declare answer array */
    double *ans = calloc( colA, sizeof(double));

    /* gaussian */
    for( int32_t i = 0; i < colA; i++ )
    {
        /* Partial Pivoting: Find Max & exchange 2 rows */
        int32_t max = i;
        for(int32_t j = i+1; j < rowA; j++ )
        {
            if( fabs( A[j][i] ) > fabs( A[max][i] ) )
            {
                max = j;
            }
        }
        for(int32_t k = 0; k < colA; k++)
        {
            double tmp = 0.0;
            tmp = A[i][k];
            A[i][k] = A[max][k];
            A[max][k] = tmp;
        }
        double tmp = 0.0;
        tmp = b[i];
        b[i] = b[max];
        b[max] = tmp;

        /* elimination */
        for(int32_t j = i+1; j < rowA; j++)
        {

            if( A[i][i] == 0 || A[j][i] == 0 )
            {
                continue;
            }
            double diff = 0.0;
            diff = A[j][i] / A[i][i];
            for(int32_t k = 0; k < colA; k++)
            {
                A[j][k] = A[j][k] - diff * A[i][k];
            }
            b[j] = b[j] - diff * b[i];

        }
    }

    /* replace */
    for( int32_t i = rowA-1; i >= 0; i-- )
    {
        for(int32_t j = rowA-1; j > i; j-- )
        {
            b[i] -= A[i][j] * ans[j];
        }
        ans[i] = b[i] / A[i][i];
    }

    /* free */
    // free( ans ); // leave for outside function

    /* return */
    return ans;

}
