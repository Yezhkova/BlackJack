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

    QPushButton *m_hitButton;
    QPushButton *m_standButton;
    QCheckBox *m_soundControl;

    QLabel *m_backgroundLabel;

    QComboBox *m_betBox;
    QLabel *m_makeYourBetLabel;
   // Sound file locations
    QString BackgroundMusicPath;
    QString BackgroundPicPath;
    QString CardBackPicPath;

};

