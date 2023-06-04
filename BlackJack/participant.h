#pragma once

#include "card.h"
#include <vector>
#include <QDebug>
#include <QObject>

class Participant: public QObject
{

    Q_OBJECT

public:
    explicit Participant(QObject *parent = nullptr, QString name = "")
        : QObject(parent)
        , m_name(name)
        {};
    Participant(const Participant& p)
        : QObject(p.parent())
        , m_name(p.m_name)
        {};
    Participant(Participant&& p) noexcept
        : QObject(p.parent())
        , m_name(p.m_name)
        {};

//    Participant(Participant&& p)
//        : m_hand(p.m_hand)
//        , m_score(p.m_score)
//        , m_is_user(p.m_is_user)
//        , m_is_dealer(p.m_is_dealer)
//        , m_winner(p.m_winner)
//        , m_has_blackjack(p.m_has_blackjack)
//        , m_is_bust(p.m_is_bust)
//        , m_is_active(p.m_is_active)
//        , m_is_soft(p.m_is_soft)
//    {
//    };

//    ~Participant(){};

    std::vector<Card>& getHand()
    {
        return m_hand;
    }

    int getScore() const
    {
        return m_score;
    }

    void takeCard(const Card& card);

    bool checkForBlackjack();

    void setAsUser()
    {
        m_is_user = true;
    }

    void setAsDealer()
    {
        m_is_dealer = true;
    }

    bool is_user()
    {
        return m_is_user;
    }

    bool is_dealer()
    {
        return m_is_dealer;
    }

    bool isWinner()
    {
        return m_winner;
    }

    void setWinner(bool win)
    {
        m_winner = win;
    }

    bool isActive()
    {
        return m_is_active;
    }

    void setActive(bool active)
    {
        m_is_active = active;
    }

    bool isSoft()
    {
        return m_is_soft;
    }

    void setSoft(bool soft)
    {
        m_is_soft = soft;
    }

    bool hasBlackjack()
    {
        return m_has_blackjack;
    }

    void setBlackjack(bool bj)
    {
        m_has_blackjack = bj;
    }

    bool isBust()
    {
        return m_is_bust;
    }

    void setBust(bool bust)
    {
        m_is_bust = bust;
    }

    const QString& getName() const
    {
        return m_name;
    }

    void setName(const QString& name)
    {
        m_name = name;
    }

signals:
    void scoreUpdated(int score);

private:
    std::vector<Card> m_hand;
    int m_score = 0;
    bool m_is_user = false;
    bool m_is_dealer = false;
    bool m_winner = false;
    bool m_has_blackjack = false;
    bool m_is_bust = false;
    bool m_is_active = true;
    bool m_is_soft = false;
    QString m_name;

public:
    static int winScore;
};

