#include <QButtonGroup>
#include <QPushButton>
#include <QLayout>
#include <QTimer>
#include <memory>
#include <QRectF>
#include <QtGlobal>
#include <QSize>
#include <QIntValidator>
#include "previewarea.h"

using namespace std;

PreviewArea::PreviewArea(QWidget *parent, std::vector<std::unique_ptr<Frame>> *publicFrames) :
    QWidget(parent), frames(publicFrames){
    initWidgets();
    initConnections();
}

void PreviewArea::initWidgets(){
    previewLayout = new QVBoxLayout(this);
    buttonLayout = new QHBoxLayout();
    playbackButtons = new QButtonGroup(this);

    currentFrame = new QGraphicsView();
    playButton = new QPushButton();
    pauseButton = new QPushButton();
    nextFrame = new QPushButton();
    previousFrame = new QPushButton();

    playButton->setToolTip("Play");
    pauseButton->setToolTip("Pause");
    nextFrame->setToolTip("Next Frame");
    previousFrame->setToolTip("Previous Frame");

    duration = new QTextEdit();
    QSize size(80, 25);
    duration->setMaximumSize(size);
    duration->setMinimumSize(size);
    duration->setToolTip("Frame Duration in ms");

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
    buttonLayout->addWidget(duration);

    previewLayout->addWidget(currentFrame);
    previewLayout->addLayout(buttonLayout);
}

void PreviewArea::initConnections(){
    connect(playButton, &QPushButton::released, this, &PreviewArea::playAnimation);
    connect(pauseButton, &QPushButton::released, this, &PreviewArea::pauseAnimation);
    connect(nextFrame, &QPushButton::released, this, &PreviewArea::goToNextFrame);
    connect(previousFrame, &QPushButton::released, this, &PreviewArea::goToPreviousFrame);
    connect(duration, &QTextEdit::textChanged, this, &PreviewArea::updateDuration);

}

void PreviewArea::setDuration(int ms){
    duration->setText(QString::number(ms));
}

void PreviewArea::updateDuration(){
    QString text = duration->toPlainText();
    QIntValidator validator;
    for(int i = 0; i < text.length(); i++){
        QString temp(text.at(i));
        if(QValidator::Acceptable != validator.validate(temp, i)){
            text = text.remove(i, 1);
            i--;
        }
    }

    if(duration->toPlainText() != text){
        duration->setPlainText(text);
    }
    frames->at(currentFrameNumber)->setDuration(text.toInt());
}

void PreviewArea::setPreview(){
    QRectF rect(previewLayout->itemAt(0)->geometry());
    int frameDuration = frames->at(currentFrameNumber)->duration();
    duration->setPlainText(QString::number(frameDuration));
    QGraphicsScene* scene= &frames->at(currentFrameNumber)->scene();
    currentFrame->setScene(scene);
}

void PreviewArea::updatePreview(){
    currentFrame->viewport()->update();
}

void PreviewArea::updateScale(){
    currentFrame->scale(1/width, 1/height);
    QGraphicsScene* scene= &frames->at(currentFrameNumber)->scene();
    QRectF rect(previewLayout->itemAt(0)->geometry());
    if(rect.width() < rect.height()){
        width = (rect.width() / scene->width()) - .2;
        height = width;
    }
    else{
        height = (rect.height() / scene->height()) - .2;
        width = height;
    }

    currentFrame->scale(width, height);
}

void PreviewArea::resizeEvent(QResizeEvent *event){
    currentFrame->scale(1/width, 1/height);
    QGraphicsScene* scene= &frames->at(currentFrameNumber)->scene();
    QRectF rect(previewLayout->itemAt(0)->geometry());
    if(rect.width() < rect.height()){
        width = (rect.width() / scene->width()) - .2;
        height = width;
    }
    else{
        height = (rect.height() / scene->height()) - .2;
        width = height;
    }

    currentFrame->scale(width, height);
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
        if(currentFrameNumber >= ((int)frames->size() - 1)){
            currentFrameNumber = 0;
        }
        else{
            currentFrameNumber++;
        }
        currentFrame->setScene(&frames->at(currentFrameNumber)->scene());
        int frameDuration = frames->at(currentFrameNumber)->duration();
        duration->setPlainText(QString::number(frameDuration));
        QTimer::singleShot(frameDuration, this, SLOT(goToNextFrameIsPlaying()));
    }
}

void PreviewArea::goToNextFrame(){
    if(isPlaying){
        isPlaying = false;
    }
    if(currentFrameNumber >= ((int)frames->size() - 1)){
        currentFrameNumber = 0;
    }
    else{
        currentFrameNumber++;
    }
    int frameDuration = frames->at(currentFrameNumber)->duration();
    duration->setPlainText(QString::number(frameDuration));
    currentFrame->setScene(&frames->at(currentFrameNumber)->scene());
}

void PreviewArea::goToPreviousFrame(){
    if(isPlaying){
        isPlaying = false;
    }
    if(currentFrameNumber <= 0){
        currentFrameNumber = frames->size() - 1;
    }
    else{
        currentFrameNumber--;
    }
    int frameDuration = frames->at(currentFrameNumber)->duration();
    duration->setPlainText(QString::number(frameDuration));
    currentFrame->setScene(&frames->at(currentFrameNumber)->scene());
}

void PreviewArea::setFrames(vector<unique_ptr<Frame>> *frames) {
    this->frames = frames;
}
