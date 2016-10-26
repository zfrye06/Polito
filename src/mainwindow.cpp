
#include <QtWidgets>

#include "mainwindow.h"
#include "imagesizedialog.h"

MainWindow::MainWindow() : animation(emitter), drawArea(new QGraphicsView) {
    initActions();
    initWidgets();
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
        animation.activeFrame().clear();
    });

    connect(&emitter, &AnimationEventEmitter::drawEvent,
            &actionHistory, &ActionHistory::addAction);
}

void MainWindow::initWidgets() {
    window = new QWidget(this);
    layout = new QGridLayout(window);
    toolbar = new Toolbar(window);
    layerMenu = new LayerMenu(window);
    previewArea = new PreviewArea(window);

    drawArea->setScene(&animation.activeFrame().scene());

    layout->addWidget(toolbar, 0, 0);
    layout->addWidget(drawArea, 0, 1);
    layout->addWidget(layerMenu, 0, 2);
    layout->addWidget(previewArea, 1, 2);

    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,4);
    layout->setColumnStretch(2,0);

    layout->setRowStretch(0,4);
    layout->setRowStretch(1,0);

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
    resize(600, 600);
}
