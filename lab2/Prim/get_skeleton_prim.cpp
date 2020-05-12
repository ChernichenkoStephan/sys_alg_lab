#include <iostream>
#include <vector>
#include "../Graph/graph.h"

#include "get_skeleton_prim.h"

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

// Skeleton by Prim method function
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
