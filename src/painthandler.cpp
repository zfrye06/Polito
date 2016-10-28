#include "painthandler.h"

PaintHandler::~PaintHandler() {
}

void PaintHandler::mousePressEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) {
}

void PaintHandler::mouseMoveEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) {
}

void PaintHandler::mouseReleaseEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) {
}

PaintBrush::~PaintBrush() {
}

void PaintBrush::mousePressEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) {
    lastMousePoint = pos;
}

void PaintBrush::mouseMoveEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) {
    QPainter painter(&image);
    painter.setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
    painter.drawLine(lastMousePoint, pos);
    lastMousePoint = pos;
}

void PaintBrush::mouseReleaseEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) {
}
