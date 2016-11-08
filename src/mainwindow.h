
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
#include "drawarea.h"
#include "imagesizedialog.h"
#include "layermenu.h"
#include "previewarea.h"
#include "scrubber.h"
#include "toolbar.h"
#include "fpsdialog.h"
#include "keybindingdialog.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

    // This is added as a callback to undo/redo actions
    // when the effect of the action includes updating
    // global UI state.
    void updateDisplay();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void getFPS();
    void setFPS(int fps);
    void saveProject(bool extendedFormat);
    void saveGif();
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
    int currentFPS = 5;

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
    FPSDialog *fd;
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *optionMenu;
    QAction *saveAct;
    QAction *fpsAct;
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
    
    void initActions();
    void initSignals();
    void initWidgets();
    void synchronizeScrubber();
    void synchronizeLayerMenu();
    
};

#endif
