
#include "frame.h"
#include <stdexcept>

Frame::Frame(AnimationEventEmitter &emitter) :
    emitter(emitter), activeLayerIndex(0), durationMs(-1) {
    addLayer();
    activeLayerIndex = 0;
}

void Frame::addLayer() {
    addLayer(layers.size());
}

void Frame::addLayer(int index) {
    if (index < 0 || index > (int)layers.size()) {
        throw std::invalid_argument("Index out of bounds.");
    }
    Layer *layer = new Layer();
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
        for (auto i = toIndex; i < fromIndex; i++) {
            layers[i + 1] = layers[i];
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
    if (index != activeLayerIndex) {
        layers[activeLayerIndex]->setEnabled(false);
        activeLayerIndex = index;
        layers[activeLayerIndex]->setEnabled(true);
    }
}

int Frame::activeLayerIdx() const {
    return activeLayerIndex;
}

Layer* Frame::activeLayer() {
    return layers[activeLayerIndex];
}

int Frame::numlayers() const {
    return layers.size();
}

void Frame::setDuration(int duration) { durationMs = duration; }

int Frame::duration() const { return durationMs; }

void Frame::clear() {
    gscene.clear();
    layers.clear();
    addLayer();
    setActiveLayer(0);
}

QGraphicsScene& Frame::scene() { return gscene; }
