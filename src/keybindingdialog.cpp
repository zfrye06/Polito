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
    connect(ui->colorBind, &QKeySequenceEdit::keySequenceChanged, this, &KeyBindingDialog::colorChanged);
}

void KeyBindingDialog::initWidgets(){

}

void KeyBindingDialog::colorChanged(const QKeySequence &keySequence){
    emit colorChanged(keySequence);
}
