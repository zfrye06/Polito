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

signals:
//    colorSignal(const QKeySequence&);
//    eraserSignal(const QKeySequence&);
//    lineSignal(const QKeySequence&);
//    addFrameSignal(const QKeySequence&);
//    addLayerSignal(const QKeySequence&);
//    nextFrameSignal(const QKeySequence&);
//    nextLayerSignal(const QKeySequence&);
//    removeFrameSignal(const QKeySequence&);
//    removeLayerSignal(const QKeySequence&);
//    brushSignal(const QKeySequence&);
//    fillSignal(const QKeySequence&);
//    selectSignal(const QKeySequence&);
//    circleSignal(const QKeySequence&);
//    squareSignal(const QKeySequence&);
//    previousFrameSignal(const QKeySequence&);
//    previousLayerSignal(const QKeySequence&);

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
//    void colorChanged();
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
