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
//    Player(Player&& p)
//        : m_balance(p.m_balance)
//        , m_bet(p.m_bet)
//    {
//    };

//    ~Player(){};
//    void setName(const QString& name)
//    {
//        m_name = name;
//    }
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

//    void makeBet()
//    {
//        m_bet = rand() % bets.size();
//    }

    int getBet()
    {
        return m_bet;
    }

public slots:
    void setBet(int index)
    {
        m_bet = bets[index];
    }

private:
    int m_balance = 100;
    int m_bet = rand() % bets.size();

public:
    static std::array<int, 5> bets;

};

