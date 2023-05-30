#include "mainwindow.h"
#include "gamewindow.h"
#include "musicthread.h"
#include "qsoundeffect.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Hello!");
    for(int i = 2; i < 4; ++i){
        ui->playersNumberComboBox->addItem(QString::number(i));
    }
    QPixmap background(":/images/resources/images/playtech.jpg");
    ui->bgLabel->setPixmap(background);
    ui->bgLabel->lower();
    this->setFixedSize(800,600);
    this->show();
    // Start the thread to play the background music
    musicThread = new MusicThread;
    musicThread->start();
}

void MainWindow::on_quitButton_clicked()
{
    musicThread->quit();
    musicThread->requestInterruption();

    QApplication::quit();
}

void MainWindow::on_playButton_clicked()
{
    musicThread->quit();
    musicThread->requestInterruption();

    QString players = ui->playersNumberComboBox->currentText();
    gamewindow = new GameWindow( this, players.toInt() );
    gamewindow->show();
    this->hide();
}

void MainWindow::playMusic(const QString& s)
{
    QSoundEffect effect;
    effect.setSource(QUrl::fromLocalFile(s));
    effect.setVolume(1.0);
    effect.play();
    QEventLoop eventloop;
    eventloop.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
