#include <Agent.h>

Agent::Agent(int chrSize, long long targ)
{
    target = targ;
    for(int i = 0; i < chrSize; i++)
    {
        chromosome.push_back(1 + rand() % (target - 1));
    }
}

Agent::Agent(std::vector<int> chromo, long long targ)
{
    target = targ;
    chromosome = chromo;
}

std::vector<int> Agent::getChromo()
{
    return chromosome;
}


void Agent::setProd(double prod)
{
    productivity = prod;
}


double Agent::getProductivity()
{
    return productivity;
}

void Agent::mutation()
{
    int i = rand() % chromosome.size();
    chromosome[i] = 1 + rand() % (target / chromosome.size());
}


void Agent::print()
{
    for(int i = 0; i < chromosome.size(); i++)
    {
        std::cout << chromosome[i] << " ";
    }
    std::cout << "\n";
}