
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QList>
#include <QMainWindow>
#include <vector>
#include <QWidget>
#include <QGridLayout>
#include <QSplitter>
#include "action.h"
#include "drawarea.h"
#include "animation.h"
#include "imagesizedialog.h"
#include "toolbar.h"
#include "layermenu.h"
#include "previewarea.h"

class DrawArea;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void imageSize();
    void finishImageSize(int w, int h);

private:

    AnimationEventEmitter emitter;
    Animation animation;
    ActionHistory actionHistory;
    Toolbar *toolbar;
    PreviewArea *previewArea;

    DrawArea *drawArea;
    ImageSizeDialog *d;
    LayerMenu *layerMenu;
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *optionMenu;
    QAction *undoAct;
    QAction *redoAct;
    QAction *imageSizeAct;
    QAction *exitAct;
    QAction *clearScreenAct;
    QWidget *window;
    QVBoxLayout *layout;
    QSplitter *splitter;
    QSplitter *upperArea;
    QSplitter *lowerArea;
    
    void initActions();
    void initWidgets();
};

#endif
