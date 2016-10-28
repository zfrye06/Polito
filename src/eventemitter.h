
#ifndef EVENT_EMITTER_H
#define EVENT_EMITTER_H

// Serves as an event bus for all actions from
// within a single animation and its components.
class AnimationEventEmitter : public QObject {
    Q_OBJECT

 signals:

    void drawEvent(DrawAction *);
    void addLayerEvent(AddLayerAction *);
    void moveLayerEvent(MoveLayerAction *);
    void removeLayerEvent(RemoveLayerAction *);

 public:
  
    void emitDrawEvent(DrawAction *action) { emit drawEvent(action); }
    void emitAddLayerEvent(AddLayerAction *action) { emit addLayerEvent(action); }
    void emitMoveLayerEvent(MoveLayerAction *action) { emit moveLayerEvent(action); }
    void emitRemoveLayerEvent(RemoveLayerAction *action) { emit removeLayerEvent(action); }
};

#endif // EVENT_EMITTER_H
