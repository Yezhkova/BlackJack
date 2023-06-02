#include "musicthread.h"
#include "qeventloop.h"
#include "qsoundeffect.h"
#include <QMediaPlayer>
#include <QAudioOutput>

MusicThread::MusicThread(const QString& fileName, int loopCount)
    :m_fileName(fileName)
    , m_loopCount(loopCount)
{
    m_effect.setSource(QUrl::fromLocalFile(m_fileName));
    m_effect.setLoopCount(m_loopCount);
}

void MusicThread::run()
{
    m_effect.play();
    QEventLoop eventloop;
    eventloop.exec();
}

void MusicThread::endLater()
{
    m_effect.setLoopCount(0);
    m_effect.setMuted(true);
    this->quit();
    this->requestInterruption();
}

void MusicThread::muteSound(int arg)
{
    if(arg == 0) m_effect.setMuted(true);
    else if(arg == 2) m_effect.setMuted(false);
}

void MusicThread::unmuteSound()
{
    m_effect.setMuted(false);
}

