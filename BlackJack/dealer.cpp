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

void Dealer::dealCards(Participant *participant, int numberOfCards)
{
    for(int i = 0; i < numberOfCards; ++i)
    {
        int pickedCardIdx = rand() % m_deck.size();
        auto it = m_deck.begin();
        std::advance(it, pickedCardIdx);
        //initial dealing
        if(numberOfCards == 2 && it->getName()=="Ace")
        {
            participant->setSoft(true);
        }
        participant->takeCard(*it);
        emit cardDealt(participant, it);
        m_deck.erase(it);
    }
}
bool Dealer::checkForBlackjack(Participant *participant)
{
    if(participant->getHand().size() == 2 && participant->getScore() == winScore)
    {
        participant->setBlackjack(true);
        //        emit foundStatus(participant, ":/images/resources/images/blackjackStatus.png");
        participant->setWinner(true);
        participant->setActive(false);
        return true;
    }
    return false;
}

void Dealer::checkCardAmount()
{
    if(m_deck.size() < Card::fullDeck / 4){
        makeDeck();
    }
}

int Dealer::compareScore(Participant *participant)
{
    qDebug() << participant->getName();
    if(participant->isBust())
    {
        emit foundStatus(participant, ":/images/resources/images/busted.png");
        emit foundTextStatus(participant, "loses bet");
    }
    else if(participant->hasBlackjack())
    {
        if(this->hasBlackjack())
        {
            emit foundTextStatus(participant, "loses bet");
        }
        else{
            emit foundStatus(participant, ":/images/resources/images/blackjackStatus.png");
            emit foundTextStatus(participant, "wins bet");
        }
    }
    else if(this->isBust() || (winScore - participant->getScore()) < (winScore - this->getScore()))
    {
        participant->setWinner(true);
        emit foundTextStatus(participant, "wins bet");
        return 1;
    }
    else if((winScore - participant->getScore()) > (winScore - this->getScore()))
    {
        this->setWinner(true);
        emit foundTextStatus(participant, "loses bet");
        return -1;
    }
    else if(participant->getScore() == this->getScore())
    {
        if(this->hasBlackjack())
        {
            emit foundTextStatus(participant, "loses bet");
            return -1;
        }
        else {
            emit foundTextStatus(participant, "ends in a draw");
        }
    }
}

