
#ifndef ANIMATION_H
#define ANIMATION_H

#include <QColorDialog>
#include <istream>
#include <memory>
#include <ostream>
#include <vector>
#include "action.h"
#include "animationeventemitter.h"
#include "animationwidgets.h"
#include "frame.h"

class AddFrameAction;
class MoveFrameAction;
class RemoveFrameAction;
class ResizeAction;

class Animation {
    friend class AddFrameAction;
    friend class MoveFrameAction;
    friend class RemoveFrameAction;
    friend class ResizeAction;
 public:

    static const int DEFAULT_DIMENSION = 64;

    // Constructs an animation with a single frame.
    Animation(AnimationEventEmitter &emitter);

    void addFrame(int index);

    void moveFrame(int fromIndex, int toIndex);

    void removeFrame(int index);

    void setActiveFrame(int index);

    int activeFrameIdx() const;

    Frame &activeFrame();

    // Resizes every frame in this animation to the given dimension
    void resize(int dim);

    int dimension() const;

    int numframes() const;

    void save(std::ostream&) const;

    void saveExtendedFormat(std::ostream&) const;

    void saveGif(std::string filename) const;

    void load(std::istream&);

    std::vector<std::unique_ptr<Frame>>& getFrames();

    void setDim(int dim);

 private:

    void addFrameInternal(std::unique_ptr<Frame>, int index);
    void moveFrameInternal(int fromIndex, int toIndex);
    void removeFrameInternal(int index);
    void resizeInternal(int dim);

    std::vector<std::unique_ptr<Frame>> frames;
    int activeFrameIndex;
    int dim;
    AnimationEventEmitter &emitter;
};

class AddFrameAction : public Action {
 public:

 AddFrameAction(Animation *animation, int index) :
    animation(animation), index(index), widget(nullptr) {}

    void undo() {
        frame.swap(animation->frames.at(index));
        animation->removeFrameInternal(index);
        if (widget != nullptr) {
            widget->updateDisplay();
        }
    }

    void redo() {
        animation->addFrameInternal(std::move(frame), index);
        if (widget != nullptr) {
            widget->updateDisplay();
        }
    }

    void setWidgetToUpdate(UpdateableWidget *w) {
        widget = w;
    }

 private:
    Animation *animation;
    std::unique_ptr<Frame> frame;
    int index;
    UpdateableWidget *widget;
};

class MoveFrameAction : public Action {
 public:

 MoveFrameAction(Animation *animation, int fromIndex, int toIndex) :
    animation(animation), fromIndex(fromIndex), toIndex(toIndex), widget(nullptr) {}

    void undo() {
        animation->moveFrameInternal(toIndex, fromIndex);
        if (widget != nullptr) {
            widget->updateDisplay();
        }
    }

    void redo() {
        animation->moveFrameInternal(fromIndex, toIndex);
        if (widget != nullptr) {
            widget->updateDisplay();
        }
    }

    void setWidgetToUpdate(UpdateableWidget *w) {
        widget = w;
    }

 private:
    Animation *animation;
    int fromIndex;
    int toIndex;
    UpdateableWidget *widget;
};

class RemoveFrameAction : public Action {
 public:

 RemoveFrameAction(Animation *animation, std::unique_ptr<Frame> frame, int index) :
    animation(animation), frame(std::move(frame)), index(index), widget(nullptr) {}

    void undo() {
        animation->addFrameInternal(std::move(frame), index);
        if (widget != nullptr) {
            widget->updateDisplay();
        }
    }

    void redo() {
        frame.swap(animation->frames.at(index));
        animation->removeFrameInternal(index);
        if (widget != nullptr) {
            widget->updateDisplay();
        }
    }

    void setWidgetToUpdate(UpdateableWidget *w) {
        widget = w;
    }

 private:
    Animation *animation;
    std::unique_ptr<Frame> frame;
    int index;
    UpdateableWidget *widget;
};
#include <iostream>
class ResizeAction : public Action {
public:

    ResizeAction(Animation *animation, std::vector<std::unique_ptr<Frame>> &frames) :
        animation(animation), widget(nullptr) {
        for(int i = 0; i < frames.size(); i++){
            Frame &frame = *frames.at(i);
            pastLayers.push_back(std::vector<std::shared_ptr<QPixmap>>());
            for(auto layer : frame.getLayers()){
                pastLayers.at(i).push_back(layer->image);
            }
        }
    }

    void swapLayers() {
        std::vector<std::unique_ptr<Frame>> &frames = animation->getFrames();
        for (int i = 0; i < frames.size(); i++) {
            std::vector<Layer *> &layers = frames.at(i)->getLayers();
            for (int j = 0; j < layers.size(); j++) {
                std::shared_ptr<QPixmap> temp = layers.at(j)->image;
                layers.at(j)->image = pastLayers.at(i).at(j);
                pastLayers.at(i)[j] = temp;
            }
        }
        if (widget != nullptr) {
            widget->updateDisplay();
        }
    }

    void undo() {
        swapLayers();
    }

    void redo() {
        swapLayers();
    }

    void setWidgetToUpdate(UpdateableWidget *w) {
        widget = w;
    }

private:
   Animation *animation;
   std::vector<std::vector<std::shared_ptr<QPixmap>>> pastLayers;
   UpdateableWidget *widget;
};

#endif // ANIMATION_H
