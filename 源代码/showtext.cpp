#include "showtext.h"

ShowText::ShowText(QWidget *parent) : QWidget(parent)
{
    this->text=new QTextEdit(this);
    this->lay=new QVBoxLayout(this);
    lay->addWidget(text);
    this->setFixedSize(300,720);

}
