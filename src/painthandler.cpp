#include "painthandler.h"

PaintHandler::~PaintHandler() {
}

void PaintHandler::mousePressEvent( std::shared_ptr<QPixmap> image,
                                    Qt::MouseButtons buttons, QPointF pos ) {
}

void PaintHandler::mouseMoveEvent( std::shared_ptr<QPixmap> image,
                                   Qt::MouseButtons buttons, QPointF pos ) {
}

void PaintHandler::mouseReleaseEvent( std::shared_ptr<QPixmap> image,
                                      Qt::MouseButtons buttons, QPointF pos ) {
}

PaintBrush::~PaintBrush() {
}

void PaintBrush::mousePressEvent( std::shared_ptr<QPixmap> image,
                                  Qt::MouseButtons buttons, QPointF pos ) {
    lastMousePoint = pos;
}

void PaintBrush::mouseMoveEvent( std::shared_ptr<QPixmap> image,
                                 Qt::MouseButtons buttons, QPointF pos ) {
    QPainter painter(image.get());
    painter.setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
    painter.drawLine(lastMousePoint, pos);
    lastMousePoint = pos;
}

void PaintBrush::mouseReleaseEvent( std::shared_ptr<QPixmap> image,
                                    Qt::MouseButtons buttons, QPointF pos ) {
}
