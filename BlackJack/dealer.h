#pragma once

#include "participant.h"
#include "player.h"
#include <list>

class Dealer: public Participant
{
public:
    Dealer();
    void dealCards(Player& player, int numberOfcards);

private:
    void makeSuit(const std::string& suit);

private:
    std::list<Card> m_deck;

};

