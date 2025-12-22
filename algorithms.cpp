#include "algorithms.h"

void nearest_insertion_greedy_TSP(Graph &graph, Solution &solution, const int startVertex) {
    solution.addVertex(graph.vertices[startVertex], 0);
    std::priority_queue<std::pair<double, Graph::Vertex>, std::vector<std::pair<double, Graph::Vertex>>, std::greater<std::pair<double, Graph::Vertex>>> pq;
    for (int v = 0; v < graph.vSize; v++) {
        if (v != startVertex) {
            double dist = graph.vertices[startVertex].getEuclideDistance(graph.vertices[v]);
            pq.push({dist, graph.vertices[v]});
        }
    }

    while (solution.fillPtr < solution.vSize) {
        double minIncrease = std::numeric_limits<double>::max();
        int bestVertex = -1;
        int bestPosition = -1;

        while (pq.size() > 0) {
            auto [dist, vertex] = pq.top();
            pq.pop();

            if (solution.visited[vertex.id]) {
                continue;
            }

            bestVertex = vertex.id;
            for (int pos = 0; pos < solution.fillPtr; pos++) {

                Graph::Vertex v1 = solution.tour[pos];
                Graph::Vertex v2 = solution.tour[(pos + 1) % solution.fillPtr];

                double increase = v1.getEuclideDistance(vertex) + vertex.getEuclideDistance(v2) - v1.getEuclideDistance(v2);
                if (increase < minIncrease) {
                    minIncrease = increase;
                    bestPosition = (pos + 1) % solution.fillPtr;
                }
            }

            break;
        }

        if (bestPosition == 0) {
            bestPosition = solution.fillPtr;
        }

        solution.addVertex(graph.vertices[bestVertex], bestPosition);
        for (int v = 0; v < graph.vSize; v++) {
            if (!solution.visited[v]) {
                double dist = graph.vertices[bestVertex].getEuclideDistance(graph.vertices[v]);
                pq.push({dist, graph.vertices[v]});
            }
        }
    }
    
}

static void recursive_permutation_TSP(Graph &graph, Solution &solution, std::vector<bool> &visited, std::vector<Graph::Vertex> &currentTour, double currentLength, int level) {

}

void check_all_permutations_TSP(Graph &graph, Solution &solution) {

}
