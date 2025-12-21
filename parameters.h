#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "common.h"
class Graph {

public:

    class Vertex {
    public:
        std::pair<double, double> position;

        Vertex() {
            position = {0.0, 0.0};
        }

        Vertex(double x, double y) {
            position = {x, y};
        }

        double getEuclideDistance(const Vertex& other);
        
    };

    int vSize;
    std::vector<Vertex> vertices;
    std::vector<std::vector<double>> dist;
    
    Graph() {
        vSize = 0;
    }

    Graph(int _vSize) {
        vSize = _vSize;
        vertices.resize(vSize);
        dist.resize(vSize);

        std::vector<double> sample(vSize, 0.0);
        std::fill(dist.begin(), dist.end(), sample);
    }

    void calculateDistance();
};



#endif