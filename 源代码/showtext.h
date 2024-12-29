#ifndef SHOWTEXT_H
#define SHOWTEXT_H

#include <QWidget>
#include<QTextEdit>
#include<QVBoxLayout>
class ShowText : public QWidget
{
    Q_OBJECT
public:
    explicit ShowText(QWidget *parent = nullptr);
    QTextEdit *text=NULL;
    QVBoxLayout *lay=NULL;
signals:

};

#endif // SHOWTEXT_H
