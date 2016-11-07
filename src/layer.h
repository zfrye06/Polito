
#ifndef LAYER_H
#define LAYER_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <memory>
#include "action.h"
#include "animationwidgets.h"

class DrawAction;
class ResizeAction;

class Layer : public QGraphicsItem {
    friend class DrawAction;
    friend class ResizeAction;
 public:

    Layer(int dim);

    Layer(QImage);

    void resize(int dim);

    QRectF boundingRect() const override;

    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

    QPixmap &pixmap();

    int dimension() const;

    void setImage(QPixmap* image);

 private:

    std::shared_ptr<QPixmap> image;
};

class DrawAction : public Action {
 public:

 DrawAction(Layer *layer, std::shared_ptr<QPixmap> before) :
    layer(layer), before(before), widget(nullptr) {}

    void finish(std::shared_ptr<QPixmap> after) {
        this->after = after;
    }

    void undo() {
        layer->image = std::shared_ptr<QPixmap>(new QPixmap(*before));
        layer->update();
        if (widget != nullptr) {
            widget->updateDisplay();
        }
    }

    void redo() {
        layer->image = std::shared_ptr<QPixmap>(new QPixmap(*after));
        layer->update();
        if (widget != nullptr) {
            widget->updateDisplay();
        }
    }

    void setWidgetToUpdate(UpdateableWidget *w) {
        widget = w;
    }

 private:

    Layer *layer;
    std::shared_ptr<QPixmap> before;
    std::shared_ptr<QPixmap> after;
    UpdateableWidget *widget;
};

#endif // LAYER_H
