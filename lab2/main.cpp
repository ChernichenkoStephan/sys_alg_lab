#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstdint>
#include <vector>
#include <ctime>
#include <chrono>
#include <limits.h>

struct Link;

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

// compear function for sort
bool compare_links(Link l, Link r) {
	return l.weight < r.weight;
}

struct Graph {
    std::string name;
	std::vector<Node> nodes;
	std::vector<Link> links;
};


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

// ------------------------ Kruskal method ------------------------


struct Plurality_Node {
	int index;
	std::vector<Node> elements;
	Plurality_Node* next;
};

// returns pularlity from stack
Plurality_Node* get_pluraluty ( Node element, Plurality_Node *head ) {
	Plurality_Node *current = head;
	while (current->next != NULL) {
		for (Node e : current->elements ) {
			if (e.name == element.name) {
				return current;
			}
		}
		current = current->next;
	}
	return NULL;
}

// deleting pularlity from stack
bool delete_plurality ( Plurality_Node *p, Plurality_Node *head ) {
	Plurality_Node *current = head;
	while (current->next != NULL) {
		if (p == current->next) {

			Plurality_Node *prew = current;
			Plurality_Node *deleting = current->next;
			Plurality_Node *next = deleting->next;

			prew->next = next;
			free(deleting);

			return true;
		}
		current = current->next;
	}
	return false;
}


// adding link in Kurskal method
void include_link( Plurality_Node *head, Plurality_Node *first, Plurality_Node *second, Link link, Graph *graph ) {

	// transportiong all nodes between pluralities
	for (Node e : second->elements) {
		first->elements.push_back(e);
	}

	// deleting second
	delete_plurality(second, head);

	// adding link to graph
	graph->links.push_back(link);

	// linking nodes
	Node *source_node = get_node_by_name(link.left->name, graph);
	int receive_node_index = get_node_index_by_name(link.right->name, graph);

	if ( source_node && receive_node_index != INT_MIN ) {

		// refresh nodes links
		std::vector<int> new_links;
		source_node->linked_nodes_indexes = new_links;

		// connecting back nodes
		source_node->linked_nodes_indexes.push_back(receive_node_index);
		printf("\033[0;32mNode linked in Ostov\033[0m\n");
	} else {
		printf("\033[0;31m Node linking in Ostov Error \033[0m\n");
	}

}

// Printing all plurality stack function
void print_plurality(Plurality_Node *p) {
	Plurality_Node *current = p;
	while (current->next != NULL) {
		std::cout << "Plurality: " << current->index << '\n';
		for (auto e : current->elements) {
			std::cout << e.name << '\n';
		}
		current = current->next;
	}
}


Graph get_skeleton_kruskal ( Graph *g ) {

	Graph skeleton;
	skeleton.name = "Kruskals skeleton";
	int skeleton_weight = 0;
	Plurality_Node* head_plurality = new Plurality_Node();
	Plurality_Node* current_plurality = head_plurality;
	skeleton.nodes = g->nodes;
	std::vector<Link> links = g->links;

	// starts array of pluralities
	for (size_t i = 0; i < skeleton.nodes.size(); i++) {
		// filling plurality
		current_plurality->elements.push_back(skeleton.nodes[i]);
		current_plurality->index = i; // test

		// making new plurality, connecting it into previous one, and moving to it
		Plurality_Node *new_plurality = new Plurality_Node();
		current_plurality->next = new_plurality;
		current_plurality = new_plurality;
	}

	print_plurality(head_plurality);

	// sorting liks
	std::sort(links.begin(), links.end(), compare_links);

	int cyclomatic_number = links.size() - skeleton.nodes.size() + 1;

	// printing links for comparison
	for ( Link l : links )
		std::cout << "Link: " << l.name << '\n';

	// for all links in our links array checking if nodes from one plurality
	for (Link l : links) {

		Plurality_Node *first = get_pluraluty(*l.left, head_plurality);
		Plurality_Node *second = get_pluraluty(*l.right, head_plurality);

		// checking if nodes from one plurality statment
		if ( first != second ) {
			include_link(head_plurality, first, second, l, &skeleton);
			skeleton_weight+=l.weight;
		}

		// printing plurality for visualisation of program working
		// print_plurality(head_plurality); // uncomment this if u want to see closer
	}

	print_plurality(head_plurality);

	// printing links for comparison
	for ( Link l : skeleton.links )
		std::cout << "Link: " << l.name << '\n';

	std::cout << "OSTOW WEIGHT: "<< skeleton_weight << '\n';
	return skeleton;
}

// ------------------------ Prim method ------------------------

// Retun lightest link from array (used in combination of get_links_array function)
Link get_lightest ( std::vector<Link> array ) {
	int min_weight = INT_MAX;
	Link res;
	for (Link l : array) {
		if (l.weight < min_weight) {
			res = l;
			min_weight = l.weight;
		}
	}
	return res;
}

// Checking if link is already in graph
bool link_duplecate_protector ( Link link, Graph g ) {
	for (Link l : g.links)
		if (link.name == l.name)
			return true;
	return false;
}

// Retutn new vector without deleted Link
std::vector<Link> remove_link ( std::vector<Link> array, Link link ) {
	std::vector<Link> new_array;
	for (Link l : array) {
		if (l.name == link.name) { continue; }
		new_array.push_back(l);
	}
	return new_array;
}


Graph get_skeleton_prim ( Graph *g ) {

	Graph skeleton;
	skeleton.name = "Prims Skeleton";
	int skeleton_weight = 0;

	std::vector<Link> links = g->links;

	// Finding first link for our skeleton
	Link lightest = get_lightest(g->links);

	skeleton.nodes.push_back(*lightest.left);
	skeleton.nodes.push_back(*lightest.right);
	skeleton.links.push_back(lightest);
	skeleton_weight += lightest.weight;

	// remiving link from observing
	links = remove_link( links, lightest );

	while ( g->nodes.size() != skeleton.nodes.size() ) {

		lightest = get_lightest(get_links_array(skeleton.nodes[0], links));

		for (size_t j = 0; j < skeleton.nodes.size(); j++) {

			// this protection is not so necessary, but it's better to protect
			if (g->nodes.size() == skeleton.nodes.size()) { break; }

			Node n = skeleton.nodes[j];
			Link lite = get_lightest(get_links_array(n, links));

			// find's lightest from the vector before we get link, that connecting graph with new node
			while (duplecate_protector( skeleton.nodes, lite.left->name )
			 	&& duplecate_protector( skeleton.nodes, lite.right->name ) ) {
						// removing link that makes cycle
						links = remove_link( links, lite );
						lite = get_lightest(get_links_array(n, links));

			}

			// check if our light link from current node is lightests in graph
			if (lite.weight < lightest.weight)
				lightest = lite;


		}

		// Statment to check if our new node is right in link or left
		if (duplecate_protector( skeleton.nodes, lightest.right->name )) {
			skeleton.nodes.push_back(*lightest.left);
		} else {
			skeleton.nodes.push_back(*lightest.right);
		}

		std::cout << "\033[0;32mLink: " << lightest.name << " added to Ostov\033[0m" << '\n';
		skeleton.links.push_back(lightest);
		skeleton_weight += lightest.weight;

		// remiving link from observing
		links = remove_link( links, lightest );

	}

	// printing links for comparison
	for ( Link l : skeleton.links )
		std::cout << "Link: " << l.name << '\n';

	std::cout << "OSTOW WEIGHT: "<< skeleton_weight << '\n';
	return skeleton;
}



int main(int argc, char **argv) {

    system("clear");

	bool manual_enter = false;  // make this true if u want manual entering

	Graph my_graph;

    if (manual_enter) {
		if (graph_init(&my_graph)) {
	        printf("\033[0;32m\n--------- GRAPH INITIALIZATION SUCCESS ---------\033[0m\n\n");
	    } else {
	        printf("\033[0;31mINIT ERROR\033[0m\n");
	    }
    } else {
		set_test_graph(&my_graph);
		printf("\033[0;32m\n--------- GRAPH INITIALIZATION SUCCESS ---------\033[0m\n\n");
	}

	print_graph(my_graph);
	printf("\033[0;34m\n--------- KRUSKAL METHOD ---------\033[0m\n\n");
	my_graph = get_skeleton_kruskal ( &my_graph );
	// print_graph(my_graph);
	printf("\033[0;34m\n--------- PRIM METHOD ---------\033[0m\n\n");
	my_graph = get_skeleton_prim ( &my_graph );
	print_graph(my_graph);


    return 0;
}
