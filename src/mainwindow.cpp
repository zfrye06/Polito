
#include <QtWidgets>
#include <iostream>
#include <fstream>

#include "mainwindow.h"
#include "imagesizedialog.h"

MainWindow::MainWindow() :
    animation(std::unique_ptr<Animation>(new Animation(emitter))) {
    initActions();
    initWidgets();
    initSignals();
}

void MainWindow::saveProject() {
    try {
        QString fileName = QFileDialog::getSaveFileName(this);
        ofstream out(fileName.toStdString());
        animation->save(out);
        out.close();
    } catch (const std::exception &ex) {
        std::cerr << "Unable to save project: " << ex.what() << std::endl;
    }
}

void MainWindow::loadProject() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::FileMode::ExistingFile);
    if (dialog.exec()) {
        QStringList file = dialog.selectedFiles();
        if (file.size() != 1) return;
        try {
            ifstream in(file.front().toStdString());
            std::unique_ptr<Animation> toLoad(new Animation(emitter));
            toLoad->load(in);
            actionHistory.clear();
            drawArea->setFrame(&toLoad->activeFrame());
            drawArea->setScene(&toLoad->activeFrame().scene());
            previewArea->setFrames(&toLoad->getFrames());
            scrubber->clear();
            for (int i = 0; i < animation->numframes(); i++) {
               scrubber->addFrame(i);
            }
            scrubber->setActiveFrame(animation->activeFrameIdx());
            layerMenu->clear();
            Frame &activeFrame = animation->activeFrame();
            for (int i = 0; i < activeFrame.numlayers(); i++) {
                layerMenu->addLayer(i);
            }
            layerMenu->setActiveLayer(activeFrame.activeLayerIdx());
            animation.swap(toLoad);
        } catch (const std::exception &ex) {
            std::cerr << "Unable to load project: " << ex.what() << std::endl;
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    event->accept();
}

void MainWindow::imageSize() {
    int width = drawArea->width();
    int height = drawArea->height();
    // TOOD: This leaks. Not deleted until the main window is.
    ImageSizeDialog* d = new ImageSizeDialog(this, width, height);
    d->activateWindow();
    d->showNormal();
    d->setVisible(true);
    connect(d,&ImageSizeDialog::done,this,&MainWindow::finishImageSize);
}

void MainWindow::finishImageSize(int w, int h) {
    animation->resize(w);
}

void MainWindow::initActions() {
    saveAct = new QAction(tr("Save Project"), this);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveProject);

    loadAct = new QAction(tr("Load Project"), this);
    connect(loadAct, &QAction::triggered, this, &MainWindow::loadProject);

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
        animation->activeFrame().clear();
    });

}

void MainWindow::initWidgets() {
    window = new QWidget(this);
    layout = new QVBoxLayout(window);
    splitter = new QSplitter(window);
    upperArea = new QSplitter(window);
    lowerArea = new QSplitter(window);
    toolbar = new Toolbar(window);
    drawArea = new DrawArea(&animation->activeFrame());
    scrubber = new Scrubber(window);
    previewArea = new PreviewArea(window, &animation->getFrames());
    layerMenu = new LayerMenu(window);

    drawArea->setScene(&animation->activeFrame().scene());

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

    lowerArea->addWidget(scrubber);
    lowerArea->addWidget(previewArea);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(loadAct);
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

    connect(&emitter, &AnimationEventEmitter::addFrameEvent,
            this, [this](AddFrameAction *a){
                a->setAnimationWidget(scrubber);
                actionHistory.addAction(a);
    });

    connect(&emitter, &AnimationEventEmitter::moveFrameEvent,
            this, [this](MoveFrameAction *a){
                a->setAnimationWidget(scrubber);
                actionHistory.addAction(a);
    });

    connect(&emitter, &AnimationEventEmitter::removeFrameEvent,
            this, [this](RemoveFrameAction *a){
                a->setAnimationWidget(scrubber);
                actionHistory.addAction(a);
    });

    connect(&emitter, &AnimationEventEmitter::addLayerEvent,
            &actionHistory, &ActionHistory::addAction);

    connect(&emitter, &AnimationEventEmitter::moveLayerEvent,
            &actionHistory, &ActionHistory::addAction);

    connect(&emitter, &AnimationEventEmitter::removeLayerEvent,
            &actionHistory, &ActionHistory::addAction);

    connect(&emitter, &AnimationEventEmitter::resizeEvent,
            this, [this](ResizeAction *action){
                action->setWidgetToUpdate(drawArea);
                actionHistory.addAction(action);
            });

    connect(toolbar, &Toolbar::colorChanged,
            this, [this](QColor to){
                drawArea->paintHandler().settings.color = to;
    });

    connect(scrubber, &Scrubber::frameAdded,
            this, [this](int index) {
                animation->addFrame(index);
    });

    connect(scrubber, &Scrubber::frameMoved,
            this, [this](int from, int to) {
                animation->moveFrame(from, to);
    });

    connect(scrubber, &Scrubber::frameRemoved,
            this, [this](int index) {
                animation->removeFrame(index);
    });

    connect(layerMenu, &LayerMenu::layerAddedSignal,
            this, [this](int index) {
                animation->activeFrame().addLayer(index);
    });

    connect(layerMenu, &LayerMenu::layersSwappedSignal,
            this, [this](int from, int to) {
                animation->activeFrame().moveLayer(from, to);
    });

    connect(layerMenu, &LayerMenu::layerDeletedSignal,
            this, [this](int index) {
                animation->activeFrame().removeLayer(index);
     });

    connect(layerMenu, &LayerMenu::activeLayerChangedSignal,
            this, [this](int to) {
                animation->activeFrame().setActiveLayer(to);
    });

}
