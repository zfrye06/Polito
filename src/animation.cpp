#include "animation.h"
#include <iostream>

Layer::Layer() : image(500, 500) {
  image.fill(Qt::transparent);
}

QRectF Layer::boundingRect() const {
  return QRectF(image.rect());
}

void Layer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
  std::cout << "paint" << std::endl;
  painter->drawPixmap(image.rect(), image);
}

void Layer::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  std::cout << "mouse pressed" << std::endl;
  drawState.lastMousePoint = event->pos().toPoint();
}

void Layer::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  std::cout << "mouse move" << std::endl;
  QPainter painter(&image);
  painter.setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
  painter.drawLine(drawState.lastMousePoint, event->pos());
  update();
  drawState.lastMousePoint = event->pos().toPoint();
}

void Layer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  std::cout << "mouse released" << std::endl;
}

Frame::Frame() : durationMs(-1) {
  addLayer();
  setActiveLayer(0);
}

void Frame::addLayer() {
  addLayer(layers.size());
}

void Frame::addLayer(int index) {
  Layer *l = new Layer;
  gscene.addItem(l);
  l->setZValue(index);
}

void Frame::removeLayer(int index) {
  Layer *l = layers[index];
  gscene.removeItem(l);
  delete l;
  layers.erase(layers.begin() + index);
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

QGraphicsScene& Frame::scene() { return gscene; }

Animation::Animation() {
  addFrame();
  setActiveFrame(0);
}

void Animation::addFrame() {
  addFrame(frames.size());
}

void Animation::addFrame(int index) {
  std::unique_ptr<Frame> f(new Frame);
  frames.insert(frames.begin() + index, std::move(f));
}

void Animation::removeFrame(int index) {
  frames.erase(frames.begin() + index);
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
