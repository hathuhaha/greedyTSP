#include "parameters.h"

void Graph::calculateDistance() {

    for(int i = 0; i < vSize; i++) {

        for(int j = 0; j < vSize; j++) {

            dist[i][j] = vertices[i].getEuclideDistance(vertices[j]);

        }
    }
}

double Graph::Vertex::getEuclideDistance(const Vertex &other) { 

    double dx = position.f - other.position.f;
    double dy = position.s - other.position.s;
    return std::sqrt(dx * dx + dy * dy);

}
