
#ifndef ANIMATION_H
#define ANIMATION_H

#include <istream>
#include <memory>
#include <ostream>
#include <vector>
#include "action.h"
#include "animationeventemitter.h"
#include "frame.h"

class AddFrameAction;
class MoveFrameAction;
class RemoveFrameAction;

class Animation {
    friend class AddFrameAction;
    friend class MoveFrameAction;
    friend class RemoveFrameAction;
 public:

    // Constructs an animation with a single frame.
    Animation(AnimationEventEmitter &emitter);

    void addFrame();

    void addFrame(int index);

    void moveFrame(int fromIndex, int toIndex);

    void removeFrame(int index);

    void setActiveFrame(int index);

    Frame &activeFrame();

    // Resizes every frame in this animation to the given dimension.
    // TODO: Add appropriately-typed size parameter.
    void resize(int dim);

    int numframes() const;

    void save(std::ostream&) const;

    void saveExtendedFormat(std::ostream&) const;

    void saveGif(std::ostream&) const;

    void load(std::istream&);

    std::vector<std::unique_ptr<Frame>>& getFrames();

 private:

    void addFrameInternal(std::unique_ptr<Frame>, int index);
    void moveFrameInternal(int fromIndex, int toIndex);
    void removeFrameInternal(int index);

    std::vector<std::unique_ptr<Frame>> frames;
    int activeFrameIndex;
    AnimationEventEmitter &emitter;
};

class AddFrameAction : public Action {
 public:

 AddFrameAction(Animation *animation, int index) :
    animation(animation), index(index) {}

    void undo() {
        frame.swap(animation->frames[index]);
        animation->removeFrameInternal(index);
    }

    void redo() {
        animation->addFrameInternal(std::move(frame), index);
    }

 private:
    Animation *animation;
    std::unique_ptr<Frame> frame;
    int index;
    bool ownsLayer;
};

class MoveFrameAction : public Action {
 public:

 MoveFrameAction(Animation *animation, int fromIndex, int toIndex) :
    animation(animation), fromIndex(fromIndex), toIndex(toIndex) {}

    void undo() {
        animation->moveFrameInternal(toIndex, fromIndex);
    }

    void redo() {
        animation->moveFrameInternal(fromIndex, toIndex);
    }

 private:
    Animation *animation;
    int fromIndex;
    int toIndex;
};

class RemoveFrameAction : public Action {
 public:

 RemoveFrameAction(Animation *animation, std::unique_ptr<Frame> frame, int index) :
    animation(animation), frame(std::move(frame)), index(index) {}

    void undo() {
        animation->addFrameInternal(std::move(frame), index);
    }

    void redo() {
        frame.swap(animation->frames[index]);
        animation->removeFrameInternal(index);
    }

 private:
    Animation *animation;
    std::unique_ptr<Frame> frame;
    int index;
};

#endif // ANIMATION_H
