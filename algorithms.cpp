#include "algorithms.h"

void nearest_insertion_greedy_TSP(Graph &graph, Solution &solution, const int startVertex) {
    solution.addVertex(graph.vertices[startVertex], 0);
    while(solution.fillPtr < solution.vSize) {
        double minIncrease = std::numeric_limits<double>::max();
        int bestVertex = -1;
        int bestPosition = -1;

    
    }
}