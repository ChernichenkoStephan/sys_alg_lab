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
    std::vector<Node> children;

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
    Node* root;
    int size = 0;
};

bool enter_node( Node *node ) {

    printf("\nNode name: ");
    std::cin >> node->name;
    if (node->name == "_") { return false; }

    int num;

    try {
       int num = stoi(node->name);
    }
    catch (std::invalid_argument) {
        num = INT_MIN;
    }

    if ( num == INT_MIN ) {
        for ( char c : node->name ) {
            node->weight.push_back(c);
            // node->number = (int)char;
        }
    } else {
        node->weight.push_back(num);
    }
    printf("\033[0;31m--------------------- Test point 0 ---------------------\033[0m\n");
    std::cout << "New node name: " << node->name << " New node weight size: " << node->weight.size() << '\n';

    return true;
}

bool init_node( Node *node ) {

    Node new_node;
    bool res = false;

    for (unsigned short i = 0; i < 2 ; i++) {

        if (!enter_node( &new_node )) {
            printf("\033[0;31m--------------------- Test point 1 ---------------------\033[0m\n");
            continue;
         }

        printf("\033[0;31m--------------------- Test point 2 ---------------------\033[0m\n");
        std::cout << "New node name: " << new_node.name << " New node weight size: " << new_node.weight.size() << '\n';

        node->children.push_back(new_node);
        printf("\033[0;32mNode created\033[0m\n");
        res = true;

        new_node = Node();

    }

    for (unsigned short i = 0; i < node->children.size() ; i++) {
        init_node( &(node->children[i]) );
    }

    return res;

}

bool init_tree( Tree *tree ) {

    Node root;
    tree->root = &root;

    printf("\nTree name: ");
    std::cin >> tree->name;
    if (tree->name == "_") { return false; }

    if (!enter_node( &root )) { return false; }
    
    if (!init_node( &root )) { return false; }

     return true;

}

bool node_print( Node* node ) {

    std::cout << "Name: " << node->name << '\n';
    std::cout << "Weight size: " << node->weight.size() << '\n';

    for (Node node : node->children) {
        node_print( &node );
    }

}

bool tree_print( Tree *tree ) {

    std::cout << "Name: " << tree->name << '\n';
    std::cout << "Size: " << tree->size << '\n';

    return node_print( tree->root );

}




int main(int argc, char **argv) {

    Tree my_tree;

    printf("\033[0;34m--------- TREE INITIALIZATION ---------\033[0m\n");

    if (!init_tree( &my_tree )) {
        printf("\033[0;31mTree init error\033[0m\n");
    }

    // if (!tree_print( &my_tree )) {
    //     printf("\033[0;31mTree print error\033[0m\n");
    // }

    // delete
    return 0;
}
