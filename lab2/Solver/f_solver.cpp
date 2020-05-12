#include <iostream>
#include <vector>

#include "f_solver.h"

long factorial(int n) {
	if ( n == 0 ) { return 1; }
	return ( n * factorial(n - 1) );
}

long power(long num, int degree) {
	if (degree - 1 == 0) { return num; }
	num *= power(num, degree - 1 );
	return num;
}

long f_solver(int n) {
	return power(2, n) * factorial( n - 1 );
}
