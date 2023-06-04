#pragma once

#include "dealer.h"
#include "player.h"

class GameProcess: public QObject
{

    Q_OBJECT

public:
    GameProcess(int playersNumber);

    int getPlayersNum() const
    {
        return m_playersNum;
    }

    Dealer& getDealer()
    {
        return m_dealer;
    }

    std::vector<Player>& getPlayers()
    {
        return m_players;
    }

public slots:
    void playRound();

signals:

private:
    Dealer m_dealer;
    int m_playersNum;
    std::vector<Player> m_players;

public:
    static double winCoeff;

};
