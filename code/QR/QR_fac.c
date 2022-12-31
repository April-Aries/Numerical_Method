#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h>

double vecmul( double *A, double *B, int32_t size );
void matrix_print( double **matrix, int32_t row, int32_t col );
void free_matrix( double **matrix, int32_t row );

int main()
{
    /* A matrix */
    int32_t rowA = 5;	int32_t colA = 3;
    double **A = calloc( rowA, sizeof(double*) );
    for( int32_t i = 0; i < rowA; i++ )
    {
	A[i] = calloc( colA, sizeof(double));
    }
    A[0][0] =  3;    A[0][1] = -1;  A[0][2] = 2;
    A[1][0] =  4;    A[1][1] =  1;  A[1][2] = 0;
    A[2][0] = -3;    A[2][1] =  2;  A[2][2] = 1;
    A[3][0] =  1;    A[3][1] =  1;  A[3][2] = 5;
    A[4][0] = -2;    A[4][1] =  0;  A[4][2] = 3;

    /* Y matrix */
    int32_t rowY = rowA;    int32_t colY = colA;
    double **Y = calloc( rowY, sizeof(double*) );
    for( int32_t i = 0; i < rowY; i++ )
    {
	Y[i] = calloc( colY, sizeof(double));
    }

    /* length Y declaration */
    double *length = calloc( colY, sizeof(double));

    /* Q matrix */
    int32_t rowQ = rowY;    int32_t colQ = colY;
    double **Q = calloc( rowQ, sizeof(double*) );
    for( int32_t i = 0; i < rowQ; i++ )
    {
	Q[i] = calloc( colQ, sizeof(double));
    }

    /* R matrix */
    int32_t rowR = colA;    int32_t colR = colA;
    double **R = calloc( rowR, sizeof(double*) );
    for( int32_t i = 0; i < rowR; i++ )
    {
	R[i] = calloc( colR, sizeof(double));
    }

    /* Y1, R1, length1 */
    for( int32_t i = 0; i < rowY; i++ )
    {
	Y[i][0] = A[i][0];
	length[0] += Y[i][0] * Y[i][0];
    }
    length[0] = sqrt( length[0] );
    R[0][0] = length[0];

    /* Q1 */
    for( int32_t i = 0; i < rowQ; i++ )
    {
	Q[i][0] = Y[i][0] / length[0];
    }

    /* Yj, Qj, Rj, length j */
    for( int32_t i = 1; i < colY; i++ )
    {
	double *tmp = calloc( rowY, sizeof( double ));
	double *Aj = calloc( rowA, sizeof(double) );
	for(int32_t k = 0; k < rowA; k++)
	{
	    Aj[k] = A[k][i];
	}

	/* form Y */
	for( int32_t j = 0; j < i; j++ )
	{
	    /* qk^T * Aj */
	    double *qkT = calloc( rowQ, sizeof(double) );
	    for(int32_t k = 0; k < rowQ; k++)
	    {
		qkT[k] = Q[k][j];
	    }
	    double qkTAj = vecmul( qkT, Aj, rowA );

	    /* form R */
	    R[j][i] = qkTAj;

	    /* qk * ( qkT * Aj )*/
	    for( int32_t k = 0; k < rowQ; k++ )
	    {
		tmp[k] += qkTAj * Q[k][j];
	    }

	    //free( qkT );
	    //free( Aj );
	}
	for( int32_t j = 0; j < rowY; j++ )
	{
	    Y[j][i] = A[j][i] - tmp[j];
	}

	/* form length */
	for( int32_t j = 0; j < rowY; j++ )
	{
	    length[i] += Y[j][i] * Y[j][i];
	}
	length[i] = sqrt( length[i] );
	R[i][i] = length[i];

	/* form Q */
	for(int32_t j = 0; j < rowQ; j++ )
	{
	    Q[j][i] = Y[j][i] / length[i];
	}
	
	free( tmp );
	
    }

    printf("Q:\n");
    matrix_print( Q, rowQ, colQ );
    printf("\nR:\n");
    matrix_print( R, rowR, colR );

    free( length );
    free_matrix( A, rowA );
    free_matrix( Y, rowY );
    free_matrix( Q, rowQ );
    free_matrix( R, rowR );

    return 0;
}

void free_matrix( double **matrix, int32_t row )
{
    for(int32_t i = 0; i < row; i++)
    {
	free( matrix[i] );
    }
    free( matrix );
}

double vecmul( double *A, double *B, int32_t size )
{
    double sum = 0.0;
    for( int32_t i = 0; i < size; i++ )
    {
	sum += A[i] * B[i];
    }
    return sum;
}

void matrix_print( double **matrix, int32_t row, int32_t col )
{
    for(int32_t i = 0; i < row; i++ )
    {
	for(int32_t j = 0; j < col; j++ )
	{
	    if( matrix[i][j] < 0 )  printf("%.4lf\t", matrix[i][j]);
	    else		    printf(" %.4lf\t", matrix[i][j]);
	}
	printf("\n");
    }
    return;
}
