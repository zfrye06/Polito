#include "layermenu.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QPalette>
#include <QLabel>
#include <QIcon>
#include <QSize>

// TODO: We shouldn't be manually managing the layout and indices of stuff at all here...

LayerMenu::LayerMenu(QWidget *parent, vector<unique_ptr<Frame>> *frames) : QWidget(parent) {
    this->frames = frames;

    addLayerButton = new QPushButton();
    removeLayerButton = new QPushButton();
    moveLayerUp = new QPushButton();
    moveLayerDown = new QPushButton();

    addLayerButton->setIcon(addIcon);
    removeLayerButton->setIcon(deleteIcon);

    layerMenuLayout = new QVBoxLayout(this);
    layerButtons = new QHBoxLayout();
    layerMenuLayout->addLayout(layerButtons);

    layerButtons->addWidget(addLayerButton);
    layerButtons->addWidget(removeLayerButton);
    layerButtons->addWidget(moveLayerUp);
    layerButtons->addWidget(moveLayerDown);

    list = new QListWidget();
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    list->setFlow(QListView::TopToBottom);
    list->setIconSize(QSize(100,100));
    list->setAlternatingRowColors(true);

    layerMenuLayout->addWidget(list);

    addLayer(0);

    list->setCurrentRow(0);

    connect(addLayerButton, &QPushButton::clicked,this, &LayerMenu::addLayerButtonClicked);
    connect(removeLayerButton, &QPushButton::clicked, this, &LayerMenu::deleteLayerButtonClicked);
    connect(moveLayerUp, &QPushButton::clicked, this, &LayerMenu::moveLayerUpButtonClicked);
    connect(moveLayerDown, &QPushButton::clicked, this, &LayerMenu::moveLayerDownButtonClicked);
    connect(list, &QListWidget::clicked, this, &LayerMenu::layerClicked);
}

void LayerMenu::updateLayer(){
    vector<Layer*> layers = frames->at(currentFrameNumber)->getLayers();
    Layer* layer = layers.at(list->currentRow());
    QPixmap px = layer->pixmap();
    QIcon icon(px);

    QListWidgetItem* item = list->item(list->currentRow());
    item->setIcon(icon);
}

void LayerMenu::addExistingLayer(int index){
    vector<Layer*> layers = frames->at(currentFrameNumber)->getLayers();
    Layer* layer = layers.at(index);
    QSize size(100,100);
    QPixmap pixmap = layer->pixmap();
    QIcon icon(pixmap);

    QListWidgetItem* item = new QListWidgetItem(pixmap, "");
    list->addItem(item);
}

void LayerMenu::layerClicked(){
    emit activeLayerChangedSignal(list->currentRow());
}

void LayerMenu::setCurrentFrame(int index){
    currentFrameNumber = index;
}

void LayerMenu::addLayer(int index) {
    QSize size(100,100);
    QPixmap pixmap;
    QIcon icon(pixmap);

    QListWidgetItem* item = new QListWidgetItem(icon, "");
    item->setSizeHint(size);
    list->insertItem(list->currentRow(), item);
    item->setTextAlignment(Qt::AlignCenter);
}

void LayerMenu::moveLayer(int from, int to) {
    auto item = list->takeItem(from);
    list->insertItem(to, item);
}

void LayerMenu::removeLayer(int index) {
    auto item = list->takeItem(index);
    delete item;
}

void LayerMenu::setActiveLayer(int index) {
    list->setCurrentRow(index);
}

void LayerMenu::clear() {
    list->clear();
}

void LayerMenu::addLayerButtonClicked() {
    vector<Layer*> layers = frames->at(currentFrameNumber)->getLayers();
    if(layers.size() >= 4){
        return;
    }
    emit layerAddedSignal(list->currentRow());
}

void LayerMenu::deleteLayerButtonClicked() {
    emit layerDeletedSignal(list->currentRow());
}

void LayerMenu::moveLayerUpButtonClicked(){
    emit layersSwappedSignal(list->currentRow(), list->currentRow() + 1);
}

void LayerMenu::moveLayerDownButtonClicked(){
    emit layersSwappedSignal(list->currentRow(), list->currentRow() - 1);
}
