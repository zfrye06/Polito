
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

// Represents an animation consisting of one or more frames,
// where exactly one frame is active at all times. Frames' positions
// are zero-indexed from first to last.
class Animation {
    friend class AddFrameAction;
    friend class MoveFrameAction;
    friend class RemoveFrameAction;
    friend class ResizeAction;
 public:

    // Specifies the default width and height, in pixels.
    static const int DEFAULT_DIMENSION = 64;

    // Constructs an animation with a single frame.
    Animation(AnimationEventEmitter &emitter);

    // Adds a frame to the animation.
    void addFrame(int index);

    // Moves a frame from fromIndex to toIndex.
    // The same frame which was active prior the move
    // remains active after the move.
    void moveFrame(int fromIndex, int toIndex);

    // Removes a frame from the animation. The active
    // frame remains at the same index, 
    void removeFrame(int index);

    // Sets the active frame to that at the given index.
    void setActiveFrame(int index);

    // Returns the active frame index.
    int activeFrameIdx() const;

    // Returns the active frame. 
    Frame &activeFrame();

    // Resizes every frame in this animation to the given dimension
    void resize(int dim);

    // Returns the dimension of this animation.
    int dimension() const;

    // Returns the number of frames in this animation.
    int numframes() const;

    // Saves this animation to the given output stream.
    void save(std::ostream&) const;

    // Saves this animation in extended format, which maintains
    // duration and layer information.
    void saveExtendedFormat(std::ostream&) const;

    // Saves this animation as a GIF file.
    void saveGif(std::string filename) const;

    // Loads this animation from the given input stream, where
    // the bytes of the stream may represent an animation saved
    // with either Animation::save or Animation::saveExtendedFormat.
    void load(std::istream&);

    // Returns the frames of this animation.
    std::vector<std::unique_ptr<Frame>>& getFrames();

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
    animation(animation), index(index) {}

    void undo() {
        frame.swap(animation->frames.at(index));
        animation->removeFrameInternal(index);
    }

    void redo() {
        animation->addFrameInternal(std::move(frame), index);
    }

 private:
    Animation *animation;
    std::unique_ptr<Frame> frame;
    int index;
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
        frame.swap(animation->frames.at(index));
        animation->removeFrameInternal(index);
    }

 private:
    Animation *animation;
    std::unique_ptr<Frame> frame;
    int index;
};

class ResizeAction : public Action {
public:

    ResizeAction(Animation *animation, std::vector<std::unique_ptr<Frame>> &frames) :
        animation(animation) {
        for(int i = 0; i < (int)frames.size(); i++){
            Frame &frame = *frames.at(i);
            pastLayers.push_back(std::vector<std::shared_ptr<QPixmap>>());
            for(auto layer : frame.getLayers()){
                pastLayers.at(i).push_back(layer->image);
            }
        }
    }

    void swapLayers() {
        std::vector<std::unique_ptr<Frame>> &frames = animation->getFrames();
        for (int i = 0; i < (int)frames.size(); i++) {
            std::vector<Layer *> &layers = frames.at(i)->getLayers();
            for (int j = 0; j < (int)layers.size(); j++) {
                std::shared_ptr<QPixmap> temp = layers.at(j)->image;
                layers.at(j)->image = pastLayers.at(i).at(j);
                pastLayers.at(i)[j] = temp;
            }
        }
    }

    void undo() {
        swapLayers();
    }

    void redo() {
        swapLayers();
    }

private:
   Animation *animation;
   std::vector<std::vector<std::shared_ptr<QPixmap>>> pastLayers;
};

#endif // ANIMATION_H
