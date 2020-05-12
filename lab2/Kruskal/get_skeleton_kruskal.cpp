#include <iostream>
#include <vector>
#include "../Graph/graph.h"

#include "get_skeleton_kruskal.h"


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
