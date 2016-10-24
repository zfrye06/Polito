
#ifndef FRAME_H
#define FRAME_H

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

enum PaintMode {
  SELECTION,
  BRUSH,
  FILL,
  ERASE,
  LINE,
  RECTANGLE,
  CIRCLE
};

struct DrawState {
  QPoint lastMousePoint;
};

class Layer : public QGraphicsItem {
 public:

  Layer();
  QRectF boundingRect() const override;
  void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

 protected:

  virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override;
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *) override;
  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;

 private:

  QPixmap image;
  DrawState drawState;
};

// Represents a frame consisting of a stack of images, or layers,
// indexed from 0 starting at the bottom-most layer. A frame
// always contains one or more layers.
class Frame {
 public:

  // Constructs a new frame with a single layer.
  Frame();

  // Adds a single layer to the top of this frame.
  // Does not change the active layer.
  void addLayer();

  // Adds a single layer to this frame at the given index, which must
  // be in the range [0, numlayers()]. Does not change the active layer.
  void addLayer(int index);

  // Removes the layer at the given index, which must be in the range
  // [0, numlayers()).
  void removeLayer(int index);

  // Sets the layer currently being edited.
  // idx must be in the range [0, numlayers()).
  void setActiveLayer(int index);

  // Returns the number of layers in this frame.
  int numlayers() const;

  // Sets the duration of this frame to the number of milliseconds given.
  void setDuration(int duration);

  // Returns the duration of this frame in milliseconds,
  // or -1 if no duration is set.
  int duration() const;

  QGraphicsScene& scene();

 private:

  // gscene owns the layers. We maintain the pointers in order
  // to access and control them by z-index (layer index) in the scene.
  std::vector<Layer*> layers;
  int activeLayerIndex;
  int durationMs;
  QGraphicsScene gscene;
};

class Animation {
 public:

  // Constructs an animation with a single frame.
  Animation();

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
};

#endif // FRAME_H
