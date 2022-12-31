#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h>

/* functions */
void free_matrix( double **matrix, int32_t row, int32_t col);
double** matrix_transpose( double **matrix, int32_t row, int32_t col );
double **matrix_mul( double **A, int32_t rowA, int32_t colA, double **B, int32_t rowB, int32_t colB );
double *gaussian( double **A, int32_t rowA, int32_t colA, double *b, int32_t rowb );

int main()
{
    /* A */
    double **A = calloc( 13, sizeof(double));
    for(int32_t i = 0; i < 13; i++)
    {
	A[i] = calloc( 4, sizeof(double));
    }
    for(int32_t i = 0; i < 13; i++)
    {
	A[i][0] = 1;
	A[i][1] = ( 0.25 * i );
	A[i][2] = ( 0.25 * i ) * ( 0.25 * i );
	A[i][3] = ( 0.25 * i ) * ( 0.25 * i ) * ( 0.25 * i );
    }
    /* x */
    double **x = calloc( 4, sizeof(double));
    x[0] = calloc(1, sizeof(double));
    /* y */
    double *y = calloc( 13, sizeof(double));
    y[0] = 6.3806;  y[1] = 7.1338;  y[2] = 9.1662;  y[3] = 11.5545;	y[4] = 15.6414; y[5] = 22.7371;
    y[6] = 32.0696; y[7] = 47.0756; y[8] = 73.1596; y[9] = 111.4684;	y[10] = 175.9895;   y[11] = 278.5550;	y[12] = 446.4441;

    /* ( A^T * A ) * x = A^T * b */
    /* Transpose: A^T */
    double **AT = calloc( 4, sizeof(double));
    for(int32_t i = 0; i < 4; i++)
    {
	AT[i] = calloc( 13, sizeof(double));
    }
    AT = matrix_transpose( A, 13, 4 );

    /* A^T * A */
    double **ATA = calloc( 4, sizeof(double));
    for(int32_t i = 0; i < 4; i++)
    {
	ATA[i] = calloc( 4, sizeof(double));
    }
    ATA = matrix_mul( AT, 4, 13, A, 13, 4);

    /* A^T * b */
    double **ATb = calloc( 4, sizeof(double));
    for(int32_t i = 0; i < 13; i++)
    {
	ATb[i] = calloc( 1, sizeof(double));
    }
    for(int32_t i = 0; i < 4; i++)
    {
	for(int32_t j = 0; j < 1; j++)
	{
	    double sum = 0.0;
	    for(int32_t k = 0; k < 13; k++ )
	    {
		sum += AT[i][k] * y[k];
	    }
	    ATb[i][j] = sum;
	}
    }

    double *b = calloc(4, sizeof(double));
    for(int32_t i = 0; i < 4; i++)
    {
	b[i] = ATb[i][0];
    }

    /* Guassian: ( A^T * A ) * x = ( A^T * b ) */
    double *ans = calloc( 4, sizeof(double));
    ans = gaussian( ATA, 4, 4, b, 4 );
    //ans = partial_pivot( ATA, 4, 4, b, 4 ); 

    printf("Result --> \n");
    printf("\ta = %lf\n", ans[0]);
    printf("\tb = %lf\n", ans[1]);
    printf("\tc = %lf\n", ans[2]);
    printf("\td = %lf\n", ans[3]);
    /* free */
    free_matrix( A, 13, 4 );
    free_matrix( x, 4, 1 );
    free( y );
    free_matrix( AT, 4, 13);
    free_matrix( ATA, 3, 4);
    //free_matrix( ATb, 4, 1);
    free( b );

    return 0;
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
