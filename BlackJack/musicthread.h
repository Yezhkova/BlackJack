#pragma once
#include <QThread>

class MusicThread : public QThread
{
public:
    MusicThread();
    void run();
};

