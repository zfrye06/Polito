#include "drawarea.h"

DrawArea::DrawArea(Frame *frame):
    frame(frame), currentPaintHandler(new PaintBrush()) {}

DrawArea::~DrawArea() {
    delete currentPaintHandler;
}

void DrawArea::setPaintHandler( PaintHandler* handler ) {
    handler->settings = currentPaintHandler->settings;
    delete currentPaintHandler;
    currentPaintHandler = handler;

    // Test if we're a pan tool...
    PanTool* x = dynamic_cast<PanTool*>(handler);
    if ( x ) {
        this->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
    } else {
        this->setDragMode(QGraphicsView::DragMode::NoDrag);
    }
}

PaintHandler &DrawArea::paintHandler() {
    return *currentPaintHandler;
}

void DrawArea::setFrame(Frame *frame) {
    this->frame = frame;
    setScene(&frame->scene());
}

void DrawArea::updateDisplay() {
   viewport()->repaint();
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
    emit updatePreview();
    emit updateFrame();
}

void DrawArea::mouseMoveEvent(QMouseEvent *event) {
    if (!currentPaintHandler) {
        return;
    }
    
    QPointF pos = mapToScene(event->pos());
    currentPaintHandler->mouseMoveEvent(frame->activeLayer()->pixmap(), event->buttons(), pos );
    
    this->viewport()->update();
    emit updatePreview();
    emit updateFrame();
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
    emit updatePreview();
    emit updateFrame();
}
