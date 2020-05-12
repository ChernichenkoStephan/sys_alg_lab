#ifndef PRIM_METHOD
#define PRIM_METHOD


// Retun lightest link from array (used in combination of get_links_array function)
Link get_lightest ( std::vector<Link> array );

// Checking if link is already in graph
bool link_duplecate_protector ( Link link, Graph g );

// Retutn new vector without deleted Link
std::vector<Link> remove_link ( std::vector<Link> array, Link link );

// Skeleton by Prim method function
Graph get_skeleton_prim ( Graph *g );


#endif /* end of include guard: PRIM_METHOD */
