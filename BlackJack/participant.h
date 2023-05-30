#pragma once

#include "card.h"
#include <vector>
class Participant
{
public:
    Participant();

    std::vector<Card> const getHand()
    {
        return m_hand;
    }

    int getScore() const {
        return m_score;
    }

    void addCard(const Card& card)
    {
        m_hand.push_back(card);
        m_score += card.getNumber();
    }

private:
    std::vector<Card> m_hand;
    int m_score;
};

