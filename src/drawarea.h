#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QObject>
#include "action.h"
#include "frame.h"
#include "layer.h"
#include "painthandler.h"

class DrawArea : public QGraphicsView {
    Q_OBJECT

 public:

    DrawArea(Frame *frame);
    ~DrawArea();
    PaintHandler &paintHandler();
    void setFrame(Frame *frame);
    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );

public slots:
    void setPaintHandler( PaintHandler* paintHandler );

signals:
    void addAction( Action* action );

 private:

    Frame *frame; // does not own
    PaintHandler *currentPaintHandler; // owns
    DrawAction *currentAction; // owns
};



#endif
