#pragma once

#include <string>
#include <map>
#include <QString>

class Card
{
public:
    Card(QString suit, QString name, int num)
        : m_suit(suit)
        , m_name(name)
        , m_cardScore(num)
        {
        };

    QString getSuit() const {
        return m_suit;
    }

    QString getFullName() const {
        return m_suit+m_name;
    }

    QString getName() const {
        return m_name;
    }

    int getCardScore() const {
        return m_cardScore;
    }

private:
    QString m_suit;
    QString m_name;
    int m_cardScore;


public:
    static std::map<QString, int> cards;
    static int fullDeck;
    static int cardWidth;
    static int cardHeight;

};

