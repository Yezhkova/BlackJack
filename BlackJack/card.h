#pragma once

#include <string>
#include <map>
#include <QString>

class Card
{
public:
    Card(std::string suit, std::string name, int num)
        : m_suit(suit)
        , m_name(name)
        , m_number(num)
        {
        };

//    Card(Card&& c)
//        : m_suit(c.m_suit)
//        , m_name(c.m_name)
//        , m_number(c.m_number)
//    {
//    };

//    Card(const Card& c)
//        : m_suit(c.m_suit)
//        , m_name(c.m_name)
//        , m_number(c.m_number)

//    {
//    };

//    ~Card() = default;

    std::string getSuit() const {
        return m_suit;
    }

    QString getName() const {
        return QString::fromStdString(m_suit+m_name);
    }

    int getNumber() const {
        return m_number;
    }

private:
    std::string m_suit;
    std::string m_name;
    int m_number;


public:
    static std::map<std::string, int> cards;
    static int fullDeck;
    static int cardWidth;
    static int cardHeight;

};

