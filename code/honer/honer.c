//Horner's Method

#include<stdio.h>
#include<stdint.h>

#define VALUE 1.0001 // initial value

int main()
{
    double x = VALUE;

    double result = 0.0;

    result = 1 + x; 

    for(int32_t i = 0; i < 49; i++) // do n-1 times
    {
	result = result * x + 1;
    }

    printf("Result: %lf\n", result);

    return 0;
}

//Ouestuon:
//P(x) = 1 + x + ... + x^50
//By Honer's method, find P(1.0001)
//
//P(x) = 1 + x( 1 + x + x^2 + ... + x^49)
//P(X) = 1 + x( 1 + x( 1 + x + x^2 + ... + x^48))
//P(x) = 1 + x( 1 + x( 1 + x( ...x(1 + x))))
