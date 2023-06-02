#include "gamewindow.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "ui_gamewindow.h"
#include "mainwindow.h"
#include <QScreen>
#include <QVBoxLayout>
#include "Stylesheet.h"

GameWindow::GameWindow(MainWindow *parent, int playersNum) :
    ui(new Ui::GameWindow),
    m_parent(parent),
    m_game(playersNum)
{
    ui->setupUi(this);

    this->setWindowTitle("Blackjack by Yezhkova");

    BackgroundMusicPath = ":/sounds/resources/sounds/cyber.wav";
    BackgroundPicPath = ":/images/resources/images/gameBgImg.jpg";
    CardBackPicPath = ":/images/resources/images/back1.jpg";

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    this->setFixedSize(m_globWidth, m_globHeight);
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    this->move(x, y);
//    int x = screenGeometry.width();
//    int y = screenGeometry.height();
//    this->setFixedSize(x,y);

    m_backgroundLabel = new QLabel(this);
    drawPicture(m_backgroundLabel
                , BackgroundPicPath
                , 0, 0, m_globWidth, m_globHeight);

    m_musicThread = new MusicThread(BackgroundMusicPath, -2);
    m_musicThread->start();

    m_cardDeckLabel = new QLabel(this);
    drawPicture(m_cardDeckLabel
                , CardBackPicPath
                , 1100, 50, Card::cardWidth, Card::cardHeight);

    int initPointX = m_globWidth / (playersNum+1);
    int initPointY = 280;

    m_soundControl = new QCheckBox(this);
    m_soundControl->setCheckState(Qt::Checked);
    m_soundControl->setText("Play background music");

    m_soundControl->setStyleSheet(checkBoxStyle);
    m_soundControl->setGeometry(50, 50, 350, 100);
    connect(m_soundControl, &QCheckBox::stateChanged, m_musicThread, &MusicThread::muteSound);

    for(int i = 0; i < m_game.getPlayersNum(); ++i)
    {
        int newinitPointX = initPointX * (i+1);

        QGroupBox* groupBox = new QGroupBox(QString("Player%1Box").arg(i+1), this);
//        groupBox->setStyleSheet("border:0px;");
        int boxWidth = Card::cardWidth+230;
        int boxHeight = Card::cardHeight+300;

        groupBox->setGeometry(newinitPointX - boxWidth/2, initPointY, boxWidth, boxHeight);

        QLabel* scoreLabel = new QLabel(QString("Player%1ScoreLabel").arg(i+1), groupBox);
        int scoreWidth = 100;
        int scoreHeight = 70;
        scoreLabel->setStyleSheet("opacity: 0.5;font-size: 15px; color: white; font-weight: bold;");
        scoreLabel->setGeometry(boxWidth/2 - scoreWidth/2, 0, scoreWidth, scoreHeight);

        QLabel* handLabels[12];
        int handPositionX = 0;
        int handPositionY = 40;
        // Create a card label for every possible card in each hand
        // No hand can hold more than 11 cards
        for(int card = 0; card < 11; ++card)
        {
            handLabels[card] = new QLabel(QString("Player%1CardLabel%2").arg(i+1).arg(card+1), groupBox);
            handLabels[card]->setGeometry(0 + handPositionX, 0 + handPositionY, Card::cardWidth, Card::cardHeight);
            drawPicture(handLabels[card]
                        , CardBackPicPath
                        , 0 + handPositionX, 0 + handPositionY
                        , Card::cardWidth, Card::cardHeight);
            handPositionX += 10;
            handPositionY += 20;
        }
        QLabel* nameLabel = new QLabel(groupBox);
        int nameWidth = 120;
        int nameHeight = 60;
        nameLabel->setStyleSheet("opacity: 0.5;font-size: 20px; color: white; font-weight: bold;");
        if(i == 0) {
            nameLabel->setText("User");
        }
        else {
            nameLabel->setText(QString("Player%1").arg(i+1));
        }
        nameLabel->setGeometry(boxWidth/2 - nameHeight/2, boxHeight-60, nameWidth, nameHeight);

//        QVBoxLayout* singleBox = new QVBoxLayout(groupBox);
//        singleBox->addWidget(scoreLabel);
//        for(int card = 0; card < 11; ++card)
//        {
//            singleBox->addWidget(handLabels[card]);
//        }
//        singleBox->addWidget(nameLabel);
        m_participantsSetups.push_back(groupBox);
    }

    int buttonsX = m_participantsSetups[0]->x() - 160;

    m_hitButton = new QPushButton(this);
    m_hitButton->setGeometry(buttonsX, 360, 100, 40);
    m_hitButton->setText("Hit");

    m_standButton = new QPushButton(this);
    m_standButton->setGeometry(buttonsX, 460, 100, 40);
    m_standButton->setText("Stand");

}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::drawPicture(
    QLabel *label
    , const QString& fileName
    , int posX, int posY
    , int width, int height)
{
    label->setPixmap(QPixmap(fileName)); // Replace with your own image
    label->setScaledContents(true);
    label->setGeometry(posX, posY, width, height);
}

