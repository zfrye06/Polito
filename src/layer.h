
#ifndef LAYER_H
#define LAYER_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <memory>
#include "action.h"

class DrawAction;

class Layer : public QGraphicsItem {
    friend class DrawAction;
 public:

    Layer(int dim);
    Layer(QImage);
    QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QPixmap &pixmap();

 private:

    std::shared_ptr<QPixmap> image;
};

class DrawAction : public Action {
 public:

 DrawAction(Layer *layer, std::shared_ptr<QPixmap> before) :
    layer(layer), before(before) {}

    void finish(std::shared_ptr<QPixmap> after) {
        this->after = after;
    }

    void undo() {
        layer->image = std::shared_ptr<QPixmap>(new QPixmap(*before));
        layer->update();
    }

    void redo() {
        layer->image = std::shared_ptr<QPixmap>(new QPixmap(*after));
        layer->update();
    }

 private:

    Layer *layer;
    std::shared_ptr<QPixmap> before;
    std::shared_ptr<QPixmap> after;
};

#endif // LAYER_H
