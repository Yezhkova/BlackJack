#include "participant.h"

int Participant::winScore = 21;

void Participant::takeCard(const Card& card)
{
    m_hand.push_back(card);
    m_score += card.getNumber();
    //        qDebug() << m_hand.cbegin()->getName() << " taken. Score: " << m_score;
    if(m_score > winScore) {
        if(m_is_soft)
        {
            m_score -= 10;
            m_is_soft = false;
        }
        else
        {
            m_is_bust = false;
            m_winner = false;
            m_is_active = false;
            // emit is bust;
        }
    }
    // emit display score
    //        qDebug() << "Score after levelling: " << m_score;
}

bool Participant::checkForBlackjack()
{
    if(m_hand.size() == 2 && m_score == winScore)
    {
        m_has_blackjack = true;
        m_winner = true;
        m_is_active = false;
        return true;
    }
    return false;
}
