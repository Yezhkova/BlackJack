#pragma once

#include "dealer.h"
#include "player.h"

class GameProcess
{
public:
    GameProcess(int playersNumber);
    void playRound();

    int getPlayersNum() const
    {
        return m_playersNum;
    }

    Dealer getDealer()
    {
        return m_dealer;
    }

public slots:

signals:

private:
    Dealer m_dealer;
    int m_playersNum;
    std::vector<Player> m_players;

public:
    static double winCoeff;

};
