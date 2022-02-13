//
// Created by danie on 04/02/2022.
//

#include "Graph.h"
#include <string>
#include <vector>
#include <queue>
#include <limits>

#include <iostream>

Graph::Graph(std::istream &f){
    int a, b, c; // variáveis para receber os valores
    f >> a;
    this->n = a;
    while(f >> a >> b >> c){
        this->addEdge(a, b, c);
    }
}

void Graph::addEdge(int u, int v, int w) {
    if(V.find(u) == V.end())
        V.insert({u, new Vertex(u)});
    if(V.find(v) == V.end())
        V.insert({v, new Vertex(v)});
    V.at(u)->adj.insert({v, w});
}

void Graph::initialize_single_source(int s){
    for (std::unordered_map<int, Vertex*>::iterator v = V.begin(); v != V.end(); v++) {
        v->second->d = std::numeric_limits<int>::max();
        v->second->pi = nullptr; // a indexação de um vértice nunca é negativa, logo pode-se usar -1 como "nulo"
    }
    V.at(s)->d = 0;
}

Vertex* Graph::extract_min(std::unordered_map<int, Vertex*> *queue) {
    std::unordered_map<int, Vertex*>::iterator min = queue->begin();
    for (std::unordered_map<int, Vertex*>::iterator v = ++queue->begin(); v != queue->end(); v++)
        if(v->second->d < min->second->d)
            min = v;
    queue->erase(min->first);
    std::cout << "\n" << min->first << "\n";
    return min->second;
}

void Graph::relax(Vertex *u, Vertex *v, int w) {
    if(v->d > (u->d + w)){
        v->d = u->d + w;
        v->pi = u;
    }
}

void Graph::dijkstra(int s) {
    initialize_single_source(s);
    std::unordered_map<int, Vertex*> Q(V);
    Vertex *u;
    while(!Q.empty()){
        u = extract_min(&Q);
        for (std::unordered_map<int, int>::iterator v = u->adj.begin(); v != u->adj.end(); v++) {
            relax(u, V.at(v->first), v->second);
        }
    }
}

std::string Graph::to_string() {
    std::string res = "Número de vértices: " + std::to_string(this->n) + "\n";

    /*for (std::map<int, Vertex*>::iterator it = V->begin(); it != V->end(); it++) {
        for (std::map<int, int>::iterator it_s = it->second->adj()->begin(); it_s != it->second->adj()->end(); it_s++) {
            res.append(std::to_string(it->first) + "->" + std::to_string(it_s->first) + ", w: " + std::to_string(it_s->second) + "\n");
        }
    }*/

    return res;
}