#ifndef SHELL_SORT
#define SHELL_SORT

std::vector<int> GenerateArray(unsigned int array_size, unsigned int seed);
void swap_nums (int *a, int *b);
bool isSorted(std::vector<int> array);
void shell_sort( std::vector<int> *array );
void print_array( std::vector<int> array );
std::vector<int> input_array ( char **input_array, unsigned int array_size );

#endif /* end of include guard: SHELL_SORT */
