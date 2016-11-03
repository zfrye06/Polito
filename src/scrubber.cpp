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
//    list->setDragEnabled(true);
//    list->setDragDropMode(QAbstractItemView::InternalMove);
//    list->setDefaultDropAction(Qt::MoveAction);
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
    connect(moveFrameLeft, &QPushButton::clicked, this, [this]{ emit moveFrameClicked(list->currentRow(), list->currentRow() - 1); });
    connect(moveFrameRight, &QPushButton::clicked, this, [this]{ emit moveFrameClicked(list->currentRow(), list->currentRow() + 1); });
}

void Scrubber::frameClicked(QListWidgetItem *item) {
    emit frameIconClicked(list->currentRow());
}

void Scrubber::addFrame(int index) {
    int row = list->currentRow() + 1;
    QListWidgetItem* item = new QListWidgetItem("Frame");
    list->insertItem(row, item);
}

void Scrubber::moveFrame(int from, int to) {
   auto item = list->takeItem(from);
   list->insertItem(to, item);
}

void Scrubber::removeFrame(int index) {
    list->takeItem(index);
}

void Scrubber::setActiveFrame(int index) {
    list->setCurrentRow(index);
}

void Scrubber::clear() {
    list->clear();
}

void Scrubber::setFrames(vector<unique_ptr<Frame>> *frames) {
    this->frames = frames;
}
