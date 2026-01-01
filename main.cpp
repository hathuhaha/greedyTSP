#include "common.h"
#include "parameters.h"
#include "input.h"
#include "solver.h"


void checkSolution(const Solution &solution, const Instance &instance) {
    if (solution.tTour.empty()) {
        std::cout << "Warning: tTour is empty!" << std::endl;
        // Xử lý riêng hoặc return
        return; 
    }
    double computedLength = 0.0;
    for(int d : solution.dTour) {
        computedLength += instance.getDDistance(d, 0) * 2;
    }
    for(int i = 1; i < solution.tTour.size(); i++) {
        computedLength += instance.getTDistance(solution.tTour[i], solution.tTour[i - 1]);
    }
    computedLength += instance.getTDistance(0, solution.tTour[0]);
    computedLength += instance.getTDistance(0, solution.tTour.back());
    // double computedLength = 0.0;
    // for(size_t i = 0; i < solution.tour.size(); i++) {
    //     int from = solution.tour[i];
    //     int to = solution.tour[(i + 1) % solution.tour.size()];
    //     computedLength += instance.getDistance(from, to);
    // }
    if(abs(computedLength - solution.total_cost) > eps) {
        std::cerr << "Solution length mismatch! Computed: " << computedLength << ", Reported: " << solution.total_cost << std::endl;
    } else {
        std::cout << "Solution length verified: " << solution.total_cost << std::endl;
    }
}
int main() {
    srand(187);
    std::ifstream read_file_name("D:/Personal/lab/PDSTSP-ILS/fileNames.txt");
    if (!read_file_name.is_open()) {
        std::cerr << "Cannot open the file fileNames.txt" << std::endl;
        return 1;
    }
    std::string file_name;

    while (std::getline(read_file_name, file_name)) {
        if (file_name.empty()) continue;
        std::cout << "Processing Instance " << file_name << std::endl;
        Instance instance;
        instance.readFromFile("formatted_data/" + file_name);

        Solver solver(instance);
        solver.setConfig_timeLimitInSeconds(60); 
        solver.setConfig_algorithm("ILS"); 

        auto start = std::chrono::high_resolution_clock::now();
        
        Solution bestSolution = solver.solve();
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        std::cout << "Best tour: " << bestSolution.total_cost << std::endl;
        std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
        checkSolution(bestSolution, instance);

        std::cout << "Truck-served customers: ";
        for(int x : bestSolution.tTour)
            std::cout << x << ' ';
        std::cout << '\n';
        std::cout << "Drone-served customers: ";
        for(int x : bestSolution.dTour)
            std::cout << x << ' ';
        std::cout << '\n';

        std::cout << "-----------------------------------------------------------------------" << std::endl;

    }
    read_file_name.close();
    return 0;
}