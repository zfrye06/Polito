/**
 * @file action.cpp
 * @brief Handles undo/redo actions.
 * @author Dalton Nell
 * @version 0
 * @date 2016-10-18
 */

#include "action.h"

Action::~Action() {
}

ActionHistory::ActionHistory() {
  maxSize = 30;
}

ActionHistory::~ActionHistory() {
  for( auto a : redoStack ) {
    delete a;
  }
  for ( auto a : undoStack ) {
    delete a;
  }
}

/**
 * @brief Add a new action to the Undo stack, and clears the redo stack.
 *
 * @param action When ActionHandler::undo() is called, this action will
 *               be the one to have undo() called.
 */
void ActionHistory::addAction( Action* action ) {
  undoStack.push_back( action );
  // Since we added a new action, clear the redo stack.
  for( auto a : redoStack ) {
    delete a;
  }
  redoStack.clear();
  if ( undoStack.size() > maxSize ) {
    delete undoStack.front();
    // Delete the first element.
    undoStack.erase(undoStack.begin());
  }
}

/**
 * @brief Calls undo() on the last action added to the stack, and moves it to
 * the redo stack.
 */
void ActionHistory::undo() {
  if ( undoStack.empty() ) {
    return;
  }
  Action* a = undoStack.back();
  undoStack.pop_back();
  a->undo();
  emit update();
  redoStack.push_back( a );
}

/**
 * @brief Calls redo() on the action last added to the redo stack, and moves it
 * to the undo stack.
 */
void ActionHistory::redo() {
  if ( redoStack.empty() ) {
    return;
  }
  Action* a = redoStack.back();
  redoStack.pop_back();
  a->redo();
  emit update();
  undoStack.push_back( a );
}
