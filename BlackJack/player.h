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
    }

    void makeBet() {

    };


private:
    int m_balance = 100;
};

