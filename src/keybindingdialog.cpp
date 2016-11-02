#include "keybindingdialog.h"
#include "ui_keybindingdialog.h"

KeyBindingDialog::KeyBindingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyBindingDialog)
{
    ui->setupUi(this);
    initConnections();
}

KeyBindingDialog::~KeyBindingDialog()
{
    delete ui;
}

void KeyBindingDialog::initConnections(){
//    connect(ui->colorBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::colorChanged);
//    connect(ui->eraserBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::eraserChanged);
//    connect(ui->lineBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::lineChanged);
//    connect(ui->addLayerBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::addLayerChanged);
//    connect(ui->addFrameBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::addFrameChanged);
//    connect(ui->nextFrameBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::nextFrameChanged);
//    connect(ui->nextLayerBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::nextLayerChanged);
//    connect(ui->deleteFrameBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::removeFrameChanged);
//    connect(ui->deleteLayerBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::removeLayerChanged);
//    connect(ui->brushBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::brushChanged);
//    connect(ui->fillBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::fillChanged);
//    connect(ui->selectBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::selectChanged);
//    connect(ui->circleBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::circleChanged);
//    connect(ui->squareBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::squareChanged);
//    connect(ui->previousFrameBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::previousFrameChanged);
//    connect(ui->previousLayerBind, &QKeySequenceEdit::editingFinished, this, &KeyBindingDialog::previousLayerChanged);
}

void KeyBindingDialog::initWidgets(){

}

//void KeyBindingDialog::colorChanged(){
//    emit colorSignal(ui->colorBind->keySequence());
//}

//void KeyBindingDialog::eraserChanged(){
//    emit eraserSignal(ui->eraserBind->keySequence());
//}

//void KeyBindingDialog::lineChanged(){
//    emit lineSignal(ui->lineBind->keySequence());
//}

//void KeyBindingDialog::addFrameChanged(){
//    emit addFrameSignal(ui->addFrameBind->keySequence());
//}

//void KeyBindingDialog::addLayerChanged(){
//    emit addLayerSignal(ui->addLayerBind->keySequence());
//}

//void KeyBindingDialog::nextFrameChanged(){
//    emit nextFrameSignal(ui->nextFrameBind->keySequence());
//}

//void KeyBindingDialog::nextLayerChanged(){
//    emit nextLayerSignal(ui->nextLayerBind->keySequence());
//}

//void KeyBindingDialog::removeFrameChanged(){
//    emit removeFrameSignal(ui->deleteFrameBind->keySequence());
//}

//void KeyBindingDialog::removeLayerChanged(){
//    emit removeLayerSignal(ui->deleteLayerBind->keySequence());
//}

//void KeyBindingDialog::brushChanged(){
//    emit brushSignal(ui->brushBind->keySequence());
//}

//void KeyBindingDialog::fillChanged(){
//    emit fillSignal(ui->fillBind->keySequence());
//}

//void KeyBindingDialog::selectChanged(){
//    emit selectSignal(ui->selectBind->keySequence());
//}

//void KeyBindingDialog::circleChanged(){
//    emit circleSignal(ui->circleBind->keySequence());
//}

//void KeyBindingDialog::previousLayerChanged(){
//    emit previousLayerSignal(ui->previousLayerBind->keySequence());
//}

//void KeyBindingDialog::previousFrameChanged(){
//    emit previousFrameSignal(ui->previousFrameBind->keySequence());
//}

//void KeyBindingDialog::squareChanged(){
//    emit squareSignal(ui->squareBind->keySequence());
//}
