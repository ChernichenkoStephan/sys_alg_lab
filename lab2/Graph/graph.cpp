#include <iostream>
#include <vector>

#include "graph.h"

struct Link;

// compear function for sort
bool compare_links(Link l, Link r) {
	return l.weight < r.weight;
}


// Find node and return nodes index, if node is not exist returning const
int get_node_index_by_name( std::string name, Graph *g ) {
    for (unsigned short i = 0; i < g->nodes.size(); i++) {
        Node *n = &(g->nodes[i]);
        if ( n->name == name) {
            return i;
        }
    }
    return INT_MIN;
}


// Find node and return nodes index, if node is not exist returning NULL
Node* get_node_by_name( std::string name, Graph *g ) {
    for (unsigned short i = 0; i < g->nodes.size(); i++) {
        Node *n = &(g->nodes[i]);
        if ( n->name == name) {
            return n;
        }
    }
    return NULL;
}

// Return all links that connected to entered node
std::vector<Link> get_links_array ( Node node, std::vector<Link> links ) {
	std::vector<Link> res;
	for ( Link l : links ) {
		if (l.right->name == node.name || l.left->name == node.name) {
			res.push_back(l);
		}
	}
	return res;
}

// Checking if node is in array
bool duplecate_protector( std::vector<Node> nodes, std::string name ) {
    for (unsigned short i = 0; i < nodes.size(); i++) {
        if (nodes[i].name == name) {
            return true;
        }
    }
    return false;
}


// Printing node with its links and connected nodes
void print_node ( Graph g ) {
	for (Node n : g.nodes) {

        std::cout << "\n\t---------- Node: " << n.name << " ----------" <<"\n\tlinked nodes of node:\n";
        if (n.linked_nodes_indexes.empty()) { printf("\tempty\n"); }
        for (int ln_index : n.linked_nodes_indexes) {
            std::cout << "\t" << g.nodes[ln_index].name <<'\n';
        }

		std::cout << "\n\tlinks of node:\n";
		std::vector<Link> links_array = get_links_array(n, g.links);
        if (links_array.empty()) { printf("\tempty\n"); }
        for (Link l : links_array) {
            std::cout << "\t" << l.name <<'\n';
        }
        printf("\t------------------------------\n");
    }
}

// graph print function
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

// Entering information and implementing stop by entering "_"
bool addPair( std::string *s, std::string *r ) {
    printf("\nSource node name: ");
    std::cin >> *s;
	// If entered "_" => stop entering
    if (*s == "_") { return false; }

    printf("\nReceive node name: ");
    std::cin >> *r;
	// If entered "_" => stop entering
    if (*r == "_") { return false; }
    return true;
}


// func to adding Link structure objects to graph
bool add_link( Graph *g, std::string l_name, std::string r_name) {

	Link new_link;
	std::string link_name;
	int link_weight;

	printf("\nLink name: ");
    std::cin >> link_name;
	// If entered "_" => stop entering
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

		// statment for proctection from adding non existing nodes
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

		// prints graph each 5 addings (it helps with interaction)
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

		// statment for proctection from adding non existing nodes
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


	// adding nodes to array without links, just initialization if nodes array
    if (!init_nodes_array( graph )) { return false; }

    printf("\033[0;34m--------- NODES INITIALIZATION ---------\033[0m\n");

	// connecting nodes (filling of linked_nodes_indexes), adding links
    if (!nodes_init( graph )) { return false; }

    return true;


}

// check if index is in array (used for linked_nodes_indexes in Node)
bool is_exist( int *array, int element, int count ) {
    for (unsigned short i = 0; i < count; i++)
        if (array[i] == count) { return true; }
    return false;
}

// ------------------------ Graph for test ------------------------

Graph* set_test_graph ( Graph *my_graph ) {

	Node *a = new Node();
	Node *b = new Node();
	Node *c = new Node();
	Node *d = new Node();
	Node *e = new Node();
	Link *l1 = new Link();
	Link *l2 = new Link();
	Link *l3 = new Link();
	Link *l4 = new Link();
	Link *l5 = new Link();
	Link *l6 = new Link();
	Link *l7 = new Link();
	Link *l8 = new Link();

	a->name = "A";
	b->name = "B";
	c->name = "C";
	d->name = "D";
	e->name = "E";
	a->linked_nodes_indexes.push_back(1);
	b->linked_nodes_indexes.push_back(2);
	c->linked_nodes_indexes.push_back(3);
	d->linked_nodes_indexes.push_back(0);
	a->linked_nodes_indexes.push_back(4);
	b->linked_nodes_indexes.push_back(4);
	c->linked_nodes_indexes.push_back(4);
	d->linked_nodes_indexes.push_back(4);


	l1->name = "l1";
	l2->name = "l2";
	l3->name = "l3";
	l4->name = "l4";
	l5->name = "l5";
	l6->name = "l6";
	l7->name = "l7";
	l8->name = "l8";

	l1->weight = 1;
	l2->weight = 2;
	l3->weight = 3;
	l4->weight = 4;
	l5->weight = 5;
	l6->weight = 6;
	l7->weight = 7;
	l8->weight = 8;

	l1->left = a;
	l1->right = b;

	l2->left = b;
	l2->right = c;

	l3->left = c;
	l3->right = d;

	l4->left = d;
	l4->right = a;

	l5->left = a;
	l5->right = e;

	l6->left = b;
	l6->right = e;

	l7->left = c;
	l7->right = e;

	l8->left = d;
	l8->right = e;


	my_graph->name = "G";
	my_graph->nodes.push_back(*a);
	my_graph->nodes.push_back(*b);
	my_graph->nodes.push_back(*c);
	my_graph->nodes.push_back(*d);
	my_graph->nodes.push_back(*e);
	my_graph->links.push_back(*l1);
	my_graph->links.push_back(*l2);
	my_graph->links.push_back(*l3);
	my_graph->links.push_back(*l4);
	my_graph->links.push_back(*l5);
	my_graph->links.push_back(*l6);
	my_graph->links.push_back(*l7);
	my_graph->links.push_back(*l8);

	return my_graph;
}
