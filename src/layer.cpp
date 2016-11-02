
#include "layer.h"

Layer::Layer(int dim) :
    image(std::make_shared<QPixmap>(dim, dim)) {
    image->fill(Qt::transparent);
}

Layer::Layer(QImage image) :
    image(std::shared_ptr<QPixmap>(new QPixmap(QPixmap::fromImage(image)))) {}

void Layer::resize(int dimension) {
    image = std::make_shared<QPixmap>(
                image->scaled(dimension, dimension, Qt::KeepAspectRatio));
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

int Layer::dimension() const {
    return image->height();
}
