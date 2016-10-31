
#ifndef FRAME_WIDGETS_H
#define FRAME_WIDGETS_H

// Contains interfaces used by actions to undo and redo
// events in the UI.

class AnimationWidget {
 public:
    virtual void addFrame(int index) = 0;
    virtual void moveFrame(int from, int to) = 0;
    virtual void removeFrame(int index) = 0;
    virtual void setActiveFrame(int index) = 0;
};

class FrameWidget {
 public:
    virtual void addLayer(int index) = 0;
    virtual void moveLayer(int from, int to) = 0;
    virtual void removeLayer(int index) = 0;
    virtual void setActiveLayer(int index) = 0;
};

#endif // FRAME_WIDGETS_H
