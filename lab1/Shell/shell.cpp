#include <iostream>
#include <vector>

#include "shell.h"

std::vector<int> GenerateArray(unsigned int array_size, unsigned int seed) {
  srand(seed);

  std::vector<int> res;

  for (int i = 0; i < array_size; i++) {
    res.push_back(rand() % 1000);
  }

  return res;
}

void swap_nums (int *a, int *b) {
    *a += *b;
    *b = *a - *b;
    *a = *a - *b;
}

bool isSorted(std::vector<int> array) {
    for (int i = 0; i < array.size() - 1; i++) {
        if (array[i] > array[i+1]) {
            return false;
        }
    }
    return true;
}

void shell_sort( std::vector<int> *array ) {

    /*

    The Shell method compares not neighboring elements, but elements located
     at a distance d (where d is the step between the compared elements): d = [n / 2].
     After each scan, step d is halved. At the last viewing he
     reduced to d = 1.

    */
    unsigned int array_size = (*array).size();
    unsigned int step = array_size / 2;
    unsigned long steps = 0;
    bool iverson;



    do {
        unsigned int index = 0;
        iverson = true;

        while ( index < (array_size - step) ) {

            if ((*array)[index] > (*array)[index + step]) {
                swap_nums (&(*array)[index], &(*array)[index + step]);
                iverson = false;
            }

            index++;

            /* Error protection */
            if (index > 2147483647) {
                iverson = true;
                break;
            }

        }

        steps++;

        if (step != 1 ) { step /= 2; }

    } while (!iverson);

    std::cout << "Steps: " << steps << '\n';


}

void print_array( std::vector<int> array ) {

    std::cout << array[0];

    for (int i = 1; i < array.size(); i++) {
        std::cout <<  ", " << array[i];
    }

}


std::vector<int> input_array ( char **input_array, unsigned int array_size ) {

    std::vector<int> res;

    for (int i = 1; i <= array_size; i++) {
        res.push_back(atoi(input_array[i]));
    }

    return res;

}
