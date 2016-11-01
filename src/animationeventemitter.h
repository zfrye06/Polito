
#ifndef EVENT_EMITTER_H
#define EVENT_EMITTER_H

#include <QObject>

class AddFrameAction;
class MoveFrameAction;
class RemoveFrameAction;
class AddLayerAction;
class MoveLayerAction;
class RemoveLayerAction;
class ResizeAction;

// Serves as an event bus for all actions from
// within a single animation and its components.
class AnimationEventEmitter : public QObject {
    Q_OBJECT

 signals:

    void addFrameEvent(AddFrameAction *);
    void moveFrameEvent(MoveFrameAction *);
    void removeFrameEvent(RemoveFrameAction *);
    void addLayerEvent(AddLayerAction *);
    void moveLayerEvent(MoveLayerAction *);
    void removeLayerEvent(RemoveLayerAction *);
    void resizeEvent(ResizeAction *);

 public:
  
    void emitAddFrameEvent(AddFrameAction *action) { emit addFrameEvent(action); }
    void emitMoveFrameEvent(MoveFrameAction *action) { emit moveFrameEvent(action); }
    void emitRemoveFrameEvent(RemoveFrameAction *action) { emit removeFrameEvent(action); }
    void emitAddLayerEvent(AddLayerAction *action) { emit addLayerEvent(action); }
    void emitMoveLayerEvent(MoveLayerAction *action) { emit moveLayerEvent(action); }
    void emitRemoveLayerEvent(RemoveLayerAction *action) { emit removeLayerEvent(action); }
    void emiteResizeEvent(ResizeAction *action) { emit resizeEvent(action); }
};

#endif // EVENT_EMITTER_H
