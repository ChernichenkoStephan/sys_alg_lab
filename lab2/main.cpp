#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstdint>
#include <vector>
#include <ctime>
#include <chrono>
#include <limits.h>




std::vector<size_t> prefix_function (std::string s) {

	int n = (int)s.length();

	std::vector<size_t> p_array(n);

	for (size_t i = 1; i < n; ++i) {

		size_t j = p_array[i-1];

		while ( j > 0 && (s[i] != s[j]) ) {
            j = p_array[j-1];
        }

		if (s[i] == s[j]) { ++j; }

		p_array[i] = j;

	}
	return p_array;
}


bool kmp_search() {
	std::string s, key;

	std::cout << "Enter investigation string" << '\n';
    std::cin >> s;
	std::cout << "Enter string to find" << '\n';
	std::cin >> key;

    std::vector<size_t> p_array = prefix_function(key + '#' + s);

    int key_len = key.length();

    for (int i = 0; i < s.length(); i++) {
        if (p_array[key_len + 1 + i] == key_len) {

			size_t start_index = i - key_len + 1;
			size_t end_index = i;

			std::cout << "Key found at index: "<< start_index << std::endl;
        }
    }
	return true;
}



int main(int argc, char **argv) {

    system("clear");

	kmp_search();

    return 0;
}
