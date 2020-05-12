#include <iostream>
#include <vector>

#include "binary_tree_search.h"

std::string get_string_weight( std::vector<int> w ) {
    std::string res = "";
    for (int num : w) {
        res += std::to_string(num) + " ";
    }
    return res;
}


int compear( std::vector<int> n1_weight, std::vector<int> n2_weight ) {

    for ( unsigned short i = 0; i < n1_weight.size(); i++ ) {
        if (n1_weight[i] > n2_weight[i]) {
            return 1;
        } else if(n1_weight[i] < n2_weight[i]) {
            return -1;
        }
    }
    return 0;

}

std::vector<int> get_weight( std::string weight_str ) {
    int num = 999;
    std::vector<int> res;

    try {
       num = stoi(weight_str);
    }
    catch (std::invalid_argument) {
        num = INT_MIN;
    }

    if ( num == INT_MIN ) {
        for ( char c : weight_str ) {
            res.push_back(c);
        }
    } else {
        res.push_back(num);
    }

    return res;
}


bool enter_node( BinNode *node ) {

    printf("\nBinNode name: ");

    std::cin >> node->name;
    if (node->name == "_") { return false; }

    node->weight = get_weight(node->name);

    std::cout << "New node name: " << node->name << " New node weight: " << get_string_weight(node->weight) << '\n';

    return true;
}

bool init_node( BinNode *node ) {

    bool res = false;

    printf("\033[0;34m");
    std::cout << "\n\n--------- " << node->name << " NODES CHILDREN INITIALIZATION ---------" << '\n';
    printf("\033[0m");

    for (unsigned short i = 0; i < 2 ; i++) {

        BinNode *new_node = new BinNode;

        if (!enter_node( new_node )) {
            free(new_node);
            printf("\033[0;32mBinNode creation canceled. Memory cleaned.\033[0m\n");
            continue;
         }

         // Checking if first node was lighter
         if ( i == 1) {

             if (compear( node->children[0]->weight, new_node->weight ) == 1) {

                 std::cout << "\033[0;31m\nSecond child shuld be heavier than first\033[0m\n"
                           << "Fist w8: " << node->children[0]->weight[0] << " name: " << node->children[0]->name
                           << "\nSecond w8: " << new_node->weight[0] << " name: " << new_node->name << '\n';
                 i--;
                 free(new_node);
             }
         }

        node->children.push_back(new_node);
        printf("\033[0;32mBinNode created\033[0m\n");
        res = true;

    }

    for (unsigned short i = 0; i < node->children.size() ; i++) {
        init_node( node->children[i] );
    }

    return res;

}

bool init_tree( Tree *tree ) {

    BinNode *root = new BinNode;
    tree->root = root;

    printf("\nTree name: ");
    std::cin >> tree->name;
    if (tree->name == "_") { return false; }

    printf("\nStart from root:\n");
    if (!enter_node( root )) { return false; }

    printf("\033[0;34m\n\n--------- ROOT NODES CHILDREN INITIALIZATION ---------\033[0m");
    if (!init_node( root )) { return false; }

     return true;

}

bool node_print( BinNode* node, int level ) {

    if (!node) {
        level--;
        return false;
     }

     std::string indentation = "";
     for (int i = 0; i < level; i++) {
         indentation += "\t";
     }
    std::cout << '\n' << indentation << "---------- BinNode: " << node->name
                                             << " weight: " << get_string_weight(node->weight) << " ----------\n"
                                                            << indentation << "Children nodes:" << '\n';

    level++;
    for (BinNode *node : node->children) {
        node_print( node, level );
    }

    return true;
}

bool tree_print( Tree *tree ) {

    printf("\033[0;34m\n\n--------- TREE PRINT ---------\033[0m\n");
    std::cout << "Name: " << tree->name << '\n';
    std::cout << "Size: " << tree->size << '\n';

    return node_print( tree->root, 1 );

}

bool delete_node( BinNode* node ) {

    if (!node) { return false; }

    for (BinNode *node : node->children) {
        delete_node( node );
    }

    // std::cout << "---------- BinNode: " << node->name << node->weight.size() << " Deleted ----------\n";
    free(node);

    return true;

}

bool clear_memory( Tree* tree ) {

    if (!tree) { return false; }

    if (!delete_node(tree->root)) { return false; }

    // std::cout << "---------- BinNode: " << tree->name << tree->size << " Deleted ----------\n";
    free(tree);

    return true;

}

/*

It is required to find the SAG key from the binary tree.
When viewed from the root of the tree, it can be seen that the first
the letter of the Latin alphabet the name SAG is more than САР.
Therefore, further search will be carried out
in the right branch. This word is more than PIS - go right again;
it is less than TAU - go left; it's smaller
than SCO, and we get to node 8. Thus,
SAG name must be in node 8.

*/

/*

T:
            A
      B            C
    D    E      F    G
H    I J   K   L  M N  O


T2:
        1
  2          3
4   5     6    7


BinNode search(x : BinNode, k : T):
   if x == null or k == x.key
      return x
   if k < x.key
      return search(x.left, k)
   else
      return search(x.right, k)


*/

BinNode* binary_tree_search( Tree *tree, std::string key ) {

    BinNode *node = tree->root;

    std::vector<int> key_weight = get_weight( key );

    int diff = compear(key_weight, node->weight);

    for (unsigned short i = 0; i < 1000; i++) {

        std::cout << "key_weight:" << get_string_weight(key_weight) << "|node->weight:" << get_string_weight(node->weight) << '\n';
        std::cout << "diff:" << diff << '\n';
        if ( diff == 0 ) {
            std::cout << "\033[0;32mKEY FOUND\033[0m" << '\n';
            return node;
        } else if ( diff == 1 ) {
            node = node->children[node->children.size() - 1];
            std::cout << "Go to node: "<< node->name << '\n';
        } else if ( diff == -1 ) {
            node = node->children[0];
            std::cout << "Go to node: "<< node->name << '\n';
        }

        diff = compear(key_weight, node->weight);

    }

    std::cout << "\033[0;31mKEY NOT FOUND\033[0m" << '\n';
    return NULL;

}
