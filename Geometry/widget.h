#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QCheckBox>
#include <QSpacerItem>
#include <QDial>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QPixmap>
#include <QColor>
#include <QStatusBar>

#include "imagemousewidget.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void openFile();
    void mirroredImage();
    void rotateImage();
    void saveImage();
    void zoomIn();
    void zoomOut();

private:
    void updateImageView();

    ImageMouseWidget *inWin;
    QImage originImg;
    QImage displayImg;
    double scaleFactor = 1.0;

    QGroupBox *mirrorGroup;
    QCheckBox *hCheckBox;
    QCheckBox *vCheckBox;
    QPushButton *mirrorButton;
    QDial *rotateDial;
    QPushButton *saveButton;
    QPushButton *openButton;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;

    QHBoxLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *groupLayout;

    QStatusBar *statusBar;
};

#endif // WIDGET_H
