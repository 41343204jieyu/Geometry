#ifndef IMAGEMOUSEWIDGET_H
#define IMAGEMOUSEWIDGET_H

#include <QLabel>
#include <QImage>
#include <QMouseEvent>

class ImageMouseWidget : public QLabel
{
    Q_OBJECT
public:
    explicit ImageMouseWidget(QWidget *parent = nullptr);

    void setImage(const QImage &img);
    void setScaleFactor(double factor);

signals:
    void mouseInfoChanged(const QString &info);   // 給狀態列用

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QImage img;
    double scaleFactor = 1.0;
};

#endif // IMAGEMOUSEWIDGET_H
