#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QLabel>
#include<QGroupBox>
#include<QPushButton>
#include<QCheckBox>
#include<QSpacerItem>
#include<QDial>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QImage>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QLabel *inWin;
    QGroupBox *mirrorGroup;
    QCheckBox *hCheckBox;
    QCheckBox *vCheckBox;
    QPushButton *mirrorButton;
    QDial *rotateDial;
    QSpacerItem *vSpacer;
    QHBoxLayout *mainLayout;
    QVBoxLayout *groupLayout;
    QVBoxLayout *leftLayout;
    QImage srcImg;
    QImage dstImg;

private slots:
    void mirroredImage();
    void rotateImage();

};
#endif // WIDGET_H
