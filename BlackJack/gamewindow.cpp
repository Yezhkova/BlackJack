#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "mainwindow.h"

GameWindow::GameWindow(MainWindow *parent, int playersNum) :
    ui(new Ui::GameWindow),
    m_parent(parent),
    m_game(playersNum)
{
    ui->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete ui;
}
