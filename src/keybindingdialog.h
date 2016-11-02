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

private slots:

private:
    Ui::KeyBindingDialog *ui;

    QKeySequence colorKey;
    QKeySequence eraserKey;
    QKeySequence lineKey;
    QKeySequence addFrameKey;
    QKeySequence addLayerKey;
    QKeySequence nextFrameKey;
    QKeySequence nextLayerKey;
    QKeySequence removeFrameKey;
    QKeySequence removeLayerKey;
    QKeySequence brushKey;
    QKeySequence fillKey;
    QKeySequence selectKey;
    QKeySequence circleKey;
    QKeySequence squareKey;
    QKeySequence previousFrameKey;
    QKeySequence previousLayerKey;

    void initWidgets();
    void initConnections();

public:
    void colorChanged(const QKeySequence &keySequence);
//    void eraserChanged();
//    void lineChanged();
//    void addFrameChanged();
//    void addLayerChanged();
//    void nextFrameChanged();
//    void nextLayerChanged();
//    void removeFrameChanged();
//    void removeLayerChanged();
//    void brushChanged();
//    void fillChanged();
//    void selectChanged();
//    void circleChanged();
//    void squareChanged();
//    void previousFrameChanged();
//    void previousLayerChanged();

};

#endif // KEYBINDINGDIALOG_H
