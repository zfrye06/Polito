
#ifndef FRAME_H
#define FRAME_H

#include <QGraphicsScene>
#include <QImage>
#include <vector>
#include "action.h"
#include "animationeventemitter.h"
#include "animationwidgets.h"
#include "layer.h"

class AddLayerAction;
class MoveLayerAction;
class RemoveLayerAction;
class ClearFrameAction;

// Represents a frame consisting of a stack of images, or layers,
// indexed from 0 starting at the bottom-most layer. 
// Always contains one or more layers.
class Frame {
    friend class AddLayerAction;
    friend class RemoveLayerAction;
    friend class MoveLayerAction;
    friend class ClearFrameAction;
 public:

    static const int DEFAULT_DURATION = 1000;

    // Constructs a new frame with a single layer.
    Frame(AnimationEventEmitter &emitter, int dim);

    // Constructs a new frame with a single layer matching
    // the given image.
    Frame(AnimationEventEmitter &emitter, QImage);

    // Constructs a frame with the given layers. The frame takes
    // ownership of each layer.
    Frame(AnimationEventEmitter &emitter, std::vector<std::unique_ptr<Layer>> &layers);

    // Adds a single layer to the top of this frame.
    // Does not change the active layer.
    // Emits an AddLayerAction.
    void addLayer();

    // Adds a single layer to this frame at the given index, which must
    // be in the range [0, numlayers()]. Does not change the active layer.
    // Emits an AddLayerAction.
    void addLayer(int index);

    // Moves the layer at fromIndex to toIndex. If the layer is the active
    // layer, it remains so. If not, the active layer is unchanged.
    // Emits a MoveLayerAction.
    void moveLayer(int fromIndex, int toIndex);

    // Removes the layer at the given index, which must be in the range
    // [0, numlayers()). If the layer is the active layer, sets the active
    // layer to the next layer, which now occupies the removed layer's position,
    // or the previous layer, if the removed layer was the top layer.
    // Emits a RemoveLayerAction.
    void removeLayer(int index);

    // Sets the layer currently being edited.
    // idx must be in the range [0, numlayers()).
    void setActiveLayer(int index);

    // Returns the index of the active layer.
    int activeLayerIdx() const;

    Layer* activeLayer();

    // Returns the number of layers in this frame.
    int numlayers() const;

    // Returns a non-owning vector of the layers in this frame.
    std::vector<Layer *>& getLayers();

    // Sets the duration of this frame to the number of milliseconds given.
    void setDuration(int duration);

    // Returns the duration of this frame in milliseconds,
    // or -1 if no duration is set.
    int duration() const;

    // Resizes the image this frame represents to the given dimension.
    void resize(int dim);

    // Removes all layers from this frame and adds a single empty layer.
    void clear();

    // Returns this frame's underlying QGraphicsScene.
    QGraphicsScene& scene();

    // Returns the image this frame represents.
    QImage image();

 private:

    // These perform the action without emitting an event.
    void addLayerInternal(Layer *layer, int index);
    void moveLayerInternal(int fromIndex, int toIndex);
    void removeLayerInternal(Layer *layer, int index);
    void clearInternal(Layer *newbottom);

    AnimationEventEmitter &emitter;
    
    // Ownership of the layers is a bit tricky here. When a layer is held by
    // this frame in the graphics scene, the scene owns it.  When it is held by
    // an AddLayerAction which has been undone, the action owns it. When it is
    // held by a RemoveLayerAction that has not been undone, the action owns
    // it. If, in either of these latter cases, the owning action is evicted
    // from ActionHistory, the layer should be deleted.
    std::vector<Layer *> layers;
    QGraphicsScene gscene;
    int activeLayerIndex;
    int durationMs;
    int dim;
};

class AddLayerAction : public Action {
 public:

 AddLayerAction(Frame *frame, Layer *layer, int index) :
    frame(frame), layer(layer), index(index), ownsLayer(false), widget(nullptr) {}

    ~AddLayerAction() {
        if (ownsLayer) {
            delete layer;
        }
    }

    void undo() {
        frame->removeLayerInternal(layer, index);
        ownsLayer = true;
        if (widget != nullptr) {
            widget->removeLayer(index);
        }
    }

    void redo() {
        frame->addLayerInternal(layer, index);
        ownsLayer = false;
        if (widget != nullptr) {
            widget->addLayer(index);
        }
    }

    void setFrameWidget(FrameWidget *w) {
        widget = w;
    }

 private:
    Frame *frame;
    Layer *layer;
    int index;
    bool ownsLayer;
    FrameWidget *widget;
};

class MoveLayerAction : public Action {
 public:

 MoveLayerAction(Frame *frame, int fromIndex, int toIndex) :
    frame(frame), fromIndex(fromIndex), toIndex(toIndex), widget(nullptr) {}

    void undo() {
        frame->moveLayerInternal(toIndex, fromIndex);
        if (widget != nullptr) {
            widget->moveLayer(toIndex, fromIndex);
        }
    }

    void redo() {
        frame->moveLayerInternal(fromIndex, toIndex);
        if (widget != nullptr) {
            widget->moveLayer(fromIndex, toIndex);
        }
    }

    void setFrameWidget(FrameWidget *w) {
        widget = w;
    }

 private:
    Frame *frame;
    int fromIndex;
    int toIndex;
    FrameWidget *widget;
};

class RemoveLayerAction : public Action {
 public:

 RemoveLayerAction(Frame *frame, Layer *layer, int index) :
    frame(frame), layer(layer), index(index), ownsLayer(true), widget(nullptr) {}

    ~RemoveLayerAction() {
        if (ownsLayer) {
            delete layer;
        }
    }

    void undo() {
        frame->addLayerInternal(layer, index);
        ownsLayer = false;
        if (widget != nullptr) {
            widget->addLayer(index);
        }
    }

    void redo() {
        frame->removeLayerInternal(layer, index);
        ownsLayer = true;
        if (widget != nullptr) {
            widget->removeLayer(index);
        }
    }

    void setFrameWidget(FrameWidget *w) {
        widget = w;
    }

 private:
    Frame *frame;
    Layer *layer;
    int index;
    bool ownsLayer;
    FrameWidget *widget;
};

class ClearFrameAction : public Action {
 public:
    
    ClearFrameAction(Frame *frame, std::vector<Layer*> layers, Layer *newbottom) :
       frame(frame), layers(layers), newbottom(newbottom), ownsLayers(true), widget(nullptr) {}

    ~ClearFrameAction() {
        if (ownsLayers) for (auto layer : layers) delete layer;
        else delete newbottom;
    }

    void undo() {
        frame->layers.clear();
        frame->gscene.removeItem(newbottom);
        for (int i = 0; i < (int)layers.size(); i++) {
            frame->addLayerInternal(layers.at(i), i);
        }
        frame->activeLayerIndex = 0;
        if (widget != nullptr) {
            widget->updateDisplay();
        }
    }

    void redo() {
        frame->clearInternal(newbottom);
        if (widget != nullptr) {
            widget->updateDisplay();
        }
    }

    void setWidgetToUpdate(UpdateableWidget *w) {
        widget = w;
    }

 private:
    Frame *frame;
    std::vector<Layer*> layers;
    Layer *newbottom; // The "new bottom" layer added after the frame was cleared.
    bool ownsLayers;
    UpdateableWidget *widget;
};

#endif // FRAME_H
