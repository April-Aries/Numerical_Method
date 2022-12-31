#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h>

double slope( double x );

int main()
{
    double x = 3.0;
    double ita = 0.001;
    double m = slope( x );

    while(  fabs( m ) > 0.000001 )
    {
	x = x - ita * m;
	m = slope( x );
    }

    printf("x = %lf\n", x);

    return 0;
}

double slope( double x )
{
    return 4 * pow( x, 3 ) - 6 * pow( x, 2 );
}
