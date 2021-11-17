#ifndef AGENT_H
#define AGENT_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_set>

class Agent
{
private:
    std::vector<int> chromosome; 
    double productivity;
public:
    // constructors
    Agent(int chromoSize);
    Agent(std::vector<int> chromo);
    
    // fitness function
    int targetFunction(); 

    // mutation
    void mutation();

    //getters
    std::vector<int> getChromo();
    double getProductivity();

    // print chromosome
    void print();
};

#endif