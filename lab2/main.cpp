#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstdint>
#include <vector>
#include <ctime>
#include <chrono>
#include <limits.h>




vector<size_t> prefix_function (string s) {

	int n = (int) s.length();

	vector<size_t> P(n);

	for (size_t i = 1; i < n; ++i) {

		size_t j = pi[i-1];

		while ( j > 0 && (s[i] != s[j]) ) {
            j = pi[j-1];
        }

		if (s[i] == s[j]) { ++j; }

		pi[i] = j;

	}
	return pi;
}






int main(int argc, char **argv) {

    system("clear");

    return 0;
}
