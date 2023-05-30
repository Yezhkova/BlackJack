#include "dealer.h"

Dealer::Dealer()
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
        int pickedCardIdx = rand() % Card::fullDeck;
        auto it = m_deck.begin();
        std::advance(it, pickedCardIdx);
        player.takeCard(*it);
    }

}
