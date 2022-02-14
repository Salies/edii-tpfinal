#include <iostream>
#include "Graph.h"

int main() {
    std::ifstream infile("grafo.txt");
    Graph G(infile);
    G.dijkstra(1);
    std::ifstream infile_dag("grafo2.txt");
    Graph DAG(infile_dag);
    DAG.dag_shortest_paths(0);
    //std::cout << G.to_string();
    //std::cout << DAG.to_string();
    std::cout << G.get_log();
    std::cout << DAG.get_log();
    return 0;
}
