//Fixed Point Iteration ( FPI )
//Newton's Method

#include<stdio.h>
#include<stdint.h>
#include<math.h>

#define INITIAL 1 

double f1( double x );
double f1_( double x );

int main()
{
    double x = INITIAL;
    double result = 0.0;

    result = x - f1(x)/f1_(x);

    while( fabs( result - x ) > 0.000001 )
    {
	x = result;
	result = x - f1(x)/f1_(x);
    }

    printf("Result: %lf\n", x);

    return 0;
}

double f1( double x )
{
    return powf(x, 5) + x - 1;
}

double f1_( double x )
{
    return 5*powf(x, 4) + 1;
}

