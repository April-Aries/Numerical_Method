#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include"matrix.h"

double side( double x, double y, double x0, double y0 );
void formR( double *R, double *x, double *y, double *r, double *ans );
void formDr( double** Dr, double* x, double *y, double* ans );

int main()
{
    /* Given variables */
    double *x = calloc( 4, sizeof(double));
    x[0] = -1;	    x[1] = 1;	    x[2] = 1;	    x[3] = 0;
    double *y = calloc( 4, sizeof(double));
    y[0] = 0;	    y[1] = 0.5;	    y[2] = -0.5;    y[3] = 1;
    double *r = calloc( 4, sizeof(double));
    r[0] = 1;	    r[1] = 0.5;	    r[2] = 0.5;	    r[3] = 0.5;

    /* initial guess */
    double* ans = calloc( 3, sizeof(double) ); /* x, y, K */
    ans[0] = 0.1;    ans[1] = 0.1;    ans[2] = 0.1;

    /* Using variables -- declaration */
    double *R = calloc( 4, sizeof(double));
    double **Dr = calloc( 4, sizeof(double));
    for( int32_t i = 0; i < 4; i++ )
    {
	Dr[i] = calloc( 3, sizeof(double));
    }
    double **DrT = calloc( 3, sizeof(double));
    for(int32_t i = 0; i < 3; i++ )
    {
	DrT[i] = calloc( 4, sizeof(double));
    }
    double **DrTDr = calloc( 3, sizeof(double));
    for( int32_t i = 0; i < 3; i++ )
    {
	DrTDr[i] = calloc( 3, sizeof(double));
    }
    double *DrTR = calloc( 3, sizeof(double));
    double *v = calloc( 3, sizeof(double));
    double diff = 1.0;

    while( diff > 0.000001 )
    {
	/* R matrix ( vector ) */
	formR( R, x, y, r, ans );

	/* Dr Jacobian matrix */
	formDr( Dr, x, y, ans );

	/* Dr^T matrix */
	DrT = matrix_transpose( Dr, 4, 3 );

	/* Dr^T * Dr matrix */
	DrTDr = matrix_mul( DrT, 3, 4, Dr, 4, 3 );

	/* Dr^T * R */
	DrTR = matrix_vector_mul( DrT, 3, 4, R, 4 );
	for(int32_t i = 0; i < 3; i++ )
	{
	    DrTR[i] *= -1;
	}

	v = gaussian( DrTDr, 3, 3, DrTR, 3 );

	diff = fabs( v[0] + v[1] + v[2] );

	for( int32_t i = 0; i < 3; i++ )
	{
	    ans[i] += v[i];
	}

	//sleep(1);
    }

    /* print answer */
    printf("(x,y) = ( %.4lf, %.4lf), K = %.4lf\n", ans[0], ans[1], ans[2]);

    free( x );
    free( y );
    free( r );
    free( ans );
    free( R );
    free_matrix( Dr, 4, 3 );
    free_matrix( DrT, 3, 4 );
    free_matrix( DrTDr, 3, 3);
    free( DrTR );
    return 0;
}

void formR( double *R, double *x, double *y, double *r, double *ans )
{
    double S1 = side( ans[0], ans[1], x[0], y[0] );
    double S2 = side( ans[0], ans[1], x[1], y[1] );
    double S3 = side( ans[0], ans[1], x[2], y[2] );
    double S4 = side( ans[0], ans[1], x[3], y[3] );

    R[0] = S1 - r[0] - ans[2];
    R[1] = S2 - r[1] - ans[2];
    R[2] = S3 - r[2] - ans[2];
    R[3] = S4 - r[3] - ans[2];

    return;
}

void formDr( double** Dr, double* x, double *y, double* ans )
{
    double S1 = side( ans[0], ans[1], x[0], y[0] );
    double S2 = side( ans[0], ans[1], x[1], y[1] );
    double S3 = side( ans[0], ans[1], x[2], y[2] );
    double S4 = side( ans[0], ans[1], x[3], y[3] );

    Dr[0][0] = ( ans[0] - x[0] ) / S1;	    Dr[0][1] = ( ans[1] - y[0] ) / S1;	    Dr[0][2] = -1;
    Dr[1][0] = ( ans[0] - x[1] ) / S2;	    Dr[1][1] = ( ans[1] - y[1] ) / S2;	    Dr[1][2] = -1;
    Dr[2][0] = ( ans[0] - x[2] ) / S3;	    Dr[2][1] = ( ans[1] - y[2] ) / S3;	    Dr[2][2] = -1;
    Dr[3][0] = ( ans[0] - x[3] ) / S4;	    Dr[3][1] = ( ans[1] - y[3] ) / S4;	    Dr[3][2] = -1;

    return;
}

double side( double x, double y, double x0, double y0 )
{
    double S = 0.0;
    S = sqrt( pow( ( x - x0 ), 2 ) + pow( ( y - y0 ), 2 ) );

    return S;
} 
