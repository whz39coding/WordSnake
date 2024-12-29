#include "mainsense.h"
#include "ui_mainsense.h"
#include<QObject>
#include<QDialog>
#include<QDebug>
#include<QMenuBar>
#include<QUrl>
#include<QSound>
#include"snackdif.h"

//这是主页面
Mainsense::Mainsense(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Mainsense)
{

    this->sound=new QSound(":/r1/sorce/sound1.wav",this);
    sound->setParent(this);
    setFixedSize(1080,720);
    setWindowTitle("单词贪吃蛇");//设置主页面的标题
    setWindowIcon(QIcon(":/r1/sorce/start.png"));//设置游戏的图标
    btn=new MyPushBtn(":/r1/sorce/dif.png");
    btn->move(80,590);//这是较难模式的开始按钮
    btn2=new MyPushBtn(":/r1/sorce/easy.png");
    btn3 =new MyPushBtn(":/r1/sorce/forever.png");
    btn4=new MyPushBtn(":/r1/sorce/AI.png");
    btn->setParent(this);
    btn2->setParent(this);
    btn3->setParent(this);
    btn4->setParent(this);
    btn2->move(320,590);
    btn3->move(570,590);
    btn4->move(830,590);
   //这是点击规则说明的连接
    auto bar=new QMenuBar(this);
    QMenu *Menurul=new QMenu(this);
    bar->addMenu(Menurul);
    Menurul->setTitle("规则说明");
   connect(Menurul,&QMenu::aboutToShow,[=](){
       QDialog* dlg=new QDialog(this);
       dlg->setFixedSize(405,870);
       dlg->setWindowTitle("规则说明");
       dlg->setStyleSheet("QDialog { background-image:url(:/r1/sorce/Rule.png); }");
       dlg->show();
   });
   //这是较难模式的开始按钮,进入较难模式的界面
   connect (btn,&QPushButton::clicked,[=](){
       this->sound->play();
       this->hide();
       dif=new SnackDif(1);
       dif->setWindowIcon(QIcon(":/r1/sorce/start.png"));//设置游戏的图标
       dif->show();
       dif->setFixedSize(1080,720);
       dif->setWindowTitle("困难模式");
   });
   connect(btn2,&QPushButton::clicked,[=](){
       sound->play();
       this->hide();
       dif=new SnackDif(2);
       dif->setWindowIcon(QIcon(":/r1/sorce/start.png"));//设置游戏的图标
       dif->setFixedSize(1080,720);
       dif->show();
        dif->setWindowTitle("简单模式");
   });

   connect(btn3,&QPushButton::clicked,[=](){
       sound->play();
       qDebug()<<"wujin";
       dif=new SnackDif(3);
       this->hide();
       dif->setWindowIcon(QIcon(":/r1/sorce/start.png"));//设置游戏的图标
       dif->setFixedSize(1080,720);
        dif->setWindowTitle("无尽模式");
       dif->show();
   });
   connect(btn4,&QPushButton::clicked,[=](){
       this->hide();
       this->randsense=new RandSense;
       randsense->setWindowIcon(QIcon(":/r1/sorce/start.png"));
       randsense->setWindowTitle("单词随心吃");
       randsense->setFixedSize(1080,720);
       randsense->show();
   });
}
//对主页面进行渲染
void Mainsense::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/r1/sorce/Snack_back.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
Mainsense::~Mainsense()
{
    delete ui;
}
