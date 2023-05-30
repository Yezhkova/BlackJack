#include "gameprocess.h"
#include "qdebug.h"
GameProcess::GameProcess(int playersNumber) : m_playersNum(playersNumber)
{
//    qDebug() << "playersNumber = " << playersNumber << '\n';

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
        if(!player.is_dealer()) {
            player.makeBet();
        }
    }

    // each participant gets initial cards, including the dealer
    for(auto& participant: m_players)
    {
        m_dealer.dealCards(participant, 2);
    }
    m_dealer.checkCardAmount();


}
