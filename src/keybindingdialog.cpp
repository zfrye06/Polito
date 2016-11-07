#include "keybindingdialog.h"
#include "ui_keybindingdialog.h"

KeyBindingDialog::KeyBindingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyBindingDialog)
{
    ui->setupUi(this);
    initConnections();
    initWidgets();
}

KeyBindingDialog::~KeyBindingDialog()
{
    delete ui;
}

void KeyBindingDialog::initConnections(){
    connect(ui->colorBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::colorChanged);
    connect(ui->eraserBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::eraserChanged);
    connect(ui->lineBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::lineChanged);
    connect(ui->addLayerBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::addLayerChanged);
    connect(ui->addFrameBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::addFrameChanged);
    connect(ui->nextFrameBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::frameRightChanged);
    connect(ui->nextLayerBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::layerUpChanged);
    connect(ui->deleteFrameBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::removeFrameChanged);
    connect(ui->deleteLayerBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::removeLayerChanged);
    connect(ui->brushBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::brushChanged);
    connect(ui->fillBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::fillChanged);
    connect(ui->selectBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::selectChanged);
    connect(ui->circleBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::circleChanged);
    connect(ui->squareBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::squareChanged);
    connect(ui->previousFrameBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::frameLeftChanged);
    connect(ui->previousLayerBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::layerDownChanged);
}

void KeyBindingDialog::initWidgets(){
    ui->colorBind->setKeySequence(QKeySequence("P"));
    ui->eraserBind->setKeySequence(QKeySequence("E"));
    ui->lineBind->setKeySequence(QKeySequence("I"));
    ui->addFrameBind->setKeySequence(QKeySequence("Ctrl+T"));
    ui->addLayerBind->setKeySequence(QKeySequence("Ctrl+A"));
    ui->nextFrameBind->setKeySequence(QKeySequence("Ctrl+N"));
    ui->previousFrameBind->setKeySequence(QKeySequence("Ctrl+G"));
    ui->nextLayerBind->setKeySequence(QKeySequence("Ctrl+H"));
    ui->previousLayerBind->setKeySequence(QKeySequence("Ctrl+D"));
    ui->deleteFrameBind->setKeySequence(QKeySequence("Ctrl+J"));
    ui->deleteLayerBind->setKeySequence(QKeySequence("Ctrl+K"));
    ui->brushBind->setKeySequence(QKeySequence("B"));
    ui->fillBind->setKeySequence(QKeySequence("F"));
    ui->selectBind->setKeySequence(QKeySequence("M"));
    ui->circleBind->setKeySequence(QKeySequence("R"));
    ui->squareBind->setKeySequence(QKeySequence("S"));
}

void KeyBindingDialog::colorChanged(){
    emit colorSignal(ui->colorBind->keySequence());
}

void KeyBindingDialog::eraserChanged(){
    emit eraserSignal(ui->eraserBind->keySequence());
}

void KeyBindingDialog::lineChanged(){
    emit lineSignal(ui->lineBind->keySequence());
}

void KeyBindingDialog::addFrameChanged(){
    emit addFrameSignal(ui->addFrameBind->keySequence());
}

void KeyBindingDialog::addLayerChanged(){
    emit addLayerSignal(ui->addLayerBind->keySequence());
}

void KeyBindingDialog::frameRightChanged(){
    emit frameRightSignal(ui->nextFrameBind->keySequence());
}

void KeyBindingDialog::layerUpChanged(){
    emit layerUpSignal(ui->nextLayerBind->keySequence());
}

void KeyBindingDialog::removeFrameChanged(){
    emit removeFrameSignal(ui->deleteFrameBind->keySequence());
}

void KeyBindingDialog::removeLayerChanged(){
    emit removeLayerSignal(ui->deleteLayerBind->keySequence());
}

void KeyBindingDialog::brushChanged(){
    emit brushSignal(ui->brushBind->keySequence());
}

void KeyBindingDialog::fillChanged(){
    emit fillSignal(ui->fillBind->keySequence());
}

void KeyBindingDialog::selectChanged(){
    emit selectSignal(ui->selectBind->keySequence());
}

void KeyBindingDialog::circleChanged(){
    emit circleSignal(ui->circleBind->keySequence());
}

void KeyBindingDialog::layerDownChanged(){
    emit layerDownSignal(ui->previousLayerBind->keySequence());
}

void KeyBindingDialog::frameLeftChanged(){
    emit frameLeftSignal(ui->previousFrameBind->keySequence());
}

void KeyBindingDialog::squareChanged(){
    emit squareSignal(ui->squareBind->keySequence());
}
