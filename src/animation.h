
#ifndef ANIMATION_H
#define ANIMATION_H

#include <istream>
#include <memory>
#include <ostream>
#include <vector>
#include "animationeventemitter.h"
#include "frame.h"

class Animation {
 public:

    // Constructs an animation with a single frame.
    Animation(AnimationEventEmitter &emitter);

    void addFrame();

    void addFrame(int index);

    void moveFrame(int fromIndex, int toIndex);

    void removeFrame(int index);

    void setActiveFrame(int index);

    Frame* activeFrame();

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

    std::vector<std::unique_ptr<Frame>> frames;
    int activeFrameIndex;
    AnimationEventEmitter &emitter;
};

#endif // ANIMATION_H
