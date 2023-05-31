#pragma once

#include "participant.h"

class Player: public Participant
{
public:
    Player();

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
//        m_bet = bet;
    }

    int getBet()
    {
        return m_bet;
    }


private:
    int m_balance = 100;
    int m_bet;
};

