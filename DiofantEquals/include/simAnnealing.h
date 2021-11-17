#ifndef SIM_ANNEALING
#define SIM_ANNEALING

#include <cmath>
#include <vector>

class SimAnnealing
{
private:
    std::vector<int> positions;
    double T;
    double alpha;
    int size;
    std::vector<int> coefs;
    int limit;
public:
    // constructor
    SimAnnealing(int n, double t, double a, std::vector<int> coef, int lim);

    // cost function
    int targetFunction(std::vector<int> position);
    int func(std::vector<int> arr);

    // permutations of two elements
    std::vector<int> transposition(std::vector<int> positions);

    // run algorithm
    std::vector<int> run();

    // getters
    std::vector<int> getPos();
};

#endif