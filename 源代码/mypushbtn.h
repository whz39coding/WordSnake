#ifndef MYPUSHBTN_H
#define MYPUSHBTN_H

#include <QWidget>
#include<QPushButton>
class MyPushBtn : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushBtn(QWidget *parent = nullptr);
   MyPushBtn(QString normalI,QString pressI="");
   QString nPath;
   QString pPath;
signals:

};

#endif // MYPUSHBTN_H
