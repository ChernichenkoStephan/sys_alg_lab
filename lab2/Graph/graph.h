#ifndef GRAPH
#define GRAPH

struct Node {
    std::string name;
    std::vector<int> linked_nodes_indexes;
    int prew_count = 0;
};

struct Link {
	std::string name;
	int weight;
	Node *left;
	Node *right;
};

struct Graph {
    std::string name;
	std::vector<Node> nodes;
	std::vector<Link> links;
};

// compear function for links
bool compare_links(Link l, Link r);

// compear function for sort
int get_node_index_by_name( std::string name, Graph *g );

// Find node and return nodes index, if node is not exist returning const
Node* get_node_by_name( std::string name, Graph *g );

// Find node and return nodes index, if node is not exist returning NULL
std::vector<Link> get_links_array ( Node node, std::vector<Link> links );

// Return all links that connected to entered node
bool duplecate_protector( std::vector<Node> nodes, std::string name );

// Checking if node is in array
void print_node ( Graph g );

// Printing node with its links and connected nodes
void print_graph( Graph g );

// graph print function
bool addPair( std::string *s, std::string *r );

// Entering information and implementing stop by entering "_"
bool add_link( Graph *g, std::string l_name, std::string r_name);

// func to adding Link structure objects to graph
bool nodes_init( Graph *g );

// initialization func
bool init_nodes_array( Graph *graph );

// initialization func
bool graph_init( Graph *graph );

// check if element is in graph
bool is_exist( int *array, int element, int count );

// check if index is in array (used for linked_nodes_indexes in Node)
Graph* set_test_graph ( Graph *my_graph );



#endif /* end of include guard: GRAPH */
