#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <QFont>
#include <QString>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QList>
#include <Box2D/Box2D.h>
#include <gameitem.h>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <cmath>
#include <QMultimedia>
#include <QMediaPlayer>
#include <QSound>
#include <QMultimedia>
#include <QMediaPlayer>
#include <QWidget>
#include <QPushButton>
#include <QIcon>
#include <iostream>

#include "land.h"
#include "bird.h"
#include "sling.h"
#include "block.h"
#include "pig.h"
#include "bluebird.h"
#include "yellowbird.h"
#include "bigbird.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        bool eventFilter(QObject *, QEvent *event);
        void showEvent(QShowEvent *);
        void closeEvent(QCloseEvent *);
        void SetUpOBJ();
        void SetUpVRB();
        void Situation();
        ~MainWindow();

    private slots:
        void tick();
        void RestartGame();
        void QUITSLOT();

    signals:
        void quit_game();

    private:
        Ui::MainWindow *ui;
        b2World *world;
        QList<GameItem *> itemList;
        QGraphicsScene *scene;
        QTimer timer;

        QGraphicsPixmapItem *Main;
        QGraphicsPixmapItem *end;
        QGraphicsPixmapItem *LifeRemainder[4];

        QMediaPlayer *Music;

        QSound *QiQi;
        QSound *Mimi;
        QSound *ZiZi;
        QSound *FiFi;

        QPushButton *Restart;
        QPushButton *Exit;

        QLabel *ShowingScore;
        QLabel *ShowingLife;

        Bird *birdstay[4];
        Pig *pigpig[2];
        Sling *slingsling;
        Block *blockblock[6];

        int score;
        int no_mouse_click;
        int mx3;
        int my3;
        int count;
        int no_deleted;
        int fuck;
        int suck;
        int dx1,dy1,dx2,dy2;

        bool g;
        bool whetherD1,whetherD2;
        bool click_ed;
        bool checkscore;
};

#endif // MAINWINDOW_H
