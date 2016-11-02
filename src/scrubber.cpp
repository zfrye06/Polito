#include "scrubber.h"
#include <QListWidgetItem>
#include <QPushButton>
#include <QAbstractItemView>
#include <iostream>
#include <vector>
#include <QImage>
#include "frame.h"

Scrubber::Scrubber(QWidget *parent, vector<unique_ptr<Frame>> *frames) : QWidget(parent) {

    this->frames = frames;

    layout = new QHBoxLayout(this);
    buttons = new QVBoxLayout();

    addFrameButton = new QPushButton("Add Frame");
    removeFrameButton = new QPushButton("Remove Frame");
    moveFrameLeft = new QPushButton("Move Left");
    moveFrameRight = new QPushButton("Move Right");

    buttons->addWidget(addFrameButton);
    buttons->addWidget(removeFrameButton);
    buttons->addWidget(moveFrameLeft);
    buttons->addWidget(moveFrameRight);

    layout->addLayout(buttons);

    list = new QListWidget();
    list->setDragEnabled(true);
    list->setDragDropMode(QAbstractItemView::InternalMove);
    list->setDefaultDropAction(Qt::MoveAction);
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    list->setFlow(QListView::LeftToRight);

    layout->addWidget(list);

    for(int i = 0; i < frames->size(); i++){
        int row = list->currentRow() + 1;
        QListWidgetItem* item = new QListWidgetItem("Frame");
        list->insertItem(row, item);
    }

    connect(list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(frameClicked(QListWidgetItem*)));
    connect(addFrameButton, &QPushButton::clicked, this, &Scrubber::addFrame);
    connect(removeFrameButton, &QPushButton::clicked, this, &Scrubber::removeFrame);
}

void Scrubber::addFrame(int index) {
    int row = list->currentRow() + 1;
    QListWidgetItem* item = new QListWidgetItem("Frame");
    list->insertItem(row, item);

    emit frameAdded(row);


//    emit activeFrameChanged(index);
}

void Scrubber::moveFrame(int from, int to) {
    
}

void Scrubber::removeFrame(int index) {
    if(list->count() > 1){
        emit frameRemoved(list->currentRow());
        list->takeItem(list->currentRow());
    }
}

void Scrubber::setActiveFrame(int index) {
    //list->
}

void Scrubber::clear() {

}

void Scrubber::frameClicked(QListWidgetItem *item){
    emit activeFrameChanged(list->currentRow());
}

void Scrubber::reordered(QDropEvent* event){
    std::cout<<"reordered"<<std::endl;
}

void Scrubber::dropEvent(QDropEvent *event){
    event->accept();
    std::cout<<"reordered"<<std::endl;
}

void Scrubber::setFrames(vector<unique_ptr<Frame>> *frames) {
    this->frames = frames;
}
