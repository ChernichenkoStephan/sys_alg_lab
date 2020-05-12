#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstdint>
#include <vector>
#include <ctime>
#include <chrono>
#include <limits.h>


#include "Solver/f_solver.h"
#include "ExpressionChecker/expression_is_correct.h"
#include "Graph/graph.h"
#include "Kruskal/get_skeleton_kruskal.h"
#include "Prim/get_skeleton_prim.h"


int main(int argc, char **argv) {

    system("clear");

    // // --------------------------- task 1 EXPRESSION_CHEKER ---------------------------
    //
	// std::string str_exp;
	// std::string str_exp1 = "a+b+((c*d)\0";
	// std::string str_exp2 = "a+b+(c*d)\0";
	// std::string str_exp3 = "a+b+(c*d))\0";
	// Stack brackets = Stack();
	// Stack brackets1 = Stack();
	// Stack brackets2 = Stack();
	// Stack brackets3 = Stack();
    //
	// std::cout << "Enter expresiion" << '\n';
	// std::cin >> str_exp;
	// char *expression = to_array(str_exp);
	// char *expression1 = to_array(str_exp1);
	// char *expression2 = to_array(str_exp2);
	// char *expression3 = to_array(str_exp3);
    //
	// std::cout << "Entered expression: ";
	// std::cout << expression << '\n';
	// std::cout << "Expression is " << (expression_is_correct(expression, &brackets, '\0' ).is_correct ? "\033[0;32m correct \033[0m" : "\033[0;31mnot correct\033[0m") << '\n';
    //
	// std::cout << "Test expression1: ";
	// std::cout << expression1 << '\n';
	// std::cout << "Expression is " << (expression_is_correct(expression1, &brackets1, '\0' ).is_correct ? "\033[0;32m correct \033[0m" : "\033[0;31mnot correct\033[0m") << '\n';
    //
	// std::cout << "Test expression2: ";
	// std::cout << expression2 << '\n';
	// std::cout << "Expression is " << (expression_is_correct(expression2, &brackets2, '\0' ).is_correct ? "\033[0;32m correct \033[0m" : "\033[0;31mnot correct\033[0m") << '\n';
    //
	// std::cout << "Test expression3: ";
	// std::cout << expression3 << '\n';
	// std::cout << "Expression is " << (expression_is_correct(expression3, &brackets3, '\0' ).is_correct ? "\033[0;32m correct \033[0m" : "\033[0;31mnot correct\033[0m") << '\n';
    //
	// free(expression1);
	// free(expression2);
	// free(expression3);
    //
    //
    // // --------------------------- task 2 SOLVER ---------------------------
    //
    // long num = 0;
	// printf("num: %d\n", num);
	// num = f_solver(5);
	// printf("num: %d\n", num);

    // // --------------------------- task 3, 4 SKELETON KRUSKAL, SKELETON PRIM ---------------------------

    // bool manual_enter = false;  // make this true if u want manual entering
    //
	// Graph my_graph;
    //
    // if (manual_enter) {
	// 	if (graph_init(&my_graph)) {
	//         printf("\033[0;32m\n--------- GRAPH INITIALIZATION SUCCESS ---------\033[0m\n\n");
	//     } else {
	//         printf("\033[0;31mINIT ERROR\033[0m\n");
	//     }
    // } else {
	// 	set_test_graph(&my_graph);
	// 	printf("\033[0;32m\n--------- GRAPH INITIALIZATION SUCCESS ---------\033[0m\n\n");
	// }
    //
	// print_graph(my_graph);
	// printf("\033[0;34m\n--------- KRUSKAL METHOD ---------\033[0m\n\n");
	// my_graph = get_skeleton_kruskal ( &my_graph );
	// // print_graph(my_graph);
	// printf("\033[0;34m\n--------- PRIM METHOD ---------\033[0m\n\n");
	// my_graph = get_skeleton_prim ( &my_graph );
	// print_graph(my_graph);


    return 0;
}
