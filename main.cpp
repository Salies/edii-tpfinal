#include "Graph.h"
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
    if(argc != 5) {
        std::cerr << "\nERRO: falta ou excesso de argumentos. Deve haver exatamente 4 argumentos.";
        return 1;
    }

    std::ifstream infile(argv[1]);
    Graph G(infile);

    std::istringstream ss(argv[3]);
    int s;
    if (!(ss >> s) || !ss.eof()) {
        std::cerr << "ERRO: argumento 3 inválido: " << argv[3] << '\n';
        return 1;
    }

    if(std::string(argv[2]) == "1"){
        G.dijkstra(s);
    }
    else if(std::string(argv[2]) == "2"){
        G.dag_shortest_paths(s);
    }
    else{
        std::cerr << "\nERRO: forma inválida de caminho minimo.";
        return 1;
    }

    std::ofstream outfile(argv[4]);
    std::string txt = G.get_log();
    outfile << txt;

    return 0;
}
