#include "solver.h"

//Solution class implementations

Solution::Solution() {
    tTour = std::vector<int>();
    dTour = std::vector<int>();
    total_cost = 0;
}

bool Solution::operator<(const Solution &other) const {
    return (total_cost - other.total_cost) < eps;
}

bool Solution::operator > (const Solution &other) const {
    return (total_cost - other.total_cost) > eps;
}

void Solution::operator=(const Solution &other) {
    tTour = other.tTour;
    dTour = other.dTour;
    total_cost = other.total_cost;
}


Solver::Solver() {
    config = Config();
    instance = Instance();
    runtime = 0;
}

Solver::Solver(const Instance &_instance) {
    config = Config();
    instance = _instance;
    runtime = 0;
}

// Set configuration parameters
void Solver::setConfig_timeLimitInSeconds(long long _timeLimitInSeconds) {
    config.timeLimitInSeconds = _timeLimitInSeconds;
}

void Solver::setConfig_algorithm(std::string _algorithmName) {
    config.algorithmName = _algorithmName;
}

void Solver::setConfig_muatationRate(double _mutationRate) {
    config.mutationRate = _mutationRate;
}


void Solver::addCustomertoTruck(Solution &solution, int customer, int position)
{
    solution.tTour.insert(solution.tTour.begin() + position, customer);
    if(solution.tTour.size() > 1) {
        int next_cus = (position == solution.tTour.size() - 1) ? 0 : solution.tTour[position + 1];
        int prev_cus = (position == 0) ? 0 : solution.tTour[position - 1];
        solution.total_cost -= instance.getTDistance(next_cus, prev_cus);
        solution.total_cost += instance.getTDistance(prev_cus, customer) + instance.getTDistance(next_cus, customer);
    }
}
double Solver::delta_moveDroneToTruck(Solution &solution, int id, int position) {
    double delta = 0.0;
    delta -= instance.getDDistance(0, solution.dTour[id]) * 2;

    if(solution.tTour.size() == 0) {
        return delta;
    }

    int next_id = (position == solution.tTour.size()) ? 0 : solution.tTour[position];
    int prev_id = (position == 0) ? 0 : solution.tTour[position - 1];

    delta -= instance.getTDistance(next_id, prev_id);
    delta += instance.getTDistance(solution.dTour[id], next_id);
    delta += instance.getTDistance(solution.dTour[id], prev_id);

    return delta;
}

double Solver::delta_reverseTTour(Solution &solution, int from, int to) {
    double delta = 0.0;
    if(from > to)
        std::swap(from, to);

    int prev_from = (from == 0) ? 0 : solution.tTour[from - 1];
    int next_to = (to == solution.tTour.size() - 1) ? 0 : solution.tTour[to + 1];
    delta -= instance.getTDistance(prev_from, solution.tTour[from]);
    delta -= instance.getTDistance(next_to, solution.tTour[to]);
    delta += instance.getTDistance(prev_from, solution.tTour[to]);
    delta += instance.getTDistance(next_to, solution.tTour[from]);

    return delta;
}

double Solver::delta_moveTruckToDrone(Solution &solution, int id) {
    double delta = 0.0;
    if(solution.tTour.size() > 1) {
        int next_id = (id == solution.tTour.size() - 1) ? 0 : solution.tTour[id + 1];
        int prev_id = (id == 0) ? 0 : solution.tTour[id - 1];

        delta -= (instance.getTDistance(next_id, solution.tTour[id]) + instance.getTDistance(prev_id, solution.tTour[id]));
        delta += instance.getTDistance(next_id, prev_id);
    }
    delta += instance.getDDistance(0, solution.tTour[id]) * 2;
    return delta;
}
double Solver::delta_swapTTour(Solution &solution, int x, int y) {
    int prev_x = (x == 0) ? 0 : solution.tTour[x - 1];
    int next_x = (x == solution.tTour.size() - 1) ? 0 : solution.tTour[x + 1];
    int prev_y = (y == 0) ? 0 : solution.tTour[y - 1];
    int next_y = (y == solution.tTour.size() - 1) ? 0 : solution.tTour[y + 1];

    double delta = 0.0;
    delta += (prev_x == solution.tTour[y]) ? 0.0 : (instance.getTDistance(prev_x, solution.tTour[y]) - instance.getTDistance(prev_x, solution.tTour[x]));
    delta += (next_x == solution.tTour[y]) ? 0.0 : (instance.getTDistance(next_x, solution.tTour[y]) - instance.getTDistance(next_x, solution.tTour[x]));
    delta += (prev_y == solution.tTour[x]) ? 0.0 : (instance.getTDistance(prev_y, solution.tTour[x]) - instance.getTDistance(prev_y, solution.tTour[y]));
    delta += (next_y == solution.tTour[x]) ? 0.0 : (instance.getTDistance(next_y, solution.tTour[x]) - instance.getTDistance(next_y, solution.tTour[y]));
    return delta;
}
double Solver::delta_swapTruckandDrone(Solution &solution, int t, int d) {
    double delta = 0.0;
    delta += (instance.getDDistance(0, solution.tTour[t]) * 2 - instance.getDDistance(0, solution.dTour[d]) * 2);
    int prev_t = (t == 0) ? 0 : solution.tTour[t - 1];
    int next_t = (t == solution.tTour.size() - 1) ? 0 : solution.tTour[t + 1];

    delta -= (instance.getTDistance(solution.tTour[t], prev_t) + instance.getTDistance(solution.tTour[t], next_t));
    delta += (instance.getTDistance(solution.dTour[d], prev_t) + instance.getTDistance(solution.dTour[d], next_t));
    return delta;

}
void Solver::moveDroneToTruck(Solution &solution, int id, int position)
{
    double delta = delta_moveDroneToTruck(solution, id, position);
    solution.total_cost += delta;
    solution.tTour.insert(solution.tTour.begin() + position, solution.dTour[id]);
    solution.dTour.erase(solution.dTour.begin() + id);
}
void Solver::moveTruckToDrone(Solution &solution, int id) {
    double delta = delta_moveTruckToDrone(solution, id);
    solution.total_cost += delta;
    solution.dTour.push_back(solution.tTour[id]);
    solution.tTour.erase(solution.tTour.begin() + id);
}
void Solver::reverseTTour(Solution &solution, int from, int to) {
    if(from > to)
        std::swap(from, to);
    double delta = delta_reverseTTour(solution, from, to);
    solution.total_cost += delta;
    while(from < to) {
        std::swap(solution.tTour[from], solution.tTour[to]);
        from ++;
        to --;
    }

}

void Solver::swapTTour(Solution &solution, int x, int y) {
    solution.total_cost += delta_swapTTour(solution, x, y);
    std::swap(solution.tTour[x], solution.tTour[y]);
}

void Solver::swapTruckandDrone(Solution &solution, int t, int d) {
    solution.total_cost += delta_swapTruckandDrone(solution, t, d);
    std::swap(solution.tTour[t], solution.dTour[d]);
}

//Main solving function
Solution Solver::solve() {
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = startTime + std::chrono::seconds(config.timeLimitInSeconds);

    return ILS(endTime);
}
Solution Solver::ILS(TimePoint &endTime) {

    Solution initialSolution = generateInitialSolution();
    Solution currentSolution = initialSolution;
    Solution bestSolution = initialSolution;  // Initialize with initial solution

    double threshold = 0.2; 
    double cooling_rate = 0.996;
    int cnt = 0;
    int maxIterations = 10;
    for(int i = 1; i <= maxIterations; i++) {
        Solution newSolution = currentSolution;
        perturbation(currentSolution, newSolution);
        localsearch(newSolution);
        acceptanceCriterion(currentSolution, newSolution, cooling_rate, threshold);
        if(currentSolution.total_cost < bestSolution.total_cost) {
            bestSolution = currentSolution;
            cnt += 1;
        }
    }
    std::cerr << cnt << '\n';
    return initialSolution;
}
Solution Solver::generateInitialSolution() {

    Solution currentSolution = Solution();
    for(int i = 1; i <= instance.cntCustomers; i++) {
        currentSolution.tTour.push_back(i);
        currentSolution.total_cost += instance.getTDistance(i - 1, i);
    }
    currentSolution.total_cost += instance.getTDistance(instance.cntCustomers, 0);
    localsearch(currentSolution);
    return currentSolution;
}

void Solver::localsearch(Solution &currentSolution) {
    
    localsearch_addDrone(currentSolution);
    localsearch_swap(currentSolution);
    localsearch_addTruck(currentSolution);
    localsearch_relocate(currentSolution);
    localsearch_2opt(currentSolution);
}

void Solver::perturbation(Solution &currentSolution, Solution &afterChangedSolution) {
    int changedPairs = config.mutationRate * (int(currentSolution.tTour.size() + currentSolution.dTour.size()) / 2);
    afterChangedSolution = currentSolution;

    int changedTDPairs = randomDouble(0.1, 0.3) * std::min((double)changedPairs, std::min((double)currentSolution.dTour.size(), (double)currentSolution.tTour.size()));
    changedPairs -= changedTDPairs;
    int moveTrucktoDrone = randomDouble(0.05, 0.3) * (double)std::min(changedPairs, (int)currentSolution.tTour.size());
    changedPairs -= moveTrucktoDrone;
    int moveDronetoTruck = randomDouble(0.05, 0.3) * (double)std::min(changedPairs, (int)currentSolution.dTour.size());
    changedPairs -= moveDronetoTruck;
    for(int i = 0; i < changedPairs; i++) {
        std::pair<int, int> randPair = randomDistinctPair(0, currentSolution.tTour.size() - 1);
        int x = randPair.first;
        int y = randPair.second;
        swapTTour(afterChangedSolution, x, y);
    }
    for(int i = 0; i < changedTDPairs; i++) {
        int x = randomInt(0, afterChangedSolution.dTour.size() - 1);
        int y = randomInt(0, afterChangedSolution.tTour.size() - 1);
        swapTruckandDrone(afterChangedSolution, y, x);
    }
    for(int i = 0; i < moveDronetoTruck; i++) {
        int d = randomInt(0, afterChangedSolution.dTour.size() - 1);
        int p = randomInt(0, afterChangedSolution.tTour.size());
        moveDroneToTruck(afterChangedSolution, d, p);
    }
    for(int i = 0; i < moveTrucktoDrone; i++) {
        int t = randomInt(0, afterChangedSolution.tTour.size() - 1);
        moveTruckToDrone(afterChangedSolution, t);
    }
}

void Solver::acceptanceCriterion(Solution &currentSolution, Solution &newSolution, double &coolingRate, double &threshold) {
    if((newSolution.total_cost - currentSolution.total_cost) / currentSolution.total_cost - threshold < -eps)
        currentSolution = newSolution;
    threshold *= coolingRate;
}

//local search methods
void Solver::localsearch_swap(Solution &currentSolution) {
    bool stop = false;
    while(!stop) {
        stop = true;  
        for(int i = 0; i < currentSolution.tTour.size() && stop; i++) {
            for(int j = i + 1; j < currentSolution.tTour.size() && stop; j++) {
                double delta = delta_swapTTour(currentSolution, i, j);
                if(delta < -eps) { 
                    swapTTour(currentSolution, i, j);
                    stop = false;
                }
            }
        }
    }
}

void Solver::localsearch_2opt(Solution &currentSolution) {
    bool stop = false;
    while(!stop) {
        stop = true;
        for(int i = 0; i < currentSolution.tTour.size() && stop; i++) {
            for(int j = i + 1; j < currentSolution.tTour.size() && stop; j++) {
                double delta = delta_reverseTTour(currentSolution, i, j);
                if(delta < -eps) {
                    reverseTTour(currentSolution, i, j);
                    stop = false;
                }
            }
        }
    }
}

void Solver::localsearch_relocate(Solution &currentSolution) {
    bool stop = false;
    while(!stop) {
        stop = true;
        for(int i = 0; i < currentSolution.tTour.size() && stop; i++) {
            int id_cus = currentSolution.tTour[i];
            if(instance.demand[id_cus] > 2.5)
                continue;
            for(int j = 0; j < currentSolution.dTour.size() && stop; j++) {
                double delta = delta_swapTruckandDrone(currentSolution, i, j);
                if(delta < -eps) {
                    swapTruckandDrone(currentSolution, i, j);
                    stop = false;
                }
            }
        }
    }
}

void Solver::localsearch_addTruck(Solution &currentSolution) {
    bool stop = false;
    while(!stop) {
        stop = true;
        for(int i = 0; i < currentSolution.dTour.size() && stop; i++) {
            int dTour_i = currentSolution.dTour[i];
            for(int position = 0; position <= currentSolution.tTour.size() && stop; position++) {
                double delta = delta_moveDroneToTruck(currentSolution, i, position);
                if(delta < -eps) {
                    moveDroneToTruck(currentSolution, i, position);
                    stop = false;
                }
            }
        }
    }
}

void Solver::localsearch_addDrone(Solution &currentSolution) {
    bool stop = false;
    while(!stop) {
        stop = true;
        for(int i = 0; i < currentSolution.tTour.size() && stop; i++) {
            int tTour_i = currentSolution.tTour[i];
            if(instance.demand[tTour_i] > 2.5)
                continue;
            double delta = delta_moveTruckToDrone(currentSolution, i);
            if(delta < -eps) {
                moveTruckToDrone(currentSolution, i);
                stop = false;
            }
        }
    }
}

//construct new tour for truck
Solution Solver::NearestInsertion() {
    return Solution();
}
