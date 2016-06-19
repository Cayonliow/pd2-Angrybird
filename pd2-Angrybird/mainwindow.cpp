#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qApp->installEventFilter(this);

    /*Restart= new QPushButton;
    QPixmap button1(":/Button/restart.png");
    QIcon Button1(button1);
    Restart->setFixedSize(100,100);
    Restart->setGeometry(600,10,150,100);
    Restart->setIcon(Button1);
    Restart->setIconSize(button1.rect().size());
    connect(Restart,SIGNAL(clicked(bool)),this,SLOT(RestartGame()));

    Exit= new QPushButton;
    QPixmap button2(":/Button/exit.png");
    QIcon Button2(button2);
    Exit->setFixedSize(100,100);
    Exit->setGeometry(700,10,150,100);
    Exit->setIcon(Button2);
    Exit->setIconSize(button2.rect().size());
    connect(Exit,SIGNAL(clicked(bool)),this,SLOT(close()));*/
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    SetUpVRB();
    SetUpOBJ();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
    Situation();

    if(score==10200||suck>4)
    {
        scene->addWidget(Restart);
        scene->addWidget(Exit);
        QPixmap pixmap1(":/Background/End.png");
        pixmap1=pixmap1.scaled(500,400);
        end=new QGraphicsPixmapItem();
        end->setPixmap(pixmap1);
        end->setPos(150,20);

        scene->addItem(end);
        timer.stop();
    }
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouse_event=static_cast<QMouseEvent*>(event);
        click_ed=true;
        if(no_deleted<=3)birdstay[3-no_deleted]->set_type_of_body(false);

        if (mouse_event->button() == Qt::LeftButton)
        {
            no_mouse_click++;
            g=false;
            if(no_mouse_click>=5)
            {
               count++;
               no_mouse_click=0;

               if(count%2!=0)
               {
                   if(no_deleted>=0&&no_deleted<=3)
                   {   delete LifeRemainder[no_deleted];
                       delete birdstay[3-no_deleted];

                   if(count==1)birdstay[3-no_deleted]=new Bird(6.5f,10.0f,0.50f,&timer,QPixmap(":/Bird/RedBird.png").scaled((height()-200)/9.0,(height()-200)/9.0),world,scene);
                   if(count==3)birdstay[3-no_deleted]=new Bluebird(6.5f,10.0f,0.50f,&timer,QPixmap(":/Bird/BlueBird.png").scaled((height()-200)/9.0,(height()-200)/9.0),world,scene);
                   if(count==5)birdstay[3-no_deleted]=new Yellowbird(6.5f,10.0f,0.50f,&timer,QPixmap(":/Bird/YellowBird.png").scaled((height()-200)/9.0,(height()-200)/9.0),world,scene);
                   if(count==7)
                   {
                       birdstay[3-no_deleted]=new Bigbird(6.5f,10.0f,0.70f,&timer,QPixmap(":/Bird/BigBird.png").scaled((height()-200)/6.0,(height()-200)/6.0),world,scene);
                       fuck=15;
                   }
                   QiQi->play();
                }
             }


               if(count%2==0)
               {
                    if(no_deleted>=0&&no_deleted<=3)
                    {
                        birdstay[3-no_deleted]->set_type_of_body(false);
                        birdstay[3-no_deleted]->set_linear_velocity(b2Vec2(1,1));

                    click_ed=true;
                    mx3 = QCursor::pos().x();
                    my3 = QCursor::pos().y();
                    }
                }
            }
         }

        if (mouse_event->button() == Qt::RightButton)
        {
            if(no_deleted>0&&no_deleted<=3)no_deleted--;

            if(no_deleted>=0&&no_deleted<=3)
            {
                birdstay[3-no_deleted]->SpecialSkill();
                no_deleted++;
            }
            if(fuck==15)
            {
                birdstay[0]->SpecialSkill();
            }
            g=true;
        }
      }

     else if (event->type() == QEvent::MouseMove)
     {
        if(click_ed==true&&count%2==0&&count!=0)
        {
            if(no_deleted<=3&&no_deleted>=0)
            {
                birdstay[3-no_deleted]->set_type_of_body(false);
                birdstay[3-no_deleted]->g_body->SetTransform(b2Vec2((mx3-480)*32/960,18/2-(my3-480)*32/960),0);
            }   birdstay[3-no_deleted]->set_linear_velocity(b2Vec2(1,1));

            mx3 = QCursor::pos().x();
            my3 = QCursor::pos().y();
        }
     }

     else if(event->type() == QEvent::MouseButtonRelease)
     {

        if(click_ed==true&&count%2==0&&g==false)
        {
            float O=(float)slingsling->g_body->GetPosition().y+1-(float)(my3-480)*32/960;
            float A=(float)slingsling->g_body->GetPosition().x-(float)(mx3-480)*32/960;
            float H=sqrt(pow(A,2)+pow(O,2));
            if(no_deleted>=-1&&no_deleted<=3)
            {
                FiFi->play();
                birdstay[3-no_deleted]->set_type_of_body(true);
                birdstay[3-no_deleted]->set_linear_velocity(b2Vec2((15*A/H),(15*O/H)));
                suck++;
                no_deleted++;
            }
        }

        click_ed=false;
     }

    return false;
}

void MainWindow::Situation()
{
    double speed1=pigpig[0]->g_body->GetLinearVelocity().x+pigpig[0]->g_body->GetLinearVelocity().y;
    double speed2=pigpig[1]->g_body->GetLinearVelocity().x+pigpig[1]->g_body->GetLinearVelocity().y;
    double rot1=pigpig[0]->g_body->GetAngularVelocity();
    double rot2=pigpig[1]->g_body->GetAngularVelocity();

    if(count>2)
    {
        if((abs(speed1)>0.01||abs(rot1)>0.01)&&whetherD1==false)
        {
            delete pigpig[0];
            ZiZi->play();
            whetherD1=true;
            score=score+100;
            ShowingScore->setText("<h1><font color=black>Score : "+QString::number(score));
        }

        if((abs(speed2)>0.01||abs(rot2)>0.001)&&whetherD2==false)
        {
            delete pigpig[1];
            ZiZi->play();
            whetherD2=true;
            score=score+100;
            ShowingScore->setText("<h1><font color=black>Score : "+QString::number(score));
        }

        if(whetherD1==true&&whetherD2==true&&checkscore==false)
        {
            score=score+10000;
            ShowingScore->setText("<h1><font color=black>Score : "+QString::number(score));
            checkscore=true;
        }
    }
}

void MainWindow::SetUpOBJ()
{
    //setting QGraphicsScene
    scene = new QGraphicsScene(0, 0, 960, 540);
    ui->graphicsView->setScene(scene);

    //create world
    world = new b2World(b2Vec2(0.0f, -9.8f));

    //setting Size
    GameItem::setGlobalSize(QSizeF(32.0f, 18.0f),size());

    //setting BackGround
    QPixmap Mainscreen(":/Background/Sakura_background.png");
    Mainscreen=Mainscreen.scaled(1000,600);
    Main=new QGraphicsPixmapItem();
    Main->setPixmap(Mainscreen);
    Main->setPos(0,0);
    scene->addItem(Main);

    //seting Score
    ShowingScore=new QLabel(this);
    ShowingScore->setFont(QFont("Time",10,QFont::Bold));
    ShowingScore->setText("<h1><font color=black>Score : "+QString::number(score));
    ShowingScore->setGeometry(20,-70,400,200);
    ShowingScore->show();

    ShowingLife=new QLabel(this);
    ShowingLife->setFont(QFont("Time",10,QFont::Bold));
    ShowingLife->setText("<h1><font color=black>Life : ");
    ShowingLife->setGeometry(20,-10,400,200);
    ShowingLife->show();

    //adding pics of life
    QPixmap LifeImg(":/Life/Life.png");
    LifeImg=LifeImg.scaled(50,50);

    for(int i=0;i<4;i++)
    {
        LifeRemainder[i]=new QGraphicsPixmapItem();
        LifeRemainder[i]->setPixmap(LifeImg);
        LifeRemainder[i]->setPos(50+(i+1)*50,70);
        scene->addItem(LifeRemainder[i]);
    }

    //push back all the objects to the world
    itemList.push_back(new Land(16.0, 1.5, 32.0, 3.0, QPixmap(":/land/land.png").scaled(960,75), world, scene));

    slingsling=new Sling(6.0f,6.0f,1.5f,0.005f,QPixmap(":/Sling/Sling.png").scaled(45,110),world,scene);
    itemList.push_back(slingsling);

    birdstay[0] = new Bigbird(1.0f,7.0f,0.70f,&timer,QPixmap(":/Bird/BigStay.png").scaled(50, 50),world,scene);
    birdstay[1] = new Yellowbird(1.0f,8.0f,0.50f,&timer,QPixmap(":/Bird/YellowStay.png").scaled(30, 30),world,scene);
    birdstay[2] = new Bluebird(1.0f,9.0f,0.50f,&timer,QPixmap(":/Bird/BlueStay.png").scaled(30, 30),world,scene);
    birdstay[3] = new Bird(1.0f,10.0f,0.50f,&timer,QPixmap(":/Bird/RedStay.png").scaled(30, 30),world,scene);

    for(int i=0;i<4;i++)
    {
        birdstay[i]->set_type_of_body(true);
        itemList.push_back(birdstay[i]);
    }

    blockblock[0]= new Block(30.0f,7.5f,0.68f,4.0f,&timer,QPixmap(":/Block/WoodenBlock.png").scaled(21,120),world,scene);
    blockblock[1]= new Block(23.0f,7.5f,0.68f,4.0f,&timer,QPixmap(":/Block/WoodenBlock.png").scaled(21,120),world,scene);
    blockblock[2]= new Block(26.8f,10.0f,10.0f,0.8f,&timer,QPixmap(":/Block/WoodenBlockH.png").scaled(300,24),world,scene);
    blockblock[3]= new Block(24.0f,12.0f,0.8f,4.0f,&timer,QPixmap(":/Block/IronBlock.png").scaled(28,130),world,scene);
    blockblock[4]= new Block(28.0f,12.0f,0.8f,4.0f,&timer,QPixmap(":/Block/IronBlock.png").scaled(28,130),world,scene);
    blockblock[5]= new Block(26.8f,15.0f,10.0f,0.8f,&timer,QPixmap(":/Block/IronBlockH.png").scaled(300,24),world,scene);

    //0.5 x 30 = 15
    //2.0 x 30 = 60

    for(int i=0;i<6;i++)
    {
        itemList.push_back(blockblock[i]);
    }

    pigpig[0] = new Pig(26.8f,11.0f,1.0f,&timer,QPixmap(":/Pig/KingPig.png").scaled(80,80),world,scene);
    pigpig[1] = new Pig(26.8f,7.0f,1.7f,&timer,QPixmap(":/Pig/SmallPig.png").scaled(150,150),world,scene);

    for(int i=0;i<2;i++)
    {
        itemList.push_back(pigpig[i]);
    }

    Music=new QMediaPlayer();
    Music->setMedia(QUrl("qrc:/Sound/BGMusic.mp3"));
    Music->play();

    QiQi=new QSound(":/Sound/qiqi.wav");
    Mimi=new QSound(":/Sound/Mouseclick.wav");
    ZiZi=new QSound(":/Sound/ARH.wav");
    FiFi=new QSound(":/Sound/FLY.wav");

    Restart= new QPushButton;
    QPixmap button1(":/Button/restart.png");
    QIcon Button1(button1);
    Restart->setFixedSize(100,100);
    Restart->setGeometry(600,10,150,100);
    Restart->setIcon(Button1);
    Restart->setIconSize(button1.rect().size());
    connect(Restart,SIGNAL(clicked(bool)),this,SLOT(RestartGame()));

    Exit= new QPushButton;
    QPixmap button2(":/Button/exit.png");
    QIcon Button2(button2);
    Exit->setFixedSize(100,100);
    Exit->setGeometry(700,10,150,100);
    Exit->setIcon(Button2);
    Exit->setIconSize(button2.rect().size());
    connect(Exit,SIGNAL(clicked(bool)),this,SLOT(close()));

    scene->addWidget(Restart);
    scene->addWidget(Exit);

    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quit_game()),this,SLOT(QUITSLOT()));

    timer.start(100/6);
}

void MainWindow::RestartGame()
{
    Mimi->play();
    ShowingScore->clear();

   timer.stop();
   /*delete ShowingScore;
   delete ShowingLife;

   delete Main;
   delete end;
   delete slingsling;
   delete scene;
   delete world;
   delete Restart;
   delete Exit;

   for(int i=0;i<4;i++)
   {
       delete birdstay[i];
       //delete LifeRemainder[i];
   }

   if(whetherD1==false) delete pigpig[0];
   if(whetherD2==false)delete pigpig[1];

   for(int i=0;i<6;i++)
   delete blockblock[i]; 
*/
   disconnect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
   itemList.clear();

   SetUpVRB();
   SetUpOBJ();
}

void MainWindow::QUITSLOT()
{
    //send output signal
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    //exit-ing
    emit quit_game();
}

void MainWindow::SetUpVRB()
{
    score=0;
    no_deleted=0;
    count=0;
    click_ed=false;
    whetherD1=false;
    whetherD2=false;
    checkscore=false;
    fuck=0;
    suck=0;
    no_mouse_click=0;
}

