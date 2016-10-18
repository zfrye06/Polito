#include "action.h"

void Action::undo() {
}

void Action::redo() {
}

void ActionHandler::addAction( Action* a ) {
    undoStack.push( a );
}
void ActionHandler::undo() {
    if ( undoStack.empty() ) {
        return;
    }
    Action* a = undoStack.top();
    undoStack.pop();
    a->undo();
    emit update();
    redoStack.push( a );
}

void ActionHandler::redo() {
    if ( redoStack.empty() ) {
        return;
    }
    Action* a = redoStack.top();
    redoStack.pop();
    a->redo();
    emit update();
    undoStack.push( a );
}
