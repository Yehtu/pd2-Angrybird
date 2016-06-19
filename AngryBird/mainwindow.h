#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QList>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <iostream>

#include "how.h"
#include "gameitem.h"
#include "land.h"
#include "shoot.h"
#include "setbird.h"
#include "bird.h"
#include "redbird.h"
#include "yellowbird.h"
#include "bluebird.h"
#include "bigbird.h"
#include "whitebird.h"
#include "greenbird.h"
#include "egg.h"
#include "pig.h"
#include "wood.h"
#include "rock.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void gameInit();
    void dataInit();
    void setBtn();
    void deleteAll();
    void killPig();
    void damageBarrier();

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();   
    void QUITSLOT(); // For debug slot
    void gameInform();
    void setBgm();
    void pauseGame();
    void restartGame();
    void exitGame();    

private:
    Ui::MainWindow *ui;
    how *h;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    QGraphicsLineItem *line1;
    QGraphicsLineItem *line2;
    QMediaPlayer *bgm;
    QLabel *scoredisplay, *scoreboard, *numdisplay, *birdnum, *pause, *npause;
    QPushButton *exit, *restart, *inform, *music;
    Shoot *shoot;
    Setbird *setbird[6];
    Bird *bird[6];
    Pig *pig[3];
    Wood *wood[6];
    Rock *rock[3];
    Egg *egg;
    Bluebird *blue1;
    Bluebird *blue2;
    Bigbird *big;

    bool ready; // press on the bird
    bool launch; // launch birds
    bool skillused; // use skill
    bool gamepause; // pause game
    bool musicon; // turn on music
    bool eggexist; //new egg
    bool cloneexist; // new bluebirds
    bool bigexist; // new bigbird
    // pigs killed
    bool pig0_killed, pig1_killed, pig2_killed;
    bool killall;
    // wood damaged
    bool wood0_damaged, wood1_damaged, wood2_damaged, wood3_damaged, wood4_damaged, wood5_damaged;
    // rock damaged
    bool rock0_damaged, rock1_damaged, rock2_damaged;

    int num; // total birds
    int score; //total score
    // score of each pig
    int score_p0, score_p1, score_p2;
    // score of each wood
    int score_w0, score_w1, score_w2, score_w3, score_w4, score_w5;
    // score of each rock
    int score_r0, score_r1, score_r2;

    int pig_0, pig_1, pig_2;
    int rock_0, rock_1, rock_2;
    int wood_0, wood_1, wood_2, wood_3, wood_4, wood_5;
    // check end game
    int spdx, spdy;
    float bound;

};

#endif // MAINWINDOW_H
