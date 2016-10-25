#include "animation.h"
#include <iostream>
#include <stdexcept>

Layer::Layer(AnimationEventEmitter *emitter) :
  image(std::make_shared<QPixmap>(500, 500)), emitter(emitter) {
  image->fill(Qt::transparent);
}

QRectF Layer::boundingRect() const {
  return QRectF(image->rect());
}

void Layer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
  std::cout << "paint" << std::endl;
  painter->drawPixmap(image->rect(), *image);
}

void Layer::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  std::cout << "mouse pressed" << std::endl;
  prevImage = std::make_shared<QPixmap>(*image);
  drawState.lastMousePoint = event->pos().toPoint();
}

void Layer::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  std::cout << "mouse move" << std::endl;
  QPainter painter(image.get());
  painter.setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
  painter.drawLine(drawState.lastMousePoint, event->pos());
  drawState.lastMousePoint = event->pos().toPoint();
  update();
}

void Layer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  std::cout << "mouse released" << std::endl;
  emitter->emitDrawEvent(new DrawAction(this, prevImage, image));
}

Frame::Frame(AnimationEventEmitter *emitter) : durationMs(-1), emitter(emitter){
  addLayer();
  setActiveLayer(0);
}

void Frame::addLayer() {
  addLayer(layers.size());
}

void Frame::addLayer(int index) {
  Layer *l = new Layer(emitter);
  gscene.addItem(l);
  l->setZValue(index);
  if (activeLayerIndex == index) activeLayerIndex++;
}

void Frame::removeLayer(int index) {
  if (layers.size() == 1) {
    throw std::invalid_argument("A Frame must have at least one layer.");
  }
  Layer *l = layers[index];
  gscene.removeItem(l);
  delete l;
  layers.erase(layers.begin() + index);
  if (index == activeLayerIndex && activeLayerIndex != 0) activeLayerIndex--;
}

void Frame::setActiveLayer(int index) {
  // TODO: ERROR CHECK
  activeLayerIndex = index;
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

Animation::Animation(AnimationEventEmitter *emitter) : emitter(emitter) {
  addFrame();
  setActiveFrame(0);
}

void Animation::addFrame() {
  addFrame(frames.size());
}

void Animation::addFrame(int index) {
  std::unique_ptr<Frame> f(new Frame(emitter));
  frames.insert(frames.begin() + index, std::move(f));
  if (activeFrameIndex == index) activeFrameIndex++;
}

void Animation::removeFrame(int index) {
  if (frames.size() == 0) {
    throw std::invalid_argument("An animation must have at least one frame.");
  }
  frames.erase(frames.begin() + index);
  if (index == activeFrameIndex && activeFrameIndex != 0) activeFrameIndex--;
}

void Animation::setActiveFrame(int index) {
  // TODO: Error check?
  activeFrameIndex = index;
}

Frame& Animation::activeFrame() {
  return *frames[activeFrameIndex];
}

void Animation::resize(int dim) {
  
}

int Animation::numframes() const {
  return frames.size();
}

void Animation::save(std::ostream& out) const {
  
}

void Animation::saveExtendedFormat(std::ostream& out) const {
  
}

void Animation::saveGif(std::ostream& out) const {
  
}

void Animation::load(std::istream& in) {
  
}
