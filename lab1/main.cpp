#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstdint>
#include <vector>
#include <ctime>
#include <chrono>

#define FIRST_INDEX 1
#define END_INDEX argc - 1
#define ARRAY_SIZE (argc - 1)


struct Node {
    std::string name;
    std::vector<Node> linked_nodes;
};

struct Graph {
    std::string name;
    std::vector<Node> nodes;
};


unsigned int* get_nodes_links_array(Graph graph) {

    unsigned int *links_array = (unsigned int*)malloc(sizeof(*links_array) * graph.nodes.size());
    unsigned int index = 0;

    for ( Node n : graph.nodes ) {
        links_array[index] = n.linked_nodes.size();
        index++;
    }

    return links_array;

}

Node* get_node_by_name(std::string name, Graph *g) {
    for (unsigned short i = 0; i < g->nodes.size(); i++) {
        Node *n = &(g->nodes[i]);
        if ( n->name == name) {
            return n;
        }
    }
    return NULL;
}

bool duplecate_protector(std::vector<Node> nodes, std::string name) {
    for (unsigned short i = 0; i < nodes.size(); i++) {
        if (nodes[i].name == name) {
            return true;
        }
    }
    return false;
}


void print_graph(Graph g) {
    std::cout << "\n---------- Graph: " << g.name << " ----------\n Graph nodes:" << '\n';
    if (g.nodes.empty()) { printf("\tempty\n\n\n"); }
    for (Node n : g.nodes) {
        std::cout << "\n\t---------- Node: " << n.name << " ----------" <<"\n\tlinked nodes of node:\n";
        if (n.linked_nodes.empty()) { printf("\tempty\n"); }
        for (Node ln : n.linked_nodes) {
            std::cout << "\t" << ln.name <<'\n';
        }
        printf("\t------------------------------\n");
    }
}




bool node_init(std::string node_name, Graph *g, Node *node) {

    if (duplecate_protector(g->nodes, node_name)) { return false; }

    node->name = node_name;

    std::string entered_name;

    unsigned short index = 1;
    std::cout << "Enter " << index << " node name (for quit \"_\") from graph: "
              << g->name << '\n';
    print_graph(*g);

    printf("\nNode name: ");
    std::cin >> entered_name;

    while (entered_name != "_") {

        Node *node_to_add = get_node_by_name(entered_name, g);
        if (node_to_add) {
            node->linked_nodes.push_back(*node_to_add);
            printf("\033[0;32mNode added\033[0m\n");
        } else {
            printf("\033[0;31mError node not exists\033[0m\n");
        }

        index++;
        std::cout << "Enter " << index << " node name (for quit \"_\") from graph: "
                  << g->name << '\n';
        if (index % 10 == 0) { print_graph(*g); }
        std::cin >> entered_name;

    }

    return true;
}

Graph graph_init() {

    Graph my_graph;

    std::string entered_name;

    std::cout << "Enter graphs name" << '\n';
    std::cin >> my_graph.name;

    printf("\n============================\n");
    unsigned short index = 1;
    std::cout << "Enter " << index << " node name" << '\n';
    std::cin >> entered_name;

    while (entered_name != "_") {
        Node node;
        if (node_init(entered_name, &my_graph, &node)) {
            my_graph.nodes.push_back(node);
        } else {
            printf("\033[0;31mError node already exists\033[0m\n");
        }
        printf("\033[0;32mNode created\033[0m\n");

        printf("\n============================\n");
        index++;
        std::cout << "Enter " << index << " node (for quit \"_\")" << '\n';
        std::cin >> entered_name;

    }

    return my_graph;

}


int main(int argc, char **argv) {

    std::cout << "/* Start */" << '\n';

    Graph g = graph_init();

    print_graph(g);

    std::cout << "/* End */" << '\n';

    return 0;
}

/*

Укрупненный алгоритм топологической сортировки выглядит следующим образом:
п. 1. Инициализация массива A.
п. 2. Ввод исходных данных вида М  K.
п. 3. Подсчет количества предшественников и формирование спиков преемников.
п. 4. Организация списка Q и задание его хвоста R.
п. 5. L:= 0. { Количество элементов, выведенных на печать }
п. 6. Если Q = 0, то переход к п. 13.
п. 7. Извлечение и печать первого элемента списка Q.
п. 8. L:=L+1.
п. 9. Если L = max, то переход к п. 14.
п. 10. Просмотр преемников элемента с номером Q, пересчет числа предшественников этих элементов. Если у какого-либо элемента P чис- ло предшественников стало равным нулю, то включить данный элемент в список Q с конца: A[R].data.N:=P; R:=P.
п. 11. п. 12. п. 13. п. 14.
Перестроение начала списка: Q:=A[Q].data.N. Переход к п. 6.
Вывод: «Полное решение не существует». Конец работы.

*/
