#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QColor>
#include <QPixmap>
#include <QPointF>
#include <QPainter>
#include <memory>

struct PaintSettings {
    QColor color;
    int brushWidth;

    static PaintSettings defaults();
};

class PaintHandler {
public:
    PaintSettings settings;
    
    PaintHandler();
    virtual ~PaintHandler();
    virtual void mousePressEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) = 0;
    virtual void mouseMoveEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) = 0;
    virtual void mouseReleaseEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) = 0;
};

class PaintBrush: public PaintHandler {
private:
    QPointF lastMousePoint;
public:
    virtual void mousePressEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos);
    virtual void mouseMoveEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos);
    virtual void mouseReleaseEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos);
};

class Eraser: public PaintHandler {
private:
    QPointF lastMousePoint;
public:
    virtual void mousePressEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos );
    virtual void mouseMoveEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos );
    virtual void mouseReleaseEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos );
};

class PaintBucket: public PaintHandler {
public:
    virtual void mousePressEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos );
    virtual void mouseMoveEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos );
    virtual void mouseReleaseEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos );

    void floodFill(QImage &image, QPainter &painter, QColor target, QColor replacement, QPoint position);
};

#endif
