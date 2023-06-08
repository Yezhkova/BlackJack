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
void Dealer::compareScore(Participant *participant)
{
    if(participant->isBust())
    {
        emit foundStatus(participant, ":/images/resources/images/bustStatus.png");
    }
    else if(participant->hasBlackjack())
    {
        emit foundStatus(participant, ":/images/resources/images/blackjackStatus.png");
    }
}

int Dealer::compareScore(Player *player)
{
    if(player->isBust())
    {
        emit foundStatus(player, ":/images/resources/images/bustStatus.png");
        emit foundTextStatus(player, "loses bet");
        player->loseMoney(player->getBet());
    }
    else if(player->hasBlackjack())
    {
        if(this->hasBlackjack())
        {
            emit foundTextStatus(player, "ends in a draw");
        }
        else{
            emit foundStatus(player, ":/images/resources/images/blackjackStatus.png");
            emit foundTextStatus(player, "wins bet");
            player->winMoney(1.5 * player->getBet());
        }
    }
    else if(this->isBust() || (winScore - player->getScore()) < (winScore - this->getScore()))
    {
        player->setWinner(true);
        emit foundTextStatus(player, "wins bet");
        player->winMoney(player->getBet());
        return 1;
    }
    else if((winScore - player->getScore()) > (winScore - this->getScore()))
    {
        this->setWinner(true);
        emit foundTextStatus(player, "loses bet");
        player->loseMoney(player->getBet());
        return -1;
    }
    else if(player->getScore() == this->getScore())
    {
        if(this->hasBlackjack())
        {
            emit foundTextStatus(player, "loses bet");
            player->loseMoney(player->getBet());
            return -1;
        }
        else {
            emit foundTextStatus(player, "ends in a draw");
        }
    }

    emit balanceUpdated(player);
}

