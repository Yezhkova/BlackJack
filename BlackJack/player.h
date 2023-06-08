#pragma once

#include "participant.h"

class Player: public Participant
{
    Q_OBJECT

public:
    Player(QString name)
        : Participant(nullptr, name)
    {
        setName(name);
    };

    Player(const Player& p){
        setName(p.getName());
    };

    Player(Player&& p) noexcept {
        setName(p.getName());
    };

    void winMoney(int money)
    {
        m_balance += money;
    }

    void loseMoney(int money)
    {
        m_balance -= money;
        if(m_balance <= 0)
        {
            this->setActive(false);
        }
    }

    void makeBet()
    {
        if(m_is_user)
        {
            return;
        }
        int idx = rand() % bets.size();
        while(bets[idx] > m_balance)
        {
            --idx;
        }
        m_bet = bets[idx];
    }

    int getBet()
    {
        return m_bet;
    }

    int getBalance()
    {
        return m_balance;
    }

public slots:
    void setBet(int index)
    {
        m_bet = bets[index];
    }

private:
    int m_balance = 100;
    int m_bet = 0;

public:
    static std::array<int, 5> bets;

};

