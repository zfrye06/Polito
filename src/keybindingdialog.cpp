#include "keybindingdialog.h"
#include "ui_keybindingdialog.h"

KeyBindingDialog::KeyBindingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyBindingDialog)
{
    ui->setupUi(this);
}

KeyBindingDialog::~KeyBindingDialog()
{
    delete ui;
}
