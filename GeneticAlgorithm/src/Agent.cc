#include <Agent.h>

Agent::Agent(int chrSize)
{
    for(int i = 0; i < chrSize; i++)
    {
        chromosome.push_back(i);
    }
    std::random_shuffle(chromosome.begin(), chromosome.end());
    productivity = targetFunction();
}

Agent::Agent(std::vector<int> chromo)
{
    std::unordered_set<int> usedPos;
    for(int i = 0; i < chromo.size(); i++)
    {
        if(usedPos.find(chromo[i]) == usedPos.end())
        {
            chromosome.push_back(chromo[i]);
            usedPos.insert(chromo[i]);
        }
        else
        {
            int tmp = rand() % chromo.size();
            while(usedPos.find(tmp) != usedPos.end())
            {
                tmp = rand() % chromo.size();
            }
            chromosome.push_back(tmp);
            usedPos.insert(tmp);
        }
    }
    productivity = targetFunction();
}



std::vector<int> Agent::getChromo()
{
    return chromosome;
}

// combination formula for calculate number of pairs of threaten queens
int threat_calculate(int n) { 
    if (n < 2) return 0;
    if (n == 2) return 1;
    return (n - 1) * n / 2;
}



int Agent::targetFunction()
{
    std::vector<int> chess_board = chromosome;
    unsigned long size = chess_board.size();
    int threat = 0;
    int m_chessboard[size];
    int a_chessboard[size];

    for (int i = 0; i < size; i++) {
        a_chessboard[i] = i + chess_board[i];
        m_chessboard[i] = i - chess_board[i];
    }

    std::sort(m_chessboard, m_chessboard + size);
    std::sort(a_chessboard, a_chessboard + size);

    int m_count = 1;
    int a_count = 1;

    for (int i = 0; i < size - 1; i++) {
        int j = i + 1;
        if (m_chessboard[i] == m_chessboard[j]) m_count += 1;
        else {
            threat += threat_calculate(m_count);
            m_count = 1;
        }
        if (a_chessboard[i] == a_chessboard[j]) a_count += 1;
        else {
            threat += threat_calculate(a_count);
            a_count = 1;
        }
        if (j == size - 1) {
            threat += threat_calculate(m_count);
            threat += threat_calculate(a_count);
            break;
        }
    }

    return threat;
}

double Agent::getProductivity()
{
    return productivity;
}

void Agent::mutation()
{
    int i = 0;
    int j = 0;
    while(i == j)
    {
        i = rand() % chromosome.size();
        j = rand() % chromosome.size();
    }
    int tmp = chromosome[i];
    chromosome[i] = chromosome[j];
    chromosome[j] = tmp;
    productivity = targetFunction();
}


void Agent::print()
{
    for(int i = 0; i < chromosome.size(); i++)
    {
        std::cout << chromosome[i] << " ";
    }
    std::cout << "\n";
}