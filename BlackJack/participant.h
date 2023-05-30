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

    int getScore() const {
        return m_score;
    }

    void takeCard(const Card& card)
    {
        m_hand.push_back(card);
        m_score += card.getNumber();
//        qDebug() << m_hand.cbegin()->getName() << " taken. Score: " << m_score;
        if(m_hand.cbegin()->getName() == "Ace" && m_score > 21) {
            m_score -= 10;
        }
//        qDebug() << "Score after levelling: " << m_score;

    }

    void setAsUser() {
        m_is_user = true;
    }

    void setAsDealer() {
        m_is_dealer = true;
    }

    bool is_user(){
        return m_is_user;
    }

    bool is_dealer(){
        return m_is_dealer;
    }

private:
    std::vector<Card> m_hand;
    int m_score;
    bool m_is_user = false;
    bool m_is_dealer = false;
};

