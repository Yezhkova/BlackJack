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

    void closeEvent(QCloseEvent *event) override
    {
        exit(0);
    }

    GameWindow *gamewindow;

private slots:
    void on_quitButton_clicked();

    void on_playButton_clicked();

signals:
    void muteBackgroundMusic();

private:
    Ui::MainWindow *ui;
    MusicThread *musicThread;

    QString BackgroundMusicPath;
    QString BackgroundPicPath;

};
