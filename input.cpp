#include "input.h"

void inputGraph(Graph &graph, const std::string &filename) {
    std::ifstream infile(filename);
    if(!infile.is_open()) {
        std::cerr << "Error opening file: " << filename << '\n';
        return;
    }   
    int vSize;
    infile >> vSize;            
    graph = Graph(vSize);
    for(int i = 0; i < vSize; i++) {
        double x, y;
        infile >> x >> y;
        graph.vertices[i] = Graph::Vertex(x, y, i);
    }
    infile.close();
    
}