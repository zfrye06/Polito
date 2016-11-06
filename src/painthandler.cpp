#include <QStack>
#include "painthandler.h"

PaintSettings PaintSettings::defaults() {
    PaintSettings s;
    s.color = Qt::black;
    s.brushWidth = 1;
    return s;
}

PaintHandler::PaintHandler() : settings(PaintSettings::defaults()) {}

PaintHandler::~PaintHandler() {
}

void PanTool::mousePressEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) {
}

void PanTool::mouseMoveEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) {
}

void PanTool::mouseReleaseEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) {
}

void PaintBrush::mousePressEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) {
    lastMousePoint = pos;
}

void PaintBrush::mouseMoveEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) {
    QPainter painter(&image);
    painter.setPen(QPen(settings.color, settings.brushWidth, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
    painter.drawLine(lastMousePoint, pos);
    lastMousePoint = pos;
}

void PaintBrush::mouseReleaseEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos) {
}

void Eraser::mousePressEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos ) {
    lastMousePoint = pos;
}

void Eraser::mouseMoveEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos ) {
    QPainter painter(&image);
    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    painter.setPen(QPen(Qt::transparent, settings.brushWidth, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
    painter.drawLine(lastMousePoint, pos);
    lastMousePoint = pos;
}

void Eraser::mouseReleaseEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos ) {
}

void PaintBucket::mousePressEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos ){
    QPainter painter(&image);
    QImage newImage = image.toImage();
    QPoint point = pos.toPoint();

    painter.setPen(QPen(settings.color));

    floodFill(newImage, painter, newImage.pixelColor(point.x(), point.y()), settings.color, point);
}

void PaintBucket::floodFill( QImage &image, QPainter &painter, QColor target, QColor replacement, QPoint position ){
    QStack<PixelInfo> unprocessedPixels;
    PixelInfo first(position, PixelDirection::None);
    unprocessedPixels.push(first);
    while(unprocessedPixels.size() != 0){
        PixelInfo currentPoint = unprocessedPixels.pop();
        
        if (!image.valid(currentPoint.point)) {
            continue;
        }
            
        QColor currentColor = image.pixelColor(currentPoint.point.x(), currentPoint.point.y());

        if(currentColor != target || currentColor == replacement){
            continue;
        }

        painter.drawPoint(currentPoint.point);
        image.setPixelColor(currentPoint.point, replacement);

        QPoint northPoint(currentPoint.point.x(), currentPoint.point.y() - 1);
        QPoint southPoint(currentPoint.point.x(), currentPoint.point.y() + 1);
        QPoint eastPoint(currentPoint.point.x() + 1, currentPoint.point.y());
        QPoint westPoint(currentPoint.point.x() - 1, currentPoint.point.y());

        switch( currentPoint.direction ) {
            case PixelDirection::North: {
                unprocessedPixels.push(PixelInfo(northPoint,PixelDirection::North));
                unprocessedPixels.push(PixelInfo(eastPoint,PixelDirection::East));
                unprocessedPixels.push(PixelInfo(westPoint,PixelDirection::West));
                break;
                                        }
            case PixelDirection::West: {
                unprocessedPixels.push(PixelInfo(northPoint,PixelDirection::North));
                unprocessedPixels.push(PixelInfo(southPoint,PixelDirection::South));
                unprocessedPixels.push(PixelInfo(westPoint,PixelDirection::West));
                break;
                                       }
            case PixelDirection::East: {
                unprocessedPixels.push(PixelInfo(northPoint,PixelDirection::North));
                unprocessedPixels.push(PixelInfo(southPoint,PixelDirection::South));
                unprocessedPixels.push(PixelInfo(eastPoint,PixelDirection::East));
                break;
                                       }
            case PixelDirection::South: {
                unprocessedPixels.push(PixelInfo(southPoint,PixelDirection::South));
                unprocessedPixels.push(PixelInfo(eastPoint,PixelDirection::East));
                unprocessedPixels.push(PixelInfo(westPoint,PixelDirection::West));
                break;
                                        }
            case PixelDirection::None: {
                unprocessedPixels.push(PixelInfo(southPoint,PixelDirection::North));
                unprocessedPixels.push(PixelInfo(southPoint,PixelDirection::South));
                unprocessedPixels.push(PixelInfo(eastPoint,PixelDirection::East));
                unprocessedPixels.push(PixelInfo(westPoint,PixelDirection::West));
                break;
                                       }
            default: {
                         throw "Yeah this should never throw haha.";
                     }
        }
    }
}

void PaintBucket::mouseMoveEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos ){

}

void PaintBucket::mouseReleaseEvent( QPixmap &image, Qt::MouseButtons buttons, QPointF pos ){

}

void PaintSquare::mousePressEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos){
    baseImage = image;
    lastMousePoint = pos;
}

void PaintSquare::mouseMoveEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos){
    image = baseImage;
    QPainter painter(&image);
    painter.setPen(QPen(settings.color, settings.brushWidth, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
    QRectF rect(lastMousePoint, pos);
    painter.drawRect(rect);
}

void PaintSquare::mouseReleaseEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos){
    QPainter painter(&image);
    painter.setPen(QPen(settings.color, settings.brushWidth, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
    QRectF rect(lastMousePoint, pos);
    painter.drawRect(rect);
}

void PaintCircle::mousePressEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos){
    baseImage = image;
    lastMousePoint = pos;
}

void PaintCircle::mouseMoveEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos){
    image = baseImage;
    QPainter painter(&image);
    painter.setPen(QPen(settings.color, settings.brushWidth, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
    QRectF ellipse(lastMousePoint, pos);
    painter.drawEllipse(ellipse);
}

void PaintCircle::mouseReleaseEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos){
    QPainter painter(&image);
    painter.setPen(QPen(settings.color, settings.brushWidth, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
    QRectF ellipse(lastMousePoint, pos);
    painter.drawEllipse(ellipse);
}

void PaintLine::mousePressEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos){
    baseImage = image;
    lastMousePoint = pos;
}

void PaintLine::mouseMoveEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos){
    image = baseImage;
    QPainter painter(&image);
    painter.setPen(QPen(settings.color, settings.brushWidth, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
    QLineF line(lastMousePoint, pos);
    painter.drawLine(line);
}

void PaintLine::mouseReleaseEvent(QPixmap &image, Qt::MouseButtons buttons, QPointF pos){
    QPainter painter(&image);
    painter.setPen(QPen(settings.color, settings.brushWidth, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
    QLineF line(lastMousePoint, pos);
    painter.drawLine(line);
}

PixelInfo::PixelInfo(){
    QPoint p(0,0);
    point = p;
}
