#ifndef MAINSENSE_H
#define MAINSENSE_H
#include <QMainWindow>
#include<QIcon>
#include<QPushButton>
#include<QPainter>
#include"snackdif.h"
#include"mypushbtn.h"
#include<QSound>
#include"randsense.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Mainsense; }
QT_END_NAMESPACE

class Mainsense : public QMainWindow
{
    Q_OBJECT

public:
    QSound *sound=NULL;
    Mainsense(QWidget *parent = nullptr);
    ~Mainsense();
    void paintEvent(QPaintEvent*);
   SnackDif* dif=NULL;//这是主窗口的困难模式的变量,是一个窗口的变量
   RandSense *randsense=NULL;
   MyPushBtn *btn,*btn2,*btn3,*btn4;
private:
    Ui::Mainsense *ui;
};
#endif // MAINSENSE_H
