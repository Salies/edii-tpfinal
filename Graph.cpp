//
// Created by danie on 04/02/2022.
//

#include "Graph.h"
#include <sstream>
#include <string>

#include <iostream>

Graph::Graph(){
    this->V = {};
    this->E = {};
}

void Graph::addVertex(vertex v){

};

void Graph::addEdge(edge e){

};

int Graph::getNVertex(){
    return nVertex;
};

void Graph::buildFromFile(std::istream &f){
    std::string line;
    // inteiros para receber os números lidos
    int a, b, c;
    // último valor adicionado (para saber se é valor novo ou não)
    // -1 é um bom valor inicial para lastVertex.v
    // pois sabe-se que os vértices têm apenas valores inteiros positivos
    // TODO: colocar isso nas documentações/exemplos (coisa da ordem)
    vertex aux_v;
    aux_v.value = -1;
    vertex *lastVertex = &aux_v;
    // pega a primeira linha (número de vértices)
    std::getline(f, line);
    std::istringstream(line) >> a;
    this->nVertex = a;
    // iterando pelo restante dos dados
    while (std::getline(f, line)){
        vertex *vu;
        vertex *vv;
        std::istringstream(line) >> a >> b >> c;
        if(a != lastVertex->value){
            vertex v;
            v.value = a;
            V.push_back(v);
            vu = &v;
        }
        else{
            vu = lastVertex;
        }

        if(b != a){
            vertex v;
            v.value = b;
            V.push_back(v);
            vv = &v;
            lastVertex = &v;
        }

        edge e;
        e.u = vu;
        e.v = vv;
        e.w = c;

        E.push_back(e);
    }

    for(vertex v: V){
        std::cout << v.value << ' ';
    }
};