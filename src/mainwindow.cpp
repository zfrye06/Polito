
#include <QtWidgets>

#include "mainwindow.h"
#include "imagesizedialog.h"

MainWindow::MainWindow() : animation(emitter), drawArea(new DrawArea(animation.activeFrame())) {
    initActions();
    initWidgets();
    initSignals();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    event->accept();
}

void MainWindow::imageSize() {
    int width = drawArea->width();
    int height = drawArea->height();
    ImageSizeDialog* d = new ImageSizeDialog(this, width, height);
    d->activateWindow();
    d->showNormal();
    d->setVisible(true);
    connect(d,&ImageSizeDialog::done,this,&MainWindow::finishImageSize);
}

void MainWindow::finishImageSize(int w, int h) {
//    ScribbleAction* a = new ScribbleAction(scribbleArea);
//    scribbleArea->resizeImage(w,h);
//    a->finish();
//    actionHistory.addAction(a);
}

void MainWindow::initActions() {
    imageSizeAct = new QAction(tr("&Image Size..."), this);
    connect(imageSizeAct, SIGNAL(triggered()), this, SLOT(imageSize()));

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    connect(undoAct, &QAction::triggered, &actionHistory, &ActionHistory::undo);

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    connect(redoAct, &QAction::triggered, &actionHistory, &ActionHistory::redo);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, &QAction::triggered,
            this, [this] {
        animation.activeFrame()->clear();
    });

}

void MainWindow::initWidgets() {
    window = new QWidget(this);
    layout = new QVBoxLayout(window);
    splitter = new QSplitter(window);
    upperArea = new QSplitter(window);
    lowerArea = new QSplitter(window);
    toolbar = new Toolbar(window);
    layerMenu = new LayerMenu(window);
    previewArea = new PreviewArea(window, animation.getFrames());

    drawArea->setScene(&animation.activeFrame()->scene());

    connect(toolbar,&Toolbar::setPaintHandler, drawArea, &DrawArea::setPaintHandler);

    layout->addWidget(splitter);

    splitter->setOrientation(Qt::Vertical);

    splitter->addWidget(upperArea);
    splitter->addWidget(lowerArea);

    splitter->setStretchFactor(0,10);
    splitter->setStretchFactor(1,2);

    toolbar->setMaximumWidth(50);
    layerMenu->setMaximumWidth(200);

    upperArea->setStretchFactor(0,0);
    upperArea->setStretchFactor(1,20);
    upperArea->setStretchFactor(2,0);

    upperArea->addWidget(toolbar);
    upperArea->addWidget(drawArea);
    upperArea->addWidget(layerMenu);

    lowerArea->addWidget(previewArea);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = new QMenu(tr("&Edit"), this);
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(imageSizeAct);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(clearScreenAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(optionMenu);

    this->setCentralWidget(window);

    setWindowTitle(tr("Polito"));
    resize(755, 665);
}

void MainWindow::initSignals() {
    connect(drawArea, &DrawArea::addAction,
            &actionHistory, &ActionHistory::addAction);

    connect(toolbar, &Toolbar::colorChanged,
            this, [this](QColor to){
                drawArea->paintHandler().settings.color = to;
    });

    connect(layerMenu, &LayerMenu::layerAddedSignal,
            this, [this](int index) {
                Frame *frame = animation.activeFrame();
                if (index > 0 && index <= frame->numlayers()) {
                    frame->addLayer(index);
                }
    });

    connect(layerMenu, &LayerMenu::layersSwappedSignal,
            this, [this](int from, int to) {
                Frame *frame = animation.activeFrame();
                if (from > 0 && from < frame->numlayers() &&
                    to > 0 && to < frame->numlayers()) {
                    frame->moveLayer(from, to);
                }
    });

    connect(layerMenu, &LayerMenu::layerDeletedSignal,
            this, [this](int index) {
                Frame *frame = animation.activeFrame();
                if (index > 0 && index <= frame->numlayers() && frame->numlayers() > 0) {
                    frame->removeLayer(index);
                }
     });

    connect(layerMenu, &LayerMenu::activeLayerChangedSignal,
            this, [this](int to) {
                Frame *frame = animation.activeFrame();
                if (to > 0 && to < frame->numlayers()) {
                    frame->setActiveLayer(to);
                }
    });
}
