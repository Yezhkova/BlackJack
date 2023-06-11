#include "mainwindow.h"
#include "gamewindow.h"
#include "musicthread.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    BackgroundMusicPath = ":/sounds/resources/sounds/ukulele.wav";
    BackgroundPicPath =  ":/images/resources/images/playtech.jpg";

    ui->setupUi(this);
    this->setWindowTitle("Hello!");
    for(int i = 2; i < 4; ++i){
        ui->playersNumberComboBox->addItem(QString::number(i));
    }
    QPixmap background(BackgroundPicPath);
    ui->bgLabel->setPixmap(background);
    ui->bgLabel->lower();
    this->setFixedSize(800,600);
    this->show();

    // Start the thread to play the background music
    musicThread = new MusicThread(BackgroundMusicPath, -2);
    musicThread->start();
}

void MainWindow::on_quitButton_clicked()
{
    musicThread->endLater();
    QApplication::quit();
}

void MainWindow::on_playButton_clicked()
{
    musicThread->endLater();
    QString players = ui->playersNumberComboBox->currentText();
    gamewindow = new GameWindow( this, players.toInt());
    gamewindow->show();
    this->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete musicThread;
}
