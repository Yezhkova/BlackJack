#include "music.h"

Music::Music()
{
    m_pAlarmSound = new QSoundEffect;
    m_pAlarmSound->setSource(QUrl::fromLocalFile(":/sounds/resources/sounds/ukulele.wav"));
}

Music::~Music()
{
    delete m_pAlarmSound;
}

void Music::PlaySoundEffect()
{
    m_pAlarmSound->play();
}

void Music::mute()
{
    m_pAlarmSound->setMuted(true);
}
