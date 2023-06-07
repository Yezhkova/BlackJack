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
    void makeDeck();
    void checkCardAmount();
    int compareScore(Participant *participant);
    void act(Participant *participant) {
        while(participant->getScore() <= 17 && participant->isActive())
        {
            dealCards(participant, 1);
        }
    }
    bool checkForBlackjack(Participant *participant);

public slots:
    void dealCards(Participant *participant, int numberOfcards);

signals:

    void cardDealt(Participant *receiver, std::_List_iterator<Card> it);
    void foundStatus(Participant *participant, const QString& filepath);
    void foundTextStatus (Participant *participant, const QString& text);
    void participantActive(Participant *participant, bool active);
private:
    void makeSuit(const std::string& suit);

private:
    std::list<Card> m_deck;

};

