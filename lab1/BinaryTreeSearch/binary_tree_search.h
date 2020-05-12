#ifndef BINARY_TREE_SEARCH
#define BINARY_TREE_SEARCH

struct BinNode {

    std::string name;
    std::vector<BinNode*> children;

    /*

    For numbers:
    ( name1 = 5 )   =>   ( weight = [5] )
    ( name2 = 157433 )   =>   ( weight = [157433] )

    For words:
    ( name1 = a )   =>   ( weight = [97] )
    ( name2 = aa )   =>   ( weight = [97, 97] )
    ( name3 = aaa )   =>   ( weight = [97, 97, 97] )
    ( name4 = abc )   =>   ( weight = [97, 98, 99] )

    name1 > name2 > name3 > name4

    */

    std::vector<int> weight;

};

struct Tree {

    std::string name;
    BinNode* root;
    int size = 0;
};


std::string get_string_weight( std::vector<int> w );
int compear( std::vector<int> n1_weight, std::vector<int> n2_weight );
std::vector<int> get_weight( std::string weight_str );
bool enter_node( BinNode *node );
bool init_node( BinNode *node );
bool init_tree( Tree *tree );
bool node_print( BinNode* node, int level );
bool tree_print( Tree *tree );
bool delete_node( BinNode* node );
bool clear_memory( Tree* tree );
BinNode* binary_tree_search( Tree *tree, std::string key );


#endif /* end of include guard: BINARY_TREE_SEARCH */
