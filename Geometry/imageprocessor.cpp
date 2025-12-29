#include "imageprocessor.h"

#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QPixmap>
#include <QColor>
#include <QtMath>

ImageProcessor::ImageProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("影像處理"));

    central = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(central);

    imgWin = new QLabel;
    QPixmap initPixmap(300, 200);
    initPixmap.fill(Qt::white);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(initPixmap);

    layout->addWidget(imgWin);
    setCentralWidget(central);

    createActions();
    createMenus();
    createToolBars();
}

ImageProcessor::~ImageProcessor() {}

void ImageProcessor::createActions()
{
    openFileAction = new QAction(tr("開啟檔案"), this);
    connect(openFileAction, &QAction::triggered, this, &ImageProcessor::showOpenFile);

    exitAction = new QAction(tr("結束"), this);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    zoomInAction = new QAction(tr("放大"), this);
    connect(zoomInAction, &QAction::triggered, this, &ImageProcessor::zoomIn);

    zoomOutAction = new QAction(tr("縮小"), this);
    connect(zoomOutAction, &QAction::triggered, this, &ImageProcessor::zoomOut);
}

void ImageProcessor::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("檔案"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(exitAction);

    QMenu *toolsMenu = menuBar()->addMenu(tr("工具"));
    toolsMenu->addAction(zoomInAction);
    toolsMenu->addAction(zoomOutAction);
}

void ImageProcessor::createToolBars()
{
    fileTool = addToolBar(tr("工具列"));
    fileTool->addAction(openFileAction);
    fileTool->addAction(zoomInAction);
    fileTool->addAction(zoomOutAction);
}

void ImageProcessor::showOpenFile()
{
    filename = QFileDialog::getOpenFileName(
        this, tr("開啟影像"), ".", "Images (*.bmp *.png *.jpg)"
        );

    if (!filename.isEmpty())
        loadFile(filename);
}

void ImageProcessor::loadFile(const QString &filename)
{
    originImg.load(filename);
    scaleFactor = 1.0;
    updateImageView();
}

void ImageProcessor::zoomIn()
{
    if (originImg.isNull()) return;
    scaleFactor = qMin(scaleFactor * 1.25, 5.0);
    updateImageView();
}

void ImageProcessor::zoomOut()
{
    if (originImg.isNull()) return;
    scaleFactor = qMax(scaleFactor / 1.25, 0.2);
    updateImageView();
}

void ImageProcessor::updateImageView()
{
    if (originImg.isNull()) return;

    QImage scaled = originImg.scaled(
        originImg.size() * scaleFactor,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        );
    imgWin->setPixmap(QPixmap::fromImage(scaled));
}
