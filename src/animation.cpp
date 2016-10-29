
#include "animation.h"

Animation::Animation(AnimationEventEmitter &emitter) : activeFrameIndex(-1), emitter(emitter) {
    addFrame();
    activeFrameIndex = 0;
}

void Animation::addFrame() {
    addFrame(frames.size());
}

void Animation::addFrame(int index) {
    if (index < 0 || index > frames.size()) {
        throw std::invalid_argument("Index out of bounds.");
    }
    std::unique_ptr<Frame> f(new Frame(emitter));
    addFrameInternal(std::move(f), index);
    emitter.emitAddFrameEvent(new AddFrameAction(this, index));
}

void Animation::addFrameInternal(std::unique_ptr<Frame> f, int index) {
    frames.insert(frames.begin() + index, std::move(f));
    if (activeFrameIndex >= index){
        activeFrameIndex++;  
    } 
}

void Animation::moveFrame(int fromIndex, int toIndex) {
    if (fromIndex < 0 || fromIndex >= (int)frames.size() ||
        toIndex < 0 || toIndex >= (int)frames.size()) {
        throw std::invalid_argument("Index out of bounds.");
    }
    moveFrame(fromIndex, toIndex);
    emitter.emitMoveFrameEvent(new MoveFrameAction(this, fromIndex, toIndex));
}

void Animation::moveFrameInternal(int fromIndex, int toIndex) {
    auto frame = std::move(frames[fromIndex]);
    frames.erase(frames.begin() + fromIndex);
    frames.insert(frames.begin() + toIndex, std::move(frame));
    if (activeFrameIndex == fromIndex) {
        activeFrameIndex = toIndex;
    } else if (fromIndex < toIndex &&
               activeFrameIndex > fromIndex &&
               activeFrameIndex <= toIndex){
        activeFrameIndex--;
    } else if (fromIndex > toIndex &&
               activeFrameIndex >= toIndex &&
               activeFrameIndex < fromIndex) {
        activeFrameIndex++;
    }
}

void Animation::removeFrame(int index) {
    if (frames.size() <= 1) {
        throw std::invalid_argument("An animation must have at least one frame.");
    }
    if (index < 0 || index >= (int)frames.size()) {
        throw std::invalid_argument("Index out of bounds.");
    }
    auto frame = std::move(frames[index]);
    frames.erase(frames.begin() + index);
    emitter.emitRemoveFrameEvent(new RemoveFrameAction(this, std::move(frame), index));
}

void Animation::removeFrameInternal(int index) {
    frames.erase(frames.begin() + index);
    if (index < activeFrameIndex ||
        (index == activeFrameIndex &&
         activeFrameIndex == (int)frames.size())) {
        activeFrameIndex--;
    }    
}

void Animation::setActiveFrame(int index) {
    if (index < 0 || index >= (int)frames.size()) {
        throw std::invalid_argument("Index out of bounds.");
    }
    activeFrameIndex = index;
}

Frame &Animation::activeFrame() {
    return *frames[activeFrameIndex];
}

void Animation::resize(int dim) {

}

int Animation::numframes() const {
    return frames.size();
}

void Animation::save(std::ostream& out) const {
    out << "TODO" << std::endl;
}

void Animation::saveExtendedFormat(std::ostream& out) const {
    out << "TODO" << std::endl;
}

void Animation::saveGif(std::ostream& out) const {
    out << "TODO" << std::endl;
}

void Animation::load(std::istream& in) {

}

std::vector<std::unique_ptr<Frame>>& Animation::getFrames(){
    return frames;
}
