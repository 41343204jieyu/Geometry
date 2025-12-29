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

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void openFile();          // 開啟影像
    void mirroredImage();     // 鏡射
    void rotateImage();       // 旋轉
    void saveImage();         // 儲存
    void zoomIn();            // 放大
    void zoomOut();           // 縮小

private:
    void updateImageView();   // 更新 QLabel 顯示
    void createActions();     // 建立功能 action
    void createMenus();       // 建立選單
    void createToolBars();    // 建立工具列

    QLabel *inWin;
    QImage originImg;
    QImage displayImg;
    double scaleFactor = 1.0;

    // 左側功能區
    QGroupBox *mirrorGroup;
    QCheckBox *hCheckBox;
    QCheckBox *vCheckBox;
    QPushButton *mirrorButton;
    QDial *rotateDial;
    QPushButton *saveButton;
    QPushButton *openButton;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;

    // Layout
    QHBoxLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *groupLayout;

    // menu & toolbar
    QMenuBar *menuBarPtr;
    QMenu *fileMenu;
    QToolBar *fileTool;

    QAction *openFileAction;
    QAction *exitAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
};

#endif // WIDGET_H
