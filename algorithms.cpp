#include "algorithms.h"

void nearest_insertion_greedy_TSP(Graph &graph, Solution &solution, const int startVertex) {
    solution.addVertex(graph.vertices[startVertex], 0);
    std::vector<double> minDist(graph.vSize, std::numeric_limits<double>::max()); 

    for (int v = 0; v < graph.vSize; v++) {
        minDist[v] = graph.vertices[startVertex].getEuclideDistance(graph.vertices[v]);
    }

    while (solution.fillPtr < solution.vSize) {
        double minIncrease = std::numeric_limits<double>::max();
        double minDistance = std::numeric_limits<double>::max();
        int bestVertex = -1;
        int bestPosition = -1;

        for(int v = 0; v < graph.vSize; v++) {
            if(solution.visited[v]) {
                continue;
            }
            if(minDist[v] <= minDistance) {
                bestVertex = v;
                minDistance = minDist[v];
            }
        }

        Graph::Vertex vertex = graph.vertices[bestVertex];
        for (int pos = 0; pos < solution.fillPtr; pos++) {

            Graph::Vertex v1 = solution.tour[pos];
            Graph::Vertex v2 = solution.tour[(pos + 1) % solution.fillPtr];

            double increase = v1.getEuclideDistance(vertex) + vertex.getEuclideDistance(v2) - v1.getEuclideDistance(v2);
            if (increase <= minIncrease) {
                minIncrease = increase;
                bestPosition = (pos + 1) % solution.fillPtr;
            }
        }

        if(bestPosition == 0) {
            bestPosition = solution.fillPtr;
        }
        
        solution.addVertex(graph.vertices[bestVertex], bestPosition);
        for (int v = 0; v < graph.vSize; v++) {
            minDist[v] = std::min(minDist[v], graph.vertices[bestVertex].getEuclideDistance(graph.vertices[v]));
        }
    }
    double total_distance = 0.0;
    for (int i = 0; i < solution.vSize; i++) {
        total_distance += solution.tour[i].getEuclideDistance(solution.tour[(i + 1) % solution.vSize]);
    }
    std::cerr << "Calculated total distance: " << total_distance << '\n';
    
}

static void recursive_permutation_TSP(Graph &graph, Solution &solution, std::vector<bool> &visited, std::vector<Graph::Vertex> &currentTour, double currentLength, int level) {

}

void check_all_permutations_TSP(Graph &graph, Solution &solution) {

}
