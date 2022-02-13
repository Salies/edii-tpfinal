//
// Created by danie on 04/02/2022.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <unordered_map>

struct Vertex {
    int val;
    Vertex *pi;
    int d;
    std::unordered_map<int, int> adj;
    Vertex(const int& v) : val(v), d(-1) {}
};

class Graph {
public:
    Graph(std::istream &f);
    ~Graph(){};
    std::string to_string(); // Imprime informações básicas sobre o grafo
    void dijkstra(int s);
    void dag_shortest_paths();
protected:
    int n; // número de vértices
    std::unordered_map<int, Vertex*> V;
    void addEdge(int u, int v, int w);
    // Funções auxiliares
    void initialize_single_source(int s);
    Vertex* extract_min(std::unordered_map<int, Vertex*> *queue);
    void relax(Vertex *u, Vertex *v, int w);
};


#endif //GRAPH_H
