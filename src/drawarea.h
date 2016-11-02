#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QObject>
#include "action.h"
#include "animationwidgets.h"
#include "frame.h"
#include "layer.h"
#include "painthandler.h"

class DrawArea : public QGraphicsView, public UpdatableWidget {
    Q_OBJECT

 public:

    DrawArea(Frame *frame);
    ~DrawArea();
    PaintHandler &paintHandler();
    void setFrame(Frame *frame);
    void updateDisplay() override;
    virtual void mousePressEvent( QMouseEvent* event ) override;
    virtual void mouseMoveEvent( QMouseEvent* event ) override;
    virtual void mouseReleaseEvent( QMouseEvent* event ) override;

public slots:
    void setPaintHandler( PaintHandler* paintHandler );

signals:
    void updatePreview();
    void addAction( Action* action );

 private:

    Frame *frame; // does not own
    PaintHandler *currentPaintHandler; // owns
    DrawAction *currentAction; // owns
};



#endif
