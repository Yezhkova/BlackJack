#pragma once
#include "gameprocess.h"
#include "musicthread.h"
#include "qcheckbox.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "ui_gamewindow.h"
#include <QMainWindow>
#include <QGroupBox>
#include <QComboBox>

namespace Ui {
class GameWindow;
}
class MainWindow;
class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(MainWindow *parent = nullptr, int playersNum = 1);
    ~GameWindow();

    void closeEvent(QCloseEvent *event) override
    {
        exit(0);
        // Accept the close event to allow the window to close
//        event->accept();
    }

    void drawPicture(
        QLabel *label
        , const QString& fileName);

public slots:
    void displayCard(const QString& receiver
                     , const QString& cardName
                     , int cardNum);
    void displayScore(const QString& receiver, int score);

signals:

private:
    Ui::GameWindow *ui;
    MainWindow *m_parent;
    MusicThread *m_musicThread;
//    MusicThread *effectsThread;
    GameProcess m_game;
    int m_globWidth = 1280;
    int m_globHeight = 720;
    QLabel *m_backgroundLabel;

    std::map<QString, QGroupBox*> m_participantsSetups;

    QCheckBox *m_soundControl;

    QPushButton *m_hitButton;
    QPushButton *m_standButton;
    QLabel *m_makeYourBetLabel;
    QPushButton *m_playButton;
    QComboBox *m_betBox;

   // Sound file locations
    QString BackgroundMusicPath;
    QString BackgroundPicPath;
    QString CardBackPicPath;

};

