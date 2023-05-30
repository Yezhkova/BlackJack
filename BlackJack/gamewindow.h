#pragma once
#include "gameprocess.h"
#include <QMainWindow>

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

private:
    Ui::GameWindow *ui;
    MainWindow *m_parent;
    GameProcess m_game;
};

