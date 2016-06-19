#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);   
    // Enable the event Filter
    qApp->installEventFilter(this);
    // background music
    bgm = new QMediaPlayer();
    bgm->setMedia(QUrl("qrc:/image/bgm.mp3"));
    //set scoreboard
    scoredisplay = new QLabel(this);
    scoredisplay->setStyleSheet("color:black; background-color: transparent; font: 32pt Comic Sans MS");
    scoredisplay->setText("Score :");
    scoredisplay->setGeometry(900, 10, 150, 50);
    scoredisplay->show();
    scoreboard = new QLabel(this);
    scoreboard->setStyleSheet("color:black; background-color: transparent; font: 32pt Comic Sans MS");
    scoreboard->setGeometry(1055, 10, 100, 50);
    scoreboard->show();
    //set number of birds
    numdisplay = new QLabel(this);
    numdisplay->setPixmap(QPixmap(":/image/numdisplay.png").scaled(80,51));
    numdisplay->setGeometry(700, 10, 80, 51);
    numdisplay->show();
    birdnum = new QLabel(this);
    birdnum->setStyleSheet("color:black; background-color: transparent; font: 32pt Comic Sans MS");
    birdnum->setGeometry(790, 12, 50, 50);
    birdnum->show();
    gameInit();
    dataInit();
    setBtn();
    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    /*gameInit();
    dataInit();
    setBtn();
    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);*/
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{    
    QMouseEvent *mos = dynamic_cast <QMouseEvent*>(event);
    QKeyEvent *kp = dynamic_cast <QKeyEvent*>(event);
    if(event->type() == QEvent::MouseButtonPress)
    {      
        if( gamepause == false )
        {
            if( mos->button() == Qt::LeftButton )
            {
                // 滑鼠在彈弓的鳥上
                if( mos->screenPos().x() > 248 && mos->screenPos().x() <= 284 )
                {
                    if( mos->screenPos().y() > 430 && mos->screenPos().y() <= 463 )
                    {
                        line1->setLine(-10,-10,-10,-10);
                        line2->setLine(-10,-10,-10,-10);
                        line1->show();
                        line2->show();
                        ready = true;
                        return true;
                    }
                }
                else
                {
                // 避免 buttons 誤觸 skill
                if( mos->screenPos().y() > 195 )
                {
                    if( skillused == false )
                    {
                        bird[num+1]->skill();
                        if(num == 0)
                        {
                            egg = new Egg(bird[num+1]->getPosition().x, bird[num+1]->getPosition().y-3, 0.1f, &timer, QPixmap(":/image/egg.png"), world, scene);
                            egg->setLinearVelocity(b2Vec2(0, 5));
                            itemList.push_back(egg);
                            eggexist = true;
                        }
                        if(num == 2)
                        {
                            float bx = bird[num+1]->getPosition().x;
                            float by = bird[num+1]->getPosition().y;
                            int vx = bird[num+1]->getLinearVelocity().x;
                            int vy = bird[num+1]->getLinearVelocity().y;
                            blue1 = new Bluebird(bx, by+2, 0.4f, &timer, QPixmap(":/image/BlueBird.png"), world, scene);
                            blue1->setLinearVelocity(b2Vec2(vx, vy+2));
                            itemList.push_back(blue1);
                            blue2 = new Bluebird(bx, by-2, 0.4f, &timer, QPixmap(":/image/BlueBird.png"), world, scene);
                            blue2->setLinearVelocity(b2Vec2(vx, vy-2));
                            itemList.push_back(blue2);
                            cloneexist = true;
                        }
                        if(num == 1)
                        {
                            float bx = bird[num+1]->getPosition().x;
                            float by = bird[num+1]->getPosition().y;
                            int vx = bird[num+1]->getLinearVelocity().x;
                            int vy = bird[num+1]->getLinearVelocity().y;
                            delete bird[num+1];
                            big = new Bigbird(bx, by, 0.8f, &timer, QPixmap(":/image/BigBirds.png"), world, scene);
                            big->setLinearVelocity(b2Vec2(vx, vy));
                            itemList.push_back(big);
                            bigexist = true;
                        }
                        skillused = true;
                    }
                }
                }
            }
        }
        //cout << "Now event x: " << mos->screenPos().x()<< " event y: " << mos->screenPos().y() << endl;
        //std::cout << "Press !" << std::endl ;
        return false;
    }
    if(event->type() == QEvent::MouseMove)
    {
        if(ready == true)
        {
            if( mos->screenPos().x() > 122 && mos->screenPos().x() <= 284 )
            {
                if( mos->screenPos().y() > 360 && mos->screenPos().y() <= 528 )
                {
                    line2->setLine(mos->screenPos().x()-100,mos->screenPos().y()-100,190,330);
                    line1->setLine(mos->screenPos().x()-100,mos->screenPos().y()-100,156,330);
                    setbird[num]->setPos(mos->screenPos().x()-112,mos->screenPos().y()-140);
                    launch = true;
                    return true;
                }
            }
        }
        //std::cout << "Move !" << std::endl ;
        return false;
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {        
        if( launch == true )
        {
            scene->removeItem(setbird[num]);
            delete setbird[num];            
            float a , b;
            a = (mos->screenPos().x()-112)/30;
            b = (680-mos->screenPos().y())/30;
            int v , w ;
            v = (266 - (mos->screenPos().x()))/5;
            w = (mos->screenPos().y() - 446)/5;
            if( num == 0 )
            {
                delete bird[1];
                if( eggexist == true ) delete egg;
                bird[0] = new Greenbird(a, b, 0.4f, &timer, QPixmap(":/image/GreenBird.png"), world, scene);
                bird[0]->setLinearVelocity(b2Vec2(v,w));
                itemList.push_back(bird[0]);
                setbird[num-1]->setPos(150,300);
            }
            if( num == 1 )
            {
                if( bigexist == true ) delete big;
                else {delete bird[2];}
                bird[1] = new Whitebird(a, b, 0.4f, &timer, QPixmap(":/image/WhiteBird.png"), world, scene);
                bird[1]->setLinearVelocity(b2Vec2(v,w));
                itemList.push_back(bird[1]);
                setbird[num-1]->setPos(150,300);
            }
            if( num == 2 )
            {
                delete bird[3];
                bird[2] = new Bigbird(a, b, 0.4f, &timer, QPixmap(":/image/BigBird.png"), world, scene);
                bird[2]->setLinearVelocity(b2Vec2(v,w));
                itemList.push_back(bird[2]);
                if( cloneexist == true )
                {
                    delete blue1;
                    delete blue2;
                }
                setbird[0]->setPos(90,390);                
                setbird[num-1]->setPos(150,300);
            }
            if( num == 3 )
            {
                delete bird[4];
                bird[3] = new Bluebird(a, b, 0.4f, &timer, QPixmap(":/image/BlueBird.png"), world, scene);
                bird[3]->setLinearVelocity(b2Vec2(v,w));
                itemList.push_back(bird[3]);
                setbird[1]->setPos(90,392);
                setbird[0] = new Setbird();
                QPixmap b0;
                b0.load(":/image/GreenBird.png");
                setbird[0]->setPixmap(b0);
                setbird[0]->setPos(30,390);
                scene->addItem(setbird[0]);               
                setbird[num-1]->setPos(150,300);
            }
            if( num == 4 )
            {  
                delete bird[5];
                bird[4] = new Yellowbird(a, b, 0.4f, &timer, QPixmap(":/image/YellowBird.png"), world, scene);
                bird[4]->setLinearVelocity(b2Vec2(v,w));
                itemList.push_back(bird[4]);
                setbird[2]->setPos(90,394);
                setbird[1] = new Setbird();
                QPixmap b1;
                b1.load(":/image/WhiteBird.png");
                setbird[1]->setPixmap(b1);
                setbird[1]->setPos(30,392);
                scene->addItem(setbird[1]);                
                setbird[num-1]->setPos(150,300);
            }
            if( num == 5 )
            {
                bird[5] = new Redbird(a, b, 0.4f, &timer, QPixmap(":/image/RedBird.png"), world, scene);
                bird[5]->setLinearVelocity(b2Vec2(v,w));
                itemList.push_back(bird[5]);
                setbird[3]->setPos(90,394);
                setbird[2] = new Setbird();
                QPixmap b2;
                b2.load(":/image/BigBird.png");
                setbird[2]->setPixmap(b2);
                setbird[2]->setPos(30,394);
                scene->addItem(setbird[2]);               
                setbird[num-1]->setPos(150,300);
            }
            line1->hide();
            line2->hide();
            --num;
            birdnum->setText(QString::number(num+1));
            ready = false;
            launch = false;
            skillused = false;
            return true;
        }   
        //std::cout << "Release !" << std::endl ;
        return false;
    }

    if(event->type() == QEvent::KeyPress)
    {
        if( kp->key() == Qt::Key_P )
        {
            if(gamepause)
            {
                delete pause;

                gamepause = false;
                bgm->play();
                timer.start(100/6);
            }
            else
            {                
                pause = new QLabel(this);
                pause->setPixmap(QPixmap(":/image/pause.png").scaled(45,45));
                pause->setGeometry(290, 14, 45, 45);
                pause->show();

                gamepause = true;
                bgm->stop();
                timer.stop();
                scene->update();
            }
        }
    }
    return false;
}

void MainWindow::damageBarrier()
{
    if( wood0_damaged == false )
    {
        if( score_w0 > 15)
        {
            wood0_damaged = true;
            delete wood[0];
        }
        else
        {
            wood_0 = wood[0]->getLinearVelocity().x + wood[0]->getLinearVelocity().y;
            if( wood_0 > 3 )
            {
                score_w0 += 1;
                score += 1;
            }
        }
    }
    if( wood1_damaged == false )
    {
        if( score_w1 > 15)
        {
            wood1_damaged = true;
            delete wood[1];
        }
        else
        {
            wood_1 = wood[1]->getLinearVelocity().x + wood[1]->getLinearVelocity().y;
            if( wood_1 > 3 )
            {
                score_w1 += 1;
                score += 1;
            }
        }
    }
    if( wood2_damaged == false )
    {
        if( score_w2 > 15)
        {
            wood2_damaged = true;
            delete wood[2];
        }
        else
        {
            wood_2 = wood[2]->getLinearVelocity().x + wood[2]->getLinearVelocity().y;
            if( wood_2 > 3 )
            {
                score_w2 += 1;
                score += 1;
            }
        }
    }
    if( wood3_damaged == false )
    {
        if( score_w3 > 25)
        {
            wood3_damaged = true;
            delete wood[3];
        }
        else
        {
            wood_3 = wood[3]->getLinearVelocity().x + wood[3]->getLinearVelocity().y;
            if( wood_3 > 3 )
            {
                score_w3 += 1;
                score += 1;
            }
        }
    }
    if( wood4_damaged == false )
    {
        if( score_w4 > 18)
        {
            wood4_damaged = true;
            delete wood[4];
        }
        else
        {
            wood_4 = wood[4]->getLinearVelocity().x + wood[4]->getLinearVelocity().y;
            if( wood_4 > 3 )
            {
                score_w4 += 1;
                score += 1;
            }
        }
    }
    if( wood5_damaged == false )
    {
        if( score_w5 > 35)
        {
            wood5_damaged = true;
            delete wood[5];
        }
        else
        {
            wood_5 = wood[5]->getLinearVelocity().x + wood[5]->getLinearVelocity().y;
            if( wood_5 > 3 )
            {
                score_w5 += 1;
                score += 1;
            }
        }
    }

    if( rock0_damaged == false )
    {
        if( score_r0 > 20)
        {
            rock0_damaged = true;
            delete rock[0];
        }
        else
        {
            rock_0 = rock[0]->getLinearVelocity().x + rock[0]->getLinearVelocity().y;
            if( rock_0 > 3 )
            {
                score_r0 += 1;
                score += 1;
            }
        }
    }
    if( rock1_damaged == false )
    {
        if( score_r1 > 20)
        {
            rock1_damaged = true;
            delete rock[1];
        }
        else
        {
            rock_1 = rock[1]->getLinearVelocity().x + rock[1]->getLinearVelocity().y;
            if( rock_1 > 3 )
            {
                score_r1 += 1;
                score += 1;
            }
        }
    }
    if( rock2_damaged == false )
    {
        if( score_r2 > 40)
        {
            rock2_damaged = true;
            delete rock[2];
        }
        else
        {
            rock_2 = rock[2]->getLinearVelocity().x + rock[2]->getLinearVelocity().y;
            if( rock_2 > 3 )
            {
                score_r2 += 1;
                score += 1;
            }
        }
    }
}

void MainWindow::killPig()
{
    if(pig0_killed == false)
    {
        if( score_p0 > 250)
        {
            pig0_killed = true;
            delete pig[0];
        }
        else
        {
            pig_0 = pig[0]->getLinearVelocity().x + pig[0]->getLinearVelocity().y;
            if( pig_0 > 3 )
            {
                score_p0 += 15;
                score += 15;
                //std::cout << ">3" << std::endl ;
            }
        }
    }
    if(pig1_killed == false)
    {
        if( score_p1 > 200)
        {
            pig1_killed = true;
            delete pig[1];
        }
        else
        {
            pig_1 = pig[1]->getLinearVelocity().x + pig[1]->getLinearVelocity().y;
            if( pig_1 > 3 )
            {
                score_p1 += 15;
                score += 15;
            }
        }
    }
    if(pig2_killed == false)
    {
        if( score_p2 > 200)
        {
            pig2_killed = true;
            delete pig[2];
        }
        else
        {
            pig_2 = pig[2]->getLinearVelocity().x + pig[2]->getLinearVelocity().y;
            if( pig_2 > 3 )
            {
                score_p2 += 10;
                score += 10;
            }
        }
    }
    if( pig0_killed == true && pig1_killed == true && pig2_killed == true )
    {
        score += (500 + (num+1)*100);
        killall = true;
    }
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
    damageBarrier();
    killPig();
    scoreboard->setText(QString::number(score));
    if( killall == true )
    {
        bgm->stop();
        QString result;
        QTextStream(&result) << "LEVEL CLEARED ! " << " \n Your score : " << score << "\n\n  Play again ?";
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, " Congratulation ", result, QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::No) exitGame(); //end game
        else restartGame();
    }
    if( num == -1 )
    {
        spdx = bird[0]->getLinearVelocity().x;
        spdy = bird[0]->getLinearVelocity().y;
        bound = bird[0]->getPosition().x;
        //std::cout << g << std::endl;
        if(( spdx == 0 && spdy == 0 )|| bound > 45 || bound < -5 )
        {
            bgm->stop();
            QString result;
            QTextStream(&result) << "Your score : " << score << "\n\n  Try again ?";
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, " Gameover ", result, QMessageBox::Yes | QMessageBox::No);
            if(reply == QMessageBox::No) exitGame(); //end game
            else restartGame();
        }
    }
}

void MainWindow::gameInit()
{
    // background music
    bgm->play();
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    scene->setBackgroundBrush(QPixmap(":/image/background.png"));
    ui->graphicsView->setScene(scene);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(40,18),size());
    // Create ground
    itemList.push_back(new Land(20,1.5,40,3,QPixmap(":/image/ground.png").scaled(width(),height()/6.0),world,scene));
    // Create slingshot
    shoot = new Shoot();
    QPixmap sh;
    sh.load(":/image/shot.png");
    sh = sh.scaled( sh.width()*3/4, sh.height()*3/4 ,Qt::KeepAspectRatio );
    shoot->setPixmap(sh);
    shoot->setPos(150,300);
    scene->addItem(shoot);
    // Create Line
    line1 = scene->addLine(-10,-10,-10,-10,QPen(Qt::darkRed,4));
    line2 = scene->addLine(-10,-10,-10,-10,QPen(Qt::darkRed,4));

    // Create bird
    setbird[5] = new Setbird();
    QPixmap b5;
    b5.load(":/image/RedBird.png");
    setbird[5]->setPixmap(b5);
    setbird[5]->setPos(150,300);
    scene->addItem(setbird[5]);
    setbird[4] = new Setbird();
    QPixmap b4;
    b4.load(":/image/YellowBird.png");
    setbird[4]->setPixmap(b4);
    setbird[4]->setPos(90,396);
    scene->addItem(setbird[4]);
    setbird[3] = new Setbird();
    QPixmap b3;
    b3.load(":/image/BlueBird.png");
    setbird[3]->setPixmap(b3);
    setbird[3]->setPos(30,394);
    scene->addItem(setbird[3]);

    // Create barriers    
    wood[0] = new Wood(24.0f,4.0f,0.4f,1.0f,&timer,QPixmap(":/image/woodbarv.png").scaled(25,90),world,scene);
    itemList.push_back(wood[0]);
    wood[1] = new Wood(28.5f,4.0f,0.4f,1.0f,&timer,QPixmap(":/image/woodbarv.png").scaled(25,90),world,scene);
    itemList.push_back(wood[1]);
    wood[2] = new Wood(25.6f,7.0f,3.0f,0.4f,&timer,QPixmap(":/image/woodbarh.png").scaled(150,25),world,scene);
    itemList.push_back(wood[2]);
    wood[3] = new Wood(30.0f,4.0f,2.0f,0.5f,&timer,QPixmap(":/image/box.png").scaled(96,60),world,scene);
    itemList.push_back(wood[3]);
    rock[0] = new Rock(26.0f,8.5f,0.7f,0.8f,&timer,QPixmap(":/image/rocksq.png").scaled(42,42),world,scene);
    itemList.push_back(rock[0]);
    rock[1] = new Rock(27.0f,8.5f,0.7f,0.8f,&timer,QPixmap(":/image/rocksq.png").scaled(42,42),world,scene);
    itemList.push_back(rock[1]);
    wood[4] = new Wood(27.0f,9.8f,0.8f,0.8f,&timer,QPixmap(":/image/boxsq.png").scaled(47,47),world,scene);
    itemList.push_back(wood[4]);
    wood[5] = new Wood(35.5f,4.2f,1.0f,1.2f,&timer,QPixmap(":/image/boxf.png").scaled(87,100),world,scene);
    itemList.push_back(wood[5]);
    rock[2] = new Rock(35.7f,8.0f,0.9f,&timer,QPixmap(":/image/rock.png"),world,scene);
    itemList.push_back(rock[2]);

    // Create pig
    pig[0] = new Pig(25.2f,3.4f,0.4f,&timer,QPixmap(":/image/pig1.png"),world,scene);
    itemList.push_back(pig[0]);
    pig[1] = new Pig(27.2f,10.5f,0.6f,&timer,QPixmap(":/image/pig2.png"),world,scene);
    itemList.push_back(pig[1]);
    pig[2] = new Pig(30.7f,4.5f,0.6f,&timer,QPixmap(":/image/pig2.png"),world,scene);
    itemList.push_back(pig[2]);
}

void MainWindow::dataInit()
{
    ready = false;
    launch = false;
    skillused = true;
    gamepause = false;
    musicon = true;
    // for skill
    eggexist = false;
    cloneexist = false;
    bigexist = false;
    // for pigs
    pig0_killed = false;
    pig1_killed = false;
    pig2_killed = false;
    killall = false;
    // for barrier
    wood0_damaged = false;
    wood1_damaged = false;
    wood2_damaged = false;
    wood3_damaged = false;
    wood4_damaged = false;
    wood5_damaged = false;
    rock0_damaged = false;
    rock1_damaged = false;
    rock2_damaged = false;
    // score of pigs and barrier
    score_p0 = 0;
    score_p1 = 0;
    score_p2 = 0;
    score_w0 = 0;
    score_w1 = 0;
    score_w2 = 0;
    score_w3 = 0;
    score_w4 = 0;
    score_w5 = 0;
    score_r0 = 0;
    score_r1 = 0;
    score_r2 = 0;

    num = 5;
    score = 0;
    birdnum->setText("6");
    scoreboard->setText("0");
}

void MainWindow::deleteAll()
{
    itemList.clear();
}

void MainWindow::setBtn()
{
    //create exit button
    exit = new QPushButton;
    exit->setGeometry(10, 10, 50, 50);
    exit->setIcon(QIcon(":/image/exit.png"));
    exit->setIconSize(QSize(45, 45));
    exit->setStyleSheet("background-color: transparent");
    connect(exit, SIGNAL(clicked(bool)), this, SLOT(exitGame()));
    scene->addWidget(exit);

    //create restart button
    restart = new QPushButton;
    restart->setGeometry(80, 10, 50, 50);
    restart->setIcon(QIcon(":/image/restart.png"));
    restart->setIconSize(QSize(45, 45));
    restart->setStyleSheet("background-color: transparent");
    connect(restart, SIGNAL(clicked(bool)), this, SLOT(restartGame()));
    scene->addWidget(restart);

    //create pause button
    npause = new QLabel(this);
    npause->setPixmap(QPixmap(":/image/npause.png").scaled(45,45));
    npause->setGeometry(290, 14, 45, 45);
    npause->show();
    /*pause = new QPushButton;
    pause->setGeometry(290, 10, 50, 50);
    pause->setIcon(QIcon(":/image/pause.png"));
    pause->setIconSize(QSize(45, 45));
    pause->setStyleSheet("background-color: transparent");
    connect(pause, SIGNAL(clicked(bool)), this, SLOT(pauseGame()));
    scene->addWidget(pause);*/

    //create music button
    music = new QPushButton;
    music->setGeometry(150, 10, 50, 50);
    music->setIcon(QIcon(":/image/music.png"));
    music->setIconSize(QSize(45, 45));
    music->setStyleSheet("background-color: transparent");
    connect(music, SIGNAL(clicked(bool)), this, SLOT(setBgm()));
    scene->addWidget(music);

    //create information button
    inform = new QPushButton;
    inform->setGeometry(220, 10, 50, 50);
    inform->setIcon(QIcon(":/image/how.png"));
    inform->setIconSize(QSize(45, 45));
    inform->setStyleSheet("background-color: transparent");
    connect(inform, SIGNAL(clicked(bool)), this, SLOT(gameInform()));
    scene->addWidget(inform);       
}

void MainWindow::gameInform()
{
    if(gamepause == false)
    {
        h = new how();
        h->setWindowTitle("Information");
        h->setWindowIcon(QIcon(":/image/icon.png"));
        h->show();
    }
}

void MainWindow::setBgm()
{
    if(gamepause == false)
    {
        if(musicon)
        {
            bgm->stop();
            musicon = false;
        }
        else
        {
            bgm->play();
            musicon = true;
        }
    }
}

void MainWindow::pauseGame()
{
    if(gamepause)
    {
        gamepause = false;
        bgm->play();
        timer.start(100/6);
    }
    else
    {
        gamepause = true;
        timer.stop();
        bgm->stop();
        scene->update();
    }
}

void MainWindow::restartGame()
{
    if(gamepause == false)
    {
        deleteAll();
        gameInit();
        dataInit();
        setBtn();
    }
}

void MainWindow::exitGame()
{
    if(gamepause == false)
        close();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}
