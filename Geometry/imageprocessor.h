#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QMainWindow>
#include <QWidget>
#include <QMenu>
#include <QToolBar>
#include <QAction>
#include <QImage>
#include <QLabel>
#include <QString>

class ImageProcessor : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageProcessor(QWidget *parent = nullptr);
    ~ImageProcessor();

private slots:
    void showOpenFile();
    void zoomIn();
    void zoomOut();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void loadFile(const QString &filename);
    void updateImageView();

    QWidget  *central = nullptr;
    QLabel   *imgWin  = nullptr;

    QMenu    *fileMenu = nullptr;
    QToolBar *fileTool = nullptr;

    QAction  *openFileAction = nullptr;
    QAction  *exitAction     = nullptr;
    QAction  *zoomInAction   = nullptr;
    QAction  *zoomOutAction  = nullptr;

    QImage  originImg;
    QString filename;
    double  scaleFactor = 1.0;
};

#endif // IMAGEPROCESSOR_H
