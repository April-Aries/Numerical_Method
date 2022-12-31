#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#define TERM 4

double lagrange( double *x, double *y, double X);

int main()
{
    double *x = calloc(TERM, sizeof(double));
    double *y = calloc(TERM, sizeof(double));
    //double *x = calloc(TERM, sizeof(double));

    //Given Variables
    x[0] = 1.00;    x[1] = 1.05;    x[2] = 1.10;    x[3] = 1.15;
    y[0] = 0.1924;  y[1] = 0.2414;  y[2] = 0.2933;  y[3] = 0.3492;
    double X = 1.09;

    double ans = lagrange(x, y, X);

    printf("Result: %.4lf\n", ans);

    free(x);
    free(y);

    return 0;
}

double lagrange( double *x, double *y, double X)
{
    double Y = 0.0;

    for(int32_t i = 0; i < TERM; i++)
    {
	//Lk
	double numerator = 1.0;
	double denominator = 1.0;
	for( int32_t j = 0; j < TERM; j++)
	{
	    if( i == j )    continue;

	    numerator *= ( X - x[j] );
	    denominator *= ( x[i] - x[j] );
	}

	//Y
	Y += y[i] * ( numerator / denominator );
    }

    return Y;
    
}
