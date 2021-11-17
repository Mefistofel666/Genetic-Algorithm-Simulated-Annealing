#include <simAnnealing.h>
#include <iostream>
#include <algorithm>


SimAnnealing::SimAnnealing(int n, double t, double a)
{
    size = n;
    T = t;
    alpha = a;
    for(int i = 0; i < size; i++)
    {
        positions.push_back(i);
    }
}

std::vector<int> SimAnnealing::run()
{
    int currentUnderAttack = targetFunction(positions);
    std::vector<int> mixedPos;
    while(T > 0)
    {
        mixedPos = transposition(positions);
        int potentialUnderAttack = targetFunction(mixedPos);
        if (potentialUnderAttack == 0)
        {
            positions = mixedPos;
            break;
        }
        int deltaTargetFunction = potentialUnderAttack - currentUnderAttack;
    
        if (deltaTargetFunction < 0)
        {
            positions = mixedPos;
            currentUnderAttack = potentialUnderAttack;
        }
        else
        {
            double p = exp(-deltaTargetFunction / T);
            if (p > double(rand()) / RAND_MAX)
            {
                positions = mixedPos;
                currentUnderAttack = potentialUnderAttack;
            }
            T = alpha * T;
        }
    }
    return positions;
}


// combination formula for calculate number of pairs of threaten queens
int threat_calculate(int n)
{ 
    if (n < 2) return 0;
    if (n == 2) return 1;
    return (n - 1) * n / 2;
}

// cost function to count total of pairs of threaten queens
int SimAnnealing::targetFunction(std::vector<int> chess_board)
{
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

std::vector<int> SimAnnealing::getPos()
{
    return positions;
}




std::vector<int> SimAnnealing::transposition(std::vector<int> positions)
{
    std::vector<int> tpos(size);
    for(int i = 0; i < size; i++)
    {
        tpos[i] = positions[i];
    }
    int i = 0;;
    int j = 0;
    while(i == j)
    {
        i = (rand() % size);
        j = (rand() % size);
    }
    int tmp = tpos[i];
    tpos[i] = tpos[j];
    tpos[j] = tmp;
    return tpos;
}

