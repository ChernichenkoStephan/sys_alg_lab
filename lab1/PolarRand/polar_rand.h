#ifndef POLAR_RAND
#define POLAR_RAND

struct PResult {
    double left;
    double right;

    PResult(double l, double r) {
		left = l;
		right = r;
    }
	PResult() {
        left = 0;
		right = 0;
    }
};


long power(long num, int degree);
size_t number_digit (int number);
// using square_rand to get better rands than rand()
unsigned long long square_rand( int seed, size_t steps );
PResult polar_rand(int seed);

#endif /* end of include guard: POLAR_RAND */
