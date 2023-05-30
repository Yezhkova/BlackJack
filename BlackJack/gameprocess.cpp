#include "gameprocess.h"

GameProcess::GameProcess(int playersNumber) : m_playersNum(playersNumber)
{
    for(int i = 0; i < playersNumber; ++i){
        m_players.emplace_back(Player());
    }
    m_players[0].setAsUser();
    m_players[playersNumber-1].setAsDealer();
}

void GameProcess::playRound()
{
    for(auto& player: m_players)
    {
        m_dealer.dealCards(player, 2);
    }

}
