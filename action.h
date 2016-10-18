#ifndef _POLITO_STACK_H_
#define _POLITO_STACK_H_

#include <QObject>
#include <stack>

class Action {
public:
    virtual void undo();
    virtual void redo();
};

class ActionHandler : public QObject {
    Q_OBJECT
private:
    std::stack<Action*> undoStack;
    std::stack<Action*> redoStack;
public:

signals:
    void update();

public slots:
    void undo();
    void redo();
    void addAction( Action* a );
};

#endif
