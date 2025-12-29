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
    groupLayout = new QVBoxLayout(mirrorGroup);

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

    openButton = new QPushButton("開啟影像", this);
    zoomInButton = new QPushButton("放大", this);
    zoomOutButton = new QPushButton("縮小", this);
    saveButton = new QPushButton("儲存影像", this);

    leftLayout->addWidget(openButton);
    leftLayout->addWidget(zoomInButton);
    leftLayout->addWidget(zoomOutButton);
    leftLayout->addWidget(saveButton);
    leftLayout->addWidget(rotateDial);
    leftLayout->addStretch();

    mainLayout->addLayout(leftLayout);


    inWin = new ImageMouseWidget(this);
    inWin->setScaledContents(true);

    QPixmap initPixmap(400, 300);
    initPixmap.fill(Qt::white);

    QPainter painter(&initPixmap);
    painter.setPen(Qt::black);
    painter.drawRect(10, 10, 60, 40);
    painter.end();

    displayImg = initPixmap.toImage();
    originImg  = displayImg;

    inWin->setPixmap(initPixmap);
    inWin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->addWidget(inWin);


    statusBar = new QStatusBar(this);
    mainLayout->setMenuBar(statusBar);

    connect(inWin, &ImageMouseWidget::mouseInfoChanged,
            this, [=](const QString &text){
                statusBar->showMessage(text);
            });



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
    QString fileName = QFileDialog::getOpenFileName(
        this, "開啟影像", ".", "Images (*.bmp *.png *.jpg)"
        );
    if (fileName.isEmpty()) return;

    originImg.load(fileName);
    displayImg = originImg;
    scaleFactor = 1.0;
    updateImageView();
}

void Widget::mirroredImage()
{
    if (originImg.isNull()) return;

    displayImg = originImg.mirrored(
        hCheckBox->isChecked(),
        vCheckBox->isChecked()
        );

    originImg = displayImg;
    updateImageView();
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
    if (displayImg.isNull()) return;

    QString fileName = QFileDialog::getSaveFileName(
        this, "儲存影像", "", "PNG Image (*.png)"
        );
    if (fileName.isEmpty()) return;

    if (!fileName.endsWith(".png")) fileName += ".png";

    if (!displayImg.save(fileName, "PNG")) {
        QMessageBox::warning(this, "錯誤", "儲存失敗");
    }
}

void Widget::zoomIn()
{
    if (displayImg.isNull()) return;
    scaleFactor = qMin(scaleFactor * 1.25, 5.0);
    updateImageView();
}

void Widget::zoomOut()
{
    if (displayImg.isNull()) return;
    scaleFactor = qMax(scaleFactor / 1.25, 0.2);
    updateImageView();
}

void Widget::updateImageView()
{
    if (displayImg.isNull()) return;

    QImage scaled = displayImg.scaled(
        displayImg.size() * scaleFactor,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        );

    inWin->setPixmap(QPixmap::fromImage(scaled));
    inWin->setImage(displayImg);
    inWin->setScaleFactor(scaleFactor);
}
