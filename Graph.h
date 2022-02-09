//
// Created by danie on 04/02/2022.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <fstream>

typedef struct vertex {
   int value; // dado armazenado no vértice
   struct vertex *pi; // pai do vértice
   int d; // distância da fonte
} vertex;

typedef struct{
    vertex *u; // vértice inicial (dígrafos)
    vertex *v; // vértice final (dígrafos)
    int w; // peso
} edge;

class Graph {
public:
    Graph();
    ~Graph(){};
    // Funções públicas caso deseje-se construir um grafo
    // manualmente. Para efeito deste trabalho, contudo,
    // são utilizadas apenas dentro desta classe.
    void addVertex(vertex v);
    void addEdge(edge e);
    int getNVertex();
    void buildFromFile(std::istream &f);
private:
    int nVertex; // número de vértices
    std::list<vertex> V;
    std::list<edge> E;
};


#endif //GRAPH_H
