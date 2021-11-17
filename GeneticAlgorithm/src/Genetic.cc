#include <Genetic.h>

// char xor_c(char a, char b) { return (a == b) ? '0' : '1'; }
 
// // Helper function to flip the bit
// char flip(char c) { return (c == '0') ? '1' : '0'; }

// std::string graytoBinary(std::string gray)
// {
//     std::string binary = "";
 
//     // MSB of binary code is same as gray code
//     binary += gray[0];
 
//     // Compute remaining bits
//     for (int i = 1; i < gray.length(); i++) {
//         // If current bit is 0, concatenate
//         // previous bit
//         if (gray[i] == '0')
//             binary += binary[i - 1];
 
//         // Else, concatenate invert of
//         // previous bit
//         else
//             binary += flip(binary[i - 1]);
//     }
 
//     return binary;
// }



// std::vector<std::string> generateGrayArr(int n)
// {
    
//     std::vector<std::string> arr;
//     arr.push_back("0");
//     arr.push_back("1");
 
//     int i, j;
//     for (i = 2; i < (1<<n); i = i<<1)
//     {
//         for (j = i-1 ; j >= 0 ; j--)
//             arr.push_back(arr[j]);
 
//         for (j = 0 ; j < i ; j++)
//             arr[j] = "0" + arr[j];
 
//         for (j = i ; j < 2*i ; j++)
//             arr[j] = "1" + arr[j];
//     }
//     return arr;
// }




// std::vector<int> toDecimal(std::vector<std::string> arr)
// {
//     std::vector<int> res;
//     for(int i = 0; i < arr.size();i++)
//     {
//         std::string binary = graytoBinary(arr[i]);
//         int tmp = 0;
//         for(int j = 0; j < binary.length(); j++)
//         {
//             tmp += pow(2, binary.length() - 1 - j)* (binary[j] - '0');
//         }
//         res.push_back(tmp);
//     }
//     return res;
// }
 

// comparator for sort vector

bool cmp(Agent* a, Agent* b)
{
    return a->getProductivity() < b->getProductivity();
}



// CONSTRUCTOR

Genetic::Genetic(int popSize, int chrSize)
{
    populationSize = popSize;
    chromoSize = chrSize;
    for(int i = 0; i < populationSize; i++)
    {
        population.push_back(new Agent(chromoSize));
    }
    sort(population.begin(), population.end(), cmp);
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
    int max = n * (n - 1) / 2;
    for(int i = 0; i < populationSize; i++)
    {
        allSum += max - population[i]->getProductivity();
    }

    for(int i = 0; i < populationSize; i++)
    {
        probs.push_back(( (n * (n - 1) - population[i]->getProductivity()) / allSum));
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
//         res.push_back(new Agent(chr));
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
        std::vector<int> firstChildChromo(chromoSize);
        std::vector<int> secondChildChromo(chromoSize);
        for(int j = 0; j < delimiter; j++)
        {
            firstChildChromo[j] = agents[firstParent]->getChromo()[j];
            secondChildChromo[j] = agents[secondParent]->getChromo()[j];
        }
        for(int j = delimiter; j < chromoSize; j++)
        {
            firstChildChromo[j] = agents[secondParent]->getChromo()[j];
            secondChildChromo[j] = agents[firstParent]->getChromo()[j]; 
        }
        
        res.push_back(new Agent(firstChildChromo));
        res.push_back(new Agent(secondChildChromo));
    }
    return res;
}


// int Genetic::best()
// {
//     int min = population[0]->getProductivity();
//     int index = 0;
//     for(int i = 1; i < population.size(); i++)
//     {
//         if (population[i]->getProductivity() < min)
//         {
//             min = population[i]->getProductivity();
//             index = i;
//         }
//     }
//     return index;
// }



// void Genetic::run()
// {
//     int bestProd = -1;
//     int threshold = 7;
//     while(bestProd != 0)
//     {
//         std::vector<Agent*> forCross = agentForCross();
//         std::vector<Agent*> crossed = cross(forCross);
//         std::vector<Agent*> all;

//         for(int i = 0; i < populationSize; i++)
//         {
//             if(rand() % 10 > threshold)
//             {
//                 crossed[i]->mutation();
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
//         bestProd = population[0]->getProductivity();
//     }
// }


void Genetic::run()
{
    int bestProd = -1;
    int threshold = 7;
    while(bestProd != 0)
    {
        std::vector<Agent*> forCross = agentForCross();
        std::vector<Agent*> crossed = onePointCross(forCross);

        for(int i = 0; i < populationSize; i++)
        {
            if(rand() % 10 > threshold)
            {
                crossed[i]->mutation();
            }
        }
        population = crossed;
        sort(population.begin(), population.end(), cmp);
        bestProd = population[0]->getProductivity();
    }   
}
