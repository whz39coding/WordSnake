#ifndef GAMEOVER_H
#define GAMEOVER_H
#include<QPainter>
#include<QPen>
#include<QPixmap>
#include <QWidget>
#include<mypushbtn.h>
#include<QSound>
class GameOver : public QWidget
{
    Q_OBJECT
public:
     GameOver(QWidget *parent = nullptr);
     MyPushBtn *restart=NULL;
     MyPushBtn *back=NULL;
     MyPushBtn *quit=NULL;
     void paintEvent(QPaintEvent *event);
     QSound *sound=NULL;
signals:

};

#endif // GAMEOVER_H
