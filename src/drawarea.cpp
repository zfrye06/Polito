#include "drawarea.h"

DrawArea::~DrawArea() {
    delete currentPaintHandler;
}

void DrawArea::setPaintHandler( PaintHandler* currentPaintHandler ) {
    delete currentPaintHandler;
    currentPaintHandler = currentPaintHandler;
}

void DrawArea::mousePressEvent( QMouseEvent* event ) {
    if (!currentPaintHandler) {
        return;
    }
    currentAction = new DrawAction( animation->activeFrame()->activeLayer(), animation->activeFrame()->activeLayer()->pixmap() );
    QPointF pos = mapToScene(event->pos());
    currentPaintHandler->mousePressEvent( animation->activeFrame()->activeLayer()->pixmap(), event->buttons(), pos );
    this->viewport()->update();
}

void DrawArea::mouseMoveEvent( QMouseEvent* event ) {
    if (!currentPaintHandler) {
        return;
    }
    QPointF pos = mapToScene(event->pos());
    currentPaintHandler->mouseMoveEvent( animation->activeFrame()->activeLayer()->pixmap(), event->buttons(), pos );
    this->viewport()->update();
}

void DrawArea::mouseReleaseEvent( QMouseEvent* event ) {
    if (!currentPaintHandler) {
        return;
    }
    currentAction->finish( animation->activeFrame()->activeLayer()->pixmap() );
    emit addAction( currentAction );
    QPointF pos = mapToScene(event->pos());
    currentPaintHandler->mouseReleaseEvent( animation->activeFrame()->activeLayer()->pixmap(), event->buttons(), pos );
    this->viewport()->update();
}
