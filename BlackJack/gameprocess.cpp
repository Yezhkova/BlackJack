#include "gameprocess.h"

GameProcess::GameProcess(int playersNumber) : m_playersNum(playersNumber)
{
    for(int i = 0; i < playersNumber; ++i){
        m_players.emplace_back(Player());
    }
    m_players[0].setAsUser();
}
