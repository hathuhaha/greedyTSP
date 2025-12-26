#ifndef SOLVER_H
#define SOLVER_H

#include "common.h"
#include "parameters.h"
#include "input.h"
#include "helpers.h"


class Solution {
public: 
    std::vector<int> tour; 
    double totalLength;
    Solution();
    Solution(const std::vector<int> &_tour, double _totalLength);

    bool operator < (const Solution &other) const;
    bool operator > (const Solution &other) const;
    bool operator == (const Solution &other) const;
    void operator=(const Solution &other);
    
};

class solver {
    class Config {
    public:
        long long timeLimitInSeconds;
        std::string algorithmName;
        Config() {
            timeLimitInSeconds = 3600;
            algorithmName = "ILS";
        }
        Config(long long _timeLimitInSeconds, std::string _algorithmName) {
            timeLimitInSeconds = _timeLimitInSeconds;
            algorithmName = _algorithmName;
        }
    };
public: 
    Instance instance;
    Solution initialSolution();
    Config config;

    solver();
    solver(const Instance &_instance);
    void setConfig(long long _timeLimitInSeconds, std::string _algorithmName);
    Solution solve();
};

#endif