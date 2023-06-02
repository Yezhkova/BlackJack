#pragma once

#include "participant.h"

class Player: public Participant
{
public:
    Player() = default;

    void winMoney(int money)
    {
        m_balance += money;
    }

    void loseMoney(int money)
    {
        m_balance -= money;
        if(m_balance == 0)
        {
            this->setActive(false);
        }
    }

    void makeBet()
    {
        m_bet = rand() % bets.size();
    }

    int getBet()
    {
        return m_bet;
    }

private:
    int m_balance = 100;
    int m_bet;

public:
    static std::array<int, 5> bets;

};

