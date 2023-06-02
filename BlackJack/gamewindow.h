#pragma once
#include "gameprocess.h"
#include "musicthread.h"
#include "qcheckbox.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "ui_gamewindow.h"
#include <QMainWindow>
#include <QGroupBox>

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
        , const QString& fileName
        , int posX, int posY
        , int width, int height);

public slots:


signals:

private:
    Ui::GameWindow *ui;
    MainWindow *m_parent;
    MusicThread *m_musicThread;
//    MusicThread *effectsThread;
    GameProcess m_game;
    int m_globWidth = 1280;
    int m_globHeight = 720;

    std::vector<QGroupBox*> m_participantsSetups;

    // Grouping hands of cards
    QGroupBox *m_playerCards;
    QGroupBox *m_dealersCards;

    // Array of card placeholders
    QLabel *m_dealersHand[12];
    QLabel *m_playersHand[12];

    QPushButton *m_hitButton;
    QPushButton *m_standButton;
    QCheckBox *m_soundControl;

    QLabel *m_cardDeckLabel;
    QLabel *m_backgroundLabel;
    // Mapping button functions
//    QSignalMapper *ButtonMapping;

    // Graphic elements
//    QLabel* labelBetValue;
//    QLabel* labelStackValue;
//    QLabel* labelGameStatus;
//    QLabel* labelResultsSummary;
//    QLabel* labelBetRing;
//    QLabel* labelStackSpot;
//    QLabel* labelBustText;
//    QLabel* labelDealersBustText;
//    QLabel* labelBlackjackText;
//    QLabel* labelDealersBlackjackText;
//    QLabel* labelPlayersHandValue;
//    QLabel* labelDealersHandValue;
//    QLabel* labelHandValueSpot;
//    QLabel* labelDealersHandValueSpot;
//    QLabel* labelResultsBubble;
//    QLabel* labelStatusBubble;

    // About Box elements
//    QSignalMapper *AboutBoxMapper;
//    QWidget *AboutBox;
//    QVBoxLayout *AboutLayout;
//    QHBoxLayout *TextLayout;
//    QHBoxLayout *ButtonLayout;
//    QVBoxLayout *PicLayout;
//    QLabel *labelAboutPicture;
//    QLabel *labelAbout;
//    QString AboutBoxText;
//    QPushButton *OKButton;
//    QPushButton *LicenceButton;
//    QPushButton *CreditsButton;
//    QPushButton *AboutButton;

//    // Sound file locations
    QString BackgroundMusicPath;
    QString BackgroundPicPath;
    QString CardBackPicPath;

};

