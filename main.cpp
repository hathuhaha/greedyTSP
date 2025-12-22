#include <iostream> 
#include "common.h"
#include "variables.h"
#include "parameters.h"
#include "input.h"
#include "algorithms.h"

std::string filename[] = {"att48.tsp", "berlin52.tsp"};
int main() {

    for(const std::string file : filename) {
        Graph graph;
        inputGraph(graph, file);

        Solution solution(graph.vSize);
        nearest_insertion_greedy_TSP(graph, solution, graph.vSize - 1);
        solution.printTourInFile("results/output_" + file);
    }
    return 0;
}