//
// Created by danie on 04/02/2022.
//

#include "Graph.h"
#include <string>
#include <vector>
#include <limits>

Graph::Graph(std::istream &f){
    int a, b, c; // variáveis para receber os valores
    f >> a;
    n = a;
    while(f >> a >> b >> c){
        addEdge(a, b, c);
    }
}

void Graph::addEdge(int u, int v, int w) {
    if(V.find(u) == V.end())
        V.insert({u, new Vertex()});
    if(V.find(v) == V.end())
        V.insert({v, new Vertex()});
    V.at(u)->adj.insert({v, w});
}

void Graph::initialize_single_source(int s){
    for (std::unordered_map<int, Vertex*>::iterator v = V.begin(); v != V.end(); v++) {
        v->second->d = std::numeric_limits<int>::max();
        v->second->pi = -1; // a indexação de um vértice nunca é negativa, logo pode-se usar -1 como "nulo"
    }
    V.at(s)->d = 0;
}

int Graph::extract_min(std::unordered_map<int, Vertex*> *queue) {
    std::unordered_map<int, Vertex*>::iterator min = queue->begin();
    for (std::unordered_map<int, Vertex*>::iterator v = ++queue->begin(); v != queue->end(); v++){
        if(v->second->d < min->second->d)
            min = v;
    }
    queue->erase(min->first);
    return min->first;
}

void Graph::relax(Vertex *u, int uid, Vertex *v, int w) {
    if(v->d > (u->d + w)){
        v->d = u->d + w;
        v->pi = uid;
    }
}

void Graph::dijkstra(int s) {
    initialize_single_source(s);
    std::unordered_map<int, Vertex*> Q(V);
    // Abordagem para preservar o uid
    // para que v.pi possa ser exibido depois
    int uid;
    Vertex *u;
    while(!Q.empty()){
        uid = extract_min(&Q);
        u = V.at(uid);
        for (std::unordered_map<int, int>::iterator v = u->adj.begin(); v != u->adj.end(); v++) {
            relax(u, uid, V.at(v->first), v->second);
        }
    }
}

void Graph::dfs_visit(int uid, Vertex *u, std::vector<int> *f) {
    u->color = gray;
    Vertex *v;
    for (std::unordered_map<int, int>::iterator vit = u->adj.begin(); vit != u->adj.end(); vit++) {
        v = V.at(vit->first);
        if(v->color == white){
            v->pi = uid;
            dfs_visit(vit->first, v, f);
        }
    }
    u->color = black;
    f->push_back(uid);
}

std::vector<int> Graph::dfs() {
    std::vector<int> finish_times = {};
    for (std::unordered_map<int, Vertex*>::iterator u = V.begin(); u != V.end(); u++) {
        u->second->color = white;
        u->second->pi = -1;
    }
    for (std::unordered_map<int, Vertex*>::iterator u = V.begin(); u != V.end(); u++) {
        if(u->second->color == white)
            dfs_visit(u->first, u->second, &finish_times);
    }
    return finish_times;
}

std::vector<int> Graph::topsort() {
    std::vector<int> d = dfs();
    std::reverse(d.begin(), d.end());
    return d;
}

void Graph::dag_shortest_paths(int s) {
    std::vector<int> tps = topsort();
    initialize_single_source(s);
    Vertex *u;
    for(int uid: tps){
        u = V.at(uid);
        for (std::unordered_map<int, int>::iterator v = u->adj.begin(); v != u->adj.end(); v++) {
            relax(u, uid, V.at(v->first), v->second);
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