#ifndef TOPOLOGICAL_SORT
#define TOPOLOGICAL_SORT

struct Node {
    std::string name;
    std::vector<int> linked_nodes_indexes;
    int prew_count = 0;
};

struct Graph {
    std::string name;
    std::vector<Node> nodes;
};

Node* get_node_by_name(std::string name, Graph *g);
bool duplecate_protector(std::vector<Node> nodes, std::string name);
void print_graph(Graph g);
bool addPair(std::string *s, std::string *r);
bool nodes_init( Graph *g );
bool init_nodes_array( Graph *graph );
bool graph_init( Graph *graph );
bool is_exist(int *array, int element, int count);
bool set_links_count( Graph *graph );
void print_res_array(std::vector<int> array);
std::vector<int> init_res_array( Graph *graph, int* tail );
bool topological_sort(std::vector<int> res_array, int tail, Graph *graph);

#endif /* end of include guard: TOPOLOGICAL_SORT */
