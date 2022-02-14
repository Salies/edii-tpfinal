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
    log = "LOG DE PROCESSAMENTO\n";
    while(f >> a >> b >> c){
        addEdge(a, b, c);
    }
}

void Graph::addEdge(int u, int v, int w) {
    //log.append("\naddEdge(" + std::to_string(u) + ", " + std::to_string(v) + ", " + std::to_string(w) + ")");
    if(V.find(u) == V.end())
        V.insert({u, new Vertex()});
    if(V.find(v) == V.end())
        V.insert({v, new Vertex()});
    V.at(u)->adj.insert({v, w});
}

void Graph::initialize_single_source(int s){
    log.append("\ninitialize_single_source(" + std::to_string(s) + ")");
    for (std::unordered_map<int, Vertex*>::iterator v = V.begin(); v != V.end(); v++) {
        v->second->d = std::numeric_limits<int>::max();
        v->second->pi = -1; // a indexação de um vértice nunca é negativa, logo pode-se usar -1 como "nulo"
    }
    V.at(s)->d = 0;
    log_graph();
}

int Graph::extract_min(std::unordered_map<int, Vertex*> *queue) {
    log.append("\nextract_min(&Q)");
    std::unordered_map<int, Vertex*>::iterator min = queue->begin();
    for (std::unordered_map<int, Vertex*>::iterator v = ++queue->begin(); v != queue->end(); v++){
        if(v->second->d < min->second->d)
            min = v;
    }
    queue->erase(min->first);
    return min->first;
}

void Graph::relax(Vertex *u, int uid, Vertex *v, int vid, int w) {
    log.append("\nrelax(" + std::to_string(uid) + ", " + std::to_string(vid) + ", " + std::to_string(w) + ")");
    // Verificação para evitar um possível overflow com u.d + w > max
    // prevenindo a função de operar corretamente
    if(u->d == std::numeric_limits<int>::max() && w >= 0) return;
    if(v->d > (u->d + w)){
        v->d = u->d + w;
        v->pi = uid;
    }
    log_graph();
}

void Graph::dijkstra(int s) {
    log.append("\ndijkstra(" + std::to_string(s) + ")");
    initialize_single_source(s);
    std::unordered_map<int, Vertex*> Q(V);
    // Abordagem para preservar o uid
    // para que v.pi possa ser exibido depois
    int uid;
    Vertex *u;
    log_q(&Q);
    while(!Q.empty()){
        uid = extract_min(&Q);
        log_q(&Q);
        u = V.at(uid);
        for (std::unordered_map<int, int>::iterator v = u->adj.begin(); v != u->adj.end(); v++) {
            relax(u, uid, V.at(v->first), v->first, v->second);
        }
    }
}

void Graph::dfs_visit(int uid, Vertex *u, std::vector<int> *f) {
    log.append("\ndfs_visit(" + std::to_string(uid) + ")");
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
    log.append("\ndfs()");
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

std::vector<int> Graph::topological_sort() {
    log.append("\ntopological_sort()");
    std::vector<int> d = dfs();
    std::reverse(d.begin(), d.end());
    return d;
}

void Graph::dag_shortest_paths(int s) {
    log.append("\ndag_shortest_paths(" + std::to_string(s) + ")");
    std::vector<int> tps = topological_sort();
    initialize_single_source(s);
    Vertex *u;
    for(int uid: tps){
        u = V.at(uid);
        for (std::unordered_map<int, int>::iterator v = u->adj.begin(); v != u->adj.end(); v++) {
            relax(u, uid, V.at(v->first), v->first, v->second);
        }
    }
}

void Graph::log_graph() {
    log.append("\n---------------------------------\n");
    for (std::unordered_map<int, Vertex*>::iterator v = V.begin(); v != V.end(); v++) {
        log.append(std::to_string(v->first) + " | d: " +
        (v->second->d == std::numeric_limits<int>::max() ? "inf" : std::to_string(v->second->d)) +
        " | pi: " + (v->second->pi == -1 ? "null" : std::to_string(v->second->pi)) + "\n");
    }
    log.append("---------------------------------");
}

std::string Graph::get_log() {
    // Imprimindo os menores caminhos
    Vertex *v;
    std::string path;
    log.append("\n\nCaminhos gerados:\n");
    for (std::unordered_map<int, Vertex*>::iterator vit = V.begin(); vit != V.end(); vit++) {
        path = "";
        v = vit->second;
        path.append(std::to_string(vit->first) + " ");
        while(v->pi != -1){
            path.insert(0, std::to_string(v->pi) + " -> ");
            v = V.at(v->pi);
        }
        path.append("(peso " + std::to_string(vit->second->d) +  ")\n");
        path.insert(0, std::to_string(vit->first) + ": ");
        log.append(path);
    }
    log.append("\nArquivo produzido pelo dssp\nDaniel Serezane <daniel.serezane@unesp.br>");
    return log;
}

void Graph::log_q(std::unordered_map<int, Vertex *> *queue) {
    log.append("\nQ:");
    for (std::unordered_map<int, Vertex*>::iterator it = queue->begin(); it != queue->end(); it++) {
        log.append(" " + std::to_string(it->first));
    }
}