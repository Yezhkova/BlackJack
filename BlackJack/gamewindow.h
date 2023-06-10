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

    void drawPicture(QLabel *label, const QString& fileName);
    void drawAnimation(QLabel *label, const QString& fileName);

public slots:
    void displayCard(Participant *receiver, const QString& cardName, bool flag, bool animate);
    void displayScore(Participant *receiver,const QString& cardName, bool flag);
    void displayBalance(Player *receiver);
    void enableButton(QPushButton *button, bool active);
    void setSkin(int index);
    void displayStatus(Participant *receiver, const QString& filepath);
    void displayTextStatus(Participant *receiver, const QString& text);
    void results();
    void clearAll();

signals:
    void displayingCard();

private:
    void setupBackground();
    void setupSound();
    void setupPlayers(int playersNum);
    void setupPlayButton();
    void setupDealer();
    void setupControl();
    void checkPossibleBets(Player *receiver);

private:
    Ui::GameWindow *ui;
    MainWindow *m_parent;
    MusicThread *m_musicThread;
    MusicThread *m_mouseSoundThread;
    MusicThread *m_cardThread;

    GameProcess m_game;
    int m_globWidth = 1280;
    int m_globHeight = 720;
    QLabel *m_backgroundLabel;

    std::map<QString, QGroupBox*> m_participantsSetups;

    QCheckBox *m_soundControl;
    QComboBox *m_skinControl;

    QPushButton *m_hitButton;
    QPushButton *m_standButton;
    QLabel *m_makeYourBetLabel;
    QPushButton *m_playButton;
    QComboBox *m_betBox;

   // Sound file locations
    QString BackgroundMusicPath;
    QString MouseMusicPath;
    QString CardMusicPath;
    QString BackgroundPicPath;
    QString CardBackPicPath;
    QString BlackJackPicPath;

    QString m_skin;

};

