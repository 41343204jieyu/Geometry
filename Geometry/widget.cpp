#include "widget.h"
#include <QTransform>
#include <QPainter>
#include <QtMath>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("影像處理整合版");

    mainLayout = new QHBoxLayout(this);
    leftLayout = new QVBoxLayout();
    mirrorGroup = new QGroupBox("鏡射", this);
    groupLayout  = new QVBoxLayout(mirrorGroup);

    hCheckBox = new QCheckBox("水平", mirrorGroup);
    vCheckBox = new QCheckBox("垂直", mirrorGroup);
    mirrorButton = new QPushButton("執行", mirrorGroup);

    groupLayout->addWidget(hCheckBox);
    groupLayout->addWidget(vCheckBox);
    groupLayout->addWidget(mirrorButton);
    mirrorGroup->setLayout(groupLayout);
    leftLayout->addWidget(mirrorGroup);

    rotateDial = new QDial(this);
    rotateDial->setNotchesVisible(true);
    saveButton = new QPushButton("儲存影像", this);
    openButton = new QPushButton("開啟影像", this);
    zoomInButton = new QPushButton("放大", this);
    zoomOutButton = new QPushButton("縮小", this);

    leftLayout->addWidget(openButton);
    leftLayout->addWidget(zoomInButton);
    leftLayout->addWidget(zoomOutButton);
    leftLayout->addWidget(saveButton);
    leftLayout->addWidget(rotateDial);
    leftLayout->addStretch(); // 下方填滿空間

    mainLayout->addLayout(leftLayout);

    // 右側 QLabel
    inWin = new QLabel(this);
    inWin->setScaledContents(true);
    QPixmap initPixmap(400, 300);
    initPixmap.fill(Qt::white);

    QPainter paint(&initPixmap);
    paint.setPen(QColor(0, 0, 0));
    paint.drawRect(10, 10, 60, 40);
    paint.end();

    displayImg = initPixmap.toImage();
    originImg = displayImg;
    inWin->setPixmap(initPixmap);
    inWin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->addWidget(inWin);

    // 連接槽
    connect(mirrorButton, &QPushButton::clicked, this, &Widget::mirroredImage);
    connect(rotateDial, &QDial::valueChanged, this, &Widget::rotateImage);
    connect(saveButton, &QPushButton::clicked, this, &Widget::saveImage);
    connect(openButton, &QPushButton::clicked, this, &Widget::openFile);
    connect(zoomInButton, &QPushButton::clicked, this, &Widget::zoomIn);
    connect(zoomOutButton, &QPushButton::clicked, this, &Widget::zoomOut);
}

Widget::~Widget() {}

void Widget::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "開啟影像", ".", "Images (*.bmp *.png *.jpg)");
    if (fileName.isEmpty()) return;

    originImg.load(fileName);
    displayImg = originImg;
    scaleFactor = 1.0;
    updateImageView();
}

void Widget::mirroredImage()
{
    if (originImg.isNull()) return;
    displayImg = originImg.mirrored(hCheckBox->isChecked(), vCheckBox->isChecked());
    updateImageView();
    originImg = displayImg;
}

void Widget::rotateImage()
{
    if (originImg.isNull()) return;
    QTransform tran;
    tran.rotate(rotateDial->value());
    displayImg = originImg.transformed(tran);
    updateImageView();
}

void Widget::saveImage()
{
    if (originImg.isNull()) return;

    QString fileName = QFileDialog::getSaveFileName(this, "儲存影像", "", "PNG Image (*.png)");
    if (fileName.isEmpty()) return;
    if (!fileName.endsWith(".png")) fileName += ".png";

    if (!displayImg.save(fileName, "PNG")) {
        QMessageBox::warning(this, "錯誤", "儲存失敗");
    }
}

void Widget::zoomIn()
{
    if (originImg.isNull()) return;
    scaleFactor = qMin(scaleFactor * 1.25, 5.0);
    updateImageView();
}

void Widget::zoomOut()
{
    if (originImg.isNull()) return;
    scaleFactor = qMax(scaleFactor / 1.25, 0.2);
    updateImageView();
}

void Widget::updateImageView()
{
    if (originImg.isNull()) return;

    QImage scaled = displayImg.scaled(displayImg.size() * scaleFactor, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    inWin->setPixmap(QPixmap::fromImage(scaled));
}
