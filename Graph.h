//
// Daniel Serezane <daniel.serezane@unesp.br>
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
    // Funções de processamento
    void dijkstra(int s);
    void dag_shortest_paths(int s);
    // Retorna o log de processamento
    std::string get_log();
protected:
    int n; // número de vértices
    std::unordered_map<int, Vertex*> V; // mapa de vértices
    std::string log; // log de operações, a ser impresso
    enum Color {white, gray, black}; // cores de vértices
    // Adiciona um vértice (chave u), predecessor de outro (chave v), aresta de peso w.
    void addEdge(int u, int v, int w);
    // Inicializa o processamento a partir da origem s.
    void initialize_single_source(int s);
    // Retira de queue o vértice com menor v.d .
    int extract_min(std::unordered_map<int, Vertex*> *queue);
    // Relaxa a aresta (u, v) com o peso w.
    void relax(Vertex *u, int uid, Vertex *v, int vid, int w);
    // Implementação parcial (não armazena os tempos) de dfs
    // apenas para criar a topological_sort.
    std::vector<int> dfs();
    // Função de visita para dfs, usada por dfs();
    void dfs_visit(int uid, Vertex *u, std::vector<int> *f);
    // Retorna as chaves dos vértices do grafo, topologicamente ordenados.
    std::vector<int> topological_sort();
    // Imprime informações básicas sobre o grafo.
    void log_graph();
    // Função de impressão da fila Q, apenas para fins de log.
    void log_q(std::unordered_map<int, Vertex*> *queue);
};

#endif //GRAPH_H
