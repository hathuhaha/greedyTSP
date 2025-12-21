#include <iostream> 
#include "common.h"
#include "variables.h"


int main() {
    Solution S;
    S = Solution(9);
    for(int s : S.tour) {
        std::cout << s << ' ';
    }
    std::cout << '\n';
}