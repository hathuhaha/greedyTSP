#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "common.h"
class Graph {

public:

    class Vertex {
    public:
        std::pair<double, double> position;
        int id;
        Vertex() {
            id = -1;
            position = {0.0, 0.0};
        }

        Vertex(double x, double y, int _id) {
            position = {x, y};
            id = _id;
        }

        double getEuclideDistance(const Vertex& other);
        double getManhattanDistance(const Vertex& other);
    };

    int vSize;
    std::vector<Vertex> vertices;
    std::vector<std::vector<double>> tdist, ddist;
    
    Graph() {
        vSize = 0;
    }

    Graph(int _vSize) {
        vSize = _vSize;
        vertices.resize(vSize);
        tdist.resize(vSize);
        ddist.resize(vSize);

        std::vector<double> sample(vSize, 0.0);
        std::fill(tdist.begin(), tdist.end(), sample);
        std::fill(ddist.begin(), ddist.end(), sample);

    }
    
    Graph(const Graph& other) {
        vSize = other.vSize;
        vertices = other.vertices;
        tdist = other.tdist;
        ddist = other.ddist;
    }

    void calculateTDistance();
    void calculateDDistance();
};



#endif