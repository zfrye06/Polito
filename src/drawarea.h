#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QObject>
#include <QColor>
#include <typeinfo>
#include "action.h"
#include "animationwidgets.h"
#include "frame.h"
#include "layer.h"
#include "painthandler.h"

class DrawArea : public QGraphicsView, public UpdateableWidget {
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
    virtual void drawForeground( QPainter* painter, const QRectF& rect ) override;

public slots:
    void setPaintHandler( PaintHandler* paintHandler );
    void setBrushWidth(int width);

signals:
    void updateView();
    void drawEvent( DrawAction* action );

 private:

    QImage *checkerboard;
    Frame *frame; // does not own
    PaintHandler *currentPaintHandler; // owns
    DrawAction *currentAction; // owns
};



#endif
