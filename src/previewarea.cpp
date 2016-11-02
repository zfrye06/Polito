#include <QButtonGroup>
#include <QPushButton>
#include <QLayout>
#include <QTimer>
#include <iostream>
#include <memory>
#include <QRectF>
#include "previewarea.h"

using namespace std;

PreviewArea::PreviewArea(QWidget *parent, std::vector<std::unique_ptr<Frame>> *publicFrames) :
    QWidget(parent), frames(publicFrames){
    initWidgets();
    initConnections();
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

    playButton->setCheckable(true);
    pauseButton->setCheckable(true);
    nextFrame->setCheckable(true);
    previousFrame->setCheckable(true);

    playButton->setIcon(playIcon);
    pauseButton->setIcon(pauseIcon);
    nextFrame->setIcon(nextIcon);
    previousFrame->setIcon(previousIcon);

    playbackButtons->addButton(playButton);
    playbackButtons->addButton(pauseButton);
    playbackButtons->addButton(nextFrame);
    playbackButtons->addButton(previousFrame);
    playbackButtons->setExclusive(true);

    buttonLayout->addWidget(playButton);
    buttonLayout->addWidget(pauseButton);
    buttonLayout->addWidget(previousFrame);
    buttonLayout->addWidget(nextFrame);

    previewLayout->addWidget(currentFrame);
    previewLayout->addLayout(buttonLayout);
}

void PreviewArea::initConnections(){
    connect(playButton, &QPushButton::released, this, &PreviewArea::playAnimation);
    connect(pauseButton, &QPushButton::released, this, &PreviewArea::pauseAnimation);
    connect(nextFrame, &QPushButton::released, this, &PreviewArea::goToNextFrame);
    connect(previousFrame, &QPushButton::released, this, &PreviewArea::goToPreviousFrame);

}

void PreviewArea::setPreview(){
    QRectF rect(previewLayout->itemAt(0)->geometry());
    QGraphicsScene* scene= &frames->at(currentFrameNumber)->scene();
    currentFrame->setScene(scene);
    currentFrame->scale(rect.width() / scene->width(), rect.height() / scene->height());
}

void PreviewArea::updatePreview(){
    currentFrame->viewport()->update();
}

void PreviewArea::playAnimation(){
    if(!isPlaying){
        isPlaying = true;
        int duration = frames->at(currentFrameNumber)->duration();
        QTimer::singleShot(duration, this, SLOT(goToNextFrameIsPlaying()));
    }
}

void PreviewArea::pauseAnimation(){
    isPlaying = false;
}

void PreviewArea::goToNextFrameIsPlaying(){
    if(isPlaying){
        if(currentFrameNumber == (frames->size() - 1)){
            currentFrameNumber = 0;
        }
        else{
            currentFrameNumber++;
        }
        currentFrame->setScene(&frames->at(currentFrameNumber)->scene());
        QTimer::singleShot(200, this, SLOT(goToNextFrameIsPlaying()));
    }
}

void PreviewArea::goToNextFrame(){
    if(isPlaying){
        isPlaying = false;
    }
    if(currentFrameNumber == (frames->size() - 1)){
        currentFrameNumber = 0;
    }
    else{
        currentFrameNumber++;
    }
    currentFrame->setScene(&frames->at(currentFrameNumber)->scene());
}

void PreviewArea::goToPreviousFrame(){
    if(isPlaying){
        isPlaying = false;
    }
    if(currentFrameNumber == 0){
        currentFrameNumber = frames->size() - 1;
    }
    else{
        currentFrameNumber--;
    }
    currentFrame->setScene(&frames->at(currentFrameNumber)->scene());
}

void PreviewArea::setFrames(vector<unique_ptr<Frame>> *frames) {
    this->frames = frames;
}
