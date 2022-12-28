#include <stdlib.h>
#include <math.h>


#define EPS 0.000000000000000000001


double factorial(double n);
double exp_limit(int count);
double exp_loop(int count);
double pi_limit(int count);
double pi_loop(int count);
double ln_limit(int count);
double ln_loop(int count);
double sqrt_limit(int count);
double sqrt2_loop(int count);
double combinations(double k, double m);
double gamma_limit(int count);
double gamma_loop(int count);
double gamma_equation_limit(int count);
double func_pi(double x);
double func_exp(double x);
double func_ln(double x);
double func_sqrt(double x);
double func_gamma(double x);
double dichotomy(double (*func) (double), double left, double right, int count);
int is_prime(int number);



double factorial(double n)
{
	return (n < 2) ? 1 : n * factorial(n - 1);
}


double func_gamma(double x)
{
	return exp(-x) - gamma_equation_limit(4);
}


double func_exp(double x)
{
	return log(x) - 1;
}


double func_pi(double x)
{
	return -sin(x);
}


double func_ln(double x)
{
	return exp(x) - 2;
}


double func_sqrt(double x)
{
	return x * x - 2;
}


double exp_limit(int count)
{
    double accuracy = pow(10, -count);
	double prev = 0;
	double cur = 2;
	int i = 2;

	do
    {
		prev = cur;
		cur = pow(1 + 1.0 / i, i); 
		++i;
	} while (fabs(cur - prev) > accuracy);

	return cur;
}


double exp_loop(int count)
{
    double accuracy = pow(10, -count);
	double cur = 1;
	double prev = 0;
	int i = 1;

	do
    {
		prev = cur;
		cur += 1.0 / factorial(i);
		++i;
	} while (fabs(cur - prev) > accuracy);

	return cur;
}


double pi_limit(int count)
{
    double accuracy = pow(10, -count);
	double prev = 0;
	double cur = 4;
	int i = 1;

	do
    {
		prev = cur;
		cur *= (4 * i * (i + 1)) / pow(2 * i + 1, 2);
		++i;
	} while (fabs(cur - prev) > accuracy);

	return cur;
}


double pi_loop(int count)
{
    double accuracy = pow(10, -count);
	double prev = 0;
	double cur = 1;
	int i = 2;

	do
    {
		prev = cur;
		cur += ((i % 2 == 0) ? (-1.0) : (1.0)) / (2 * i - 1);
		++i; 
	} while (fabs(cur - prev) > accuracy);

	return 4.0 * cur;
}


double ln_limit(int count)
{
    double accuracy = pow(10, -count);
	double prev = 0;
	double cur = 1;
	int i = 2;

	do
    {
		prev = cur;
		cur = i * (pow(2, 1.0 / i) - 1.0);
		++i;
	} while (fabs(cur - prev) > accuracy);

	return cur;
}


double ln_loop(int count)
{
    double accuracy = pow(10, -count);
	double prev = 0;
	double cur = 1;
	int i = 2;

	do
    {
		prev = cur;
		cur += ((i % 2 == 0) ? (-1.0) : (1.0)) / i;
		++i;
	} while (fabs(cur - prev) > accuracy);

	return cur;
}


double sqrt_limit(int count)
{
    double accuracy = pow(10, -count);
	double prev = 0;
	double cur = -0.5;

	do
    {
		prev = cur;
		cur = cur - pow(cur, 2) / 2 + 1.0;
	} while (fabs(cur - prev) > accuracy);

	return cur;
}


double sqrt2_loop(int count)
{
    double accuracy = pow(10, -count);
	double prev = 0;
	double cur = pow(2, pow(2, -2));
	double k = 3;

	do
    {
		prev = cur;
		cur *= pow(2, pow(2, -k));
		++k;
	} while (fabs(cur - prev) > accuracy);

	return cur;
}


double combinations(double k, double m)
{
	return factorial(m) / (factorial(k) * factorial(m - k));
}


double gamma_limit(int count)
{
    double accuracy = pow(10, -count);
	double prev = 0;
	double cur = 0;
	double k = 2;
    int i;

	do
    {
		prev = cur;
		cur = 0.0;
		for (int i = 1; i <= k; ++i)
        {
			cur += (combinations(i, k) * ((i % 2 == 0) ? (1) : (-1)) * log(factorial(i))) / i;
		}
		++k;
	} while (fabs(cur - prev) > accuracy);

	return cur;
}


double gamma_loop(int count)
{
    double accuracy = pow(10, -count);
	double prev = 0;
	double cur = 0.5;
	double sum = 0;
	int i = 3;

	do
    {
		prev = cur;
		sum = ((1.0 / pow(floor(sqrt(i)), 2)) - (1.0 / i));
		cur += sum;
		if (sum < EPS)
        {
			prev = 0.0;	
		}
		i++;
	} while (fabs(cur - prev) > accuracy);

	return -pow(M_PI, 2) / 6.0 + cur;
}


int is_prime(int number)
{
    int i;
	number = abs(number);
	
	if (number == 1)
    {
		return 0;
	}

	for (i = 2; i <= sqrt(number); ++i)
    {
		if (number % i == 0)
        {
			return 0;
		}
	}

	return 1;
}


double get_mult(int t)
{
    int i;
	double mult = 1.0;

	for (i = 2; i <= t; ++i)
    {
		if (is_prime(i))
        {
			mult *= (i - 1.0) / i;
		}
	}

	return mult;
}


double gamma_equation_limit(int count)
{
    double accuracy = pow(10, -count);
	double prev = 0;
	double cur = 0;
	int k = 2;

	do
    {
		prev = cur;
		cur = log(k) * get_mult(k);
		k++;
	} while (fabs(cur - prev) > accuracy);

	return cur;
}


double dichotomy(double (*func) (double), double left, double right, int count)
{
    double accuracy = pow(10, -count);
	double result = 0.0;
	
	do
    {
		result = (right + left) / 2;

		if (func(result) * func(right) < accuracy)
        {
			left = result;
		}
        else
        {
			right = result;
		}
	} while (fabs(right - left) > accuracy);

	return result;
}