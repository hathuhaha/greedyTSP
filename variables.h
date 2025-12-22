#ifndef VARIABLES_H
#define VARIABLES_H

#include "common.h"
#include "parameters.h"

class Solution {
public:
    int vSize, fillPtr;
    std::vector<Graph::Vertex> tour;
    double totalLength;
    std::vector<bool> visited;

    Solution() {
        fillPtr = totalLength = vSize = 0;
    }

    Solution(int _tourSize) {
        vSize = _tourSize;
        fillPtr = totalLength = 0;

        tour.resize(vSize);
        visited.resize(vSize);

        Graph::Vertex emptyVertex = Graph::Vertex();
        std::fill(tour.begin(), tour.end(), emptyVertex);
        std::fill(visited.begin(), visited.end(), 0);
    }
    
    Solution(const Solution& other) {
        vSize = other.vSize;
        fillPtr = other.fillPtr;
        totalLength = other.totalLength;
        tour = other.tour;
        visited = other.visited;
    }

    void addVertex(Graph::Vertex vertex, int position);
    void printTour();
    void printTourInFile(const std::string &filename);
};

#endif