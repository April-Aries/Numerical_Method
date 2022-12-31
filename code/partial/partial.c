// Partial Pivot 

#include<stdio.h>
#include<stdint.h>

#define TERM 4 

//function I'll use

int main()
{
 
    double A[TERM][TERM]  = {{1.19, 2.11, -100, 1}, {14.2, -0.122, 12.2, -1}, {0, 100, -99.9, 1}, {15.3, 0.11, -13.1, -1}};

    double A_[TERM][TERM] = {{1.19, 2.11, -100, 1}, {14.2, -0.122, 12.2, -1}, {0, 100, -99.9, 1}, {15.3, 0.11, -13.1, -1}};

    double L[TERM][TERM]  = {0};

    double P[TERM][TERM]  = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

    //elemination
    for(int32_t a = 0; a < TERM; a++) 
    {
		//Partial Pivot
		int32_t max = a;
		for(int32_t k = a; k < TERM; k++)	
		{
		    if(A[k][a] > A[max][a])
		    {
			max = k;
		    }
		}

		for(int32_t k = 0; k < TERM; k++)	
		{
			double tmp = 0.0;
			tmp = P[a][k]; 
			P[a][k] = P[max][k];
			P[max][k] = tmp;
			
			double tmp_ = 0.0;
			tmp_ = A[a][k]; 
			A[a][k] = A[max][k];
			A[max][k] = tmp_;

			double tmp__ = 0.0;
			tmp__ = L[a][k]; 
			L[a][k] = L[max][k];
			L[max][k] = tmp__;

		}

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
	double U[TERM][TERM]  = {{1, 0, 0, 0}, { 0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    for(int32_t i = 0; i < TERM; i++)
    {
	for(int32_t j = 0; j < TERM; j++)
	{
	    U[i][j] = A[i][j];
	}
    }

	L[0][0] = 1;
	L[1][1] = 1;
	L[2][2] = 1;
	L[3][3] = 1;

	//test after elemination
	printf("P = \n");
	for(int32_t i = 0; i < TERM; i++)
	{
	    for(int32_t j = 0; j < TERM; j++)
	    {
		printf("%.2lf ", P[i][j]);
	    }

	    printf("\n");
	}
	printf("\n");
	printf("A = \n");
	for(int32_t i = 0; i < TERM; i++)
	{
	    for(int32_t j = 0; j < TERM; j++)
	    {
		printf("%.2lf ", A_[i][j]);
	    }

	    printf("\n");
	}
	printf("\n");
	printf("L = \n");
	for(int32_t i = 0; i < TERM; i++)
	{
	    for(int32_t j = 0; j < TERM; j++)
	    {
		printf("%.4lf ", L[i][j]);
	    }

	    printf("\n");
	}
	printf("\n");
	printf("U = \n");
	for(int32_t i = 0; i < TERM; i++)
	{
	    for(int32_t j = 0; j < TERM; j++)
	    {
		printf("%.4lf ", U[i][j]);
	    }

	    printf("\n");
	}
	printf("\n");


	//solve x
	double ans[TERM] = {0};

	double c[TERM];
    for(int32_t i = 0; i < TERM; i++)
    {
	    c[i] = 0;
    }

    ///////////////////////////////////// c = Lx /////////////////////////////////////
    for(int32_t i = 0; i < TERM; i++)
    {
        ans[i] = A[i][TERM];
        for(int32_t j = 0; j < i; j++)
        {
            ans[i] -= L[i][j]*ans[j];
        }
        ans[i] /= L[i][i];
    }

    ///////////////////////////////////// Ux = c /////////////////////////////////////
    for(int32_t i = TERM-1; i >= 0; i--)
    {
        for(int32_t j = TERM-1; j > i; j--)
        {
            ans[i] -= U[i][j]*ans[j];
        }
        ans[i] /= U[i][i];
    }

	for(int32_t i = 0; i < TERM; i++)
	{
		printf("X%d = %.4lf\t", i+1, ans[i] );
	}
	printf("\n");



    return 0;
}

