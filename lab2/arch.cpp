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
    std::vector<Node*> children;

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


bool enter_node( Node *node ) {

    printf("\nNode name: ");

    std::cin >> node->name;
    if (node->name == "_") { return false; }

    node->weight = get_weight(node->name);

    std::cout << "New node name: " << node->name << " New node weight: " << get_string_weight(node->weight) << '\n';

    return true;
}

bool init_node( Node *node ) {

    bool res = false;

    printf("\033[0;34m");
    std::cout << "\n\n--------- " << node->name << " NODES CHILDREN INITIALIZATION ---------" << '\n';
    printf("\033[0m");

    for (unsigned short i = 0; i < 2 ; i++) {

        Node *new_node = new Node;

        if (!enter_node( new_node )) {
            free(new_node);
            printf("\033[0;32mNode creation canceled. Memory cleaned.\033[0m\n");
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
        printf("\033[0;32mNode created\033[0m\n");
        res = true;

    }

    for (unsigned short i = 0; i < node->children.size() ; i++) {
        init_node( node->children[i] );
    }

    return res;

}

bool init_tree( Tree *tree ) {

    Node *root = new Node;
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

bool node_print( Node* node, int level ) {

    if (!node) {
        level--;
        return false;
     }

     std::string indentation = "";
     for (int i = 0; i < level; i++) {
         indentation += "\t";
     }
    std::cout << '\n' << indentation << "---------- Node: " << node->name
                                             << " weight: " << get_string_weight(node->weight) << " ----------\n"
                                                            << indentation << "Children nodes:" << '\n';

    level++;
    for (Node *node : node->children) {
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

bool delete_node( Node* node ) {

    if (!node) { return false; }

    for (Node *node : node->children) {
        delete_node( node );
    }

    // std::cout << "---------- Node: " << node->name << node->weight.size() << " Deleted ----------\n";
    free(node);

    return true;

}

bool clear_memory( Tree* tree ) {

    if (!tree) { return false; }

    if (!delete_node(tree->root)) { return false; }

    // std::cout << "---------- Node: " << tree->name << tree->size << " Deleted ----------\n";
    free(tree);

    return true;

}

/*

Требуется по бинарному дереву отыскать ключ SAG.
При просмотре от корня дерева видно, что по первой
букве латинского алфави- та название SAG больше чем САР.
Следовательно, дальнейший поиск будем осуществлять
в правой ветви. Это слово больше, чем PIS - снова идем вправо;
 оно меньше, чем TAU - идем влево; оно меньше,
 чем SCO, и попадаем в узел 8. Таким образом,
 название SAG должно находиться в узле 8.

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


Node search(x : Node, k : T):
   if x == null or k == x.key
      return x
   if k < x.key
      return search(x.left, k)
   else
      return search(x.right, k)


*/

Node* binary_tree_search( Tree *tree, std::string key ) {

    Node *node = tree->root;

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



int main(int argc, char **argv) {

    system("clear");

    Tree *my_tree = new Tree;

    printf("\033[0;34m--------- TREE INITIALIZATION ---------\033[0m\n");


    if (!init_tree( my_tree )) {
        printf("\033[0;31mTree init error\033[0m\n");
    }

    if (!tree_print( my_tree )) {
        printf("\033[0;31mTree print error\033[0m\n");
    }

    std::string key;

    std::cout << "Enter the key: ";
    std::cin >> key;

    binary_tree_search( my_tree, key );

    if (!clear_memory( my_tree )) {
        printf("\033[0;31mTree was empty, or was not exist.\033[0m\n");
    } else {
        printf("\033[0;32mMemory cleaned\033[0m\n");
    }

    return 0;
}


/*

// пример функции обработки, которая выводит индекс начала найденного образца
int f(size_t i)
{
    printf("%d\n",i);
    return 1;
}
// str строка поиска.
// obr образец, который ищем.
// pi массив длин префиксов для образца (минимум  сколько символов в образце).
// int f(size_t i) когда образец найден, вызывается эта функция,
// ей передается индекс начала найденного в str образца.
// функция возвращает 0, если надо прекратить поиск и 1, если надо продолжить.
void prefix_find (char *str, char *obr, size_t *pi, int (*f)(size_t))
{
     pi[0]=0;     // в i-м элементе (его индекс i-1) количество совпавших
                  // символов в начале образца и в конце подстроки длины i.
                  // p[0]=0 всегда, p[1]=1, если начинается с двух одинаковых
     size_t l;    // будет длина образца
     // заполняем массив длин префиксов для образца
     for (l=1; obr[l]; ++l)
     {
        size_t j = pi[l-1];
        while ((j > 0) && (obr[l] != obr[j])) // не равны
            j = pi[j-1];	         // берем ранее рассчитанное значение (начиная с максимально возможных)
        if (obr[l] == obr[j])      // равны
            ++j;
        pi[l] = j;
     }
     size_t j=0; // количество совпавших символов, оно же индекс сравниваемого
     // символа в образце. В строке сравниваемый символ будет иметь индекс i
     for (size_t i=0; str[i]; ++i)
     {
         while ((j > 0) && (str[i] != obr[j]))
// Очередной символ строки не совпал с символом в образце. Сдвигаем образец,
// причем точно знаем, что первые j символов образца совпали с символами строки
// и надо сравнить j+1й символ образца (его индекс j) с i+1м символом строки.
           j = pi[j-1];    // если j=0, то достигли начала образца и цикл следует прервать

       if (str[i] == obr[j]) // есть совпадение очередного символа
           ++j;              // увеличиваем длину совпавшего фрагмента на 1
       if (j==l)
           if (!f(i-l+1)) // образец найден, вызовем функцию обработки
                 return;  // и выйдем из процедуры, если она вернет 0.
    }
}
*/
