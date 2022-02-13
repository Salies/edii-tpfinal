#include <iostream>
#include <fstream>

#include "Graph.h"

int main() {
    std::ifstream infile("grafo.txt");
    Graph *G = new Graph(infile);
    //std::cout << G->to_string();
    G->dijkstra(1);

    return 0;
}
