#ifndef KEYBINDINGDIALOG_H
#define KEYBINDINGDIALOG_H

#include <QDialog>

namespace Ui {
class KeyBindingDialog;
}

class KeyBindingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeyBindingDialog(QWidget *parent = 0);
    ~KeyBindingDialog();

private:
    Ui::KeyBindingDialog *ui;
};

#endif // KEYBINDINGDIALOG_H
