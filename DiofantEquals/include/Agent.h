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
    long long target;
public:
    // constructors
    Agent(int chromoSize, long long targ);
    Agent(std::vector<int> chromo, long long targ);

    // mutation
    void mutation();

    //getters
    std::vector<int> getChromo();
    double getProductivity();

    // setters
    void setProd(double prod);

    // print
    void print();
};

#endif