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
    connect(addFrameButton, &QPushButton::clicked, this, [this]{ emit addFrameClicked(); });
    connect(removeFrameButton, &QPushButton::clicked, this, [this]{ emit removeFrameClicked(); });
}

void Scrubber::addFrame(int index) {
    int row = list->currentRow() + 1;
    QListWidgetItem* item = new QListWidgetItem("Frame");
    list->insertItem(row, item);
}

void Scrubber::moveFrame(int from, int to) {
    
}

void Scrubber::removeFrame(int index) {
    list->takeItem(index);
}

void Scrubber::setActiveFrame(int index) {
    //list->
}

void Scrubber::clear() {

}

void Scrubber::frameClicked(QListWidgetItem *item){
    emit setActiveFrameClicked(list->currentRow());
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
