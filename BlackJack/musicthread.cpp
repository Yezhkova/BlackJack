#include "musicthread.h"
#include "qeventloop.h"
#include "qsoundeffect.h"
#include <QMediaPlayer>
#include <QAudioOutput>

MusicThread::MusicThread()
{
}

void MusicThread::run()
{
    QSoundEffect effect;
    effect.setSource(QUrl::fromLocalFile(":/sounds/resources/sounds/ukulele.wav"));
    effect.setLoopCount(QSoundEffect::Infinite);
    effect.setVolume(0.25f);
    effect.play();
    QEventLoop eventloop;
    eventloop.exec();
}
