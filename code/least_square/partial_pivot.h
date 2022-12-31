#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h>

/* functions */
void print_matrix( double **A, int32_t rowA, int32_t colA );
void print_vector( double *b, int32_t size );
double *gaussian( double **A, int32_t rowA, int32_t colA, double *b, int32_t rowb );

void print_matrix( double **A, int32_t rowA, int32_t colA )
{
    for(int32_t i = 0; i < rowA; i++ )
    {
	for(int32_t j = 0; j < colA; j++ )
	{
	    printf("%lf ", A[i][j]);
	}
	printf("\n");
    }

    return;
}

void print_vector( double *b, int32_t size )
{
    for(int32_t i = 0; i < size; i++ )
    {
	printf("%lf ", b[i]);
    }
    printf("\n");

    return;
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
