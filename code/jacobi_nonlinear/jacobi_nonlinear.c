// Jacobian ===> nonlinear

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>

#define TERM 3

//functions
double* guassian( double **A_, int32_t row_A_, int32_t col_A_, double *b, int32_t row_b );
double f1(double u, double v, double w);
double f2(double u, double v, double w);
double f3(double u, double v, double w);
double df1dx(double x);
double df1dy(double y);
double df1dr(double r);
double df2dx(double x);
double df2dy(double y);
double df2dr(double r);
double df3dx(double x);
double df3dy(double y);
double df3dr(double r);

int main()
{
    //////////////// variables, vectors, matrices prototype ////////////////

    // Variables and Vectors I need
    double initial[TERM] = {0};
        for(int32_t i = 0; i < TERM; i++)
        {
            initial[i] = i+1;
        }

    double DF[TERM][TERM] = {0};
    double DF_[TERM][TERM+1] = {0};

    double Xk[TERM] = {0};
        //init -> assign
        for(int32_t i = 0; i < TERM; i++)   Xk[i] = initial[i];

    double Xk_[TERM] = {0};

    double Fx[TERM] = {0};

    int32_t flag = 1;
    while(flag)
    {
        // form Jacobian
        DF[0][0] = df1dx(Xk[0]);    DF[0][1] = df1dy(Xk[1]);		DF[0][2] = df1dr(Xk[2]);
		DF[1][0] = df2dx(Xk[0]);	DF[1][1] = df2dy(Xk[1]);		DF[1][2] = df2dr(Xk[2]);
		DF[2][0] = df3dx(Xk[0]);	DF[2][1] = df3dy(Xk[1]);		DF[2][2] = df3dr(Xk[2]);

        //backup DF_
        for(int32_t i = 0; i < TERM; i++)
        {
            for(int32_t j = 0; j < TERM; j++)
            {
                DF_[i][j] = DF[i][j];
            }
        }

        // form F(Xk)
		Fx[0] = -1 * f1(Xk[0], Xk[1], Xk[2]);
		Fx[1] = -1 * f2(Xk[0], Xk[1], Xk[2]);
		Fx[2] = -1 * f3(Xk[0], Xk[1], Xk[2]);
        for(int32_t i = 0; i < TERM; i++)
        {
            DF_[i][TERM] = Fx[i];
        }

        // solving s
        double s[TERM] = {0};
        guassian(DF[0][0], DF[0][1], DF[0][2], DF[1][0], DF[1][1], DF[1][2], DF[2][0], DF[2][1], DF[2][2], Fx[0], Fx[1], Fx[2], s);

        //Xk_ = s + Xk
        for(int32_t i = 0; i < TERM; i++)
        {
            Xk_[i] = s[i] + Xk[i];
        }

        // Check for next step
        for(int32_t i = 0; i < TERM; i++)
        {
            if( fabs(Xk[i] - Xk_[i]) < 0.000001 )
            {
                flag *= 1;
                continue;
            }
            else{
                flag *= 0;
                break;
            }
        }

        if( flag == 0 )
        {
            for(int32_t i = 0; i < TERM; i++)
            {
                Xk[i] = Xk_[i];
            }
            flag = 1;
        }
        else
        {
            flag = 0;
        }
        
    }

    printf("Result:\n");
    printf("h = %.4lf, k = %.4lf, r=%.4lf\n", Xk[0], Xk[1], Xk[2]);

    return 0;
}

double f1(double u, double v, double w)
{
    return u*u + 16*u + v*v + 8*v - w*w + 80;
}
double f2(double u, double v, double w)
{
    return u*u -12*u + v*v - 18*v - w*w + 117;
}
double f3(double u, double v, double w)
{
    return u*u - 8*u + v*v + 18*v - w*w + 97;
}
double df1dx(double x)
{
    return 2*x+16;
}
double df1dy(double y)
{
    return 2*y+8;
}
double df1dr(double r)
{
    return -2*r;
}
double df2dx(double x)
{
    return 2*x-12;
}
double df2dy(double y)
{
    return 2*y-18;
}
double df2dr(double r)
{
    return -2*r;
}
double df3dx(double x)
{
    return 2*x-8;
}
double df3dy(double y)
{
    return 2*y+18;
}
double df3dr(double r)
{
    return -2*r;
}

void guassian(double a, double b, double c, double d, double e,double f,double g,double h,double i,double j,double k,double l, double *s)
{
 
    double A[TERM][TERM+1] = {a, b, c, j,
			    			  d, e, f, k,
			    			  g, h, i, l};
    
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

    //replace
    double C[TERM];
    for(int32_t i = 0; i < TERM; i++)
    {
	C[i] = 0;
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

    for(int32_t i = 0; i < TERM; i++)
    {
        s[i] = ans[i];
    }

    return;
}