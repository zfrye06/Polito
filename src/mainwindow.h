
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QList>
#include <QMainWindow>
#include <vector>
#include <QWidget>
#include <QGridLayout>
#include <QSplitter>
#include <memory>
#include "action.h"
#include "animation.h"
#include "animationwidgets.h"
#include "drawarea.h"
#include "imagesizedialog.h"
#include "layermenu.h"
#include "previewarea.h"
#include "scrubber.h"
#include "toolbar.h"
#include "keybindingdialog.h"


class DrawArea;

class MainWindow : public QMainWindow, public UpdateableWidget {
    Q_OBJECT

public:
    MainWindow();

    // This is added as a callback to undo/redo actions
    // when the effect of the action includes updating
    // global UI state.
    void updateDisplay() override;

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void saveProject(bool extendedFormat);
//    void saveGif();
    void loadProject();
    void imageSize();
    void finishImageSize(int dimension);
    void bindings();
    void setColorBind(const QKeySequence&);
    void setEraserBind(const QKeySequence&);
    void setLineBind(const QKeySequence&);
    void addFrameBind(const QKeySequence&);
    void addLayerBind(const QKeySequence&);
    void frameRightBind(const QKeySequence&);
    void frameLeftBind(const QKeySequence&);
    void layerUpBind(const QKeySequence&);
    void layerDownBind(const QKeySequence&);
    void removeLayerBind(const QKeySequence&);
    void removeFrameBind(const QKeySequence&);
    void setBrushBind(const QKeySequence&);
    void setFillBind(const QKeySequence&);
    void setSelectBind(const QKeySequence&);
    void setCircleBind(const QKeySequence&);
    void setSquareBind(const QKeySequence&);

private:

    AnimationEventEmitter emitter;
    std::unique_ptr<Animation> animation;
    ActionHistory actionHistory;
    
    Toolbar *toolbar;
    DrawArea *drawArea;
    Scrubber *scrubber;
    PreviewArea *previewArea;
    LayerMenu *layerMenu;
    
    ImageSizeDialog *d;
    KeyBindingDialog *kd;
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *optionMenu;
    QAction *saveAct;
    QAction *saveExtendedAct;
    QAction *exportGifAct;
    QAction *loadAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *imageSizeAct;
    QAction *keyBindAct;
    QAction *exitAct;
    QAction *clearScreenAct;
    QAction *chooseColor;
    QAction *eraserAct;
    QAction *lineAct;
    QAction *addFrameAct;
    QAction *addLayerAct;
    QAction *frameRightAct;
    QAction *layerUpAct;
    QAction *removeFrameAct;
    QAction *removeLayerAct;
    QAction *brushAct;
    QAction *fillAct;
    QAction *selectAct;
    QAction *circleAct;
    QAction *squareAct;
    QAction *frameLeftAct;
    QAction *layerDownAct;
    QWidget *window;
    QVBoxLayout *layout;
    QSplitter *splitter;
    QSplitter *upperArea;
    QSplitter *lowerArea;
    int currentDimension;
    
    void initActions();
    void initSignals();
    void initWidgets();
    void synchronizeScrubber();
    void synchronizeLayerMenu();
    
};

#endif
