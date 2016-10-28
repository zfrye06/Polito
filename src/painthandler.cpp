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
