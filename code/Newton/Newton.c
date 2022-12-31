#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#define TERM 5

/* functions */
void Newton_Divide_Difference( double **coef, double *x, double *y, int32_t term );
double honer_newton( double **coef, double *x, double var_x );

int main()
{

    double *x = calloc(TERM, sizeof(double));
    x[0] = 0.6;	x[1] = 0.7; x[2] = 0.8;	x[3] = 0.9; x[4] = 1.0;
    double *y = calloc(TERM, sizeof(double));
    y[0] = 1.433329;	y[1] = 1.632316;    y[2] = 1.896481;	y[3] = 2.247908;	y[4] = 2.718282;

    double **coef = calloc( TERM, sizeof(double));
    for(int32_t i = 0; i < TERM; i++)
    {
	coef[i] = calloc( TERM, sizeof(double) );
    }

    /* forming coef 2-D array */
    Newton_Divide_Difference( coef, x, y, TERM );
    
    /* calculate result */
    double var_x = 0.82; /* given */
    double ans = 0.0;

    /* First testcase */
    ans = honer_newton( coef, x, var_x );
    printf("P(%.2lf) = %lf\n", var_x, ans );

    /* Second testcase */
    var_x = 0.98;
    ans = honer_newton( coef, x, var_x );
    printf("P(%.2lf) = %lf\n", var_x, ans );

    /* free */
    free(x);
    free(y);
    for(int32_t i = 0; i < TERM; i++)
    {
	free( coef[i] );
    }
    free(coef);

    return 0;
}

void Newton_Divide_Difference( double **coef, double *x, double *y, int32_t term )
{
    for(int32_t i = 0; i < term; i++)
    {
	for(int32_t j = 0; j < term - i; j++)
	{
	    if(i == 0)
	    {
		coef[j][i] = y[j];
	    }
	    else
	    {
		coef[j][i] = ( coef[j+1][i-1] - coef[j][i-1] ) / ( x[j+i] - x[j] );
	    }
	}
    }

    return;
}

double honer_newton( double **coef, double *x, double var_x )
{
    double ans = 0.0;
    for(int32_t i = TERM - 1; i > 0; i--)
    {
	ans += coef[0][i];
	ans *= ( var_x - x[i-1] );
    }
    ans += coef[0][0];

    return ans;
}
