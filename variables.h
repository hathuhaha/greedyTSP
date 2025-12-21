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

        std::fill(tour.begin(), tour.end(), -1);
        std::fill(visited.begin(), visited.end(), 0);
    }
    void addVertex(Graph::Vertex vertex, int position);
    void printTour();
};

#endif