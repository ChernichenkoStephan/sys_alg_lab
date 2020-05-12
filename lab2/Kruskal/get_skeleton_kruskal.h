#ifndef KRUSKAL
#define KRUSKAL

struct Plurality_Node {
	int index;
	std::vector<Node> elements;
	Plurality_Node* next;
};

// returns pularlity from stack
Plurality_Node* get_pluraluty ( Node element, Plurality_Node *head );
// deleting pularlity from stack
bool delete_plurality ( Plurality_Node *p, Plurality_Node *head );
// adding link in Kurskal method
void include_link( Plurality_Node *head, Plurality_Node *first, Plurality_Node *second, Link link, Graph *graph );
// Printing all plurality stack function
void print_plurality(Plurality_Node *p);
// Find skeleton by Kruskal method
Graph get_skeleton_kruskal ( Graph *g );

#endif /* end of include guard: KRUSKAL */
