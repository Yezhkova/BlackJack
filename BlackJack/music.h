#pragma once
#include "qobject.h"
#include "qsoundeffect.h"

class Music: public QObject
{
    Q_OBJECT

public:
    Music();
    ~Music();

public slots:
    void PlaySoundEffect();
    void mute();
signals:
    void finished();

private:
    QSoundEffect* m_pAlarmSound;
};

