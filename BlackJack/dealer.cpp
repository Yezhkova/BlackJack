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

void Dealer::makeSuit(const QString& suit)
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
        if(numberOfCards == 2 && participant->getName()=="Dealer" && i == 1) {
            emit cardDealt(participant, "back", false, true);
        }
        else{
            emit cardDealt(participant, it->getFullName(), true, true);
        }
        m_deck.erase(it);
    }
}
bool Dealer::checkForBlackjack(Participant *participant)
{
    if(participant->getHand().size() == 2 && participant->getScore() == winScore)
    {
        participant->setBlackjack(true);
        participant->setActive(false);
        qDebug() << participant->getName() << ' ' << participant->getHand().size() << ' ' << participant->getScore() << ' ' << participant->hasBlackjack();
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
        QString text = "loses " + QString::number(player->getBet()) + '$';
        emit foundTextStatus(player, text);
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
            QString text = "wins " + QString::number(1.5*player->getBet()) + '$';
            emit foundTextStatus(player, text);
            player->winMoney(1.5 * player->getBet());
        }
    }

    else if(this->isBust() || (winScore - player->getScore()) < (winScore - this->getScore()))
    {
        QString text = "wins " + QString::number(player->getBet()) + '$';
        emit foundTextStatus(player, text);
        player->winMoney(player->getBet());
        return 1;
    }

    else if((winScore - player->getScore()) > (winScore - this->getScore()))
    {
        QString text = "loses " + QString::number(player->getBet()) + '$';
        emit foundTextStatus(player, text);
        player->loseMoney(player->getBet());
        return -1;
    }

    else if(player->getScore() == this->getScore())
    {
        if(this->hasBlackjack())
        {
            QString text = "loses " + QString::number(player->getBet()) + '$';
            emit foundTextStatus(player, text);
            player->loseMoney(player->getBet());
            return -1;
        }
        else {
            emit foundTextStatus(player, "ends in a draw");
        }
    }

//    emit balanceUpdated(player);
}

