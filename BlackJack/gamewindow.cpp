#include "gamewindow.h"
#include "qcombobox.h"
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

    int initPointX = m_globWidth / (playersNum+1) + 70;
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
        groupBox->setTitle("");
        groupBox->setStyleSheet("border:0px;");
        int boxWidth = Card::cardWidth+230;
        int boxHeight = Card::cardHeight+300;

        groupBox->setGeometry(newinitPointX - boxWidth/2, initPointY, boxWidth, boxHeight);

        QLabel* scoreTextLabel = new QLabel(QString("Player%1ScoreTextLabel").arg(i+1), groupBox);
        int scoreTextWidth = 140;
        int scoreTextHeight = 20;
        int scoreTextX = 0;
        int scoreTextY = 20;
        scoreTextLabel->setStyleSheet("opacity: 0.5;font-size: 20px; color: white; font-weight: bold;");
        if(i == 0) {
            scoreTextLabel->setText("User Score:");
        }
        else {
            scoreTextLabel->setText(QString("Player %1 Score:").arg(i+1));
        }
        scoreTextLabel->setGeometry(scoreTextX, scoreTextY, scoreTextWidth, scoreTextHeight);

        QLabel* scoreLabel = new QLabel(QString("Player%1ScoreLabel").arg(i+1), groupBox);
        int scoreWidth = 50;
        int scoreHeight = 20;
        int scoreX = scoreTextX + scoreTextWidth;
        int scoreY = 20;
        scoreLabel->setStyleSheet("opacity: 0.5;font-size: 20px; color: white; font-weight: bold;");
        scoreLabel->setText("0");
        scoreLabel->setGeometry(scoreX, scoreY, scoreWidth, scoreHeight);

        QLabel *balanceTextLabel = new QLabel(QString("Player%1BalanceTextLabel").arg(i+1), groupBox);
        int balanceTextWidth = 90;
        int balanceTextHeight = 20;
        int balanceTextX = scoreTextX;
        int balanceTextY = scoreTextY + scoreTextHeight + 5;
        balanceTextLabel->setStyleSheet("opacity: 0.5;font-size: 20px; color: white; font-weight: bold;");
        balanceTextLabel->setText("Balance:");
        balanceTextLabel->setGeometry(balanceTextX, balanceTextY, balanceTextWidth, balanceTextHeight);

        QLabel* balanceLabel = new QLabel(QString("Player%1BalanceLabel").arg(i+1), groupBox);
        int balanceWidth = 50;
        int balanceHeight = 20;
        int balanceX = balanceTextX + balanceTextWidth;
        int balanceY = balanceTextY;
        balanceLabel->setStyleSheet("opacity: 0.5;font-size: 20px; color: white; font-weight: bold;");
        balanceLabel->setText("0");
        balanceLabel->setGeometry(balanceX, balanceY, balanceWidth, balanceHeight);

        QLabel* handLabels[12];
        int handPositionX = 25;
        int handPositionY = balanceY + balanceHeight + 5;
        for(int card = 0; card < 11; ++card)
        {
            handLabels[card] = new QLabel(QString("Player%1CardLabel%2").arg(i+1).arg(card+1), groupBox);
            handLabels[card]->setGeometry(0 + handPositionX, 0 + handPositionY, Card::cardWidth, Card::cardHeight);
            handLabels[card]->setText("");
            if(card < 3){
            drawPicture(handLabels[card]
                        , CardBackPicPath
                        , 0 + handPositionX, 0 + handPositionY
                        , Card::cardWidth, Card::cardHeight);
            }
            handPositionX += 10;
            handPositionY += 20;
        }
        m_participantsSetups.push_back(groupBox);
    }

    int buttonWidth = 100;
    int buttonHeight = 40;
    int spacing = 30;

    int userActionsX = m_participantsSetups[0]->x() - 140;
    int hitY = 320;
    int standY = hitY+buttonHeight+spacing;

    int makeYourBetLabelWidth = 150;
    int makeYourBetLabelHeight = 20;
    int betBoxWidth = 50;
    int betBoxHeight = 25;

    int makeYourBetLabelX = userActionsX + buttonWidth/2 - makeYourBetLabelWidth/2;
    int makeYourBetLabelY = standY+buttonHeight+spacing;
    int betBoxX = makeYourBetLabelX + makeYourBetLabelWidth/2 - betBoxWidth/2;
    int betBoxY = makeYourBetLabelY + makeYourBetLabelHeight + spacing;

    m_hitButton = new QPushButton(this);
    m_hitButton->setGeometry(userActionsX, hitY, buttonWidth, buttonHeight);
    m_hitButton->setStyleSheet("font-size: 15px");
    m_hitButton->setText("Hit");
    m_hitButton->setEnabled(false);

    m_standButton = new QPushButton(this);
    m_standButton->setGeometry(userActionsX, standY, buttonWidth, buttonHeight);
    m_standButton->setStyleSheet("font-size: 15px");
    m_standButton->setText("Stand");
    m_standButton->setEnabled(false);

    m_betBox = new QComboBox(this);

    m_makeYourBetLabel = new QLabel(this);
    m_makeYourBetLabel->setStyleSheet("opacity: 0.5;font-size: 20px; color: white; font-weight: bold;");
    m_makeYourBetLabel->setText("Make your bet:");
    m_makeYourBetLabel->setGeometry(makeYourBetLabelX, makeYourBetLabelY
                                  , makeYourBetLabelWidth, makeYourBetLabelHeight);

    m_betBox->setStyleSheet("opacity: 0.5;font-size: 15px; font-weight: bold;");
    m_betBox->addItem("5");
    m_betBox->addItem("25");
    m_betBox->addItem("50");
    m_betBox->addItem("75");
    m_betBox->addItem("100");
    m_betBox->setGeometry(betBoxX, betBoxY, betBoxWidth, betBoxHeight);
    //            connect(betBox, &QComboBox::)

    QGroupBox* groupBox = new QGroupBox(QString("DealerBox"), this);
    groupBox->setTitle("");
    groupBox->setStyleSheet("border:0px;");
    int dealerBoxWidth = Card::cardWidth+202;
    int dealerBoxHeight = Card::cardHeight+100;

    groupBox->setGeometry(m_globWidth/2 - dealerBoxWidth/2, 40, dealerBoxWidth, dealerBoxHeight);

    int scoreWidth = 50;
    int scoreHeight = 20;
    int scoreX = 0;
    int scoreY = 0;

    QLabel *nameLabel = new QLabel(groupBox);
    int nameWidth = 130;
    nameLabel->setStyleSheet("opacity: 0.5;font-size: 20px; color: white; font-weight: bold;");
    nameLabel->setText("Dealer Score:");
    nameLabel->setGeometry(scoreX, scoreY, nameWidth, scoreHeight);

    QLabel* scoreLabel = new QLabel(QString("DealerScoreLabel"), groupBox);
    scoreLabel->setStyleSheet("opacity: 0.5;font-size: 20px; color: white; font-weight: bold;");
    scoreLabel->setText("0");
    scoreLabel->setGeometry(scoreX + nameWidth, scoreY, scoreWidth, scoreHeight);

    QLabel* handLabels[12];
    int handPositionX = 0;
    int handPositionY = scoreY + scoreHeight+10;
    for(int card = 0; card < 11; ++card)
    {
        handLabels[card] = new QLabel(QString("DealerCardLabel%1").arg(card+1), groupBox);
        handLabels[card]->setGeometry(0 + handPositionX, handPositionY, Card::cardWidth, Card::cardHeight);
        handLabels[card]->setText("");
        if(card < 3){
            drawPicture(handLabels[card]
                        , CardBackPicPath
                        , 0 + handPositionX, handPositionY
                        , Card::cardWidth, Card::cardHeight);
        }
        handPositionX += 20;
    }
    m_participantsSetups.push_back(groupBox);
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

