#include "scrubber.h"
#include <QListWidgetItem>
#include <QPushButton>
#include <QAbstractItemView>
#include <iostream>
#include <vector>

Scrubber::Scrubber(QWidget *parent) : QWidget(parent) {

    layout = new QVBoxLayout(this);
    list = new QListWidget();
    list->setDragEnabled(true);
    list->setDragDropMode(QAbstractItemView::InternalMove);
    list->setDefaultDropAction(Qt::MoveAction);
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    list->setFlow(QListView::LeftToRight);
    layout->addWidget(list);

    connect(list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(frameClicked(QListWidgetItem*)));

    addFrame(0);
    addFrame(1);
    addFrame(2);
    addFrame(3);
    addFrame(4);
    addFrame(5);
    addFrame(6);
    addFrame(7);
    addFrame(8);
    addFrame(9);
    addFrame(10);
    addFrame(11);
    addFrame(12);
    addFrame(13);
    addFrame(0);
    addFrame(1);
    addFrame(2);
    addFrame(3);
    addFrame(4);
    addFrame(5);
    addFrame(6);
    addFrame(7);
    addFrame(8);
    addFrame(9);
    addFrame(10);
    addFrame(11);
    addFrame(12);
    addFrame(13);
    addFrame(0);
    addFrame(1);
    addFrame(2);
    addFrame(3);
    addFrame(4);
    addFrame(5);
    addFrame(6);
    addFrame(7);
    addFrame(8);
    addFrame(9);
    addFrame(10);
    addFrame(11);
    addFrame(12);
    addFrame(13);
    addFrame(0);
    addFrame(1);
    addFrame(2);
    addFrame(3);
    addFrame(4);
    addFrame(5);
    addFrame(6);
    addFrame(7);
    addFrame(8);
    addFrame(9);
    addFrame(10);
    addFrame(11);
    addFrame(12);
    addFrame(13);
    addFrame(0);
    addFrame(1);
    addFrame(2);
    addFrame(3);
    addFrame(4);
    addFrame(5);
    addFrame(6);
    addFrame(7);
    addFrame(8);
    addFrame(9);
    addFrame(10);
    addFrame(11);
    addFrame(12);
    addFrame(13);

}

void Scrubber::addFrame(int index) {
    QListWidgetItem* item = new QListWidgetItem(QString::number(index));
    list->insertItem(list->currentRow() + 1, item);
}

void Scrubber::moveFrame(int from, int to) {
    
}

void Scrubber::removeFrame(int index) {
    
}

void Scrubber::setActiveFrame(int index) {
    
}

void Scrubber::clear() {

}

void Scrubber::frameClicked(QListWidgetItem *item){
    std::cout<<item->text().toStdString()<<std::endl;
}

void Scrubber::reordered(QDropEvent* event){
    std::cout<<"reordered"<<std::endl;
}

void Scrubber::dropEvent(QDropEvent *event){
    event->accept();
    std::cout<<"reordered"<<std::endl;
}
