//Fixed Point Iteration ( FPI )

#include<stdio.h>
#include<stdint.h>
#include<math.h>

#define INITIAL 10 

double f( double x );

int main()
{
    double x = INITIAL;
    double result = 0.0;

    result = f(x);

    while( fabs( result - x ) > 0.000001 )
    {
	x = result;	
	result = f( x );
    }

    printf("Result: %lf\n", x);

    return 0;
}

double f( double x )
{
    return powf(x,3);
}

