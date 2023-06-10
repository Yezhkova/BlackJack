#pragma once

#include "participant.h"
#include "player.h"
#include <list>

class Dealer: public Participant
{

    Q_OBJECT

public:
    Dealer();
    Dealer(const Dealer&) {};
    Dealer(Dealer&&) noexcept {};
    void makeDeck();
    void checkCardAmount();
    void compareScore(Player *player);
    void compareScore(Participant *participant);
    void act(Participant *participant) {
        while(participant->getScore() < 17 && participant->isActive())
        {
            dealCards(participant, 1);
        }
    }
    bool checkForBlackjack(Participant *participant);

public slots:
    void dealCards(Participant *participant, int numberOfcards);

signals:

    void cardDealt(Participant *receiver, const QString& cardName, bool flag, bool animate);
    void foundStatus(Participant *participant, const QString& filepath);
    void foundTextStatus (Participant *participant, const QString& text);
    void participantActive(Participant *participant, bool active);
    void balanceUpdated(Player *receiver);

private:
    void makeSuit(const QString& suit);

private:
    std::list<Card> m_deck;

};

