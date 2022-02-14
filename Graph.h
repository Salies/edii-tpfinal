//
// Created by danie on 04/02/2022.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <unordered_map>
#include <vector>

// Vertex.f não é definido pois os tempos de finalização
// são irrelevantes para os algoritmos pertinentes ao trabalho
struct Vertex {
    int pi; // predecessor no menor caminho
    int d; // distância da fonte até o vértice
    int color; // "cor" do vértice, usada na DFS
    std::unordered_map<int, int> adj; // vértices adjacentes <chave, peso>
    Vertex() : pi(-1), d(-1), color(-1){} // inicializa apenas por convenção
};

class Graph {
public:
    explicit Graph(std::istream &f);
    ~Graph()= default;;
    void dijkstra(int s);
    void dag_shortest_paths(int s);
    std::string get_log();
protected:
    int n; // número de vértices
    std::unordered_map<int, Vertex*> V;
    std::string log; // log de operações, a ser impresso
    enum Color {white, gray, black};
    void addEdge(int u, int v, int w);
    // Funções auxiliares
    void initialize_single_source(int s);
    int extract_min(std::unordered_map<int, Vertex*> *queue);
    void relax(Vertex *u, int uid, Vertex *v, int vid, int w);
    // Implementação parcial (faltando armazenar os tempos) de dfs
    // apenaspara criar a topological_sort
    std::vector<int> dfs();
    void dfs_visit(int uid, Vertex *u, std::vector<int> *f);
    std::vector<int> topological_sort();
    void log_graph(); // Imprime informações básicas sobre o grafo
    // Função de impressão da fila Q, apenas para fins de log
    void log_q(std::unordered_map<int, Vertex*> *queue);
};


#endif //GRAPH_H
