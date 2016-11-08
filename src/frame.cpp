
#include "frame.h"
#include <stdexcept>

Frame::Frame(AnimationEventEmitter &emitter, int dim) :
    emitter(emitter), activeLayerIndex(0), durationMs(Frame::DEFAULT_DURATION), dim(dim) {
    addLayerInternal(new Layer(dim), 0);
    activeLayerIndex = 0;
}

Frame::Frame(AnimationEventEmitter &emitter, QImage image) :
    emitter(emitter), activeLayerIndex(0), durationMs(Frame::DEFAULT_DURATION), dim(image.height()) {
    addLayerInternal(new Layer(image), 0);
    activeLayerIndex = 0;
}

Frame::Frame(AnimationEventEmitter &emitter, std::vector<std::unique_ptr<Layer>> &inlayers) :
    emitter(emitter), activeLayerIndex(0), durationMs(Frame::DEFAULT_DURATION) {
    if (inlayers.size() == 0) {
        throw std::invalid_argument("layers must contain at least one layer.");
    }
    dim = inlayers.front()->dimension();
    for (auto& layer : inlayers) {
        addLayerInternal(layer.release(), layers.size());
    }
    activeLayerIndex = 0;
}

void Frame::addLayer() {
    addLayer(layers.size());
}

void Frame::addLayer(int index) {
    if (index < 0 || index > (int)layers.size()) {
        throw std::invalid_argument("Index out of bounds.");
    }
    Layer *layer = new Layer(dim);
    addLayerInternal(layer, index);
    emitter.emitAddLayerEvent(new AddLayerAction(this, layer, index));
}

void Frame::addLayerInternal(Layer *layer, int index) {
    gscene.addItem(layer);
    layers.insert(layers.begin() + index, layer);
    layer->setZValue(index);
    for (auto i = index + 1; i < (int)layers.size(); i++) {
        layers[i]->setZValue(i);
    }
    if (activeLayerIndex >= index) {
        activeLayerIndex++;
    }
}

void Frame::moveLayer(int fromIndex, int toIndex) {
    if (fromIndex < 0 || fromIndex >= (int)layers.size() ||
                    toIndex < 0 || toIndex >= (int)layers.size()) {
        throw std::invalid_argument("Index out of bounds");
    }
    moveLayerInternal(fromIndex, toIndex);
    emitter.emitMoveLayerEvent(new MoveLayerAction(this, fromIndex, toIndex));
}

void Frame::moveLayerInternal(int fromIndex, int toIndex) {
    Layer *layer = layers[fromIndex];
    if (fromIndex < toIndex) {
        for (auto i = fromIndex; i < toIndex; i++) {
            layers[i] = layers[i + 1];
            layers[i]->setZValue(i);
        }
        if (activeLayerIndex > fromIndex && activeLayerIndex <= toIndex) {
            activeLayerIndex--;
        }
    } else {
        for (auto i = fromIndex; i > toIndex; i--) {
            layers[i] = layers[i - 1];
            layers[i]->setZValue(i);
        }
        if (activeLayerIndex >= toIndex && activeLayerIndex < fromIndex) {
            activeLayerIndex++;
        }
    }
    if (activeLayerIndex == fromIndex) {
        activeLayerIndex = toIndex;
    }
    layers[toIndex] = layer;
    layer->setZValue(toIndex);
}

void Frame::removeLayer(int index) {
    if (index < 0 || index >= (int)layers.size()) {
        throw std::invalid_argument("Index out of bounds");
    }
    if (layers.size() == 1) {
        throw std::invalid_argument("A Frame must have at least one layer.");
    }
    Layer *layer = layers[index];
    removeLayerInternal(layer, index);
    emitter.emitRemoveLayerEvent(new RemoveLayerAction(this, layer, index));
}

void Frame::removeLayerInternal(Layer *layer, int index) {
    gscene.removeItem(layer);
    layers.erase(layers.begin() + index);
    for (auto i = index; i < (int)layers.size(); i++) {
        layers[i]->setZValue(i);
    }
    if (index < activeLayerIndex) {
        activeLayerIndex--;
    }
    else if (index == activeLayerIndex) {
        if (activeLayerIndex == (int)layers.size()) {
            activeLayerIndex--;
        }
        layers[activeLayerIndex]->setEnabled(true);
    }
}

void Frame::setActiveLayer(int index) {
    if (index < 0 || index >= (int)layers.size()) {
        throw std::invalid_argument("Index out of bounds");
    }
    activeLayerIndex = index;
}

int Frame::activeLayerIdx() const {
    return activeLayerIndex;
}

Layer* Frame::activeLayer() {
    return layers.at(activeLayerIndex);
}

int Frame::numlayers() const {
    return layers.size();
}

std::vector<Layer *>& Frame::getLayers() {
    return layers;
}

void Frame::setDuration(int duration) { durationMs = duration; }

int Frame::duration() const { return durationMs; }

void Frame::resize(int dimension, bool bilinear) {
    dim = dimension;
    for (auto layer : layers) layer->resize(dimension, bilinear);
}

void Frame::clear() {
    Layer *newbottom = new Layer(dim);
    std::unique_ptr<ClearFrameAction> action(new ClearFrameAction(this, layers, newbottom));
    clearInternal(newbottom);
    emitter.emitClearFrameEvent(action.release());
}

void Frame::clearInternal(Layer *newbottom) {
    for (auto layer : layers) gscene.removeItem(layer);
    layers.clear();
    addLayerInternal(newbottom, 0);
    activeLayerIndex = 0;
}

QGraphicsScene& Frame::scene() { return gscene; }

QImage Frame::image() {
    gscene.clearSelection();
    gscene.setSceneRect(gscene.itemsBoundingRect());
    QImage image(gscene.sceneRect().size().toSize(), QImage::Format_RGBA8888);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    gscene.render(&painter);
    return image;
}
