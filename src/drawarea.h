#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "animation.h"
#include "painthandler.h"

class DrawArea : public QGraphicsView {
    Q_OBJECT
public:
    PaintHandler* currentPaintHandler;
    Animation* animation;
    DrawAction* currentAction;

    DrawArea(Animation* animation) : animation(animation){
        currentPaintHandler = new PaintBrush();
    }

    ~DrawArea();

    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );

public slots:
    void setPaintHandler( PaintHandler* paintHandler );

signals:
    void addAction( Action* action );
};

#endif
