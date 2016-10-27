#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QColor>
#include <QPixmap>
#include <QPointF>
#include <QPainter>
#include <memory>

class PaintHandler {
public:
    int brushWidth;
    QColor foregroundColor;
    QColor backgroundColor;
    virtual ~PaintHandler();

    virtual void mousePressEvent( std::shared_ptr<QPixmap> image, Qt::MouseButtons buttons, QPointF pos );
    virtual void mouseMoveEvent( std::shared_ptr<QPixmap> image, Qt::MouseButtons buttons, QPointF pos );
    virtual void mouseReleaseEvent( std::shared_ptr<QPixmap> image, Qt::MouseButtons buttons, QPointF pos );
};

class PaintBrush: public PaintHandler {
    QPointF lastMousePoint;
    virtual ~PaintBrush();
    virtual void mousePressEvent( std::shared_ptr<QPixmap> image, Qt::MouseButtons buttons, QPointF pos );
    virtual void mouseMoveEvent( std::shared_ptr<QPixmap> image, Qt::MouseButtons buttons, QPointF pos );
    virtual void mouseReleaseEvent( std::shared_ptr<QPixmap> image, Qt::MouseButtons buttons, QPointF pos );
};

#endif
