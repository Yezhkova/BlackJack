#pragma once
#include "qsoundeffect.h"
#include <QThread>

class MusicThread : public QThread
{
public:
    MusicThread(const QString& fileName, int loopCount);
    void run() override;
    void endLater();

public slots:

    void muteSound(int arg);
    void unmuteSound();

private:
    QSoundEffect m_effect;
    QString m_fileName;
    int m_loopCount;
};

