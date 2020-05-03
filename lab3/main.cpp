#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstdint>
#include <vector>
#include <ctime>
#include <chrono>
#include <limits.h>
#include <utility>
#include <cmath>

#define MACHINE_AMOUNT 3


// rand on hight values works better, so we are using it here
int good_rand( int up_boarder ) {
	return ( rand() % up_boarder * 10000 ) / 10000 + 1;
}

bool sort_func( std::vector<int> l, std::vector<int> r ) {

	if (l[1] < r[1]) {
		return true;
	} else if (l[1] == r[1]) {
		if (l[2] < r[2]) {
			return true;
		} else if (l[2] == r[2]) {
			return (l[3] < r[3]);
		}
	}

	return false;

}

int get_time () {

}


int main(int argc, char const *argv[]) {

	/*
		std::vector<unsigned> is a part,
		first  element of array - part index;
		second element of array - A machine time;
		third  element of array - B machine time;
		fourth element of array - C machine time;
	*/
	
	std::vector<std::vector<int> > parts;

	size_t parts_amount = 10;

	for (int i = 0; i < parts_amount; i++){
		std::vector<int> part;
		part.push_back(i);
		for (size_t j = 0; j < MACHINE_AMOUNT; j++) {
			part.push_back(good_rand(20));
		}
		parts.push_back(part);
	}

	std::sort(parts.begin(), parts.end(), sort_func);

	std::cout << "PARTS ORDER: " << '\n';

	for (auto part : parts) {
		std::cout << part[0] << ' ';
		/*
		// Uncoomment this to print
		for (size_t i = 1; i < part.size(); i++) {
			std::cout << part[i] << ' ';
		}
		std::cout << '\n';
		*/
	}

	return 0;
}
