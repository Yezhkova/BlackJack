#include "gamewindow.h"
#include "qcombobox.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "ui_gamewindow.h"
#include "mainwindow.h"
#include <QScreen>
#include <QVBoxLayout>
#include "Stylesheet.h"
#include <QStandardItemModel>
#include <QTimer>
#include <QPropertyAnimation>

GameWindow::GameWindow(MainWindow *parent, int playersNum) :
    ui(new Ui::GameWindow),
    m_parent(parent),
    m_game(playersNum)
{
    ui->setupUi(this);

    this->setWindowTitle("Blackjack by Yezhkova");

    BackgroundMusicPath = ":/sounds/resources/sounds/cyber.wav";
    MouseMusicPath = ":/sounds/resources/sounds/tz.wav";
    CardMusicPath = ":/sounds/resources/sounds/t-ch.wav";
    BackgroundPicPath = ":/images/resources/images/gameBgImg.jpg";
    CardBackPicPath = ":/images/resources/images/back1.jpg";
    BlackJackPicPath = ":/images/resources/images/blackjackStatus.png";

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    this->setFixedSize(m_globWidth, m_globHeight);
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    this->move(x, y);

    setupBackground();
    setupSound();
    setupPlayers(playersNum);
    setupControl();
    setupDealer();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::setupBackground()
{
    m_backgroundLabel = new QLabel(this);
    m_backgroundLabel->setGeometry(0, 0, m_globWidth, m_globHeight);
    drawPicture(m_backgroundLabel, BackgroundPicPath);
}

void GameWindow::setupSound()
{
    m_musicThread = new MusicThread(BackgroundMusicPath, -2);
    m_musicThread->start();
    m_mouseThread = new MusicThread(MouseMusicPath, 1);
    m_mouseThread->start();
    m_cardThread = new MusicThread(CardMusicPath, 1);
//    m_cardThread->start();

    m_soundControl = new QCheckBox(this);
    m_soundControl->setCheckState(Qt::Checked);
    m_soundControl->setText("Play background music");
    m_soundControl->setStyleSheet(checkBoxStyle);
    m_soundControl->setGeometry(50, 50, 350, 100);
    connect(m_soundControl, &QCheckBox::stateChanged, m_musicThread, &MusicThread::muteSound);
}

void GameWindow::setupPlayers(int playersNum)
{
    int initPointX = m_globWidth / (playersNum+1) + 70;
    int initPointY = 280;

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
        int scoreTextWidth = 145;
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
        scoreLabel->setStyleSheet(greaterYellowFont);
        scoreLabel->setGeometry(scoreX, scoreTextY, scoreWidth, scoreTextHeight);
        connect(&m_game.getDealer(), &Dealer::cardDealt
                , this, &GameWindow::displayScore);

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
        balanceLabel->setStyleSheet(greaterYellowFont);
        balanceLabel->setText("0");
        balanceLabel->setGeometry(balanceX, balanceTextY, balanceWidth, balanceTextHeight);
        connect(&m_game, &GameProcess::betsMade, this, &GameWindow::displayBalance);

        int initHandPositionX = 30;
        int initHandPositionY = balanceTextY + balanceTextHeight + 5;
        int handPositionX = initHandPositionX;
        int handPositionY = initHandPositionY;

        for(int card = 0; card < 11; ++card)
        {
            QLabel *handLabel = new QLabel(groupBox);
            handLabel->setObjectName(QString("Player%1CardLabel%2").arg(i).arg(card));
            handLabel->setGeometry(0 + handPositionX, 0 + handPositionY, Card::cardWidth, Card::cardHeight);

            //            if(card < 4){
            //            drawPicture(handLabel, CardBackPicPath);
            //            }
            handPositionX += 10;
            handPositionY += 20;
        }

        QLabel* textStatusLabel = new QLabel(groupBox);
        textStatusLabel->setObjectName(QString("Player%1TextStatusLabel").arg(i));
        int textStatusLabelWidth = boxWidth;
        int textStatusLabelHeight = 25;
        int textStatusLabelX =  0;
        int textStatusLabelY = boxHeight - 25;
        textStatusLabel->setStyleSheet(greaterYellowFont);
        textStatusLabel->setGeometry(textStatusLabelX, textStatusLabelY
                                      , textStatusLabelWidth, textStatusLabelHeight);
        connect(&m_game.getDealer(), &Dealer::foundTextStatus
                , this, &GameWindow::displayTextStatus);


        QLabel* imageStatusLabel = new QLabel(groupBox);
        imageStatusLabel->setObjectName(QString("Player%1ImageStatusLabel").arg(i));
        int imageStatusLabelWidth = boxWidth-100;
        int imageStatusLabelHeight = boxWidth/2;
        int imageStatusLabelX = initHandPositionX;
        int imageStatusLabelY = initHandPositionY;
        imageStatusLabel->setGeometry(imageStatusLabelX, imageStatusLabelY
                                      , imageStatusLabelWidth, imageStatusLabelHeight);
        connect(&m_game.getDealer(), &Dealer::foundStatus
                , this, &GameWindow::displayStatus);

        m_participantsSetups[QString("Player%1").arg(i)] = groupBox;
    }
}

void GameWindow::setupDealer()
{
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
    scoreLabel->setStyleSheet(greaterYellowFont);
    scoreLabel->setText("0");
    scoreLabel->setGeometry(scoreX + nameWidth, scoreY, scoreWidth, scoreHeight);

    int initHandPositionX = 0;
    int initHandPositionY = scoreY + scoreHeight+10;
    int handPositionX = initHandPositionX;
    int handPositionY = initHandPositionY;

    for(int card = 0; card < 11; ++card)
    {
        QLabel *handLabel = new QLabel(groupBox);
        handLabel->setObjectName(QString("DealerCardLabel%1").arg(card));
        handLabel->setGeometry(0 + handPositionX, handPositionY, Card::cardWidth, Card::cardHeight);
        //        if(card < 3){
        //            drawPicture(handLabel, CardBackPicPath);
        //        }
        handPositionX += 20;
        handPositionY  += 5;
    }

    QLabel* imageStatusLabel = new QLabel(groupBox);
    imageStatusLabel->setObjectName(QString("DealerImageStatusLabel"));
    int imageStatusLabelWidth = dealerBoxWidth;
    int imageStatusLabelHeight = imageStatusLabelWidth/2;
    int imageStatusLabelX = initHandPositionX;
    int imageStatusLabelY = initHandPositionY;
    imageStatusLabel->setGeometry(imageStatusLabelX, imageStatusLabelY
                                  , imageStatusLabelWidth, imageStatusLabelHeight);
    connect(&m_game.getDealer(), &Dealer::foundStatus
            , this, &GameWindow::displayStatus);


    m_participantsSetups["Dealer"] = groupBox;

    connect(&m_game.getDealer()
            , &Dealer::cardDealt
            , this
            , &GameWindow::displayCard);
}

void GameWindow::setupControl()
{
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
    connect(m_hitButton, &QPushButton::released, &m_game.getDealer()
            , [this] {m_game.getDealer().dealCards(&m_game.getPlayers()[0], 1);});
    connect(m_hitButton, &QPushButton::released, m_mouseThread, &MusicThread::run);
//    connect(m_hitButton, &QPushButton::released,this,
//            [this]{MusicThread *m = new MusicThread(MouseMusicPath, 1); m->run(); });

    m_standButton = new QPushButton("Stand", this);
    m_standButton->setGeometry(userActionsX, standY, buttonWidth, buttonHeight);
    m_standButton->setStyleSheet(smallerFont);
    m_standButton->setEnabled(false);
    connect(m_standButton, &QPushButton::released, &m_game.getPlayers()[0]
            , [this] {m_game.getPlayers()[0].setActive(false);});
    connect(m_standButton, &QPushButton::released, m_hitButton, [this]{m_hitButton->setEnabled(false);});
    connect(m_standButton, &QPushButton::released, this, &GameWindow::results);
    connect(m_standButton, &QPushButton::released, m_mouseThread, &MusicThread::run);

//    connect(m_standButton, &QPushButton::released,this,
//            [this]{MusicThread *m = new MusicThread(MouseMusicPath, 1); m->run(); });


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
    m_betBox->setCurrentIndex(0);
    connect(m_betBox, &QComboBox::activated, &m_game.getPlayers()[0], &Player::setBet);
    emit m_betBox->activated(0);

    m_playButton = new QPushButton("Play!", this);
    m_playButton->setGeometry(userActionsX, betBoxY+150, buttonWidth, buttonHeight);
    m_playButton->setStyleSheet(smallerFont);
    m_playButton->setEnabled(true);
    connect(m_playButton, &QPushButton::released, &m_game, &GameProcess::playRound);
    connect(&m_game, &GameProcess::roundStarted, this, [this]{ enableButton(m_playButton, false); });
    connect(&m_game, &GameProcess::roundStarted, this, [this]{ enableButton(m_hitButton, true); });
    connect(&m_game, &GameProcess::roundStarted, this, [this]{ enableButton(m_standButton, true); });
    connect(m_playButton, &QPushButton::released, m_mouseThread, &MusicThread::run);

//    connect(m_playButton, &QPushButton::released,this,
//            [this]{MusicThread *m = new MusicThread(MouseMusicPath, 1); m->run(); });


    // TODO difference between released and clicked

}

void GameWindow::drawPicture(QLabel *label, const QString& fileName)
{
    QPixmap pixmap(fileName);
    label->setScaledContents(true);
    label->setPixmap(pixmap);
}

void GameWindow::drawAnimation(QLabel *label, const QString& fileName)
{
//    QWidget window;
//    QVBoxLayout layout(&window);

//    QLabel picture;
//    QPixmap pixmap(fileName);
//    label->setScaledContents(true);
//    label->setPixmap(pixmap);

//    layout.addWidget(&picture);
//    window.setLayout(&layout);
//    window.setGeometry(100, 100, 300, 300);
//    window.show();
    drawPicture(label, fileName);
    int startY = -label->height();  // Initial starting position (above the window)
    int endY = label->y() + label->height();  // Desired stopping position (Y-coordinate)

//    QPropertyAnimation animation(label, "pos");
    QPropertyAnimation *animation = new QPropertyAnimation(label, "pos");
    animation->setDuration(2000);  // Animation duration (in milliseconds)
    animation->setStartValue(QPoint(label->x(), -label->height()));
    animation->setEndValue(QPoint(label->x(), label->y()));
    animation->setEasingCurve(QEasingCurve::InOutQuad);  // Optional easing curve for smoother animation
    connect(animation, &QPropertyAnimation::valueChanged, [label]() {label->update(); });
    animation->start();
}

void GameWindow::displayCard(Participant *receiver, std::_List_iterator<Card> it)
{
    QString place =  receiver->getName() + "CardLabel" + QString::number(receiver->getHand().size());
    auto cardLabel = m_participantsSetups[receiver->getName()]->findChild<QLabel*>(place);

    if(cardLabel == nullptr) qDebug() << place << ": no such value";
    QString cardToDisplay = ":/images/resources/images/" + it->getName() + ".png";
    drawAnimation(cardLabel, cardToDisplay);
//    drawPicture(cardLabel, cardToDisplay);
    connect(this, &GameWindow::displayingCard, m_cardThread, &MusicThread::run);
//    emit displayingCard();
}

void GameWindow::displayScore(Participant *receiver)
{
    QString place =  receiver->getName() + "ScoreLabel";
    auto scoreLabel = m_participantsSetups[receiver->getName()]->findChild<QLabel*>(place);
    scoreLabel->setText(QString::number(receiver->getScore()));
}

void GameWindow::displayBalance(Player *receiver)
{
    QString place =  receiver->getName() + "BalanceLabel";
    auto balanceLabel = m_participantsSetups[receiver->getName()]->findChild<QLabel*>(place);
    balanceLabel->setText(QString::number(receiver->getBalance() - receiver->getBet()));
}

void GameWindow::displayStatus(Participant *receiver, const QString& filepath)
{
    QString place =  receiver->getName() + "ImageStatusLabel";
    auto imgStatLabel = m_participantsSetups[receiver->getName()]->findChild<QLabel*>(place);
    imgStatLabel->setScaledContents(true);
    drawPicture(imgStatLabel, filepath);
    QTimer::singleShot(3000, [imgStatLabel]() {imgStatLabel->clear();});
}

void GameWindow::displayTextStatus(Participant *receiver, const QString& text)
{
    QString place =  receiver->getName() + "TextStatusLabel";
    auto textStatusLabel = m_participantsSetups[receiver->getName()]->findChild<QLabel*>(place);
    textStatusLabel->setText(text);
}

void GameWindow::enableButton(QPushButton *button, bool active)
{
    button->setEnabled(active);
}

void GameWindow::checkPossibleBets(Player *player)
{
    auto * model = qobject_cast<QStandardItemModel*>(m_betBox->model());
    for(int i = 0; i < Player::bets.size(); ++i) {
        auto * item = model->item(i);
        item->setEnabled(player->getBalance() >= Player::bets[i]);
    }
}

void GameWindow::results()
{
    m_game.getDealer().compareScore(&m_game.getDealer());
    for(auto& player: m_game.getPlayers())
    {
        m_game.getDealer().compareScore(&player);
        emit displayBalance(&player);
    }
    if(m_game.getPlayers()[0].getBalance() > 0)
    {
        m_playButton->setEnabled(true);
    }
}
