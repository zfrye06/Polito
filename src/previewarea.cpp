#include <QButtonGroup>
#include <QPushButton>
#include <QLayout>
#include <QTimer>
#include <iostream>
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
    //timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(goToNextFrame()));
    connect(playButton, &QPushButton::released, this, &PreviewArea::playAnimation);
    connect(pauseButton, &QPushButton::released, this, &PreviewArea::pauseAnimation);
    connect(nextFrame, &QPushButton::released, this, &PreviewArea::goToNextFrame);
    connect(previousFrame, &QPushButton::released, this, &PreviewArea::goToPreviousFrame);

}

void PreviewArea::playAnimation(){
    if(!isPlaying){
        cout << "Begin Play..." << endl;
        isPlaying = true;

        //int duration = frames[currentFrameNumber]->duration();
        cout << currentFrameNumber << endl;
        QTimer::singleShot(200, this, SLOT(goToNextFrameIsPlaying()));
    }
    else{
        cout << "Already Playing..." << endl;
    }
}

void PreviewArea::pauseAnimation(){
    cout << "Pause Pressed..." << endl;
    isPlaying = false;
}

void PreviewArea::goToNextFrameIsPlaying(){
    if(isPlaying){
        if(currentFrameNumber == 6){
            currentFrameNumber = 0;
        }
        else{
            currentFrameNumber++;
        }
        cout << currentFrameNumber << endl;
        QTimer::singleShot(200, this, SLOT(goToNextFrameIsPlaying()));
    }
    else{
        cout << "Animation Stopped..." << endl;
    }
}

void PreviewArea::goToNextFrame(){
    if(isPlaying){
        isPlaying = false;
    }
    if(currentFrameNumber == 6){
        currentFrameNumber = 0;
    }
    else{
        currentFrameNumber++;
    }
    cout << currentFrameNumber << endl;
}

void PreviewArea::goToPreviousFrame(){
    if(isPlaying){
        isPlaying = false;
    }
    if(currentFrameNumber == 0){
        currentFrameNumber = 6;
    }
    else{
        currentFrameNumber--;
    }
    cout << currentFrameNumber << endl;
}

void PreviewArea::setFrames(vector<unique_ptr<Frame>> *frames) {
    this->frames = frames;
}
