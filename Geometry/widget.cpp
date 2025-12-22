#include "widget.h"
#include<QPixmap>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    mainLayout=new QHBoxLayout(this);
    leftLayout = new QVBoxLayout(this);
    mirrorGroup = new QGroupBox(QStringLiteral("鏡射"),this);
    groupLayout  = new QVBoxLayout(mirrorGroup);

    hCheckBox = new QCheckBox(QStringLiteral("水平"),mirrorGroup);
    vCheckBox = new QCheckBox(QStringLiteral("垂直"),mirrorGroup);
    mirrorButton = new QPushButton(QStringLiteral("執行"),mirrorGroup);

    hCheckBox ->setGeometry(QRect(13,28,87,19));
    vCheckBox ->setGeometry(QRect(13,54,87,19));
    mirrorButton->setGeometry(QRect(13,80,93,28));
    groupLayout->addWidget(hCheckBox);
    groupLayout->addWidget(vCheckBox);


}


Widget::~Widget() {}
void Widget::mirroredImage(){

}
void Widget::rotateImage(){

}
