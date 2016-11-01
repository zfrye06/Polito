
#include "animation.h"

Animation::Animation(AnimationEventEmitter &emitter) :
    activeFrameIndex(-1),  dim(Animation::DEFAULT_DIMENSION), emitter(emitter) {
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
    std::unique_ptr<Frame> f(new Frame(emitter, dim));
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
    out << dim << " " << dim << std::endl; // height and width
    out << numframes() << std::endl;
    for (auto& frame : frames) {
        QImage image = frame->image();
        for (int row = 0; row < image.height(); row++) {
            for (int col = 0; col < image.width(); col++) {
                QColor color = image.pixelColor(row, col);
                out << color.red() << " " <<
                       color.green() << " " <<
                       color.blue() << " " <<
                       color.alpha();
                if (col != image.width() - 1) {
                    out << " ";
                }
            }
            out << std::endl;
        }
    }
}

void Animation::saveExtendedFormat(std::ostream& out) const {
    out << "TODO" << std::endl;
}

void Animation::saveGif(std::ostream& out) const {
}

void Animation::load(std::istream& in) {
    int width, height, numFrames;
    in >> width >> height >> numFrames;
    if (in.fail() || width != height || numFrames == 0) {
        throw std::runtime_error(
                    "Unable to load: file contained misformatted width, height, nframes header.");
    }
    std::vector<std::unique_ptr<Frame>> tempFrames;
    for (int i = 0; i < numFrames; i++) {
        QImage image(width, height, QImage::Format_RGBA8888);
        image.fill(Qt::transparent);
        for (int row = 0; row < image.height(); row++) {
            for (int col = 0; col < image.width(); col++) {
                int red, green, blue, alpha;
                in >> red >> green >> blue >> alpha;
                if (in.fail()) {
                    throw std::runtime_error(
                                "Unable to load: file contained misformatted or mis-sized frame section.");
                }
                QColor color(red, green, blue, alpha);
                image.setPixelColor(row, col, color);
            }
        }
        std::unique_ptr<Frame> frame(new Frame(emitter, image));
        tempFrames.push_back(std::move(frame));
    }
    dim = height;
    activeFrameIndex = 0;
    frames.clear();
    for (int i = 0; i < tempFrames.size(); i++) {
        frames.push_back(std::move(tempFrames.at(i)));
    }
}

std::vector<std::unique_ptr<Frame>>& Animation::getFrames(){
    return frames;
}
