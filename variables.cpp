#include "variables.h"
#include "common.h"

void Solution::addVertex(int vertex) {

    tour[fillPtr++] = vertex;
    visited[vertex] = true;
    totalLength += 9.0;
    
}
