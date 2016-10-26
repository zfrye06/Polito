#include <QButtonGroup>
#include <QPushButton>
#include <QLayout>
#include "previewarea.h"

PreviewArea::PreviewArea(QWidget *parent) : QWidget(parent) {
    initWidgets();
    initConnections();
    setParent(parent);

}

void PreviewArea::initWidgets(){
    previewLayout = new QVBoxLayout(this);
    playbackButtons = new QButtonGroup(this);

    currentFrame = new QGraphicsView;
    playButton = new QPushButton;
    pauseButton = new QPushButton;
    nextFrame = new QPushButton;
    previousFrame = new QPushButton;

    playButton->setCheckable(true);
    pauseButton->setCheckable(true);
    nextFrame->setCheckable(true);
    previousFrame->setCheckable(true);

    playbackButtons->addButton(playButton);
    playbackButtons->addButton(pauseButton);
    playbackButtons->addButton(nextFrame);
    playbackButtons->addButton(previousFrame);
    playbackButtons->setExclusive(true);

    previewLayout->addWidget(playButton);
    previewLayout->addWidget(pauseButton);
    previewLayout->addWidget(nextFrame);
    previewLayout->addWidget(previousFrame);
}

void PreviewArea::initConnections(){

}
