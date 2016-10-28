
#include "layer.h"

Layer::Layer() :
    image(std::make_shared<QPixmap>(500, 500)) {
    image->fill(Qt::transparent);
}

QRectF Layer::boundingRect() const {
    return QRectF(image->rect());
}

void Layer::paint(QPainter *painter,
                  const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
    
    painter->drawPixmap(image->rect(), *image);
}

QPixmap &Layer::pixmap() {
    return *image.get();
}
