#include "participant.h"

int Participant::winScore = 21;

void Participant::takeCard(const Card& card)
{
    m_hand.push_back(card);
    m_score += card.getCardScore();
    if(m_score > winScore) {
        if(m_is_soft)
        {
            m_score -= 10;
            m_is_soft = false;
        }
        else
        {
            m_is_bust = true;
            m_is_active = false;
        }
    }
}

