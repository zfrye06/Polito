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
    Frame *frame;
    PaintHandler *currentPaintHandler;
    DrawAction *currentAction;

    DrawArea(Frame *frame);
    ~DrawArea();
    void setFrame(Frame *frame);
    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );

public slots:
    void setPaintHandler( PaintHandler* paintHandler );

signals:
=======
 signals:
>>>>>>> 3154578df3c63b59c5436ab7169fd2976118814f
    void addAction( Action* action );
};



#endif
