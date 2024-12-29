#include "mypushbtn.h"

//MyPushBtn::MyPushBtn(QWidget *parent) : QPushButton(parent)
//{

//}
MyPushBtn::MyPushBtn(QString normalI,QString pressI)
{
    this->nPath=normalI;
    this->pPath=pressI;
    QPixmap pix;
    pix.load(nPath);
    this->setFixedSize(200,75);
    this->setStyleSheet("QPushButton{border:opx}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}
