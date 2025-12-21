#ifndef VARIABLES_H
#define VARIABLES_H

#include "common.h" 

template<typename T> 
class Customer {
public: 
    std::pair<T, T> position;

    Customer() {
        position = {T(), T()};
    }

    Customer(T x, T y) {
        position = {x, y};
    }
};

class Solution {
public: 
    int tourSize, fillPtr;
    std::vector<int> tour;
    double totalLength;
    std::vector<bool> visited;

    Solution() {

        fillPtr = totalLength = tourSize = 0;
    }

    Solution(int _tourSize) {

        tourSize = _tourSize;
        tour.resize(tourSize);
        visited.resize(tourSize);

        std::fill(tour.begin(), tour.end(), -1);
        std::fill(visited.begin(), visited.end(), 0);
    }
    void addVertex(int vertex);
};

#endif