#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "animation.h"
#include "painthandler.h"

class DrawArea : public QGraphicsView {
    Q_OBJECT
 public:
    PaintHandler *currentPaintHandler;
    Frame *frame;
    DrawAction *currentAction;

 DrawArea(Frame *frame) :
    frame(frame), currentPaintHandler(new PaintBrush()) {}

    ~DrawArea();
    void setPaintHandler( PaintHandler* paintHandler );
    void setFrame(Frame *frame);
    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );

signals:
    void addAction( Action* action );
};

#endif
