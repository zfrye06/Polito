
#include "animation.h"

Animation::Animation(AnimationEventEmitter &emitter) : emitter(emitter) {
    setActiveFrame(0);
    addFrame();
}

void Animation::addFrame() {
    addFrame(frames.size());
}

void Animation::addFrame(int index) {
    std::unique_ptr<Frame> f(new Frame(emitter));
    frames.insert(frames.begin() + index, std::move(f));
    //if (activeFrameIndex == index) activeFrameIndex++;
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

Frame* Animation::activeFrame() {
    return frames[activeFrameIndex].get();
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

std::vector<std::unique_ptr<Frame>>& Animation::getFrames(){
    return frames;
}
