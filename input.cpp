#include "input.h"

void inputGraph(Graph &graph, const std::string &filename) {
    std::ifstream infile("formatted_data/" + filename); 
    
    if (!infile.is_open()) {
        std::cerr << "Error opening file: data/" << filename << '\n';
        return;
    }

    int vSize;
    if (!(infile >> vSize)) 
        return; 

    graph = Graph(vSize);

    for (int i = 0; i < vSize; i++) {
        int id; 
        double x, y;
        if (infile >> id >> x >> y) {
            graph.vertices[i] = Graph::Vertex(x, y, i);
        }
    }
    infile.close();
}