
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
#include "animation.h"
#include "drawarea.h"
#include "imagesizedialog.h"
#include "layermenu.h"
#include "previewarea.h"
#include "scrubber.h"
#include "toolbar.h"


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
    DrawArea *drawArea;
    Scrubber *scrubber;
    PreviewArea *previewArea;
    LayerMenu *layerMenu;
    
    ImageSizeDialog *d;
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
    void initSignals();
    void initWidgets();
};

#endif
