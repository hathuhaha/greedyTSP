#ifndef VARIABLES_H
#define VARIABLES_H

#include "common.h" 
#include "parameters.h"

class Solution {
public: 
    int vSize, fillPtr;
    std::vector<int> tour;
    double totalLength;
    std::vector<bool> visited;

    Solution() {

        fillPtr = totalLength = vSize = 0;
    }

    Solution(int _tourSize) {

        vSize = _tourSize;
        tour.resize(vSize);
        visited.resize(vSize);

        std::fill(tour.begin(), tour.end(), -1);
        std::fill(visited.begin(), visited.end(), 0);
    }
    void addVertex(int vertex);
};

#endif