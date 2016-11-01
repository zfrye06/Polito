
#include "layer.h"

Layer::Layer(int dim) :
    image(std::make_shared<QPixmap>(dim, dim)) {
    image->fill(Qt::transparent);
}

Layer::Layer(QImage image) :
    image(std::shared_ptr<QPixmap>(new QPixmap(QPixmap::fromImage(image)))) {}

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
