//Bisection

#include<stdio.h>
#include<stdint.h>
#include<math.h>

#define	LOW 1
#define HIGH 100000000

double f(double x);

int main()
{
    
    double low = LOW;
    double high = HIGH;
    double mid = 0.0;
    double mid_result = 0.0;
    double high_result = 0.0;
    double low_result = 0.0;
    double diff = 1.0;

    while( diff > powf(10, -6) )
    {

	mid = ( high + low ) / 2;

	mid_result = f(mid);
	high_result = f(high);
	low_result = f(low);


	if(mid_result * high_result < 0)
	{
	    low = mid;
	    diff = fabs( high_result - mid_result );
	}

	if(mid_result * low_result < 0)
	{
	    high = mid;
	    diff = fabs( low_result - mid_result );
	}


    }

    printf("x = %lf\n", mid);
    return 0;

}

double f( double x )
{
    return powf(x, 1.4) - sqrt(x) + powf(x, -1) - 100; // note that "1/3" will make it as 0 due to the computer consider it as an integer
}

//Question:
//
//x - x^(1/3) - 2 = 0
//3 < x < 4
//
//find x?
