#pragma once

#include <string>

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

    int getNumber() const {
        return m_number;
    }

private:
    std::string m_suit;
    std::string m_name;
    int m_number;
};

