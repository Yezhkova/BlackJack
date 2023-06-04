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

    m_backgroundLabel = new QLabel(this);
    m_backgroundLabel->setGeometry(0, 0, m_globWidth, m_globHeight);
    drawPicture(m_backgroundLabel, BackgroundPicPath);

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

        QGroupBox* groupBox = new QGroupBox(this);
        groupBox->setObjectName(QString("Player%1Box").arg(i));
        groupBox->setStyleSheet("border:0px;");
        int boxWidth = Card::cardWidth+230;
        int boxHeight = Card::cardHeight+300;

        groupBox->setGeometry(newinitPointX - boxWidth/2, initPointY, boxWidth, boxHeight);

        QLabel* scoreTextLabel = new QLabel(groupBox);
        int scoreTextWidth = 140;
        int scoreTextHeight = 25;
        int scoreTextX = 0;
        int scoreTextY = 20;
        scoreTextLabel->setStyleSheet(greaterFont);
        if(i == 0) {
            scoreTextLabel->setText("User Score:");
        }
        else {
            scoreTextLabel->setText(QString("Player %1 Score:").arg(i));
        }
        scoreTextLabel->setGeometry(scoreTextX, scoreTextY, scoreTextWidth, scoreTextHeight);

        QLabel* scoreLabel = new QLabel("0", groupBox);
        scoreLabel->setObjectName(QString("Player%1ScoreLabel").arg(i));
        int scoreWidth = 50;
        int scoreX = scoreTextX + scoreTextWidth;
        scoreLabel->setStyleSheet(greaterFont);
        scoreLabel->setGeometry(scoreX, scoreTextY, scoreWidth, scoreTextHeight);

        QLabel *balanceTextLabel = new QLabel("Balance:", groupBox);
        int balanceTextWidth = 90;
        int balanceTextHeight = 25;
        int balanceTextX = scoreTextX;
        int balanceTextY = scoreTextY + scoreTextHeight + 5;
        balanceTextLabel->setStyleSheet(greaterFont);
        balanceTextLabel->setGeometry(balanceTextX, balanceTextY, balanceTextWidth, balanceTextHeight);

        QLabel *balanceLabel = new QLabel(0, groupBox);
        balanceLabel->setObjectName(QString("Player%1BalanceLabel").arg(i));
        int balanceWidth = 50;
        int balanceX = balanceTextX + balanceTextWidth;
        balanceLabel->setStyleSheet(greaterFont);
        balanceLabel->setText("0");
        balanceLabel->setGeometry(balanceX, balanceTextY, balanceWidth, balanceTextHeight);

        int handPositionX = 30;
        int handPositionY = balanceTextY + balanceTextHeight + 5;
        for(int card = 0; card < 11; ++card)
        {
            QLabel *handLabel = new QLabel(groupBox);
            handLabel->setObjectName(QString("Player%1CardLabel%2").arg(i).arg(card));
            handLabel->setGeometry(0 + handPositionX, 0 + handPositionY, Card::cardWidth, Card::cardHeight);
//            if(card < 4){
//            drawPicture(handLabel
//                        , CardBackPicPath
//                        , 0 + handPositionX, 0 + handPositionY
//                        , Card::cardWidth, Card::cardHeight);
//            }
            handPositionX += 10;
            handPositionY += 20;
        }

        m_participantsSetups[QString("Player%1").arg(i)] = groupBox;
    }

    int buttonWidth = 100;
    int buttonHeight = 40;
    int spacing = 30;

    int userActionsX = m_participantsSetups["Player0"]->x() - 140;
    int hitY = 320;
    int standY = hitY+buttonHeight+spacing;

    int makeYourBetLabelWidth = 150;
    int makeYourBetLabelHeight = 27;
    int betBoxWidth = 50;
    int betBoxHeight = 25;

    int makeYourBetLabelX = userActionsX + buttonWidth/2 - makeYourBetLabelWidth/2;
    int makeYourBetLabelY = standY+buttonHeight+spacing;
    int betBoxX = makeYourBetLabelX + makeYourBetLabelWidth/2 - betBoxWidth/2;
    int betBoxY = makeYourBetLabelY + makeYourBetLabelHeight + 20;

    m_hitButton = new QPushButton("Hit", this);
    m_hitButton->setGeometry(userActionsX, hitY, buttonWidth, buttonHeight);
    m_hitButton->setStyleSheet(smallerFont);
    m_hitButton->setEnabled(false);

    m_standButton = new QPushButton("Stand", this);
    m_standButton->setGeometry(userActionsX, standY, buttonWidth, buttonHeight);
    m_standButton->setStyleSheet(smallerFont);
    m_standButton->setEnabled(false);

    m_betBox = new QComboBox(this);

    m_makeYourBetLabel = new QLabel("Make your bet:", this);
    m_makeYourBetLabel->setStyleSheet(greaterFont);
    m_makeYourBetLabel->setGeometry(makeYourBetLabelX, makeYourBetLabelY
                                  , makeYourBetLabelWidth, makeYourBetLabelHeight);

    m_betBox->setStyleSheet(smallerFont);
    m_betBox->addItem("5");
    m_betBox->addItem("25");
    m_betBox->addItem("50");
    m_betBox->addItem("75");
    m_betBox->addItem("100");
    m_betBox->setGeometry(betBoxX, betBoxY, betBoxWidth, betBoxHeight);
    connect(m_betBox, &QComboBox::activated, &m_game.getPlayers()[0], &Player::setBet);

    m_playButton = new QPushButton("Play!", this);
    m_playButton->setGeometry(userActionsX, betBoxY+150, buttonWidth, buttonHeight);
    m_playButton->setStyleSheet(smallerFont);
    m_playButton->setEnabled(true);
    connect(m_playButton, &QPushButton::clicked, &m_game, &GameProcess::playRound);

    QGroupBox* groupBox = new QGroupBox(this);
    groupBox->setObjectName("DealerBox");
    groupBox->setStyleSheet("border:0px;");
    int dealerBoxWidth = Card::cardWidth+202;
    int dealerBoxHeight = Card::cardHeight+100;

    groupBox->setGeometry(m_globWidth/2 - dealerBoxWidth/2, 40, dealerBoxWidth, dealerBoxHeight);

    int scoreWidth = 50;
    int scoreHeight = 25;
    int scoreX = 0;
    int scoreY = 0;

    QLabel *nameLabel = new QLabel("Dealer Score:", groupBox);
    int nameWidth = 130;
    nameLabel->setStyleSheet(greaterFont);
    nameLabel->setGeometry(scoreX, scoreY, nameWidth, scoreHeight);

    QLabel* scoreLabel = new QLabel("0", groupBox);
    scoreLabel->setObjectName("DealerScoreLabel");
    scoreLabel->setStyleSheet(greaterFont);
    scoreLabel->setText("0");
    scoreLabel->setGeometry(scoreX + nameWidth, scoreY, scoreWidth, scoreHeight);

    int handPositionX = 0;
    int handPositionY = scoreY + scoreHeight+10;
    for(int card = 0; card < 11; ++card)
    {
        QLabel *handLabel = new QLabel(groupBox);
        handLabel->setObjectName(QString("DealerCardLabel%1").arg(card));
        handLabel->setGeometry(0 + handPositionX, handPositionY, Card::cardWidth, Card::cardHeight);
        if(card < 3){
            drawPicture(handLabel, CardBackPicPath);
        }
        handPositionX += 20;
    }
    m_participantsSetups["Dealer"] = groupBox;

    connect(&m_game.getDealer()
            , &Dealer::cardDealt
            , this
            , &GameWindow::displayCard);

//    connect();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::drawPicture(
    QLabel *label
    , const QString& fileName)
{
    label->setPixmap(QPixmap(fileName)); // Replace with your own image
    label->setScaledContents(true);
    label->setGeometry(label->x(), label->y()
                       , label->width(), label->height());
}

void GameWindow::displayCard(const QString& receiver // Player0
                 , const QString& cardName // SuitName
                 , int cardNum)
{
    QString place =  receiver + "CardLabel" + QString::number(cardNum);
    auto cardLabel = m_participantsSetups[receiver]->findChild<QLabel*>(place);

    if(cardLabel == nullptr) qDebug() << place << ": no such value";
    QString cardToDisplay = ":/images/resources/images/" + cardName + ".png";
    drawPicture(cardLabel, cardToDisplay);
}

void GameWindow::displayScore(const QString& receiver, int score)
{
}

