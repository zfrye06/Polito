
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
class ResizeAction; // Implemented in animation.h

class Layer : public QGraphicsItem {
    friend class DrawAction;
    friend class ResizeAction;
 public:

    Layer(int dim);

    Layer(QImage);

    void resize(int dim, bool bilinear);

    QRectF boundingRect() const override;

    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

    QPixmap &pixmap();

    int dimension() const;

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
