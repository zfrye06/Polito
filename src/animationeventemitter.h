
#ifndef EVENT_EMITTER_H
#define EVENT_EMITTER_H

#include <QObject>

class AddLayerAction;
class MoveLayerAction;
class RemoveLayerAction;

// Serves as an event bus for all actions from
// within a single animation and its components.
class AnimationEventEmitter : public QObject {
    Q_OBJECT

 signals:

    void addLayerEvent(AddLayerAction *);
    void moveLayerEvent(MoveLayerAction *);
    void removeLayerEvent(RemoveLayerAction *);

 public:
  
    void emitAddLayerEvent(AddLayerAction *action) { emit addLayerEvent(action); }
    void emitMoveLayerEvent(MoveLayerAction *action) { emit moveLayerEvent(action); }
    void emitRemoveLayerEvent(RemoveLayerAction *action) { emit removeLayerEvent(action); }
};

#endif // EVENT_EMITTER_H
