#include "gameover.h"
#include"mypushbtn.h"
GameOver::GameOver(QWidget *parent) : QWidget(parent)
{
  this->restart=new MyPushBtn(":/r1/sorce/restart.png");
  this->quit=new MyPushBtn(":/r1/sorce/quit.png");
  this->sound=new QSound(":/r1/sorce/sound1.wav",this);
  restart->move(20,610);
  quit->move(460,610);
  restart->setParent(this);
  quit->setParent(this);
  this->setFixedSize(720,720);
}
void GameOver::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPixmap pix;
    pix.load(":/r1/sorce/overBack.jpg");
    p.drawPixmap(0,0,this->width(),this->height(),pix);
}
