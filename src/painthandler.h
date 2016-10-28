#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QColor>
#include <QPixmap>
#include <QPointF>
#include <QPainter>
#include <memory>

struct PaintSettings {
    QColor color;

    static PaintSettings defaults();
};

class PaintHandler {
public:
    PaintSettings settings;
    
    PaintHandler();
    virtual ~PaintHandler();
    virtual void mousePressEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos);
    virtual void mouseMoveEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos);
    virtual void mouseReleaseEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos);
};

class PaintBrush: public PaintHandler {
 public:
    QPointF lastMousePoint;
    virtual ~PaintBrush();
    virtual void mousePressEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos);
    virtual void mouseMoveEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos);
    virtual void mouseReleaseEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos);
};

#endif
