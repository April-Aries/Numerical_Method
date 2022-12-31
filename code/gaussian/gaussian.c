// Guassian Elimination

#include<stdio.h>
#include<stdint.h>

#define TERM 3

//function I'll use

int main()
{
 
    double A[TERM][TERM+1] = {-8, 2, 3, 320,
			      4, -7, 1, 480,
			      4, 5, -14, 480};
    
    double ans[TERM];
    for(int32_t i = 0; i < TERM; i++)
    {
	ans[i] = 0;
    }

    double L[TERM][TERM]   = {1, 0, 0,
			      0, 1, 0,
			      0, 0, 1};

    double U[TERM][TERM]   = {1, 0, 0,
			      0, 1, 0,
			      0, 0, 1};

    //elemination
    for(int32_t a = 0; a < TERM; a++) 
    {
	for(int32_t i = a+1; i < TERM; i++)
	{
		if(A[i][a] == 0)
		{
		    continue;
		}

		double diff = 0;
		diff = A[i][a] / A[a][a];

		//Guassian
		for(int32_t k = 0; k < TERM; k++)
		{
		    A[i][k] = A[i][k] - diff * A[a][k];
		}

		//L matrix
		L[i][a] = diff;
	}
    }

    //U matrix
    for(int32_t i = 0; i < TERM; i++)
    {
	for(int32_t j = 0; j < TERM; j++)
	{
	    U[i][j] = A[i][j];
	}
    }

	//test after elemination
	printf("A = \n");
	for(int32_t i = 0; i < TERM; i++)
	{
	    for(int32_t j = 0; j < TERM+1; j++)
	    {
		printf("%.2lf ", A[i][j]);
	    }

	    printf("\n");
	}
	printf("\n");
	printf("L = \n");
	for(int32_t i = 0; i < TERM; i++)
	{
	    for(int32_t j = 0; j < TERM; j++)
	    {
		printf("%.2lf ", L[i][j]);
	    }

	    printf("\n");
	}
	printf("\n");
	printf("U = \n");
	for(int32_t i = 0; i < TERM; i++)
	{
	    for(int32_t j = 0; j < TERM; j++)
	    {
		printf("%.2lf ", U[i][j]);
	    }

	    printf("\n");
	}
	printf("\n");

    //replace
    double c[TERM];
    for(int32_t i = 0; i < TERM; i++)
    {
	c[i] = 0;
    }

    //c = Lx
    for(int32_t i = 0; i < TERM; i++)
    {
	ans[i] = A[i][TERM];
	for(int32_t j = 0; j < i; j++)
	{
	    ans[i] -= L[i][j]*ans[j];
	}
	ans[i] /= L[i][i];
    }

    //Ux = c
    for(int32_t i = TERM; i >= 0; i--)
    {
	for(int32_t j = TERM; j > i; j--)
	{
	    ans[i] -= U[i][j]*ans[j];
	}
	ans[i] /= U[i][i];
    }


    /*
    for(int32_t i = TERM-1; i >= 0; i--)  
    {
	for(int32_t k = TERM-1; k >= 0 ; k--)
	{
	    ans[i] += ans[k] * A[i][k]; 
	}
	ans[i] = ans[i] / A[i][TERM];
    }
    */
    printf("Ans ( x, y, z, w ) = ");
    for(int32_t i = 0; i < TERM; i++)
    {
	printf("%.2lf ", ans[i]);
    }
    printf("\n");

    return 0;
}

/*
void print_matrix( double *matrix[TERM][] )
{
    for(int32_t i = 0; i < TERM; i++)
    {
	for(int32_t j = 0; j < TERM; j++)
	{
	    printf("%.2lf ", *matrix[i][j]);
	}

	printf("\n");
    }
}
*/

//2x +  y           = 1
//      y + 2z      = 1
//2x + 4y + 5z +  w = 2
//8x + 5y      + 3w = 0
