#pragma once

#include "card.h"
#include <vector>
#include <QDebug>

class Participant
{
public:
    Participant()
    {
    };

    std::vector<Card> const getHand()
    {
        return m_hand;
    }

    int getScore() const
    {
        return m_score;
    }

    void takeCard(const Card& card);

    bool checkForBlackjack();

    void setAsUser()
    {
        m_is_user = true;
    }

    void setAsDealer()
    {
        m_is_dealer = true;
    }

    bool is_user()
    {
        return m_is_user;
    }

    bool is_dealer()
    {
        return m_is_dealer;
    }

    bool isWinner()
    {
        return m_winner;
    }

    void setWinner(bool win)
    {
        m_winner = win;
    }

    bool isActive()
    {
        return m_is_active;
    }

    void setActive(bool active)
    {
        m_is_active = active;
    }

    bool isSoft()
    {
        return m_is_soft;
    }

    void setSoft(bool soft)
    {
        m_is_soft = soft;
    }

    bool hasBlackjack()
    {
        return m_has_blackjack;
    }

    void setBlackjack(bool bj)
    {
        m_has_blackjack = bj;
    }

    bool isBust()
    {
        return m_is_bust;
    }

    void setBust(bool bust)
    {
        m_is_bust = bust;
    }


private:
    std::vector<Card> m_hand;
    int m_score = 0;
    bool m_is_user = false;
    bool m_is_dealer = false;
    bool m_winner = false;
    bool m_has_blackjack = false;
    bool m_is_bust = false;
    bool m_is_active = true;
    bool m_is_soft = false;

public:
    static int winScore;
};

