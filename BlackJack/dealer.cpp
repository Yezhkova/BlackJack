#include "dealer.h"

Dealer::Dealer()
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

void Dealer::dealCards(Player& player, int numberOfCards)
{
    for(int i = 0; i < numberOfCards; ++i)
    {
        int pickedCardIdx = rand() % m_deck.size();
        auto it = m_deck.begin();
        std::advance(it, pickedCardIdx);
        player.takeCard(*it);
        m_deck.erase(it);
    }
}

void Dealer::checkCardAmount()
{
    if(m_deck.size() < Card::fullDeck / 4){
        makeDeck();
    }
}
