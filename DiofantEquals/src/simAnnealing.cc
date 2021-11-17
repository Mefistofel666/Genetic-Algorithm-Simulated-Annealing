#include <simAnnealing.h>
#include <iostream>
#include <algorithm>


void printVec(std::vector<int> arr)
{
    for(auto& item : arr)
    {
        std::cout << item << " ";
    }
    std::cout << "\n";
}



int SimAnnealing::func(std::vector<int> arr)
{
    int res = 0;
    for(int i = 0; i < arr.size(); i++)
    {
        res += arr[i] * coefs[i];
    }
    return res;
}


int SimAnnealing::targetFunction(std::vector<int> arr)
{
    return abs(func(arr) - limit);
}

SimAnnealing::SimAnnealing(int n, double t, double a, std::vector<int> coef, int lim)
{
    size = n;
    T = t;
    alpha = a;
    coefs = coef;
    limit = lim;
    for(int i = 0; i < n; i++)
    {
        positions.push_back(1 + rand() % (limit-1));
    }
}

std::vector<int> SimAnnealing::run()
{
    int current = targetFunction(positions);
    std::vector<int> mixedPos;
    int count = 0;
    while(T > 0)
    {
        count++;
        mixedPos = transposition(positions);
   
        int potential = targetFunction(mixedPos);
        if (potential == 0)
        {
            positions = mixedPos;
            break;
        }
        int deltaTargetFunction = potential - current;
    
        if (deltaTargetFunction < 0)
        {
            positions = mixedPos;
            current = potential;
        }
        else
        {
            double p = exp(-deltaTargetFunction / T);
            if (p > double(rand()) / RAND_MAX)
            {
                positions = mixedPos;
                current = potential;
            }
            T = alpha * T;
        }
    }
    return positions;
}





std::vector<int> SimAnnealing::transposition(std::vector<int> positions)
{
    std::vector<int> tpos = positions;
    int j = rand() % size;
    tpos[j] = 1 + rand() % (limit);
    return tpos;
}




std::vector<int> SimAnnealing::getPos()
{
    return positions;
}

