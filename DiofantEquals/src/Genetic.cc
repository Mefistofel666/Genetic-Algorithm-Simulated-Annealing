#include <Genetic.h>


// comparator for sort vector
bool cmp(Agent* a, Agent* b)
{
    return a->getProductivity() < b->getProductivity();
}



// CONSTRUCTOR

Genetic::Genetic(int popSize, int chrSize, int targ, std::vector<int> coefs)
{
    coef = coefs;
    target = targ;
    populationSize = popSize;
    chromoSize = chrSize;
    for(int i = 0; i < populationSize; i++)    
    {
        Agent* tmp = new Agent(chromoSize, target);
        tmp->setProd(targetFunction(tmp));
        population.push_back(tmp);
    }
}

// DESTRUCTOR
Genetic::~Genetic()
{
    for(int i = 0; i < population.size(); i++)
    {
        delete population[i];
    }
}


std::vector<Agent* > Genetic::getPopulation()
{
    return population;
}


// рулеточный отбор
std::vector<Agent*> Genetic::agentForCross()
{
    int n = chromoSize;
    std::vector<Agent*> res;
    std::vector<double> probs;
    double allSum = 0;
    for(int i = 0; i < populationSize; i++)
    {
        allSum += 1.0 / population[i]->getProductivity();
    }

    for(int i = 0; i < populationSize; i++)
    {
        probs.push_back( ( 1.0 / population[i]->getProductivity()) / allSum);
    }

    std::vector<std::pair<double, double> > segments;
    segments.push_back( {0.0, probs[0]} );

    for(int i = 1; i < probs.size(); i++)
    {
        segments.push_back({segments[i-1].second, segments[i-1].second + probs[i]});
    }

    for(int i = 0; i < populationSize; i++)
    {
        double rnd = (rand() % 1000) / 1000.0;
        for(int j = 0; j < segments.size(); j++)
        {
            if (rnd >= segments[j].first && rnd < segments[j].second)
            {
                res.push_back(population[j]);
                break;
            }
        }
    }
    return res;
}


// std::vector<Agent*> Genetic::cross(std::vector<Agent*> agents)
// {
//     std::vector<Agent*> res;

//     for(int k = 0; k < population.size(); k++)
//     {
//         int i = 0;
//         int j = 0;
//         while(i == j)
//         {
//             i = rand() % agents.size();
//             j = rand() % agents.size();
//         }
//         Agent* first = agents[i];
//         Agent* second = agents[j];
//         std::vector<int> chr;
//         std::unordered_set<int> usedPos;


//         for(int i = 0; i < first->getChromo().size(); i++)
//         {
//             if (first->getChromo()[i] == second->getChromo()[i] && usedPos.find(first->getChromo()[i]) == usedPos.end())
//             {
//                 chr.push_back(first->getChromo()[i]);
//                 usedPos.insert(first->getChromo()[i]);
//             }
//             else
//             {
//                 int pos = rand() % first->getChromo().size();
//                 while (usedPos.find(pos) != usedPos.end())
//                 {
//                     pos = rand() % first->getChromo().size();
//                 }
                
//                 chr.push_back(pos);   
//                 usedPos.insert(pos);
//             }
//         }
//         Agent* tmp = new Agent(chr, target);
//         tmp->setProd(targetFunction(tmp));
//         res.push_back(tmp);
//     }
//     return res; 
// }

// одноточечное скрещивание
std::vector<Agent*> Genetic::onePointCross(std::vector<Agent*> agents)
{
    std::vector<Agent*> res;
    for(int i = 0; i < populationSize / 2; i++)
    {
        int delimiter = 1 + rand() % (chromoSize - 2);
        int firstParent = rand() % populationSize;
        int secondParent = rand() % populationSize;
        while (firstParent == secondParent)
        {
            firstParent = rand() % populationSize;
            secondParent = rand() % populationSize;
        }
        std::vector<int> firstChildChromo;
        std::vector<int> secondChildChromo;
        for(int j = 0; j < delimiter; j++)
        {
            firstChildChromo.push_back(agents[firstParent]->getChromo()[j]);
            secondChildChromo.push_back(agents[secondParent]->getChromo()[j]);
        }
        for(int j = delimiter; j < chromoSize; j++)
        {
            firstChildChromo.push_back(agents[secondParent]->getChromo()[j]);
            secondChildChromo.push_back(agents[firstParent]->getChromo()[j]); 
        }
        Agent* f = new Agent(firstChildChromo, target);
        Agent* s = new Agent(secondChildChromo, target);
        f->setProd(targetFunction(f));
        s->setProd(targetFunction(s));
        res.push_back(f);
        res.push_back(s);
    }

    return res;
}


// int best(std::vector<Agent*> arr)
// {
//     int minProd = arr[0]->getProductivity();
//     int index = 0;
//     for(int i = 1; i < arr.size(); i++)
//     {
//         if (arr[i]->getProductivity() < minProd)
//         {
//             minProd = arr[i]->getProductivity();
//             index = i;
//         }
//     }
//     return index;
// }


// void Genetic::run()
// {
//     int bestProd = -1;
//     int threshold = 9;
//     while(bestProd != 0 )
//     {
//         std::vector<Agent*> forCross = agentForCross();
//         std::vector<Agent*> crossed = cross(forCross);
//         std::vector<Agent*> all;

//         for(int i = 0; i < populationSize; i++)
//         {
//             if(rand() % 10 > threshold)
//             {
//                 crossed[i]->mutation();
//                 crossed[i]->setProd(targetFunction(crossed[i]));
//             }
//         }

//         for(int i = 0; i < crossed.size(); i++)
//         {
//             all.push_back(crossed[i]);
//             all.push_back(population[i]);
//         } 
//         sort(all.begin(), all.end(), cmp);
//         for(int i = 0; i < populationSize; i++)
//         {
//             population[i] = all[i];
//         }
//         bestProd = population[best(population)]->getProductivity();
//     }
// }

int Genetic::best()
{
    int minProd = population[0]->getProductivity();
    int index = 0;
    for(int i = 1; i < population.size(); i++)
    {
        if (population[i]->getProductivity() < minProd)
        {
            minProd = population[i]->getProductivity();
            index = i;
        }
    }
    return index;
}


void Genetic::run()
{
    int bestProd = -1;
    int threshold = 8;
    int count = 0;

    while(bestProd != 0)
    {
        count++;
        std::vector<Agent*> forCross = agentForCross();
        std::vector<Agent*> crossed = onePointCross(forCross);

        for(int i = 0; i < populationSize; i++)
        {
            if(rand() % 11 > threshold)
            {
                crossed[i]->mutation();
                crossed[i]->setProd(targetFunction(crossed[i]));
            }
        }
        population = crossed;
        bestProd = population[best()]->getProductivity();
    }   
}



int Genetic::func(Agent* agent)
{
    int res = 0;
    for(int i = 0; i < agent->getChromo().size(); i++)
    {
        res += agent->getChromo()[i] * coef[i];
    }
    return res;
}


int Genetic::targetFunction(Agent* agent)
{
    return abs(func(agent) - target);
}