
#include <QtWidgets>
#include <iostream>

#include "drawarea.h"

DrawArea::DrawArea(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(true);
    //if (!background.load("../checkerboard.png")) {
    //    throw 1;
    //}
    resizeImage( &image, QSize(64,64) );
    // Set up the camera matrix
    camera.translate( size().rwidth()/2, size().rheight()/2 );
    //camera.rotate(45);
    //camera.rotate(45,Qt::YAxis);
    //camera.translate( 256, 256 );
    //camera.translate( image.width()/2, image.height()/2 );
    cameraScale = 1;
    offset = QPoint(-image.width()/2,-image.height()/2);
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    //dragging = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::blue;
    //QHBoxLayout *layout = new QHBoxLayout();
    layerMenu = new LayerMenu(this);
    //layerMenu->setLayout(layout);
}

void DrawArea::setImage(QImage& i ) {
    //QSize newSize = i.size().expandedTo(size());
    //resizeImage(&i, newSize);
    image = i;
    modified = true;
    update();
}

QImage& DrawArea::getImage() {
    return image;
}

bool DrawArea::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    modified = false;
    update();
    return true;
}

bool DrawArea::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}

void DrawArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void DrawArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void DrawArea::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void DrawArea::wheelEvent( QWheelEvent* event ) {
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees/15;
    if ( numSteps == 0 ) {
        event->accept();
        return;
    }
    if ( numSteps > 0 ) {
        camera.scale(2, 2);
        cameraScale *= 2;
    } else {
        camera.scale(0.5,0.5);
        cameraScale *= 0.5;
    }
    update();
    event->accept();
}

void DrawArea::mousePressEvent(QMouseEvent *event)
{
    QPoint p = QPoint( floor(event->pos().x()), floor(event->pos().y()) )*camera.inverted()-QPoint(offset.x(),offset.y());
    QPoint realp = QPoint( floor(event->pos().x()), floor(event->pos().y()) );
    if (event->button() == Qt::LeftButton) {
        lastPoint = p;
        scribbling = true;
        currentAction = new ScribbleAction( this );
    }
    if ((event->button() == Qt::MidButton)) {
        lastDraggingPoint = realp;
        dragging = true;
    }
}

void DrawArea::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p = QPoint( floor(event->pos().x()), floor(event->pos().y()) )*camera.inverted()-QPoint(offset.x(), offset.y());
    QPoint realp = QPoint( floor(event->pos().x()), floor(event->pos().y()) );
    if ((event->buttons() & Qt::LeftButton) && scribbling) {
        drawLineTo(p);
    }
    if ( (event->buttons() & Qt::MidButton) && dragging ) {
        offset += (realp-lastDraggingPoint)/cameraScale;
        lastDraggingPoint = realp;
        update();
    }
}

void DrawArea::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint p = QPoint( floor(event->pos().x()), floor(event->pos().y()) )*camera.inverted()-QPoint(offset.x(),offset.y());
    QPoint realp = QPoint( floor(event->pos().x()), floor(event->pos().y()) );
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(p);
        scribbling = false;
        currentAction->finish();
        emit addAction( (Action*)currentAction );
    }
    if ( event->button() == Qt::MidButton && dragging ) {
        offset += (realp-lastDraggingPoint)/cameraScale;
        dragging = false;
        update();
    }
}

void DrawArea::paintEvent(QPaintEvent *event)
{
    // Clamp offset to screen
    QPointF projectedOffset = (offset+(QPoint(image.size().rwidth(),image.size().rheight()))/2)*camera;
    if ( projectedOffset.x() > size().rwidth() + image.size().rwidth()/2*cameraScale) {
        projectedOffset.setX(size().rwidth() + image.size().rwidth()/2*cameraScale);
    } else if ( projectedOffset.x() < 0 - image.size().rwidth()/2*cameraScale ) {
        projectedOffset.setX(0 - image.size().rwidth()/2*cameraScale);
    }
    if ( projectedOffset.y() > size().rheight() + image.size().rheight()/2*cameraScale ) {
        projectedOffset.setY(size().rheight() + image.size().rheight()/2*cameraScale );
    } else if ( projectedOffset.y() < 0 - image.size().rheight()/2*cameraScale ) {
        projectedOffset.setY(0 - image.size().rheight()/2*cameraScale);
    }
    offset = projectedOffset*camera.inverted()-(QPoint(image.size().rwidth(),image.size().rheight()))/2;
    QPainter painter(this);
    QRect dirtyRect = event->rect();

    // First draw a checkerboard.
    //painter.drawImage(dirtyRect, background, dirtyRect);
    painter.setTransform( camera );
    // Then the layers in order
    painter.drawImage(offset-QPointF(0.5,0.5), image, dirtyRect);
}

void DrawArea::resizeEvent(QResizeEvent *event)
{
    // We don't want to resize the image all willy-nilly
    /*if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }*/
    QWidget::resizeEvent(event);
}

void DrawArea::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    //int rad = (myPenWidth / 2) + 2;
    // This update tries to just update what changed instead of the whole widget. PfFFFFF hahahaha
    //update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    update();
    lastPoint = endPoint;
}

void DrawArea::resizeImage( int width, int height, int filtering ) {
    resizeImage( &image, QSize( width, height ) );
    if ( filtering != 0 ) {
        throw 1; // not implemented
    }
    update();
}

void DrawArea::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

ScribbleAction::ScribbleAction( DrawArea* Area ) {
    area = Area;
    QImage copy(area->getImage());
    before = copy;
}

void ScribbleAction::undo() {
    area->setImage( before );
}

void ScribbleAction::finish() {
    QImage copy(area->getImage());
    after = copy;
}

void ScribbleAction::redo() {
    area->setImage( after );
}
