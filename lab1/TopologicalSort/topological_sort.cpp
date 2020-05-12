#include <iostream>
#include <vector>

#include "topological_sort.h"

#define FIRST_INDEX 1
#define END_INDEX argc - 1
#define ARRAY_SIZE (argc - 1)


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
        
        printed_elements_ammount++;
    }



    return true;
}
