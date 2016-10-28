#include "drawarea.h"

DrawArea::DrawArea(Frame *frame):
    frame(frame), currentPaintHandler(new PaintBrush()) {}

DrawArea::~DrawArea() {
    delete currentPaintHandler;
}

void DrawArea::setPaintHandler(PaintHandler *handler) {
    handler->settings = currentPaintHandler->settings;
    delete currentPaintHandler;
    this->currentPaintHandler = currentPaintHandler;
}

PaintHandler &DrawArea::paintHandler() {
    return *currentPaintHandler;
}

void DrawArea::setFrame(Frame *frame) {
    this->frame = frame;
}

void DrawArea::mousePressEvent(QMouseEvent *event) {
    if (!currentPaintHandler) {
        return;
    }
    
    auto imgCpy = std::shared_ptr<QPixmap>(new QPixmap(frame->activeLayer()->pixmap()));
    currentAction = new DrawAction(frame->activeLayer(), imgCpy);
    
    QPointF pos = mapToScene(event->pos());
    currentPaintHandler->mousePressEvent(frame->activeLayer()->pixmap(), event->buttons(), pos );
    
    this->viewport()->update();
}

void DrawArea::mouseMoveEvent(QMouseEvent *event) {
    if (!currentPaintHandler) {
        return;
    }
    
    QPointF pos = mapToScene(event->pos());
    currentPaintHandler->mouseMoveEvent(frame->activeLayer()->pixmap(), event->buttons(), pos );
    
    this->viewport()->update();
}

void DrawArea::mouseReleaseEvent(QMouseEvent *event) {
    if (!currentPaintHandler) {
        return;
    }
    
    QPointF pos = mapToScene(event->pos());
    currentPaintHandler->mouseReleaseEvent(frame->activeLayer()->pixmap(), event->buttons(), pos );

    auto imgCpy = std::shared_ptr<QPixmap>(new QPixmap(frame->activeLayer()->pixmap()));
    currentAction->finish(imgCpy);
    emit addAction(currentAction);
    
    this->viewport()->update();
}
