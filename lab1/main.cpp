#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstdint>
#include <vector>
#include <ctime>
#include <chrono>
#include <limits.h>
#include <cmath>

#include "Shell/shell.h"
#include "TopologicalSort/topological_sort.h"
#include "BinaryTreeSearch/binary_tree_search.h"
#include "KMPSearch/kmp_search.h"
#include "PolarRand/polar_rand.h"

#define MAX_U_L_L_INT 4294967296
#define FIRST_INDEX 1
#define END_INDEX argc - 1
#define ARRAY_SIZE (argc - 1)



int main(int argc, char **argv) {

    std::cout << "\n\nTASK 1(SHELL SORT):\n";
    auto now = time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());

    std::vector<int> array;

    unsigned int array_size = 20;

    if (argc < 3) {
        std::cout << "\n----------- Using default generation -----------" << '\n';
        if (argc == 2) {
            if ( atoi(argv[FIRST_INDEX]) ) { array_size = atoi(argv[FIRST_INDEX]); }
        }
        array = GenerateArray( array_size, 9 );
    } else {
        array_size = ARRAY_SIZE;
        array = input_array(argv, array_size);
    }

    if ( (ARRAY_SIZE % 2) != 0 && (array_size %2) != 0 ) {
        std::cout << "array should be even" << '\n';
        return 1;
    }

    std::cout << "ARRAY SIZE: " << array_size <<'\n';


    shell_sort( &array );

    if (isSorted(array)) { std::cout << "Sorted\n\n\n" << '\n'; }


    if (array_size < 50) {
        print_array( array );
    }

    std::cout << "\n\nTime to algorithm (microseconds): "
     << (time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()) - now).count();



     // --------------------------- task 2 topological_sort ---------------------------

     std::cout << "/* Start */" << '\n';

     Graph my_graph;

     if (graph_init(&my_graph)) {
         printf("\033[0;34m\n--------- GRAPH INITIALIZATION SUCCESS---------\033[0m\n\n");
         print_graph(my_graph);
     } else {
         printf("SUCCESS\n");
     }

     if (!set_links_count(&my_graph)) { printf("Not a graph\n"); }

     // for ( Node node : my_graph.nodes) {
     //     std::cout << node.prew_count << '\n';
     // }

     int tail = 0;

     std::vector<int> q_array = init_res_array( &my_graph, &tail );

     // print_res_array(q_array); // test only

     printf("\033[0;34m\n--------------- SORTED GRAPH PRINT ---------------\033[0m\n\n");

     if(!topological_sort(q_array, tail, &my_graph)) { printf("Sort fault\n"); }

     std::cout << "/* End */" << '\n';


      // --------------------------- task 3 binary_tree_search ---------------------------


     Tree *my_tree = new Tree;

     printf("\033[0;34m--------- TREE INITIALIZATION ---------\033[0m\n");


     if (!init_tree( my_tree )) {
         printf("\033[0;31mTree init error\033[0m\n");
     }

     if (!tree_print( my_tree )) {
         printf("\033[0;31mTree print error\033[0m\n");
     }

     std::string key;

     std::cout << "Enter the key: ";
     std::cin >> key;

     binary_tree_search( my_tree, key );

     if (!clear_memory( my_tree )) {
         printf("\033[0;31mTree was empty, or was not exist.\033[0m\n");
     } else {
         printf("\033[0;32mMemory cleaned\033[0m\n");
     }

      // --------------------------- task 4 kmp_search ---------------------------

     kmp_search();

      // --------------------------- task 5 polar_rand ---------------------------

     PResult res = polar_rand(19);

     printf("RandNum: (%d, %d)\n", res.left, res.right);


    return 0;
}
