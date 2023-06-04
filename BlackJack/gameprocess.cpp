#include "gameprocess.h"
#include "qdebug.h"

double GameProcess::winCoeff = 1.5;

GameProcess::GameProcess(int playersNumber) : m_playersNum(playersNumber)
{
    //    qDebug() << "playersNumber = " << playersNumber << '\n';

    for(int i = 0; i < playersNumber; ++i){
        Player p(QString("Player%1").arg(i));
        m_players.push_back(p);
    }
    m_players[0].setAsUser();
}

void GameProcess::playRound()
{
    for(auto& player: m_players)
    {
//        player.makeBet();
        m_dealer.dealCards(player, 2);
    }

    m_dealer.dealCards(m_dealer, 2);
    m_dealer.checkForBlackjack();
    m_dealer.act(m_dealer);
    m_dealer.checkCardAmount();

    for(auto& player: m_players)
    {
        player.checkForBlackjack();
        if(!player.hasBlackjack())
        {
            if(!player.is_user())
            {
                m_dealer.act(player);
            }
            // palyer is human (user)
            else
            {
                while(player.isActive())
                {
                    //                if(hit)
                    //                {
                    //                    m_dealer.dealCards(player, 1);
                    //                }
                    //                else if(stand)
                    //                {
                    //                    player.setActive(false);
                    //                }
                }
            }

            int evaluate = m_dealer.compareScore(player);
            if(evaluate > 0)
            {
                player.winMoney(winCoeff * player.getBet());
            }
            else if(evaluate < 0)
            {
                player.loseMoney(player.getBet());
            }
            // emit blackjack
        }
    }
}
