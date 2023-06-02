#pragma once
#include <QMainWindow>
#include "gamewindow.h"
#include "musicthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    GameWindow *gamewindow;

private slots:
    void on_quitButton_clicked();

    void on_playButton_clicked();

signals:
    void muteBackgroundMusic();

private:
    Ui::MainWindow *ui;
    MusicThread *musicThread;

};
