#include <iostream>
#include <vector>
#include <simAnnealing.h>
#include <Genetic.h>
#include <chrono>

int main()
{
    double T = 100; 

    int numbersOfVariables = 30;

    std::vector<int> coefs;

    for(int i = 0; i < numbersOfVariables; i++)
    {
        coefs.push_back(rand() % 5);
    }
    std::vector<int> solution;
    for(int i = 0; i < numbersOfVariables; i++)
    {
        solution.push_back(1 + rand() % 5);
    }

    long long targetInt = 0;
    for(int i = 0; i < numbersOfVariables; i++)
    {
        targetInt += solution[i] * coefs[i];
    }


    
    // // Simulation Annealing 
    std::cout << "Target = " << targetInt << "\n";


    SimAnnealing *sa = new SimAnnealing(numbersOfVariables, T, 0.95, coefs, targetInt);
    std::vector<int> start = sa->getPos();
    std::cout << "Before SimAnnealing:\n";
    for(auto& item : start)
    {
        std::cout << item << " ";
    }
    std::cout << "\n";

    double time1 = 0;
    auto begin1 = std::chrono::steady_clock::now();

    sa->run();


    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end1 - begin1;
    time1 = elapsed_seconds.count();
    std::cout << "Time: " << time1 << "\n";

    std::vector<int> res = sa->getPos();
    std::cout << "After SimAnnealing:\n";
    for(auto& item : res)
    {
        std::cout << item << " ";
    }
    std::cout << "\n";

    



    // Genenetic
    int popSize = 60;

    Genetic genetic(popSize, numbersOfVariables, targetInt, coefs);

    double time = 0;
    auto begin = std::chrono::steady_clock::now();
    // genetic.run();


    genetic.canoncalRun();
  

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - begin;
    time = elapsed_seconds.count();
    std::cout << "Time: " << time << "\n";


    std::vector<Agent*> population = genetic.getPopulation();

    // for(auto& agent : population)
    // {
    //     std::cout << agent->getProductivity() << " -> ";
    //     agent->print();
    // }


    std::cout << "\nThe best:\n";

    population[0]->print();

    return 0;
}