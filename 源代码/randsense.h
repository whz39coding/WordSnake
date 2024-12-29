#ifndef RANDSENSE_H
#define RANDSENSE_H

#include <QWidget>
#include <QMainWindow>
#include"gameover.h"
#include<QPainter>
#include<QPaintEvent>
#include<QWidget>
#include<QKeyEvent>
#include<QTimer>
#include<QList>
#include<QPixmap>
#include<QVector>
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
#include"mypushbtn.h"
#include<snackdif.h>
#include<QMap>
//这个结构体是给游戏过程中每一次在屏幕上打印字母所用的


class RandSense : public QWidget
{
    Q_OBJECT
public:
    explicit RandSense(QWidget *parent = nullptr);

public:
    int idx=0;//树的编号从1开始
    int tree[1001][30]={{0}};//用来建树;

    QMap<int,int>cun;
    QString eSTmp="";//这个是游戏过程中吃到的字母组成的单词,也就是find的参数

    int firstFlag=1;//这是是不是第一次吃对这个单词的标志,就是一血
    int constantFLag=1;//这个是连续的标志

    //这是设置音效的变量
    QSound *s32=NULL;//是连续出对两个的音效
    QSound *s33=NULL;//是连续吃对三个的音效
    QSound *s34=NULL;//这是连续吃对四个的王者音效
    QSound *s1=NULL;//第一个是吃到单词的音效
    QSound *s2=NULL;//这个是碰到墙的音效
    QSound *s3=NULL;//这个是吃对了的音效
    QSound *s4=NULL;//这个是吃错的音效

    QLabel* label33=NULL;//显示:当前的得分是:
    QLabel* label11=NULL;//显示要吃的英语
    QLabel* label22=NULL;//显示要吃的汉语
    QLabel* labelInt=NULL;//显示数字:getscore
    QLabel* label55=NULL;//显示:已经吃的字母是:
    QLabel* label66=NULL;//显示:时刻显示吃到的字母是什么
    int model;//给snackdif的参数,选择的第几个模式,1为困难模式,2为简单模式,!!!!!可以不要,改一下后面的
    int getScore=0;
    QString wordTmp="";//这是用66来显示的内容;就是她已经吃到的字母组成的序列
    void showWord();
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
    virtual void addWord();//添加新单词!!!!要重新写
    void judgeRight(QString );//判断是不是吃对了!!!这个也重新写
    void initWordSum();//用一个函数初始化所有的单词,我们自己给的!!!这个也重新写
    int wordHide();//吃到单词之后消失;!!!!!这个也是
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
    GameOver *gameover=NULL;
    void mclear();
    int mfind(QString word);
signals:

};

#endif // RANDSENSE_H
