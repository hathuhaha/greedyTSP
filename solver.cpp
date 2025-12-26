#include "solver.h"

Solution::Solution() {
    tour = std::vector<int>();
    totalLength = 0.0;
}
Solution::Solution(const std::vector<int> &_tour, double _totalLength) {
    tour = _tour;
    totalLength = _totalLength;
}

bool Solution::operator < (const Solution &other) const {
    return (totalLength - other.totalLength) <= eps;
}

bool Solution::operator > (const Solution &other) const {
    return (totalLength - other.totalLength) >= eps;
}

bool Solution::operator == (const Solution &other) const {
    return abs(totalLength - other.totalLength) <= eps && tour == other.tour;
}

void Solution::operator=(const Solution &other) {
    tour = other.tour;
    totalLength = other.totalLength;
}
