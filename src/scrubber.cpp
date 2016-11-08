#include "scrubber.h"
#include <QAbstractItemView>
#include <QListWidgetItem>
#include <QPushButton>
#include <QImage>
#include <vector>
#include <QLabel>
#include <QGraphicsView>
#include <QPalette>
#include <QVBoxLayout>
#include <QPixmap>

#include "frame.h"

Scrubber::Scrubber(QWidget *parent, vector<unique_ptr<Frame>> *frames) : QWidget(parent), frames(frames) {
    layout = new QHBoxLayout(this);
    buttons = new QVBoxLayout();

    addFrameButton = new QPushButton(addIcon, "");
    removeFrameButton = new QPushButton(deleteIcon, "");
    moveFrameLeft = new QPushButton(leftIcon, "");
    moveFrameRight = new QPushButton(rightIcon, "");

    addFrameButton->setToolTip("Add Frame");
    removeFrameButton->setToolTip("Remove Frame");
    moveFrameLeft->setToolTip("Move Selected Frame to the Left");
    moveFrameRight->setToolTip("Move Selected Frame to the Right");

    buttons->addWidget(addFrameButton);
    buttons->addWidget(removeFrameButton);
    buttons->addWidget(moveFrameLeft);
    buttons->addWidget(moveFrameRight);

    layout->addLayout(buttons);

    list = new QListWidget();
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    list->setFlow(QListView::LeftToRight);\
    list->setIconSize(QSize(100,100));
    list->setAlternatingRowColors(true);

    layout->addWidget(list);

    addFrameIcons();

    list->setCurrentRow(0);

    connect(list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(frameClicked(QListWidgetItem*)));
    connect(addFrameButton, &QPushButton::clicked, this, [this]{ emit addFrameClicked(); });
    connect(removeFrameButton, &QPushButton::clicked, this, [this]{ emit removeFrameClicked(); });
    connect(moveFrameLeft, &QPushButton::clicked, this, [this]{ emit moveFrameClicked(list->currentRow(), list->currentRow() - 1); });
    connect(moveFrameRight, &QPushButton::clicked, this, [this]{ emit moveFrameClicked(list->currentRow(), list->currentRow() + 1); });
}

void Scrubber::updateFrame(){
    QSize size(100, 100);
    QImage image = frames->at(list->currentRow())->image();
    QPixmap pixmap = QPixmap::fromImage(image);
    QIcon icon(pixmap.scaled(size));

    QListWidgetItem* item = list->currentItem();
    item->setIcon(icon);
}

void Scrubber::updateFrames(){
    for(int i = 0; i < (int)frames->size(); i++){
        QImage image = frames->at(i)->image();
        QPixmap px = QPixmap::fromImage(image);
        QIcon icon(px.scaled(QSize(100,100)));

        QListWidgetItem* item = list->item(i);
        item->setIcon(icon);
    }
}

int Scrubber::getCurrentListRow(){
    return list->currentRow();
}

vector<unique_ptr<Frame>>* Scrubber::getFrames(){
    return frames;
}

void Scrubber::frameClicked(QListWidgetItem *item) {
    emit frameIconClicked(list->currentRow());
}

void Scrubber::addFrame(int index) {
    QSize size(100,100);
    QImage image = frames->at(index)->image();
    QPixmap pixmap = QPixmap::fromImage(image);
    QIcon icon(pixmap.scaled(size));

    QListWidgetItem* item = new QListWidgetItem();
    item->setIcon(icon);
    item->setSizeHint(size);
    list->insertItem(index, item);
    item->setTextAlignment(Qt::AlignCenter);

}

void Scrubber::moveFrame(int from, int to) {
   auto item = list->takeItem(from);
   list->insertItem(to, item);
}

void Scrubber::removeFrame(int index) {
    auto item = list->takeItem(index);
    delete item;
}

void Scrubber::setActiveFrame(int index) {
    list->setCurrentRow(index);
}

void Scrubber::clear() {
    list->clear();
}

void Scrubber::setFrames(vector<unique_ptr<Frame>> *frames) {
    this->frames = frames;
    clear();
    addFrameIcons();
}

void Scrubber::addFrameIcons() {
    for(int i = 0; i < (int)frames->size(); i++){
        int row = list->currentRow() + 1;
        QSize size(100, 100);
        QImage image = frames->at(i)->image();
        QPixmap pixmap = QPixmap::fromImage(image);
        QIcon icon(pixmap.scaled(size));
        QListWidgetItem* item = new QListWidgetItem();
        item->setIcon(icon);
        item->setSizeHint(size);
        list->addItem(item);
        item->setTextAlignment(Qt::AlignCenter);
    }
}
