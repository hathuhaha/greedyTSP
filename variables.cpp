#include "variables.h"
#include "common.h"
#include "parameters.h"

void Solution::addVertex(Graph::Vertex vertex, int position) {

    tour[fillPtr++] = vertex;
    visited[vertex.id] = true;

    if (fillPtr > 1) {
        totalLength += tour[fillPtr - 2].getEuclideDistance(vertex) + tour[fillPtr - 1].getEuclideDistance(tour[0]) - tour[fillPtr - 2].getEuclideDistance(tour[0]);
    }

    int currentId = fillPtr - 1;

    while (currentId > position) {
        int prevId = (currentId - 1 + fillPtr) % fillPtr;
        int nextId = (currentId + 1) % fillPtr;
        int prevPrevId = (prevId - 1 + fillPtr) % fillPtr;
        // update total length
        totalLength -= tour[currentId].getEuclideDistance(tour[nextId]);
        totalLength += tour[prevId].getEuclideDistance(tour[nextId]);

        totalLength -= tour[prevId].getEuclideDistance(tour[prevPrevId]);
        totalLength += tour[currentId].getEuclideDistance(tour[prevPrevId]);

        std::swap(tour[currentId], tour[currentId - 1]);
        currentId --;
    }
}

void Solution::printTour() {
    std::cout << "Solution: " << totalLength << '\n';
    std::cout << "Tour: ";
    for (int i = 0; i < vSize; i++) {
        std::cout << tour[i].id << ' ';
    }
    std::cout << '\n';
}

void Solution::printTourInFile(const std::string &filename) {
    std::ofstream outfile(filename);

    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << filename << '\n';
        return;
    }

    outfile << "Solution: " << totalLength << '\n';
    outfile << "Tour: ";
    for (int i = 0; i < vSize; i++) {
        outfile << tour[i].id << ' ';
    }
    outfile << '\n';

    outfile.close();
}
