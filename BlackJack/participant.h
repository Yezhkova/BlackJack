#pragma once

#include "card.h"
#include <vector>

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
    }

    void setAsUser() {
        is_user = true;
    }

    void setAsDealer() {
        is_dealer = true;
    }

private:
    std::vector<Card> m_hand;
    int m_score;
    bool is_user = false;
    bool is_dealer = false;
};

