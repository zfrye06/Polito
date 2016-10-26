
#ifndef ANIMATION_H
#define ANIMATION_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <istream>
#include <memory>
#include <ostream>
#include <vector>
#include "action.h"

class DrawAction;
class AddLayerAction;
class MoveLayerAction;
class RemoveLayerAction;

// Serves as an event bus for all actions from
// within a single animation and its components.
class AnimationEventEmitter : public QObject {
  Q_OBJECT

 signals:

  void drawEvent(DrawAction *);
  void addLayerEvent(AddLayerAction *);
  void moveLayerEvent(MoveLayerAction *);
  void removeLayerEvent(RemoveLayerAction *);

 public:
  
  void emitDrawEvent(DrawAction *action) { emit drawEvent(action); }
  void emitAddLayerEvent(AddLayerAction *action) { emit addLayerEvent(action); }
  void emitMoveLayerEvent(MoveLayerAction *action) { emit moveLayerEvent(action); }
  void emitRemoveLayerEvent(RemoveLayerAction *action) { emit removeLayerEvent(action); }
};

struct DrawingState {
  QPoint lastMousePoint;
};

class Layer : public QGraphicsItem {
  friend class DrawAction;
 public:

  Layer(AnimationEventEmitter &);
  QRectF boundingRect() const override;
  void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

 protected:

  virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override;
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *) override;
  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;

 private:

  std::shared_ptr<QPixmap> image;
  std::shared_ptr<QPixmap> prevImage;
  DrawingState drawState;
  AnimationEventEmitter &emitter;
};

// Represents a frame consisting of a stack of images, or layers,
// indexed from 0 starting at the bottom-most layer. A frame
// always contains one or more layers.
class Frame {
  friend class AddLayerAction;
  friend class RemoveLayerAction;
  friend class MoveLayerAction;
 public:

  // Constructs a new frame with a single layer.
  Frame(AnimationEventEmitter &emitter);

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

  // Returns the number of layers in this frame.
  int numlayers() const;

  // Sets the duration of this frame to the number of milliseconds given.
  void setDuration(int duration);

  // Returns the duration of this frame in milliseconds,
  // or -1 if no duration is set.
  int duration() const;

  // Removes all layers from this frame and adds a single empty layer.
  void clear();

  QGraphicsScene& scene();

 private:

  // These perform the action without emitting an event.
  void addLayerInternal(Layer *layer, int index);
  void moveLayerInternal(int fromIndex, int toIndex);
  void removeLayerInternal(Layer *layer, int index);

  AnimationEventEmitter &emitter;
  QGraphicsScene gscene;

  // Ownership of the layers is a bit tricky here. When a layer is held by
  // this frame in the graphics scene, the scene owns it.  When it is held by
  // an AddLayerAction which has been undone, the action owns it. When it is
  // held by a RemoveLayerAction that has not been undone, the action owns
  // it. If, in either of these latter cases, the owning action is evicted
  // from ActionHistory, the layer should be deleted.
  std::vector<Layer *> layers;
  int activeLayerIndex;
  int durationMs;
};

class Animation {
 public:

  // Constructs an animation with a single frame.
  Animation(AnimationEventEmitter &emitter);

  void addFrame();

  void addFrame(int index);

  void removeFrame(int index);

  void setActiveFrame(int index);

  Frame& activeFrame();

  // Resizes every frame in this animation to the given dimension.
  // TODO: Add appropriately-typed size parameter.
  void resize(int dim);

  int numframes() const;

  void save(std::ostream&) const;

  void saveExtendedFormat(std::ostream&) const;

  void saveGif(std::ostream&) const;

  void load(std::istream&);

 private:

  std::vector<std::unique_ptr<Frame>> frames;
  int activeFrameIndex;
  AnimationEventEmitter &emitter;
};

class DrawAction : public Action {
 public:

 DrawAction(Layer *layer, std::shared_ptr<QPixmap> before,
            std::shared_ptr<QPixmap> after) :
  layer(layer), before(before), after(after) {}

  void undo() {
    layer->image = before;
    layer->update();
  }

  void redo() {
    layer->image = after;
    layer->update();
  }

 private:

  Layer *layer;
  std::shared_ptr<QPixmap> before;
  std::shared_ptr<QPixmap> after;
};

class AddLayerAction : public Action {
 public:

 AddLayerAction(Frame *frame, Layer *layer, int index) :
  frame(frame), layer(layer), index(index), ownsLayer(false) {}

  ~AddLayerAction() {
    if (ownsLayer) {
      delete layer;
    }
  }

  void undo() {
    frame->removeLayerInternal(layer, index);
    ownsLayer = true;
  }

  void redo() {
    frame->addLayerInternal(layer, index);
    ownsLayer = false;
  }

 private:
  Frame *frame;
  Layer *layer;
  int index;
  bool ownsLayer;
};

class MoveLayerAction : public Action {
 public:

 MoveLayerAction(Frame *frame, int fromIndex, int toIndex) :
  frame(frame), fromIndex(fromIndex), toIndex(toIndex) {}

  void undo() {
    frame->moveLayerInternal(toIndex, fromIndex);
  }

  void redo() {
    frame->moveLayerInternal(fromIndex, toIndex);
  }

 private:
  Frame *frame;
  int fromIndex;
  int toIndex;
};

class RemoveLayerAction : public Action {
 public:

 RemoveLayerAction(Frame *frame, Layer *layer, int index) :
  frame(frame), layer(layer), index(index), ownsLayer(true) {}

  ~RemoveLayerAction() {
    if (ownsLayer) {
      delete layer;
    }
  }

  void undo() {
    frame->addLayerInternal(layer, index);
    ownsLayer = false;
  }

  void redo() {
    frame->removeLayerInternal(layer, index);
    ownsLayer = true;
  }

 private:
  Frame *frame;
  Layer *layer;
  int index;
  bool ownsLayer;
};

#endif // ANIMATION_H
