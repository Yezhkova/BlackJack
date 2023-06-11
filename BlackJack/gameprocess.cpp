#include "gameprocess.h"
#include "qcoreapplication.h"
#include "qdebug.h"
#include <QTimer>

double GameProcess::winCoeff = 1.5;

GameProcess::GameProcess(int playersNumber) : m_playersNum(playersNumber)
{
    for(int i = 0; i < playersNumber; ++i){
        Player p(QString("Player%1").arg(i));
        m_players.push_back(p);
    }
    m_players[0].setAsUser();
}

void GameProcess::playRound()
{
    emit roundStarted();
    for(auto& player: m_players)
    {
        if(player.canPlay())
        {
            player.makeBet();
            m_dealer.dealCards(&player, 2);
        }
    }

    m_dealer.dealCards(&m_dealer, 2);
    m_dealer.checkForBlackjack(&m_dealer);
}

void GameProcess::goOnRound()
{
    m_players[0].setActive(false);
    emit continueRound();
    QString secretCard = m_dealer.getHand().rbegin()->getFullName();
    emit m_dealer.cardDealt(&m_dealer, secretCard, true, false);
    m_dealer.act(&m_dealer);
    m_dealer.checkCardAmount();
    for(auto& player: m_players)
    {
        if(player.canPlay())
        {
            m_dealer.checkForBlackjack(&player);
            if(!player.hasBlackjack())
            {
                if(!player.is_user())
                {
                    m_dealer.act(&player);
                }
            }
        }
    }
    emit roundFinished();
}
