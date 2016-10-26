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
    buttonLayout = new QHBoxLayout(this);
    playbackButtons = new QButtonGroup(this);

    currentFrame = new QGraphicsView;
    playButton = new QPushButton;
    pauseButton = new QPushButton;
    nextFrame = new QPushButton;
    previousFrame = new QPushButton;

    //playButton->("");

    playButton->setCheckable(true);
    pauseButton->setCheckable(true);
    nextFrame->setCheckable(true);
    previousFrame->setCheckable(true);

    playButton->setIcon(playIcon);
    pauseButton->setIcon(pauseIcon);
    nextFrame->setIcon(nextIcon);
    previousFrame->setIcon(previousIcon);

//    playButton->setMaximumWidth(30);
//    pauseButton->setMaximumWidth(30);
//    nextFrame->setMaximumWidth(30);
//    previousFrame->setMaximumWidth(30);

//    QFont font;
//    font.setPointSize(14);
//    playButton->setFont(font);
//    pauseButton->setFont(font);
//    nextFrame->setFont(font);
//    previousFrame->setFont(font);

    playbackButtons->addButton(playButton);
    playbackButtons->addButton(pauseButton);
    playbackButtons->addButton(nextFrame);
    playbackButtons->addButton(previousFrame);
    playbackButtons->setExclusive(true);

    buttonLayout->addWidget(playButton);
    buttonLayout->addWidget(pauseButton);
    buttonLayout->addWidget(nextFrame);
    buttonLayout->addWidget(previousFrame);

    previewLayout->addWidget(currentFrame);
    previewLayout->addLayout(buttonLayout);
}

void PreviewArea::initConnections(){

}
