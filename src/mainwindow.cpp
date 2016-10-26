
#include <QtWidgets>

#include "mainwindow.h"
#include "imagesizedialog.h"

MainWindow::MainWindow() : animation(&emitter), drawArea(new QGraphicsView) {

    window = new QWidget(this);
    layout = new QGridLayout(window);
    toolbar = new Toolbar(window);
    layout->addWidget(toolbar, 0, 0);

    drawArea->setScene(&animation.activeFrame().scene());
//    setCentralWidget(drawArea);
    layout->addWidget(drawArea, 0, 1);
    window->setLayout(layout);
    this->setCentralWidget(window);
    createActions();
    createMenus();

    setWindowTitle(tr("Polito"));
    resize(500, 500);
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

void MainWindow::createActions() {
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

void MainWindow::createMenus() {
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
}
