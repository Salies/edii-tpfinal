#include <iostream>
#include <fstream>

#include "Graph.h"

int main() {
    std::ifstream infile("grafo.txt");
    Graph *G = new Graph();
    G->buildFromFile(infile);
    std::cout << "\n" << G->getNVertex() << "\n";

    return 0;
}
