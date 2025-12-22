#include "parameters.h"

void Graph::calculateTDistance() {

    for (int i = 0; i < vSize; i++) {
        for (int j = 0; j < vSize; j++) {

            tdist[i][j] = vertices[i].getManhattanDistance(vertices[j]);
        }
    }
}

void Graph::calculateDDistance() {

    for (int i = 0; i < vSize; i++) {
        for (int j = 0; j < vSize; j++) {

            ddist[i][j] = vertices[i].getEuclideDistance(vertices[j]);
        }
    }
}

double Graph::Vertex::getEuclideDistance(const Vertex &other) {

    double dx = position.f - other.position.f;
    double dy = position.s - other.position.s;
    return std::sqrt(dx * dx + dy * dy);
}

double Graph::Vertex::getManhattanDistance(const Vertex &other) {

    double dx = std::abs(position.f - other.position.f);
    double dy = std::abs(position.s - other.position.s);
    return dx + dy;
}
