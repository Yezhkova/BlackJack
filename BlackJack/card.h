#pragma once

#include <string>
#include <map>
class Card
{
public:
    Card(std::string suit, std::string name, int num)
        : m_suit(suit)
        , m_name(name)
        , m_number(num)
        {
        };

    std::string getSuit() const {
        return m_suit;
    }

    std::string getName() const {
        return m_name;
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
};

