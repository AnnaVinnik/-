#include <stdio.h>
#include <stdlib.h>

int n = 4;
double *x, *y, *X, *Y, eps = 0.2;
const double N = 4;

double func(double x)
{
	return x * x;
}

double del[6][7] = {0};

int Del(double xn)
{

int i, j;
	for (i = 0; i < 6; i++){
		del[i][0] = X[i];
		del[i][1] = Y[i];
	}
	for (i = 2; i < 5; i++){
		for (j = 0; j < n / 2 - i + 2; j ++){
			del[j][i] = del[j + 1][i - 1] - del[j][i - 1];
		}
	}		
}

double q(int k, double xn)
{
	if (k == 0)
		return 1;
	double q = xn - X[0];
	int i;
	for (i = 1; i <  k; i++){
		q *= xn - X[0] - i;
	} 
}

int fact(int k)
{
int i, p = 1;
	if (n == 0)
		return 1;
	for ( i = k; i > 1; i--)
		p *= k;
	return p;
}

double intNewton(double xn){
	double p;
	int i, j;
	Del(xn);
	
	for (i = 0; i < 4 + 1; i++){
		p += del[0][i + 1] * q(i, xn) / fact(i);
		//printf("p = %.3f i =  %d\n", p, i);
	}
	return p;
}

double init()
{
	for (int i = 0; i <= n; i++){
		X[i] = x[i] = i;
		Y[i] = y[i] = func(x[i]);
	}
}




double integ()
{
double I, I2n, h, k = 0;
	x = (double *)malloc(sizeof(double) * n * 2);
	y = (double *)malloc(sizeof(double) * n * 2);
	X = (double *)malloc(sizeof(double) * N);
	Y = (double *)malloc(sizeof(double) * N);

	init();
		h = (x[n] - x[0]) / n;
		
	for (int i = 1; i <= n - 1; i++){
		I += y[i];
		printf("I = %.3f\n", I);
	}
	I += (y[0] + y[n]) / 2;
	printf("I = %.3f\n", I);
	I = I * h;
	printf("I = %.3f x[n] = %.1f\n", I, x[n]);
		
	{
		n *= 2;
		if (k > 0){
			x = realloc(x, sizeof(double) * n);
			y = realloc(y, sizeof(double) * n);
			I = I2n;
		}
		
		
		for (int i = 0; i <= n; i++){
			
			x[i] = i * h / 2;
			y[i] = func(x[i]);
			
		}
		
		h = (x[n] - x[0]) / n;
		
		for (int i = 1; i <= n - 1; i++){
			I2n += y[i];
			printf("I2n = %.3f\n", I2n);
		}
		I2n += (y[0] + y[n]) / 2;
		printf("I2n = %.3f\n", I2n);
		I2n = I2n * h;
		printf("I2n = %.3f\n", I2n);
		k++;
	}while ((((I - I2n) / 3) > eps) && (k < 2));
	return I2n;
}

int main()
{
	integ();
	printf("x: ");
	for (int i = 0; i <= n; i++)
		printf("%.2f  ", x[i]);
	printf("\n");
	
	printf("y: ");
	for (int i = 0; i <= n; i++)
		printf("%.2f  ", y[i]);
	printf("\n");
	/*
	x = (double *)malloc(sizeof(double) * n * 2);
	y = (double *)malloc(sizeof(double) * n * 2);
	X = (double *)malloc(sizeof(double) * N);
	Y = (double *)malloc(sizeof(double) * N);
	init();
	
		printf("x: ");
	for (int i = 0; i <= n; i++)
		printf("%.2f  ", x[i]);
	printf("\n");
	
	printf("y: ");
	for (int i = 0; i <= n; i++)
		printf("%.2f  ", y[i]);
	printf("\n");
	
	printf("Newton (0.5) = %.3f\n", intNewton(0.5));
	*/
return 0;
}
