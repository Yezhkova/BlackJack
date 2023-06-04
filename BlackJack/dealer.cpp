#include "dealer.h"

Dealer::Dealer(): Participant(nullptr, "Dealer")
{
    makeDeck();
}

void Dealer::makeDeck()
{
    makeSuit("Hearts");
    makeSuit("Diamonds");
    makeSuit("Spades");
    makeSuit("Clubs");
}

void Dealer::makeSuit(const std::string& suit)
{
    for(auto& e: Card::cards) {
        m_deck.emplace_back(Card{suit, e.first, e.second});
    }
}

void Dealer::dealCards(Participant& participant, int numberOfCards)
{
    for(int i = 0; i < numberOfCards; ++i)
    {
        int pickedCardIdx = rand() % m_deck.size();
        auto it = m_deck.begin();
        std::advance(it, pickedCardIdx);
        emit cardDealt(participant.getName()
                       , it->getName()
                       , participant.getHand().size());
        //initial dealing
        if(numberOfCards == 2 && it->getName()=="Ace")
        {
            participant.setSoft(true);
        }
        participant.takeCard(*it);
        m_deck.erase(it);
    }
}

void Dealer::checkCardAmount()
{
    if(m_deck.size() < Card::fullDeck / 4){
        makeDeck();
    }
}

int Dealer::compareScore( Participant& participant)
{
    if(participant.getScore() > this->getScore() ||this->isBust())
    {
        participant.setWinner(true);
        return 1;
    }
    if(participant.getScore() < this->getScore() || participant.isBust())
    {
        this->setWinner(true);
        return -1;
    }
    if(participant.getScore() == this->getScore())
    {
        if(participant.hasBlackjack() && this->hasBlackjack())
        {
            participant.setWinner(false);
            this->setWinner(false);
            return 0;
        }
        if(participant.hasBlackjack())
        {
            return 1;
        }
        if(this->hasBlackjack())
        {
            return -1;
        }
    }
}

