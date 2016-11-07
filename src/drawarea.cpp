#include "drawarea.h"

DrawArea::DrawArea(Frame *frame):
    frame(frame), currentPaintHandler(new PaintBrush()) {
    checkerboard = new QImage(":/icons/checkerboard");
	if(checkerboard->isNull()) {
        throw "Failed to load checkerboard image.";
    }
}

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

void DrawArea::setBrushWidth(int width){
    currentPaintHandler->settings.brushWidth = width;
}

void DrawArea::setFrame(Frame *frame) {
    this->frame = frame;
    QGraphicsScene &scene = frame->scene();
    setScene(&scene);
    //fitInView(scene.sceneRect(), Qt::KeepAspectRatio);
    updateDisplay();
}

void DrawArea::fitToScene() {
    QGraphicsScene &scene = frame->scene();
    fitInView(scene.sceneRect(), Qt::KeepAspectRatio);
    updateDisplay();
}

void DrawArea::updateDisplay() {
    QBrush brush = QBrush(*checkerboard);
    brush.setMatrix(this->matrix().inverted());
    this->setBackgroundBrush(brush);
    viewport()->repaint();
}

void DrawArea::mousePressEvent(QMouseEvent *event) {
    if ( event->buttons() & Qt::RightButton ) {
        rightMouseDown = true;
        lastPos = event->pos();
        return;
    }

    if (!currentPaintHandler) {
        return;
    }
    
    auto imgCpy = std::shared_ptr<QPixmap>(new QPixmap(frame->activeLayer()->pixmap()));
    currentAction = new DrawAction(frame->activeLayer(), imgCpy);

    QPointF pos = mapToScene(event->pos())-QPointF(0.5,0.5);
    currentPaintHandler->mousePressEvent(frame->activeLayer()->pixmap(), event->buttons(), pos );
    
    this->viewport()->update();
    emit updateView();
    QGraphicsView::mousePressEvent( event );
}

void DrawArea::mouseMoveEvent(QMouseEvent *event) {

    if ( event->buttons() & Qt::RightButton ) {
        QPoint delta = event->pos()-lastPos;
        float deltay = 1.f + (float)delta.ry() / 500.f;
        if ( deltay == 0 ) {
            deltay = 0.1;
        }
        this->scale( deltay, deltay );
        lastPos = event->pos();
        updateDisplay();
        return;
    }

    if (!currentPaintHandler) {
        return;
    }

    QPointF pos = mapToScene(event->pos())-QPointF(0.5,0.5);
    currentPaintHandler->mouseMoveEvent(frame->activeLayer()->pixmap(), event->buttons(), pos );
    

    this->viewport()->update();
    emit updateView();
    QGraphicsView::mouseMoveEvent( event );
}

void DrawArea::mouseReleaseEvent(QMouseEvent *event) {
    if(rightMouseDown){
        rightMouseDown = false;
        return;
    }

    if (!currentPaintHandler) {
        return;
    }
    
    QPointF pos = mapToScene(event->pos())-QPointF(0.5,0.5);
    currentPaintHandler->mouseReleaseEvent(frame->activeLayer()->pixmap(), event->buttons(), pos );

    auto imgCpy = std::shared_ptr<QPixmap>(new QPixmap(frame->activeLayer()->pixmap()));
    currentAction->finish(imgCpy);
    emit drawEvent(currentAction);
    
    this->viewport()->update();
    emit updateView();
    QGraphicsView::mouseReleaseEvent( event );
}

void DrawArea::drawForeground( QPainter* painter, const QRectF& outter ) {
    QGraphicsScene &scene = frame->scene();
    QRectF inner = scene.sceneRect();
    QRectF l = QRectF(outter.topLeft(),inner.bottomLeft());
    QRectF t = QRectF(outter.topLeft(),inner.topRight());
    QRectF r = QRectF(inner.right(),outter.top(),outter.right()-inner.right(),outter.height());
    QRectF b = QRectF(outter.left(),inner.bottom(),outter.width(),outter.bottom()-inner.bottom());
    painter->fillRect(l,QColor(245,245,220,255));
    painter->fillRect(t,QColor(245,245,220,255));
    painter->fillRect(r,QColor(245,245,220,255));
    painter->fillRect(b,QColor(245,245,220,255));
}
