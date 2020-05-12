#include <iostream>
#include <vector>
#include <limits.h>
#include <cmath>

#include "polar_rand.h"


long power(long num, int degree) {
	if (degree - 1 == 0) { return num; }
	num *= power(num, degree - 1 );
	return num;
}

size_t number_digit (int number) {
    std::string s = std::to_string(number);
    return s.size();
}

unsigned long long square_rand( int seed, size_t steps ) {

    if (seed < 10 || seed > ULLONG_MAX ) { return 0; }

    unsigned long long x = seed;
    int k = number_digit(seed);
    int r_board = power(10, k/2);

    for (size_t i = 0; i < steps; i++) {
        int y = power(x, 2);
        x = y / r_board;
        if (number_digit(x) > k) {
            int l_board = power(10, k);
            x %= l_board;
        }
    }
    return x;
}

PResult polar_rand(int seed) {

    if (seed < 10 || seed > ULLONG_MAX ) { printf("ERROR 1\n"); return PResult(); }

    double u1, u2, v1, v2, s;
    size_t step = 0;


    do {
        step++;
        u1 = static_cast<double>(square_rand( seed, step )) / power(10, number_digit(seed));
        u2 = static_cast<double>(square_rand( seed, step + 1 )) / power(10, number_digit(seed));

        v1 = 2 * u1 - 1;
        v2 = 2 * u2 - 1;

        s = v1 * v1 + v2 * v2;

        if (s <= 1) {
            double n1 = v1*sqrt((-2 * log(s) / s));
            double n2 = v2*sqrt((-2 * log(s) / s));

            return PResult(n1, n2);
        }

        if (step > 1000) {  printf("ERROR 2\n");break; } // error protection

    } while (true);

    return PResult();

}
