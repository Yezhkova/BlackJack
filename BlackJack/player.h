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

    void setAsUser()
    {
        is_user = true;
    }

private:
    int m_balance = 100;
    bool is_user = false;
};

