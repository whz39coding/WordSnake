#include "snackdif.h"
#include"mainsense.h"

SnackDif::SnackDif(int model,QWidget *parent) : QWidget(parent)
{
    this->showtext=new ShowText;
    this->showtext->text->append("游戏中出现的单词:");
     this->showtext->move(-10,0);
    this->showtext->show();
    this->forBtn=new MyPushBtn(":/r1/sorce/forbtn.png");
    //全局的字体变量
   this->s31=new QSound(":/r1/sorce/first.wav",this);
    this->s1=new QSound(":/r1/sorce/sound2.wav",this);
    this->s2=new QSound(":/r1/sorce/finish.wav",this);
    this->s32=new QSound(":/r1/sorce/beautiful.wav",this);
    this->s4=new QSound(":/r1/sorce/defeat.wav",this);
    this->s3=new QSound(":/r1/sorce/amazing.wav",this);
    this->s33=new QSound(":/r1/sorce/unbelieve.wav",this);
    this->s34=new QSound(":/r1/sorce/nicekilling.wav",this);
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(15);
    label11=new QLabel(this);
    label22=new QLabel(this);
    this->label33=new QLabel(this);
    label33->setFixedSize(200,100);
    label33->setText(QString("当前的得分是: "+(QString)getScore));
    label33->show();
    labelInt=new QLabel(this);
    labelInt->move(label33->x()+10,label33->y());
    this->label55=new QLabel(this);
    this->label66=new QLabel(this);
    label55->setText("已经吃到的字母是:");
    font.setPointSize(10);
    label55->setFont(font);
    this->label66->setFont(font);
    label55->move(2,10);
    label66->move(153,-28);//这个是时刻显示出字母的位置
    label66->setFixedSize(100,100);
    this->gameover=new GameOver();
    this->gameover->setWindowTitle("结束界面");
    this->gameover->setWindowIcon(QIcon(":/r1/sorce/start.png"));
    connect(gameover->quit,&QPushButton::clicked,[=](){
        this->gameover->sound->play();
        exit(0);
    });
    connect(this->gameover->restart,&QPushButton::clicked,[=](){
        this->gameover->sound->play();
        this->snackBody.clear();
        this->eatNum=0;
        for(int i=0;i<gameWordSum[appear-1].a.size();i++)
            gameWordSum[appear-1].fpoint[i]=true;
        QRectF rect(300,180,nodeW,nodeH);
        snackBody.append(rect);
        addTop();
        addTop();
        addWord();
        this->timer->start(100);
        this->gameStart=true;
        this->wordTmp="";
        this->gameover->close();
        update();
    });
    this->model=model;
    if(model==1)
        this->showFlag=false;
    else
        this->showFlag=true;
    //初始化蛇的身体长度和初识位置
    QRectF rect(300,180,nodeW,nodeH);
    snackBody.append(rect);
    addTop();
    addTop();
    initWordSum();
    //使用定时器
   timer=new QTimer(this);
   this->addWord();
   reWidget=new QStackedWidget(this);
   //链接,定时器发出超时信号,这个窗口进行绘图
   connect(timer,&QTimer::timeout,[=](){
       this->snackMove();
       if(this->eatNum==gameWordSum[appear-1].a.size())
       {
            this->judgeRight(gameWordSum[appear-1].a);//吃到指定数目的单词之后
           //就开始调用新的添加单词
            this->showtext->text->append(gameWordSum[appear-1].a);
            addWord();
            this->eatNum=0;
       }
   });

}
//实现蛇的移动函数
void SnackDif::snackMove()
{
    int cnt=wordHide()+1;
    while(cnt--)
    {
        switch (moveFlag)
        {
           case Dir_UP:
              addTop();
              break;
          case Dir_Down:
              addDown();
              break;
          case Dir_Left:
              addLeft();
              break;
          case Dir_Right:
              addRight();
              break;
       }
    }
    this->snackBody.removeLast();
    update();//每一次处理好这个链表之后就要进行重新画蛇的身体
}
//负责渲染
void SnackDif::paintEvent(QPaintEvent *)
{


    QPainter p(this);
    QPixmap pix;if(this->redraw)
    {
     p.eraseRect(QRectF(0,0,this->width(),this->height()));
    }
    pix.load(":/r1/sorce/gameBack.png");
    p.drawPixmap(0,0,this->width(),this->height(),pix);
    if(model==3)
    {
        pix.load(":/r1/sorce/forbtn.png");
        forBtn->setFixedSize(75,75);
        forBtn->setStyleSheet("QPushButton{border:opx}");
        forBtn->setIcon(pix);
        forBtn->setIconSize(QSize(75,75));
        forBtn->move(1000,640);
    }
    QPen pen;
    QBrush brush;
    pen.setColor(Qt::black);
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);
    p.setPen(pen);
    p.setBrush(brush);
    for(int i=0;i<snackBody.length();i++)
    {
        p.drawRect(snackBody[i]);
    }
    pen.setColor(Qt::red);
    p.setPen(pen);
    int tmp=appear-1;
    QString a=gameWordSum[tmp].a;
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(15);
    p.setFont(font);
    for(int i=0;i<a.size();i++)
    {
        if(!gameWordSum[tmp].fpoint[i])
          p.drawText(gameWordSum[tmp].point[i],QString(a[i]));
    }
   //时刻显示吃到的字母
    this->label66->clear();
    this->label66->setText(wordTmp);

}
//获取按键控制方向或者是暂停
void SnackDif::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        if(moveFlag!=Dir_Down)
           moveFlag=Dir_UP;

        break;
    case Qt::Key_Down:
         if(moveFlag!=Dir_UP)
            moveFlag=Dir_Down;
        break;
    case Qt::Key_Left:
         if(moveFlag!=Dir_Right)
           moveFlag=Dir_Left;
        break;
    case Qt::Key_Right:
         if(moveFlag!=Dir_Left)
           moveFlag=Dir_Right;
        break;
    case Qt::Key_Space:
        if(gameStart==false)
        {
            gameStart=true;
            //游戏开始之后定时器启动
            timer->start(100);//每一百毫秒就发出超时信号;
        }
        else
        {
            gameStart=false;
            timer->stop();
        }
        break;
    case Qt::Key_P:
        if(model==3)
        {
            gameStart=false;
            this->timer->stop();
            this->s2->play();
            QTimer::singleShot(3000,this,[=](){
               this->gameover->show();
            });
        }
        break;
    default:
        break;
    }
}
//以下是实现蛇的上下左右的移动
void SnackDif::addTop()
{
    QPointF l(snackBody[0].x(),snackBody[0].y()-nodeH);
    QPointF r(snackBody[0].topRight());
    if(l.y()<=-15)
    {
        if(this->model==3)
        {
            QPointF l1(l.x(),this->height()-nodeH);
            QPointF r2(r.x(),this->height());
            l=l1;
            r=r2;
        }
        else
        {
            gameStart=false;
            this->timer->stop();
            this->s2->play();
            QTimer::singleShot(3000,this,[=](){
               this->gameover->show();
            });
            return ;
        }
    }
    snackBody.insert(0,QRectF(l,r));
}
void SnackDif::addDown()
{
    QPointF l(snackBody[0].bottomLeft());
    QPointF r(snackBody[0].bottomRight().x(),snackBody[0].bottomRight().y()+nodeH);
    if(r.y()>=this->height()+15)
    {
        if(this->model==3)
        {
            QPointF l1(l.x(),0);
            QPointF r2(r.x(),nodeH);
            l=l1;
            r=r2;
        }
        else
        {
            gameStart=false;
            this->s2->play();
            this->timer->stop();
            QTimer::singleShot(3000,this,[=](){
               this->gameover->show();
            });
            return ;
        }
    }
    snackBody.insert(0,QRectF(l,r));
}
void SnackDif::addLeft()
{
    QPointF l(snackBody[0].x()-nodeW,snackBody[0].y());
    QPointF r(snackBody[0].bottomLeft());
    if(l.x()<=-15)
    {
        if(this->model==3)
        {
            QPointF l1(this->width()-nodeW,l.y());
            QPointF r2(this->width(),r.y());
            l=l1;
            r=r2;
        }
        else
        {
            gameStart=false;
            this->s2->play();
            this->timer->stop();
            QTimer::singleShot(3000,this,[=](){
               this->gameover->show();
            });
            return ;
        }
    }
    snackBody.insert(0,QRectF(l,r));
}
void SnackDif::addRight()
{
    QPointF l(snackBody[0].topRight());
    QPointF r(snackBody[0].bottomRight().x()+nodeW,snackBody[0].bottomRight().y());
    if(r.x()>=this->width()+15)
    {
        if(this->model==3)
        {
            QPointF l1(0,l.y());
            QPointF r2(nodeH,r.y());
            l=l1;
            r=r2;
        }
        else
        {
            gameStart=false;
            this->s2->play();
            this->timer->stop();
            QTimer::singleShot(3000,this,[=](){
               this->gameover->show();
            });
            return ;
        }
    }
    snackBody.insert(0,QRectF(l,r));
}
//吃到指定的数目之后添加显示新的单词
void SnackDif::addWord()
{
    int index=gameWordSum[appear].wIndex=qrand()%100;
    QString tmp=gameWordSum[appear].a=wordSum[index].arr;
    gameWordSum[appear].b=wordSum[index].brr;
    for(int i=0;i<tmp.size();i++)
    {
        int x=qrand()%(this->width()/20)*20+10;
        while(x<=10||this->width()-x<=25)
            x=qrand()%(this->width()/20)*20+10;
        int y=qrand()%(this->width()/20)*20+10;
        while(y<=10||this->height()-y<=25)
            y=qrand()%(this->width()/20)*20+10;
        QRectF rect(x,
                    y,
                    35,
                    35);
        gameWordSum[appear].point[i]=rect;
        gameWordSum[appear].fpoint[i]=false;//一开始单词的标志变量都为0
    }
    qDebug()<<tmp<<' '<<gameWordSum[appear].b<<' '<<tmp.size();
    QFont labelFont("Arial", 16);
    QFont labelFont2("Arial", 10);
    this->label33->setFont(labelFont2);
    this->label33->setText("");
    this->label33->setFont(labelFont2);
    this->label33->setText("当前的得分是:");
    this->labelInt->clear();
    this->labelInt->setFont(labelFont2);
    this->labelInt->setNum(getScore);
    this->labelInt->move(108,42);
    this->label33->show();
    qDebug()<<getScore;
    appear++;//可以在appear这里重新写
    if(showFlag)
    {
        QString word=gameWordSum[appear-1].a;
        QString mean=gameWordSum[appear-1].b;
        qDebug()<<mean<<' '<<word<<"0000"<<gameWordSum[appear-1].a.size()<<eatNum;
        this->label11->setText("");
        this->label11->setText(word);
        this->label11->setFixedSize(170,65);
        this->label11->move(940,70);
        this->label11->setFont(labelFont);
        this->label22->setFixedSize(170,65);
        this->label22->setText("");
        this->label22->setText(mean);
        this->label22->move(940,100);
        this->label22->setFont(labelFont);
        this->label11->setAlignment(Qt::AlignHCenter);//居中显示
        this->label22->setAlignment(Qt::AlignHCenter);
    }
}
//判断是不是蛇头碰到蛇身结束,有时间写一下蛇头和蛇身的重合
void SnackDif::judgeOver()
{

}
//判断是不是吃对了
void SnackDif::judgeRight(QString a)
{


  if(gameWordSum[appear-1].eatStr==a)
  {
      if(firstFlag==1)
          this->s31->play(),firstFlag++;
      else
      {
          if(constantFLag++==1)
              this->s3->play();
          else if(constantFLag++==2)
              this->s32->play();
          else if(constantFLag++==3)
              this->s33->play();
          else
              this->s34->play();

      }
      this->getScore++;
      qDebug()<<"判断了   "<<getScore;
  }
  else
      this->s4->play(),constantFLag=1;
  this->wordTmp="";
}
//吃到之后隐藏
int SnackDif::wordHide()
{
   int tmp=appear-1;//appear为现在出现的单词的个数多一个
   int len=gameWordSum[tmp].a.size();
   for(int i=0;i<len;i++)
   {
       if(snackBody[0].intersects(gameWordSum[tmp].point[i]))
       {
           this->s1->play();
           eatNum+=1;
           qDebug()<<"eatNum "<<eatNum;
           this->wordTmp+=gameWordSum[tmp].a[i];
           qDebug()<<eatNum<<"    0"<<gameWordSum[tmp].a[i];
           gameWordSum[tmp].eatStr+=gameWordSum[tmp].a[i];
           gameWordSum[tmp].fpoint[i]=true;
           //吃完之后就让这个点的位置清0;
           gameWordSum[tmp].point[i].moveTo(-10,-10);
           gameWordSum[tmp].point[i].moveTo(-10,-10);
           return 1;
       }
   }
   return 0;
}
//初始化我们的单词
void SnackDif::initWordSum()
{
   QFile file(":/r1/sorce/word.txt");
   if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
   {
       qDebug()<<"dakaishibai";
   }
   QTextStream in(&file);
   in.setCodec("UTF-8");
   QChar ch;
   int i=0;
   while(!in.atEnd())
   {
       in>>ch;
       in>>ch;
       while(ch!=' ')
       {
           wordSum[i].arr+=ch;
           in>>ch;
       }
       in>>ch;
       wordSum[i].brr=in.readLine();
       i++;
   }
   file.close();
}
