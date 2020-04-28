#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstdint>
#include <vector>
#include <ctime>
#include <chrono>
#include <limits.h>


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

bool compare_links(Link l, Link r) {
	return l.weight > r.weight;
}

struct Graph {
    std::string name;
	std::vector<Node> nodes;
	std::vector<Link> links;
};

int get_node_index_by_name( std::string name, Graph *g ) {
    for (unsigned short i = 0; i < g->nodes.size(); i++) {
        Node *n = &(g->nodes[i]);
        if ( n->name == name) {
            return i;
        }
    }
    return INT_MIN;
}

Node* get_node_by_name( std::string name, Graph *g ) {
    for (unsigned short i = 0; i < g->nodes.size(); i++) {
        Node *n = &(g->nodes[i]);
        if ( n->name == name) {
            return n;
        }
    }
    return NULL;
}

std::vector<Link> get_links_array ( Node node, Graph g ) {
	std::vector<Link> res;
	for ( Link l : g.links ) {
		if (l.right->name == node.name || l.left->name == node.name) {
			res.push_back(l);
		}
	}
	return res;
}

bool duplecate_protector( std::vector<Node> nodes, std::string name ) {
    for (unsigned short i = 0; i < nodes.size(); i++) {
        if (nodes[i].name == name) {
            return true;
        }
    }
    return false;
}

void print_node ( Graph g ) {
	for (Node n : g.nodes) {

        std::cout << "\n\t---------- Node: " << n.name << " ----------" <<"\n\tlinked nodes of node:\n";
        if (n.linked_nodes_indexes.empty()) { printf("\tempty\n"); }
        for (int ln_index : n.linked_nodes_indexes) {
            std::cout << "\t" << g.nodes[ln_index].name <<'\n';
        }

		std::cout << "\n\tlinks of node:\n";
		std::vector<Link> links_array = get_links_array(n, g);
        if (links_array.empty()) { printf("\tempty\n"); }
        for (Link l : links_array) {
            std::cout << "\t" << l.name <<'\n';
        }
        printf("\t------------------------------\n");
    }
}


void print_graph( Graph g ) {
    std::cout << "\n---------- Graph: " << g.name << " ----------\n Graph nodes:" << '\n';
    if (g.nodes.empty()) { printf("\tempty\n\n\n"); }
    print_node(g);

	std::cout << "\n---------- Graph: " << g.name << " ----------\n Graph Links:" << '\n';
	for (Link l : g.links) {
        std::cout << "\n\t---------- Link: " << l.name << " " << l.weight << " ----------" <<"\n\tnodes of link:\n";
		std::cout << "\t" << l.left->name <<'\n';
		std::cout << "\t" << l.right->name <<'\n';
        printf("\t------------------------------\n");
    }

}

bool addPair( std::string *s, std::string *r ) {
    printf("\nSource node name: ");
    std::cin >> *s;
    if (*s == "_") { return false; }

    printf("\nReceive node name: ");
    std::cin >> *r;
    if (*r == "_") { return false; }
    return true;
}

bool add_link( Graph *g, std::string l_name, std::string r_name) {

	Link new_link;
	std::string link_name;
	int link_weight;

	printf("\nLink name: ");
    std::cin >> link_name;
    if (link_name == "_") { return false; }

	printf("\nLink weight: ");
    std::cin >> link_weight;

	new_link.name = link_name;
	new_link.weight = link_weight;
	new_link.left = get_node_by_name(l_name, g);
	new_link.right = get_node_by_name(r_name, g);

	g->links.push_back(new_link);

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

			add_link(g, s_entered_name, r_entered_name);

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

// ------------------------ Kruskal method ------------------------

// ------------------------ Sort for links ------------------------

void swap_elements (void *l, void *r) {
	void* container = l;
	l = r;
	r = container;
}

void shell_links_sort( std::vector<Link> *array ) {

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

}

// ===============



struct Plurality {
	std::vector<void*> elements;
};



Graph get_ostov_kruskal ( Graph *g ) {

	Graph res_g;
	std::vector<Plurality> pluralities;
	std::vector<Node> nodes = g->nodes;
	std::vector<Link> links = g->links;

	// starts array of pluralities
	for ( Node n : nodes ) {
		Plurality p;
		p.elements.push_back(&n);
		pluralities.push_back(p);
	}

	std::sort(links, compare_links);
    cout << "Links sorted by weight: \n";
    for (auto l : links)
        cout << l.name << " " << l.weight << '\n';



}

// ------------------------ Prim method ------------------------

Graph get_ostov_prim ( Graph g ) {
	Graph res_g;
}

int main(int argc, char **argv) {

    system("clear");

	std::cout << "/* Start */" << '\n';

    Graph my_graph;

    if (graph_init(&my_graph)) {
        printf("\033[0;32m\n--------- GRAPH INITIALIZATION SUCCESS---------\033[0m\n\n");
        print_graph(my_graph);
    } else {
        printf("SUCCESS\n");
    }


    return 0;
}
