#pragma once

#include "participant.h"
#include <list>

class Dealer: public Participant
{

    Q_OBJECT

public:
    Dealer();
    Dealer(const Dealer&) {};
    Dealer(Dealer&&) noexcept {};
//    ~Dealer(){};
    void dealCards(Participant& participant, int numberOfcards);
    void makeDeck();
    void checkCardAmount();
    int compareScore(Participant& participant);
    void act(Participant& participant) {
        while(participant.getScore() < 17 && participant.isActive())
        {
            dealCards(participant, 1);
        }
    }


signals:
    void cardDealt(const QString& receiver
                   , const QString& cardName
                   , int cardNum);

private:
    void makeSuit(const std::string& suit);

private:
    std::list<Card> m_deck;

};

