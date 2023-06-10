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

    std::vector<Card>& getHand()
    {
        return m_hand;
    }

    int getScore() const
    {
        return m_score;
    }

    void takeCard(const Card& card);

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

    bool isActive()
    {
        return m_is_active;
    }

    void setActive(bool active)
    {
        m_is_active = active;
    }

    bool canPlay()
    {
        return m_can_play;
    }

    void setCanPlay(bool can)
    {
        m_can_play = can;
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

    void addScore(int score)
    {
        m_score += score;
    }

    void resetScore()
    {
        m_score = 0;
    }

    void resetHand()
    {
        m_hand.clear();
    }

    void resetCanPlay()
    {
        m_can_play = true;
    }

signals:

private:
    std::vector<Card> m_hand;
    int m_score = 0;
    QString m_name;

protected:
    bool m_is_user = false;
    bool m_is_dealer = false;
    bool m_has_blackjack = false;
    bool m_is_bust = false;
    bool m_is_active = true;
    bool m_is_soft = false;
    bool m_can_play = true;

public:
    static int winScore;
};

