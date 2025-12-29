#include "imagemousewidget.h"
#include <QColor>

ImageMouseWidget::ImageMouseWidget(QWidget *parent)
    : QLabel(parent)
{
    setMouseTracking(true);   // ⭐ 關鍵
}

void ImageMouseWidget::setImage(const QImage &image)
{
    img = image;
}

void ImageMouseWidget::setScaleFactor(double factor)
{
    scaleFactor = factor;
}

void ImageMouseWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (img.isNull()) return;

    int x = event->position().x() / scaleFactor;
    int y = event->position().y() / scaleFactor;

    QString text = QString("Move: (%1, %2)").arg(x).arg(y);

    if (x >= 0 && x < img.width() && y >= 0 && y < img.height()) {
        int gray = qGray(img.pixel(x, y));
        text += QString("  Gray=%1").arg(gray);
    }

    emit mouseInfoChanged(text);
}

void ImageMouseWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (img.isNull()) return;

    int x = event->position().x() / scaleFactor;
    int y = event->position().y() / scaleFactor;

    QString text = QString("Release: (%1, %2)").arg(x).arg(y);
    emit mouseInfoChanged(text);
}
