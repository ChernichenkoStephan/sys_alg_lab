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

#define MAX_U_L_L_INT 4294967296
#define FIRST_INDEX 1
#define END_INDEX argc - 1
#define ARRAY_SIZE (argc - 1)



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

    В методе Шелла сравниваются не соседние элементы, а элементы, расположенные
    на расстоянии d (где d - шаг между сравниваемыми элементами): d = [n/2].
    После каждого просмотра шаг d уменьшается вдвое. На последнем просмотре он
    сокращается до d = 1.

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



// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
// ------------------------        Task 2         --------------------------------
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------





struct Node {
    std::string name;
    std::vector<int> linked_nodes_indexes;
    int prew_count = 0;
};

struct Graph {
    std::string name;
    std::vector<Node> nodes;
};

int get_node_index_by_name(std::string name, Graph *g) {
    for (unsigned short i = 0; i < g->nodes.size(); i++) {
        Node *n = &(g->nodes[i]);
        if ( n->name == name) {
            return i;
        }
    }
    return INT_MIN;
}

Node* get_node_by_name(std::string name, Graph *g) {
    for (unsigned short i = 0; i < g->nodes.size(); i++) {
        Node *n = &(g->nodes[i]);
        if ( n->name == name) {
            return n;
        }
    }
    return NULL;
}

bool duplecate_protector(std::vector<Node> nodes, std::string name) {
    for (unsigned short i = 0; i < nodes.size(); i++) {
        if (nodes[i].name == name) {
            return true;
        }
    }
    return false;
}


void print_graph(Graph g) {
    std::cout << "\n---------- Graph: " << g.name << " ----------\n Graph nodes:" << '\n';
    if (g.nodes.empty()) { printf("\tempty\n\n\n"); }
    for (Node n : g.nodes) {
        std::cout << "\n\t---------- Node: " << n.name << " ----------" <<"\n\tlinked nodes of node:\n";
        if (n.linked_nodes_indexes.empty()) { printf("\tempty\n"); }
        for (int ln_index : n.linked_nodes_indexes) {
            std::cout << "\t" << g.nodes[ln_index].name <<'\n';
        }
        printf("\t------------------------------\n");
    }
}

bool addPair(std::string *s, std::string *r) {
    printf("\nSource node name: ");
    std::cin >> *s;
    if (*s == "_") { return false; }

    printf("\nReceive node name: ");
    std::cin >> *r;
    if (*r == "_") { return false; }
    return true;
}

bool nodes_init( Graph *g ) {

    std::string s_entered_name, r_entered_name;

    unsigned short index = 1;
    std::cout << "Enter " << index << " pair name (for quit \"_\") from graph: "
              << g->name << '\n';
    print_graph(*g);

    bool flag = addPair(&s_entered_name, &r_entered_name);

    while (flag) {

        Node *source_node = get_node_by_name(s_entered_name, g);
        int receive_node_index = get_node_index_by_name(r_entered_name, g);

        if ( source_node && receive_node_index != INT_MIN ) {
            source_node->linked_nodes_indexes.push_back(receive_node_index);
            printf("\033[0;32mNode added\033[0m\n");
        } else {
            printf("\033[0;31mError one of nodes not exists\033[0m\n");
        }

        index++;
        std::cout << "Enter " << index << " node name (for quit \"_\") from graph: "
                  << g->name << '\n';
        if (index % 5 == 0) { print_graph(*g); }

        flag = addPair(&s_entered_name, &r_entered_name);

    }

    return true;
}


bool init_nodes_array( Graph *graph ) {

    std::string entered_name;

    printf("\n============================\n");
    unsigned short index = 1;
    std::cout << "Enter " << index << " node name" << '\n';
    std::cin >> entered_name;

    while (entered_name != "_") {
        Node node;
        if (!duplecate_protector(graph->nodes, entered_name)) {
            node.name = entered_name;
            graph->nodes.push_back(node);
        } else {
            printf("\033[0;31mError node already exists\033[0m\n");
        }
        printf("\033[0;32mNode created\033[0m\n");

        printf("\n============================\n");
        index++;
        std::cout << "Enter " << index << " node (for quit \"_\")" << '\n';
        std::cin >> entered_name;

    }

    return true;
}


bool graph_init( Graph *graph ) {

    std::cout << "Enter graphs name" << '\n';
    std::cin >> graph->name;

    printf("\033[0;34m--------- NODES ARRAY INITIALIZATION ---------\033[0m\n");

    if (!init_nodes_array( graph )) { return false; }

    printf("\033[0;34m--------- NODES INITIALIZATION ---------\033[0m\n");

    if (!nodes_init( graph )) { return false; }

    return true;

}

bool is_exist(int *array, int element, int count) {

    for (unsigned short i = 0; i < count; i++) {
        if (array[i] == count) { return true; }
    }

    return false;
}

/*------------------------------ Sort fucntions ------------------------------*/



bool set_links_count( Graph *graph ) {

    int count = graph->nodes.size();

    bool res = false;

    for ( unsigned short i = 0; i < count; i++ ) {

        Node *observed_node = &(graph->nodes[i]);

        for ( unsigned short j = 0; j < count; j++ ) {

            Node *node = &(graph->nodes[j]);

            // not tracking itself
            if (observed_node->name == node->name) { continue; }

            // checking in node links
            for (int ln_index : node->linked_nodes_indexes) {

                // if there is observed_node in linked nodes
                if (graph->nodes[ln_index].name == observed_node->name) {
                        observed_node->prew_count++;
                        res = true;
                }

            }
        }
    }

    return res;

}

void print_res_array(std::vector<int> array) {
    std::cout << "Q ARRAY" << '\n';
    for (int element : array) {
        std::cout << element << '\n';
    }
}

std::vector<int> init_res_array( Graph *graph, int* tail ) {
    int a_length = graph->nodes.size();
    std::vector<int> res;

    for (unsigned short g_index = 0; g_index < a_length; g_index++) {
        if (graph->nodes[g_index].prew_count == 0) {
            res.push_back(g_index);
        }
    }
    *tail = res.size();

    std::cout << "tail: " << *tail << '\n';

    return res;
}

bool topological_sort(std::vector<int> res_array, int tail, Graph *graph) {

    int printed_elements_ammount = 0;

    int elements_ammount = graph->nodes.size();

    if (res_array.size() == 0) { return false; }

    while (printed_elements_ammount != elements_ammount) {

        // element to print
        int index = res_array[printed_elements_ammount];

        Node *observed_node = &(graph->nodes[index]);

        std::cout << observed_node->name << '\n';

        // removing observed node frome nodes prew_count counters
        for (int i : observed_node->linked_nodes_indexes) {
            graph->nodes[i].prew_count--;
            if (graph->nodes[i].prew_count == 0) {
                res_array.push_back(i);
            }
        }
        /*

        2) Перестроение начала списка: Q:=A[Q].data.N.

         */
        printed_elements_ammount++;
    }



    return true;
}


/*----------------------------------------------------------------------------*/


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

long power(long num, int degree) {
	if (degree - 1 == 0) { return num; }
	num *= power(num, degree - 1 );
	return num;
}

size_t number_digit (int number) {
    std::string s = std::to_string(number);
    return s.size();
}

unsigned long long int square_rand( int seed, size_t steps ) {

    if (seed < 10 || seed > MAX_U_L_L_INT ) { return 0; }

    unsigned long long int x = seed;
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

    if (seed < 10 || seed > MAX_U_L_L_INT ) { printf("ERROR 1\n");return PResult(); }

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

/*----------------------------------------------------------------------------*/


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


    std::cout << "/* Start task 2 */" << '\n';

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


    for (size_t i = 1; i < 10; i++) {
        PResult res = polar_rand(423 * i);
        printf("i%d) n1: %f, n2: %f\n", i, res.left, res.right);
    }

    return 0;
}
