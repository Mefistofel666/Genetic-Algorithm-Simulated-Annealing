#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <string>
#include <Agent.h>
#include <cmath>
#include <iostream>
#include <random>
#include <unordered_set>

class Genetic
{
private:
    std::vector<Agent*> population; // all population
    int populationSize;
    int chromoSize;
public:
    // constructor
    Genetic(int popSize, int chromoSize);
    // destructor
    ~Genetic();

    // fitness function
    int targetFunction(Agent* agent); 

    //Proportional selection
    std::vector<Agent*> agentForCross();

    // one point cross
    std::vector<Agent*> onePointCross(std::vector<Agent*> agents);

    // run algorithm
    void run();

    // getters
    std::vector<Agent* > getPopulation();

};

#endif