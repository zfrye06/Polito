#include <iostream>
#include <QStack>
#include "painthandler.h"

PaintSettings PaintSettings::defaults() {
    PaintSettings s;
    s.color = Qt::red;
    s.brushWidth = 5;
    return s;
}

PaintHandler::PaintHandler() : settings(PaintSettings::defaults()) {}

PaintHandler::~PaintHandler() {
}

void PaintBrush::mousePressEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) {
    lastMousePoint = pos;
}

void PaintBrush::mouseMoveEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) {
    QPainter painter(&image);
    painter.setPen(QPen(settings.color, settings.brushWidth, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
    painter.drawLine(lastMousePoint, pos);
    lastMousePoint = pos;
}

void PaintBrush::mouseReleaseEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) {
}

void Eraser::mousePressEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos ) {
    lastMousePoint = pos;
}

void Eraser::mouseMoveEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos ) {
    QPainter painter(&image);
    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    painter.setPen(QPen(Qt::transparent, settings.brushWidth, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
    painter.drawLine(lastMousePoint, pos);
    lastMousePoint = pos;
}

void Eraser::mouseReleaseEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos ) {
}

void PaintBucket::mousePressEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos ){
    QPainter painter(&image);
    QImage newImage = image.toImage();
    QPoint point = pos.toPoint();

    painter.setPen(QPen(settings.color));

    floodFill(newImage, painter, newImage.pixelColor(point.x(), point.y()), settings.color, point);
}

void PaintBucket::floodFill( QImage &image, QPainter &painter, QColor target, QColor replacement, QPoint position ){
    QStack<QPoint> unprocessedPixels;
    unprocessedPixels.push(position);
    while(unprocessedPixels.size() != 0){
        QPoint currentPoint = unprocessedPixels.pop();
        
        if (!image.valid(currentPoint)) {
            continue;
        }
            
        QColor currentColor = image.pixelColor(currentPoint.x(), currentPoint.y());

        if(currentColor != target || currentColor == replacement){
            continue;
        }

        painter.drawPoint(currentPoint);
        image.setPixelColor(currentPoint, replacement);

        QPoint north(currentPoint.x(), currentPoint.y() - 1);
        QPoint south(currentPoint.x(), currentPoint.y() + 1);
        QPoint east(currentPoint.x() + 1, currentPoint.y());
        QPoint west(currentPoint.x() - 1, currentPoint.y());

        unprocessedPixels.push(north);
        unprocessedPixels.push(south);
        unprocessedPixels.push(east);
        unprocessedPixels.push(west);
    }
}

void PaintBucket::mouseMoveEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos ){

}

void PaintBucket::mouseReleaseEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos ){

}
