
#include <QtWidgets>
#include <iostream>
#include <fstream>

#include "mainwindow.h"
#include "imagesizedialog.h"

MainWindow::MainWindow() :
    animation(std::unique_ptr<Animation>(new Animation(emitter))) {
    initWidgets();
    initActions();
    initSignals();

    previewArea->setPreview();
}

void MainWindow::saveProject(bool extendedFormat) {
    try {
        QString fileName = QFileDialog::getSaveFileName(this);
        ofstream out(fileName.toStdString());
        if (extendedFormat) {
            animation->saveExtendedFormat(out);
        } else {
            animation->save(out);
        }
        out.close();
    } catch (const std::exception &ex) {
        QString msg = "Unable to save project: ";
        msg += ex.what();
        std::cerr << msg.toStdString() << std::endl;
        QMessageBox::information(this, tr("Polito"), msg);
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
            previewArea->setFrames(&toLoad->getFrames());
            animation.swap(toLoad);
            synchronizeScrubber();
            synchronizeLayerMenu();
        } catch (const std::exception &ex) {
            QString msg = "Unable to load project: ";
            msg += ex.what();
            std::cerr << msg.toStdString() << std::endl;
            QMessageBox::information(this, tr("Polito"), msg);
        }
    }
}



void MainWindow::closeEvent(QCloseEvent *event) {
    event->accept();
}

void MainWindow::imageSize() {
    int width = drawArea->width();
    int height = drawArea->height();
    // TODO: This leaks. Not deleted until the main window is.
    ImageSizeDialog* d = new ImageSizeDialog(this, width, height);
    d->activateWindow();
    d->showNormal();
    d->setVisible(true);
    connect(d,&ImageSizeDialog::done,this,&MainWindow::finishImageSize);
}

void MainWindow::bindings(){
    kd->activateWindow();
    kd->showNormal();
    kd->setVisible(true);
}

void MainWindow::setColorBind(const QKeySequence &keySequence){
    chooseColor->setShortcut(keySequence);void setEraserBind(const QKeySequence&);
}

void MainWindow::setEraserBind(const QKeySequence &keySequence){
    eraserAct->setShortcut(keySequence);
}

void MainWindow::setLineBind(const QKeySequence& keySequence){
    lineAct->setShortcut(keySequence);
}
void MainWindow::addFrameBind(const QKeySequence& keySequence){
    addFrameAct->setShortcut(keySequence);
}

void MainWindow::addLayerBind(const QKeySequence& keySequence){
    addLayerAct->setShortcut(keySequence);
}

void MainWindow::frameRightBind(const QKeySequence& keySequence){
    frameRightAct->setShortcut(keySequence);
}

void MainWindow::frameLeftBind(const QKeySequence& keySequence){
    frameLeftAct->setShortcut(keySequence);
}

void MainWindow::layerUpBind(const QKeySequence& keySequence){
    layerUpAct->setShortcut(keySequence);
}

void MainWindow::layerDownBind(const QKeySequence& keySequence){
    layerDownAct->setShortcut(keySequence);
}

void MainWindow::removeLayerBind(const QKeySequence& keySequence){
    removeLayerAct->setShortcut(keySequence);
}

void MainWindow::removeFrameBind(const QKeySequence& keySequence){
    removeFrameAct->setShortcut(keySequence);
}

void MainWindow::setBrushBind(const QKeySequence &keySequence){
    brushAct->setShortcut(keySequence);
}

void MainWindow::setFillBind(const QKeySequence& keySequence){
    fillAct->setShortcut(keySequence);
}

void MainWindow::setSelectBind(const QKeySequence& keySequence){
    selectAct->setShortcut(keySequence);
}

void MainWindow::setCircleBind(const QKeySequence& keySequence){
    circleAct->setShortcut(keySequence);
}

void MainWindow::setSquareBind(const QKeySequence& keySequence){
    squareAct->setShortcut(keySequence);
}

void MainWindow::finishImageSize(int w, int h) {
    animation->resize(w);
}

void MainWindow::synchronizeScrubber() {
    scrubber->clear();
    for (int i = 0; i < animation->numframes(); i++) {
        scrubber->addFrame(i);
    }
    scrubber->setActiveFrame(animation->activeFrameIdx());
}

void MainWindow::synchronizeLayerMenu() {
    layerMenu->clear();
    for (int i = 0; i < animation->activeFrame().numlayers(); i++) {
        layerMenu->addLayer(i);
    }
    layerMenu->setActiveLayer(animation->activeFrame().activeLayerIdx());
}

void MainWindow::updateDisplay() {
    synchronizeScrubber();
    synchronizeLayerMenu();
    drawArea->setFrame(&animation->activeFrame());
}

void MainWindow::initActions() {
    saveAct = new QAction(tr("Save Project"), this);
    connect(saveAct, &QAction::triggered, this, [this] { this->saveProject(false); });

    saveExtendedAct = new QAction(tr("Save Project (Extended Format)"), this);
    connect(saveExtendedAct, &QAction::triggered, this, [this] { this->saveProject(true); });

    loadAct = new QAction(tr("Load Project"), this);
    connect(loadAct, &QAction::triggered, this, &MainWindow::loadProject);

    imageSizeAct = new QAction(tr("&Image Size..."), this);
    connect(imageSizeAct, SIGNAL(triggered()), this, SLOT(imageSize()));

    keyBindAct = new QAction(tr("&Set Key Bindings"), this);
    connect(keyBindAct, &QAction::triggered, this, &MainWindow::bindings);

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

    chooseColor = new QAction(tr("&Choose Color"), this);
    chooseColor->setShortcut(tr("Ctrl+P"));
    connect(chooseColor, &QAction::triggered, toolbar, &Toolbar::getColor);

    eraserAct = new QAction(tr("&Select Eraser Tool"), this);
    eraserAct->setShortcut(tr("Ctrl+E"));
    connect(eraserAct, &QAction::triggered, toolbar, &Toolbar::setEraser);

    lineAct = new QAction(tr("&Select Line Tool"), this);
    lineAct->setShortcut(tr("Ctrl+I"));
    connect(lineAct, &QAction::triggered, toolbar, &Toolbar::setLine);

    addFrameAct = new QAction(tr("&Add Frame"), this);
    addFrameAct->setShortcut(tr("Ctrl+T"));
    connect(addFrameAct, &QAction::triggered, this, [this]{emit scrubber->addFrameClicked();});

    addLayerAct = new QAction(tr("&Add Layer"), this);
    addLayerAct->setShortcut(tr("Ctrl+A"));
    connect(addLayerAct, &QAction::triggered, this, [this]{emit layerMenu->addLayerButtonClicked();});

    frameRightAct = new QAction(tr("&Move Current Frame Right"), this);
    frameRightAct->setShortcut(tr("Ctrl+N"));
    connect(frameRightAct, &QAction::triggered, this, [this]{emit this->scrubber->moveFrameClicked(scrubber->getCurrentListRow(), scrubber->getCurrentListRow() + 1);});

    frameLeftAct = new QAction(tr("&Move Current Frame Left"), this);
    frameLeftAct->setShortcut(tr("Ctrl+G"));
    connect(frameLeftAct, &QAction::triggered, this, [this]{emit this->scrubber->moveFrameClicked(scrubber->getCurrentListRow(), scrubber->getCurrentListRow() - 1);});

    layerUpAct = new QAction(tr("&Move Current Layer Up"), this);
    layerUpAct->setShortcut(tr("Ctrl+H"));
//    connect(layerUpAct, &QAction::triggered, this, [this]{emit layerMenu->moveLayerUpButtonClicked();});

    layerDownAct = new QAction(tr("&Move Current Layer Down"), this);
    layerDownAct->setShortcut(tr("Ctrl+D"));
//    connect(layerDownAct, &QAction::triggered, this, [this]{emit layerMenu->moveLayerDownButtonClicked();});

    removeFrameAct = new QAction(tr("&Delete Current Frame"), this);
    removeFrameAct->setShortcut(tr("Ctrl+J"));
    connect(removeFrameAct, &QAction::triggered, this, [this]{emit scrubber->removeFrameClicked();});

    removeLayerAct = new QAction(tr("&Delete Current Layer"), this);
    removeLayerAct->setShortcut(tr("Ctrl+K"));
    connect(removeLayerAct, &QAction::triggered, this, [this]{emit layerMenu->deleteLayerButtonClicked();});

    brushAct = new QAction(tr("&Select Brush Tool"), this);
    brushAct->setShortcut(tr("Ctrl+B"));
    connect(brushAct, &QAction::triggered, toolbar, &Toolbar::setBrush);

    fillAct = new QAction(tr("&Select Fill Tool"), this);
    fillAct->setShortcut(tr("Ctrl+F"));
    connect(fillAct, &QAction::triggered, toolbar, &Toolbar::setFill);

    selectAct = new QAction(tr("&Select Pan Tool"), this);
    selectAct->setShortcut(tr("Ctrl+M"));
//    connect(selectAct, &QAction::triggered, this, &Toolbar::);

    circleAct = new QAction(tr("&Select Circle Tool"), this);
    circleAct->setShortcut(tr("Ctrl+R"));
    connect(circleAct, &QAction::triggered, toolbar, &Toolbar::setCircle);

    squareAct = new QAction(tr("&Select Square Tool"), this);
    squareAct->setShortcut(tr("Ctrl+S"));
    connect(squareAct, &QAction::triggered, toolbar, &Toolbar::setSquare);

    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveExtendedAct);
    fileMenu->addAction(loadAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(imageSizeAct);
    editMenu->addAction(chooseColor);
    editMenu->addAction(eraserAct);
    editMenu->addAction(lineAct);
    editMenu->addAction(addFrameAct);
    editMenu->addAction(addLayerAct);
    editMenu->addAction(frameRightAct);
    editMenu->addAction(layerUpAct);
    editMenu->addAction(layerDownAct);
    editMenu->addAction(frameLeftAct);
    editMenu->addAction(removeFrameAct);
    editMenu->addAction(removeLayerAct);
    editMenu->addAction(brushAct);
    editMenu->addAction(fillAct);
//    editMenu->addAction(selectAct);
    editMenu->addAction(circleAct);
    editMenu->addAction(squareAct);

    optionMenu->addAction(clearScreenAct);
    optionMenu->addAction(keyBindAct);
}

void MainWindow::initWidgets() {
    window = new QWidget(this);
    layout = new QVBoxLayout(window);
    splitter = new QSplitter(window);
    upperArea = new QSplitter(window);
    lowerArea = new QSplitter(window);
    toolbar = new Toolbar(window);
    drawArea = new DrawArea(&animation->activeFrame());
    scrubber = new Scrubber(window, &animation->getFrames());
    previewArea = new PreviewArea(window, &animation->getFrames());
    layerMenu = new LayerMenu(window);
    kd = new KeyBindingDialog;

    drawArea->setFrame(&animation->activeFrame());

    layout->addWidget(splitter);

    splitter->setOrientation(Qt::Vertical);

    splitter->addWidget(upperArea);
    splitter->addWidget(lowerArea);

    splitter->setStretchFactor(0,10);
    splitter->setStretchFactor(1,2);

    toolbar->setMaximumWidth(50);
    layerMenu->setMaximumWidth(200);

    upperArea->addWidget(toolbar);
    upperArea->addWidget(drawArea);
    upperArea->addWidget(layerMenu);

    upperArea->setStretchFactor(0,0);
    upperArea->setStretchFactor(1,20);
    upperArea->setStretchFactor(2,0);

    lowerArea->addWidget(scrubber);
    lowerArea->addWidget(previewArea);

    lowerArea->setStretchFactor(0, 5);
    lowerArea->setStretchFactor(1, 1);

    fileMenu = new QMenu(tr("&File"), this);
    editMenu = new QMenu(tr("&Edit"), this);
    optionMenu = new QMenu(tr("&Options"), this);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(optionMenu);

    this->setCentralWidget(window);

    setWindowTitle(tr("Polito"));
    resize(755, 665);
}

void MainWindow::initSignals() {

    connect(drawArea, &DrawArea::updatePreview, previewArea, &PreviewArea::updatePreview);

    connect(drawArea, &DrawArea::addAction,
            &actionHistory, &ActionHistory::addAction);

    connect(&emitter, &AnimationEventEmitter::addFrameEvent,
            this, [this](AddFrameAction *a){
                a->setWidgetToUpdate(this);
                actionHistory.addAction(a);
            });

    connect(&emitter, &AnimationEventEmitter::moveFrameEvent,
            this, [this](MoveFrameAction *a){
                a->setWidgetToUpdate(this);
                actionHistory.addAction(a);
            });

    connect(&emitter, &AnimationEventEmitter::removeFrameEvent,
            this, [this](RemoveFrameAction *a){
                a->setWidgetToUpdate(this);
                actionHistory.addAction(a);
            });

    connect(&emitter, &AnimationEventEmitter::addLayerEvent,
            this, [this](AddLayerAction *a){
                a->setFrameWidget(layerMenu);
                actionHistory.addAction(a);
            });

    connect(&emitter, &AnimationEventEmitter::moveLayerEvent,
            this, [this](MoveLayerAction *a){
                a->setFrameWidget(layerMenu);
                actionHistory.addAction(a);
            });

    connect(&emitter, &AnimationEventEmitter::removeLayerEvent,
            this, [this](RemoveLayerAction *a){
                a->setFrameWidget(layerMenu);
                actionHistory.addAction(a);
            });

    connect(&emitter, &AnimationEventEmitter::resizeEvent,
            this, [this](ResizeAction *action){
                action->setWidgetToUpdate(drawArea);
                actionHistory.addAction(action);
            });

    connect(toolbar, &Toolbar::colorChanged,
            this, [this](QColor to){
                drawArea->paintHandler().settings.color = to;
            });

    connect(scrubber, &Scrubber::addFrameClicked,
            this, [this] {
                int insertIndex = animation->activeFrameIdx() + 1;
                animation->addFrame(insertIndex);
                scrubber->addFrame(insertIndex);
            });

    connect(scrubber, &Scrubber::moveFrameClicked,
            this, [this](int from, int to) {
                if (from >= 0 && from < animation->numframes() &&
                    to >= 0 && to < animation->numframes()) {
                    animation->moveFrame(from, to);
                    scrubber->moveFrame(from, to);
                    scrubber->setActiveFrame(animation->activeFrameIdx());
                    synchronizeLayerMenu();
                    drawArea->setFrame(&animation->activeFrame());
                }
            });

    connect(scrubber, &Scrubber::removeFrameClicked,
            this, [this]() {
                if (animation->numframes() <= 1) return;
                int removeIndex = animation->activeFrameIdx();
                
                // TODO: We have a bit of a hacky situation here.  Between when
                // we call Animation::removeFrame() and DrawArea::setFrame() the
                // emitted RemoveFrameAction's ownership of the removed frame is
                // the only thing keeping the removed frame from being deleted,
                // which would then leave the drawArea with a deleted frame as
                // its scene for a few milliseconds.  I set the drawArea's frame
                // to an arbitrarily created frame during that timeframe to
                // avoid the bug. Note that this is NOT exception safe.
                std::unique_ptr<Frame> f(new Frame(emitter, animation->dimension()));
                drawArea->setFrame(f.get());
                animation->removeFrame(removeIndex);
                scrubber->removeFrame(removeIndex);
                scrubber->setActiveFrame(animation->activeFrameIdx());
                synchronizeLayerMenu();
                drawArea->setFrame(&animation->activeFrame());
            });

    connect(scrubber, &Scrubber::frameIconClicked,
            this, [this](int index) {
                animation->setActiveFrame(index);
                scrubber->setActiveFrame(index);
                synchronizeLayerMenu();
                drawArea->setFrame(&animation->activeFrame());
            });

    connect(layerMenu, &LayerMenu::layerAddedSignal,
            this, [this](int index) {
                Frame &frame = animation->activeFrame();
                frame.addLayer(index);
                layerMenu->addLayer(index);
                layerMenu->setActiveLayer(frame.activeLayerIdx());
            });

    connect(layerMenu, &LayerMenu::layersSwappedSignal,
            this, [this](int from, int to) {
                if (from >= 0 && from < animation->activeFrame().numlayers() &&
                    to >= 0 && to < animation->activeFrame().numlayers()) {

                    Frame &frame = animation->activeFrame();
                    frame.moveLayer(from, to);
                    layerMenu->moveLayer(from, to);
                    layerMenu->setActiveLayer(frame.activeLayerIdx());
                }
            });

    connect(layerMenu, &LayerMenu::layerDeletedSignal,
            this, [this](int index) {
                if (animation->activeFrame().numlayers() <= 1) return;
                Frame &frame = animation->activeFrame();
                frame.removeLayer(index);
                layerMenu->removeLayer(index);
                layerMenu->setActiveLayer(frame.activeLayerIdx());
            });

    connect(layerMenu, &LayerMenu::activeLayerChangedSignal,
            this, [this](int to) {
                animation->activeFrame().setActiveLayer(to);
                layerMenu->setActiveLayer(to);
            });

    connect(toolbar,&Toolbar::setPaintHandler, drawArea, &DrawArea::setPaintHandler);

    connect(kd, &KeyBindingDialog::colorSignal, this, &MainWindow::setColorBind);
    connect(kd, &KeyBindingDialog::eraserSignal, this, &MainWindow::setEraserBind);
    connect(kd, &KeyBindingDialog::lineSignal, this, &MainWindow::setLineBind);
    connect(kd, &KeyBindingDialog::addFrameSignal, this, &MainWindow::addFrameBind);
    connect(kd, &KeyBindingDialog::addLayerSignal, this, &MainWindow::addLayerBind);
    connect(kd, &KeyBindingDialog::frameRightSignal, this, &MainWindow::frameRightBind);
    connect(kd, &KeyBindingDialog::frameLeftSignal, this, &MainWindow::frameLeftBind);
    connect(kd, &KeyBindingDialog::layerUpSignal, this, &MainWindow::layerUpBind);
    connect(kd, &KeyBindingDialog::layerDownSignal, this, &MainWindow::layerDownBind);
    connect(kd, &KeyBindingDialog::removeFrameSignal, this, &MainWindow::removeFrameBind);
    connect(kd, &KeyBindingDialog::removeLayerSignal, this, &MainWindow::removeLayerBind);
    connect(kd, &KeyBindingDialog::brushSignal, this, &MainWindow::setBrushBind);
    connect(kd, &KeyBindingDialog::fillSignal, this, &MainWindow::setFillBind);
    connect(kd, &KeyBindingDialog::selectSignal, this, &MainWindow::setSelectBind);
    connect(kd, &KeyBindingDialog::circleSignal, this, &MainWindow::setCircleBind);
    connect(kd, &KeyBindingDialog::squareSignal, this, &MainWindow::setSquareBind);
}

