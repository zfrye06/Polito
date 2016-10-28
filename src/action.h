/**
 * @file action.h
 * @brief Keeps track of actions to be undone/redone.
 * @author Unescaped Characters
 * @version 0
 * @date 2016-10-18
 */

#ifndef _POLITO_ACTION_H_
#define _POLITO_ACTION_H_

#include <QObject>
#include <vector>

/**
 * @brief The base class that is derived from by actions to undo/redo what they've done.
 * In order to specify a new action, you must derive this class and imagine it as a state saver/loader.
 * On creation it should save the state of the app (or the necessary part of it), and then load it
 * when you call "undo()". To implement redo would be the same concept.
 * In order to add an action to the undo stack, you must use emit and connect to the ActionHandler.
 * Look at ScribbleAction and ScribbleArea for an implementation example.
 */
class Action {
public:

    /**
     * @brief This may be unused on your actions, but when they are deconstructed
     * they may need to release some memory.
     */
    virtual ~Action();

    /**
     * @brief This should load the state saved before the action completed.
     */
    virtual void undo() = 0;

    /**
     * @brief This should load the state saved after the action completed, there may
     * be extra implemented functions to help with this.
     * DrawAction::finish()).
     */
    virtual void redo() = 0;
};

/**
 * @brief Handles two stacks of actions, the undo stack and the redo stack.
 * It has slots to cause an undo or redo, and a signal that's sent to cause
 * the app to update its visuals. The signal can probably be ignored in some cases.
 */
class ActionHistory : public QObject {
    Q_OBJECT
private:
    unsigned int maxSize;
    std::vector<Action*> undoStack;
    std::vector<Action*> redoStack;
public:
    ActionHistory();
    ~ActionHistory();

signals:
    void update();

public slots:
    void undo();
    void redo();
    void addAction( Action* a );
};

#endif
