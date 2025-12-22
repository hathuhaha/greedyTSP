#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "common.h"
#include "parameters.h"
#include "variables.h"

void nearest_insertion_greedy_TSP(Graph &graph, Solution &solution, const int startVertex);
void check_all_permutations_TSP(Graph &graph, Solution &solution);
#endif