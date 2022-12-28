#include <stdio.h>
#include "functions.c"


int main()
{
	printf("Euler limit: %.10lf\n", exp_limit(8));
	printf("Euler series: %.10lf\n", exp_loop(8));
	printf("Euler equation: %.10lf\n", dichotomy(func_exp, (double) 2.0, (double) 3.0, 8));


	printf("Pi limit: %.10lf\n", pi_limit(8));
	printf("Pi series: %.10lf\n", pi_loop(8));
	printf("Pi equation: %.10lf\n", dichotomy(func_pi, (double) 3.0, (double) 3.5, 8));


	printf("Ln2 limit: %.10lf\n", ln_limit(8));
	printf("Ln2 series: %.10lf\n", ln_loop(8));
	printf("Ln2 equation: %.10lf\n", dichotomy(func_ln, (double) 0.0, (double) 3.5, 8));


	printf("Square root limit: %.10lf\n", sqrt_limit(8));
	printf("Square root series: %.10lf\n", sqrt2_loop(8));
	printf("Square root equation: %.10lf\n", dichotomy(func_sqrt, (double) 0.0, (double) 2.0, 8));


	printf("Gamma limit: %.10lf\n", gamma_limit(4));
	printf("Gamma series: %.10lf\n", gamma_loop(8));
	printf("Gamma equation: %.10lf\n", dichotomy(func_gamma, (double) 0.0, (double) 1.0, 8));

	return 0;
}

