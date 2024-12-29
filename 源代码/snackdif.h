#ifndef SNACKDIF_H
#define SNACKDIF_H
//#include"mypushbtn.h"
#include"showtext.h"
#include <QMainWindow>
#include<QPainter>
#include<QPaintEvent>
#include<QWidget>
#include<QKeyEvent>
#include<QTimer>
#include<QSound>
#include<QList>
#include<QPixmap>
#include<QRectF>
#include<QPointF>
#include<QPen>
#include<QBrush>
#include<QLabel>
#include<qrandom.h>
#include<QString>
#include<QFile>
#include<QDebug>
#include<QChar>
#include<qrandom.h>
#include<QStackedWidget>
#include<gameover.h>
//model 是一你们就是困难模式,是二就是简单模式
enum Direct
{
  Dir_UP,
  Dir_Down,
  Dir_Left,
  Dir_Right,
};
struct wordType
{
    QString arr,brr;
};
struct gameWordType//这个是存储游戏中出现的单词的数组
{
    int wSize;//word的大小
    QString a,b;//a为英文字母,b为中文
    int wIndex;//wordSUm数组中第几个
    QRectF point[20];//按照字母的顺序存储位置
    bool fpoint[20]={0};
    QString eatStr="";
    int psize=0;
};

class SnackDif : public QWidget
{

Q_SIGNALS:

public:

    int firstFlag=1;//这是是不是第一次吃对这个单词的标志,就是一血
    int constantFLag=1;//这个是连续的标志

    //这是设置音效的变量
    QSound *s31=NULL;
    QSound *s32=NULL;//是连续出对两个的音效
    QSound *s33=NULL;//是连续吃对三个的音效
    QSound *s34=NULL;//这是连续吃对四个的王者音效
    QSound *s1=NULL;//第一个是吃到单词的音效
    QSound *s2=NULL;//这个是碰到墙的音效
    QSound *s3=NULL;//这个是吃对了的音效
    QSound *s4=NULL;//这个是吃错的音效

    //用QLAbel显示文字
    QLabel* label33=NULL;//显示:当前的得分是:
    QLabel* label11=NULL;//显示要吃的英语
    QLabel* label22=NULL;//显示要吃的汉语
    QLabel* labelInt=NULL;//显示数字:getscore
    QLabel* label55=NULL;//显示:已经吃的字母是:
    QLabel* label66=NULL;//显示:时刻显示吃到的字母是什么

    int model;//给snackdif的参数,选择的第几个模式,1为困难模式,2为简单模式
    //3为无尽模式
    int getScore=0;//得分的变量
    ShowText *showtext=NULL;

    QString wordTmp="";//这是用66来显示的内容;
    QPushButton *forBtn=NULL;
    void showWord();
    explicit SnackDif(int mod,QWidget *parent = nullptr );
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent*);
    bool showFlag=true;
public:
    void initBody();
    void addTop();
    void addDown();
    void addLeft();
    void addRight();
    QLabel *l1,*l2;
    //游戏过程中的函数
    void judgeOver();//判断蛇头和身体是否重合
    virtual void addWord();//添加新单词
    void judgeRight(QString );//判断是不是吃对了
    void initWordSum();//用一个函数初始化所有的单词,我们自己给的
    int wordHide();//吃到单词之后消失;
    //上面的函数是自己写
    int moveFlag=Dir_Down;
    bool  gameStart=false;
    QTimer *timer=NULL;
    QList<QRectF> snackBody;
    int nodeW=20;
    int nodeH=20;
    int eatNum=0;//吃到字母的个数
    int wordNum;
    bool redraw=false;
    void snackMove();
    void snackMove(int);
   wordType  wordSum[1000];//这个是从文本文件中读取的
   wordType  eatWordSum[1000];//这个是游戏过程中吃对的
   gameWordType  gameWordSum[1000];//这个是游戏过程中总的出现的
    int appear=0;//已经出现的英文单词个数
    QStackedWidget *reWidget=NULL;
    GameOver *gameover=NULL;
signals:

};

#endif // SNACKDIF_H
