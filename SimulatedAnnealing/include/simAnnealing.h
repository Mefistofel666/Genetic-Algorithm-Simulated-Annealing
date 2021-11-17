#ifndef SIM_ANNEALING
#define SIM_ANNEALING

#include <cmath>
#include <vector>

class SimAnnealing
{
private:
    std::vector<int> positions; // current solution
    double T; // temperature
    double alpha; // cooling coefficient
    int size; // field size
public:
    // constructor
    SimAnnealing(int n, double t, double a);
    // destructor
    ~SimAnnealing();

    // calculating numbers of pairs of queens under attack
    int targetFunction(std::vector<int> position);
    
    // permutation of two elements
    std::vector<int> transposition(std::vector<int> positions);


    // run algorithm
    std::vector<int> run();

    // getters
    std::vector<int> getPos();
};

#endif // SIM_ANNEALING