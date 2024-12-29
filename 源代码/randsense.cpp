#include "randsense.h"

RandSense::RandSense(QWidget *parent) : QWidget(parent)
{

    this->s1=new QSound(":/r1/sorce/sound2.wav",this);
    this->s2=new QSound(":/r1/sorce/finish.wav",this);
    this->s32=new QSound(":/r1/sorce/beautiful.wav",this);
    this->s4=new QSound(":/r1/sorce/defeat.wav",this);
    this->s3=new QSound(":/r1/sorce/amazing.wav",this);
    this->s33=new QSound(":/r1/sorce/unbelieve.wav",this);
    this->s34=new QSound(":/r1/sorce/nicekilling.wav",this);

    //下面是初始化我们字体显示(得分,吃到的实时字母)
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(15);
    label11=new QLabel(this);
    label22=new QLabel(this);
    this->label33=new QLabel(this);
    label33->setFixedSize(200,100);
//    label33->setText(QString("当前的得分是: "+(QString)getScore));
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
    this->showFlag=false;
    connect(gameover->quit,&QPushButton::clicked,[=](){
        this->gameover->sound->play();
        exit(0);
    });

    //实现重新开始的代码
    connect(this->gameover->restart,&QPushButton::clicked,[=](){
        this->gameover->sound->play();
        this->snackBody.clear();
        for(int i=0;i<gameWordSum[appear-1].a.size();i++)
            gameWordSum[appear-1].fpoint[i]=true;
        QRectF rect(300,180,nodeW,nodeH);
        this->eSTmp="";
        mclear();

    //重新初始化我们的蛇的身体
        snackBody.append(rect);
        addTop();
        addTop();
        addWord();//在屏幕上打印出字母
        this->timer->start(100);
        this->gameStart=true;
        this->wordTmp="";
        this->gameover->close();
        update();
    });

    //初始化蛇的身体长度和初识位置
    QRectF rect(300,180,nodeW,nodeH);
    snackBody.append(rect);
    addTop();
    addTop();

    //构建我们的字典树
    initWordSum();

    //使用定时器
   timer=new QTimer(this);
   this->addWord();

   //链接,定时器发出超时信号,这个窗口进行绘图
   connect(timer,&QTimer::timeout,[=](){
       this->snackMove();
       int ret=mfind(eSTmp);
       //下面的代码应该要改一下,因为不在是以NUM为判断的标准
       //而是以find函数自己写,find吃错返回0,吃对返回1,没有吃到底返回-1;
       if(ret==0||ret==1)//this->eatNum==gameWordSum[appear-1].a.size()
       {
           QSound tmp(":/r1/sorce/first.wav",this);
           if(ret==1)
            {
               this->getScore+=1;
               if(firstFlag++==1)
                   tmp.play();
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
            }
             else
                  this->s4->play(),constantFLag=1;
           this->eSTmp="";
           mclear();//将其他剩余的字母的标志设为true;
           update();
           this->wordTmp="";
           this->addWord();
           this->eatNum=0;
       }
   });
}
//实现蛇的移动函数
void RandSense::snackMove()
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
void RandSense::paintEvent(QPaintEvent *)
{

    //画背景图
    QPainter p(this);
    QPixmap pix;if(this->redraw)
    {
     p.eraseRect(QRectF(0,0,this->width(),this->height()));
    }
    pix.load(":/r1/sorce/gameBack.png");
    p.drawPixmap(0,0,this->width(),this->height(),pix);
    QPen pen;
    QBrush brush;
    pen.setColor(Qt::black);
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);
    p.setPen(pen);
    p.setBrush(brush);

    //画蛇的身体
    for(int i=0;i<snackBody.length();i++)
    {
        p.drawRect(snackBody[i]);
    }

    //设置画笔的属性
    pen.setColor(Qt::red);
    p.setPen(pen);
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(15);
    p.setFont(font);

    //画英语字母
    int cnt=1,tmp;
    while(cnt++!=3)
    {
        tmp=appear-cnt;
        QString a=gameWordSum[tmp].a;
        for(int i=0;i<a.size();i++)
        {
            if(!gameWordSum[tmp].fpoint[i])//
              p.drawText(gameWordSum[tmp].point[i],QString(a[i]));
        }
    }

   //时刻显示吃到的字母
    this->label66->clear();
    this->label66->setText(wordTmp);

}
//获取按键控制方向或者是暂停
void RandSense::keyPressEvent(QKeyEvent* event)
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
    default:
        break;
    }
}
//以下是实现蛇的上下左右的移动
void RandSense::addTop()
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
            this->gameover->show();
            return ;
        }
    }
    snackBody.insert(0,QRectF(l,r));
}
void RandSense::addDown()
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
            this->gameover->show();
            return ;
        }
    }
    snackBody.insert(0,QRectF(l,r));
}
void RandSense::addLeft()
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
            this->gameover->show();
            return ;
        }
    }
    snackBody.insert(0,QRectF(l,r));
}
void RandSense::addRight()
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
            this->gameover->show();
            return ;
        }
    }
    snackBody.insert(0,QRectF(l,r));
}
//吃到指定的数目之后添加显示新的单词
void RandSense::addWord()
{
    //从总的数组中随机选出两个字母
    int cnt=0;
    int index;
    QString tmp;
    while(cnt++!=2)
    {
        index=gameWordSum[appear].wIndex=qrand()%100;
        tmp=gameWordSum[appear].a=wordSum[index].arr;
        gameWordSum[appear].b=wordSum[index].brr;
        for(int i=0;i<tmp.size();i++)
        {
            //随机生成字母的位置
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

            //把位置存进数组
            gameWordSum[appear].point[i]=rect;
            gameWordSum[appear].fpoint[i]=false;//一开始单词的标志变量都为0
        }
        qDebug()<<tmp<<' '<<gameWordSum[appear].b<<' '<<tmp.size();
        appear++;
    }

    //显示当前的得分和要吃的单词
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
    if(showFlag)//这个是实现显示要吃的单词的代码
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
void RandSense::judgeOver()
{

}
//判断是不是吃对了
void RandSense::judgeRight(QString a)
{
  if(gameWordSum[appear-1].eatStr==a)
  {
      this->getScore++;
      qDebug()<<"判断了   "<<getScore;
  }
  this->wordTmp="";
}
//吃到之后隐藏
int RandSense::wordHide()
{
   int cnt=1;
   int tmp;
   while(cnt++!=3)
   {
       tmp=appear-cnt;//appear为现在出现的单词的个数多一个
       int len=gameWordSum[tmp].a.size();
       for(int i=0;i<len;i++)
       {
           if(snackBody[0].intersects(gameWordSum[tmp].point[i]))
           {
               this->s1->play();
               eSTmp+=gameWordSum[tmp].a[i];
               eatNum+=1;
               qDebug()<<"eatNum "<<eatNum;
               this->wordTmp+=gameWordSum[tmp].a[i];
               gameWordSum[tmp].eatStr+=gameWordSum[tmp].a[i];
               gameWordSum[tmp].fpoint[i]=true;
               //吃完之后就让这个点的位置清0;
               gameWordSum[tmp].point[i].moveTo(-30,-30);
               gameWordSum[tmp].point[i].moveTo(-30,-30);
               return 1;
           }
       }
   }
   return 0;
}
//初始化我们的单词
void RandSense::initWordSum()
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
   int p;
   QString string="";
   while(!in.atEnd())
   {
       in>>ch;
       in>>ch;
       while(ch!=' ')
       {

           //模式四不允许出现大写字母因为在这里只有小写字母的一一映射
           if(ch>='A'&&ch<='Z')
               ch=ch.toLatin1()+32;
           wordSum[i].arr+=ch;
           string+=ch;
           in>>ch;
       }
       in>>ch;
       wordSum[i].brr=in.readLine();
       i++;
       p=0;
       //构建字典树
       for(int j=0;j<string.size();j++)
       {

           int k=string[j].toLatin1()-'a';
           if(tree[p][k]==0)
           {
               tree[p][k]=++idx;
                //这样操作就使得p又多了一个子节点编号为idx存放在cun[p]中
               cun[p]=1;
           }
           p=tree[p][k];
       }
       string="";
   }
   qDebug()<<"idx: "<<idx;
   file.close();
}
void RandSense::mclear()
{
    int cnt=1,tmp;
    while(cnt++!=3)
    {
        tmp=cnt-1;
        for(int i=0;i<gameWordSum[tmp].a.size();i++)
        {
            gameWordSum[tmp].fpoint[i]=true;
        }
    }
}
int RandSense::mfind(QString word)
{
   int p=0;
   for(int i=0;i<word.size();i++)
   {
       int j=word[i].toLatin1()-'a';
       if(tree[p][j]==0)
       {
           return 0;
       }
       p=tree[p][j];
   }
   //下面的代码是判断有没有吃到底
   if(cun[p]==1)//也就是说他没有字节点
       return -1;
   else
      return 1;//他还有字节点那么就是没有吃到底
}
