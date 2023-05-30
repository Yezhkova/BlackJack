#pragma once

#include "dealer.h"
#include "player.h"

class GameProcess
{
public:
    GameProcess(int playersNumber);
    void playRound();

private:
    Dealer m_dealer;
    int m_playersNum;
    std::vector<Player> m_players;

};
